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
// マクロ定義
//=============================================================================
#define CLASS_NAME		"ウインドウクラス"		// ウインドウのクラス
#define WINDOW_NAME		"ウインドウタイトル"	// ウインドウのキャプション名
#define SCREEN_WIDTH		(640)				// ウィンドウ幅
#define SCREEN_HEIGHT		(480)				// ウィンドウ高さ

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
	TITLE		,								// タイトルを実行
	GAME		,								// ゲームメイン実行
	CLEAR		,								// ゲームクリアーを実行
	OVER										// ゲームオーバーを実行
};

#endif // _COMMON_H_