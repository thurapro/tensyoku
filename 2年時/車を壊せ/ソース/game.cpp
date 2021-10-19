//=============================================================================
//
// FAILE NAME [game.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: ゲーム処理部分
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/game.h"
#include "../hedder/Texture.h"
#include "../hedder/Font.h"
#include "../hedder/InputKey.h"
#include "../hedder/Judgment.h"
#include "../hedder/BG.h"
#include "../hedder/Enemy.h"
#include "../hedder/Player.h"
#include "../hedder/Explosion.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/common.h"
#include <dsound.h>


//=============================================================================
// グローバル変数
//=============================================================================
static LPDIRECTSOUNDBUFFER	g_BGM					= NULL;			// BGM用
static BOOL					g_bSound				= FALSE;		// BGMがなっているか
static int					g_nGameTimer			= 180;			// ゲーム世界の時間
static int					g_nOneSecondSetting		= 0;			// 1秒設定
static DRAWFONT				g_Font					= { NULL };

//=============================================================================
//
// 関数名	: GameInit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: ゲームの初期化
//
//=============================================================================
void GameInit( void )
{
	BGInit();
	PlayerInit();
	EnemyInit();
	ExplosionInit();
	if( !SoundFileLoad( "sound/BGM.wav" , 0) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_BGM , 0 ) )
	{
		return ;
	}

	g_nGameTimer = 180;

}

//=============================================================================
//
// 関数名	: GameUpdate関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: ゲームの更新
//
//=============================================================================
void GameUpdate( void )
{
	// プレイヤーポインタ宣言
	PLAYER	*pPlayer;

	// 敵ポインタ宣言
	ENEMY	*pEnemy;

	PLAYERREMAINING *pRemain;

	pRemain = RemainGet();

	if( g_nOneSecondSetting == 60 )
	{
		// ゲームタイマー更新
		g_nGameTimer--;

		g_nOneSecondSetting = 0;
	}

	// プレイヤーのキー入力判定
	PlayerControlJudg();

	// プレイヤーの更新
	PlayerUpdate();

	// 敵の動き更新
	EnemyUpdate();

	// 爆発の動き更新
	ExplosionUpdate( );

	pPlayer = PlayerGet();

	pEnemy = EnemyGet();

	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// あたり判定
		if( HitJudg( pPlayer->fPlayerPosX , pPlayer->fPlayerPosY  ,
				pPlayer->fPlayerfWidth - 40 , pPlayer->fPlayerfHeight ,
				pEnemy[i].fEnemyPosX  , pEnemy[i].fEnemyPosY ,
				pEnemy[i].fEnemyfWidth , pEnemy[i].fEnemyfHeight - 70) )
		{
			// プレイヤーが最初のモーションだったら
			if( pPlayer->fPlayerTexX0 == PLAYER_TEXVTEXX0 && pPlayer->fPlayerTexX1 == PLAYER_TEXVTEXX1 )
			{
				if( pEnemy[i].bEnemyAttack != TRUE )
				{

					// もしプレイヤーが生きていたら
					if( pPlayer->bPlayerAlive == TRUE )
					{
						// プレイヤーが死亡
						pPlayer->bPlayerAlive = FALSE;

						// 死んだときに出るエフェクトを元いたプレイヤーの場所にセット
						ExplosionPosSet( pPlayer->fPlayerPosX , pPlayer->fPlayerPosY ,
									pPlayer->fPlayerfWidth , pPlayer->fPlayerfHeight );
						
						pRemain->fPlayerRemainingX0 = 0.f;
						pRemain->fPlayerRemainingX1 -= 0.5f;
					}					

					pEnemy[i].bEnemyAttack = TRUE;
				}

			}
			else if( pPlayer->fPlayerTexX0 != PLAYER_TEXVTEXX0 && pPlayer->fPlayerTexX1 != PLAYER_TEXVTEXX1 )
			{			
				// 敵がいた中心Xを記録(X座標)
				pEnemy[i].fEnemyOldX =  pEnemy[i].fEnemyPosX;

				// 敵がいた中心Yを記録(Y座標)
				pEnemy[i].fEnemyOldY =  pEnemy[i].fEnemyPosY;
				
				// 敵の元の幅
				pEnemy[i].fEnemyOldWidth = pEnemy[i].fEnemyfWidth;

				// 敵の元の高さ
				pEnemy[i].fEnemuOldHeight = pEnemy[i].fEnemyfHeight;

				// 敵をステージ上から消す
				pEnemy[i].fEnemyfHeight		= 0;
				pEnemy[i].fEnemyfWidth		= 0;
				pEnemy[i].fEnemyPosX		= 0;
				pEnemy[i].fEnemyPosY		= 0;
				pEnemy[i].bEnemyAlive		= FALSE;

				ExplosionPosSet( pEnemy[i].fEnemyOldX  , pEnemy[i].fEnemyOldY , 
				pEnemy[i].fEnemyOldWidth , pEnemy[i].fEnemuOldHeight);
			}
		}
		if( ScreenOutJudg(pEnemy[i].fEnemyPosX ,pEnemy[i].fEnemyPosY ,
						pEnemy[i].fEnemyfWidth ,pEnemy[i].fEnemyfHeight)  == LEFT_OUT )
		{
			// 1頂点設定
			pEnemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
			pEnemy[i].fEnemyPosY = ENEMY_POSY;

			// 2頂点設定
			pEnemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
			pEnemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;
		}

	}
	

	// 復活判定
	RebornJudg();

	// 攻撃可能か判定
	TurnJudg();

	g_nOneSecondSetting++;

	if( g_nGameTimer == 0 )
	{
		GameSelectSet( CLEAR );
		GameUninit();
	}

	if(pRemain->fPlayerRemainingX1 == 0.f)
	{
		GameSelectSet( OVER );
		GameUninit();
	}
}


//=============================================================================
//
// 関数名	: GameDraw関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: ゲームの描画
//
//=============================================================================
void GameDraw( void )
{
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	pPlayer		= PlayerGet();
	pEnemy		= EnemyGet();

	// 背景の描画
	BGDraw();

	// プレイヤーの描画
	PlayerDraw();

	// 敵の描画
	EnemyDraw();

	// 爆発の描画
	ExplosionDraw();

	itoa( g_nGameTimer , g_Font.nGameTimer , 10 );
	itoa( pPlayer->nPlayerHP , g_Font.nPlayerHP , 10 );

	// フォント
	FontDraw( 300 , 150 , 360 , 220 , g_Font.nGameTimer );

	FontDraw( 200 , 100 , 400 , 220 , g_Font.nPlayerHP );/*pPlayer->fPlayerPosX , pPlayer->fPlayerPosY - 20 ,
		pPlayer->fPlayerfWidth , pPlayer->fPlayerfHeight ,  g_Font.nPlayerH );*/

		// bgmを再生
	g_BGM->Play( 0 , 0 , 0 );
}

//=============================================================================
//
// 関数名	: GameUninit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: ゲームの解放
//
//=============================================================================
void GameUninit( void )
{
	BGUninit();
	PlayerUninit();
	EnemyUninit();
	ExplosionUninit();
	if( g_BGM != NULL )
	{
		g_BGM->Release();
		g_BGM = NULL;
	}
}