//=============================================================================
//
// 弾処理 [Bullet.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Bullet.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
static BULLET g_aBullet[BULLET_MAX];				// 弾の構造体
static D3DXVECTOR3 CameraRotSet;					// カメラのセット

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexBullet( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight);

//=============================================================================
//
//	関数名	: BulletInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: 弾初期化
//
//=============================================================================
HRESULT BulletInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight)
{
	for( int i = 0;	i < BULLET_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// 弾初期化
		g_aBullet[i].posBullet = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 弾の位置
		g_aBullet[i].rotBullet = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 弾の向き
		g_aBullet[i].sclBullet = D3DXVECTOR3( 0.2f , 0.2f , 0.2f );		// 弾の大きさ
		g_aBullet[i].visible = false;									// 弾が表示されているか
		
		g_aBullet[i].fWidth = fPolygonWidth;
		g_aBullet[i].fHeight = fPolygonHeight;

		////-------------------------------------------------------------------------
		// テクスチャのロード
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/bullet000.png" , &g_aBullet[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
		SoundFileLoad("DATA/Sound/Shot.wav" , BULLET_SHOT);
		CreateSoundBuffer(&g_aBullet[i].soundBullet, BULLET_SHOT);
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexBullet(pD3DDevice , fPolygonWidth , fPolygonHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	関数名	: BulletUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 弾破棄
//
//=============================================================================
void BulletUninit(void)
{
	for( int i = 0; i < BULLET_MAX; i++ )
	{
		// もしテクスチャが解放されていなければ
		if(g_aBullet[i].pD3DTex != NULL)
		{
			// テクスチャの解放
			g_aBullet[i].pD3DTex->Release();

			// テクスチャの部分をNULLへ
			g_aBullet[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// 頂点バッファの解放
		if( g_aBullet[i].pD3DVBXYZBuffer != NULL )
		{
			g_aBullet[i].pD3DVBXYZBuffer->Release();
			g_aBullet[i].pD3DVBXYZBuffer = NULL; 
		}
		if(g_aBullet[i].soundBullet != NULL)
		{
			g_aBullet[i].soundBullet->Release();
			g_aBullet[i].soundBullet = NULL;
		}
	}
}

//=============================================================================
//
//	関数名	: BulletUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 弾更新
//
//=============================================================================
void BulletUpdate( void )
{
	MESH_WALL *aMeshWall = MeshWallGet();
	for( int i = 0; i < BULLET_MAX; i++ )
	{
		if( g_aBullet[i].visible == true )
		{
			g_aBullet[i].MemoryPos = g_aBullet[i].posBullet;
			g_aBullet[i].fMoveX = 8 * sin(g_aBullet[i].frotMove);
			g_aBullet[i].fMoveZ = 8 * cos(g_aBullet[i].frotMove);
			g_aBullet[i].posBullet.x -= g_aBullet[i].fMoveX;
			g_aBullet[i].posBullet.z -= g_aBullet[i].fMoveZ;
			EffectSet( g_aBullet[i].posBullet , g_aBullet[i].nType );
			g_aBullet[i].soundBullet->Play(0,0,0);
			ShadowUpdate(g_aBullet[i].posBullet , i, BULLET_TYPE);
			if( g_aBullet[i].posBullet.x <= aMeshWall[2].pos.x + 15|| 
				g_aBullet[i].posBullet.x > aMeshWall[1].pos.x - 15||
				g_aBullet[i].posBullet.z >= aMeshWall[0].pos.z - 15 ||
				g_aBullet[i].posBullet.z < aMeshWall[3].pos.z + 15)
			{
				ExplosionSet(g_aBullet[i].MemoryPos);
				g_aBullet[i].soundBullet->Stop();
				g_aBullet[i].posBullet.x = 0;
				g_aBullet[i].posBullet.z = 0;
				g_aBullet[i].visible = false;
				ShadowDelete(BULLET_TYPE , i);
			}

			
		}
	}

}

//=============================================================================
//
//	関数名	: BulletDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 弾描画
//
//=============================================================================
void BulletDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < BULLET_MAX; i++ )
	{
		if( g_aBullet[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ワールドマトリックス
			D3DXMatrixIdentity( &g_aBullet[i].mtxWorld );		// ワールドマトリックス初期化

			D3DXMatrixInverse( &g_aBullet[i].mtxWorld , NULL , &mtxView );
			g_aBullet[i].mtxWorld._41 = 0.0f;
			g_aBullet[i].mtxWorld._42 = 0.0f;
			g_aBullet[i].mtxWorld._43 = 0.0f;

			//*********************************
			// スケール反映
			D3DXMatrixScaling( &mtxScl , g_aBullet[i].sclBullet.x , g_aBullet[i].sclBullet.y , g_aBullet[i].sclBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxScl );
			
			//*********************************
			// 回転反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aBullet[i].rotBullet.y , g_aBullet[i].rotBullet.x , g_aBullet[i].rotBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxRot );

			//*********************************
			// 移動反映
			D3DXMatrixTranslation( &mtxTrans , g_aBullet[i].posBullet.x , g_aBullet[i].posBullet.y , g_aBullet[i].posBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ワールドマトリックス設定
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aBullet[i].mtxWorld );

			//-------------------------------------------------------------------------
			// 頂点情報設定
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

			//-------------------------------------------------------------------------
			//  頂点バッファのセット
			pD3DDevice->SetStreamSource( 0 , g_aBullet[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// テクスチャのセット
			pD3DDevice->SetTexture( 0 , g_aBullet[i].pD3DTex );

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
// 関数名 : MakeVertexBullet
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexBullet( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight)
{
	for( int i = 0; i < BULLET_MAX; i++ )
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
											&g_aBullet[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// 頂点バッファのロック
		hr = g_aBullet[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

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
		g_aBullet[i].pD3DVBXYZBuffer->Unlock();
	}
	// 作成成功
	return (S_OK);
}

//=============================================================================
//
// 関数名 : BulletSet
// 
// 戻り値 : なし
//
// 引数 : 位置
//		 弾の打つ方向
//
// 機能 : 弾をセット
//
//=============================================================================
void BulletSet(D3DXVECTOR3 position , float rotY , int nType)
{
	for( int i = 0; i < BULLET_MAX; i++ )						// 弾を最大数回す
	{
		if( g_aBullet[i].visible == false )						// 使っていない弾を出す
		{
			g_aBullet[i].posBullet = position;					// 弾の位置をセット
			g_aBullet[i].posBullet.y = 12.f;					// バレットを上にあげる
			g_aBullet[i].frotMove = rotY;						// 弾の進む方向をセット
			g_aBullet[i].visible = true;						// 弾を使った
			g_aBullet[i].nType = nType;
			ShadowSet(g_aBullet[i].posBullet , BULLET_TYPE , i);// 影をセット
			break;												// ループ脱出
		}
	}
}

BULLET *BulletPosGet(void)
{
	return &g_aBullet[0];
}