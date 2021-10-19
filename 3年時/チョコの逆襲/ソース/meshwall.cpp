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
#include "../hedder/meshwall.h"

//=============================================================================
// グローバル変数
//=============================================================================
static MESH_WALL g_aMeshWall[WALL_MAX];
static int g_nNumMeshWall = 0;						// 壁の大きさ
static int g_nVertexMax;							// 頂点バッファ数
static int g_nIndexMax;								// インデックスバッファ数

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y );

//=============================================================================
//
//	関数名	: MeshWallInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: フィールド初期化
//
//=============================================================================
HRESULT MeshWallInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nWallScl_X , int nWallScl_Y)
{
	float fPos_X = (fPolygonWidth * nWallScl_X) / 2;
	float fPos_Y = (fPolygonHeight * nWallScl_Y) / 2;

	float fPos_Z = (fPolygonHeight * nWallScl_Y) / 2;

	//-------------------------------------------------------------------------
	// 壁初期化
	g_aMeshWall[0].pos = D3DXVECTOR3( 0.0f , fPos_Y , fPos_Z );	// 壁の位置
	g_aMeshWall[0].rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// 壁の向き
	g_aMeshWall[0].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 壁の大きさ

	g_aMeshWall[1].pos = D3DXVECTOR3( fPos_X , fPos_Y , 0.0f );	// 壁の位置
	g_aMeshWall[1].rot = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );	// 壁の向き
	g_aMeshWall[1].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 壁の大きさ

	g_aMeshWall[2].pos = D3DXVECTOR3( -fPos_X , fPos_Y , 0.0f );	// 壁の位置
	g_aMeshWall[2].rot = D3DXVECTOR3( 0.0f , D3DX_PI * -0.5f , 0.0f );	// 壁の向き
	g_aMeshWall[2].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 壁の大きさ

	g_aMeshWall[3].pos = D3DXVECTOR3( 1.0f , fPos_Y , -fPos_Z);	// 壁の位置
	g_aMeshWall[3].rot = D3DXVECTOR3( 0.0f , D3DX_PI * 1.0f , 0.0f );	// 壁の向き
	g_aMeshWall[3].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// 壁の大きさ

	//-------------------------------------------------------------------------
	// テクスチャのロード
	for( int i = 0; i < WALL_MAX; i++ )
	{
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/fa.jpg" , &g_aMeshWall[i].pD3DTexture) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexMeshWall(pD3DDevice , fPolygonWidth , fPolygonHeight , nWallScl_X ,  nWallScl_Y ) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: MeshWallUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 壁破棄
//
//=============================================================================
void MeshWallUninit( void )
{
	for( int i = 0; i < WALL_MAX; i++ )
	{
		// もしテクスチャが解放されていなければ
		if(g_aMeshWall[i].pD3DTexture != NULL)
		{
			// テクスチャの解放
			g_aMeshWall[i].pD3DTexture->Release();

			// テクスチャの部分をNULLへ
			g_aMeshWall[i].pD3DTexture = NULL;
		}

		//-------------------------------------------------------------------------
		// インデックスバッファの解放
		if( g_aMeshWall[i].pIndexBuffer != NULL )
		{
			g_aMeshWall[i].pIndexBuffer->Release();
			g_aMeshWall[i].pIndexBuffer = NULL;
		}

		//-------------------------------------------------------------------------
		// 頂点バッファの解放
		if( g_aMeshWall[i].pD3DVBXYZBuffer != NULL )
		{
			g_aMeshWall[i].pD3DVBXYZBuffer->Release();
			g_aMeshWall[i].pD3DVBXYZBuffer = NULL; 
		}
	}
}

//=============================================================================
//
//	関数名	: MeshWallUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 壁更新
//
//=============================================================================
void MeshWallUpdate( void )
{

}

//=============================================================================
//
//	関数名	: MeshWallDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 壁描画
//
//=============================================================================
void MeshWallDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	HRESULT hr;
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < WALL_MAX; i++)
	{
		//-------------------------------------------------------------------------
		// ワールドマトリックス
		D3DXMatrixIdentity( &g_aMeshWall[i].mtxWorld );		// ワールドマトリックス初期化

		//*********************************
		// スケール反映
		D3DXMatrixScaling( &mtxScl , g_aMeshWall[i].scl.x , g_aMeshWall[i].scl.y , g_aMeshWall[i].scl.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxScl );
		
		//*********************************
		// 回転反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aMeshWall[i].rot.y , g_aMeshWall[i].rot.x , g_aMeshWall[i].rot.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxRot );

		//*********************************
		// 移動反映
		D3DXMatrixTranslation( &mtxTrans , g_aMeshWall[i].pos.x , g_aMeshWall[i].pos.y , g_aMeshWall[i].pos.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxTrans );

		//-------------------------------------------------------------------------
		// ワールドマトリックス設定
		pD3DDevice->SetTransform( D3DTS_WORLD , &g_aMeshWall[i].mtxWorld );	

		//-------------------------------------------------------------------------
		// 頂点情報設定
		pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

		//-------------------------------------------------------------------------
		//  頂点バッファのセット
		pD3DDevice->SetStreamSource( 0 , g_aMeshWall[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );
		hr = pD3DDevice->SetIndices( g_aMeshWall[i].pIndexBuffer );

		//-------------------------------------------------------------------------
		// テクスチャのセット
		pD3DDevice->SetTexture( 0 , g_aMeshWall[i].pD3DTexture );

		if(i == 4)
		{
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		
		//-------------------------------------------------------------------------
		// プリミティブ表示
		pD3DDevice->DrawIndexedPrimitive
					( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
					0 ,								// 三角形の数
					0 ,
					g_nVertexMax ,					// 頂点の個数（頂点バッファ）
					0 ,
					g_nIndexMax - 2 );				// プリミティブの数
		if(i == 4)
		{
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}

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
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y )
{
	//---------------------
	// 変数宣言
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	WORD *pIdx;			// 添え字数
	for( int nNum = 0; nNum < WALL_MAX; nNum++ )
	{
		float fX = 0;
		float fY = 0;
		g_nVertexMax = ( (nScl_X + 1) * (nScl_Y + 1) );
		int nVertexHalf = (nScl_X + 1);
		float fTexX = 0.f;
		float fTexY = 0.f;
		float fTexWidth = 0.f;
		float fTexHeight = 0.f;

		//---------------------------------------------------------------------
		int nScl_YMax = 1;
		int nNum_Kisu = 0;
		int nNum_Gusu = 0;


		//---------------------------------------------------------------------
		// 頂点バッファ作成処理
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * g_nVertexMax ,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aMeshWall[nNum].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// 頂点バッファのロック
		hr = g_aMeshWall[nNum].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		//-------------------------------------------------------------------------
		// 頂点バッファの座標設
		
		float A = (float)nScl_X/2;
		float B = -A * fWidth;
		
		for( int i = 0; i < g_nVertexMax; )
		{
			for( int j = 0; j < nVertexHalf; j++ )
			{
				pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , (-B - fY) , 0.0f );

				//-------------------------------------------------------------------------
				// 向きの設定
				pVtx[i].nor = D3DXVECTOR3( 0.f , 0.f , -1.f );

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
		g_aMeshWall[nNum].pD3DVBXYZBuffer->Unlock();

		g_nIndexMax = ( ( g_nVertexMax - 2 ) * 2 );


		//-------------------------------------------------------------------------
		// インデックスバッファ作成
		hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * g_nIndexMax , 
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_aMeshWall[nNum].pIndexBuffer,
											NULL );
		// 作成失敗した場合
		if( FAILED(hr) )
		{
			// バッファ作成失敗
			return (E_FAIL);
		}
		
		//---------------------------------------------------------------------
		// インデックスバッファのロック
		hr = g_aMeshWall[nNum].pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

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
		g_aMeshWall[nNum].pIndexBuffer->Unlock();
	}
		
	// 作成成功
	return (S_OK);
}

MESH_WALL *MeshWallGet(void)
{
	return &g_aMeshWall[0];
}
