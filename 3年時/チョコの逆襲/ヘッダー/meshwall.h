//=============================================================================
//
// フィールド処理 [meshwall.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Field.h"
#include "Bullet.h"
#include "WinMain.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define WALL_MAX (4)

//==============================================================================
// 壁の構造体
//==============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9 pD3DTexture;
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	int nNumBlockX;
	int nNumBlockY;
	int nNumVertex;
	int nNumIdx;
	int nNumPolygon;
	BOOL bUse;
	float fSizeBlockX;
	float fSizeBlockY;
}MESH_WALL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MeshWallInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nWallScl_X , int nWallScl_Y);		// 壁の初期化
void MeshWallUninit(void);								// 壁破棄
void MeshWallUpdate(void);								// 壁の更新
void MeshWallDraw(LPDIRECT3DDEVICE9 pD3DDevice);		// 壁更新
MESH_WALL *MeshWallGet(void);							// 壁の位置ゲット

#endif	// _FIELD_H_