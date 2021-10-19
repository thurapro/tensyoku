//=============================================================================
//
// FAILE NAME [InputKey.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �L�[����
//
//
//=============================================================================
 
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/InputKey.h"
#include <d3dx9.h>
#include <windows.h>

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static LPDIRECTINPUT8 g_pDinput = NULL;					// �L�[���� 
static LPDIRECTINPUTDEVICE8 g_pDinputDevice = NULL;		// �L�[�f�o�C�X
static BYTE g_diKeyState[KYKBOARD_MAX] = {NULL};		// �L�[�������ςȂ�
static BYTE g_keyPhush[KYKBOARD_MAX] = {NULL};			// �L�[���������u��
static BYTE g_keyRelese[KYKBOARD_MAX]  = {NULL};		// ��������


//=============================================================================
//
// �֐���	: InitInput�֐�
//
// �߂�l	: �C���^�[�t�F�[�X���擾�ł�����
//			  �I�u�W�F�N�g���쐬�ł�����
//
// ����		: �C���X�^���X
//			�@H�E�B���h�E
//
// �@�\		: �C���^�[�t�F�[�X�擾
//			: �I�u�W�F�N�g�̍쐬
// 
//=============================================================================

// �C���^�[�t�F�[�X�̎擾
BOOL InitInput(HINSTANCE hInstance , HWND hWnd)
{
	HRESULT hr;

	// �C���^�[�t�F�[�X�̐���
	hr = DirectInput8Create( hInstance,				
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8,
			(void**)&g_pDinput, NULL);
	
	if(FAILED(hr))
	{
		// �C���^�[�t�F�[�X�擾���s���
		return FALSE;
	}

	// �I�u�W�F�N�g�̍쐬
	hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
			&g_pDinputDevice, 
			NULL);

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = g_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);

	hr = g_pDinputDevice->SetCooperativeLevel( hWnd , 
											(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE) );

	// �L�[�{�[�h�̃A�N�Z�X�����擾
	hr = g_pDinputDevice->Acquire();
	if(FAILED(hr))
	{
		return hr;
	}

	if(g_pDinput == NULL)
	{
		// �I�u�W�F�N�g�쐬���s���
		return FALSE;
	}
	
	return TRUE;

}
//=============================================================================
//
// �֐���	: UninitInout�֐�
//
// ����		: �Ȃ�
//
// �߂�l	: �Ȃ�
//
// �@�\		: �L�[�����
//
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�f�o�C�X�̉��
	if(g_pDinputDevice != NULL)
	{
		g_pDinputDevice->Unacquire();
		g_pDinputDevice->Release();
		g_pDinputDevice = NULL;
	}

	// �I�u�W�F�N�g�̉��
	if(g_pDinput != NULL)
	{
		g_pDinput->Release();
		g_pDinput = NULL;
	}

}

//=============================================================================
//
// �֐���	: UpdateInput�֐�
//
// ����		: �Ȃ�
//
// �߂�l	: �Ȃ�
//
// �@�\		: �L�[�̍X�V�@
//
//=============================================================================
void UpdateInput(void)
{
	HRESULT hr;	
	BYTE KeyOld[KYKBOARD_MAX] ={ NULL};

	for(int i = 0; i < KYKBOARD_MAX; i++)
	{
		KeyOld[i] = g_diKeyState[i];
	}

	hr = g_pDinputDevice->GetDeviceState( KYKBOARD_MAX , g_diKeyState);

	if(SUCCEEDED(hr))
	{
		for(int i = 0; i < KYKBOARD_MAX; i++ )
		{
			g_keyPhush[i] = (KeyOld[i] ^  g_diKeyState[i]) & g_diKeyState[i];
			g_keyRelese[i] = (KeyOld[i] ^ g_diKeyState[i]) & KeyOld[i];
		}

	}
	else
	{
						// ��������́H 
		g_pDinputDevice->Acquire();
	}

	// �f�[�^�`���ݒ�
	hr = g_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);	

}
//=============================================================================
//
// �֐���	: GetKey�֐�
//
// ����		: �Ȃ�
//
// �߂�l	: �Ȃ�
//
// �@�\		: �L�[�̍X�V�@
//
//=============================================================================
BOOL KeyState(int i)
 {
	 return (BOOL)(g_diKeyState[i] & 0x80);
 }



//�L�[�𗣂������̃t���O
BOOL KeyRelease(int i)
{
	return (BOOL)(g_keyRelese[i] & 0x80);
}

BOOL KeyPush(int i)
{
	return (BOOL)(g_keyPhush[i] & 0x80);
} 
