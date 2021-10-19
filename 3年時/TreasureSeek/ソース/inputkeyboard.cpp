//=============================================================================
// �L�[�{�[�h���͏���	[ inputkeyboard.cpp ]
//
// �����	: ���� �Y��
//
// �@�\		: �L�[�{�[�h�𓮂���
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "inputkeyboard.h"

//=============================================================================
// �֐���	: CInputKeyboard
// ����		: �Ȃ�
// �߂�l	: �Ȃ�
// �@�\		: �L�[�{�[�h�C���X�^���X�����@
//=============================================================================
CInputKeyboard::CInputKeyboard(void)
{
}

//=============================================================================
// �֐���	: ~CInputKeyboard
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �L�[�{�[�h�C���X�^���X�j��
//=============================================================================
CInputKeyboard::~CInputKeyboard(void)
{
}

//=============================================================================
// �֐���	: Init�֐�
// ����		: HINSTANCE �C���X�^���X HWND �n���h��
// �߂�l	: HRESULT�@
// �@�\		: �L�[�{�[�h�������@
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;
	hr = CInput::Init(hInstance, hWnd);
	if(FAILED(hr))
	{
		return hr;
	}

	for(int i = 0; i < MAX_KEY; i++)
	{
		m_diKeyState[i] = NULL;	
		m_keyPush[i] = NULL;		
		m_keyRelese[i] = NULL;
	}

	// �I�u�W�F�N�g�̍쐬
	hr = m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDinputDevice, NULL);
	if(FAILED(hr))
	{
		// �I�u�W�F�N�g�������s
		return hr;								// ���͏��������s
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		// �t�H�[�}�b�g�ݒ莸�s
		return hr;								// ���͏������ݒ�
	}
	hr = m_pDinputDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE|DISCL_FOREGROUND));
	if(FAILED(hr))
	{
		// �C���^�[�t�F�[�X�擾���s���
		return hr;								// ���͏��������s
	}

	if(m_pDinput == NULL)
	{
		// �I�u�W�F�N�g�쐬���s���
		return hr;								// ���͏��������s
	}
	return hr;
}

//=============================================================================
// �֐���	: Uninit�֐�
// ����		: �Ȃ�
// �߂�l	: �Ȃ�
// �@�\		: �L�[�{�[�h�̏I��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();			// ���͏I������
}

//=============================================================================
// �֐���	: Update�֐�
// ����		: �Ȃ�
// �߂�l	: �Ȃ�
// �@�\		: �L�[�{�[�h�̍X�V
//=============================================================================
HRESULT CInputKeyboard::Update(void)
{
	HRESULT hr;	
	BYTE KeyOld[MAX_KEY] ={NULL};
	for(int i = 0; i < MAX_KEY; i++)
	{
		KeyOld[i] = m_diKeyState[i];
	}

	hr = m_pDinputDevice->GetDeviceState( MAX_KEY , m_diKeyState);					// �f�o�C�X
	if(SUCCEEDED(hr))
	{
		for(int i = 0; i < MAX_KEY; i++ )
		{
			// �L�[�{�[�h�̃{�^������������
			m_keyPush[i] = (KeyOld[i] ^  m_diKeyState[i]) & m_diKeyState[i];		// �L�[���������u�ԏ���
			m_keyRelese[i] = (KeyOld[i] ^ m_diKeyState[i]) & KeyOld[i];				// �L�[�𗣂����u�ԏ���
		}
		//CManager::GetDebug()->Print(80, 300, "%d\n",m_diKeyState);
	}
	else
	{ 
		// �A�N�Z�X���Ď擾
		m_pDinputDevice->Acquire();
	}
	// �f�[�^�`���ݒ�
	hr = m_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);
	if( FAILED(hr) )
	{
		return E_FAIL;
	}
	return S_OK;
}