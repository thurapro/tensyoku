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
#include "common.h"
#include "main.h"
#include "manager.h"
#include "game.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "player.h"
#include "renderer.h"
#include "camera.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE (15.0f)
#define PLAYER_SCORPE (10) 

//=============================================================================
// �ÓI�����o�ϐ���`
//=============================================================================

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
	m_posCameraP = D3DXVECTOR3(0.0f, 100.0f, -300.0f);	// �J�����̈ʒu������
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̒����_������
	m_vecCameraV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �J�����̃x�N�g��������

	m_Length = 	m_posCameraP - m_posCameraR;			// �J�����̈ʒu�ƒ����_�܂ł̋������v�Z
	m_rotCamera = m_posCameraR - m_posCameraP;
	
	// �J�����̊Ԋu
	m_fLengthInterval = sqrtf( (m_Length.x * m_Length.x) + (m_Length.y * m_Length.y) + (m_Length.z * m_Length.z) );

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
	CDebug *pDebug = CManager::GetDebug();
	CInputKeyboard *pInputKeyboard = CManager::GetInput();	// ���̓|�C���^
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPosition;
	D3DXVECTOR3 PlayerRotition;
	int nStopCnt = 0;

	// �J�����ʒu���璍���_�Ɍ������x�N�g�����Đݒ�
	if( pPlayer )
	{
		PlayerPosition	= pPlayer->GetPosition();			// �v���C���[�̈ʒu���擾
		PlayerRotition	= pPlayer->GetRotition();			// �v���C���[�̕����x�N�g�����擾
		nStopCnt		= pPlayer->GetStopCnt();			// �v���C���[�J�E���g
	}

	m_posCameraR		= PlayerPosition;
	m_posCameraR.y		+= 100.0f;

	if( m_posCameraR.y	< 100.0f || m_posCameraR.y > 40.0f )
	{
		m_posCameraR.y = 50.0f;
	}


	if( CManager::GetInput()->KeyState(DIK_L) )
	{
		m_fRadian += D3DX_PI * 0.01f;
		if( m_fRadian > 6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else if( CManager::GetInput()->KeyState(DIK_J) )
	{
		m_fRadian -= D3DX_PI * 0.01f;
		if( m_fRadian < -6.28f )
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
	m_posCameraP.x		= m_posCameraR.x + sinf(m_fRadian) * -m_fLengthInterval;
	m_posCameraP.z		= m_posCameraR.z + cosf(m_fRadian) * -m_fLengthInterval;


	pDebug->Print("�X�g�b�v�J�E���g %d\n", nStopCnt);
	pDebug->Print("���P: x = %.3f y = %.3f z = %.3f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	pDebug->Print("���R: x = %.3f y = %.3f z = %.3f\n", m_posCameraR.x, m_posCameraR.y, m_posCameraR.z);
	pDebug->Print("��׌�: %.3f \n", m_fRadian);
	
	///// �J�����̒����_ /////
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
								40000000.0f);								// ������e�ʂ܂ł̋���
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);			// �v���W�F�N�V�����}�g���b�N�X�ݒ�
}


float CCamera::CameraRotition(D3DXVECTOR3 Vector0, D3DXVECTOR3 Vector1)
{
	// �P�ʃx�N�g���ۑ��p
	D3DXVECTOR3 shortVec0, shortVec1;
	float		fLength0, fLength1;
	float		fDotProduct = 0;
	float		fRadian = 0;
	float		fCrossProduct = 0;

	// Vector0��P�ʃx�N�g����
	fLength0 = sqrtf( (Vector0.x * Vector0.x) + (Vector0.y * Vector0.y) + (Vector0.z *Vector0.z) );
	shortVec0.x = Vector0.x / fLength0;
	shortVec0.y = Vector0.y / fLength0;
	shortVec0.z = Vector0.z / fLength0;

	// Vector1��P�ʃx�N�g����
	fLength1 = sqrtf( (Vector1.x * Vector1.x) + (Vector1.y * Vector1.y) + (Vector1.z *Vector1.z) );
	shortVec1.x = Vector1.x / fLength1;
	shortVec1.y = Vector1.y / fLength1;
	shortVec1.z = Vector1.z / fLength1;
	
	// ���όv�Z�Ŋp�x���v�Z
	fDotProduct = (shortVec0.x * shortVec1.x) + (shortVec0.y * shortVec1.y) + (shortVec0.z * shortVec1.z);

	// ���όv�Z�덷�C��
	if( fDotProduct < -1.0f )
	{
		fDotProduct = -1.0f;
	}
	if( fDotProduct > 1.0f )
	{
		fDotProduct = 1.0f;
	}

	fRadian = cosf(fDotProduct);
	fRadian *= 0.01f;
	fCrossProduct = shortVec0.z * shortVec1.x - shortVec0.x * shortVec1.z;
	if( fCrossProduct < 0 )
	{
		fRadian *= -1; 
	}
	return fRadian;
}


///// end of file /////

