//=============================================================================
//
// 弾の処理 [Bullet.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "Sound.h"
#include "common.h"
#include "Camera.h"
#include "InputKey.h"
#include "Shadow.h"
#include "Field.h"
#include "Explosion.h"
#include "Effect.h"
#include "meshwall.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define BULLET_TYPE	(1)							// タイプ
#define BULLET_NUM	(i)						// 弾の番号
#define BULLET_MAX (40)							// 弾の数

//=============================================================================
// 弾の構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ワールド
	D3DXVECTOR3 posBullet;						// 弾の位置
	D3DXVECTOR3 rotBullet;						// 弾の向き
	D3DXVECTOR3 sclBullet;						// 弾の大きさ
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZの頂点バッ
	LPDIRECT3DTEXTURE9 pD3DTex;					// テクスチャ
	LPDIRECTSOUNDBUFFER soundBullet;			// サウンド
	int nVertexMax;								// 頂点バッファ数
	bool visible;								// 表示するかしないか
	float frotMove;								// 進む方向
	float fMoveX;
	float fMoveZ;
	D3DXVECTOR3 MemoryPos;						// 前にあった場所
	float fWidth;
	float fHeight;
	int nType;
}BULLET;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT BulletInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// 弾の初期化
void BulletUninit(void);											// 弾破棄
void BulletUpdate(void);											// 弾の更新
void BulletDraw(LPDIRECT3DDEVICE9 pD3DDevice);						// 弾更新
void BulletSet(D3DXVECTOR3 position , float rot , int nType);					// 弾のセット
BULLET *BulletPosGet(void);											// 弾の位置取得

#endif	// _BULLET_H_
