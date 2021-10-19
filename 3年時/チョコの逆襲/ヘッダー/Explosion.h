//=============================================================================
//
// 爆発の処理 [Explosion.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Camera.h"
#include "InputKey.h"
#include "clear.h"
#include "Sound.h"

//=============================================================================
// 爆発の構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ワールド
	D3DXVECTOR3 posExplosion;					// 爆発の位置
	D3DXVECTOR3 rotExplosion;					// 爆発の向き
	D3DXVECTOR3 sclExplosion;					// 爆発の大きさ
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZの頂点バッ
	LPDIRECT3DTEXTURE9 pD3DTex;					// テクスチャ
	int nVertexMax;								// 頂点バッファ数
	bool visible;								// 表示するかしないか
	float fAnimesionLeft;						// 爆発アニメーション左座標基準
	float fAnimesionRight;						// 爆発アニメーション右座標基準
	LPDIRECTSOUNDBUFFER soundExplosion;
}EXPLOSION;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT ExplosionInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// 爆発の初期化
void ExplosionUninit(void);											// 爆発破棄
void ExplosionUpdate(void);											// 爆発の更新
void ExplosionDraw(LPDIRECT3DDEVICE9 pD3DDevice);					// 爆発更新
void ExplosionSet(D3DXVECTOR3 position);							// 爆発のセット

#endif	// _EXPLOSION_H_
