//=============================================================================
//
// �}�l�[�W���[����[manager.cpp]	���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�[
//=============================================================================
CTitle *CManager::m_pTitle = 0;
CGame *CManager::m_pGame = 0;
CResult *CManager::m_pResult = 0;
CInput *CManager::m_pInput = 0;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//-----------------------------------------------------------------------------
// �}�l�[�W���[�R���X�g���N�^
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ �C���X�^���X����
//-----------------------------------------------------------------------------
CManager::CManager()
{
	// ����
}

//-----------------------------------------------------------------------------
// �}�l�[�W���[�f�X�g���N�^
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ �C���X�^���X�j��
//-----------------------------------------------------------------------------
CManager::~CManager()
{
	// �j��
}

//-----------------------------------------------------------------------------
// �}�l�[�W���[������
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ ����������
//-----------------------------------------------------------------------------
void CManager::Init(void)
{
	m_pTitle = NULL;					// �^�C�g���|�C���^������
	m_pGame = NULL;						// �Q�[���|�C���^������
	m_pResult = NULL;					// ���U���g�|�C���^������
	m_pInput = NULL;					// ���̓|�C���^������
	m_mode = MODE_TITLE;				// ���[�h������
	if(m_pInput == NULL)
	{
		// ���̓|�C���^���Ȃ�������
		m_pInput = new CInput;			// ���̓|�C���^����
		m_pInput->Init();				// ���̓|�C���^������
	}
	SetMode(MODE_TITLE);				// ���[�h�Z�b�g
}

//-----------------------------------------------------------------------------
// �}�l�[�W���[����
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ �I������
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	if(m_pInput != NULL)
	{
		// ���̓|�C���^�������
		delete m_pInput;				// ���̓|�C���^��j��
		m_pInput = NULL;				// ���̓|�C���^�̒��g��������
	}
	
	switch(m_mode)
	{
		// �e���[�h�̔j��
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// �^�C�g���|�C���^�̒��g�������
			delete m_pTitle;			// �^�C�g���|�C���^�j��
			m_pTitle = NULL;			// �^�C�g���|�C���^������
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// �Q�[���|�C���^�̒��g�������
			delete m_pGame;				// �Q�[���|�C���^�̔j��
			m_pGame= NULL;				// �Q�[���|�C���^�̏�����
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// ���U���g�|�C���^�̒��g�������
			delete m_pResult;			// ���U���g�|�C���^�̔j��
			m_pResult = NULL;			// ���U���g�|�C���^�̏�����
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// �}�l�[�W���[�̍X�V
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ �}�l�[�W���[�X�V
//-----------------------------------------------------------------------------
void CManager::Update(void)
{
	m_pInput->Update();					// ���͍X�V
	switch(m_mode)
	{
		// �e���[�h�X�V
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// �����^�C�g���|�C���^��NULL�łȂ����
			m_pTitle->Update();		// �^�C�g���X�V
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// �����Q�[���|�C���^��NULL�łȂ����
			m_pGame->Update();		// �Q�[���X�V
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// �������U���g�|�C���^��NULL�łȂ����
			m_pResult->Update();	// ���U���g�X�V
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// �}�l�[�W���[�̕`��
// �߂�l �Ȃ�
// ���� �Ȃ�
// �@�\ �}�l�[�W���[�`��
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	switch(m_mode)
	{
		// �e���[�h�`��
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// �����^�C�g���|�C���^��NULL�łȂ����
			m_pTitle->Draw();		// �^�C�g���`��
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// �����Q�[���|�C���^��NULL�łȂ����
			m_pGame->Draw();		// �Q�[���`��
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// �������U���g�|�C���^��NULL�łȂ����
			m_pResult->Draw();		// ���U���g�`��
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// ���[�h�Z�b�g
// �߂�l �Ȃ�
// ���� ���[�h
// �@�\ ���[�h�Z�b�g
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	m_mode = mode;						// ���݂̃��[�h��ۑ�
	switch(m_mode)
	{
	case MODE_TITLE:
		if(m_pResult != NULL)
		{
			// ���U���g���������ꍇ
			m_pResult->Uninit();		// ���U���g�I��
			delete m_pResult;			// ���U���g�j��
			m_pResult = NULL;			// ���U���g�|�C���^������
		}
		m_pTitle = new CTitle;			// �^�C�g������
		m_pTitle->Init();				// �^�C�g��������
		break;
	case MODE_GAME:
		if(m_pTitle != NULL)
		{
			// �^�C�g�����������ꍇ
			m_pTitle->Uninit();			// �^�C�g���I��
			delete m_pTitle;			// �^�C�g���j��
			m_pTitle = NULL;			// �^�C�g���|�C���^������
		}
		m_pGame = new CGame;			// �Q�[������
		m_pGame->Init();				// �Q�[��������
		break;
	case MODE_RESULT:
		if(m_pGame != NULL)
		{
			// �Q�[�����c���Ă����ꍇ
			m_pGame->Uninit();			// �Q�[���I��
			delete m_pGame;				// �Q�[���j��
			m_pGame = NULL;				// �Q�[���|�C���^������
		}
		m_pResult = new CResult;		// ���U���g����
		m_pResult->Init();				// ���U���g������
		break;
	default:
		break;
	}
}
