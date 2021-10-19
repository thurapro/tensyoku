//=============================================================================
//
// 敵の本元処理 [EnemyLife.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/EnemyLife.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SPEED_X			(3)
#define SPEED_Z			(3)
#define TEX_SPEED_X		(0.25f)
#define TEX_MAX			(1.0f)
#define ANIMECNT_MAX	(30)
#define TEX_INIT		(0.25f)
#define TYPE_LIFE		(4)
#define DAMAGE			(3)

//=============================================================================
// グローバル変数
//=============================================================================
static D3DXMATRIX mtxWorld;						// ワールド
static D3DXVECTOR3 g_posEnemyLife;				// 敵の本元の位置
static D3DXVECTOR3 g_rotEnemyLife;				// 敵の本元の向き
static D3DXVECTOR3 g_sclEnemyLife;				// 敵の本元の大きさ
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZの頂点バッファ
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// テクスチャ
static float g_fmoveX;
static float g_fmoveZ;
static float g_fLeftTop;
static float g_fRightTop;
static float g_fLeftBottom;
static float g_fRightBottom;
static int nAnimeCnt;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexEnemyLife( LPDIRECT3DDEVICE9 pD3DDevice, float fWidth, float fHeight);

//=============================================================================
//
//	関数名	: EnemyLifeInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: 敵の本元初期化
//
//=============================================================================
HRESULT EnemyLifeInit(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//-------------------------------------------------------------------------
	// 敵の本元初期化
	g_posEnemyLife = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 敵の本元の位置
	g_rotEnemyLife = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// 敵の本元の向き
	g_sclEnemyLife = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// 敵の本元の大きさ

	g_fmoveX = SPEED_X;
	g_fmoveZ = SPEED_Z;

	g_fLeftTop = 0.0f;
	g_fRightTop = TEX_INIT;
	g_fLeftBottom = 0.0f;
	g_fRightBottom = TEX_INIT;
	nAnimeCnt = 0;


	////-------------------------------------------------------------------------
	// テクスチャのロード
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/hart.png" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// 頂点情報作成
	if( FAILED( MakeVertexEnemyLife(pD3DDevice, 20, 30) ) )
	{
		return E_FAIL;
	}
	
	ShadowSet(g_posEnemyLife, TYPE_LIFE, 60);

	return S_OK;
}

//=============================================================================
//
//	関数名	: EnemyLifeUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 敵の本元破棄
//
//=============================================================================
void EnemyLifeUninit(void)
{
	for( int i = 0; i < BULLET_MAX; i++ )
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
	
}

//=============================================================================
//
//	関数名	: EnemyLifeUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 敵の本元更新
//
//=============================================================================
void EnemyLifeUpdate( void )
{
	//----------------
	// 変数宣言
	VERTEX_3D *pVtx;	// 頂点数

	BULLET *pBullet = BulletPosGet();
	int nLife = EnemyLifeGet();

	if( nLife > 1 )
	{
		// 頂点バッファーロック
		g_pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		pVtx[0].tex = D3DXVECTOR2( g_fLeftTop , 0.0f);			// 左上のテクスチャ頂点設定
		pVtx[1].tex = D3DXVECTOR2( g_fRightTop, 0.0f);			// 右上のテクスチャ頂点設定
		pVtx[2].tex = D3DXVECTOR2( g_fLeftBottom, 1.0f);			// 右下のテクスチャ頂点設定
		pVtx[3].tex = D3DXVECTOR2( g_fRightBottom, 1.0f);			// 左下のテクスチャ頂点設定
		
		g_pD3DVBXYZBuffer->Unlock();
		
		if( nAnimeCnt > ANIMECNT_MAX)
		{
			if( g_fLeftBottom < TEX_MAX )
			{
				g_fLeftTop += TEX_SPEED_X;
				g_fRightTop += TEX_SPEED_X;
				g_fLeftBottom += TEX_SPEED_X;
				g_fRightBottom += TEX_SPEED_X;
			}
			else
			{
				g_fLeftTop = 0.0f;
				g_fRightTop = TEX_INIT;
				g_fLeftBottom = 0.0f;
				g_fRightBottom = TEX_INIT;
			}
			nAnimeCnt = 0;
		}
		else
		{
			nAnimeCnt++;
		}
		for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
		{
			if( pBullet[nCntBullet].visible == true )
			{
				if( pBullet[nCntBullet].nType == PLAYER_TYPE )
				{
					if( g_posEnemyLife.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
						pBullet[nCntBullet].posBullet.x < ( g_posEnemyLife.x + 20 ) &&
						g_posEnemyLife.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight) &&
						pBullet[nCntBullet].posBullet.z < g_posEnemyLife.z + 30)
					{
						pBullet[nCntBullet].visible = false;
						pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
						pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
						ExplosionSet( pBullet[nCntBullet].MemoryPos);
						ShadowDelete( BULLET_TYPE , nCntBullet);
						EnemyLifeSet( DAMAGE );
					}
				}
			}
		}
	}
	else
	{
		g_sclEnemyLife= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionSet(g_posEnemyLife);
	}
}

//=============================================================================
//
//	関数名	: EnemyLifeDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: 敵の本元描画
//
//=============================================================================
void EnemyLifeDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ワールドマトリックス
	D3DXMatrixIdentity( &mtxWorld );		// ワールドマトリックス初期化

	D3DXMatrixInverse( &mtxWorld , NULL , &mtxView );
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//*********************************
	// スケール反映
	D3DXMatrixScaling( &mtxScl , g_sclEnemyLife.x , g_sclEnemyLife.y , g_sclEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );
	
	//*********************************
	// 回転反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotEnemyLife.y , g_rotEnemyLife.x , g_rotEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxRot );

	//*********************************
	// 移動反映
	D3DXMatrixTranslation( &mtxTrans , g_posEnemyLife.x , g_posEnemyLife.y , g_posEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ワールドマトリックス設定
	pD3DDevice->SetTransform( D3DTS_WORLD , &mtxWorld );

	//-------------------------------------------------------------------------
	// 頂点情報設定
	pD3DDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

	//-------------------------------------------------------------------------
	//  頂点バッファのセット
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

	//-------------------------------------------------------------------------
	// テクスチャのセット
	pD3DDevice->SetTexture( 0 , g_pD3DTex );

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

//=============================================================================
//
// 関数名 : MakeVertexEnemyLife
//
// 戻り値 : HRESULT
//
// 引数 : デバイス 
//
// 機能 : 頂点バッファ作成
//
//=============================================================================
HRESULT MakeVertexEnemyLife( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight)
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
	pVtx[1].tex = D3DXVECTOR2( 0.25f, 0.0f);			// 右上のテクスチャ頂点設定
	pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);			// 右下のテクスチャ頂点設定
	pVtx[3].tex = D3DXVECTOR2( 0.25f, 1.0f);			// 左下のテクスチャ頂点設定
	
	//-------------------------------------------------------------------------
	// 頂点バッファのロック解
	g_pD3DVBXYZBuffer->Unlock();

	// 作成成功
	return (S_OK);
}

