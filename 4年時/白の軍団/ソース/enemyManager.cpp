/******************************************************************************
/ �G���� [ enemy.cpp ]
/
/ ����� : ���� �Y��
/
/ ����� : 2014/01/20
******************************************************************************/

/*****************************************************************************
/ �C���N���[�h
*****************************************************************************/
#include "manager.h"
#include "DirectInput.h"
#include "enemyManager.h"
//#include "enemyAlpha.h"
//#include "enemyBeta.h"
//#include "enemyGamma.h"
//#include "enemyDelta.h"

/*****************************************************************************
/ �}�N����`
*****************************************************************************/
#define MAX_ENEMY ( 1 )			// �G�̍ő吔

/*****************************************************************************
/ �Œ�ϐ�
*****************************************************************************/
static const int nTimer[] = { 100, 80, 300, 500 };
static const int nTimeAlpha[] = { 60, 100, 400, 300 };	// �A���t�@�̏o������
static const int nTimeBeta[] = { 80, 200, 150, 400 };		// �x�[�^�̏o������
static const int nTimeGamma[] = { 340, 500, 300, 60 };		// �K���}�̏o������
static const int nTimeDelta[] = { 5, 20, 30, 5 };		// �f���^�̏o������

/*****************************************************************************
/ �ÓI�����o�ϐ�
*****************************************************************************/
CEnemyManager	*CEnemyManager::m_pInstance = NULL;		// ���g�̃|�C���^

/*****************************************************************************
/ �֐���	: CEnemy
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�C���X�^���X����
*****************************************************************************/
CEnemyManager::CEnemyManager(void)
{
	// �G�̎�ނɂ���Ă̏o�����Ԑݒ�
}

/*****************************************************************************
/ �֐���	: ~CEnemy
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�̃C���X�^���X�j��
*****************************************************************************/
CEnemyManager::~CEnemyManager(void)
{
	// ���ɏ����Ȃ�
}

/*****************************************************************************
/ �֐���	: Create
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�}�l�[�W������
*****************************************************************************/
CEnemyManager *CEnemyManager::Create(void)
{
	if( !m_pInstance )
	{
		// �C���X�^���X���Ȃ��ꍇ
		m_pInstance = new CEnemyManager;	// �G�}�l�[�W���C���X�^���X����
		m_pInstance->Init();				// �G�}�l�[�W��������
		return m_pInstance;					// �G�}�l�[�W����Ԃ�
	}
	return NULL;
}

/*****************************************************************************
/ �֐���	: Release
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�}�l�[�W���j��
*****************************************************************************/
void CEnemyManager::Release(void)
{
	if( m_pInstance )
	{
		// �C���X�^���X������ꍇ
		delete m_pInstance;		// �C���X�^���X�j��
		m_pInstance = NULL;		// NULL������
	}
}

/*****************************************************************************
/ �֐���	: UnInit
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �I��
*****************************************************************************/
void CEnemyManager::Init( void )
{
	SetTimeRandom(CEnemy::TYPE_ALPHA);
	SetTimeRandom(CEnemy::TYPE_BETA);
	SetTimeRandom(CEnemy::TYPE_DELTA);
	SetTimeRandom(CEnemy::TYPE_GAMMA);
	m_nTime = 0;
}

/*****************************************************************************
/ �֐���	: UnInit
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �I��
*****************************************************************************/
void CEnemyManager::UnInit(void)
{
	if( m_pInstance )
	{
		// �C���X�^���X�����݂��Ă����ꍇ
		delete m_pInstance;	// �G�}�l�[�W���C���X�^���X�j��
		m_pInstance = NULL;
	}
}

/*****************************************************************************
/ �֐���	: Update
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �X�V
*****************************************************************************/
void CEnemyManager::UpDate(void)
{
	//// �v���C���[�̈ʒu�擾
	// CPlayer *pPlayer = 0;
	// pPlayer = CManager::GetPlayer();

	CINPUTKEYBOARD *pKeyboard = CManager::GetKeyboard();
	CEnemy *pInstance = NULL;

	//-----------------------------------------------------------------
	// �f�o�b�O�R�[�h
	if( pKeyboard->Push( DIK_1 ) )
	{
		CEnemy::Create( CEnemy::TYPE_ALPHA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_2 ) )
	{
		CEnemy::Create( CEnemy::TYPE_BETA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_3 ) )
	{
		CEnemy::Create( CEnemy::TYPE_GAMMA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_4 ) )
	{
		CEnemy::Create( CEnemy::TYPE_DELTA, VECTOR3D(0, 0, 0) );
	}

	//----------------------------------------------------------------------------------

	float fAngle = rand() % 200 / 100.0f;
	float fRadius = rand() % 100 / 10.0f;

	float fPosX = cosf(fAngle * CSceneGL::PI) * fRadius;
	float fPosY = sinf(fAngle * CSceneGL::PI) * fRadius;

	if( (m_nTime % m_nAlphaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_ALPHA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_ALPHA );
	}

	if( (m_nTime % m_nBetaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_BETA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(1.0f, 1.0f, 1.0f) );
		SetTimeRandom( CEnemy::TYPE_BETA );
	}

	if( (m_nTime % m_nDeltaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_DELTA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_DELTA );
	}

	if( (m_nTime % m_nGammaTime) == 0  )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_GAMMA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_GAMMA );
	}


	m_nTime++;
}


/*****************************************************************************
/ �֐���	: SetTimeRandom
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�̏o�����Ԃ������_���Ō��߂�
*****************************************************************************/
void CEnemyManager::SetTimeRandom( CEnemy::TYPE type )
{
	int n = 0;					// �����_���ŏo���l�̕ۊǗp
	int size = 0;
	switch( type )
	{
	case CEnemy::TYPE_ALPHA:
		{
			// �����_���Ŏ��Ԃ�ݒ�
			size = ( sizeof( nTimeAlpha ) / sizeof( nTimeAlpha[0] ) );

			n = rand() % size;

			// �A���t�@�^�C�v�̓G�o�����Ԑݒ�
			m_nAlphaTime = nTimeAlpha[n];
			break;
		}
	case CEnemy::TYPE_BETA:
		{
			size = ( sizeof( nTimeBeta ) / sizeof( nTimeBeta[0] ) );

			n = rand() % size;
	
			// �A���t�@�^�C�v�̓G�o�����Ԑݒ�
			m_nBetaTime = nTimeBeta[n];
			break;
		}
	case CEnemy::TYPE_DELTA:
		{
			size = ( sizeof( nTimeDelta ) / sizeof( nTimeDelta[0] ) ); 

			n = rand() % size;
	
			// �A���t�@�^�C�v�̓G�o�����Ԑݒ�
			m_nDeltaTime = nTimeDelta[n];
			break;
		}
	case CEnemy::TYPE_GAMMA:
		{
			size = ( sizeof( nTimeDelta ) / sizeof( nTimeDelta[0] ) );

			n = rand() %  size;

			// �A���t�@�^�C�v�̓G�o�����Ԑݒ�
			m_nGammaTime = nTimeGamma[n];
			break;
		}
	}
}

