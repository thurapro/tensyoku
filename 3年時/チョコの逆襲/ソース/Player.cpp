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
#include "../hedder/Player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LIFE_MAX (10)
#define VISIBLECNT_MAX	(20)

//=============================================================================
// グローバル変数
//=============================================================================
static	D3DXMATRIX g_mtxWorld;						// ワールド
static	D3DXVECTOR3 g_posPlayer;					// プレイヤーの位置
static	D3DXVECTOR3 g_rotPlayer;					// プレイヤーの向き
static	D3DXVECTOR3 g_sclPlayer;					// プレイヤーの大きさ
static	D3DXVECTOR3 g_rotArrow;						// 向いていなければならない位置
static	D3DXVECTOR3 g_movePlayer;					// プレイヤーの動く速度
static	LPDIRECT3DTEXTURE9 g_pD3DTexturePlayer = NULL; 
static	LPD3DXMESH g_pMeshPlayer = NULL;			// メッシュの情報へのポインタ
static	LPD3DXBUFFER g_pD3DMatBuff = NULL;			// マテリアル情報へのポインタ
static	DWORD g_nNumMat;							// マテリアル情報の総数
static	float g_rotMove = D3DX_PI / 180;			// 向きを変える速度
static	float g_fPlayerX = 0;						// プレイヤーの現在の向きX
static	float g_fPlayerZ = 0;						// プレイヤーの現在の向きZ
static bool g_bVisible = true;						// プレイヤーを表示するか？ 
static int g_nPlayerLife;							// プレイヤーの体力
static int g_nVisibleCount = 0;						// プレイヤーを消した後にまた表示するための時間
static LPDIRECTSOUNDBUFFER g_soundStart;			// サウンド

//=============================================================================
//
//	関数名	: PlayerInit
//	
//	戻り値	: 初期化できたか結果
//
//	引数	: デバイス
//
//	機能	: プレイヤー初期化
//
//=============================================================================
HRESULT PlayerInit( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// プレイヤー初期化
	g_posPlayer = D3DXVECTOR3(0.0f, 0.0f, -300.0f);			// プレイヤーの位置
	g_rotPlayer = D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f);	// プレイヤーの向き
	g_sclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// プレイヤーの大きさ
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// プレイヤーの速度
	g_rotMove = D3DX_PI / 180;								// プレイヤーの向く速さ
	g_rotArrow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 次に向くベクトル	
	g_fPlayerX = 0;											// プレイヤーの現在の向き向き
	g_fPlayerZ = 0;											// プレイヤーの現在の向き
	g_nPlayerLife = PLAYER_LIFE_MAX;						// プレイヤーの体力
	g_soundStart;											// サウンド
	g_nVisibleCount = 0;									// プレイヤーを表示するための時間
	g_bVisible = true;										// プレイヤーを表示するかを決める true/表示, false/非表示 

	//-------------------------------------------------------------------------
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( "DATA/Model/tank.x" , 
									D3DXMESH_SYSTEMMEM,
									pD3DDevice,
									NULL,
									&g_pD3DMatBuff,
									NULL,
									&g_nNumMat,
									&g_pMeshPlayer) ) )
	{
		return E_FAIL;
	}
	
	//--------------------------------------------------
	// 音楽ファイルロード　& 生成
	SoundFileLoad("DATA/Sound/Start.wav", PLAYER_STOP);
	CreateSoundBuffer( &g_soundStart, PLAYER_STOP);

	FontInit(pD3DDevice, 20, 20, 0, "Terminal", PLAYER_TYPE);


	//---------------------------------------------------
	// 影をセット
	ShadowSet(g_posPlayer, PLAYER_TYPE , 0);

	return S_OK;
}

//=============================================================================
//
//	関数名	: PlayerUninit
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: プレイヤー破棄
//
//=============================================================================
void PlayerUninit( void )
{
	
	if(g_pD3DTexturePlayer!= NULL)
	{
		// もしテクスチャが解放されていなければ
		g_pD3DTexturePlayer->Release();		// テクスチャの解放
		g_pD3DTexturePlayer = NULL;			// 開放されたメモリへNULLを入れる
	}

	if( g_pMeshPlayer != NULL )
	{
		// メッシュが開放されていなければ
		g_pMeshPlayer->Release();			// メッシュ開放
		g_pMeshPlayer = NULL;				// 開放されたメモリへNULLを入れる
	}
	
	if( g_pD3DMatBuff != NULL )
	{
		// マテリアルバッファーが開放されていなければ
		g_pD3DMatBuff->Release();			// マテリアルバッファー開放
		g_pD3DMatBuff = NULL;				// 開放されたメモリへNULLを入れる
	}
	if(g_soundStart != NULL)
	{
		// サウンドが開放されていなければ
		g_soundStart->Release();			// サウンドを開放
		g_soundStart = NULL;				// 開放されたメモリへNULLを入れる
	}

	FontUninit(PLAYER_TYPE);
}

//=============================================================================
//
//	関数名	: PlayerUpdate
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: プレイヤー更新
//
//=============================================================================
void PlayerUpdate(void)
{
	
	MESH_WALL *aMeshWall = MeshWallGet();				// 壁の位置を取得
	BULLET *pBullet = BulletPosGet();					// 弾を取得
	bool bStop = GameStop();							// ポーズボタンが押されたか取得
	PlayerStop(bStop);									// ポーズが押されてのかをセット

	if(g_nPlayerLife >= 0)
	{
		// プレイヤーの体力がなくなっていな状態
		if(g_bVisible == false)
		{
			// プレイヤーが表示されていなければ
			if(g_nVisibleCount > VISIBLECNT_MAX)
			{
				// 表示するための時間を超えていたら
				g_bVisible = true;						// プレイヤーを表示
				g_nVisibleCount = 0;					// タイマーをリセット
			}
			else
			{
				// 表示するための時間に達していなければ
				g_nVisibleCount++;						// 表示するためにカウントを上げる
			}
		}
		else
		{
			// プレイヤーが表示されていたら
			g_fPlayerX = -sin( g_rotPlayer.y );			// プレイヤーの向いている向きをセット
			g_fPlayerZ = -cos( g_rotPlayer.y );			// プレイヤーの向いている向きをセット

			g_movePlayer.x = 4 * sin( g_rotPlayer.y );	// プレイヤーの移動速度
			g_movePlayer.z = 4 * cos( g_rotPlayer.y );	// プレイヤーの移動速度

			//---------------------------------
			// 右移動
			if( KeyState( DIK_D ) )
			{
				g_rotArrow.x = D3DX_PI * 0.5f;
				g_rotArrow.x = sinf(g_rotArrow.x);
				g_rotArrow.z = 0.0f;

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				if( Cross > 0 )
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.x + 13 < aMeshWall[1].pos.x)
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}
			//---------------------------------
			// 左移動
			else if( KeyState( DIK_A ) )
			{
				g_rotArrow.x = -D3DX_PI * 0.5f;
				g_rotArrow.x = sinf(g_rotArrow.x);
				g_rotArrow.z = 0.0f;
				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}
				float Cross = (g_rotArrow.z * g_fPlayerX) - ( g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				if( Cross > 0 )
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.x - 13 > aMeshWall[2].pos.x )
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z += g_movePlayer.z;
				}
			}
			//---------------------------------
			// 奥移動
			else if( KeyState( DIK_W ) )
			{
				g_rotArrow.x = 0.0f;
				g_rotArrow.z = 0.0f;
				g_rotArrow.z = cosf(g_rotArrow.z);

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				else if( Cross > 0)
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.z + 13 < aMeshWall[0].pos.z)
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}

			//---------------------------------
			// 手前移動
			else if( KeyState( DIK_S ) )
			{	
				g_rotArrow.x = 0;
				g_rotArrow.z = D3DX_PI * 1.0f;
				g_rotArrow.z = cosf(g_rotArrow.z);

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				else if( Cross > 0)
				{
					g_rotPlayer.y -= Thita;
				}
				
				if( g_posPlayer.z - 13 > aMeshWall[3].pos.z )
				{
					g_posPlayer.x += g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}

			//---------------------------------
			// 弾発射
			if( KeyPush( DIK_SPACE ) )
			{
				BulletSet( g_posPlayer, g_rotPlayer.y , PLAYER_TYPE);
			}

			ShadowUpdate(g_posPlayer, 0 , PLAYER_TYPE);
			
			for( int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
			{
				if(pBullet[nCntBullet].visible == true )
				{
					if( pBullet[nCntBullet].nType != PLAYER_TYPE )
					{
						if( pBullet[nCntBullet].posBullet.x < (g_posPlayer.x + 20)&&
							g_posPlayer.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
							pBullet[nCntBullet].posBullet.z < (g_posPlayer.z + 20)&&
							g_posPlayer.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight))
						{
							pBullet[nCntBullet].visible = false;
							pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
							pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
							ExplosionSet( pBullet[nCntBullet].MemoryPos);
							ShadowDelete( BULLET_TYPE , nCntBullet);
							g_bVisible = false;			// プレイヤーを非表示にする
							//g_nPlayerLife--;			// 体力をへらす
						}// 弾が当たっているかのifを抜ける 
					}// 弾が自分の弾かのifを抜ける
				}// 弾が表示されているかのifを抜ける
			}// 弾の判定のforを抜ける
		}// プレイヤーが表示されているかのifを抜ける
	}
	else
	{
		// もし体力がなければ
		GameSelectSet(OVER);		// ゲームオーバーに移動
	}
}

//=============================================================================
//
//	関数名	: PlayerDraw
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: プレイヤー描画
//
//=============================================================================
void PlayerDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// 変数宣言
	D3DXMATRIX mtxScl ;			// 大きさの設定
	D3DXMATRIX mtxRot ;			// 向きの設定
	D3DXMATRIX mtxTrans;		
	D3DXMATERIAL *pD3DMat;		// マテリアル設定
	char strPlayer[1024] = "プレイヤーのライフ : ";
	char strLife[10];
	char srtStopMsg[50] = "STOP";
	bool bStop = GameStop();

	if(g_bVisible == true)
	{
		//-------------------------------------------------------------------------
		// ワールドマトリックス
		D3DXMatrixIdentity( &g_mtxWorld );		// ワールドマトリックス初期化

		//*********************************
		// スケール反映
		D3DXMatrixScaling( &mtxScl , g_sclPlayer.x, g_sclPlayer.y , g_sclPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
		
		//*********************************
		// 回転反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotPlayer.y , g_rotPlayer.x , g_rotPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

		//*********************************
		// 移動反映
		D3DXMatrixTranslation( &mtxTrans , g_posPlayer.x , g_posPlayer.y , g_posPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

		//-------------------------------------------------------------------------
		// ワールドマトリックス設定
		pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );	

		//-------------------------------------------------------------------------
		// プレイヤー設定
		pD3DMat = ( D3DXMATERIAL * )g_pD3DMatBuff->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < (int)g_nNumMat; nCntMat++ )
		{
			pD3DDevice->SetMaterial( &pD3DMat[nCntMat].MatD3D );
			pD3DDevice->SetTexture( 0 , g_pD3DTexturePlayer );
			g_pMeshPlayer->DrawSubset( nCntMat );
		}
	}
		
	itoa( g_nPlayerLife, strLife, 10);
	strcat(strPlayer , strLife);
	FontDraw(20 , 300, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 255, 255, 255, strPlayer, PLAYER_TYPE);
	
	/*if( bStop == true )
	{
		FontDraw(280 , 190, SCREEN_WIDTH, SCREEN_HEIGHT, srtStopMsg);
	}*/
}

//=============================================================================
//
//	関数名	: PlayerPosGet
//	
//	戻り値	: プレイヤーの位置
//
//	引数	: なし
//
//	機能	: プレイヤー位置取得
//
//=============================================================================
D3DXVECTOR3 PlayerPosGet( void )
{
	return g_posPlayer;
}

//=============================================================================
//
//	関数名	: PlayerRosGet
//	
//	戻り値	: プレイヤーの向き
//
//	引数	: なし
//
//	機能	: プレイヤー向き取得
//
//=============================================================================
D3DXVECTOR3 PlayerRotGet(void)
{
	return g_rotPlayer;
}

bool PlayerStop(bool bStop)
{
	if( KeyPush(DIK_RETURN))
	{
		g_soundStart->Play(0,0,0);
		if( bStop == false )
		{
			bStop = true;
		}
		else
		{
			bStop = false;
		}
	}
	return bStop;
}

