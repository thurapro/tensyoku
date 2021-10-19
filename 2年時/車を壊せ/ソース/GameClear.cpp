//=============================================================================
//
// FAILE NAME [Title.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: タイトル表示
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Clear.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Texture.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/Judgment.h"
#include <d3dx9.h>
#include <dsound.h>

//=============================================================================
// グローバル変数
//=============================================================================
static DRAWCLEAR g_Clear;
static LPDIRECTSOUNDBUFFER g_lpClear = NULL;
static BOOL g_bClearCLEARTEXLoad = FALSE;
static BOOL g_bClearSouLoad = FALSE;

//=============================================================================
//
//	関数名	:	TitleInit
//	
//	戻り値	:	なし
//
//	引数	:	なし
//
//	機能	:	クリアテクスチャーロード
//				クリアサウンドロード
//				クリアのそれぞれの初期値設定
//
//=============================================================================
void ClearInit( void )
{
	if( g_bClearCLEARTEXLoad == FALSE )
	{
		// 画像のロード
		TextureLoad( "photo/GameClear.png" , CLEARNUM );
		g_bClearCLEARTEXLoad = TRUE;
	}

	// 画像の位置設定
	g_Clear.fClearPosX = 0;

	// 画像の位置設定
	g_Clear.fClearPosY = 0;

	// 画像の幅設定
	g_Clear.fClearWidth = SCREEN_WIDTH;

	// 画像の高さ設定
	g_Clear.fClearHeight = SCREEN_HEIGHT;

	// 画像モーション最初の設定
	g_Clear.fClearCLEARTEXX0 = CLEARTEXX0;

	// 画像モーション最初の設定
	g_Clear.fClearCLEARTEXY0 = CLEARTEXY0;

	// 画像モーション最後の設定
	g_Clear.fClearCLEARTEXX1 = CLEARTEXX1;

	// 画像モーション最後の設定
	g_Clear.fClearCLEARTEXY1 = CLEARTEXY1;



		if( !SoundFileLoad( "sound/Clear.wav" , CLEARSOUND ) )
		{
			return ;
		}

		if( !CreateSoundBuffer( &g_lpClear , CLEARSOUND ) )
		{
			return ;
		}

		g_bClearSouLoad = TRUE;
	

}

//=============================================================================
//
//	関数名	:	TitleUpdate
//	
//	戻り値	:	なし
//
//	引数	:	なし
//
//	機能	:	タイトルテクスチャーモーション更新
//
//=============================================================================
void ClearUpdate( void )
{
	PlayerControlJudg();

}

void ClearDraw( void )
{
	PrimitiveCreate( CLEARID ,
					 KUNCLE ,
					 CLEARNUM ,
					 0			,
					 g_Clear.fClearPosX ,
					 g_Clear.fClearPosY ,
					 g_Clear.fClearWidth ,
					 g_Clear.fClearHeight ,
					 g_Clear.fClearCLEARTEXX0 ,
					 g_Clear.fClearCLEARTEXY0 ,
					 g_Clear.fClearCLEARTEXX1 ,
					 g_Clear.fClearCLEARTEXY1 );

	g_lpClear->Play( 0 , 0 , 0 );
}

void ClearUninit( void )
{
	g_bClearCLEARTEXLoad = FALSE;

	g_bClearSouLoad = FALSE;

	TextureUninit( CLEARNUM );

	if( &g_lpClear != NULL )
	{
		g_lpClear->Release();
		g_lpClear = NULL;
	}
}
						

