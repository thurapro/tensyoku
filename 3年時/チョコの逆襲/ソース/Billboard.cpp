//=============================================================================
//
// フィールド処理 [Billboard.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Billboard.h"
	
//==============================================================================
// マクロ定義
//==============================================================================
#define MOVE_Z			( 1.0f )

//=============================================================================
// グローバル変数
//=============================================================================
static D3DXMATRIX g_mtxWorld;						// ワールド
static D3DXVECTOR3 g_posBillboard;					// 影の位置
static D3DXVECTOR3 g_rotBillboard;					// 影の向き
static D3DXVECTOR3 g_sclBillboard;					// 影の大きさ
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZの頂点バッファ
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファ
static LPDIRECT3DTEXTURE9 g_pD3DTex = NULL;			// テクスチャ
static int g_nVertexMax;							// 頂点バッファ数
static int g_nIndexMax;
static D3DXVECTOR3 CameraRotSet;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexBillboard( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y);

//=============================================================================
//
//	関数名	: BillboardInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: フィールド初期化
//
//=============================================================================
HRESULT BillboardInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nBillboardScl_X , int nBillboardScl_Y)
{
	//-------------------------------------------------------------------------
	// フィールド初期化
	g_posBillboard = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );	// 影の位置
	g_rotBillboard = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// 影の向き
	g_sclBillboard = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 影の大きさ

	//-------------------------------------------------------------------------
	// テクスチャのロード
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/tako.png" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexBillboard(pD3DDevice , fPolygonWidth , fPolygonHeight , nBillboardScl_X , nBillboardScl_Y) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: BillboardUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド破棄
//
//=============================================================================
void BillboardUninit( void )
{
	// もしテクスチャが解放されていなければ
	if(g_pD3DTex != NULL)
	{
		// テクスチャの解放
		g_pD3DTex->Release();

		// テクスチャの部分をNULLへ
		g_pD3DTex = NULL;
	}

	//-------------------------------------------------------------------------
	// 頂点バッファの解放
	if( g_pD3DVBXYZBuffer != NULL )
	{
		g_pD3DVBXYZBuffer->Release();
		g_pD3DVBXYZBuffer = NULL; 
	}
	
}

//=============================================================================
//
//	関数名	: BillboardUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド更新
//
//=============================================================================
void BillboardUpdate( void )
{
	CameraRotSet = CameraRotGet();

	if( KeyState(DIK_UP))
	{
		g_posBillboard.x += sinf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z += cosf( CameraRotSet.y ) * MOVE_Z;
	}
	
	if( KeyState(DIK_DOWN))
	{
		g_posBillboard.x -= sinf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z -= cosf( CameraRotSet.y ) * MOVE_Z;
	}

	if( KeyState(DIK_LEFT) )
	{
		g_posBillboard.x -= cosf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z += sinf( CameraRotSet.y ) * MOVE_Z;
	}

	if( KeyState(DIK_RIGHT) )
	{
		g_posBillboard.x += cosf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z -= sinf( CameraRotSet.y ) * MOVE_Z;
	}

}

//=============================================================================
//
//	関数名	: BillboardDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド描画
//
//=============================================================================
void BillboardDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	HRESULT hr;
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ワールドマトリックス
	D3DXMatrixIdentity( &g_mtxWorld );		// ワールドマトリックス初期化

	D3DXMatrixInverse( &g_mtxWorld , NULL , &mtxView );
	g_mtxWorld._41 = 0.0f;
	g_mtxWorld._42 = 0.0f;
	g_mtxWorld._43 = 0.0f;

	//*********************************
	// スケール反映
	D3DXMatrixScaling( &mtxScl , g_sclBillboard.x , g_sclBillboard.y , g_sclBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// 回転反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotBillboard.y , g_rotBillboard.x , g_rotBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// 移動反映
	D3DXMatrixTranslation( &mtxTrans , g_posBillboard.x , g_posBillboard.y , g_posBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ワールドマトリックス設定
	pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );

	//-------------------------------------------------------------------------
	// 頂点情報設定
	pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

	//-------------------------------------------------------------------------
	//  頂点バッファのセット
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );
	hr = pD3DDevice->SetIndices( g_pIndexBuffer );

	//-------------------------------------------------------------------------
	// テクスチャのセット
	pD3DDevice->SetTexture( 0 , g_pD3DTex );

	pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
	
	//-------------------------------------------------------------------------
	// プリミティブ表示
	pD3DDevice->DrawPrimitive
				( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
				0 ,								// 三角形の数
				2 );							// プリミティブの数

	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
}

//=============================================================================
//
// 関数名 : MakeVertexBillboard
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexBillboard( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y)
{
	//---------------------
	// 変数宣言
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	float fX = 0;
	float fY = 0;
	g_nVertexMax = ( (nScl_X + 1) * (nScl_Y + 1) );
	int nVertexHalf = (nScl_X + 1);
	float fTexX = 0.f;
	float fTexY = 0.f;
	float fTexWidth = 0.f;
	float fTexHeight = 0.f;
	int nScl_YMax = 1;
	int nNum_Kisu = 0;
	int nNum_Gusu = 0;

	for( int nCnt = 0; nCnt < nScl_Y; nCnt++ )
	{
		nScl_YMax *= 2;
	}

	//---------------------------------------------------------------------
	// 頂点バッファ作成処理
	hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * g_nVertexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&g_pD3DVBXYZBuffer,
										NULL );
	if( FAILED(hr) )
	{
		return (E_FAIL);
	}

	//-------------------------------------------------------------------------
	// 頂点バッファのロック
	hr = g_pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	//-------------------------------------------------------------------------
	// 頂点バッファの座標設
	
	float A = (float)nScl_X/2;
	float B = -A * fWidth;

	int i = 0;
	while( i < g_nVertexMax )
	{
		for( int j = 0; j < nVertexHalf; j++ )
		{
			pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , (-B - fY ) , 0.f );

			//-------------------------------------------------------------------------
			// 向きの設定
			pVtx[i].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

			//---------------------------------------------------------------------
			// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
			pVtx[i].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
														BLUE_MAX , ALPHA_MAX );
			
			pVtx[i].tex = D3DXVECTOR2( fTexX + fTexWidth , fTexY + fTexHeight );

			//-------------------------------------------------------------------------
			// 幅を広げる
			fX += fWidth;
			fTexWidth += 1.f;

			i++;
		}
			
		//-------------------------------------------------------------------------
		// 幅を初期値に
		fX = 0;
		fTexWidth = 0.f;
	
		//--------------------------------------------------------------------------
		// 高さを広げる
		fY += fHeight;
		fTexHeight += 1.f;
	}

	//-------------------------------------------------------------------------
	// 頂点バッファのロック解
	g_pD3DVBXYZBuffer->Unlock();
	
	
	// 作成成功
	return (S_OK);
}

//=============================================================================
// ビルボード位置取得
//=============================================================================
D3DXVECTOR3 BillboardPosGet(void)
{
	return g_posBillboard;
}