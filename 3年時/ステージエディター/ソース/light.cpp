//=============================================================================
// 照明(ライト)処理	[light.cpp]
// 
// 製作者	: 松尾 雄太
//
// 機能		: ライト初期化
//			: 更新
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "light.h"

//=============================================================================
// 関数名	: CLight
// 戻り値	: なし
// 引数		: なし
// 機能		: ライトのインスタンス生成
//=============================================================================
CLight::CLight(void)
{
	// インスタンス生成
}

//=============================================================================
// 関数名	: ~CLight
// 戻り値	: なし
// 引数		: なし
// 機能		: ライトのインスタンス破棄
//=============================================================================
CLight::~CLight(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: なし
// 機能		: ライトの初期化
//			: ライトの明るさ初期化
//			: ライトの向き初期化
//=============================================================================
HRESULT CLight::Init(void)
{
	///// ライトの初期化処理開始 /////

	// 変数宣言 
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// デバイス取得

	/////// 1つ目のライトの明るさ初期化 /////
	ZeroMemory(&m_aLight[FIRST_LIGHT], sizeof(D3DLIGHT9) );							// ライトのメモリを全初期化
	m_aLight[FIRST_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ライトの種類
	m_aLight[FIRST_LIGHT].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);				// 拡散色設定

	///// ライトの向き初期化 /////
	m_vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);										// ライトの方向 ※重要※
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[FIRST_LIGHT].Direction, &m_vecDir);	// ライトの方向修正
	hr = pDevice->SetLight(FIRST_LIGHT, &m_aLight[FIRST_LIGHT]);					// ライトの設定
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(FIRST_LIGHT, TRUE);									// ライトを有効にする
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// 2つ目のライトの明るさ初期化 /////
	ZeroMemory(&m_aLight[SECOND_LIGHT], sizeof(D3DLIGHT9) );						// ライトのメモリを全初期化
	m_aLight[SECOND_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ライトの種類
	m_aLight[SECOND_LIGHT].Diffuse = D3DXCOLOR(0.55f, 0.55f, 0.55f, 0.35f);				// 拡散色設定

	///// ライトの向き初期化 /////
	m_vecDir = D3DXVECTOR3(1.0f, 0.0f, 1.0f);										// ライトの方向 ※重要※
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[SECOND_LIGHT].Direction, &m_vecDir);	// ライトの方向修正
	hr = pDevice->SetLight(SECOND_LIGHT, &m_aLight[SECOND_LIGHT]);					// ライトの設定
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(SECOND_LIGHT, TRUE);									// ライトを有効にする
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// 3つ目のライトの明るさ初期化 /////
	ZeroMemory(&m_aLight[THIRD_LIGHT], sizeof(D3DLIGHT9) );							// ライトのメモリを全初期化
	m_aLight[THIRD_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ライトの種類
	m_aLight[THIRD_LIGHT].Diffuse = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);			// 拡散色設定

	///// ライトの向き初期化 /////
	m_vecDir = D3DXVECTOR3(-4.0f, 0.3f, 1.0f);										// ライトの方向 ※重要※
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[THIRD_LIGHT].Direction, &m_vecDir);	// ライトの方向修正
	hr = pDevice->SetLight(THIRD_LIGHT, &m_aLight[THIRD_LIGHT]);					// ライトの設定
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(THIRD_LIGHT, TRUE);									// ライトを有効にする
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// レンダーステート設定 /////
	hr = pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);								// ライトを設定する
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: ライトの破棄
//=============================================================================
void CLight::Uninit(void)
{
	// 終了処理
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: ライトの更新
//=============================================================================
void CLight::Update(void)
{
}

///// end of file /////