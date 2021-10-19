//=============================================================================
//
// 爆発処理 [Explosion.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_MAX (40)							// 爆発の数

//=============================================================================
// グローバル変数
//=============================================================================
static EXPLOSION g_aExplosion[EXPLOSION_MAX];		// 爆発の構造体
static D3DXVECTOR3 CameraRotSet;					// カメラのセット
static int g_nAnimetionTimer;						// 爆発の待ち時間

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight);

//=============================================================================
//
//	関数名	: ExplosionInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: 爆発初期化
//
//=============================================================================
HRESULT ExplosionInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight )
{
	for( int i = 0;	i < EXPLOSION_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// 爆発初期化
		g_aExplosion[i].posExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 爆発の位置
		g_aExplosion[i].rotExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 爆発の向き
		g_aExplosion[i].sclExplosion = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// 爆発の大きさ
		g_aExplosion[i].visible = false;										// 爆発が表示されているか
		g_aExplosion[i].fAnimesionLeft = 0.0f;									// アニメーション(テクスチャー座標X)
		g_aExplosion[i].fAnimesionRight = 0.1f;

		////-------------------------------------------------------------------------
		// テクスチャのロード
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/Explosion.png" , &g_aExplosion[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
		SoundFileLoad("DATA/Sound/Explosion.wav", EXPLOSION_END );
		CreateSoundBuffer(&g_aExplosion[i].soundExplosion, EXPLOSION_END);
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexExplosion(pD3DDevice , fPolygonWidth , fPolygonHeight) ) )
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
//
//	関数名	: ExplosionUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 爆発破棄
//
//=============================================================================
void ExplosionUninit( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		// もしテクスチャが解放されていなければ
		if(g_aExplosion[i].pD3DTex != NULL)
		{
			// テクスチャの解放
			g_aExplosion[i].pD3DTex->Release();

			// テクスチャの部分をNULLへ
			g_aExplosion[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// 頂点バッファの解放
		if( g_aExplosion[i].pD3DVBXYZBuffer != NULL )
		{
			g_aExplosion[i].pD3DVBXYZBuffer->Release();
			g_aExplosion[i].pD3DVBXYZBuffer = NULL; 
		}

		if(g_aExplosion[i].soundExplosion != NULL)
		{
			g_aExplosion[i].soundExplosion->Release();
			g_aExplosion[i].soundExplosion = NULL;
		}
	}
	
}

//=============================================================================
//
//	関数名	: ExplosionUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 爆発更新
//
//=============================================================================
void ExplosionUpdate( void )
{
	CameraRotSet = CameraRotGet();
	VERTEX_3D *pVtx;	// 頂点数
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == true )
		{
			if( g_nAnimetionTimer > 0 )
			{
				if( g_aExplosion[i].fAnimesionRight < 1.0f )
				{
					g_aExplosion[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0 );			// 頂点バッファロック
					g_aExplosion[i].fAnimesionLeft += 0.1f;
					g_aExplosion[i].fAnimesionRight += 0.1f;
					pVtx[0].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionLeft , 0.0f );				// テクスチャ座標更新(アニメーション)
					pVtx[1].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionRight , 0.0f );			// テクスチャ座標更新( アニメーション)
					pVtx[2].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionLeft , 1.0f );				// テクスチャ座標更新( アニメーション)
					pVtx[3].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionRight , 1.0f );			// テクスチャ座標更新( アニメーション)
					g_nAnimetionTimer = 0;
				}
				else
				{
					g_aExplosion[i].fAnimesionRight = 0.1f;
					g_aExplosion[i].fAnimesionLeft = 0;
					g_aExplosion[i].visible = false;
					g_aExplosion[i].soundExplosion->Stop();
				}
			}
			else
			{
				g_nAnimetionTimer++;
			}
			
		}
	}
}

//=============================================================================
//
//	関数名	: ExplosionDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 爆発描画
//
//=============================================================================
void ExplosionDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ワールドマトリックス
			D3DXMatrixIdentity( &g_aExplosion[i].mtxWorld );		// ワールドマトリックス初期化

			D3DXMatrixInverse( &g_aExplosion[i].mtxWorld , NULL , &mtxView );
			g_aExplosion[i].mtxWorld._41 = 0.0f;
			g_aExplosion[i].mtxWorld._42 = 0.0f;
			g_aExplosion[i].mtxWorld._43 = 0.0f;

			//*********************************
			// スケール反映
			D3DXMatrixScaling( &mtxScl , g_aExplosion[i].sclExplosion.x , g_aExplosion[i].sclExplosion.y , g_aExplosion[i].sclExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxScl );
			
			//*********************************
			// 回転反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aExplosion[i].rotExplosion.y , g_aExplosion[i].rotExplosion.x , g_aExplosion[i].rotExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxRot );

			//*********************************
			// 移動反映
			D3DXMatrixTranslation( &mtxTrans , g_aExplosion[i].posExplosion.x , g_aExplosion[i].posExplosion.y , g_aExplosion[i].posExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ワールドマトリックス設定
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aExplosion[i].mtxWorld );

			//-------------------------------------------------------------------------
			// 頂点情報設定
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

			//-------------------------------------------------------------------------
			//  頂点バッファのセット
			pD3DDevice->SetStreamSource( 0 , g_aExplosion[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// テクスチャのセット
			pD3DDevice->SetTexture( 0 , g_aExplosion[i].pD3DTex );

			
			pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
			pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
			pD3DDevice->SetRenderState( D3DRS_ALPHAREF , 253 );
			pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );

			//-------------------------------------------------------------------------
			// プリミティブ表示
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// プリミティブの種類
						0 ,								// 三角形の数
						2 );							// プリミティブの数
			pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
			pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
		}
	}
}

//=============================================================================
//
// 関数名 : MakeVertexExplosion
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight )
{
	
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		//---------------------
		// 変数宣言
		HRESULT hr;			// 結果変数
		VERTEX_3D *pVtx;	// 頂点数

		//---------------------------------------------------------------------
		// 頂点バッファ作成処理
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4 ,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aExplosion[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// 頂点バッファのロック
		hr = g_aExplosion[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		//-------------------------------------------------------------------------
		// 頂点バッファの座標設
		pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0);
		pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0);
		pVtx[2].vtx = D3DXVECTOR3(-fWidth, 0, 0);
		pVtx[3].vtx = D3DXVECTOR3(fWidth, 0, 0);

		//-------------------------------------------------------------------------
		// norの設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		//---------------------------------------------------------------------
		// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
		pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );

		//-------------------------------------------------------------------------
		// テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2( 0.0f, 0.0f);			// 左上のテクスチャ頂点設定
		pVtx[1].tex = D3DXVECTOR2( 1.0f, 0.0f);			// 右上のテクスチャ頂点設定
		pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);			// 右下のテクスチャ頂点設定
		pVtx[3].tex = D3DXVECTOR2( 1.f, 1.0f);			// 左下のテクスチャ頂点設定

		//-------------------------------------------------------------------------
		// 頂点バッファのロック解
		g_aExplosion[i].pD3DVBXYZBuffer->Unlock();
	}
	
	
	// 作成成功
	return (S_OK);
}

//=============================================================================
// ビルボード位置取得
//=============================================================================
void ExplosionSet(D3DXVECTOR3 position)
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == false )
		{
			g_aExplosion[i].posExplosion = position;
			g_aExplosion[i].posExplosion.y -= 10.f;
			g_aExplosion[i].visible = true;
			g_aExplosion[i].soundExplosion->Play(0,0,0);
			break;
		}
	}
}