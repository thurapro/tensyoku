//=============================================================================
//
// FAILE NAME [Direct3DCreater.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: デバイス生成
//			　デバイス破棄
//			　デバイスを渡す
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "../hedder/common.h"
#include "../hedder/Direct3DCreater.h"

//=============================================================================
// グローバル変数
//=============================================================================
static LPDIRECT3DDEVICE9	g_pD3DDevice;				// Direct3Dデバイス
static LPDIRECT3D9			g_pD3D = NULL;				// Direct3Dオブジェクト

//============================================================================
//
// 関数名	: DeviceInit関数
//
// 戻り値	: BOOL
//
// 引数		: HWND
//
// 機能		: デバイスの生成	
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

	// 現在のディスプレイモード習得
	D3DDISPLAYMODE d3ddm;	
	hr = g_pD3D->GetAdapterDisplayMode( 
	D3DADAPTER_DEFAULT,&d3ddm);
	if( FAILED( hr ) )
	{
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
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

	// デバイス生成
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
// 関数名	: Direct3ddeviceUninit関数
//
// 戻り値	: なし
//
// 引数		: なし	
//
// 機能		: デバイスの破棄		
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
// 関数名	: Direct3ddeviceGetDevice関数
//
// 戻り値	: LPDIRECT3DDEVICE9
//
// 引数		: なし
//
// 機能		: 生成されたデバイスを渡す
//			
//
//============================================================================
LPDIRECT3DDEVICE9 Direct3ddeviceGetDevice(void)
{
	return g_pD3DDevice;
}