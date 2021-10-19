//=========================================================================
//
// フォント表示 [font.cpp]
//
//学籍 10304 　氏名 松尾 雄太
//
//==========================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Direct3DCreater.h"
#include "../hedder/Font.h"
#include <d3dx9.h>
#include <windows.h>

//==========================================================================
// グローバル変数
//==========================================================================
static LPD3DXFONT g_pD3DFont = NULL;

//==========================================================================
//
// 関数名	: FontInit
//
// 機能		: フォントの初期化(クリエイト)
//
// 戻り値	: なし
//
// 引数		: なし
//
//==========================================================================
void FontInit(	INT		Height		,		// フォントの高さ
				UINT	Width		,		// フォントの幅
				UINT	Weight		,		// フォントの太さ
				LPCSTR	pFaceName	)		// フォント名保持
{

	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// 引数で持ってきたFontの代入
	D3DXCreateFont( pD3DDevice	,		// デバイス
					Height		,		// フォントの高さ
					Width		,		// フォントの幅
					Weight		,		// フォントの太さ
					0			,
					FALSE		,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					pFaceName	,		// フォント名保持
					&g_pD3DFont );

}

//==========================================================================
//
// 関数名	: FontDraw
//
// 機能		: フォントの描画
//
// 戻り値	: なし
//
// 引数		: なし
//
//==========================================================================
void FontDraw(	LONG fLeft,			// 左
				LONG fTop,			// 上
				LONG fRight,		// 右
				LONG fBottom,		// 下
				CHAR *str )			// 表示したい文字列
{
	// 描画範囲　X軸( fLeft - fRight ),　Y軸( fBottom - fTop )
	RECT rect = { fLeft , fTop , fRight , fBottom };
	g_pD3DFont->DrawTextA(	NULL	,
							str		,
							-1		,
							&rect	,
							DT_LEFT	,
							D3DCOLOR_ARGB( 255, 0, 0, 255 ) );
}


void FontUninit( void )
{
	if( g_pD3DFont != NULL )
	{
		g_pD3DFont->Release();
		g_pD3DFont = NULL;
	}
}