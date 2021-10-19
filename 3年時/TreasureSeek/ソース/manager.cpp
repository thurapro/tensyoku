//=============================================================================
// ツール作成の前手順　　　　　　フィールド作成ツール用
//  
// メイン処理 [maneger.cpp]
//
// 機能 : マネージャー処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"		// レンダラー
#include "data.h"			// データ
#include "scene.h"			// シーン
#include "inputkeyboard.h"	// 入力キーボード
#include "fade.h"			// フェード
#include "logo.h"			// ロゴ
#include "title.h"			// タイトル
#include "tutorial.h"		// チュートリアル
#include "game.h"			// ゲーム
#include "result.h"			// リザルト
#include "ranking.h"		// ランキング
#include "score.h"			// スコア
#include "debugproc.h"		// デバッグ
#include "manager.h"		// マネージャ
#include "scene2D.h"		// 2Dオブジェクト
#include "sceneX.h"			// Xオブジェクト

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数
//=============================================================================
HWND			CManager::m_hWnd;				// ウィンドウハンドル宣言
CRenderer		*CManager::m_pRenderer;			// レンダラーポインタ宣言
CInputKeyboard	*CManager::m_pKeyboard;			// キーボードポインタ宣言
CManager::MODE	CManager::m_Mode;				// モード宣言
CLogo			*CManager::m_pLogo;				// ロゴポインタ宣言
CTitle			*CManager::m_pTitle;			// タイトルポインタ宣言
CTutorial		*CManager::m_pTutorial;			// チュートリアルポインタ宣言
CGame			*CManager::m_pGame;				// ゲームポインタ宣言
CResult			*CManager::m_pResult;			// リザルトポインタ宣言
int				CManager::m_nRankScore;			// ランクスコア宣言
CRanking		*CManager::m_pRanking;			// ランキングポインタ宣言
CFade			*CManager::m_pFade;				// フェードポインタ宣言
CDebug			*CManager::m_pDebug;			// デバッグポインタ宣言

//=============================================================================
//	関数名	: CManager
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャーインスタンス生成
//=============================================================================
CManager::CManager(void)
{
	// インスタンス生成
	m_hWnd			= NULL;			// ウィンドウハンドル初期化
	m_pRenderer		= NULL;			// レンダラーポインタ初期化
	m_pKeyboard		= NULL;			// キーボードポインタ初期化
	m_Mode			= MODE_LOGO;	// モード初期化
	m_pLogo			= NULL;			// ロゴポインタ初期化
	m_pTitle		= NULL;			// タイトルポインタ初期化
	m_pTutorial		= NULL;			// チュートリアル初期化
	m_pGame			= NULL;			// ゲームポインタ初期化
	m_pResult		= NULL;			// リザルト初期化
	m_pRanking		= NULL;			// ランキング初期化
	m_nRankScore	= 0;			// ランクスコア初期化
	m_pFade			= NULL;			// フェード初期化
	m_pDebug		= NULL;			// デバッグ初期化
}

//=============================================================================
//	関数名	: CManager
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャーインスタンス破棄
//=============================================================================
CManager::~CManager(void)
{
	// インスタンス破棄
}

//=============================================================================
//	関数名	: Init
//	戻り値	: HRESULT
//	引数	: HINSTANCE , HWND , BOOL
//	機能	: マネージャー初期化
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr;

	m_hWnd = hWnd;		// ウィンドウハンドルを保存

	if( m_pRenderer == NULL )
	{
		// レンダラーが作成されていなければ
		m_pRenderer = NEW CRenderer;				// レンダラーインスタンス生成
		hr = m_pRenderer->Init(hWnd, bWindow);		// レンダラー初期化
		ERROR_CHACK(hr);							// レンダラーが作成に成功したか
	}
	if( m_pKeyboard == NULL )
	{
		// キーボードが作成されていなければ
		m_pKeyboard = NEW CInputKeyboard;			// キーボードインスタンス生成
		hr = m_pKeyboard->Init(hInstance, hWnd);	// キーボード初期化
		ERROR_CHACK(hr);							// キーボードが作成出来なければ
	}

	if( m_pFade == NULL )
	{
		// フェードがつくられていなければ
		m_pFade = NEW CFade;				// フェードインスタンス生成
		hr = CManager::GetFade()->Init(1);	// フェード初期化
		ERROR_CHACK(hr);					// エラーチェック
	}

	if( m_pDebug == NULL )
	{
		// デバッグが作成されていなければ
		m_pDebug = NEW CDebug;
		hr = m_pDebug->Init();
		ERROR_CHACK(hr);
	}

	SetMode(m_Mode);								// モードを設定

	return S_OK;									// マネージャ初期化成功
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャー破棄
//=============================================================================
void CManager::Uninit(void)
{
	// メモリの開放
	CScene::ReleaseAll();		// オブジェクトすべて破棄
	CLASS_DELETE(m_pKeyboard);	// キーボードインスタンス破棄
	CLASS_DELETE(m_pLogo);		// ロゴインスタンス破棄
	CLASS_DELETE(m_pTitle);		// タイトルインスタンス破棄
	CLASS_DELETE(m_pTutorial);	// チュートリアルインスタンス破棄
	CLASS_DELETE(m_pGame);		// ゲームインスタンス破棄
	CLASS_DELETE(m_pResult);	// リザルトインスタンス破棄
	CLASS_DELETE(m_pRanking);	// ランキングインスタンス破棄
	CLASS_DELETE(m_pFade);		// フェードインスタンス破棄
	CLASS_DELETE(m_pRenderer);	// レンダラーインスタンス破棄
	CLASS_DELETE(m_pDebug);		// デバッグインスタンス破棄
}

//=============================================================================
//	関数名	: Update
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャー更新
//=============================================================================
void CManager::Update(void)
{
	m_pKeyboard->Update();
	m_pDebug->Update();
	m_pFade->Update();
	switch(m_Mode)		// 現在のモードがどうなのか取得
	{
	case MODE_LOGO:				// ロゴの場合
		m_pLogo->Update();		// ロゴ更新
		break;
	case MODE_TITLE:			// タイトルの場合
		m_pTitle->Update();		// タイトル更新
		break;
	case MODE_TUTORIAL:			// チュートリアルの場合
		m_pTutorial->Update();	// チュートリアル更新
		break;
	case MODE_GAME:				// ゲームの場合
		m_pGame->Update();		// ゲーム更新
		break;
	case MODE_RESULT:			// リザルトの場合
		m_pResult->Update();	// リザルト更新
		break;
	case MODE_RANKING:			// ランキングの場合
		m_pRanking->Update();	// ランキング更新
		break;					
	default:					// なんでもない場合
		break;					// 処理なし
	}
}

//=============================================================================
//	関数名	: Draw
//	戻り値	: なし
//	引数	: デバイス
//	機能	: マネージャー描画
//=============================================================================
void CManager::Draw(void)
{
	///// 描画処理 /////
	m_pRenderer->Draw();			// レンダラー描画
}


//=============================================================================
//	関数名	: SetModde
//	戻り値	: なし
//	引数	: モード
//	機能	: モード遷移
//=============================================================================
void CManager::SetMode(MODE mode)
{
	HRESULT hr;
	m_Mode = mode;
	switch(mode)
	{
	case MODE_LOGO:									// ロゴの場合
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		CLASS_DELETE(m_pRanking);					// リザルトインスタンス破棄
		if( m_pLogo == NULL )
		{
			m_pLogo = NEW CLogo;					// ロゴインスタンス生成
			hr = m_pLogo->Init(m_hWnd);				// ロゴ初期化
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_TITLE:	
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		CLASS_DELETE(m_pGame);						// ゲームインスタンス破棄
		CLASS_DELETE(m_pLogo);						// ロゴインスタンス破棄
		if( m_pTitle == NULL )
		{
			m_pTitle = NEW CTitle;					// タイトルインスタンス生成
			hr = m_pTitle->Init(m_hWnd);			// タイトル初期化
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_TUTORIAL:								// チュートリアルの場合
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		CLASS_DELETE(m_pTitle);						// タイトルインスタンス破棄
		if( m_pTutorial == NULL )
		{
			m_pTutorial = NEW CTutorial;			// チュートリアルインスタンス生成
			hr = m_pTutorial->Init(m_hWnd);			// チュートリアル初期化
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;

	case MODE_GAME:									// ゲームの場合
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		CLASS_DELETE(m_pGame);						// ゲームインスタンス破棄
		CLASS_DELETE(m_pTutorial);					// チュートリアルインスタンス破棄
		if( m_pGame == NULL )
		{
			m_pGame = NEW CGame;					// ゲームインスタンス生成
			hr = m_pGame->Init(m_hWnd);				// ゲーム初期化
			if( FAILED(hr) )	
			{
				return;
			}
		}
		break;
	case MODE_RESULT:								// リザルトの場合
		m_nRankScore = m_pGame->GetScore()->GetScore();
		CLASS_DELETE(m_pGame);						// ゲームインスタンス破棄
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		if( m_pResult == NULL )
		{
			m_pResult = NEW CResult;				// リザルトインスタンス生成
			hr = m_pResult->Init(m_hWnd);			// リザルト初期化
			if( FAILED(hr) )
			{
				return;
			}
		}
		break;
	case MODE_RANKING:								// ランキングの場合
		m_pFade->SetFadeMode(CFade::FADEMODE_IN);	// フェードイン
		if( m_pRanking == NULL )		
		{
			m_pRanking = NEW CRanking;				// ランキングインスタンス生成
			hr = m_pRanking->Init(m_hWnd);			// ランキング初期化
			if( FAILED(hr) )
			{
				return ;
			}
		}
		break;
	default:
		break;
	}
}

///// end of file /////




