//=============================================================================
//
// FAILE NAME [FPS.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: FPSの固定
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/FPS.h"
#include <windows.h>
#include <d3dx9.h>

//=============================================================================
// グローバル宣言
//=============================================================================
static	int g_nExecLastTime;		// 最後の時間
static	int g_nFPSLastTime;			// FPS終了時間
static	int g_nCurrentTime;			// 現在の時刻
static	int g_nFrameCount;			// フレームカウント

//=============================================================================
//
// 関数名	: FPSinit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: FPSの初期化
//
//=============================================================================
void FPSInit( void )
{
	// 分解能を設定
	timeBeginPeriod(1);

	g_nExecLastTime = 
	g_nFPSLastTime = timeGetTime();
	g_nCurrentTime = 
	g_nFrameCount = 0;
}

//=============================================================================
//
// 関数名	: FPSFixing関数
//
// 戻り値	: 時間は正確に固定されたか
//
// 引数		: なし
//
// 機能		: FPSの固定化
//
//=============================================================================
BOOL FPSFixing( void )
{
	g_nCurrentTime = timeGetTime();
	if( ( g_nCurrentTime - g_nFPSLastTime ) >= 500 )
	{
		g_nFPSLastTime = g_nCurrentTime;
		g_nFrameCount = 0;
	}

	if( ( g_nCurrentTime - g_nExecLastTime ) >= FPS_FIXING )
	{
		g_nExecLastTime = g_nCurrentTime;
		return TRUE;
	}
	return FALSE;
}


void SetFrameTime( int nFrameCount )
{
	g_nFrameCount = nFrameCount;
}