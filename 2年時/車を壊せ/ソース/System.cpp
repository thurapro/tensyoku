//=============================================================================
//
// FAILE NAME [System.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: システムの初期化
//
//
//=============================================================================

//=============================================================================
// インクルード
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
// 関数名	: SystemInit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: システムの初期化
//
//=============================================================================
void SystemInit( HINSTANCE hInstance , HWND hWnd )
{
	LPDIRECTSOUNDBUFFER lpSound = NULL;
	//**************************
	// DirectXの初期化
	//**************************
	 Direct3ddeviceInit(hWnd);	

	 // 生成されたデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// レンダリングステートの初期化設定
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

	// サンプラーステートの初期化設定
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
// 関数名	: SystemUninit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: システムの解放
//
//=============================================================================
void SystemUninit( void )
{
	// フォント解放
	FontUninit();
	
	// キー入力解放
	UninitInput();

	// 音楽の解放
	UninitSound();

	// プリミティブ解放
	PrimitiveUninit();

	// デバイスの解放
	Direct3ddeviceUninit();
}