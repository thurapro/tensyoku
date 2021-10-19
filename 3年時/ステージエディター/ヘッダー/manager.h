//=============================================================================
// ツール作成の前手順　　　　　　　　フィールド作成ツール用
//  
// メイン処理 [maneger.h]
//
// 機能 : マネージャー処理
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"

//=============================================================================
// マクロ定義
//=============================================================================
class CData;
class CStage;

//=============================================================================
// クラス宣言
//=============================================================================
class CManager
{
public:		// 操作
	CManager(void);													// インスタンス生成
	~CManager(void);												// インスタンス破棄
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// マネージャー初期化
	void Uninit(void);												// マネージャー終了
	void Update(void);												// マネージャー更新
	void Draw(void);												// マネージャー描画
	static CRenderer		*GetRenderer(void){return m_pRenderer;}	// レンダラー取得
	static CInputKeyboard	*GetKeyboard(void){return m_pKeyboard;}	// キーボード取得
	static CDebug			*GetDebug(void){return m_pDebug;}		// デバッグ取得
	static CCamera			*GetCamera(void){return m_pCamera;}		// カメラ取得
	static CData			*GetData(void){return m_pData;}
	static CStage			*GetStage(void){return m_pStage;}		

private:	// 要素
	static CRenderer		*m_pRenderer;							// レンダラーポインタ
	static CInputKeyboard	*m_pKeyboard;							// キーボードポインタ
	static CDebug			*m_pDebug;								// デバッグポインタ
	static CCamera			*m_pCamera;								// カメラポインタ
	CLight					*m_pLight;								// ライトポインタ
	static CData			*m_pData;								// データポインタ
	static CStage			*m_pStage;
};

#endif // _MANAGER_H_

// end of file