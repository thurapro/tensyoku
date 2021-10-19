//=============================================================================
//
// FAILE NAME [Judgment.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: ゲーム内の判定
//
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Judgment.h"
#include "../hedder/InputKey.h"
#include "../hedder/Texture.h"
#include "../hedder/Player.h"
#include "../hedder/Enemy.h"
#include "../hedder/common.h"
#include "../hedder/BG.h"
#include "../hedder/WinMain.h"
#include "../hedder/Title.h"
#include "../hedder/Game.h"
#include "../hedder/Clear.h"
#include "../hedder/Over.h"
#include <d3d9.h>
#include <windows.h>

//=============================================================================
// グローバル変数
//=============================================================================
static int g_AliveTimer	= 0;				// 復活のタイマー
static int g_PlayerTurnTimer = 0;			// プレイヤー硬直タイマー的な
static int g_EnemyTurnTimer	= 0;			// 敵の硬直タイマー的な	


//=============================================================================
// 当たり判定
//=============================================================================
BOOL HitJudg(	float fax , float fay , float faw , float fah , 
				float fbx , float fby , float fbw , float fbh )
{
	if( fax < ( fbx + fbw ) &&
		fbx < ( fax + faw ) &&
		fay < ( fby + fbh ) && 
		fby < ( fay + fah ) )
	{
		return TRUE;
	}
	return FALSE;
}


//=============================================================================
// 操縦判定
//=============================================================================
void PlayerControlJudg( void )
{
	int Select = GameSelectGet();

	switch( Select )
	{
	case TITLE :
		if( KeyPush( DIK_G ) )
		{
			GameSelectSet( GAME );
			TitleUninit();
		}
		break;

	case GAME :

		// もし右を押したら
		if( KeyState( DIK_RIGHT ) )
		{
			// 右に移動関数
			EnemyLeft();
			BGLeftMove();
		}

		// もし左を押したら
		//if( KeyState( DIK_LEFT ) )
		//{
		//	// 左に移動関数
		//	EnemyRight();
		//	BGRightMove();
		//}

		// もし上を押したら
		if( KeyState( DIK_UP ) )
		{
			// 上に移動関数
			PlayerUp();
		}

		// もし下を押したら
		if( KeyState( DIK_DOWN ) )
		{
			// 下に移動関数
			PlayerDown();
		}

		// もしAを押したら
		if( KeyPush( DIK_F ) )
		{
			// 攻撃関数
			PlayerAttack();
		}

		// もしSを押したら
		if( KeyState( DIK_S ) )
		{
			// 防御関数
			PlayerDefense();
		}

		// もしHを押したら
		if( KeyState( DIK_H ) )
		{
			// 回転関数
			PlayerAngle();
		}
		break;

	case CLEAR :
		if( KeyPush( DIK_D ) )
		{
			GameSelectSet( INIT );
			ClearUninit();
		}
		break;

	case OVER :
		if( KeyPush( DIK_D) )
		{
			GameSelectSet( INIT );
			OverUninit();
		}
 
	default :
		break;
	}
}

//=============================================================================
// 復活判定
//=============================================================================
void RebornJudg( void )
{
	// ポインター宣言
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	// プレイヤーを構造体を持ってくる
	pPlayer = PlayerGet();

	// 敵の構造体を持ってくる
	pEnemy = EnemyGet();
	
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// もしどちらかが戦闘不能時
		if( pPlayer->bPlayerAlive == FALSE 
			|| pEnemy[i].bEnemyAlive == FALSE ) 
		{
			// タイマー起動
			g_AliveTimer++;

			// タイマーが3秒経過したときに復活
			if( g_AliveTimer == ALIVE_TIMEWATE )
			{
				// もしプレイヤーが戦闘不能な場合
				if( pPlayer->bPlayerAlive == FALSE )
				{
					pPlayer->bPlayerAlive = TRUE;
					PlayerSet( pPlayer );
				}
				
				// タイマーのリセット
				g_AliveTimer = 0;
			}

			if( pEnemy[i].nEnemyWate == ALIVE_TIMEWATE )
			{
				// もし敵が戦闘不能なら
				if( pEnemy[i].bEnemyAlive == FALSE )
				{
					EnemySet( pEnemy );
				}
				pEnemy[i].nEnemyWate = 0;
			}
			
			// 敵の復活カウント
			pEnemy[i].nEnemyWate++;
		}
	}
}

//=============================================================================
// ターン関数
//=============================================================================
void TurnJudg( void )
{
	// ポインター変数
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	// プレイヤーを構造体を持ってくる
	pPlayer = PlayerGet();

	// 敵の構造体を持ってくる
	pEnemy = EnemyGet();

	// もしどちらか一方が攻撃したら
	if( pPlayer->bPlayerAttack == TRUE )
	{
		// 2秒間攻撃できない
		if( g_PlayerTurnTimer == TURN_TIMEWATE )
		{
			// もしプレイヤーが攻撃を行ったら
			if( pPlayer->bPlayerAttack == TRUE )
			{
				// プレイヤーは攻撃可能になる
				pPlayer->bPlayerAttack = FALSE;
				PlayerSet( pPlayer );		
			}
			g_PlayerTurnTimer = 0;
		}
		g_PlayerTurnTimer++;
	}

	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// もし敵が攻撃を行ったら
		if( pEnemy[i].bEnemyAttack == TRUE )
		{
			if( g_EnemyTurnTimer == TURN_TIMEWATE )
			{
				// 敵は攻撃可能となる
				pEnemy[i].bEnemyAttack = FALSE;
				EnemySet( pEnemy );

				g_EnemyTurnTimer = 0;
			}
			g_EnemyTurnTimer++;
		}
	}
		
}

//=============================================================================
// 画面外にでたか判定
//=============================================================================
int ScreenOutJudg( float fX , float fY , float fWidth , float  fHeight)
{
	// もし左に出たら
	if( fX < 0 )
	{
		return LEFT_OUT;
	}

	// もし右に出たら
	if( fX + fWidth > SCREEN_WIDTH )
	{
		return RIGHT_OUT;
	}
	
	// もし上に出たら
	if( fY > PLAYER_POSY_INIT )
	{
		return UP_OUT;
	}

	// もし下に出たら
	if( fY + fHeight / 1.25 < SCREEN_HEIGHT )
	{
		return DOWN_OUT;
	}

	return NO_OUT;
}
