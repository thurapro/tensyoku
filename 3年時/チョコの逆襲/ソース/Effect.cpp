//=============================================================================
//
// フィールド処理 [Effect.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Effect.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define EFFECT_MAX		( 200 )				// エフェクトの初期化

//=============================================================================
// グローバル変数
//=============================================================================
static EFFECT g_aEffect[EFFECT_MAX];

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pD3DDevice,float fEffectWidth,float fEffectHeight);

//=============================================================================
//
//	関数名	: EffectInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: エフェクト初期化
//
//=============================================================================
HRESULT EffectInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fEffectWidth,float fEffectHeight)
{
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		//-------------------------------------------------------------------------
		// エフェクト初の期化
		g_aEffect[i].posEffect = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// エフェクトの位置
		g_aEffect[i].rotEffect = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// エフェクトの向き
		g_aEffect[i].sclEffect = D3DXVECTOR3( 0.4f , 0.4f , 0.4f );		// エフェクトの大きさ
		g_aEffect[i].nAlpha = ALPHA_MAX;
		g_aEffect[i].visible = false;									// 表示されているか

		//-------------------------------------------------------------------------
		// テクスチャのロード
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/effect000.jpg" , &g_aEffect[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexEffect(pD3DDevice , fEffectWidth , fEffectHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: EffectUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド破棄
//
//=============================================================================
void EffectUninit( void )
{
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		// もしテクスチャが解放されていなければ
		if(g_aEffect[i].pD3DTex != NULL)
		{
			// テクスチャの解放
			g_aEffect[i].pD3DTex->Release();

			// テクスチャの部分をNULLへ
			g_aEffect[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// 頂点バッファの解放
		if( g_aEffect[i].pD3DVBXYZBuffer != NULL )
		{
			g_aEffect[i].pD3DVBXYZBuffer->Release();
			g_aEffect[i].pD3DVBXYZBuffer = NULL; 
		}
	}

}

//=============================================================================
//
//	関数名	: EffectUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド更新
//
//=============================================================================
void EffectUpdate(void)
{
	VERTEX_3D *pVtx;	// 頂点数
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		if( g_aEffect[i].visible == true )
		{
			if(g_aEffect[i].nAlpha > 0 )
			{
				if( g_aEffect[i].nType == 0 )
				{
					g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
					pVtx[0].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[1].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[2].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[3].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					g_aEffect[i].pD3DVBXYZBuffer->Unlock();
					g_aEffect[i].nAlpha -= 50; 
				}
				else
				{
					g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
					pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					g_aEffect[i].pD3DVBXYZBuffer->Unlock();
					g_aEffect[i].nAlpha -= 50; 
				}
			}
			else
			{
				g_aEffect[i].nAlpha = ALPHA_MAX;
				g_aEffect[i].visible = false;
			}
		}
	}
}

//=============================================================================
//
//	関数名	: EffectDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: フィールド描画
//
//=============================================================================
void EffectDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < EFFECT_MAX; i++ )
	{	
		if( g_aEffect[i].visible == true )
		{
			//-----------------------------------
			// ワールドマトリックス
			D3DXMatrixIdentity( &g_aEffect[i].mtxWorld );		// ワールドマトリックス初期化

			D3DXMatrixInverse( &g_aEffect[i].mtxWorld , NULL , &mtxView );
			g_aEffect[i].mtxWorld._41 = 0.0f;
			g_aEffect[i].mtxWorld._42 = 0.0f;
			g_aEffect[i].mtxWorld._43 = 0.0f;

			//*********************************
			// スケール反映
			D3DXMatrixScaling( &mtxScl , g_aEffect[i].sclEffect.x , g_aEffect[i].sclEffect.y , g_aEffect[i].sclEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxScl );
			
			//*********************************
			// 回転反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aEffect[i].rotEffect.y , g_aEffect[i].rotEffect.x , g_aEffect[i].rotEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxRot );

			//*********************************
			// 移動反映
			D3DXMatrixTranslation( &mtxTrans , g_aEffect[i].posEffect.x , g_aEffect[i].posEffect.y , g_aEffect[i].posEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ワールドマトリックス設定
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aEffect[i].mtxWorld );	

			//-------------------------------------------------------------------------
			// 頂点情報設定
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

			//-------------------------------------------------------------------------
			//  頂点バッファのセット
			pD3DDevice->SetStreamSource( 0 , g_aEffect[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// テクスチャのセット
			pD3DDevice->SetTexture( 0 , g_aEffect[i].pD3DTex );
			

			//-------------------------------------------------------------------------
			// レンダーステート
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

			//-------------------------------------------------------------------------
			// プリミティブ表示
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
						0 ,								// 最初に書く頂点は何処？
						2 );							// プリミティブの数

			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
	}
}

//=============================================================================
//
// 関数名 : MakeVertexEffect
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pD3DDevice,float fEffectWidth,float fEffectHeight)
{
	//---------------------
	// 変数宣言
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数

	int PrimitiveMax = (int)(fEffectWidth + 1) + (int)(fEffectHeight + 1);

	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		//---------------------------------------------------------------------
		// 頂点バッファ作成処理
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aEffect[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// 頂点バッファのロック
		hr = g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		if( FAILED( hr ) )
		{
			return (E_FAIL);
		}

		//float Width = fEffectWidth * 0.5f;
		
		//-------------------------------------------------------------------------
		// 頂点バッファの
		pVtx[0].vtx = D3DXVECTOR3(-fEffectWidth , fEffectHeight , 0);
		pVtx[1].vtx = D3DXVECTOR3(fEffectWidth , fEffectHeight, 0);
		pVtx[2].vtx = D3DXVECTOR3(-fEffectWidth , -fEffectHeight , 0);
		pVtx[3].vtx = D3DXVECTOR3(fEffectWidth , -fEffectHeight , 0);

		//-------------------------------------------------------------------------
		// norの設定
		pVtx[0].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[1].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[2].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[3].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

		//---------------------------------------------------------------------
		// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
		pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
													BLUE_MAX , ALPHA_MAX );
		pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
													 BLUE_MAX , ALPHA_MAX );
		pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX ,
														BLUE_MAX , ALPHA_MAX );
		pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX ,
														BLUE_MAX , ALPHA_MAX );

		//-------------------------------------------------------------------------
		// テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2( 0.f, 1.f );					// 左上のテクスチャ頂点設定
		pVtx[1].tex = D3DXVECTOR2( 0.f, 0.f );					// 右上のテクスチャ頂点設定
		pVtx[2].tex = D3DXVECTOR2( 1.f, 1.f );					// 右下のテクスチャ頂点設定
		pVtx[3].tex = D3DXVECTOR2( 0.f, 1.f );					// 左下のテクスチャ頂点設定

		//-------------------------------------------------------------------------
		// 頂点バッファのロック解
		g_aEffect[i].pD3DVBXYZBuffer->Unlock();
	}

	
	// 作成成功
	return (S_OK);
}

void EffectSet( D3DXVECTOR3 position , int nType )
{
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		if( g_aEffect[i].visible != true )
		{
			g_aEffect[i].posEffect = position;
			g_aEffect[i].nType = nType;
			g_aEffect[i].visible = true;
			break;
		}
	}
}


