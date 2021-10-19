//=============================================================================
//
// メイン処理[WinMain.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: メイン
//
//=============================================================================
#include <windows.h>

#include "../hedder/WinMain.h"

#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 自由に設定できる頂点フォーマット
#define VERTEX_MAX		( 30 )				// 頂点バッファ設定容量
#define VTEXMAX			( 6 )				// 頂点の最大数
#define RED_MAX			( 255 )				// 赤色の最大色
#define GREEN_MAX		( 255 )				// 緑色の最大色
#define BLUE_MAX		( 255 )				// 青色の最大色
#define ALPHA_MAX		( 255 )				// 透明度の最大

static int	g_nSelect = TITLE;				// ゲーム遷移
static bool g_bStop = false;				// ゲームを止める
static int g_nGameTime;						// ゲームタイム

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
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	//---------------------------------
	// 変数宣言
	HWND hWnd;							// ウィンドに関する
	MSG msg;							// メッセージに関する
	HRESULT hr = NULL;					// 結果変数
	LPDIRECT3DDEVICE9 pDevice;			// デバイスに関する
	LPDIRECT3D9 pD3D = NULL;			// Direct3Dオブジェクト

	//-------------------------------------------------------------------------
	// ウィンドクラス
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

	//-------------------------------------------------------------------------
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//-------------------------------------------------------------------------
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

	//-------------------------------------------------------------------------
	// DirectXの初期化
	pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	// デバイス作成失敗
	if(NULL == pD3D)
	{
		return -1;
	}

	// 現在のディスプレイモード取得
	D3DDISPLAYMODE d3ddm;	
	hr = pD3D->GetAdapterDisplayMode( 
	D3DADAPTER_DEFAULT,&d3ddm);
	if( FAILED( hr ) )
	{
		return -1;
	}

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp , sizeof(d3dpp) );

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(TRUE == d3dpp.Windowed)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// デバイス生成
	struct
	{
		D3DDEVTYPE	DevType;
		DWORD		BehaviorFlags;
	} 
	DevTypes[] = {
		{ D3DDEVTYPE_HAL , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_HAL , D3DCREATE_SOFTWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_SOFTWARE_VERTEXPROCESSING }
	};

	D3DDEVTYPE	DevType;
	DWORD		BehaviorFlags;
	BOOL		bCreateDevice;
	int			i;
	bCreateDevice = FALSE;

	for( i = 0; i < _countof(DevTypes); i++)
	{
		DevType	= DevTypes[i].DevType;
		BehaviorFlags = DevTypes[i].BehaviorFlags;
		hr = pD3D->CreateDevice(
		D3DADAPTER_DEFAULT ,
		DevType ,
		hWnd ,
		BehaviorFlags ,
		&d3dpp,
		&pDevice);

		if(SUCCEEDED( hr ) )
		{
			bCreateDevice = TRUE;
			break;
		}
	}
	if( FALSE == bCreateDevice )
	{
		return FALSE;
	}
	//----------------------------------------------------------------------------
	// レンダリングステートの初期化設定
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//
	//-------------------------------------------------------------------------
	// サンプラーステートの初期化設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	 //------------------------------------------------------------------------
	 // キー初期化
	if( !InitInput( hInstance , hWnd ) )
	{
		// 初期化失敗
		return -1;
	}

	if( !SoundInit(hWnd) )
	{
		return -1;
	}

	if( !CreatePrimaryBuff() ) 
	{
		return -1;
	}

	//-------------------------------------------------------------------------
	// ウィンドウ表示
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	//---------------------------------
	// 変数宣言
	BOOL bFPS = FALSE;		// FPS固定
	int nFrameCount = 0;	// プレイムカウント

	bool bTitleInit = false;	// タイトルを初期化したか？
	bool bGameInit = false;		// ゲームを初期化したか？
	bool bClearInit = false;	// クリアを初期化したか?
	bool bOverInit= false;		// オーバーを初期化したか?
	bool bExplainInit = false;
	bool bLankInit = false;
	g_bStop = false;
	int nTimeCnt = 0;

	//-------------------------------------------------------------------------
	// メインループ
	while(1)
	{
		//---------------------------------------------------------------------
		// フレームカウント
		bFPS = FPSFixing();

		//---------------------------------------------------------------------
		// メッセージを覗く？
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
			if( bFPS == TRUE )
			{
				//-------------------------------------------------------------
				// 入力更新
				UpdateInput();
				switch(g_nSelect)
				{
				case TITLE:
					//---------------------------------
					// タイトルが初期化されていなければ
					if(bTitleInit == false)
					{
						InitTitle(pDevice);			// タイトルの初期化
						bGameInit = false;			// ゲームフラグの初期化
						bClearInit = false;			// クリアフラグの初期化
						bOverInit = false;			// オーバーフラグの初期化
						bTitleInit = true;			// タイトル初期化終了
					}
					else
					{
						UpdateTitle();				// タイトル更新
						//---------------------
						// タイトルじゃなかったら
						if(g_nSelect != TITLE)
						{
							UninitTitle();
							g_nSelect = EXPLAIN;
							bTitleInit = false;
						}
					}
					break;

				case EXPLAIN:
					if( bExplainInit == false )
					{
						InitExplain(pDevice);
						bExplainInit = true;
					}
					else
					{
						UpdateExplain();
						if( g_nSelect != EXPLAIN)
						{
							UninitExplain();
							bExplainInit = false;
						}
					}
					break;

				case GAME:
					LPDIRECTSOUNDBUFFER soundGame;
					//-------------------------------
					// ゲーム初期化されていなければ
					if(bGameInit == false)
					{
						g_nGameTime = 0;
						SoundFileLoad("DATA/Sound/Game.wav", GAME);
						CreateSoundBuffer(&soundGame, GAME);
						CameraInit();								// カメラの初期化
						LightInit(pDevice);							// ライトの初期化
						FieldInit(pDevice, 100, 100, 10, 10);		// 地面の初期化
						MeshWallInit(pDevice, 100, 100, 10, 10);	// 壁の初期化
						BulletInit(pDevice, 50, 50);			// 弾の初期化
						ShadowInit(pDevice, 25, 25);				// 影の初期化
						PlayerInit(pDevice);						// プレイヤー初期化
						EnemyInit(pDevice);							// 敵の初期化
						EnemyLifeInit(pDevice);
						ExplosionInit(pDevice, 25, 25);				// 爆発の初期化
						EffectInit(pDevice, 25, 25);				// エフェクトの初期化
						bTitleInit = false;							// タイトルフラグ初期化
						bClearInit = false;							// クリアフラグ初期化
						bOverInit = false;							// オーバーフラグ初期化
						bGameInit = true;							// ゲーム初期化終了
					}
					else
					{
						if( nTimeCnt > 60)
						{
							g_nGameTime++;
							nTimeCnt = 0;
						}
						else
						{
							nTimeCnt++;
						}
						soundGame->Play(0,0,0);
						g_bStop = PlayerStop(g_bStop);
						CameraUpdate();								// カメラの更新
						if( g_bStop == false )
						{
							PlayerUpdate();							// プレイヤーの更新
							EnemyUpdate();							// 敵の更新
							EnemyLifeUpdate();
							BulletUpdate();							// 弾の更新
				   			ExplosionUpdate();						// 爆発の更新
							EffectUpdate();							// エフェクトの更新
						}
						//--------------------------
						// ゲーム画面じゃなかったら
						if(g_nSelect != GAME)
						{
     						FieldUninit();							// 地面破棄			
							PlayerUninit();							// プレイヤー破棄
							EnemyUninit();							// 敵破棄
							EnemyLifeUninit();
							MeshWallUninit();						// 壁破棄
							BulletUninit();							// 弾破棄
							ShadowUninit();							// 影破棄
							ExplosionUninit();						// 爆発破棄
							EffectUninit();							// エフェクト破棄
							if(soundGame != NULL)
							{
								soundGame->Release();
								soundGame = NULL;
							}
							bGameInit = false;
						}
					}
					break;
				case CLEAR:
					//---------------------------------
					// クリアが初期化されていなかったら
					if(bClearInit == false)
					{
						InitClear(pDevice);
						bTitleInit = false;							// タイトルフラグ初期化
						bOverInit = false;							// オーバーフラグ初期化
						bGameInit = false;							// ゲームフラグ初期化
						bClearInit = true;							// クリア初期化終了
					}
					else
					{
						UpdateClear();								// クリア更新
						//------------------------
						// クリアじゃなかったら
						if(g_nSelect != CLEAR)
						{
							UninitClear();
							bClearInit = false;
						}
					}
					break;
				case OVER:
					if(bOverInit == false)
					{
						InitOver(pDevice);
						bOverInit = true;
					}
					else
					{
						UpdateOver();
						if(g_nSelect != OVER)
						{
							UninitOver();
							bOverInit = false;
						}
					}
					break;

				case LANK:
					if( bLankInit == false )
					{
						InitLank(pDevice);
						bLankInit = true;
					}
					else
					{
						UpdateLank();
						if(g_nSelect != LANK)
						{
							UninitLank();
							bLankInit = false;
						}
					}
					break;
				default:
					continue;										// もう一度やり直す
				}

				//-------------------------------------------------------------
				// バックバッファのクリア
				pDevice->Clear
					( 0 , NULL ,
					 (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER) ,
					 D3DCOLOR_RGBA( 255 , 255 , 255 , 255) ,
					 1.0f, 0);			

				//-------------------------------------------------------------
				// 描画開始
				hr = pDevice->BeginScene();

				//---------------------------------------------------------
				// ここに描画処理
				if( SUCCEEDED(hr) )
				{
					switch(g_nSelect)
					{
					case TITLE:
						//-----------------------------------
						// タイトルが初期化されていたら
						if(bTitleInit == true)
						{
							DrawTitle(pDevice);					// タイトル描画
						}
						break;
					case EXPLAIN:
						if( bExplainInit == true )
						{
							DrawExplain(pDevice);
						}
						break;
					case GAME:
						DrawExplain(pDevice);
						//------------------------------------
						// ゲームが初期化されていたら
						if(bGameInit == true)
						{
							CameraDraw(pDevice);			// カメラ描画
							FieldDraw(pDevice);				// 地面描画
							PlayerDraw(pDevice);			// プレイヤー描画
							EnemyDraw(pDevice);				// 敵の描画
							EnemyLifeDraw(pDevice);
							MeshWallDraw(pDevice);			// 壁の描画
							BulletDraw(pDevice);			// 弾の描画
							ShadowDraw(pDevice);			// 影の描画
							EffectDraw(pDevice);			// エフェクト描画
							ExplosionDraw(pDevice);			// 爆発描画
						}			
						break;
					case CLEAR:
						//-------------------------------------
						// クリアが初期化されていたら
						if(bClearInit == true)
						{
							DrawClear(pDevice);					// クリア描画
						}
						break;
					case OVER:
						if(bOverInit == true)
						{
							DrawOver(pDevice);
						}
						break;
					case LANK:
						if(bLankInit == true)
						{
							DrawLank(pDevice);
						}
						break;
					default:
						continue;
					}
						
					//---------------------------------------------------------
					// 描画終了
					pDevice->EndScene();
				}

				//-------------------------------------------------------------
				// バックバッファとフロントバッファ入れ替え
				pDevice->Present( 
							NULL ,
							NULL ,
							NULL , 
							NULL );

				//-------------------------------------------------------------
				// FPSに関すること
				nFrameCount++;						// フレイムカウント
				SetFrameTime( nFrameCount );		// フレイムをセット
			}
		}
	}
	//-------------------------------------------------------------------------
	// 全開放
	UninitTitle();
	FieldUninit();
	PlayerUninit();
	EnemyUninit();
	MeshWallUninit();
	BulletUninit();
	ShadowUninit();
	ExplosionUninit();
	EffectUninit();
	FontAllUninit();
	EnemyLifeUninit();
	UninitClear();
	UninitTitle();
	UninitOver();

	//-------------------------------------------------------------------------
	// キー入力解放
	UninitInput();

	//-------------------------------------------------------------------------
	// デバイスの解放
	if( pDevice != NULL)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pD3D != NULL)
	{
		pD3D->Release();
		pD3D = NULL;
	}

	//-------------------------------------------------------------------------
	// ウィンドウクラス登録を解除
	UnregisterClass(
		CLASS_NAME ,
		wcex.hInstance);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	return (int)msg.wParam;
}

void GameSelectSet(int Select)
{
	g_nSelect = Select;
}

int GameTimerGet(void)
{
	return g_nGameTime;
}

bool GameStop(void)
{
	return g_bStop;
}

	

