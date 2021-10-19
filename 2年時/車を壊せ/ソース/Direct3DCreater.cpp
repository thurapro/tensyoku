//=============================================================================
//
// FAILE NAME [Direct3DCreater.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �f�o�C�X����
//			�@�f�o�C�X�j��
//			�@�f�o�C�X��n��
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "../hedder/common.h"
#include "../hedder/Direct3DCreater.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static LPDIRECT3DDEVICE9	g_pD3DDevice;				// Direct3D�f�o�C�X
static LPDIRECT3D9			g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g

//============================================================================
//
// �֐���	: DeviceInit�֐�
//
// �߂�l	: BOOL
//
// ����		: HWND
//
// �@�\		: �f�o�C�X�̐���	
//
//============================================================================
bool Direct3ddeviceInit(HWND hWnd)
{

	HRESULT hr;
	
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(NULL == g_pD3D)
	{
		return false;
	}

	// ���݂̃f�B�X�v���C���[�h�K��
	D3DDISPLAYMODE d3ddm;	
	hr = g_pD3D->GetAdapterDisplayMode( 
	D3DADAPTER_DEFAULT,&d3ddm);
	if( FAILED( hr ) )
	{
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp , sizeof(d3dpp) );

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(TRUE == d3dpp.Windowed)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// �f�o�C�X����
	struct
	{
		D3DDEVTYPE	DevType;
		DWORD		BehaviorFlags;
	} 
	DevTypes[] = {
		{ D3DDEVTYPE_HAL , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_HAL , D3DCREATE_SOFTWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_SOFTWARE_VERTEXPROCESSING }
	};

	D3DDEVTYPE	DevType;
	DWORD		BehaviorFlags;
	BOOL		bCreateDevice;
	int			i;
	bCreateDevice = FALSE;
	for( i = 0; i < _countof(DevTypes); i++)
	{
		DevType	= DevTypes[i].DevType;
		BehaviorFlags = DevTypes[i].BehaviorFlags;


		hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT ,
		DevType ,
		hWnd ,
		BehaviorFlags ,
		&d3dpp,
		&g_pD3DDevice);

		if(SUCCEEDED( hr ) )
		{
			bCreateDevice = TRUE;
			break;
		}
	}
	if( FALSE == bCreateDevice )
	{
		return false;
	}

	return true;
}

//============================================================================
//
// �֐���	: Direct3ddeviceUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�	
//
// �@�\		: �f�o�C�X�̔j��		
//
//============================================================================
void Direct3ddeviceUninit(void)
{
	if(g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//============================================================================
//
// �֐���	: Direct3ddeviceGetDevice�֐�
//
// �߂�l	: LPDIRECT3DDEVICE9
//
// ����		: �Ȃ�
//
// �@�\		: �������ꂽ�f�o�C�X��n��
//			
//
//============================================================================
LPDIRECT3DDEVICE9 Direct3ddeviceGetDevice(void)
{
	return g_pD3DDevice;
}