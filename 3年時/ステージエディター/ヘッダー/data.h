//=============================================================================
// データ一括管理 [ data.h ]
//
// 製作者	: 松尾 雄太
//
// 機能		: データ一括管理
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _DATA_H_
#define _DATA_H_

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "model.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_TEXT	("data/text/title.txt")
#define GAME_TEXT	("data/text/game.txt")
#define RESULT_TEXT	("data/text/result.txt")

//=============================================================================
// クラス定義
//=============================================================================
class CData
{
public:		// 操作
	CData(void);							// インスタンス生成
	~CData(void);							// インスタンス破棄
	HRESULT Init(HWND hWnd, const char *FileName);// データの初期化処理
	void Uninit(void);						// データの終了処理
	void Save(void);						// まとめているデータを保存

	CTexture	*GetTexture(void){return m_pTexture;}		// テクスチャ取得
	CModel		*GetModel(void){return m_pModel;}			// モデル取得
	CSound		*GetSound(void){return m_pSound;}			// サウンド取得

private:	// 要素
	HRESULT LoardData(HWND hWnd, const char *FileName);		// まとめているデータを読み込む

	CTexture	*m_pTexture;		// テクスチャポインタ
	CModel		*m_pModel;			// モデルポインタ
	CSound		*m_pSound;			// サウンドポインタ
};

#endif	// _DATA_H_

// end of file //