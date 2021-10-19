//=============================================================================
// ツール作成の前手順　　　　　　　　フィールド作成ツール用
//  
// メイン処理 [main.cpp]
//
// 機能 : DXUTの基礎を調べるもの
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================

#include "manager.h"
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CLASS_NAME	("メッシュフィールド")		// クラスの名前
#define WINDOW_NAME	("メッシュフィールド")		// ウィンドウの名前

//=============================================================================
// プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//=============================================================================
// 関数名	: APIENTRY WinMain
// 戻り値	: DWORD
// 引数値	: Hインスタンス, Hプレビューインスタンス, 
//				コマンドライン, コマンド映像
// 機能		: メイン処理
//=============================================================================
int APIENTRY WinMain(HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	// ウィンドウに関する変数
	HWND	hWnd;			// ウィンドウハンドル
	MSG		msg;			// メッセージ
	HRESULT	hr;				// エラー処理

	// FPSに関する変数
	DWORD dwExecLastTime;	// 最後の時間
	DWORD dwFPSLastTime;	// FPS終了時間
	DWORD dwCurrentTime;	// 現在の時刻
	DWORD dwFrameCount;		// フレームカウント
	DWORD dwCoudwtFPS;		// FPSカウンター

	// ウィンドウクラス作成
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);


	// ウィンドウの作成
	hWnd = CreateWindowEx( 0,			// ウィンドウスタイル作成
				CLASS_NAME,				// クラスの名前設定
				WINDOW_NAME,			// ウィンドウの名前設定
				WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル設定
				CW_USEDEFAULT,			// ウィンドウを表示する位置 (X座標)
				CW_USEDEFAULT,			// ウィンドウを表示する位置 (Y座標)
				WINDOW_WIDTH,			// ウィンドウの幅
				WINDOW_HEIGHT,			// ウィンドウの高さ
				NULL,					// 親ウィンドウのハンドル
				NULL,					// メニューハンドル
				hInstance,				// インスタンスハンドル
				NULL);					// その他の作成データ

	// FPS設定
	timeBeginPeriod(1);					// デバイスドライブの時間をミリ秒に指定
	dwExecLastTime =					// FPS最後の時間を代入	
	dwFPSLastTime = timeGetTime();		// 時間を取得
	dwCurrentTime =						// フレームカウントを現在の時間に代入
	dwFrameCount = 0;					// フレームカウントを初期化
	dwCoudwtFPS	= 0;					// FPSカウンター初期化

	// マネージャーを作成
	CManager *pManager = NULL;						// マネージャーポインタ初期化 
	NEW_TYPE(pManager, CManager);					// マネージャー生成
	hr = pManager->Init(hInstance, hWnd, TRUE);		// マネージャ初期化
	ERROR_CHACK(hr);								// エラーチェック

	// ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);						// ウィンドウ表示
	UpdateWindow(hWnd);								// ウィンドウの更新

	// 更新＆描画
	while(true)
	{
		// メッセージ取得
		if( PeekMessage(&msg , NULL , 0 , 0 ,PM_REMOVE) )
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if( (dwCurrentTime - dwFPSLastTime) >= 500)
			{
				dwCoudwtFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			/////// FPSが1秒たったら //////
			if((dwCurrentTime - dwExecLastTime) >= 1000 / 60)
			{
				CManager::GetDebug()->Print("FPS:%d\n", dwCoudwtFPS);	// FPS出力
				pManager->Update();										// マネージャー更新
				pManager->Draw();										// マネージャー描画
				dwExecLastTime = dwCurrentTime;						
				dwFrameCount++;											// 現在の時間をカウントアップ
			}
		}
	}

	// 終了処理
	CLASS_DELETE(pManager);		// マネージャクラス破棄

	///// システム終了処理 /////
	return NULL;
}


//=============================================================================
// 関数名	: WndProc
// 戻り値	: LRESULT
// 引数値	: ウィンドウハンドル, メッセージ, Wパラメータ, Lパラメータ 
// 機能		: ウィンドウに直接行う処理
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{	
	case WM_DESTROY:
		PostQuitMessage(0);						// ウィンドウを破棄
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE :						// [ESC]キーが押された
			DestroyWindow(hWnd);				// ウィンドウを破棄するように指示
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd , message , wParam , lParam);
		break;
	}
	return 0;
}

