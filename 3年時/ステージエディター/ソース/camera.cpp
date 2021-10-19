//=============================================================================
// �J�������� [camera.h]
//
// �����	: ���� �Y��
//
// �@�\		: �J�����̏�����
//			: �X�V
//			: �`��
//			: �r���[�擾
//			: �p�x�擾
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "camera.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE (20.0f)			// �J�����̈ʒu�ړ����x
#define MOVE_R (20.0f)
#define PLAYER_SCORPE (10)		// �v���C���[�̌����Ă���ʒu����10����݂�

//=============================================================================
// �֐���	: CCamera
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �J�����C���X�^���X����
//=============================================================================
CCamera::CCamera(void)
{
	// �C���X�^���X����
}

//=============================================================================
// �֐���	: ~CCamera
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �J�����C���X�^���X�j��
//=============================================================================
CCamera::~CCamera(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �Ȃ�
// �@�\		: �J�����̏�����
//			: �J�����̈ʒu������
//			: �J�����̒����_������
//			: �J�����̃x�N�g��������
//			: �J�����̊p�x������
//=============================================================================
void CCamera::Init(void)
{
	///// �J�����ʒu�������J�n /////
	m_posCameraP = D3DXVECTOR3(0.0f, 200.0f, -100.0f);	// �J�����̈ʒu������
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̒����_������
	m_vecCameraV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �J�����̃x�N�g��������

	m_Length	= m_posCameraP - m_posCameraR;			// �J�����̈ʒu�ƒ����_�܂ł̋������v�Z
	m_rotCamera = m_posCameraR - m_posCameraP;			// �J�����̌���
	
	// �J�����̊Ԋu
	m_fLengthInterval = sqrtf( (m_Length.x * m_Length.x) + (m_Length.y * m_Length.y) + (m_Length.z * m_Length.z) );

	// �J�����̊p�x
	m_fRadian = 0;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �J�����̏I������	( ���݂Ȃ� )
//=============================================================================
void CCamera::Uninit(void)
{
	// �I������
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �J�����̍X�V
//			: �J�����̈ʒu(���_�ύX)
//			: �J�����̒����_
//			: �J�����̃x�N�g��
//			: �J�����̊p�x
//=============================================================================
void CCamera::Update(void)
{
	///// �J�����̍X�V�J�n /////

	//�ϐ��錾 
	CDebug *pDebug = CManager::GetDebug();						// �f�o�b�O�|�C���^�擾
	CInputKeyboard *pInputKeyboard = CManager::GetKeyboard();	// ���̓|�C���^�擾
	D3DXVECTOR3 PlayerPosition;									// �v���C���[�ʒu�擾
	D3DXVECTOR3 PlayerRotition;									// �v���C���[�����擾
	int nStopCnt = 0;											// �v���C���[�X�g�b�v�J�E���g�擾

	// �L�[�{�[�h����
	if( pInputKeyboard->KeyState(DIK_Q) )						// ����]
	{
		m_fRadian -= D3DX_PI * 0.01f;
		if( m_fRadian < -6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else if( pInputKeyboard->KeyState(DIK_E) )					// �E��]
	{
		m_fRadian += D3DX_PI * 0.01f;
		if( m_fRadian > 6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else
	{
		if( nStopCnt > 200 )
		{
			if( m_fRadian < PlayerRotition.y )
			{		
				m_fRadian += PlayerRotition.y * 0.007f;
			}
		}
	}

	// ���_�ړ�
	if( pInputKeyboard->KeyState(DIK_Z) )					// ���_����Ɉړ�
	{
		if( !CManager::GetDebug()->GetDebugMode() )
		{
			if( m_posCameraR.y < 640.0f )
			{
				// ��Ɍ�������
				m_posCameraR.y += 5.0f;
			}
		}
		m_posCameraR.y += MOVE_R;
	}
	else if( pInputKeyboard->KeyState(DIK_X) )				// ���_�����Ɉړ�
	{
		if( !CManager::GetDebug()->GetDebugMode() )
		{
			if( m_posCameraR.y > -180.0f )
			{
				m_posCameraR.y -= 5.0f;
			}
		}
		m_posCameraR.y -= MOVE_R;
	}

	if(pInputKeyboard->KeyState(DIK_W) )
	{
		m_move = MOVE;
		m_posCameraR.x += sinf(m_fRadian) * m_move;
		m_posCameraP.x += sinf(m_fRadian) * m_move;
		m_posCameraR.z += cosf(m_fRadian) * m_move;
		m_posCameraP.z += cosf(m_fRadian) * m_move;
	}
	else if(pInputKeyboard->KeyState(DIK_S) )
	{
		m_move = MOVE; 
		m_posCameraR.x -= sinf(m_fRadian) * m_move;
		m_posCameraP.x -= sinf(m_fRadian) * m_move;
		m_posCameraR.z -= cosf(m_fRadian) * m_move;
		m_posCameraP.z -= cosf(m_fRadian) * m_move;
	}

	if(pInputKeyboard->KeyState(DIK_A) )
	{
		m_move = MOVE; 
		m_posCameraR.x -= cosf(m_fRadian) * m_move;
		m_posCameraP.x -= cosf(m_fRadian) * m_move;
		m_posCameraR.z += sinf(m_fRadian) * m_move;
		m_posCameraP.z += sinf(m_fRadian) * m_move;
	}

	else if(pInputKeyboard->KeyState(DIK_D) )
	{
		m_move = MOVE; 
		m_posCameraR.x += cosf(m_fRadian) * m_move;
		m_posCameraP.x += cosf(m_fRadian) * m_move;
		m_posCameraR.z -= sinf(m_fRadian) * m_move;
		m_posCameraP.z -= sinf(m_fRadian) * m_move;
	}

	if( pInputKeyboard->KeyState(DIK_R) )
	{
		m_move = MOVE;
		m_posCameraP.y += m_move;
		m_posCameraR.y += m_move;
	}
	else if( pInputKeyboard->KeyState(DIK_C) )
	{
		m_posCameraP.y -= m_move;
		m_posCameraR.y -= m_move;
	}



	// �f�o�b�O�R�[�h
	if( pInputKeyboard->KeyPush(DIK_F7) )
	{
		Init();		// �J����������
	}
	
	m_posCameraP.x		= m_posCameraR.x + sinf(m_fRadian) * -m_fLengthInterval;
	m_posCameraP.z		= m_posCameraR.z + cosf(m_fRadian) * -m_fLengthInterval;


	pDebug->Print("�X�g�b�v�J�E���g %d\n", nStopCnt);
	pDebug->Print("���P: x = %.3f y = %.3f z = %.3f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	pDebug->Print("���R: x = %.3f y = %.3f z = %.3f\n", m_posCameraR.x, m_posCameraR.y, m_posCameraR.z);
	pDebug->Print("��׌�: %.3f \n", m_fRadian);
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �J�����`��
//			: �r���[�}�g���b�N�X�쐬
//			: �v���W�F�N�V�����}�g���b�N�X�쐬
//=============================================================================
void CCamera::Draw(void)
{
	///// �J�����̕`�揈���J�n /////

	//--- �ϐ��錾 ---//
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxProjection;											// �v���W�F�N�V����

	///// �r���[�}�g���b�N�X�쐬 /////
	D3DXMatrixIdentity(&m_mtxView);										// �r���[�}�g���b�N�X������
	D3DXMatrixLookAtLH(&m_mtxView,										// �r���[�}�g���b�N�X�쐬
					&m_posCameraP,										// �J�����̈ʒu(���_)
					&m_posCameraR,										// �J�����̒����_
					&m_vecCameraV);										// �J�����̏���x�N�g��
 	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);						// �r���[�}�g���b�N�X�ݒ�

	///// �v���W�F�N�V�����}�g���b�N�X�쐬 /////
	D3DXMatrixIdentity(&mtxProjection);									// �v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixPerspectiveFovLH(&mtxProjection,							// �v���W�F�N�V�����}�g���b�N�X�쐬					
								D3DX_PI / 6.0f,							// ����p�ݒ�
								(float)WINDOW_WIDTH / WINDOW_HEIGHT,	// ��ʂ̃A�X�y�N�g��
								1.0f,									// �O�����e�ʂ܂ł̋���
								40000000.0f);							// ������e�ʂ܂ł̋���
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);			// �v���W�F�N�V�����}�g���b�N�X�ݒ�

	CManager::GetDebug()->Print("�J�����ڂ��Ă��\n");	
}




///// end of file /////

