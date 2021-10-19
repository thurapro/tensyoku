//=============================================================================
//
// FAILE NAME [Player.h]
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
// 二重インクルード防止
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define ENEMY_NUM			( 3 )		// テクスチャー番号
#define ENEMY_POSX			( 270 )		// 敵のいるX座標
#define ENEMY_POSY			( 250 )		// 敵のいるY座標
#define ENEMY_WIDHTINIT		( 90 )		// 敵の幅
#define ENEMY_HEIGHTINIT	( 120 )		// 敵の高さ
#define ENEMY_TEXVTEXX0		( 0.f )		// 敵の画像頂点座標X1
#define ENEMY_TEXVTEXY0		( 0.f )		// 敵の画像頂点座標Y1
#define ENEMY_TEXVTEXX1		( 1.f )		// 敵の画像頂点座標X2
#define ENEMY_TEXVTEXY1		( 1.f )		// 敵の画像頂点座標Y2
#define ENEMY_ANGLE			( 0.f )		// 敵の角度
#define RADIUS				( 180 )		// 半径
#define ANGLEADD			( 50.f )	// 角度を足す
#define ENEMY_MAX			( 2 )		// 敵の最大数

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	float	fEnemyPosX;					// 敵のポジションX( vtxX1と同じ )
	float	fEnemyPosY;					// 敵のポジションY( vtxY1と同じ )
	float	fEnemyfWidth;				// 敵の幅( vtxX4と同じ )
	float	fEnemyfHeight;				// 敵の高さ( vtxY4と同じ )
	float	fEnemyTexX0;				// 敵のテクスチャーX座標1
	float	fEnemyTexY0;				// 敵のテクスチャーY座標1
	float	fEnemyTexX1;				// 敵のテクスチャーX座標2
	float	fEnemyTexY1;				// 敵のテクスチャーY座標2
	float	fEnemyAngle;				// 敵の角度
	float	fEnemyOldX;					// 敵の元の座標X
	float	fEnemyOldY;					// 敵の元の座標Y
	float	fEnemyOldWidth;				// 敵の元の幅
	float	fEnemuOldHeight;			// 敵の元の高さ
	int		nEnemyWate;					// 敵の出現待ち
	int		nDeadcount;					// 敵の死んだ回数
	BOOL	bEnemyAlive;				// 敵が生きているか
	BOOL	bEnemyAttack;				// 敵は攻撃したか
	BOOL	bEnemyDefense;				// 敵は防御したか
}ENEMY;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void EnemyInit( void );				// 敵の初期化		
void EnemyUpdate( void );			// 敵の更新
void EnemyLeft( void );				// 敵を左に移動
void EnemyRight( void );			// 敵を右に移動
void EnemyDraw( void );				// 敵の描画
void EnemyUninit( void );			// 敵の解放
ENEMY* EnemyGet( void );			// 敵のゲッター
void EnemySet( ENEMY *pEnemy );		// 敵のセッター


#endif //_PLAYER_H_