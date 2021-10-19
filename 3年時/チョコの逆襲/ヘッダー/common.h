//=============================================================================
//
// FAILE NAME [common.h]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: 共通マクロ定義の管理
//
//=============================================================================

//=============================================================================
// 二重インクルード防止
//=============================================================================
#ifndef _COMMON_H_
#define _COMMON_H_

//=============================================================================
// インクルード
//=============================================================================
#include "debug.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CLASS_NAME		"ウインドウクラス"		// ウインドウのクラス
#define WINDOW_NAME		"ウインドウタイトル"	// ウインドウのキャプション名
#define SCREEN_WIDTH		(640)				// ウィンドウ幅
#define SCREEN_HEIGHT		(480)				// ウィンドウ高さ

#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 自由に設定できる頂点フォーマット
#define VERTEX_MAX		( 30 )				// 頂点バッファ設定容量
#define VTEXMAX			( 6 )				// 頂点の最大数
#define RED_MAX			( 255 )				// 赤色の最大色
#define GREEN_MAX		( 255 )				// 緑色の最大色
#define BLUE_MAX		( 255 )				// 青色の最大色
#define ALPHA_MAX		( 255 )				// 透明度の最大

//==============================================================================
// 
//==============================================================================
typedef struct
{
	D3DXVECTOR3		vtx;		// 3D頂点座標( X , Y , Z )　directXでは左手座標系
	D3DXVECTOR3		nor;		// 法線ベクトル 面の向き( 表裏 )
	D3DCOLOR		diffuse;	// 反射光の色合い
	D3DXVECTOR2		tex;		// テクスチャ座標
}VERTEX_3D;

//=============================================================================
// ID列挙型
//=============================================================================
enum
{
	TITLEID = 0	,								// タイトルID
	BGID		,								// 背景のID
	PLAYERID	,								// プレイヤーのID
	ENEMYID		,								// 敵のID
	EXPLOSIONID	,								// 爆発のID	
	CLEARID		,								// ゲームクリアーID
	OVERID		,								// ゲームオーバーID
	REMAINID	,								// 残機
	MAXID										// 最後のID
};

//=============================================================================
// ゲームセレクト列挙型
//=============================================================================
enum
{
	INIT = 0	,								// 初期化を行う
	TITLE		,			// タイトルを実行
	EXPLAIN		,
	GAME		,			// ゲームメイン実行
	CLEAR		,								// ゲームクリアーを実行
	OVER		,								// ゲームオーバーを実行
	LANK
};

enum
{
	PLAYER_STOP = 3,
	BULLET_SHOT ,
	EXPLOSION_END
};

#endif // _COMMON_H_