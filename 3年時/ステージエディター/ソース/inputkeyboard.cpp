//=============================================================================
// キーボード入力処理	[ inputkeyboard.cpp ]
//
// 製作者	: 松尾 雄太
//
// 機能		: キーボードを動かす
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "inputkeyboard.h"

//=============================================================================
// 関数名	: CInputKeyboard
// 引数		: なし
// 戻り値	: なし
// 機能		: キーボードインスタンス生成　
//=============================================================================
CInputKeyboard::CInputKeyboard(void)
{
}

//=============================================================================
// 関数名	: ~CInputKeyboard
// 戻り値	: なし
// 引数		: なし
// 機能		: キーボードインスタンス破棄
//=============================================================================
CInputKeyboard::~CInputKeyboard(void)
{
}

//=============================================================================
// 関数名	: Init関数
// 引数		: HINSTANCE インスタンス HWND ハンドル
// 戻り値	: HRESULT　
// 機能		: キーボード初期化　
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

	// オブジェクトの作成
	hr = m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDinputDevice, NULL);
	if(FAILED(hr))
	{
		// オブジェクト生成失敗
		return hr;								// 入力初期化失敗
	}

	// データフォーマットの設定
	hr = m_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		// フォーマット設定失敗
		return hr;								// 入力初期化設定
	}
	hr = m_pDinputDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE|DISCL_FOREGROUND));
	if(FAILED(hr))
	{
		// インターフェース取得失敗作業
		return hr;								// 入力初期化失敗
	}

	if(m_pDinput == NULL)
	{
		// オブジェクト作成失敗作業
		return hr;								// 入力初期化失敗
	}
	return hr;
}

//=============================================================================
// 関数名	: Uninit関数
// 引数		: なし
// 戻り値	: なし
// 機能		: キーボードの終了
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();			// 入力終了処理
}

//=============================================================================
// 関数名	: Update関数
// 引数		: なし
// 戻り値	: なし
// 機能		: キーボードの更新
//=============================================================================
HRESULT CInputKeyboard::Update(void)
{
	HRESULT hr;	
	BYTE KeyOld[MAX_KEY] ={NULL};
	for(int i = 0; i < MAX_KEY; i++)
	{
		KeyOld[i] = m_diKeyState[i];
	}

	hr = m_pDinputDevice->GetDeviceState( MAX_KEY , m_diKeyState);					// デバイス
	if(SUCCEEDED(hr))
	{
		for(int i = 0; i < MAX_KEY; i++ )
		{
			// キーボードのボタン分処理を回す
			m_keyPush[i] = (KeyOld[i] ^  m_diKeyState[i]) & m_diKeyState[i];		// キーを押した瞬間処理
			m_keyRelese[i] = (KeyOld[i] ^ m_diKeyState[i]) & KeyOld[i];				// キーを離した瞬間処理
		}
		//CManager::GetDebug()->Print(80, 300, "%d\n",m_diKeyState);
	}
	else
	{ 
		// アクセス権再取得
		m_pDinputDevice->Acquire();
	}
	// データ形式設定
	hr = m_pDinputDevice->SetDataFormat(&c_dfDIKeyboard);
	if( FAILED(hr) )
	{
		return E_FAIL;
	}
	return S_OK;
}