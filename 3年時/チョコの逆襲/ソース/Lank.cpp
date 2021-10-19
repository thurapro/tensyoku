//=============================================================================
//
// title処理 [title.cpp]  松尾　雄太
//
//=============================================================================

//=============================================================================
// ヘッダー読み込み
//=============================================================================
#include "../hedder/Lank.h"

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
static Lank g_Lank;								// タイトル変数
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// 頂点バッファー
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// タイトル画像
static int g_nAnimeCnt = 0;
static LPDIRECTSOUNDBUFFER g_soundLank;
static int g_nGameTimer;
static int g_nLank[3];
static bool g_bLank = false;

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
static HRESULT MakeVertexLank(LPDIRECT3DDEVICE9 pDevice);	// 頂点バッファー作成

//=============================================================================
// タイトル初期化
//=============================================================================
HRESULT InitLank(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	//g_Lank.fPosX = 0.0f;						// 画像のX軸位置
	//g_Lank.fPosY = 0.0f;						// 画像のY軸位置
	//g_Lank.fWidth = (float)SCREEN_WIDTH;		// 画像の幅設定
	//g_Lank.fHeight = (float)SCREEN_HEIGHT;		// 画像の高さ設定
	//g_Lank.fTexX0 = 0.0f;						// 画像頂点
	//g_Lank.fTexY0 = 0.0f;						// 画像頂点
	//g_Lank.fTexX1 = TEX_INIT_X;						// 画像頂点
	//g_Lank.fTexY1 = 1.0f;						// 画像頂点
	//g_Lank.fMoveX = TEX_SPEED_X;						// 画像の動く速度
	//g_Lank.fMoveY = 0.0f;						// 画像の動く速度
	//g_nAnimeCnt = 0;
	//SoundFileLoad( "DATA/Sound/Clear.wav" , LANK );
	//CreateSoundBuffer(&g_soundLank, LANK);

	//if( g_bLank == false )
	//{
	//	for( int i = 0; i < 3; i++)
	//	{
	//		g_nLank[i] = 0;
	//	}
	//	g_bLank = true;
	//}
	////------------------------
	//// テクスチャーのロード
	//hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Lank.png" , &g_pD3DTex);
	//
	////---------------------------------------
	//// テクスチャーがロードできなかった場合
	//if( FAILED(hr) )
	//{
	//	return hr;
	//}

	////----------------------------------------
	//// 頂点作成
	//hr = MakeVertexLank(pDevice);

	////----------------------------------------
	//// 頂点バッファーが作成できなかったら
	//if( FAILED(hr) )
	//{
	//	return hr;
	//}

	return hr;
}

//=============================================================================
// タイトル破棄
//=============================================================================
void UninitLank(void)
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
	if(g_soundLank != NULL)
	{
		g_soundLank->Release();
		g_soundLank = NULL;
	}
}

//=============================================================================
// タイトル更新
//=============================================================================
void UpdateLank(void)
{
	//VERTEX_2D *pVtx;
	//// 更新
	//if( KeyPush(DIK_RETURN) )
	//{
	//	GameSelectSet(TITLE);
	//}
	//else
	//{
	//	if( g_nAnimeCnt > ANIMECNT_MAX )
	//	{
	//		if( g_Lank.fTexX1 < TEX_MAX )
	//		{
	//			g_Lank.fTexX0 += g_Lank.fMoveX;
	//			g_Lank.fTexX1 += g_Lank.fMoveX;
	//		}
	//		else
	//		{
	//			g_Lank.fTexX0 += g_Lank.fMoveX;
	//			g_Lank.fTexX1 += g_Lank.fMoveX;
	//		}
	//		g_nAnimeCnt = 0;
	//	}
	//	else
	//	{
	//		g_nAnimeCnt++;
	//	}
	//	g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
	//	pVtx[0].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY0);
	//	pVtx[1].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY0);
	//	pVtx[2].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY1);
	//	pVtx[3].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY1);
	//	g_pD3DVBXYZBuffer->Unlock();
	//}
	//g_soundLank->Play(0,0,0);
}

//=============================================================================
// タイトル描画
//=============================================================================
void DrawLank(LPDIRECT3DDEVICE9 pDevice)
{
	//char strKing[1024] = "1位 : ";
	//char strSecond[1024] = "2位 : ";
	//char strTherd[1024] = "3位 : ";

	//char strChangeKing[40] = {NULL};
	//char strChangeSecond[50] = {NULL};
	//char strChangeTherd[50] = {NULL};

	//g_nGameTimer = GameTimerGet();

	//for( int i = 0; i < 3; i++ )
	//{
	//	g_nLank[i] = g_nGameTimer;
	//	break;
	//}
	//// 頂点フォーマットをセット
	//pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	//
	//// 頂点バッファーのセット
	//pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	//
	//// テクスチャーセット
	//pDevice->SetTexture(0, g_pD3DTex);

	//// プリミティブ
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//itoa(g_nLank[0], strChangeKing, 10);
	//itoa(g_nLank[1], strChangeSecond, 10);
	//itoa(g_nLank[2], strChangeTherd, 10);

	//strcat(strKing, strChangeKing);
	//strcat(strSecond, strChangeSecond);
	//strcat(strTherd, strChangeTherd);

	//strcat(strKing, "秒");
	//strcat(strSecond, "秒");
	//strcat(strTherd, "秒");

	//FontDraw(250, 40, SCREEN_WIDTH, SCREEN_HEIGHT, strKing);
	//FontDraw(250, 100, SCREEN_WIDTH, SCREEN_HEIGHT, strSecond);
	//FontDraw(250, 160, SCREEN_WIDTH, SCREEN_HEIGHT, strTherd);
}

//=============================================================================
// タイトルの頂点バッファー作成
//=============================================================================
HRESULT MakeVertexLank(LPDIRECT3DDEVICE9 pDevice)
{
	//HRESULT hr;
	//VERTEX_2D *pVtx;

	//// 頂点バッファー作成
	//hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
	//								D3DUSAGE_WRITEONLY,
	//								FVF_VERTEX_2D_TEX,
	//								D3DPOOL_MANAGED,
	//								&g_pD3DVBXYZBuffer,
	//								NULL);
	////-----------------------
	//// 作成できなかったら
	//if(FAILED(hr))
	//{
	//	return hr;
	//}

	//// 頂点バッファーロック
	//hr = g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);

	////-----------------------
	//// ロックできなかったら
	//if(FAILED(hr))
	//{
	//	return hr;
	//}

	//// 頂点バッファー位置セット
	//pVtx[0].vtx = D3DXVECTOR3(g_Lank.fPosX, g_Lank.fPosY, 0);
	//pVtx[1].vtx = D3DXVECTOR3(g_Lank.fWidth, g_Lank.fPosY, 0);
	//pVtx[2].vtx = D3DXVECTOR3(g_Lank.fPosX,g_Lank.fHeight, 0);
	//pVtx[3].vtx = D3DXVECTOR3(g_Lank.fWidth, g_Lank.fHeight, 0);
	//
	//// rhwの設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// 色情報
	//pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// テクスチャー座標設定
	//pVtx[0].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY0);
	//pVtx[1].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY0);
	//pVtx[2].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY1);
	//pVtx[3].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY1);

	//// ロック解除
	//hr = g_pD3DVBXYZBuffer->Unlock();

	////-----------------------
	//// ロック解除できなかったら
	//if(FAILED(hr))
	//{
	//	return hr;
	//}
	//return hr;
}	






