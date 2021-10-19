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
#include "manager.h"
#include "data.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "item.h"
#include "stage.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "pose.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SOCRE	( 5 )			// ���_

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CCamera		*CGame::m_pCamera;		// �J�����|�C���^�錾
CLight		*CGame::m_pLight;		// ���C�g�|�C���^�錾
CData		*CGame::m_pData;		// �f�[�^�|�C���^�錾
CStage		*CGame::m_pStage;		// �X�e�[�W�|�C���^�錾
CPlayer		*CGame::m_pPlayer;		// �v���C���[�|�C���^�錾
CEnemy		**CGame::m_ppEnemy;		// �G�|�C���^�錾
CScore		*CGame::m_pScore;		// �X�R�A�[�|�C���^�錾
CTimer		*CGame::m_pTimer;		// �^�C�}�[�|�C���^�錾
CItem		**CGame::m_pItem;		// �A�C�e���|�C���^�錾
bool		CGame::m_bPose;			// �|�[�Y�t���O�錾
bool		CGame::m_bFace;			// �t�F�[�Y�t���O�錾

//=============================================================================
// �֐���	: Game
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X����
//=============================================================================
CGame::CGame(void)
{
	m_pCamera	= NULL;		// �J�����|�C���^������
	m_pLight	= NULL;		// ���C�g�|�C���^������
	m_pData		= NULL;		// �f�[�^�|�C���^������
	m_pStage	= NULL;		// �X�e�[�W�|�C���^������
	m_pPlayer	= NULL;		// �v���C���[�|�C���^������
	m_ppEnemy	= NULL;		// �G�|�C���^������
	m_pScore	= NULL;		// �X�R�A�[�|�C���^������
	m_pTimer	= NULL;		// �^�C�}�[�|�C���^������
	m_pItem		= NULL;		// �A�C�e���|�C���^������
	m_pClear	= NULL;		// �N���A�摜�|�C���^������
	m_bFace		= false;	// ���̃��[�h�ړ�
	m_pPose		= NULL;		// �|�[�Y������
	m_bPose		= false;	// �|�[�Y
}

//=============================================================================
// �֐���	: ~CGame
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X�j��
//=============================================================================
CGame::~CGame(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �E�B���h�E�n���h��
// �@�\		: ������
//=============================================================================
HRESULT CGame::Init(HWND hWnd)
{
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//----------------------------------------------------------------------------
	// �����_�����O�X�e�[�g�̏������ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//

	//-------------------------------------------------------------------------
	// �T���v���[�X�e�[�g�̏������ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if( m_pCamera == NULL )
	{
		// �J�������쐬����Ă��Ȃ����
		m_pCamera = NEW CCamera;			// �J�����C���X�^���X����
		m_pCamera->Init();					// �J����������
	}

	if( m_pLight == NULL )
	{
		// ���C�g���쐬����Ă��Ȃ����
		m_pLight = NEW CLight;				// ���C�g�C���X�^���X����
		hr = m_pLight->Init();				// ���C�g������
		ERROR_CHACK(hr);					// ���C�g���쐬����Ă��邩
	}
	
	if( m_pData == NULL )
	{
		// �f�[�^���쐬����Ă��Ȃ����
		m_pData = NEW CData;								// �f�[�^�C���X�^���X����
		hr = m_pData->Init(hWnd, "data/text/game.txt");		// �f�[�^������
		ERROR_CHACK(hr);									// �f�[�^���쐬���ꂽ��
	}

	NEW_TYPE(m_pStage, CStage);
	hr = m_pStage->Init();
	ERROR_CHACK(hr);

	if( m_pPlayer == NULL )
	{
		// �v���C���[���쐬����Ă��Ȃ����
		m_pPlayer = CPlayer::Create(500, 0, 500, 3, 18);
		if(  m_pPlayer == NULL )
		{
			return E_FAIL;
		}
		m_pPlayer->SetScale( 1.0f, 1.0f, 1.0f);
	}

	if( m_pScore == NULL )
	{
		// �X�R�A���쐬����Ă��Ȃ����
		m_pScore = CScore::Create(0, 40, 0, 40, 12);			// �X�R�A�C���X�^���X����
		if( m_pScore == NULL )
		{
			// �X�R�A���쐬����Ă��Ȃ����
			return E_FAIL;		// �G���[�R�[�h
		}
	}

	if( m_pTimer == NULL )
	{
		m_pTimer = CTimer::Create(350, 40, 0, 40, 12);		// �^�C�}�[�C���X�^���X����
		if( m_pTimer == NULL )
		{
			// �G���[�`�F�b�N
			return E_FAIL;		// �G���[�R�[�h
		}
	}

	m_pItem = NEW CItem*[MAX_ITEM];

	for( int item = 0; item < MAX_ITEM; item++ )
	{
		// �A�C�e��������Ă��Ȃ����
		m_pItem[item] = CItem::Create(30, 0, 500, 3, 18);
		if( m_pItem == NULL )
		{
			// �G���[�`�F�b�N
			return E_FAIL;
		}
		m_pItem[item]->SetScale(1.0f, 1.0f, 1.0f);
	}
	m_pItem[1]->SetPosition(80, 0, -500);
	m_pItem[2]->SetPosition(-200, 0, -80);
	m_pItem[3]->SetPosition(400, 0, -800);
	m_pItem[4]->SetPosition(-400, 0, -500);

	if( m_pPose == NULL )
	{
		m_pPose = NEW CPose;
		hr = m_pPose->Init();
		ERROR_CHACK(hr);
	}

	m_pData->GetSound()->Play(1);

	return S_OK;		// ����R�[�h
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �I��
//=============================================================================
void CGame::Uninit(void)
{
	// ���������
	CScene::ReleaseAll();			// �V�[���j��
	CLASS_DELETE(m_pStage);			// �X�e�[�W�C���X�^���X�j��
	CLASS_DELETE(m_pCamera);		// �J�����C���X�^���X�j��
	CLASS_DELETE(m_pLight);			// ���C�g�C���X�^���X�j��
	CLASS_DELETE(m_pData);			// �f�[�^�C���X�^���X�j��
}

//=============================================================================
// �֐���	: Updata
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �X�V
//=============================================================================
void CGame::Update(void)
{
	int score = 0;											// ���_
	CScene2D **pPose = m_pPose->GetPose();
	unsigned short nPoseNum = m_pPose->GetPoseNum();
	int Time = 0;

	if( CManager::GetInput()->KeyPush(DIK_P) )
	{
		if( m_pPose->GetTutorialFlag() == false )
		{

			if( m_bPose == true )
			{
				m_bPose = false;
				for( int i = 0; i < MAX_POSE; i++ )
				{
					pPose[i]->SetColor(0, 0, 0, 0);
					pPose[i]->SetTexNum(-1);
				}
				m_pPose->SetPoseNum(2);
			}
			else
			{
				m_bPose = true;
				pPose[0]->SetColor(0, 0, 0, 125);
				pPose[1]->SetColor(192, 192, 192, 255);

				for( int i = 2; i < MAX_POSE; i++ )
				{
					pPose[i]->SetColor(255, 255, 255, 255);
				}
				pPose[2]->SetTexNum(20);
				pPose[3]->SetTexNum(21);
				pPose[4]->SetTexNum(22);
				pPose[5]->SetTexNum(23);
				pPose[6]->SetTexNum(24);
			}
		}
	}
	if( m_bPose == false )
	{
		for( int i = 0; i < MAX_POSE; i++ )
		{
			pPose[i]->SetColor(0, 0, 0, 0);
			pPose[i]->SetTexNum(-1);
		}
		m_pCamera->Update();								// �J�����̍X�V
		m_pLight->Update();
		CScene::UpdateAll();								// �Q�[���X�V
		
		score = m_pScore->GetScore();						// ���_�擾
		Time = m_pTimer->GetTime();
		if( score >= MAX_SOCRE )
		{
			// �Œ�������_�ɒB���Ă�����
			if( m_pClear == NULL )
			{
				// �N���A�摜������Ă��Ȃ����
				CManager::SetRankScore(m_pTimer->GetTime());
				m_pClear = CScene2D::Create(60, 30, 500, 300, 17);			// �N���A�쐬
				m_bFace = true;												//�@�ړ��t���O��ON��
				CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// �t�F�[�h���[�h��ݒ�
			}
		}
		else if( Time >= 60 )
		{
			if( m_pClear == NULL )
			{
				m_pClear = CScene2D::Create(60, 30, 500, 300, 17);			// �N���A�쐬
				m_bFace = true;												//�@�ړ��t���O��ON��
				CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// �t�F�[�h���[�h��ݒ�
			}
		}
	}
	else
	{
		m_pPose->Update();
	}
	
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE && m_bFace == true )
	{
		if( nPoseNum == 3 )
		{
			CManager::SetMode(CManager::MODE_GAME);
		}
		else if( nPoseNum == 4 )
		{
			CManager::SetMode(CManager::MODE_TITLE);
		}
		else
		{
			// �t�F�[�h�̐F��0(��)�Ŏ��̃t�F�[�Y�ړ��t���O��ON�ł����
			CManager::SetMode(CManager::MODE_RESULT);			// ���U���g�w�ڍs
		}
	}
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �`��
//=============================================================================
void CGame::Draw(void)
{
	// �t�F�[�h���[�h�łȂ����
	m_pCamera->Draw();
	CScene::DrawAll();
}
