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
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>


//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_NUM			( 2 )			// テクスチャー番号	
#define PLAYER_SOUND		( 2 )
#define PLAYER_WIDTHINIT	( 90 )			// プレイヤーの幅の初期値
#define PLAYER_HEIGHTINIT	( 120 )			// プレイヤーの高さの初期値
#define PLAYER_POSX_INIT	( 0 )			// プレイヤーの初期位置X座標
#define PLAYER_POSY_INIT	( 240 )
#define PLAYER_TEXVTEXX0	( 0.f )			// プレイヤーモーション初期値( 初めのX軸 )
#define PLAYER_TEXVTEXY0	( 0.f )			// プレイヤーモーション初期値( 初めのY軸 )
#define PLAYER_TEXVTEXX1	( 1.f* 0.25f )	// プレイヤーモーション初期値( 終わりのX軸 )
#define PLAYER_TEXVTEXY1	( 1.0f * 0.5f )	// プレイヤーモーション初期値( 終わりのY軸 )
#define ATTACK_CONTINUOUS	( 120 )			// コンボがつながる時間	
#define MOTION_WATE			( 120 )					


//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	float fPlayerPosX;						// プレイヤーのポジションX( vtxX1と同じ )
	float fPlayerPosY;						// プレイヤーのポジションY( vtxY1と同じ )
	float fPlayerfWidth;					// プレイヤーの幅( vtxX4と同じ )
	float fPlayerfHeight;					// プレイヤーの高さ( vtxY4と同じ )
	float fPlayerTexX0;						// プレイヤーテクスチャーX座標0
	float fPlayerTexY0;						// プレイヤーテクスチャーY座標0
	float fPlayerTexX1;						// プレイヤーテクスチャーX座標1
	float fPlayerTexY1;						// プレイヤーテクスチャーY座標1
	float fPlayerAngle;						// プレイヤーの角度
	int	nPlayerHP;							// プレイヤーのライフ
	BOOL bPlayerAlive;						// プレイヤーが生きているか
	BOOL bPlayerAttack;						// プレイヤーは攻撃をしたか
	BOOL bPlayerDefense;					// プレイヤーは防御をしたか
	BOOL bContinuousAttack;					// プレイヤーの連続攻撃が成功したかの確認
	BOOL bAttackMotion;
}PLAYER;

typedef struct
{
	float fPlayerRemainingX0;
	float fPlayerRemainingX1;
	float fPlayerRemainingY0;
	float fPlayerRemainingY1;
}PLAYERREMAINING;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void PlayerInit( void );					// プレイヤーの初期化
void PlayerLeft( void );					// プレイヤーの左移動
void PlayerRight( void );					// プレイヤーの右移動
void PlayerUp( void );						// プレイヤーの上移動
void PlayerDown( void );					// プレイヤーの下移動
void PlayerAngle( void );					// プレイヤーの角度変更
void PlayerAttack( void );					// プレイヤーの攻撃
void PlayerDefense( void );					// プレイヤーの防御
void PlayerUpdate( void );					// プレイヤーの更新
void PlayerDraw( void );					// プレイヤーの描画
void PlayerUninit( void );					// プレイヤーの解放
PLAYER *PlayerGet( void );					// プレイヤーゲッター
void PlayerSet( PLAYER * pPlayer );			// プレイヤーセッター
PLAYERREMAINING *RemainGet(void);
void RemainSet( PLAYERREMAINING *pRemain );

#endif //_PLAYER_H_