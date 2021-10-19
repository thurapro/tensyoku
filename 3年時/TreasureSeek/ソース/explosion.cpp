//=============================================================================
// 弾処理 [bullet.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: 弾
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "explosion.h"

//=============================================================================
// 関数名	: CExplosion
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾インスタンス生成
//=============================================================================
CExplosion::CExplosion(int nPriority, OBJTYPE objType):CBillboard(nPriority, objType)
{
	// インスタンス生成
}

//=============================================================================
// 関数名	: ~CExplosion
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾インスタンス破棄
//=============================================================================
CExplosion::~CExplosion(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾生成
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,
								USHORT nTexNum)
{
	HRESULT hr;
	CExplosion *pExplosion = NULL;
	if( pExplosion == NULL )
	{
		pExplosion = NEW CExplosion;
		hr = pExplosion->Init(pos, fWidth, fHeight, nTexNum);
		if( FAILED(hr) )
		{
			return NULL;
		}
	}
	return pExplosion;
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾生成
//=============================================================================
CExplosion *CExplosion::Create(float fPosX, float fPosY, float fPosZ, float fWidth, float fHeight,
								USHORT nTexNum)
{
	HRESULT hr;
	CExplosion *pExplosion = NULL;
	if( pExplosion == NULL )
	{
		pExplosion = NEW CExplosion;
		hr = pExplosion->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, nTexNum);
		if( FAILED(hr) )
		{
			return NULL;
		}
	}
	return pExplosion;
}


//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: float fWidth : 弾の幅
//			: float fHeight: 弾の高さ	テクスチャ番号
// 機能		: 弾初期化
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fWidth, float fHeight,
						USHORT nTexNum)
{
	HRESULT hr;
	pos.y = 10;
	hr = CBillboard::Init(fWidth, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: float fWidth : 弾の幅
//			: float fHeight: 弾の高さ	テクスチャ番号
// 機能		: 弾初期化
//=============================================================================
HRESULT CExplosion::Init(float fPosX, float fPosY, float fPosZ, float fWidth, float fHeight,
						USHORT nTexNum)
{
	HRESULT hr;
	hr = CBillboard::Init(fWidth, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}


//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾更新処理
//=============================================================================
void CExplosion::Update(void)
{
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: 弾の描画
//=============================================================================
void CExplosion::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
	pDevice->SetRenderState( D3DRS_ALPHAREF , 253 );
	pDevice->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
	CBillboard::Draw();
	pDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
}
