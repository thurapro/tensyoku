//=============================================================================
// 草処理 [grass.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: 草作成
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _GRASS_H_
#define _GRASS_H_

//=============================================================================
// インクルード
//=============================================================================
#include "sceneBillboard.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CGrass : public CBillboard 
{
public:		// 操作
	CGrass(int nPriority = 4, OBJTYPE objType = OBJTYPE_BILLBOARD);		// 草インスタンス生成
	~CGrass(void);														// 草インスタンス破棄
	static CGrass *Create(float fWidth, float fHeight, 
							USHORT nTexNum);							// 草作成
	static CGrass *CreateLoad(BILLBOARD dataGrass);						// 草作成&読み込み
	
	HRESULT Init(void){return S_OK;	}									// 草初期化
	HRESULT Init(float fWidth, float fHeight, 
					USHORT nTexNum);									// 草初期化
	void Uninit(void);													// 草終了
	void Update(void);													// 草更新
	void Draw(void);													// 草描画

private:	// 要素
	BILLBOARD	m_DataGrass;											// 草のデータ
};

#endif	// _GRASS_H_