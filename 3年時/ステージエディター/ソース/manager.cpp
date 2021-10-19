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
#include "manager.h"
#include "scene.h"
#include "field.h"
#include "wall.h"
#include "mountain.h"
#include "sceneX.h"
#include "sky.h"
#include "data.h"
#include "stage.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CRenderer		*CManager::m_pRenderer;			// レンダラーポインタ宣言
CInputKeyboard	*CManager::m_pKeyboard;			// キーボードポインタ宣言
CDebug			*CManager::m_pDebug;			// デバッグポインタ宣言
CCamera			*CManager::m_pCamera;			// カメラポインタ宣言
CData			*CManager::m_pData;				// データポインタ宣言
CStage			*CManager::m_pStage;			// ステージポインタ宣言

//=============================================================================
//	関数名	: CManager
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャーインスタンス生成
//=============================================================================
CManager::CManager(void)
{
	// インスタンス生成
	m_pRenderer	= NULL;			// レンダラーポインタ初期化
	m_pKeyboard	= NULL;			// キーボードポインタ初期化
	m_pDebug	= NULL;			// デバッグポインタ初期化
	m_pCamera	= NULL;			// カメラポインタ初期化
	m_pLight	= NULL;			// ライトポインタ初期化
	m_pData		= NULL;			// データポインタ初期化
	m_pStage	= NULL;
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
	
	NEW_TYPE(m_pRenderer, CRenderer);			// レンダラーインスタンス生成
	hr = m_pRenderer->Init(hWnd, bWindow);		// レンダラー初期化
	ERROR_CHACK(hr);							// エラーチェック
	
	NEW_TYPE(m_pKeyboard, CInputKeyboard);		// キーボードインスタンス生成
	hr = m_pKeyboard->Init(hInstance, hWnd);	// キーボード初期化
	ERROR_CHACK(hr);							// エラーチェック

	NEW_TYPE(m_pDebug, CDebug);					// デバッグインスタンス生成
	hr = m_pDebug->Init();						// デバッグ初期化
	ERROR_CHACK(hr);							// エラーチェック

	NEW_TYPE(m_pCamera, CCamera);				// カメラインスタンス生成
	m_pCamera->Init();							// カメラ初期化

	NEW_TYPE(m_pLight, CLight);					// ライトインスタンス生成
	hr = m_pLight->Init();						// ライト初期化
	ERROR_CHACK(hr);							// エラーチェック

	NEW_TYPE(m_pData, CData);					// データ生成
	hr = m_pData->Init(hWnd, "DATA/TEXT/GAME.txt");
	ERROR_CHACK(hr);

	NEW_TYPE(m_pStage, CStage);
	hr = m_pStage->Init();
	ERROR_CHACK(hr);

	return S_OK;								// マネージャ初期化成功
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャー破棄
//=============================================================================
void CManager::Uninit(void)
{
	CLASS_DELETE(m_pRenderer);		// レンダラーインスタンス破棄
	CLASS_DELETE(m_pKeyboard);		// キーボードインスタンス破棄
	CLASS_DELETE(m_pDebug);			// デバッグインスタンス破棄
	CLASS_DELETE(m_pCamera);		// カメラインスタンス破棄
	CLASS_DELETE(m_pLight);			// ライトインスタンス破棄
	CLASS_DELETE(m_pData);			// データインスタンス破棄
	CLASS_DELETE(m_pStage);			// ステージインスタンス破棄
	CScene::ReleaseAll();			// シーン破棄
}

//=============================================================================
//	関数名	: Update
//	戻り値	: なし
//	引数	: なし
//	機能	: マネージャー更新
//=============================================================================
void CManager::Update(void)
{
	m_pKeyboard->Update();			// キーボード更新
	m_pDebug->Update();				// デバッグ更新
	m_pCamera->Update();			// カメラ更新	
	m_pStage->Update();

	if( m_pKeyboard->KeyPush(DIK_F12) )
	{
		m_pStage->Save();
		m_pDebug->Print("セーブしたよ");
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

///// end of file /////




