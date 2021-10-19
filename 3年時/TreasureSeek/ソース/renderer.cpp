//=============================================================================
// ツール作成の前手順　　　　　　　　フィールド作成ツール用
//  
// 描画処理 [renderer.cpp]
//
// 機能 : レンダリング (DirectX)
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "logo.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "debugproc.h"
#include "fade.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BUFFER_DOUBLE_MODE (1)		// バッファーカウント

//=============================================================================
// 関数名	: CRenderer
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス生成 (基本は初期化)
//=============================================================================
CRenderer::CRenderer(void)
{
	m_pD3D		= NULL;		// IDirect9インターフェース初期化
	m_pDevice	= NULL;		// Directデバイスインターフェース初期化
}

//=============================================================================
// 関数名	: ~CRenderer
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄 ( 終了処理 )
//=============================================================================
CRenderer::~CRenderer(void)
{
	Uninit();	// 終了処理
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT	正常終了したか
// 引数値	: HWnd		ウィンドウハンドル
// 機能		: なし
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindowMode)
{
	HRESULT hr;	// エラーチェック処理

	// IDirect9インターフェース作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	// DirectXバージョを作成
	if( m_pD3D == NULL )
	{
		//  IDirect9インターフェース作成失敗
		return E_FAIL;	// エラーコード
	}

	// ディスプレイモード設定
	D3DDISPLAYMODE	d3ddm;	// ディスプレイモード構造体変数
	hr = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	ERROR_CHACK(hr);		// エラーチェック

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;								// プレゼンテーション構造体変数
	ZeroMemory(&d3dpp , sizeof(d3dpp) );						// 構造体の中身を０初期化
	d3dpp.Windowed					= bWindowMode;				// ウィンドウモード設定
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// スワップエフェクト設定
	d3dpp.BackBufferCount			= BUFFER_DOUBLE_MODE;		// バッファ数 現在(ダブルバッファ)
	d3dpp.EnableAutoDepthStencil	= TRUE;						// 深度/ステンシルバッファ設定 (有効)						
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// 深度/ステンシルバッファのフォーマット
	if(d3dpp.Windowed == TRUE)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファフォーマット設定
		d3dpp.FullScreen_RefreshRateInHz = 0;						// ウィンドウモード設定 (ウィンドウモード) 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// リフレッシュレート (直ちに更新)
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;						// バックバッファーフォーマット設定
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ウィンドウモード設定 (フルスクリーンモード)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// リフレッシュレート (少し待って更新)
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

	D3DDEVTYPE	DevType;				// デバイスのタイプ
	DWORD		BehaviorFlags;			// フラグ
	BOOL		bCreateDevice;			// デバイスができたかどうか
	int			i;						// カウンター
	bCreateDevice = FALSE;				// デバイスはできてない

	for( i = 0; i < _countof(DevTypes); i++ )
	{
		DevType	= DevTypes[i].DevType;
		BehaviorFlags = DevTypes[i].BehaviorFlags;
		hr = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT ,
		DevType ,
		hWnd ,
		BehaviorFlags ,
		&d3dpp,
		&m_pDevice);
		if( SUCCEEDED(hr) )
		{
			// デバイスの生成成功
			bCreateDevice = TRUE;		// デバイスができた
			break;
		}
	}
	if( bCreateDevice == FALSE )
	{
		// デバイスが作れなければ
		return E_FAIL;					// エラーコード
	}
	return S_OK;						// 成功コード

}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: メンバ変数破棄
//=============================================================================
void CRenderer::Uninit(void)
{
	SALF_RELEASE(m_pD3D);		// メモリの開放
	SALF_RELEASE(m_pDevice);	// メモリの開放
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数値	: なし
// 機能		: 更新だけど特に機能なし
//=============================================================================
void CRenderer::Update(void)
{
	// ウィンドウを変える場合に更新

}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: 描画
//=============================================================================
void CRenderer::Draw(void)
{
	HRESULT hr;
	CLogo		*pLogo		= CManager::GetLogo();		// ロゴ取得
	CTitle		*pTitle		= CManager::GetTitle();		// タイトル取得
	CTutorial	*pTutorial	= CManager::GetTutorial();	// チュートリアル取得
	CGame		*pGame		= CManager::GetGame();		// ゲーム取得
	CResult		*pResult	= CManager::GetResult();	// リザルト取得
	CRanking	*pRanking	= CManager::GetRanking();	// ランキング取得

	// バックバッファのクリア
	m_pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	// 描画処理
	hr = m_pDevice->BeginScene();			// 描画開始
	if( SUCCEEDED(hr) )
	{
		switch( CManager::GetMode() )		// 現在のモードがどうなのか取得
		{
		case CManager::MODE_LOGO:					// ロゴの場合
			pLogo->Draw();							// ロゴ描画
			break;

		case CManager::MODE_TITLE:					// タイトルの場合
			pTitle->Draw();							// タイトル描画
			break;
		
		case CManager::MODE_TUTORIAL:				// チュートリアルの場合
			pTutorial->Draw();						// チュートリアル描画
			break;									

		case CManager::MODE_GAME:					// ゲームの場合
			pGame->Draw();							// ゲーム描画
			break;

		case CManager::MODE_RESULT:					// リザルトの場合
			pResult->Draw();						// リザルト描画
			break;

		case CManager::MODE_RANKING:				// ランキングの場合
			pRanking->Draw();						// ランキング描画
			break;

		default:									// なんでもない場合
			break;									// 処理なし
		}
		CManager::GetDebug()->Draw();				// デバッグを描画

		if( CManager::GetFade()->GetFadeMode() 
			!= CFade::FADEMODE_NONE)
		{
			CManager::GetFade()->Draw();
		}

		m_pDevice->EndScene();				// 描画終了
	}

	// バックバッファとフロントバッファ入れ替え
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

// end of file
