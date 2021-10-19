//=============================================================================
// �c�[���쐬�̑O�菇�@�@�@�@�@�@�t�B�[���h�쐬�c�[���p
//  
// ���C������ [maneger.cpp]
//
// �@�\ : �}�l�[�W���[����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "renderer.h"		// �����_���[
#include "data.h"			// �f�[�^
#include "scene.h"			// �V�[��
#include "inputkeyboard.h"	// ���̓L�[�{�[�h
#include "fade.h"			// �t�F�[�h
#include "logo.h"			// ���S
#include "title.h"			// �^�C�g��
#include "tutorial.h"		// �`���[�g���A��
#include "game.h"			// �Q�[��
#include "result.h"			// ���U���g
#include "ranking.h"		// �����L���O
#include "score.h"			// �X�R�A
#include "debugproc.h"		// �f�o�b�O
#include "manager.h"		// �}�l�[�W��
#include "scene2D.h"		// 2D�I�u�W�F�N�g
#include "sceneX.h"			// X�I�u�W�F�N�g

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
HWND			CManager::m_hWnd;				// �E�B���h�E�n���h���錾
CRenderer		*CManager::m_pRenderer;			// �����_���[�|�C���^�錾
CInputKeyboard	*CManager::m_pKeyboard;			// �L�[�{�[�h�|�C���^�錾
CManager::MODE	CManager::m_Mode;				// ���[�h�錾
CLogo			*CManager::m_pLogo;				// ���S�|�C���^�錾
CTitle			*CManager::m_pTitle;			// �^�C�g���|�C���^�錾
CTutorial		*CManager::m_pTutorial;			// �`���[�g���A���|�C���^�錾
CGame			*CManager::m_pGame;				// �Q�[���|�C���^�錾
CResult			*CManager::m_pResult;			// ���U���g�|�C���^�錾
int				CManager::m_nRankScore;			// �����N�X�R�A�錾
CRanking		*CManager::m_pRanking;			// �����L���O�|�C���^�錾
CFade			*CManager::m_pFade;				// �t�F�[�h�|�C���^�錾
CDebug			*CManager::m_pDebug;			// �f�o�b�O�|�C���^�錾

//=============================================================================
//	�֐���	: CManager
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�C���X�^���X����
//=============================================================================
CManager::CManager(void)
{
	// �C���X�^���X����
	m_hWnd			= NULL;			// �E�B���h�E�n���h��������
	m_pRenderer		= NULL;			// �����_���[�|�C���^������
	m_pKeyboard		= NULL;			// �L�[�{�[�h�|�C���^������
	m_Mode			= MODE_LOGO;	// ���[�h������
	m_pLogo			= NULL;			// ���S�|�C���^������
	m_pTitle		= NULL;			// �^�C�g���|�C���^������
	m_pTutorial		= NULL;			// �`���[�g���A��������
	m_pGame			= NULL;			// �Q�[���|�C���^������
	m_pResult		= NULL;			// ���U���g������
	m_pRanking		= NULL;			// �����L���O������
	m_nRankScore	= 0;			// �����N�X�R�A������
	m_pFade			= NULL;			// �t�F�[�h������
	m_pDebug		= NULL;			// �f�o�b�O������
}

//=============================================================================
//	�֐���	: CManager
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�C���X�^���X�j��
//=============================================================================
CManager::~CManager(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: HINSTANCE , HWND , BOOL
//	�@�\	: �}�l�[�W���[������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr;

	m_hWnd = hWnd;		// �E�B���h�E�n���h����ۑ�

	if( m_pRenderer == NULL )
	{
		// �����_���[���쐬����Ă��Ȃ����
		m_pRenderer = NEW CRenderer;				// �����_���[�C���X�^���X����
		hr = m_pRenderer->Init(hWnd, bWindow);		// �����_���[������
		ERROR_CHACK(hr);							// �����_���[���쐬�ɐ���������
	}
	if( m_pKeyboard == NULL )
	{
		// �L�[�{�[�h���쐬����Ă��Ȃ����
		m_pKeyboard = NEW CInputKeyboard;			// �L�[�{�[�h�C���X�^���X����
		hr = m_pKeyboard->Init(hInstance, hWnd);	// �L�[�{�[�h������
		ERROR_CHACK(hr);							// �L�[�{�[�h���쐬�o���Ȃ����
	}

	if( m_pFade == NULL )
	{
		// �t�F�[�h�������Ă��Ȃ����
		m_pFade = NEW CFade;				// �t�F�[�h�C���X�^���X����
		hr = CManager::GetFade()->Init(1);	// �t�F�[�h������
		ERROR_CHACK(hr);					// �G���[�`�F�b�N
	}

	if( m_pDebug == NULL )
	{
		// �f�o�b�O���쐬����Ă��Ȃ����
		m_pDebug = NEW CDebug;
		hr = m_pDebug->Init();
		ERROR_CHACK(hr);
	}

	SetMode(m_Mode);								// ���[�h��ݒ�

	return S_OK;									// �}�l�[�W������������
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�j��
//=============================================================================
void CManager::Uninit(void)
{
	// �������̊J��
	CScene::ReleaseAll();		// �I�u�W�F�N�g���ׂĔj��
	CLASS_DELETE(m_pKeyboard);	// �L�[�{�[�h�C���X�^���X�j��
	CLASS_DELETE(m_pLogo);		// ���S�C���X�^���X�j��
	CLASS_DELETE(m_pTitle);		// �^�C�g���C���X�^���X�j��
	CLASS_DELETE(m_pTutorial);	// �`���[�g���A���C���X�^���X�j��
	CLASS_DELETE(m_pGame);		// �Q�[���C���X�^���X�j��
	CLASS_DELETE(m_pResult);	// ���U���g�C���X�^���X�j��
	CLASS_DELETE(m_pRanking);	// �����L���O�C���X�^���X�j��
	CLASS_DELETE(m_pFade);		// �t�F�[�h�C���X�^���X�j��
	CLASS_DELETE(m_pRenderer);	// �����_���[�C���X�^���X�j��
	CLASS_DELETE(m_pDebug);		// �f�o�b�O�C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�X�V
//=============================================================================
void CManager::Update(void)
{
	m_pKeyboard->Update();
	m_pDebug->Update();
	m_pFade->Update();
	switch(m_Mode)		// ���݂̃��[�h���ǂ��Ȃ̂��擾
	{
	case MODE_LOGO:				// ���S�̏ꍇ
		m_pLogo->Update();		// ���S�X�V
		break;
	case MODE_TITLE:			// �^�C�g���̏ꍇ
		m_pTitle->Update();		// �^�C�g���X�V
		break;
	case MODE_TUTORIAL:			// �`���[�g���A���̏ꍇ
		m_pTutorial->Update();	// �`���[�g���A���X�V
		break;
	case MODE_GAME:				// �Q�[���̏ꍇ
		m_pGame->Update();		// �Q�[���X�V
		break;
	case MODE_RESULT:			// ���U���g�̏ꍇ
		m_pResult->Update();	// ���U���g�X�V
		break;
	case MODE_RANKING:			// �����L���O�̏ꍇ
		m_pRanking->Update();	// �����L���O�X�V
		break;					
	default:					// �Ȃ�ł��Ȃ��ꍇ
		break;					// �����Ȃ�
	}
}

//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �f�o�C�X
//	�@�\	: �}�l�[�W���[�`��
//=============================================================================
void CManager::Draw(void)
{
	///// �`�揈�� /////
	m_pRenderer->Draw();			// �����_���[�`��
}


//=============================================================================
//	�֐���	: SetModde
//	�߂�l	: �Ȃ�
//	����	: ���[�h
//	�@�\	: ���[�h�J��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	HRESULT hr;
	m_Mode = mode;
	switch(mode)
	{
	case MODE_LOGO:									// ���S�̏ꍇ
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		CLASS_DELETE(m_pRanking);					// ���U���g�C���X�^���X�j��
		if( m_pLogo == NULL )
		{
			m_pLogo = NEW CLogo;					// ���S�C���X�^���X����
			hr = m_pLogo->Init(m_hWnd);				// ���S������
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_TITLE:	
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		CLASS_DELETE(m_pGame);						// �Q�[���C���X�^���X�j��
		CLASS_DELETE(m_pLogo);						// ���S�C���X�^���X�j��
		if( m_pTitle == NULL )
		{
			m_pTitle = NEW CTitle;					// �^�C�g���C���X�^���X����
			hr = m_pTitle->Init(m_hWnd);			// �^�C�g��������
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_TUTORIAL:								// �`���[�g���A���̏ꍇ
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		CLASS_DELETE(m_pTitle);						// �^�C�g���C���X�^���X�j��
		if( m_pTutorial == NULL )
		{
			m_pTutorial = NEW CTutorial;			// �`���[�g���A���C���X�^���X����
			hr = m_pTutorial->Init(m_hWnd);			// �`���[�g���A��������
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_GAME:									// �Q�[���̏ꍇ
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		CLASS_DELETE(m_pGame);						// �Q�[���C���X�^���X�j��
		CLASS_DELETE(m_pTutorial);					// �`���[�g���A���C���X�^���X�j��
		if( m_pGame == NULL )
		{
			m_pGame = NEW CGame;					// �Q�[���C���X�^���X����
			hr = m_pGame->Init(m_hWnd);				// �Q�[��������
			if( FAILED(hr) )	
			{
				return;
			}
		}
		break;
	case MODE_RESULT:								// ���U���g�̏ꍇ
		m_nRankScore = m_pGame->GetScore()->GetScore();
		CLASS_DELETE(m_pGame);						// �Q�[���C���X�^���X�j��
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		if( m_pResult == NULL )
		{
			m_pResult = NEW CResult;				// ���U���g�C���X�^���X����
			hr = m_pResult->Init(m_hWnd);			// ���U���g������
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;
	case MODE_RANKING:								// �����L���O�̏ꍇ
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// �t�F�[�h�C��
		if( m_pRanking == NULL )		
		{
			m_pRanking = NEW CRanking;				// �����L���O�C���X�^���X����
			hr = m_pRanking->Init(m_hWnd);			// �����L���O������
			if( FAILED(hr) )
			{
				return ;
			}
		}
		break;
	default:
		break;
	}
}

///// end of file /////




