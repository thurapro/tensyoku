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
#include "../hedder/Font.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define FONT_MAX (3)

//==========================================================================
// グローバル変数
//==========================================================================
static LPD3DXFONT g_pD3DFont[FONT_MAX] = {NULL};

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
void FontInit(	LPDIRECT3DDEVICE9 pDevice,
				INT		Height		,		// フォントの高さ
				UINT	Width		,		// フォントの幅
				UINT	Weight		,		// フォントの太さ
				LPCSTR	pFaceName	,		// フォント名保持
				INT		nType		)		// どこで使うか
{
	// 引数で持ってきたFontの代入
	D3DXCreateFont( pDevice	,		// デバイス
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
					&g_pD3DFont[nType] );

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
				INT	 A		,		// 透明度( 255は不透明 0は透明 )
				INT	 R		,		// 赤色の度合い
				INT	 G		,		// 緑色の度合い
				INT	 B		,		// 青色の度合い
				CHAR *str	,		// 表示したい文字列
				INT  nType )		// どこで使うか
{
	// 描画範囲　X軸( fLeft - fRight ),　Y軸( fBottom - fTop )
	RECT rect = { fLeft , fTop , fRight , fBottom };
	g_pD3DFont[nType]->DrawTextA(	NULL	,
							str		,
							-1		,
							&rect	,
							DT_LEFT	,
							D3DCOLOR_ARGB( R, G, B, A ) );
}


void FontUninit( INT nType )
{
	if( g_pD3DFont[nType] != NULL )
	{
		g_pD3DFont[nType]->Release();
		g_pD3DFont[nType] = NULL;
	}
}

void FontAllUninit(void)
{
	for(int i = 0; i < FONT_MAX; i++)
	{
		if( g_pD3DFont[i] != NULL )
		{
			g_pD3DFont[i]->Release();
			g_pD3DFont[i] = NULL;
		}
	}
}