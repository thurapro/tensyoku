//=============================================================================
// 入力処理 [Input.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: キーボード入力を可能とする
//=============================================================================
 
//=============================================================================
// ライブラリ読み込み
//=============================================================================
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

//=============================================================================
// インクルード
//=============================================================================
#include <dinput.h>
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECTINPUT8  CInput::m_pDinput;		// DirectInput8

//=============================================================================
// 関数名	: CInput
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス生成
//=============================================================================
CInput::CInput(void)
{
	m_pDinput = NULL;	// DirectInput8初期化
}

//=============================================================================
// 関数名	: ~CInput
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス破棄
//=============================================================================
CInput::~CInput(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: InitInput関数
// 戻り値	: インターフェースが取得できたか
//			  オブジェクトが作成できたか
// 引数		: インスタンス
//			　Hウィンドウ
// 機能		: インターフェース取得
//			: オブジェクトの作成
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;
	if(m_pDinput == NULL)
	{
		// インターフェースの生成
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDinput, NULL);
		ERROR_CHACK(hr);
	}
	return S_OK;
}

//=============================================================================
// 関数名	: Uninit関数
// 引数		: なし
// 戻り値	: なし
// 機能		: キーを解放
//=============================================================================
void CInput::Uninit(void)
{
	SALF_RELEASE(m_pDinputDevice);	// 入力デバイスの解放
	SALF_RELEASE(m_pDinput);		// Direct3Dインスタンス破棄 
}

///// end of file /////
