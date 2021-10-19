//=============================================================================
//
// FAILE NAME [Enemy.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: プレイヤーの設定
//
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Enemy.h"
#include "../hedder/Texture.h"
#include "../hedder/game.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Judgment.h"
#include "../hedder/Player.h"
#include "../hedder/Explosion.h"


//=============================================================================
// グローバル変数
//=============================================================================
static ENEMY g_Enemy[ENEMY_MAX];
static int g_EnemyWate = 0;
static int g_bEnemyTex[ENEMY_MAX] = {FALSE};

//=============================================================================
//
// 関数名	: EnemyInit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵の初期化
//
//=============================================================================
void EnemyInit( void )
{
	for( int i = 0; i < ENEMY_MAX; i++ )
	{

		// テクスチャーをロード
		TextureLoad("photo/sample002.png", ENEMY_NUM + i  );
		g_bEnemyTex[i] = TRUE;
		
		
		// 1頂点設定
		g_Enemy[i].fEnemyPosX = SCREEN_WIDTH;
		if( g_Enemy[0].fEnemyfWidth )
		{
			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * 0.5;
		}
		g_Enemy[i].fEnemyPosY = ENEMY_POSY;

		// 2頂点設定
		g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
		g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;

		// テクスチャの頂点1設定
		g_Enemy[i].fEnemyTexX0 = ENEMY_TEXVTEXX0;
		g_Enemy[i].fEnemyTexY0 = ENEMY_TEXVTEXY0;

		// テクスチャの頂点2設定
		g_Enemy[i].fEnemyTexX1 = ENEMY_TEXVTEXX1;
		g_Enemy[i].fEnemyTexY1 = ENEMY_TEXVTEXY1;

		// 敵の出現待ち
		g_Enemy[i].nEnemyWate = 0;
		
		// プレイヤーの角度を設定(ラジアン値)
		g_Enemy[i]. fEnemyAngle = ENEMY_ANGLE; 

		// 敵が生きているか
		g_Enemy[i].bEnemyAlive = TRUE;

		// 敵の元の座標X
		g_Enemy[i].fEnemyOldX = 0;

		// 敵の元の座標Y
		g_Enemy[i].fEnemyOldY = 0;

		// 敵は攻撃したか
		g_Enemy[i].bEnemyAttack = FALSE;

		// 敵は防御したか
		g_Enemy[i].bEnemyDefense = FALSE;
	}
}

//=============================================================================
//
// 関数名	: EnemyUpdate関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵の更新
//
//=============================================================================
void EnemyUpdate( void )
{	
	PLAYER *Player;
	Player =  PlayerGet();

	EnemyLeft();

	//for( int i = 0; i < ENEMY_MAX; i++ )
	//{
	//	if( g_Enemy[i].bEnemyAlive == TRUE )
	//	{
	//		// もし当たっていたら
	//		if( HitJudg(	Player->fPlayerPosX , Player->fPlayerPosY , 
	//						Player->fPlayerfWidth - 20 , Player->fPlayerfHeight ,
	//						g_Enemy[i].fEnemyPosX , g_Enemy[i].fEnemyPosY ,
	//						g_Enemy[i].fEnemyfWidth + 20 , g_Enemy[i].fEnemyfHeight) )
	//		{
	//			if( Player->fPlayerTexX0 != PLAYER_TEXVTEXX0 && Player->fPlayerTexX1 != PLAYER_TEXVTEXX1 )
	//			{
	//				
	//					// 敵がいた中心Xを記録(X座標)
	//					g_Enemy[i].fEnemyOldX =  g_Enemy[i].fEnemyPosX;

	//					// 敵がいた中心Yを記録(Y座標)
	//					g_Enemy[i].fEnemyOldY =  g_Enemy[i].fEnemyPosY;
	//					
	//					// 敵の元の幅
	//					g_Enemy[i].fEnemyOldWidth = g_Enemy[i].fEnemyfWidth;

	//					// 敵の元の高さ
	//					g_Enemy[i].fEnemuOldHeight = g_Enemy[i].fEnemyfHeight;

	//					// 敵をステージ上から消す
	//					g_Enemy[i].fEnemyfHeight	= 0;
	//					g_Enemy[i].fEnemyfWidth		= 0;
	//					g_Enemy[i].fEnemyPosX		= 0;
	//					g_Enemy[i].fEnemyPosY		= 0;
	//					g_Enemy[i].bEnemyAlive		= FALSE;

	//					ExplosionPosSet( g_Enemy[i].fEnemyOldX  , g_Enemy[i].fEnemyOldY , 
	//					g_Enemy[i].fEnemyOldWidth , g_Enemy[i].fEnemuOldHeight);
	//			}
	//		}
	//	
	//		if( ScreenOutJudg( g_Enemy[i].fEnemyPosX , g_Enemy[i].fEnemyPosY ,
	//					g_Enemy[i].fEnemyfWidth , g_Enemy[i].fEnemyfHeight)  == LEFT_OUT )
	//		{
	//			// 1頂点設定
	//			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
	//			g_Enemy[i].fEnemyPosY = ENEMY_POSY;

	//			// 2頂点設定
	//			g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
	//			g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;
	//		}

	//	}
	//}
}

//=============================================================================
//
// 関数名	: EnemyDraw関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵の描画
//
//=============================================================================
void EnemyDraw( void )
{
	// すべての敵を描画
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			PrimitiveCreate(	ENEMYID					,	
								ROTATION						,
								ENEMY_NUM				,
								g_Enemy[i].fEnemyAngle		,
								g_Enemy[i].fEnemyPosX		, 
								g_Enemy[i].fEnemyPosY		,
								g_Enemy[i].fEnemyfWidth	,
								g_Enemy[i].fEnemyfHeight	,
								g_Enemy[i].fEnemyTexX0		,
								g_Enemy[i].fEnemyTexY0		,
								g_Enemy[i].fEnemyTexX1		,
								g_Enemy[i].fEnemyTexY1		);
		}
	}
}

//=============================================================================
//
// 関数名	: EnemyLeft関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵の左移動
//
//=============================================================================
void EnemyLeft( void )
{
	for( int i= 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			g_Enemy[i].fEnemyPosX -= 2.f;
		}
	}
}

//=============================================================================
//
// 関数名	: EnemyRight関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵の右移動
//
//=============================================================================
void EnemyRight( void )
{
	// すべての敵を右へ移動
	for( int i= 0; i < ENEMY_MAX; i++ )
	{
		// もし敵が生きていたら
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			g_Enemy[i].fEnemyPosX += 2.f;
		}
	}
}


//=============================================================================
//
// 関数名	: PlayerUninit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プレイヤーの解放
//
//=============================================================================
void EnemyUninit( void )
{
	// プレイヤーのテクスチャ解放
	TextureUninit( ENEMY_NUM );
}

//=============================================================================
//
// 関数名	: EnemyGet関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 敵のゲッター
//
//=============================================================================
ENEMY* EnemyGet( void )
{
	return &g_Enemy[0];
}

//=============================================================================
//
// 関数名	: EnemySet関数
//
// 戻り値	: なし
//
// 引数		: EnemyAlive
//
// 機能		: 敵のセッター
//
//=============================================================================
void EnemySet( ENEMY *pEnemy )
{
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == FALSE )
		{
			// 1頂点設定
			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
			g_Enemy[i].fEnemyPosY = ENEMY_POSY;

			// 2頂点設定
			g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
			g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;


			// テクスチャの頂点1設定
			g_Enemy[i].fEnemyTexX0 = ENEMY_TEXVTEXX0;
			g_Enemy[i].fEnemyTexY0 = ENEMY_TEXVTEXY0;

			// テクスチャの頂点2設定
			g_Enemy[i].fEnemyTexX1 = ENEMY_TEXVTEXX1;
			g_Enemy[i].fEnemyTexY1 = ENEMY_TEXVTEXY1;


			// 敵が復活
			g_Enemy[i].bEnemyAlive = TRUE;

			// 敵が攻撃可能となる
			g_Enemy[i].bEnemyAttack = pEnemy[i].bEnemyAttack;
		}
	}
}

