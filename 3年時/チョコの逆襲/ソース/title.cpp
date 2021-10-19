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
static Title g_Title;								// タイトル変数
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// 頂点バッファー
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// タイトル画像
static int g_nAnimeCnt = 0;
static LPDIRECTSOUNDBUFFER g_soundTitle;

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
static HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);	// 頂点バッファー作成


//=============================================================================
// タイトル初期化
//=============================================================================
HRESULT InitTitle(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	g_Title.fPosX = 0.0f;						// 画像のX軸位置
	g_Title.fPosY = 0.0f;						// 画像のY軸位置
	g_Title.fWidth = (float)SCREEN_WIDTH;		// 画像の幅設定
	g_Title.fHeight = (float)SCREEN_HEIGHT;		// 画像の高さ設定
	g_Title.fTexX0 = 0.0f;						// 画像頂点
	g_Title.fTexY0 = 0.0f;						// 画像頂点
	g_Title.fTexX1 = TEX_INIT_X;						// 画像頂点
	g_Title.fTexY1 = 1.0f;						// 画像頂点
	g_Title.fMoveX = TEX_SPEED_X;						// 画像の動く速度
	g_Title.fMoveY = 0.0f;						// 画像の動く速度
	g_nAnimeCnt = 0;
	SoundFileLoad( "DATA/Sound/Title.wav" , TITLE_SOUND );
	CreateSoundBuffer(&g_soundTitle, TITLE_SOUND);

	//------------------------
	// テクスチャーのロード
	hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Title.png" , &g_pD3DTex);
	
	//---------------------------------------
	// テクスチャーがロードできなかった場合
	if( FAILED(hr) )
	{
		return hr;
	}

	//----------------------------------------
	// 頂点作成
	hr = MakeVertexTitle(pDevice);

	//----------------------------------------
	// 頂点バッファーが作成できなかったら
	if( FAILED(hr) )
	{
		return hr;
	}

	g_soundTitle->Play(0,0,0);

	return hr;
}

//=============================================================================
// タイトル破棄
//=============================================================================
void UninitTitle(void)
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
	if(g_soundTitle != NULL)
	{
		g_soundTitle->Release();
		g_soundTitle = NULL;
	}
}

//=============================================================================
// タイトル更新
//=============================================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	// 更新
	if( KeyPush(DIK_RETURN) )
	{
		GameSelectSet(GAME);
	}
	else
	{
		if( g_nAnimeCnt > ANIMECNT_MAX )
		{
			if( g_Title.fTexX1 < TEX_MAX )
			{
				g_Title.fTexX0 += g_Title.fMoveX;
				g_Title.fTexX1 += g_Title.fMoveX;
			}
			else
			{
				g_Title.fTexX0 += g_Title.fMoveX;
				g_Title.fTexX1 += g_Title.fMoveX;
			}
			g_nAnimeCnt = 0;
		}
		else
		{
			g_nAnimeCnt++;
		}
		g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY0);
		pVtx[1].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY0);
		pVtx[2].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY1);
		pVtx[3].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY1);
		g_pD3DVBXYZBuffer->Unlock();
	}

}

//=============================================================================
// タイトル描画
//=============================================================================
void DrawTitle(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点フォーマットをセット
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// 頂点バッファーのセット
	pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	
	// テクスチャーセット
	pDevice->SetTexture(0, g_pD3DTex);

	// プリミティブ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// タイトルの頂点バッファー作成
//=============================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
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
	pVtx[0].vtx = D3DXVECTOR3(g_Title.fPosX, g_Title.fPosY, 0);
	pVtx[1].vtx = D3DXVECTOR3(g_Title.fWidth, g_Title.fPosY, 0);
	pVtx[2].vtx = D3DXVECTOR3(g_Title.fPosX,g_Title.fHeight, 0);
	pVtx[3].vtx = D3DXVECTOR3(g_Title.fWidth, g_Title.fHeight, 0);
	
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
	pVtx[0].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY0);
	pVtx[1].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY0);
	pVtx[2].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY1);
	pVtx[3].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY1);

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






