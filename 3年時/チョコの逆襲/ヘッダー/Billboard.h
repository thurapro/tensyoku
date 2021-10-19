//=============================================================================
//
// フィールド処理 [Billboard.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Camera.h"
#include "InputKey.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT BillboardInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nBillboardScl_X , int nBillboardScl_Y);		// 影の初期化
void BillboardUninit(void);	// 影破棄
void BillboardUpdate(void);	// 影の更新
void BillboardDraw(LPDIRECT3DDEVICE9 pD3DDevice);		// 影更新
D3DXVECTOR3 BillboardPosGet(void);


#endif	// _EFFECT_H_
