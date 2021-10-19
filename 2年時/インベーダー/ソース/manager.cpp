//=============================================================================
//
// マネージャー処理[manager.cpp]	松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "input.h"

//=============================================================================
// 静的メンバー
//=============================================================================
CTitle *CManager::m_pTitle = 0;
CGame *CManager::m_pGame = 0;
CResult *CManager::m_pResult = 0;
CInput *CManager::m_pInput = 0;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//-----------------------------------------------------------------------------
// マネージャーコンストラクタ
// 戻り値 なし
// 引数 なし
// 機能 インスタンス生成
//-----------------------------------------------------------------------------
CManager::CManager()
{
	// 生成
}

//-----------------------------------------------------------------------------
// マネージャーデストラクタ
// 戻り値 なし
// 引数 なし
// 機能 インスタンス破棄
//-----------------------------------------------------------------------------
CManager::~CManager()
{
	// 破棄
}

//-----------------------------------------------------------------------------
// マネージャー初期化
// 戻り値 なし
// 引数 なし
// 機能 初期化処理
//-----------------------------------------------------------------------------
void CManager::Init(void)
{
	m_pTitle = NULL;					// タイトルポインタ初期化
	m_pGame = NULL;						// ゲームポインタ初期化
	m_pResult = NULL;					// リザルトポインタ初期化
	m_pInput = NULL;					// 入力ポインタ初期化
	m_mode = MODE_TITLE;				// モード初期化
	if(m_pInput == NULL)
	{
		// 入力ポインタがなかったら
		m_pInput = new CInput;			// 入力ポインタ生成
		m_pInput->Init();				// 入力ポインタ初期化
	}
	SetMode(MODE_TITLE);				// モードセット
}

//-----------------------------------------------------------------------------
// マネージャー処理
// 戻り値 なし
// 引数 なし
// 機能 終了処理
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	if(m_pInput != NULL)
	{
		// 入力ポインタがあれば
		delete m_pInput;				// 入力ポインタを破棄
		m_pInput = NULL;				// 入力ポインタの中身を初期化
	}
	
	switch(m_mode)
	{
		// 各モードの破棄
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// タイトルポインタの中身があれば
			delete m_pTitle;			// タイトルポインタ破棄
			m_pTitle = NULL;			// タイトルポインタ初期化
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// ゲームポインタの中身があれば
			delete m_pGame;				// ゲームポインタの破棄
			m_pGame= NULL;				// ゲームポインタの初期化
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// リザルトポインタの中身があれば
			delete m_pResult;			// リザルトポインタの破棄
			m_pResult = NULL;			// リザルトポインタの初期化
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// マネージャーの更新
// 戻り値 なし
// 引数 なし
// 機能 マネージャー更新
//-----------------------------------------------------------------------------
void CManager::Update(void)
{
	m_pInput->Update();					// 入力更新
	switch(m_mode)
	{
		// 各モード更新
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// もしタイトルポインタがNULLでなければ
			m_pTitle->Update();		// タイトル更新
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// もしゲームポインタがNULLでなければ
			m_pGame->Update();		// ゲーム更新
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// もしリザルトポインタがNULLでなければ
			m_pResult->Update();	// リザルト更新
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// マネージャーの描画
// 戻り値 なし
// 引数 なし
// 機能 マネージャー描画
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	switch(m_mode)
	{
		// 各モード描画
	case MODE_TITLE:
		if(m_pTitle != NULL)
		{
			// もしタイトルポインタがNULLでなければ
			m_pTitle->Draw();		// タイトル描画
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			// もしゲームポインタがNULLでなければ
			m_pGame->Draw();		// ゲーム描画
		}
		break;
	case MODE_RESULT:
		if(m_pResult != NULL)
		{
			// もしリザルトポインタがNULLでなければ
			m_pResult->Draw();		// リザルト描画
		}
		break;
	case MODE_MAX:
		break;
	}
}

//-----------------------------------------------------------------------------
// モードセット
// 戻り値 なし
// 引数 モード
// 機能 モードセット
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	m_mode = mode;						// 現在のモードを保存
	switch(m_mode)
	{
	case MODE_TITLE:
		if(m_pResult != NULL)
		{
			// リザルトがあった場合
			m_pResult->Uninit();		// リザルト終了
			delete m_pResult;			// リザルト破棄
			m_pResult = NULL;			// リザルトポインタ初期化
		}
		m_pTitle = new CTitle;			// タイトル生成
		m_pTitle->Init();				// タイトル初期化
		break;
	case MODE_GAME:
		if(m_pTitle != NULL)
		{
			// タイトルがあった場合
			m_pTitle->Uninit();			// タイトル終了
			delete m_pTitle;			// タイトル破棄
			m_pTitle = NULL;			// タイトルポインタ初期化
		}
		m_pGame = new CGame;			// ゲーム生成
		m_pGame->Init();				// ゲーム初期化
		break;
	case MODE_RESULT:
		if(m_pGame != NULL)
		{
			// ゲームが残っていた場合
			m_pGame->Uninit();			// ゲーム終了
			delete m_pGame;				// ゲーム破棄
			m_pGame = NULL;				// ゲームポインタ初期化
		}
		m_pResult = new CResult;		// リザルト生成
		m_pResult->Init();				// リザルト初期化
		break;
	default:
		break;
	}
}
