//-----------------------------------------------------------------------------
//
// object処理		[object.h]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2重インクルード防止
//-----------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "CScreen.h"
//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_OBJECT (100)						// オブジェクトの最大数

//-----------------------------------------------------------------------------
// オブジェクラス定義
//-----------------------------------------------------------------------------
class CObject
{
public:
	typedef enum
	{
		OBJTYPE_PLAYER = 0,												// プレイヤーが入っている
		OBJTYPE_ENEMY,													// 敵が入っている
		OBJTYPE_BULLET,													// 弾が入っている
		OBJTYPE_EXPLOSION,												// 爆発が入っている
		OBJTYPE_MAX														// 最高値
	}OBJTYPE;
	CObject();															// コンストラクタ
	virtual ~CObject() = 0;												// デストラクタ
	virtual void Init(void){};											// 初期化
	virtual void Uninit(void)=0;										// 終了処理
	virtual void Update(void)=0;										// 更新処理
	virtual void Draw(void)=0;											// 描画処理
	virtual void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld)=0;			// 爆発の位置取得
	// ポジションを取得
	void Release(void);													// オブジェクト破棄
	static void UpdateAll(void);										// すべての更新
	static void DrawAll(void);											// すべての描画
	static void ReleaseAll(void);										// すべての破棄
	void SetObjType(OBJTYPE type){m_objType = type;}					// オブジェクトタイプをセット
	OBJTYPE GetObjTyep(void){ return m_objType;}						// オブジェクトタイプを取得
	static CObject *GetObj(void){return (CObject *)&m_apObject[0];}
private:
	static CObject *m_apObject[MAX_OBJECT];				// オブジェクトワーク
	static int m_nNumObject;							// オブジェクト総数
	OBJTYPE m_objType;									// オブジェクトのタイプ
	int m_nID;											// オブジェクトID
};

#endif //_OBJECT_H_