//=============================================================================
// メッシュ3Dオブジェクト処理 [scene3D.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: メッシュの多い3Dオブジェクトを作成
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "sceneline.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)		// 自由に設定できる頂点フォーマット
#define UPSTARTINm_POINT	(0)																// 上の原点
#define DOWNSTARTINm_POINT	(25)															// 下の原点
#define ANGLE_INIT			(180)															// 初期角度
#define INDEX_MAX			(20)

//=============================================================================
//	関数名	: CScene3D
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス生成
//=============================================================================
CSceneLine::CSceneLine(int nPriority):CScene(nPriority)
{

}

//=============================================================================
//	関数名	: ~CScene3D
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CSceneLine::~CSceneLine(void)
{
	// インスタンス破棄
}

HRESULT CSceneLine::Init(void)
{
	return S_OK;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: なし
//	引数	: なし
//	機能	: 3Dオブジェクトの初期化
//=============================================================================
HRESULT CSceneLine::Init(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	///// 3Dオブジェクト初期化処理開始 /////
	//--- 変数宣言 ---//
	HRESULT hr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き初期化
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさ初期化

	hr = MakeVerTex(startPoint,  endPoint, nRed, nGreen,  nBlue,  nAlpha);
	if(FAILED(hr))
	{
		return hr;
	}
	return hr;
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: 3Dオブジェクトの破棄
//=============================================================================
void CSceneLine::Uninit(void)
{
	if(m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	Release();
}

//=============================================================================
//	関数名	: Update
//	引数	: なし
//	機能	: 3Dオブジェクトの更新
//=============================================================================
void CSceneLine::Update(void)
{
}

//=============================================================================
//	関数名	: Draw
//	引数	: なし
//	機能	: 3Dオブジェクトの描画
//			: 大きさ反映
//			: 向き反映
//			: 場所反映
//			: ワールドマトリックスの設定
//			: 頂点情報設定
//			: テクスチャセット
//=============================================================================
void CSceneLine::Draw(void)
{
	///// 3Dオブジェクトの描画処理開始 /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//--- 変数宣言 ---//
	D3DXMATRIX mtxScl;		// スケールマトリックス
	D3DXMATRIX mtxRot;		// ロットマトリックス
	D3DXMATRIX mtxTrans;	// トランスマトリックス
	
	D3DXMatrixIdentity(&m_mtxWorld);					// ワールドマトリックス初期化

	//*********************************
	// スケール反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
		
	//*********************************
	// 回転反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//*********************************
	// 移動反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//-------------------------------------------------------------------------
	// ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld );	

	pDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	///// 頂点情報設定 /////
	pDevice->SetFVF(FVF_VERTEX_3D);

	///// 頂点バッファセット /////
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	// プリミティブ表示
	pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 1);

	pDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
}

//=============================================================================
//	関数名	: MakeVerTexCylinder
//	戻り値	: HRESULT
//	引数	: なし
//	機能	: 3Dオブジェクトの頂点を作る
//=============================================================================
HRESULT CSceneLine::MakeVerTex(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	///// 共通変数宣言 /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	///// 頂点用変数宣言 /////
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点

	//---------------------------------------------------------------------
	// 頂点バッファ作成処理
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 2 ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	//-------------------------------------------------------------------------
	// 頂点バッファのロック
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	pVtx[0].vtx = startPoint;
	pVtx[1].vtx = D3DXVECTOR3( (endPoint.x * 10) + startPoint.x, (endPoint.y * 10) + startPoint.y, (endPoint.z * 10) + startPoint.z);

	for(int i = 0; i < 2; i++)
	{
		//-------------------------------------------------------------------------
		// 向きの設定if( FAILED(hr) )
		pVtx[i].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		//---------------------------------------------------------------------
		// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
		pVtx[i].diffuse = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	}

	//-------------------------------------------------------------------------
	// 頂点バッファのロック解
	m_pVertexBuffer->Unlock();

	
	// 作成成功
	return (S_OK);
}

//=============================================================================
// 3D作成
//=============================================================================
CSceneLine *CSceneLine::Create(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	CSceneLine *pSceneLine;
	pSceneLine = NEW CSceneLine;
	pSceneLine->Init(startPoint,  endPoint, nRed, nGreen,  nBlue,  nAlpha);
	return pSceneLine;
}

