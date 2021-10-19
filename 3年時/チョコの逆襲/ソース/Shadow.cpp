//=============================================================================
//
// フィールド処理 [Shadow.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SHADOW_MAX (100)					// 影の最大数

//=============================================================================
// グローバル変数
//=============================================================================
static SHADOW g_aShadow[SHADOW_MAX];		// 影変数

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pD3DDevice,float fShadowWidth,float fShadowHeight);

//=============================================================================
//
//	関数名	: ShadowInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: 影初期化
//
//=============================================================================
HRESULT ShadowInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fShadowWidth,float fShadowHeight)
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// 影初の期化
		g_aShadow[i].posShadow = D3DXVECTOR3( 0.0f , 0.1f , 0.0f );		// 影の位置
		g_aShadow[i].rotShadow = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 影の向き
		g_aShadow[i].sclShadow = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// 影の大きさ
		g_aShadow[i].visible = false;

		//-------------------------------------------------------------------------
		// テクスチャのロード
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/shadow000.jpg" , &g_aShadow[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexShadow(pD3DDevice , fShadowWidth , fShadowHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: ShadowUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 影破棄
//
//=============================================================================
void ShadowUninit( void )
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		// もしテクスチャが解放されていなければ
		if(g_aShadow[i].pD3DTex != NULL)
		{
			// テクスチャの解放
			g_aShadow[i].pD3DTex->Release();

			// テクスチャの部分をNULLへ
			g_aShadow[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// 頂点バッファの解放
		if( g_aShadow[i].pD3DVBXYZBuffer != NULL )
		{
			g_aShadow[i].pD3DVBXYZBuffer->Release();
			g_aShadow[i].pD3DVBXYZBuffer = NULL;
			
		}
	}

}

//=============================================================================
//
//	関数名	: ShadowUpdate
//	
//	戻り値	: なし
//
//	引数	: 位置
//			 何の影か
//
//	機能	: 影更新
//
//=============================================================================
void ShadowUpdate(D3DXVECTOR3 position , int nNum, int nType)
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		if(g_aShadow[i].visible == true)
		{
			if( g_aShadow[i].nNum == nNum)
			{
				if( g_aShadow[i].nType == nType )
				{
					g_aShadow[i].posShadow = position;
					g_aShadow[i].posShadow.y = 0.1f;
					break;
				}
			}
		}
	}
}

//=============================================================================
//
//	関数名	: ShadowDraw
//	
//	戻り値	: なし
//
//	引数	: デバイス
//
//	機能	: 影描画
//
//=============================================================================
void ShadowDraw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < SHADOW_MAX; i++ )
	{	
		if( g_aShadow[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ワールドマトリックス
			D3DXMatrixIdentity( &g_aShadow[i].mtxWorld );		// ワールドマトリックス初期化

			//*********************************
			// スケール反映
			D3DXMatrixScaling( &mtxScl , g_aShadow[i].sclShadow.x , g_aShadow[i].sclShadow.y , g_aShadow[i].sclShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxScl );
			
			//*********************************
			// 回転反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aShadow[i].rotShadow.y , g_aShadow[i].rotShadow.x , g_aShadow[i].rotShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxRot );

			//*********************************
			// 移動反映
			D3DXMatrixTranslation( &mtxTrans , g_aShadow[i].posShadow.x , g_aShadow[i].posShadow.y , g_aShadow[i].posShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ワールドマトリックス設定
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aShadow[i].mtxWorld );	

			//-------------------------------------------------------------------------
			// レンダーステート
			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE );

			//-------------------------------------------------------------------------
			// 頂点情報設定
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

			//-------------------------------------------------------------------------
			//  頂点バッファのセット
			pD3DDevice->SetStreamSource( 0 , g_aShadow[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// テクスチャのセット
			pD3DDevice->SetTexture( 0 , g_aShadow[i].pD3DTex );
	
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//-------------------------------------------------------------------------
			// プリミティブ表示
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
						0 ,								// 最初に書く頂点は何処？
						2 );							// プリミティブの数

			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
		}
	}
}

//=============================================================================
//
// 関数名 : MakeVertexShadow
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//		 影の幅
//		 影の高さ
//
// 機能 : 影の頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pD3DDevice,float fShadowWidth,float fShadowHeight)
{
	//---------------------
	// 変数宣言
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数

	int PrimitiveMax = (int)(fShadowWidth + 1) + (int)(fShadowHeight + 1);

	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		//---------------------------------------------------------------------
		// 頂点バッファ作成処理
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aShadow[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// 頂点バッファのロック
		hr = g_aShadow[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		if( FAILED( hr ) )
		{
			return (E_FAIL);
		}

		float Width = fShadowWidth * 0.5f;
		
		//-------------------------------------------------------------------------
		// 頂点バッファの
		pVtx[0].vtx = D3DXVECTOR3(-Width , 0 , -fShadowHeight);
		pVtx[1].vtx = D3DXVECTOR3(-Width , 0 , fShadowHeight);
		pVtx[2].vtx = D3DXVECTOR3(Width , 0 , -fShadowHeight);
		pVtx[3].vtx = D3DXVECTOR3(Width , 0 , fShadowHeight);

		//-------------------------------------------------------------------------
		// norの設定
		pVtx[0].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[1].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[2].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[3].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

		//---------------------------------------------------------------------
		// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
		pVtx[0].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[1].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[2].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[3].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);

		//-------------------------------------------------------------------------
		// テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2( 0.f, 1.f );					// 左上のテクスチャ頂点設定
		pVtx[1].tex = D3DXVECTOR2( 0.f, 0.f );					// 右上のテクスチャ頂点設定
		pVtx[2].tex = D3DXVECTOR2( 1.f, 1.f );					// 右下のテクスチャ頂点設定
		pVtx[3].tex = D3DXVECTOR2( 0.f, 1.f );					// 左下のテクスチャ頂点設定

		//-------------------------------------------------------------------------
		// 頂点バッファのロック解
		g_aShadow[i].pD3DVBXYZBuffer->Unlock();
	}

	// 作成成功
	return (S_OK);
}

//=============================================================================
//
// 関数名 : ShadowSet
//
// 戻り値 : なし
//
// 引数 : 位置
//		 何の影か
//
// 機能 : 影をセット
//
//=============================================================================
void ShadowSet(D3DXVECTOR3 position , int nType, int nNum)
{
	for( int i = 0; i < SHADOW_MAX; i++ )				// 影を最大数分回す
	{
		if( g_aShadow[i].visible != true )				// 影が使われていない部分
		{
			g_aShadow[i].posShadow = position;			// 影の位置をセット
			if( nType == BULLET_TYPE )
			{
				g_aShadow[i].sclShadow = D3DXVECTOR3(0.4f , 0.4f , 0.4f);
			}
			g_aShadow[i].nType = nType;
			g_aShadow[i].visible = true;				// 影が使われた
			g_aShadow[i].nNum = nNum;
			break;										// ループを脱出
		}
	}
}

//=============================================================================
//
// 関数名 : ShadowDelete
//
// 戻り値 : なし
//
// 引数 : 何の影か
//
// 機能 : 影を削除
//
//=============================================================================
void ShadowDelete(int nType , int nNum)
{
	for(int i = 0; i < SHADOW_MAX; i++)
	{
		if( g_aShadow[i].nType == nType )
		{
			if( g_aShadow[i].nNum == nNum )
			{
				g_aShadow[i].posShadow = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
				g_aShadow[i].visible = false;
				g_aShadow[i].nNum = -1;
				break;
			}
		}
	}
}