//=============================================================================
//
// title処理 [title.cpp]  松尾　雄太
//
//=============================================================================

//=============================================================================
// ヘッダー読み込み
//=============================================================================
#include "../hedder/title.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2Dテクスチャー設定
#define TEX_INIT_X			(0.25f)
#define TEX_MAX				(1.0f)
#define ANIMECNT_MAX		(40)
#define TEX_SPEED_X			(0.25f)
#define TITLE_SOUND			(0)

//=============================================================================
// グローバル変数
//=============================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// 頂点バッファー
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// タイトル画像
static int g_nTime = 0;
static int g_faide = 255;
static LPDIRECTSOUNDBUFFER g_soundExplain;

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DVECTOR	vtx;						// 頂点座標
	float		rhw;						// 同次座標の逆数
	D3DCOLOR	diffuse;					// 色情報
	D3DXVECTOR2	tex;						// テクスチャー座標
}VERTEX_2D;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
static HRESULT MakeVertexExplain(LPDIRECT3DDEVICE9 pDevice);	// 頂点バッファー作成

//=============================================================================
// タイトル初期化
//=============================================================================
HRESULT InitExplain(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	g_nTime = 0;
	g_faide = 255;
	//------------------------
	// テクスチャーのロード
	hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Player.png" , &g_pD3DTex);
	
	//---------------------------------------
	// テクスチャーがロードできなかった場合
	if( FAILED(hr) )
	{
		return hr;
	}

	//----------------------------------------
	// 頂点作成
	hr = MakeVertexExplain(pDevice);

	//----------------------------------------
	// 頂点バッファーが作成できなかったら
	if( FAILED(hr) )
	{
		return hr;
	}

	return hr;
}

//=============================================================================
// タイトル破棄
//=============================================================================
void UninitExplain(void)
{
	if(g_pD3DVBXYZBuffer != NULL)
	{
		g_pD3DVBXYZBuffer->Release();
		g_pD3DVBXYZBuffer = NULL;
	}
	if(g_pD3DTex != NULL)
	{
		g_pD3DTex->Release();
		g_pD3DTex = NULL;
	}
}

//=============================================================================
// タイトル更新
//=============================================================================
void UpdateExplain(void)
{
	VERTEX_2D *pVtx;

	if(g_faide > 0)
	{
		g_faide -= 1;
	}
	else
	{
		GameSelectSet(GAME);
	}
	g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[1].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[2].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[3].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	g_pD3DVBXYZBuffer->Unlock();
}

//=============================================================================
// タイトル描画
//=============================================================================
void DrawExplain(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点フォーマットをセット
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// 頂点バッファーのセット
	pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	
	// テクスチャーセット
	pDevice->SetTexture(0, g_pD3DTex);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);

	// プリミティブ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// タイトルの頂点バッファー作成
//=============================================================================
HRESULT MakeVertexExplain(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	VERTEX_2D *pVtx;

	// 頂点バッファー作成
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&g_pD3DVBXYZBuffer,
									NULL);
	//-----------------------
	// 作成できなかったら
	if(FAILED(hr))
	{
		return hr;
	}

	// 頂点バッファーロック
	hr = g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);

	//-----------------------
	// ロックできなかったら
	if(FAILED(hr))
	{
		return hr;
	}

	// 頂点バッファー位置セット
	pVtx[0].vtx = D3DXVECTOR3(0, 0, 0);
	pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
	pVtx[2].vtx = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
	pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色情報
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャー座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ロック解除
	hr = g_pD3DVBXYZBuffer->Unlock();

	//-----------------------
	// ロック解除できなかったら
	if(FAILED(hr))
	{
		return hr;
	}
	return hr;
}	






