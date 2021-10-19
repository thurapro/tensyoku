//=============================================================================
// 番号処理[number.h]
//
// 製作者 : 松尾 雄太
//
// 機能 :  スコアー・タイマーなど 
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "manager.h"
#include "main.h"
#include "debugproc.h"
#include "renderer.h"
#include "data.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "number.h"

//=============================================================================
// 関数名	: CNumber
// 引数		: なし
// 戻り値	: なし
// 機能		: インスタンス生成
//=============================================================================
CNumber::CNumber(void)
{
	// インスタンス生成
	m_pVertexBuffer = NULL;
	m_nNumber		= -1;
}

//=============================================================================
// 関数名	: ~CNumber
// 引数		: なし
// 戻り値	: なし
// 機能		: インスタンス破棄
//=============================================================================
CNumber::~CNumber(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: HREUSLT	正常,エラー結果
// 引数		: 位置の左上、右上、左下、右下, テクスチャ番号
// 機能		: 番号作成
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, 
						D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom,
						unsigned int nTexNum)
{
	HRESULT hr;
	CNumber *pNumber = NULL;
	pNumber = NEW CNumber;
	hr = pNumber->Init(fPosLeftTop, fPosRightTop, fPosLeftBottom, fPosRightBottom, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pNumber;
}

//=============================================================================
// 関数名	: Create
// 戻り値	: HREUSLT	正常,エラー結果
// 引数		: 位置の左上、右上、幅, 高さ, テクスチャ番号
// 機能		: 番号作成
//=============================================================================
CNumber *CNumber::Create(float fPosX, float fPosY, float fWidth, float fHeight,
						unsigned int nTexNum)
{
	HRESULT hr;
	CNumber *pNumber = NULL;
	pNumber = NEW CNumber;
	hr = pNumber->Init(fPosX, fPosY, fWidth, fHeight, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pNumber;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HREUSLT	正常,エラー結果
// 引数		: テクスチャ座標の左上、右上、左下、右下
// 機能		: 初期化
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop,
					D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom,
					unsigned int nTexNum )
{
	HRESULT hr;
	CData	*pData = NULL;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData	= CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData	= CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData	= CResult::GetData();
		break;
	case CManager::MODE_RANKING:
		pData	= CRanking::GetData();
		break;
	}
	
	if( nTexNum > pData->GetTexture()->GetTextureNum() ||
		nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = pData->GetTexture()->GetTexture(nTexNum);
	}

	if( m_pTexture == NULL )
	{
		return E_FAIL;
	}

	// 頂点作成
	hr = MakeVerTex(fPosLeftTop, fPosRightTop, fPosLeftBottom, fPosRightBottom);
	
	//-----------------------
	// 頂点が作成出来なければ
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HREUSLT	正常,エラー結果
// 引数		: 位置 (X, Y) 大きさ( 幅, 高さ ) 
// 機能		: 初期化
//=============================================================================
HRESULT CNumber::Init(float fPosX, float fPosY, float fWidth, float fHeight,
					unsigned int nTexNum)
{
	HRESULT hr;
	CData	*pData = NULL;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData	= CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData	= CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData	= CResult::GetData();
		break;
	case CManager::MODE_RANKING:
		pData	= CRanking::GetData();
		break;
	}
	
	if( nTexNum > pData->GetTexture()->GetTextureNum() ||
		nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(nTexNum);
	}

	if( m_pTexture == NULL )
	{
		return E_FAIL;
	}

	// 頂点作成
	hr = MakeVerTex(fPosX, fPosY, fWidth, fHeight);
	
	//-----------------------
	// 頂点が作成出来なければ
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}
				

//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点フォーマットをセット
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// 頂点バッファーのセット
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
	
	// テクスチャーセット
	pDevice->SetTexture(0, m_pTexture);

	// プリミティブ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点作成
//=============================================================================
HRESULT CNumber::MakeVerTex(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, 
							D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファー作成
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// 作成できなかったら
	if(FAILED(hr))
	{
		return hr;
	}

	// 頂点バッファーロック
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// 頂点バッファー位置セット
	pVtx[0].vtx = fPosLeftTop;
	pVtx[1].vtx = fPosRightTop;
	pVtx[2].vtx = fPosLeftBottom;
	pVtx[3].vtx = fPosRightBottom;
	
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
	pVtx[1].tex = D3DXVECTOR2(1.0f / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f, 1.0f);

	// ロック解除
	hr = m_pVertexBuffer->Unlock();
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 頂点作成
//=============================================================================
HRESULT CNumber::MakeVerTex(float fPosX, float fPosY, float fWidth, float fHeight)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファー作成
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// 作成できなかったら
	if(FAILED(hr))
	{
		return hr;
	}

	// 頂点バッファーロック
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// 頂点バッファー位置セット
	pVtx[0].vtx = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(fPosX, fHeight, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	
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
	pVtx[1].tex = D3DXVECTOR2(1.0f / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f, 1.0f);

	// ロック解除
	hr = m_pVertexBuffer->Unlock();
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 関数名	: SetNumber
// 戻り値	: 番号
// 引数値	: なし
// 機能		: 番号設定
//=============================================================================
void CNumber::SetNumberTexture(unsigned int nNumber)
{
	VERTEX_2D *pVtx;
	
	float fNumber	= nNumber * 0.1f;
	float fLeftTex	= fNumber;
	m_nNumber		= nNumber;

	// ロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);


	// テクスチャー座標設定
	pVtx[0].tex.x = fNumber;
	pVtx[1].tex.x = fNumber + 0.1f;
	pVtx[2].tex.x = fNumber;
	pVtx[3].tex.x = fNumber + 0.1f;

	if( pVtx[0].tex.x > 0.9f && pVtx[1].tex.x > 1.0f)
	{
		pVtx[0].tex.x = 0.0f;
		pVtx[1].tex.x = 1.0f / 10.0f;
		pVtx[2].tex.x = 0.0f;
		pVtx[3].tex.x = 1.0f / 10.0f;
	}


	// ロック解除
	m_pVertexBuffer->Unlock();
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y ) 大きさ( 幅, 高さ )
// 機能		: 位置を設定
//=============================================================================
void CNumber::SetPosition(float fPosX, float fPosY,
						float fWidth, float fHeight)
{
	VERTEX_2D	*pVtx;					// 頂点作成用の格納変数
	
	fWidth += fPosX;
	fHeight += fPosY;

	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点バッファー位置セット
	pVtx[0].vtx = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}

//=============================================================================
// 関数名	: SetPosHeight
// 戻り値	: なし
// 引数値	: 高さ設定 ( 赤, 緑, 青, 透明度 )
// 機能		: 高さ設定
//=============================================================================
void CNumber::SetPosHeight(float fPosY, float fHeight)
{
	VERTEX_2D	*pVtx;					// 頂点作成用の格納変数
	
	fHeight += fPosY;

	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点バッファー位置セット
	pVtx[0].vtx.y = fPosY;
	pVtx[1].vtx.y = fPosY;
	pVtx[2].vtx.y = fHeight;
	pVtx[3].vtx.y = fHeight;

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}

//=============================================================================
// 関数名	: SetNumColor
// 戻り値	: なし
// 引数値	: 色設定 ( 赤, 緑, 青, 透明度 )
// 機能		: 番号の色設定
//=============================================================================
void CNumber::SetNumColor(int nR, int nG, int nB, int nA)
{
	VERTEX_2D	*pVtx;				// 頂点作成用の格納変数
	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[1].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[2].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[3].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}