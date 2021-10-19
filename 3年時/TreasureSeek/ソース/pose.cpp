//=============================================================================
// ���� [game.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: 
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "game.h"
#include "pose.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TIME		( 1000 )
#define INIT_TEX_Y		( 0.0f )
#define INIT_TEX_HEIGHT	( 1.0f / 2.0f )
#define NUMBER_INIT		( 2 )
#define MAX_NUNBER		( 5 )

//=============================================================================
// �֐���	: pose
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �|�[�Y�C���X�^���X����
//=============================================================================
CPose::CPose(void)
{
	ZeroMemory(m_apPose, sizeof(m_apPose) );			// �^�C�g���摜������
	ZeroMemory(m_pTutorial, sizeof(m_pTutorial) );		// �`���[�g���A��
	m_fTexY			= INIT_TEX_Y;						// ���ꂼ��̏����e�N�X�`��Y���W
	m_fTexHeight	= INIT_TEX_HEIGHT;					// ���ꂼ��̏����e�N�X�`���̍���
	m_nNumber		= NUMBER_INIT;						// �ǂ����w���Ă��邩
	m_bTutorial		= false;
}

//=============================================================================
// �֐���	: ~CPose
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �|�[�Y�C���X�^���X�j��
//=============================================================================
CPose::~CPose(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �Ȃ�
// �@�\		: ������
//=============================================================================
HRESULT CPose::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	for( int i = 0; i < MAX_POSE; i++ )
	{
		m_apPose[i] = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, -1);
		m_apPose[i]->SetColor(0, 0, 0, 0);
	}

	// �o�b�N�|���S��
	m_apPose[1]->SetPosition( (float)WINDOW_WIDTH / 5.0f, (float)WINDOW_HEIGHT / 7.0f);
	
	// �R���e�B�j���[
	m_apPose[2]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 6.5f);
	m_apPose[2]->SetTexure(0.0f, 0.0f, 1.0f, 0.5f); 

	// ���g���C
	m_apPose[3]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 4.5f);
	m_apPose[3]->SetTexure(0.0f, 0.0f, 1.0f, 0.5f);

	// �^�C�g����
	m_apPose[4]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 3.2f);
	m_apPose[4]->SetTexure(0.0f, 0.0, 1.0f, 0.5f);

	// �`���[�g���A��
	m_apPose[5]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 2.7f);
	m_apPose[5]->SetTexure(0.0f, 0.0, 1.0f, 0.5f);

	float fPointerPosX = m_apPose[m_nNumber]->GetPosition().x - 30;
	float fPointerPosY = m_apPose[m_nNumber]->GetPosition().y + 20;

	// �J�[�\��
	m_apPose[6]->SetPosition(fPointerPosX , fPointerPosY);
	return S_OK;
}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �I��
//=============================================================================
void CPose::Uninit(void)
{
	CScene::ReleaseAll();		// �V�[���j��
}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �X�V
//=============================================================================
void CPose::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();		// �L�[�{�[�h���擾
	
	if( m_bTutorial == false )
	{
		if( pKeyboard->KeyPush(DIK_W) )
		{
			if( m_nNumber > NUMBER_INIT )
			{
				m_nNumber--;
			}
		}
		else if( pKeyboard->KeyPush(DIK_S) )
		{
			if( m_nNumber < (MAX_POSE - 2) )
			{
				m_nNumber++;
			}
		}
	}
	float fPointerPosX = m_apPose[m_nNumber]->GetPosition().x - 30;
	float fPointerPosY = m_apPose[m_nNumber]->GetPosition().y + 20;
	m_apPose[6]->SetPosition(fPointerPosX , fPointerPosY);
	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		if( m_nNumber > 2  && m_nNumber < (MAX_POSE - 2) )
		{
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);
			CGame::SetFaceFlag(true);
		}
		else if( m_nNumber == 2 )
		{
			CGame::SetPoseFlag(false);
		}
		else if( m_nNumber == (MAX_POSE - 2) )
		{
			for( int tutorial = 0; tutorial < 2; tutorial++ )
			{
				if( m_pTutorial[tutorial] == NULL )
				{
					m_pTutorial[tutorial] = CScene2D::Create( 0.0f, 0.0f, 640, 480, -1);
					m_pTutorial[tutorial]->SetColor(255, 255, 255, 255);
					m_bTutorial = true;
				}
				else
				{
					m_pTutorial[tutorial]->SetColor(0, 0, 0, 0);
					m_pTutorial[tutorial]->SetTexNum(-1);
					m_pTutorial[tutorial]->Release();
					m_pTutorial[tutorial] = NULL;
					m_bTutorial = false;
				}
			}
			if( m_pTutorial[1] != NULL )
			{
				m_pTutorial[1]->SetColor(0, 0, 255, 255);
				m_pTutorial[1]->SetTexNum(25);
			}
		}
	}
}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �`��
//=============================================================================
void CPose::Draw(void)
{
	CScene::DrawAll();
}
