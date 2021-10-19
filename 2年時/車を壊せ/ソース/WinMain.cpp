//=============================================================================
//
// FAILE NAME[WinMain.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: メイン
//
//
//=============================================================================
#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "../hedder/Font.h"
#include "../hedder/Direct3DCreater.h"
#include "../hedder/WndProc.h"
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Judgment.h"
#include "../hedder/common.h"
#include "../hedder/InputKey.h"
#include "../hedder/game.h"
#include "../hedder/System.h"
#include "../hedder/FPS.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/Title.h"
#include "../hedder/Clear.h"
#include "../hedder/Over.h"

static int g_GameSelect = INIT;

//============================================================================
//
// 関数名	:	WinMain関数
//
// 戻り値	:	int
//
// 引数		:	hインスタンス , プレブインスタンス
//
// 機能		:	
//			
//
//============================================================================
// メイン関数
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
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

	HWND hWnd;
	MSG msg;
	HRESULT hr = NULL;


	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	int nFrameCount = 0;
	
	// システム初期化
	SystemInit(hInstance , hWnd);

	if( !SoundInit( hWnd ) )
	{
		return -1;
	}
	if( !CreatePrimaryBuff() ) 
	{
		return -1;
	}

	// 変数定義
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// ウィンドウ表示
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	BOOL bFPSFixing = FALSE;


	// メインループ
	while(1)
	{
		bFPSFixing = FPSFixing();

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
			if( bFPSFixing == TRUE )
			{
				UpdateInput();

				switch( g_GameSelect )
				{
				case INIT :
					TitleInit();
					GameInit();
					ClearInit();
					OverInit();
					g_GameSelect = TITLE;
					break;

				case TITLE :
					TitleUpdate();
					break;

				//=========================
				// ゲーム更新処理
				//=========================
				case GAME :
					GameUpdate();
					break;

				case CLEAR :
					ClearUpdate();
					break;

				case OVER :
					OverUpdate();
				}
				
#if 0
				for(int i=0;i<敵の数;++i)
				{
					プレーヤーと敵のxの差分 = プレーヤーのx座標 - 敵のx座標
					プレーヤーと敵のyの差分 = プレーヤーのy座標 - 敵のy座標
					プレーヤーと敵の距離 = sqrtf( (プレーヤーと敵のxの差分 * プレーヤーと敵のxの差分) + (プレーヤーと敵のyの差分 * プレーヤーと敵のyの差分) );
					if( あたっていたら(プレーヤーと敵の距離<プレーヤーの半径＋敵の半径) )
					{
						あたっていた時の処理
					}
				}
#endif

				//=========================
				// ゲーム描画処理
				//=========================
				// バックバッファのクリア
				pD3DDevice->Clear
					( 0 , NULL ,
					 (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER) ,
					 D3DCOLOR_RGBA( 0 , 0 , 0 , 0) ,
					 1.0f, 0);			


				// 描画開始
				hr = pD3DDevice->BeginScene();
				if( SUCCEEDED(hr) )
				{
					//==============================
					// ここに描画処理
					//==============================
					
					//*******************************
					// 描画関数
					//*******************************
					switch( g_GameSelect )
					{
						if( g_GameSelect != INIT )
						{
							case TITLE :
								TitleDraw();
								break;

							case GAME :
								GameDraw();
								break;

							case CLEAR :
								ClearDraw();
								break;

							case OVER :
								OverDraw();

							default :
								break;
						}
					}
						
					// 描画終了
					pD3DDevice->EndScene();
				}

				// バックバッファとフロントバッファ入れ替え
				pD3DDevice->Present( 
							NULL ,
							NULL ,
							NULL , 
							NULL );

				nFrameCount++;
				SetFrameTime( nFrameCount );
			}
		}

	}

	// 全システムの解放
	SystemUninit();

	// ウィンドウクラス登録を解除
	UnregisterClass(
		CLASS_NAME ,
		wcex.hInstance);

	return (int)msg.wParam;
}

int GameSelectGet( void )
{
	return g_GameSelect;
}

void GameSelectSet( int Select )
{
	g_GameSelect = Select;
}


