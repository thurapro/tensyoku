//-----------------------------------------------------------------------------
//
// main処理 		[main.cpp]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "CScreen.h"
#include "main.h"
#include "manager.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
static int		g_nCountFPS = 0;			// FPSのカウンター

//-----------------------------------------------------------------------------
// メイン処理
//-----------------------------------------------------------------------------
void main(void)
{
	int nExecLastTime;
	int nFPSLastTime;
	int nCurrentTime;
	int nFrameCount;
	CManager *pManager = NULL;

	// 分解能を設定
	timeBeginPeriod(1);

	nExecLastTime = 
	nFPSLastTime = timeGetTime();
	nCurrentTime = 
	nFrameCount = 0;

	if(pManager == NULL)
	{
		pManager = new CManager();
		pManager->Init();
	}

	// カーソルOFF
	CUROFF();

	// ゲームメイン処理
	do{
		nCurrentTime = timeGetTime();
		if( ( nCurrentTime - nFPSLastTime ) >= 500 )
		{
			g_nCountFPS = nFrameCount * 1000 / (nCurrentTime - nFPSLastTime );
			nFPSLastTime = nCurrentTime;
			nFrameCount = 0;
		}
		if( ( nCurrentTime - nExecLastTime ) >= ( 1000 / 60 ) )
		{
			nExecLastTime = nCurrentTime;

			// 更新処理
			pManager->Update();

			// 描画処理
			pManager->Draw();

#ifdef _DEBUG		
			// FPS表示
			DispFPS();
#endif
			// FPS表示
			nFrameCount++;
		}
	}while(!INP( KEY_ESC ));

	// カーソルON
	CURON();

	// 終了処理
	pManager->Uninit();

	if(pManager != NULL)
	{
		delete pManager;
		pManager = NULL;
	}
	// 分解能を戻す
	timeEndPeriod(1);
}

//-------------------------------------------------------------------------------
// FPS画面表示
//-------------------------------------------------------------------------------
void DispFPS(void)
{
	LOCATE(1 , 1);
	printf("FPS = %d", g_nCountFPS );	// FPS描画
}




