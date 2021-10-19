#ifndef	_PRIMITIVE_H_
#define _PRIMITIVE_H_

//===========================================================================
// インクルード
//===========================================================================
#include <d3dx9.h>
#include <windows.h>

//============================================================================
// マクロ定義
//============================================================================		
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define ROTATION			( 1 )				// 回転頂点
#define KUNCLE				( 2 )				// 無回転頂点
#define BUFFERMAX			( 20 )				// バッファの最大数
#define VTEXMAX				( 4 )				// 頂点の最大数
#define RED_MAX				( 255 )				// 赤色の最大色
#define GREEN_MAX			( 255 )				// 緑色の最大色
#define BLUE_MAX			( 255 )				// 青色の最大色
#define ALPHA_MAX			( 255 )				// 透明度の最大
#define LEFTTOP_VTEX		( 0 )				// 頂点座標左上
#define RIGHTTOP_VTEX		( 1 )				// 頂点座標右上
#define LEFTBOTTOM_VTEX		( 2 )				// 頂点座標左下
#define RIGHTBOTTOM_VTEX	( 3 )				// 頂点座標右下

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DVECTOR	vtx;							// 頂点座標(x,y,z)
	float		rhw;							// reciprocal homogeneous w(同次座標のw要素の逆数)
	D3DCOLOR	diffuse;						// 色の情報
	D3DXVECTOR2	tex	;							// 画像情報表示
}VERTEX_2D;

typedef struct
{
	float fVtexx1;								// テクスチャ頂点1
	float fVtexy1;								// テクスチャ頂点1
	float fVtexx2;								
	float fVtexy2;
	float fVtexx3;
	float fVtexy3;
	float fVtexx4;
	float fVtexy4;
}VTEX;


//=============================================================================
// プロトタイプ宣言
//=============================================================================
BOOL PrimitiveInit( void );						// プリミティブの初期化

void PrimitiveCreate(	int ID			,		// どのプリミティブを作るか
						int VtxType		,		// プリミティブが回転するか(1),しないか(2)
						int TextureNum	,		// テクスチャの番号
						float fAngle	,		// テクスチャの角度※回らない場合は０
						float fPosX		,		// 頂点1の設定
						float fPosY		,		// 頂点1の設定
						float ffWidth	,		// 頂点2の設定
						float ffHeight	,		// 頂点2の設定
						float texx0		,		// テクスチャ始点座標
						float texy0		,		// テクスチャ始点座標
						float texx1		,		// テクスチャ終点座標
						float texy1		);		// テクスチャ終点座標

void PrimitiveUninit( void );					// プリミティブの解放

void VtexRotation( void );						// 回る頂点

void VtexKnuckle( void );						// 回らない頂点

#endif // _PRIMITIVE_H_


