//=============================================================================
//
// FAILE NAME [System.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �V�X�e���̏�����
//
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/InputKey.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/System.h"
#include "../hedder/Direct3DCreater.h"
#include "../hedder/Font.h"
#include "../hedder/FPS.h"
#include "../hedder/Sound.h"

//=============================================================================
//
// �֐���	: SystemInit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �V�X�e���̏�����
//
//=============================================================================
void SystemInit( HINSTANCE hInstance , HWND hWnd )
{
	LPDIRECTSOUNDBUFFER lpSound = NULL;
	//**************************
	// DirectX�̏�����
	//**************************
	 Direct3ddeviceInit(hWnd);	

	 // �������ꂽ�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// �����_�����O�X�e�[�g�̏������ݒ�
	pD3DDevice->SetRenderState(
		D3DRS_CULLMODE ,
		D3DCULL_NONE);
	pD3DDevice->SetRenderState(
		D3DRS_ZENABLE,TRUE);
	pD3DDevice->SetRenderState(
		D3DRS_ALPHABLENDENABLE , TRUE);
	pD3DDevice->SetRenderState(
		D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(
		D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̏������ݒ�
	pD3DDevice->SetSamplerState( 
		0 , D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP);
	pD3DDevice->SetSamplerState(
		0 , D3DSAMP_ADDRESSV , D3DTADDRESS_WRAP);
	pD3DDevice->SetSamplerState(
		0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(
		0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR);

	PrimitiveInit();
	InitInput( hInstance , hWnd );
	FontInit( 30 , 20 , 0 , "Terminal");
	FPSInit();
}

//=============================================================================
//
// �֐���	: SystemUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �V�X�e���̉��
//
//=============================================================================
void SystemUninit( void )
{
	// �t�H���g���
	FontUninit();
	
	// �L�[���͉��
	UninitInput();

	// ���y�̉��
	UninitSound();

	// �v���~�e�B�u���
	PrimitiveUninit();

	// �f�o�C�X�̉��
	Direct3ddeviceUninit();
}