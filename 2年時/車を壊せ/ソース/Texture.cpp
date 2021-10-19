//============================================================================
//　インクルード
//============================================================================
#include <d3dx9.h>
#include <windows.h>
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Direct3DCreater.h"

//============================================================================
//　グローバル変数
//============================================================================
static LPDIRECT3DTEXTURE9	g_pD3DTex[TEXTUREMAX] = {NULL};
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer = NULL;	// XYZの頂点バッファ
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;		// インデックスバッファ

//============================================================================
//
// 関数名	:	TextLoad関数
//
// 戻り値	:	HRESULT型でロードしたテキスチャを返す
//
// 引数		:	テキスチャの名前(～.jpg , ～.png等),テキスチャ何枚目
//
// 機能		:	テキスチャをロード
//			
//============================================================================
HRESULT TextureLoad( char *str, int Numof)
{
	// ローカルHRESULT変数
	HRESULT hr;

	// 生成されたデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// テクスチャのロード
	hr = D3DXCreateTextureFromFile( pD3DDevice , str , &g_pD3DTex[Numof]);

	// テクスチャの中身がなければ
	if( FAILED( hr ) )
	{
		// テキスチャがなかった
		return (E_FAIL);
	}

	// テキスチャを返す
	return (S_OK);
}


//=============================================================================
//
// 関数名	:	TextureUnit関数
//
// 戻り値	:	なし
//
// 引数		:	テキスチャの番号
//
// 機能		:	テキスチャの解放
//			
//=============================================================================
void TextureUninit(int Numof)
{
	// もしテクスチャが解放されていなければ
	if(g_pD3DTex[Numof] != NULL)
	{
		// テクスチャの解放
		g_pD3DTex[Numof]->Release();

		// テクスチャの部分をNULLへ
		g_pD3DTex[Numof] = NULL;
	}
}

//==============================================================================
//
// 関数名	: GetD3DTexture関数
//
// 戻り値	: テクスチャのアドレス
//
// 引数		: テクスチャの番号
//
//===============================================================================
LPDIRECT3DTEXTURE9* GetD3DTexture( int Num )
{
	// テクスチャを送る
	return &g_pD3DTex[Num];
}