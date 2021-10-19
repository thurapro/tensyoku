//=============================================================================
// ���� [player.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: �v���C���[����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "manager.h"
#include "camera.h"
#include "item.h"
#include "field.h"
#include "score.h"
#include "shadow.h"
#include "game.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "debugproc.h"
#include "stage.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define JUMP_SPEED	( 10 )						// �W�����v���x
#define GRAVITY		( 0.6f )					// �d��
#define MOVE_X		( 5 )						// ���x

//=============================================================================
// �֐���	: CPlayer
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �C���X�^���X����
//=============================================================================
CPlayer::CPlayer(int nPriority = 3, OBJTYPE objType):CSceneX(nPriority, objType)
{
	// �C���X�^������
	m_pShadow = NULL;
}

//=============================================================================
// �֐���	: ~CPlayer
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CPlayer::~CPlayer(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[����
//=============================================================================
CPlayer *CPlayer::Create(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	CPlayer *pPlayer;		// �v���C���[�錾
	pPlayer = NEW CPlayer;	// �v���C���[����
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
HRESULT CPlayer::Init(void)
{
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �Ȃ�
// �@�\		: �v���C���[������
//=============================================================================
HRESULT CPlayer::Init(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// �v���C���[������
	ERROR_CHACK(hr);												// �G���[�`�F�b�N
	m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI;							// �v���C���[�̌�����ݒ�	
	m_rotVector = m_pos - m_oldpos;									// �v���C���[�̕����x�N�g���v�Z
	D3DXVec3Normalize(&m_rotVector, &m_rotVector);					// �����x�N�g����P�ʃx�N�g����
	m_bJump		= false;											// �W�����v�t���O������				
	m_bMove		= false;											// �ړ��t���O������
	m_nStopCnt	= 0;												// �Î~�J�E���g������
	m_fRadius	= 15.0f;											// �v���C���[�̔��a
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
void CPlayer::Uninit(void)
{
	CSceneX::Uninit();	// �I������
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[�X�V
//=============================================================================
void CPlayer::Update(void)
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

	m_fMoveY -= GRAVITY;

	// ����̈ʒu��ۑ�
	m_oldpos = m_pos;

	D3DXVECTOR3 NextPos = m_pos;

	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE )
	{
		// �v���C���[�̕����x�N�g��
		if(pKeyboard->KeyState(DIK_W))
		{	
			m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI;
			m_pos.x += sinf(m_rot.y  - D3DX_PI) * MOVE_X;
			m_pos.z += cosf(m_rot.y  - D3DX_PI) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_S))
		{
			m_rot.y = CGame::GetCamera()->GetRot();
			m_pos.x -= sinf(m_rot.y) * MOVE_X;
			m_pos.z -= cosf(m_rot.y) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_A))
		{
			m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI / 2;
			m_pos.x -= cosf(m_rot.y - D3DX_PI / 2) * MOVE_X;
			m_pos.z += sinf(m_rot.y - D3DX_PI / 2) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_D))
		{
			m_rot.y = CGame::GetCamera()->GetRot() - D3DX_PI / 2;
			m_pos.x += cosf(m_rot.y + D3DX_PI / 2) * MOVE_X;
			m_pos.z -= sinf(m_rot.y + D3DX_PI / 2) * MOVE_X;
			m_bMove = true;
		}
		else
		{
			m_bMove = false;
		}
		
		CGame::GetStage()->GetFieldNum(FieldMax);

		
		for( int field = 0; field < FieldMax; field++ )
		{
			if(pField[field])
			{
				// �n�ʂ��擾�ł����̂Ȃ�
				fHeight = pField[field]->GetHeight(m_pos);	// �n�ʂ̍������擾
			}
		}
		if(pKeyboard->KeyPush(DIK_SPACE))
		{
			// �W�����v�L�[�������ꂽ��
			if( m_bJump == false )
			{
				m_fMoveY = JUMP_SPEED;			// �W�����v�𑬓x
				m_bJump = true;					// �W�����v���Ă���
			}
			m_bMove = true;						// �v���C���[��������
		}
		if(m_bJump == true )
		{
			// �����W�����v���Ă���̂Ȃ�
			m_pos.y += m_fMoveY;				// �W�����v��������
		}
		else
		{
			// �W�����v���Ă��Ȃ����
			m_pos.y = fHeight;					// �n�ʂƂ̓����蔻��			
		}
		if( fHeight >= m_pos.y && m_bJump == true )
		{
			// �n�ʂ̍����������ŁA�W�����v�t���O�������Ă�����
			m_bJump = false;					// �W�����v���Ă��Ȃ��Ƃ���
		}
		if( m_bMove == false )
		{
			// �v���C���[�������Ȃ����
			m_nStopCnt++;						// �v���C���[�̐Î~�J�E���g��������
		}
		else
		{
			// �v���C���[����������
			m_nStopCnt = 0;						// �v���C���[�̐Î~�J�E���g��0�ɏ�����
		}
	}

	m_rotVector = m_pos - m_oldpos;									// �v���C���[�̕����x�N�g���v�Z
	D3DXVec3Normalize(&m_rotVector, &m_rotVector);					// �����x�N�g����P�ʃx�N�g����

	m_pShadow->SetPosition( m_pos.x, fHeight + 1, m_pos.z);

	pDebug->Print("�v�ʒu x:%.2f y:%.2f z:%.2f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebug->Print("�v���� x:%.2f y:%.2f z:%.2f\n", m_rot.x, m_rot.y, m_rot.z);
	pDebug->Print("�v�����x�N�g�� x: %.2f y: %.2f z: %.2f\n", m_rotVector.x, m_rotVector.y, m_rotVector.z);
	pDebug->Print("�v�O�� x:%.2f y:%.2f z:%.2f\n", m_oldpos.x, m_oldpos.y, m_oldpos.z);
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �v���C���[�`��
//=============================================================================
void CPlayer::Draw(void)
{
	CSceneX::Draw();	// �`�揈��
}


float CPlayer::PlayerRotition(D3DXVECTOR3 rot, D3DXVECTOR3 Next)
{
	float fDotProduct = 0;
	float fRadian = 0;
	float fCrossProduct = 0;

	fDotProduct = (rot.x * Next.x) + (rot.y * Next.y) + (rot.z * Next.z);

	if( fDotProduct < -1.0f )
	{
		fDotProduct = -1.0f;
	}
	if( fDotProduct > 1.0f )
	{
		fDotProduct = 1.0f;
	}

	fRadian = acos(fDotProduct);
	fRadian *= 0.1f;
	
	fCrossProduct = (rot.z * Next.x) - (rot.x * Next.z);

	if( fCrossProduct < 0 )
	{
		fRadian *= -1;
	}
	if( fCrossProduct > 1)
	{
		fRadian *= 1;
	}
	return fRadian;
}

///// end of file /////