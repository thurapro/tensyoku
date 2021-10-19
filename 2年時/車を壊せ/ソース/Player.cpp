//=============================================================================
//
// FAILE NAME [Player.cpp]
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
#include "../hedder/Player.h"
#include "../hedder/Texture.h"
#include "../hedder/game.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/BG.h"
#include "../hedder/Judgment.h"
#include "../hedder/Sound.h"
#include "../hedder/Enemy.h"
#include "../hedder/Explosion.h"
#include <dsound.h>


//=============================================================================
// グローバル変数
//=============================================================================
static PLAYER g_Player;					// プレイヤー構造体定義
static int g_Attack_Wate = 0;			// 攻撃待ち時間
static BOOL g_bAttack = FALSE;			// 攻撃音が再生されたか
static LPDIRECTSOUNDBUFFER g_SAttack;	// 攻撃音バッファ作成
static int g_PlayerTimer = 0;			// プレイヤーの連続攻撃ができるタイマー
static BOOL g_bPlayerTex = FALSE;
static BOOL g_bAttackSou = FALSE;
static PLAYERREMAINING g_Remain;


//=============================================================================
//
// 関数名	: PlayerInit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 初期化
//
//=============================================================================
void PlayerInit( void )
{

	// テクスチャーをロード
	TextureLoad("photo/Player.png", PLAYER_NUM );

	// 1頂点設定
	g_Player.fPlayerPosX = PLAYER_POSX_INIT;
	g_Player.fPlayerPosY = PLAYER_POSY_INIT;

	// 2頂点設定
	g_Player.fPlayerfWidth = PLAYER_WIDTHINIT;
	g_Player.fPlayerfHeight = PLAYER_HEIGHTINIT;

	// テクスチャの頂点0設定
	g_Player.fPlayerTexX0 = PLAYER_TEXVTEXX0;
	g_Player.fPlayerTexY0 = PLAYER_TEXVTEXY0;

	// テクスチャの頂点1設定
	g_Player.fPlayerTexX1 = PLAYER_TEXVTEXX1;
	g_Player.fPlayerTexY1 = PLAYER_TEXVTEXY1;
	
	// プレイヤーの角度を設定(ラジアン値)
	g_Player.fPlayerAngle = 0.f;

	// プレイヤーライフの設定
	g_Player.nPlayerHP = 1;

	// プレイヤーが生きているか
	g_Player.bPlayerAlive = TRUE;

	// プレイヤーは攻撃をしたか
	g_Player.bPlayerAttack = FALSE;

	// プレイヤーは防御したか
	g_Player.bPlayerDefense = FALSE;

	// プレイヤーの連続攻撃が成功したか
	g_Player.bContinuousAttack = FALSE;

	if( !SoundFileLoad( "sound/Attack.wav" , PLAYER_SOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_SAttack , PLAYER_SOUND ) )
	{
		return ;
	}

	TextureLoad( "photo/5.png" , 20 );

	g_Remain.fPlayerRemainingX0 = 0.f;
	g_Remain.fPlayerRemainingX1 = 1.f;
	g_Remain.fPlayerRemainingY0 = 0.f;
	g_Remain.fPlayerRemainingY1 = 1.f;


}

//=============================================================================
//
// 関数名	: PlayerLeft関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 左に移動
//
//=============================================================================
void PlayerLeft( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		if( g_Player.fPlayerPosX > 0   )
		{
			// 左に移動
			BGLeftMove();
		}
	}
}

//=============================================================================
//
// 関数名	: PlayerRight関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 右に移動
//
//=============================================================================
void PlayerRight( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		// 右に移動
		if( g_Player.fPlayerPosX + g_Player.fPlayerfWidth <  SCREEN_WIDTH )
		{
		//	g_Player.fPlayerPosX += 5.f;
		//	g_Player.fPlayerAngle = 165.f; 
			BGRightMove();
		}
	}
	
}

//=============================================================================
//
// 関数名	: PlayerUp関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 上に移動
//
//=============================================================================
void PlayerUp( void )
{
	// プレイヤーが生きている
	if( g_Player.bPlayerAlive == TRUE )
	{
		// 画面外にでていなければ
		if( ScreenOutJudg( g_Player.fPlayerPosX , g_Player.fPlayerPosY ,
					g_Player.fPlayerfWidth , g_Player.fPlayerfHeight ) == UP_OUT )
		{
			// 上に移動
			g_Player.fPlayerPosY -= 5.f;
		}
		
	}

}

//=============================================================================
//
// 関数名	: PlayerDOWN関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 下に移動
//
//=============================================================================
void PlayerDown( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		// 下に移動
		if( g_Player.fPlayerPosY +  g_Player.fPlayerfHeight / 1.25 < SCREEN_HEIGHT )
		{
			g_Player.fPlayerPosY += 5;
		}
	}
}

//=============================================================================
//
// 関数名	: PlayerAngle関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プレイヤーの更新
//
//=============================================================================
void PlayerAngle( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		if( g_Player.fPlayerAngle > 3.1415926534f )
		{
			g_Player.fPlayerAngle -= 3.1415926534f * 2.f;
		}
		else
		{
			g_Player.fPlayerAngle += 2.f;
		}
	}
}

//=============================================================================
//
// 関数名	: PlayerAttack関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プレイヤーの攻撃
//
//=============================================================================
void PlayerAttack( void )
{
	// プレイヤーが攻撃していなければ
	if( g_Player.bPlayerAlive == TRUE && g_Player.bPlayerAttack == FALSE )
	{
		// モーションがすべて完了していなければ
		if( g_Player.fPlayerTexX1 < 1.f  )
		{
			// モーション変更
			g_Player.fPlayerTexX0 += PLAYER_TEXVTEXX1;

			// モーション変更
			g_Player.fPlayerTexX1 += PLAYER_TEXVTEXX1;

			// コンボが成立
			g_Player.bContinuousAttack = TRUE;

			// モーションを変更させた
			g_Player.bAttackMotion = TRUE;

		}

		// モーションすべてを完了させた場合
		else
		{
			// コンボがすべて終わったので攻撃をしたとなる
			g_Player.bPlayerAttack = TRUE;
		}
	}


}

//=============================================================================
//
// 関数名	: PlayerDefense関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プレイヤーの防御
//
//=============================================================================
void PlayerDefense( void )
{
}

//=============================================================================
//
// 関数名	: PlayerUpdate関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 攻撃後の更新
//
//=============================================================================
void PlayerUpdate( void )
{
	ENEMY *pEnemy;
	pEnemy = EnemyGet();

	// もしプレイヤーのコンボが成立した かつ プレイヤーが攻撃をしていなければ
	if( g_Player.bContinuousAttack == TRUE )
	{
		// もし2秒超えていたら
		if( g_PlayerTimer > ATTACK_CONTINUOUS )
		{
			// プレイヤータイマーをリセット
			g_PlayerTimer = 0;
		}

		// プレイヤータイマーの
		g_PlayerTimer++;

		// ゲーム時間で2秒たったらコンボをも元に戻す
		if( g_PlayerTimer == ATTACK_CONTINUOUS )
		{	
			//// コンボ終了
			g_Player.bContinuousAttack = FALSE;

			// 攻撃をした
			g_Player.bPlayerAttack = TRUE;

			g_PlayerTimer = 0;
		}
	}

	if( g_Player.bPlayerAttack == TRUE )
	{
		// プレイヤーモーション座標を初期値へ
		g_Player.fPlayerTexX0 = PLAYER_TEXVTEXX0;

		// プレイヤーモーション座標を初期値へ
		g_Player.fPlayerTexX1 = PLAYER_TEXVTEXX1;
	}

	/*for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( HitJudg( g_Player.fPlayerPosX - 20 , g_Player.fPlayerPosY - 20,
			g_Player.fPlayerfWidth - 20, g_Player.fPlayerfHeight ,
			pEnemy[i].fEnemyPosX - 20 , pEnemy[i].fEnemyPosY ,
			pEnemy[i].fEnemyfWidth + 20 , pEnemy[i].fEnemyfHeight - 50) )
		{
			if( g_Player.fPlayerTexX0 == PLAYER_TEXVTEXX0 && g_Player.fPlayerTexX1 == PLAYER_TEXVTEXX1 )
			{
				if( g_Player.bPlayerAlive == TRUE )
				{
					g_Player.bPlayerAlive = FALSE;

					ExplosionPosSet( g_Player.fPlayerPosX , g_Player.fPlayerPosY ,
								g_Player.fPlayerfWidth , g_Player.fPlayerfHeight );
				}
			}
			
		}

	}*/
}

//=============================================================================
//
// 関数名	: PlayerDraw関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: プレイヤーの描画
//
//=============================================================================
void PlayerDraw( void )
{
	// もしプレイヤーがコンボ(攻撃)していたら
	if( g_Player.bAttackMotion == TRUE )
	{
		g_SAttack->Play( 0 , 0 , 0 );
		g_Player.bAttackMotion = FALSE;
	}

	if( g_Player.bPlayerAlive == TRUE )
	{
		PrimitiveCreate(	PLAYERID					,
							ROTATION					,
							PLAYER_NUM					,
							g_Player.fPlayerAngle		,
							g_Player.fPlayerPosX		, 
							g_Player.fPlayerPosY		,
							g_Player.fPlayerfWidth		,
							g_Player.fPlayerfHeight		,
							g_Player.fPlayerTexX0		,
							g_Player.fPlayerTexY0		,
							g_Player.fPlayerTexX1		,
							g_Player.fPlayerTexY1		);
	}

			PrimitiveCreate(	REMAINID				,
							2							,
							20							,
							0							,
							0							,
							40							,
							60							,
							70							,
							g_Remain.fPlayerRemainingX0		,
							g_Remain.fPlayerRemainingY0		,
							g_Remain.fPlayerRemainingX1		,
							g_Remain.fPlayerRemainingY1		);


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
void PlayerUninit( void )
{
	// プレイヤーのテクスチャ解放
	TextureUninit( PLAYER_NUM );

	TextureUninit( 20 );

	// サウンド解放
	if( g_SAttack != NULL )
	{
		g_SAttack->Release();
		g_SAttack = NULL;
	}
}

//=============================================================================
//
// 関数名	: PlayerGet関数
//
// 戻り値	: PLAYER構造体
//
// 引数		: なし
//
// 機能		: プレイヤーのゲッター
//
//=============================================================================
PLAYER* PlayerGet( void )
{
	return &g_Player;
}

//=============================================================================
//
// 関数名	: PlayerSet関数
//
// 戻り値	: PLAYER構造体
//
// 引数		: なし
//
// 機能		: プレイヤーのゲッター
//
//=============================================================================
void PlayerSet( PLAYER *pPlayer )
{
	// プレイヤーが復活
	g_Player.bPlayerAlive = pPlayer->bPlayerAlive;

	// プレイヤー攻撃可能
	g_Player.bPlayerAttack = pPlayer->bPlayerAttack;

	g_Player.bContinuousAttack = pPlayer->bContinuousAttack;
}

PLAYERREMAINING *RemainGet(void)
{
	return &g_Remain;
}

void RemainSet( PLAYERREMAINING *pRemainSet )
{
	g_Remain.fPlayerRemainingX0 = pRemainSet->fPlayerRemainingX0;

	g_Remain.fPlayerRemainingX1 = pRemainSet->fPlayerRemainingX1;
}