//=============================================================================
//
// フィールド処理 [Effect.h]
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
#include "WinMain.h"

//=============================================================================
// エフェクト構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ワールド
	D3DXVECTOR3 posEffect;						// エフェクトの位置
	D3DXVECTOR3 rotEffect;						// エフェクトの向き
	D3DXVECTOR3 sclEffect;						// エフェクトの大きさ
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZの頂点バッファ
	LPDIRECT3DTEXTURE9 pD3DTex;					// テクスチャ
	bool visible;								// 表示変数
	int nAlpha;									// アルファー値
	int nType;
}EFFECT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT EffectInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// エフェクトの初期化
void EffectUninit(void);																			// エフェクト破棄
void EffectUpdate(void);																			// エフェクトの更新
void EffectDraw(LPDIRECT3DDEVICE9 pD3DDevice);														// エフェクト更新
void EffectSet( D3DXVECTOR3 position , int nType );

#endif	// _EFFECT_H_
