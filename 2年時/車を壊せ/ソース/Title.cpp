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
#include "../hedder/Title.h"
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
static DRAWTITLE g_Title;
static int g_TitleTimer = 0;
static int g_TitleWate = 0;
static LPDIRECTSOUNDBUFFER g_lpTitle = NULL;

//=============================================================================
//
//	関数名	:	TitleInit
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
void TitleInit( void )
{
	// 画像のロード
	TextureLoad( "photo/Title.png" , TITLENUM );

	// 画像の位置設定
	g_Title.fTitlePosX = 0;

	// 画像の位置設定
	g_Title.fTitlePosY = 0;

	// 画像の幅設定
	g_Title.fTitleWidth = SCREEN_WIDTH;

	// 画像の高さ設定
	g_Title.fTitleHeight = SCREEN_HEIGHT;

	// 画像モーション最初の設定
	g_Title.fTitleTexX0 = TEXX0;

	// 画像モーション最初の設定
	g_Title.fTitleTexY0 = TEXY0;

	// 画像モーション最後の設定
	g_Title.fTitleTexX1 = TEXX1;

	// 画像モーション最後の設定
	g_Title.fTitleTexY1 = TEXY1;

	if( !SoundFileLoad( "sound/Title.wav" , TITLESOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_lpTitle , TITLESOUND ) )
	{
		return ;
	}

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
void TitleUpdate( void )
{
	// プレイヤーコントロール
	PlayerControlJudg();

	// 1秒たったら
	if( g_TitleTimer == TITLEWATE )
	{
		// テクスチャ座標変更
		g_Title.fTitleTexX0 += TEXX1;

		// テクスチャ座標変更
		g_Title.fTitleTexX1 += TEXX1;

		// タイマーをリセット
		g_TitleTimer = 0;
	}

	// タイトルのテクスチャ座標( X , Y )が最大数を超えていたら
	if( g_Title.fTitleTexX1 == TEXXMAX && g_Title.fTitleTexY1 == TEXYMAX )
	{
		// テクスチャ座標を初期化
		g_Title.fTitleTexX0 = TEXX0;

		// テクスチャ座標を初期化
		g_Title.fTitleTexY0 = TEXY0;

		// テクスチャ座標を初期化
		g_Title.fTitleTexX1 = TEXX1;

		// テクスチャ座標を初期化
		g_Title.fTitleTexY1 = TEXY1;	
	}

	// もし
	else if( g_Title.fTitleTexX0 < 0.5f && g_Title.fTitleTexX1 > 1.f )
	{
		g_Title.fTitleTexX0 = TEXX0;
		g_Title.fTitleTexY0 = TEXY1;
		g_Title.fTitleTexX1 = TEXX1;
		g_Title.fTitleTexY1 += TEXY1;
	}

	g_TitleTimer++;

}

void TitleDraw( void )
{
	PrimitiveCreate( TITLEID ,
					 KUNCLE ,
					 TITLENUM ,
					 0			,
					 g_Title.fTitlePosX ,
					 g_Title.fTitlePosY ,
					 g_Title.fTitleWidth ,
					 g_Title.fTitleHeight ,
					 g_Title.fTitleTexX0 ,
					 g_Title.fTitleTexY0 ,
					 g_Title.fTitleTexX1 ,
					 g_Title.fTitleTexY1 );

	g_lpTitle->Play( 0 , 0 , 0 );
}

void TitleUninit( void )
{
	TextureUninit( TITLENUM );

	if( g_lpTitle != NULL )
	{
		g_lpTitle->Release();
		g_lpTitle = NULL;
	}
}
						

