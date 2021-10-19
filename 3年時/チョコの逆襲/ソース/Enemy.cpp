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
#include "../hedder/Enemy.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIFE_MAX				(40)	// 敵のライフ最大値
#define RECUPERATING_CNT_MAX	(60)	// 回復カウント最大値
#define BULLET_ENEMY_SHOT		(40)	// 敵が弾を撃つ間隔

//=============================================================================
// グローバル変数
//=============================================================================
static	D3DXMATRIX g_mtxWorld;					// ワールド
static	D3DXVECTOR3 g_posEnemy;					// モデルの位置
static	D3DXVECTOR3 g_rotEnemy;					// モデルの向き
static	D3DXVECTOR3 g_sclEnemy;					// モデルの大きさ
static	LPDIRECT3DTEXTURE9 g_pD3DTextureEnemy = NULL;
static	LPD3DXMESH g_pMeshEnemy = NULL;			// メッシュの情報へのポインタ
static LPD3DXBUFFER g_pD3DMatBuff = NULL;		// マテリアル情報へのポインタ
static DWORD g_nNumMat;							// マテリアル情報の総数
static float g_fEnemyRotX;						// 敵の向きX座標
static float g_fEnemyRotZ;						// 敵の向きZ座標
static int g_nEnemyShot;						// 敵が弾を撃ってくる間隔
static float g_fAngleEnemy = D3DXToRadian(0); 
static int g_nEnemyLife;						// 敵のライフ
static bool g_bEnemyAlive;						// 生きているか
static int g_nLifeUpCnt;						// ライフ回復カウント

//=============================================================================
//
//	関数名	: EnemyInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: モデル初期化
//
//=============================================================================
HRESULT EnemyInit( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// モデル初期化
	g_posEnemy = D3DXVECTOR3(0.0f , 0.0f , 0.0f);		// モデルの位置
	g_rotEnemy = D3DXVECTOR3(0.0f , 0.0f , 0.0f);		// モデルの向き
	g_sclEnemy = D3DXVECTOR3(5.0f , 5.0f , 5.0f);	// モデルの大きさ
	g_nEnemyShot = 0;									// 弾の間隔
	g_nEnemyLife = LIFE_MAX;									// 敵のライフ
	g_nLifeUpCnt = 0;
	g_fAngleEnemy = D3DXToRadian(0);
	g_bEnemyAlive = true;								// 敵は生きているか

	//-------------------------------------------------------------------------
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( "DATA/Model/choco.x" , 
									D3DXMESH_SYSTEMMEM,
									pD3DDevice,
									NULL,
									&g_pD3DMatBuff,
									NULL,
									&g_nNumMat,
									&g_pMeshEnemy) ) )
	{
		return E_FAIL;
	}

	FontInit(pD3DDevice, 30, 20, 0, "Terminal", ENEMY_TYPE);

	ShadowSet(g_posEnemy , ENEMY_TYPE , ENEMY_NUM);
	
	return S_OK;
}

//=============================================================================
//
//	関数名	: EnemyUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: モデル破棄
//
//=============================================================================
void EnemyUninit( void )
{
	// もしテクスチャが解放されていなければ
	if(g_pD3DTextureEnemy!= NULL)
	{
		// テクスチャの解放
		g_pD3DTextureEnemy->Release();

		// テクスチャの部分をNULLへ
		g_pD3DTextureEnemy = NULL;
	}

	if( g_pMeshEnemy != NULL )
	{
		g_pMeshEnemy->Release();		// メッシュ開放
		g_pMeshEnemy = NULL;
	}
	
	if( g_pD3DMatBuff != NULL )
	{
		g_pD3DMatBuff->Release();		// マテリアルバッファー開放
		g_pD3DMatBuff = NULL;
	}

	FontUninit(ENEMY_TYPE);
}

//=============================================================================
//
//	関数名	: EnemyUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: モデル更新
//
//=============================================================================
void EnemyUpdate(void)
{
	D3DXVECTOR3 PlayerPos = PlayerPosGet();
	MESH_WALL *apMeshWall = MeshWallGet();
	BULLET *pBullet = BulletPosGet();
	
	float Vec_XZ = sqrt(((PlayerPos.x - g_posEnemy.x) * (PlayerPos.x - g_posEnemy.x)) + ((PlayerPos.z - g_posEnemy.z) * (PlayerPos.z - g_posEnemy.z)));	// プレイヤーの距離
	float Vec_X = (PlayerPos.x - g_posEnemy.x) / Vec_XZ;
	float Vec_Z = (PlayerPos.z - g_posEnemy.z) / Vec_XZ;
	float Thita = 0;

	if( g_bEnemyAlive == true )
	{

		if( g_posEnemy.x == PlayerPos.x && g_posEnemy.z == PlayerPos.z )
		{
			GameSelectSet(OVER);
		}
		else
		{
			float Product = (Vec_X * -cosf(g_fAngleEnemy)) + (Vec_Z * -sinf(g_fAngleEnemy));
			Thita = acos(Product);
		}

		float Cross = (Vec_Z * -sinf(g_fAngleEnemy)) - (Vec_X * -cosf(g_fAngleEnemy));
		if(Cross > 0 )
		{
			if(Thita >= D3DXToRadian(2))
			{
				g_fAngleEnemy -= D3DXToRadian(2);
			}
			else
			{
				g_fAngleEnemy -= Thita;
			}
		}
		if( Cross < 0 )
		{
			if(Thita >= D3DXToRadian(2))
			{
				g_fAngleEnemy += D3DXToRadian(2);
			}
			else
			{
				g_fAngleEnemy += Thita;
			}
		}
		g_rotEnemy.y = g_fAngleEnemy;

		g_posEnemy.x -= sin(g_rotEnemy.y);
		g_posEnemy.z -= cos(g_rotEnemy.y);

		if( g_nEnemyShot > BULLET_ENEMY_SHOT )
		{
			BulletSet( g_posEnemy , g_rotEnemy.y , ENEMY_TYPE);
			g_nEnemyShot = 0;
		}
		else
		{
			g_nEnemyShot++;
		}
		if(g_nLifeUpCnt > RECUPERATING_CNT_MAX)
		{
			if(g_nEnemyLife < LIFE_MAX)
			{
				g_nEnemyLife++;
			}
			g_nLifeUpCnt = 0;
		}
		else
		{
			g_nLifeUpCnt++;
		}
		ShadowUpdate(g_posEnemy, 30, ENEMY_TYPE);

		for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
		{
			if( pBullet[nCntBullet].visible == true )
			{
				if( pBullet[nCntBullet].nType == PLAYER_TYPE )
				{
					if( pBullet[nCntBullet].posBullet.x < (g_posEnemy.x + 20)  &&
						g_posEnemy.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
						pBullet[nCntBullet].posBullet.z < ( g_posEnemy.z + 20 ) &&
						g_posEnemy.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight))
					{
						pBullet[nCntBullet].visible = false;
						pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
						pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
						ExplosionSet( pBullet[nCntBullet].MemoryPos);
						ShadowDelete( BULLET_TYPE , nCntBullet);
						ExplosionSet(g_posEnemy);
					}
				}
			}
		}
	}
	else
	{
		GameSelectSet(CLEAR);
	}

}

//=============================================================================
//
//	関数名	: EnemyDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: モデル描画
//
//=============================================================================
void EnemyDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxScl ;			// 大きさの設定
	D3DXMATRIX mtxRot ;			// 向きの設定
	D3DXMATRIX mtxTrans;		
	D3DXMATERIAL *pD3DMat;		// マテリアル設定
	char strLife[20];			// ライフ文字型

	//-------------------------------------------------------------------------
	// ワールドマトリックス
	D3DXMatrixIdentity( &g_mtxWorld );		// ワールドマトリックス初期化

	//*********************************
	// スケール反映
	D3DXMatrixScaling( &mtxScl , g_sclEnemy.x, g_sclEnemy.y , g_sclEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// 回転反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotEnemy.y , g_rotEnemy.x , g_rotEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// 移動反映
	D3DXMatrixTranslation( &mtxTrans , g_posEnemy.x , g_posEnemy.y , g_posEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ワールドマトリックス設定
	pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );	

	//-------------------------------------------------------------------------
	// モデル設定
	pD3DMat = ( D3DXMATERIAL * )g_pD3DMatBuff->GetBufferPointer();

	for( int nCntMat = 0; nCntMat < (int)g_nNumMat; nCntMat++ )
	{
		pD3DDevice->SetMaterial( &pD3DMat[nCntMat].MatD3D );
		pD3DDevice->SetTexture( 0 , g_pD3DTextureEnemy );
		g_pMeshEnemy->DrawSubset( nCntMat );
	}
	
	char g_strLifeBuffe[1024] = "敵のライフ : ";		// 敵のライフの文字列
	itoa(g_nEnemyLife, strLife , 10);
	
	strcat( g_strLifeBuffe , strLife );
	FontDraw(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, 255, 255, 255, g_strLifeBuffe, ENEMY_TYPE);
	
}

//=============================================================================
//
//	関数名	: EnemyPosGet
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: モデル位置取得
//
//=============================================================================
D3DXVECTOR3 EnemyPosGet( void )
{
	return g_posEnemy;
}

void EnemyLifeSet(int nLife)
{	
	g_nEnemyLife -= nLife;
	if( g_nEnemyLife < 1 )
	{
		GameSelectSet(CLEAR);
	}
}


int EnemyLifeGet(void)
{
	return g_nEnemyLife;
}