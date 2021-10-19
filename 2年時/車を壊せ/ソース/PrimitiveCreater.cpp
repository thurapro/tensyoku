//================================
// インクルード
//================================
#include <d3dx9.h>
#include <windows.h>
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/common.h"
#include "../hedder/Direct3DCreater.h"
#include "../hedder/Texture.h"
#include "../hedder/InputKey.h"
#include "../hedder/common.h"
#include "../hedder/math.h"

//============================================================================
// グローバル変数
//============================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer[BUFFERMAX] = {NULL};	// XYZの頂点バッファ
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer[BUFFERMAX] = {NULL};		// インデックスバッファ
static VTEX g_Vtex;
static float g_fWidth	= 0;
static float g_fHeight	= 0;
static float g_fAngle	= 0;
static float g_fPosX	= 0;
static float g_fPosY	= 0;

//=============================================================================
//
// 関数名	:	PrimitiveInit
//
// 戻り値	:	初期化することができたか BOOL
//
// 引数		:	なし
//
// 機能		:	頂点バッファー作成
//				インデックスバッファー作成
//
//=============================================================================
BOOL PrimitiveInit( void )
{
	// 審判
	HRESULT hr;

	// プリミティブ描画
	VERTEX_2D *pVtx;

	// デバイスを取得
	LPDIRECT3DDEVICE9	pD3DDevice  = Direct3ddeviceGetDevice();

	WORD *pIdx;

	for( int i = 0; i < MAXID; i++)
	{
		// 頂点バッファを作成
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * VTEXMAX,
											D3DUSAGE_WRITEONLY,
											D3DFMT_VERTEXDATA,
											D3DPOOL_MANAGED,
											&g_pD3DVBXYZBuffer[i],
											NULL );
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// インデックスバッファを作成
		hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * VTEXMAX , 
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_pIndexBuffer[i],
											NULL);
		if( FAILED( hr ) )
		{
			return FALSE;
		}


		// 頂点バッファのロック
		hr = g_pD3DVBXYZBuffer[i]->Lock( 0 , 0 , (void **)&pVtx , 0);
		
		// 頂点バッファがロックできていなければ
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// 頂点バッファの座標設定
		pVtx[LEFTTOP_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// 左上の頂点

		pVtx[RIGHTTOP_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// 右上の頂点

		pVtx[LEFTBOTTOM_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// 右下の頂点

		pVtx[RIGHTBOTTOM_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );	// 左下の頂点
		

		// rhwの設定
		pVtx[LEFTTOP_VTEX].rhw = 1.f;

		pVtx[RIGHTTOP_VTEX].rhw = 1.f;

		pVtx[LEFTBOTTOM_VTEX].rhw = 1.f;

		pVtx[RIGHTBOTTOM_VTEX].rhw = 1.f;


		// 色情報の設定					( 赤 , 緑 , 青 , 透明度)
		pVtx[LEFTTOP_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[RIGHTTOP_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[LEFTBOTTOM_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[RIGHTBOTTOM_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );


		// テクスチャの座標設定
		pVtx[LEFTTOP_VTEX].tex = D3DXVECTOR2(0.f, 0.f);						// 左上のテクスチャ頂点設定

		pVtx[RIGHTTOP_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// 右上のテクスチャ頂点設定

		pVtx[LEFTBOTTOM_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// 右下のテクスチャ頂点設定

		pVtx[RIGHTBOTTOM_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// 左下のテクスチャ頂点設定


		// 頂点バッファのロック解除
		g_pD3DVBXYZBuffer[i]->Unlock();

		// インデックスバッファのロック
		hr = g_pIndexBuffer[i]->Lock( 0 , 0 , (void **)&pIdx , 0);

		// ロックされなかった場合
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// インデックスの書き込み
		pIdx[LEFTTOP_VTEX] = LEFTTOP_VTEX;

		pIdx[RIGHTTOP_VTEX] = RIGHTTOP_VTEX;

		pIdx[LEFTBOTTOM_VTEX] = LEFTBOTTOM_VTEX;

		pIdx[RIGHTBOTTOM_VTEX] = RIGHTBOTTOM_VTEX;

		// インデックスバッファのロック解除
		g_pIndexBuffer[i]->Unlock();
		
	}
	return TRUE;
}


//============================================================================
//
// 関数名	:	PrimitiveGetDevice関数
//
// 戻り値	:	デバイスを返す
//
// 引数		:	テキスチャの番号
//				頂点座標始点(x , y)
//				頂点座標終点(x , y)
//				テキスチャ始点座標(x , y)
//				テキスチャ終点座標(x , y)
//
// 機能		:	プリミティブの生成
//			
//
//============================================================================
void PrimitiveCreate(	int ID,										// どのプリミティブを作りたいか
						int VtxType	,								// プリミティブが回転するか(1) , しないか(2)
						int TextureNum ,							// テクスチャの番号
						float fAngle ,								// テクスチャの角度
						float fPosX , float fPosY,					// 頂点ポジション指定
						float fWidth , float fHeight,				// 幅と高さ指定
						float texx0 , float texy0,					// テキスチャーの始点座標
						float texx1 , float texy1 )					// テキスチャーの終点座標
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pD3DDevice  = Direct3ddeviceGetDevice();

	// テクスチャのポインタ定義
	LPDIRECT3DTEXTURE9 *pD3DTex;

	// テクスチャを持ってくる
	pD3DTex = GetD3DTexture(TextureNum);

	// プリミティブ描画
	VERTEX_2D *pVtx;

	// 頂点の値を設定できたかのフラグ
	BOOL bVtex = FALSE;

	// 幅の設定
	g_fWidth	= fWidth ;

	// 高さの設定
	g_fHeight	= fHeight;

	// 角度の設定
	g_fAngle	= fAngle;

	// 位置設定
	g_fPosX		= fPosX;

	// 位置設定
	g_fPosY		= fPosY;

	// 頂点を回る形式でつくるか
	// 頂点を回らない形式でつくるのか
	switch( VtxType )
	{
		// 回る頂点設定
	case ROTATION	: VtexRotation();

		// 頂点座標正常に設定された
		bVtex = TRUE;
		break;
	
		// 回らない頂点設定
	case KUNCLE	: VtexKnuckle();

		// 頂点座標正常に設定された
		bVtex = TRUE;
		break;

	default :
		break;
	}

	if( bVtex == FALSE )
	{
		return ;
	}



	// 頂点バッファのロック
	g_pD3DVBXYZBuffer[ID]->Lock( 0 , 0 , (void **)&pVtx , 0);

	
	// 頂点バッファの座標設定
	pVtx[LEFTTOP_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx1 + fPosX  , g_Vtex.fVtexy1 + fPosY, 0.f );	// 左上の頂点

	pVtx[RIGHTTOP_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx2  + fPosX , g_Vtex.fVtexy2 + fPosY , 0.f );	// 右上の頂点

	pVtx[LEFTBOTTOM_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx3  + fPosX , g_Vtex.fVtexy3 + fPosY , 0.f );	// 右下の頂点

	pVtx[RIGHTBOTTOM_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx4  + fPosX , g_Vtex.fVtexy4 + fPosY , 0.f );	// 左下の頂点
	

	// テクスチャの座標設定
	pVtx[LEFTTOP_VTEX].tex = D3DXVECTOR2(texx0, texy0);							// 左上のテクスチャ頂点設定

	pVtx[RIGHTTOP_VTEX].tex = D3DXVECTOR2(texx1, texy0);							// 右上のテクスチャ頂点設定

	pVtx[LEFTBOTTOM_VTEX].tex = D3DXVECTOR2(texx0, texy1);							// 右下のテクスチャ頂点設定

	pVtx[RIGHTBOTTOM_VTEX].tex = D3DXVECTOR2(texx1, texy1);							// 左下のテクスチャ頂点設定

	// 頂点バッファのロック解除
	g_pD3DVBXYZBuffer[ID]->Unlock();


	// 頂点フォーマットを設定
	pD3DDevice->SetFVF( FVF_VERTEX_2D_TEX );	// 頂点フォーマットは2D座標と色に設定

	//  頂点バッファのセット
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer[ID] , 0 ,sizeof(VERTEX_2D) );

	// インデックスバッファのセット
	pD3DDevice->SetIndices(g_pIndexBuffer[ID]);

	// テクスチャのセット
	pD3DDevice->SetTexture( 0 , *pD3DTex );
	
	// プリミティブ表示
	pD3DDevice->DrawIndexedPrimitive
				( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
				0 ,								// 三角形の数
				0 ,
				VTEXMAX ,						// 頂点の個数
				0 ,
				2 );
	
}

//=============================================================================
//
// 関数名	: PrimitiveUninit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プリミティブの解放
//
//=============================================================================
void PrimitiveUninit( void )
{
	for( int i = 0; i < MAXID; i++ )
	{
		// 頂点バッファの解放
		if( g_pD3DVBXYZBuffer[i] != NULL )
		{
			g_pD3DVBXYZBuffer[i]->Release();
			g_pD3DVBXYZBuffer[i] = NULL; 
		}

		// インデックスバッファの解放
		if( g_pIndexBuffer[i] != NULL )
		{
			g_pIndexBuffer[i]->Release();
			g_pIndexBuffer[i] = NULL;
		}
	}
}

//=============================================================================
//
// 関数名	: VTexRatation関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 回る頂点設定
//
//=============================================================================
void VtexRotation( void )
{
	// 角度を求める
	float AngleOld = AngleMath( g_fWidth , g_fHeight );

	// 半径を求める
	float Raidus = RaidusMath();

	// 中心Xを求める式
	float CenterX = g_fWidth  * 0.5f ;

	// 中心Yを求める式
	float CenterY = g_fHeight * 0.5f ;

	// 頂点1のX座標を設定
	g_Vtex.fVtexx1 = CenterX - sinf( AngleOld - g_fAngle ) * Raidus;

	// 頂点1のY座標を設定
	g_Vtex.fVtexy1 = CenterY - cosf( AngleOld - g_fAngle ) * Raidus;

	// 頂点2のX座標を設定
	g_Vtex.fVtexx2 = CenterX + sinf( AngleOld + g_fAngle ) * Raidus;

	// 頂点2のY座標を設定
	g_Vtex.fVtexy2 = CenterY - cosf( AngleOld + g_fAngle ) * Raidus;

	// 頂点3のX座標を設定
	g_Vtex.fVtexx3 = CenterX - sinf( AngleOld + g_fAngle ) * Raidus;

	// 頂点3のY座標を設定
	g_Vtex.fVtexy3 = CenterY + cosf( AngleOld + g_fAngle ) * Raidus;

	// 頂点4のX座標を設定
	g_Vtex.fVtexx4 = CenterX + sinf( AngleOld - g_fAngle ) * Raidus;

	// 頂点4のY座標を設定
	g_Vtex.fVtexy4 = CenterY + cosf( AngleOld - g_fAngle ) * Raidus;
}

//=============================================================================
//
// 関数名	: VTexKnuckle関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 回わらない頂点設定
//
//=============================================================================
void VtexKnuckle( void )
{
	g_Vtex.fVtexx1 = g_fPosX;
	g_Vtex.fVtexy1 = g_fPosY;
	g_Vtex.fVtexx2 = g_fWidth;
	g_Vtex.fVtexy2 = g_fPosY;
	g_Vtex.fVtexx3 = g_fPosX;
	g_Vtex.fVtexy3 = g_fHeight;
	g_Vtex.fVtexx4 = g_fWidth;
	g_Vtex.fVtexy4 = g_fHeight;
}