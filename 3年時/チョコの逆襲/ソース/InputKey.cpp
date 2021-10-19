//=============================================================================
//
// FAILE NAME [InputKey.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: キー入力
//
//
//=============================================================================
 
//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/InputKey.h"
#include <d3dx9.h>
#include <windows.h>

//=============================================================================
//グローバル変数
//=============================================================================
static LPDIRECTINPUT8 g_pDinput = NULL;					// キー入力 
static LPDIRECTINPUTDEVICE8 g_pDinputDevice = NULL;		// キーデバイス
static BYTE g_diKeyState[KYKBOARD_MAX] = {NULL};		// キー押しっぱなし
static BYTE g_keyPhush[KYKBOARD_MAX] = {NULL};			// キーを押した瞬間
static BYTE g_keyRelese[KYKBOARD_MAX]  = {NULL};		// 離した時


//=============================================================================
//
// 関数名	: InitInput関数
//
// 戻り値	: インターフェースが取得できたか
//			  オブジェクトが作成できたか
//
// 引数		: インスタンス
//			　Hウィンドウ
//
// 機能		: インターフェース取得
//			: オブジェクトの作成
// 
//=============================================================================

// インターフェースの取得
BOOL InitInput(HINSTANCE hInstance , HWND hWnd)
{
	HRESULT hr;

	// インターフェースの生成
	hr = DirectInput8Create( hInstance,				
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8,
			(void**)&g_pDinput, NULL);
	
	if(FAILED(hr))
	{
		// インターフェース取得失敗作業
		return FALSE;
	}

	// オブジェクトの作成
	hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
			&g_pDinputDevice, 
			NULL);

	// データフォーマットの設定
	hr = g_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);

	hr = g_pDinputDevice->SetCooperativeLevel( hWnd , 
											(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE) );

	// キーボードのアクセス権を取得
	hr = g_pDinputDevice->Acquire();
	if(FAILED(hr))
	{
		return hr;
	}

	if(g_pDinput == NULL)
	{
		// オブジェクト作成失敗作業
		return FALSE;
	}
	
	return TRUE;

}
//=============================================================================
//
// 関数名	: UninitInout関数
//
// 引数		: なし
//
// 戻り値	: なし
//
// 機能		: キーを解放
//
//=============================================================================
void UninitInput(void)
{
	// キーボードデバイスの解放
	if(g_pDinputDevice != NULL)
	{
		g_pDinputDevice->Unacquire();
		g_pDinputDevice->Release();
		g_pDinputDevice = NULL;
	}

	// オブジェクトの解放
	if(g_pDinput != NULL)
	{
		g_pDinput->Release();
		g_pDinput = NULL;
	}

}

//=============================================================================
//
// 関数名	: UpdateInput関数
//
// 引数		: なし
//
// 戻り値	: なし
//
// 機能		: キーの更新　
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
						// ↓何するの？ 
		g_pDinputDevice->Acquire();
	}

	// データ形式設定
	hr = g_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);	

}
//=============================================================================
//
// 関数名	: GetKey関数
//
// 引数		: なし
//
// 戻り値	: なし
//
// 機能		: キーの更新　
//
//=============================================================================
BOOL KeyState(int i)
 {
	 return (BOOL)(g_diKeyState[i] & 0x80);
 }



//キーを離した時のフラグ
BOOL KeyRelease(int i)
{
	return (BOOL)(g_keyRelese[i] & 0x80);
}

BOOL KeyPush(int i)
{
	return (BOOL)(g_keyPhush[i] & 0x80);
} 
