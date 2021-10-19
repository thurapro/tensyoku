//=============================================================================
// �G�̏���[ enemy.cpp ]
//
// ����� : ���� �Y��
//
// �@�\ : �G�̏���
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "manager.h"
#include "camera.h"
#include "item.h"
#include "score.h"
#include "shadow.h"
#include "game.h"
#include "stage.h"
#include "enemy.h"

//=============================================================================
// �֐���	: CEnemy
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �C���X�^���X����
//=============================================================================
CEnemy::CEnemy(int nPriority, OBJTYPE objType):CSceneX(nPriority, objType)
{
	// �C���X�^������
	m_pShadow = NULL;
}

//=============================================================================
// �֐���	: ~CEnemy
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CEnemy::~CEnemy(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[����
//=============================================================================
CEnemy *CEnemy::Create(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	CEnemy *pPlayer;		// �v���C���[�錾
	pPlayer = NEW CEnemy;	// �v���C���[����
	hr = pPlayer->Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// �v���C���[������
	if( FAILED(hr) )
	{
		// �v���C���[�������s
		return NULL;		// �G���[�R�[�h
	}
	return pPlayer;			// �v���C���[��߂�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �Ȃ�
// �@�\		: �v���C���[������
//=============================================================================
HRESULT CEnemy::Init(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// �v���C���[������
	ERROR_CHACK(hr);												// �G���[�`�F�b�N
	m_rot.y = CGame::GetCamera()->GetRot();							// �v���C���[�̌�����ݒ�	
	m_fRadius	= 10.5f;											// �v���C���[�̔��a
	if( m_pShadow == NULL )
	{
		// �e��������
		m_pShadow =CShadow::Create(m_pos.x, m_pos.y, m_pos.z, 10, 0, 10, 5);
	}
	return S_OK;		// ����I��
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[�I��
//=============================================================================
void CEnemy::Uninit(void)
{
	CSceneX::Uninit();	// �I������
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[�X�V
//=============================================================================
void CEnemy::Update(void)
{
	CCamera *pCamera = NULL;
	CDebug *pDebug = CManager::GetDebug();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CField **pField = NULL;
	int		FieldMax = 0;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_GAME:
		pField = CGame::GetStage()->GetField();
		pCamera = CGame::GetCamera();
		break;
	case CManager::MODE_RESULT:
		break;
	}

	float fHeight = 0;
	float fRotition = 0;
	float fAngle = 0;

	CGame::GetStage()->GetFieldNum(FieldMax);

	if(pField)
	{
		// �n�ʂ��擾�ł����̂Ȃ�
		for( int field = 0; field < FieldMax; field++ )
		{
			fHeight = pField[field]->GetHeight(m_pos);	// �n�ʂ̍������擾
		}
	}
	
	m_pShadow->SetPosition( m_pos.x, fHeight + 1, m_pos.z);
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[�`��
//=============================================================================
void CEnemy::Draw(void)
{
	CSceneX::Draw();	// �`�揈��
}

///// end of file /////