//=============================================================================
// �A�C�e������[item.cpp]
//
// ����� : ���� �Y��
//
// �@�\ :  �A�C�e��
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "manager.h"
#include "field.h"
#include "shadow.h"
#include "game.h"
#include "data.h"
#include "title.h"
#include "player.h"
#include "stage.h"
#include "score.h"
#include "item.h"

//=============================================================================
// �֐���	: CItem
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X����
//=============================================================================
CItem::CItem(int nPriority, OBJTYPE objType):CSceneX(nPriority, objType)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̌���
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// X�I�u�W�F�N�g�̑傫��
	m_nModelNum		= MODEL_NUM_INIT;			// ���f���ԍ�
	m_nTextureNum	= TEXTURE_NUM_INIT;			// �e�N�X�`���ԍ�
	m_pTexture		= NULL;						// �e�N�X�`���f�[�^
	m_pShadow		= NULL;						// �e�̏�����
}

//=============================================================================
// �֐���	: ~CItem
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CItem::~CItem(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: CItem		(�G���[ NULL) 
// �����l	: �\���ʒu ( X , Y, Z ) , �e�N�X�`���ԍ�
// �@�\		: �Ȃ�
//=============================================================================
CItem *CItem::Create(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;					// �G���[�`�F�b�N�ϐ�
	CItem *pItem = NULL;		// �A�C�e��������
	pItem = NEW CItem;			// �A�C�e���C���X�^���X����
	hr = pItem->Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);
	if( FAILED(hr) )
	{
		// �G���[�`�F�b�N
		return NULL;		// �쐬���s
	}
	return pItem;			// �A�C�e����Ԃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT 
// �����l	: �\���ʒu ( X , Y, Z ) , �e�N�X�`���ԍ�
// �@�\		: �Ȃ�
//=============================================================================
HRESULT CItem::Init(void)
{
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT 
// �����l	: �\���ʒu ( X , Y, Z ) , ���f���ԍ� , �e�N�X�`���ԍ�
// �@�\		: �Ȃ�
//=============================================================================
HRESULT CItem::Init(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;		// �G���[�`�F�b�N�ϐ�
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// �A�C�e��������
	m_fRadius	= 5.0f;
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	if( m_pShadow == NULL )
	{
		m_pShadow = CShadow::Create(m_pos.x, m_pos.y, m_pos.z, 10, 0, 10, 5);
	}

	return S_OK;		// ����R�[�h
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �A�C�e���I������
//=============================================================================
void CItem::Uninit(void)
{
	CSceneX::Uninit();		// �A�C�e���j��
	m_pShadow->Uninit();
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �A�C�e���X�V����
//=============================================================================
void CItem::Update(void)
{
	float fHeight = 0;
	CField	**pField = NULL;
	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_GAME:
		pField = CGame::GetStage()->GetField();
		break;
	default:
		break;
	}

	for( int i = 0; i < MAX_LIST; i++ )
	{
		CScene *pScene;
		pScene = CScene::GetScene(i);	
		while(pScene)
		{
			CScene *pNext = pScene->GetNext();
			CScene::OBJTYPE objType = pScene->GetObjType();
			if( objType == OBJTYPE_PLAYER )
			{
				CPlayer *pPlayer  = CGame::GetPlayer();
			
				D3DXVECTOR3 objPos = pPlayer->GetPosition();
				D3DXVECTOR3 HitPos = objPos - m_pos;
				float fLength = sqrtf( (HitPos.x * HitPos.x) + (HitPos.z * HitPos.z) );
				float fR = m_fRadius + pPlayer->GetRadius();			// ���a�̑����Z �����̔��a + ������I�u�W�F�N�g�̔��a
				if( fLength < fR )
				{
					Release();
					CScore *pScore = CGame::GetScore();
					if(pScore)
					{
						pScore->SetScore(1);
						break;
					}
				}
			}
			pScene = pNext;
		}
	}
	m_rot.y += D3DX_PI * 0.7f;

	int FieldMax = 0;
	CGame::GetStage()->GetFieldNum(FieldMax);

	for( int field = 0; field < FieldMax; field++ )
	{
		fHeight = pField[field]->GetHeight(m_pos);
	}
	m_pos.y = fHeight + m_fRadius;

	m_pShadow->SetPosition(m_pos.x, fHeight + 1, m_pos.z);
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �A�C�e���`��
//=============================================================================
void CItem::Draw(void)
{
	CSceneX::Draw();		// �`��
}

// end of file