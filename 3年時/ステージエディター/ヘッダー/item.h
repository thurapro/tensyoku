//=============================================================================
// アイテム処理[item.h]
//
// 製作者 : 松尾 雄太
//
// 機能 :  アイテム
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// インクルード
//=============================================================================
#include "sceneX.h"

class CShadow;

//=============================================================================
// クラス定義
//=============================================================================
class CItem : public CSceneX
{
public:		// 操作
	CItem(int nPriority = 0, OBJTYPE objType = OBJTYPE_ITEM);			// アイテムインスタンス生成
	~CItem(void);			// アイテムインスタンス破棄
	static CItem *Create(float fPosX, float fPosY, float fPosZ, 
						unsigned int nModeNum, unsigned int nTexNum);		// アイテム生成
	HRESULT Init(void);		// アイテム初期化処理
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
						unsigned int nModeNum, unsigned int nTexNum);		// アイテム初期化処理
	void Uninit(void);		// アイテム終了処理
	void Update(void);		// アイテム更新処理
	void Draw(void);		// アイテム描画処理

private:
	CShadow		*m_pShadow;		// 影ポインタ
};

#endif // _ITEM_H_

// end of file //
