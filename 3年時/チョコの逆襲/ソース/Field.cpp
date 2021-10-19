//=============================================================================
//
// フィールド処理 [Field.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Field.h"

//=============================================================================
// グローバル変数
//=============================================================================
static D3DXMATRIX g_mtxView;						// ビュー	
static D3DXMATRIX g_mtxProjection;					// プロジェクション
static D3DXMATRIX g_mtxWorld;						// ワールド
static D3DXVECTOR3 g_posField;						// 影の位置
static D3DXVECTOR3 g_rotField;						// 影の向き
static D3DXVECTOR3 g_sclField;						// 影の大きさ
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZの頂点バッファ
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファ
static LPDIRECT3DTEXTURE9 g_pD3DTex = NULL;			// テクスチャ
static int g_nVertexMax;							// 頂点バッファ数
static int g_nIndexMax;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexField( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y);

//=============================================================================
//
//	関数名	: FieldInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: フィールド初期化
//
//=============================================================================
HRESULT FieldInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nFieldScl_X , int nFieldScl_Y)
{
	//-------------------------------------------------------------------------
	// フィールド初期化
	g_posField = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// 地面の位置
	g_rotField = D3DXVECTOR3( 0.f , 0.f , 0.f );	// 地面の向き
	g_sclField = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 地面の大きさ

	//-------------------------------------------------------------------------
	// テクスチャのロード
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/field.jpg" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexField(pD3DDevice , fPolygonWidth , fPolygonHeight , nFieldScl_X , nFieldScl_Y) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: FieldUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド破棄
//
//=============================================================================
void FieldUninit( void )
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

	//-------------------------------------------------------------------------
	// インデックスバッファの解放
	if( g_pIndexBuffer != NULL )
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

//=============================================================================
//
//	関数名	: FieldUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド更新
//
//=============================================================================
void FieldUpdate( void )
{
	/*//---------------------------------
	// 右移動
	if( KeyState( DIK_D ) )
	{
		g_posField.x += 3;
	}

	//---------------------------------
	// 左移動
	if( KeyState( DIK_A ) )
	{
		g_posField.x -= 3;
	}

	//---------------------------------
	// 奥移動
	if( KeyState( DIK_W ) )
	{
		g_posField.z += 3;
	}

	//---------------------------------
	// 手前移動
	if( KeyState( DIK_S ) )
	{
		g_posField.z -= 3;
	}

	//---------------------------------
	// 上移動
	if( KeyState( DIK_UP ) )
	{
		g_posField.y += 2;
	}

	//---------------------------------
	// 下移動
	if( KeyState( DIK_DOWN ) )
	{
		g_posField.y -= 2;
	}*/
}

//=============================================================================
//
//	関数名	: FieldDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド描画
//
//=============================================================================
void FieldDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	HRESULT hr;
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ワールドマトリックス
	D3DXMatrixIdentity( &g_mtxWorld );		// ワールドマトリックス初期化

	//*********************************
	// スケール反映
	D3DXMatrixScaling( &mtxScl , g_sclField.x , g_sclField.y , g_sclField.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// 回転反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotField.y , g_rotField.x , g_rotField.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// 移動反映
	D3DXMatrixTranslation( &mtxTrans , g_posField.x , g_posField.y , g_posField.z );
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
	
	//-------------------------------------------------------------------------
	// プリミティブ表示
	pD3DDevice->DrawIndexedPrimitive
				( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
				0 ,								// 三角形の数
				0 ,
				g_nVertexMax ,							// 頂点の個数（頂点バッファ）
				0 ,
				g_nIndexMax - 2 );							// プリミティブの数
}

//=============================================================================
//
// 関数名 : MakeVertexField
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexField( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y)
{
	//---------------------
	// 変数宣言
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	WORD *pIdx;			// 添え字数
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
			pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , 0.f , (-B - fY ) );

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

	g_nIndexMax = ( ( g_nVertexMax - 2 ) * 2 );


	//-------------------------------------------------------------------------
	// インデックスバッファ作成
	hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * g_nIndexMax , 
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&g_pIndexBuffer,
										NULL );
	// 作成失敗した場合
	if( FAILED(hr) )
	{
		// バッファ作成失敗
		return (E_FAIL);
	}
	
	//---------------------------------------------------------------------
	// インデックスバッファのロック
	hr = g_pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

	int index = 0;
	int gyo = 0;
	int polygon = 0;
	while( index < g_nIndexMax )
	{
		// 折り返し地点だった場合
		if( index ==  (( nScl_X * 2 ) + 1)  + gyo )
		{
			for( int k = 0; k < 2; k++ )
			{
				if( index != g_nIndexMax )
				{ 
					pIdx[index] = nScl_X + polygon;
					index++;
				}
			}

			if( index < g_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( nScl_X + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (nScl_X + 1 )+ 1) * 2;
				polygon += (nScl_X + 1);
			}
		}
		// 偶数だった場合
		else if( index % 2 == 0 )
		{
			pIdx[index] =  (nScl_X + 1) + nNum_Gusu;
			nNum_Gusu++;
			index++;
		}

		// 奇数だった場合
		else if(  index % 2 == 1 )
		{
			pIdx[index] = nNum_Kisu;
			nNum_Kisu++;
			index++;
		}
	}
			

	//---------------------------------------------------------------------
	// インデックスバッファのロック解除
	g_pIndexBuffer->Unlock();
	
	// 作成成功
	return (S_OK);
}

D3DXVECTOR3 FieldPosGet(void)
{
	return g_posField;
}
