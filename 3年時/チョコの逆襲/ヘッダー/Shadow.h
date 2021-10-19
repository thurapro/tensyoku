//=============================================================================
//
// フィールド処理 [Field.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "InputKey.h"
#include "Field.h"
#include "Player.h"
#include "Bullet.h"

//=============================================================================
// 影構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ワールド
	D3DXVECTOR3 posShadow;						// 影の位置
	D3DXVECTOR3 rotShadow;						// 影の向き
	D3DXVECTOR3 sclShadow;						// 影の大きさ
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZの頂点バッファ
	LPDIRECT3DTEXTURE9 pD3DTex;					// テクスチャ
	int nType;									// 何の影なのか
	bool visible;								// 表示変数
	int nNum;
}SHADOW;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT ShadowInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fShadowWidth , float fShadowHeight);	// 影の初期化
void ShadowUninit(void);										// 影破棄
void ShadowUpdate(D3DXVECTOR3 position , int nNum, int nType);			// 影の更新
void ShadowDraw(LPDIRECT3DDEVICE9 pD3DDevice);					// 影の描画
void ShadowSet(D3DXVECTOR3 position , int nType , int nNum);	// 影のセット
void ShadowDelete(int nType , int nNum);						// 影の削除

#endif	// _SHADOW_H_
