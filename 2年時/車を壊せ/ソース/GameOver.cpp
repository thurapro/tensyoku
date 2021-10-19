//=============================================================================
//
// FAILE NAME [Over.cpp]
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
#include "../hedder/Over.h"
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
static DRAWOVER				g_Over;
static LPDIRECTSOUNDBUFFER	g_lpOver = NULL;

//=============================================================================
//
//	関数名	:	OverInit
//	
//	戻り値	:	なし
//
//	引数	:	なし
//
//	機能	:	タイトルテクスチャーロード
//				タイトルサウンドロード
//				タイトルのそれぞれの初期値設定
//
//=============================================================================
void OverInit( void )
{
	// 画像のロード
	TextureLoad( "photo/Over.png" , OVERNUM );

	// 画像の位置設定
	g_Over.fOverPosX = 0;

	// 画像の位置設定
	g_Over.fOverPosY = 0;

	// 画像の幅設定
	g_Over.fOverWidth = SCREEN_WIDTH;

	// 画像の高さ設定
	g_Over.fOverHeight = SCREEN_HEIGHT;

	// 画像モーション最初の設定
	g_Over.fOverTexX0 = OVERTEXX0;

	// 画像モーション最初の設定
	g_Over.fOverTexY0 = OVERTEXY0;

	// 画像モーション最後の設定
	g_Over.fOverTexX1 = OVERTEXX1;

	// 画像モーション最後の設定
	g_Over.fOverTexY1 = OVERTEXY1;

	if( !SoundFileLoad( "sound/Over.wav" , OVERSOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_lpOver , OVERSOUND ) )
	{
		return ;
	}
}

//=============================================================================
//
//	関数名	:	OverUpdate
//	
//	戻り値	:	なし
//
//	引数	:	なし
//
//	機能	:	タイトルテクスチャーモーション更新
//
//=============================================================================
void OverUpdate( void )
{
	// プレイヤーコントロール
	PlayerControlJudg( );
}

void OverDraw( void )
{
	PrimitiveCreate( OVERID ,
					 KUNCLE ,
					 OVERNUM ,
					 0			,
					 g_Over.fOverPosX ,
					 g_Over.fOverPosY ,
					 g_Over.fOverWidth ,
					 g_Over.fOverHeight ,
					 g_Over.fOverTexX0 ,
					 g_Over.fOverTexY0 ,
					 g_Over.fOverTexX1 ,
					 g_Over.fOverTexY1 );

	g_lpOver->Play( 0 , 0 , 0 );
}

void OverUninit( void )
{
	TextureUninit( OVERNUM );

	if( g_lpOver != NULL )
	{
		g_lpOver->Release();
		g_lpOver = NULL;
	}
}
						

