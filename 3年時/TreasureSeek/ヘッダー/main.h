//=============================================================================
// ツール作成の前手順　　　　　　　　フィールド作成ツール用
//  
// メイン処理 [main.h]
//
// 機能 : DXUTの基礎を調べるもの
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// ライブラリーファイル読み込み
//=============================================================================
#pragma comment (lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBGUG)	// DEBUG
#pragma comment (lib, "d3dx9.lib")
#else	// RELEASE
#pragma comment (lib, "d3dx9.lib")
#endif // pragma comment

#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

//=============================================================================
// マクロ定義
//=============================================================================
#define WINDOW_WIDTH	(640)											// ウィンドウの幅
#define WINDOW_HEIGHT	(480)											// ウィンドウの高さ

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void FPSCnt(int nFrameCount);

#endif // _MAIN_H_


// end of file //

