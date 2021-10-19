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
#include "logo.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "data.h"
#include "scene3D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 自由に設定できる頂点フォーマット
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
CScene3D::CScene3D(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// インスタンス生成
	m_pTexture = NULL;							// テクスチャ初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き初期化
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさ初期化
	m_nTexNum = -1;
}

//=============================================================================
//	関数名	: ~CScene3D
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CScene3D::~CScene3D(void)
{
	// インスタンス破棄
}

//=============================================================================
//	関数名	: Create
//	戻り値	: なし
//	引数	: 位置 (X, Y, Z) 大きさ( 幅, 高さ, 奥行 ), テクスチャ番号
//	機能	: 3Dオブジェクトの作成
//=============================================================================
CScene3D *CScene3D::Create(float fPosX, float fPosY, float fPosZ, 
							float fWidth, float fHeight, float fLength,
							unsigned int nTexNum)
{
	HRESULT hr;						// エラーチェック
	CScene3D *pScene3D;				// 3Dオブジェクト
	pScene3D = NEW CScene3D;		// 3Dオブジェクトインスタンス生成

	hr = pScene3D->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength ,nTexNum);	// 3Dオブジェクト初期化
	if( FAILED(hr) )
	{
		// 3Dオブジェクト作成に失敗
		return NULL;				// エラーコード
	}
	return pScene3D;				// 正常コード
}

//=============================================================================
//	関数名	: Init
//	戻り値	: なし
//	引数	: なし
//	機能	: 3Dオブジェクトの初期化
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: なし
//	引数	: 位置 (X, Y, Z) 大きさ( 幅, 高さ, 奥行 ), テクスチャ番号
//	機能	: 3Dオブジェクトの初期化
//=============================================================================
HRESULT CScene3D::Init(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						unsigned int nTexNum)
{
	///// 3Dオブジェクト初期化処理開始 /////

	//--- 変数宣言 ---//
	HRESULT hr;
	CData	 *pData = NULL;			// データ
	CTexture *pTex	= NULL;			// テクスチャ

	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// 位置初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き初期化
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさ初期化

	switch( CManager::GetMode() )
	{
	case CManager::MODE_LOGO:				// ロゴの場合
		pData	= CLogo::GetData();			// ロゴからデータ取得
		pTex	= pData->GetTexture();		// テクスチャ取得
		break;

	case CManager::MODE_TITLE:				// タイトルの場合
		pData = CTitle::GetData();			// タイトルからデータ取得
		pTex = pData->GetTexture();			// テクスチャ取得
		break;

	case CManager::MODE_TUTORIAL:			// チュートリアルの場合
		pData	= CTutorial::GetData();		// チュートリアルからデータ取得
		pTex	= pData->GetTexture();		// テクスチャ取得
		break;

	case CManager::MODE_GAME:				// ゲームの場合
		pData = CGame::GetData();			// ゲームからデータ取得
		pTex = pData->GetTexture();			// テクスチャ取得
		break;

	case CManager::MODE_RESULT:				// リザルトの場合
		pData = CResult::GetData();			// リザルトからデータ取得
		pTex = pData->GetTexture();			// テクスチャ取得
		break;

	case CManager::MODE_RANKING:			// ランキングの場合
		pData = CRanking::GetData();		// ランキングからデータ取得
		pTex = pData->GetTexture();			// テクスチャ取得
		break;

	default:
		break;
	}
	
	unsigned int nMaxTex = pTex->GetTextureNum();
	m_nTexNum = nTexNum;

	if( m_nTexNum > nMaxTex
		|| m_nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = pTex->GetTexture(m_nTexNum);
	}

	hr = MakeVerTex(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength);
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
void CScene3D::Uninit(void)
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
void CScene3D::Update(void)
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
void CScene3D::Draw(void)
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

	if( m_pTexture != NULL)
	{
		///// テクスチャセット /////
		pDevice->SetTexture(0, m_pTexture);
	}

	///// 頂点情報設定 /////
	pDevice->SetFVF(FVF_VERTEX_3D);

	///// 頂点バッファセット /////
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	// プリミティブ表示
	pDevice->DrawPrimitive(
						D3DPT_TRIANGLESTRIP,			// プリミティブの種類
							0,							// どこから書くか
							2);			// ポリゴン数(3角1つで1個)
}

//=============================================================================
//	関数名	: MakeVerTex
//	戻り値	: HRESULT
//	引数	: なし
//	機能	: 3Dオブジェクトの頂点を作る
//=============================================================================
HRESULT CScene3D::MakeVerTex(float fPosX, float fPosY, float fPosZ, 
							float fWidth , float fHeight, float fLength)
{
	///// 共通変数宣言 /////
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	///// 頂点用変数宣言 /////
	VERTEX_3D	*pVertex;										// 頂点データを持つ構造体


	///// 頂点バッファ作成 /////
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,	// 頂点を何個設定するのか
									D3DUSAGE_WRITEONLY,			// バッファの使用方 (現在の設定書き込み専用)
									FVF_VERTEX_3D,				// D3DFVFフラグの組み合わせ
									D3DPOOL_MANAGED,			// 頂点バッファが配置される有効なメモリクラス
									&m_pVertexBuffer,			// 頂点バッファを受け取るポインタ
									NULL);						// 絶対NULL
	if(FAILED(hr))
	{
		// 頂点バッファが作成できなければ
		return hr;
	}
	
	///// 頂点にデータを書き込む /////
	hr = m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);					// 頂点全体をロック
	if( FAILED( hr ) )
	{
		return hr;
	}

	pVertex[0].vtx = D3DXVECTOR3(-fWidth, fPosY, -fLength);
	pVertex[1].vtx = D3DXVECTOR3(-fWidth, fHeight, fLength);
	pVertex[2].vtx = D3DXVECTOR3(fWidth, fHeight, -fLength);
	pVertex[3].vtx = D3DXVECTOR3(fWidth, fPosY, fLength);
	//
	//D3DXVECTOR3 Vector0 = pVertex[1].vtx - pVertex[0].vtx;
	//D3DXVECTOR3 Vector1 = pVertex[2].vtx - pVertex[0].vtx;
	//D3DXVECTOR3 Vector2 = pVertex[1].vtx - pVertex[3].vtx;
	//D3DXVECTOR3 Vector3 = pVertex[2].vtx - pVertex[3].vtx;

	//D3DXVECTOR3 VectorA;
	//VectorA.x = (Vector0.y * Vector1.z) - (Vector0.z * Vector1.y);
	//VectorA.y = (Vector0.z * Vector1.x) - (Vector0.x * Vector1.z);
	//VectorA.z = (Vector0.x * Vector1.y) - (Vector0.y * Vector1.x);

	//D3DXVECTOR3 VectorB;
	//VectorB.x = (Vector2.y * Vector3.z) - (Vector2.z * Vector3.y);
	//VectorB.y = (Vector2.z * Vector3.x) - (Vector2.x * Vector3.z);
	//VectorB.z = (Vector2.x * Vector3.y) - (Vector2.y * Vector3.x);

	//float fLengthA = sqrt( (VectorA.x * VectorA.x) + (VectorA.y * VectorA.y) + (VectorA.z * VectorA.z) );
	//float fLengthB = sqrt( (VectorB.x * VectorB.x) + (VectorB.y * VectorB.y) + (VectorB.z * VectorB.z) );

	//D3DXVECTOR3 VectorC;
	//VectorC.x = (VectorA.x + VectorB.x) / 2;
	//VectorC.y = (VectorA.y + VectorB.y) / 2;
	//VectorC.z = (VectorA.z + VectorB.z) / 2;
	//VectorC = (VectorA + VectorB) / 2;

	//float fLengthC = sqrt( (VectorC.x * VectorC.x) + (VectorC.y * VectorC.y) + (VectorC.z * VectorC.z) );

	//pVertex[0].nor = D3DXVECTOR3( (VectorA.x / fLengthA), (VectorA.y / fLengthA), (VectorA.z / fLengthA) );
	//pVertex[1].nor = D3DXVECTOR3( (VectorC.x / fLengthC), (VectorC.y / fLengthC), (VectorC.z / fLengthC) );
	//pVertex[2].nor = D3DXVECTOR3(( VectorC.x / fLengthC), (VectorC.y / fLengthC), (VectorC.z / fLengthC) );
	//pVertex[3].nor = D3DXVECTOR3( (VectorB.x / fLengthB), (VectorB.y / fLengthB), (VectorB.z / fLengthB) );

	pVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	hr = m_pVertexBuffer->Unlock();								// 頂点全体ロックを解除

	if( FAILED( hr ) )
	{
		return hr;
	}
	
	// 作成成功
	return (S_OK);
}

//=============================================================================
//	関数名	: SetPotition
//	戻り値	: なし
//	引数	: 位置 ( X, Y, Z ) float型
//	機能	: 位置設定
//=============================================================================
void CScene3D::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// 位置設定
}

//=============================================================================
//	関数名	: SetPotition
//	戻り値	: なし
//	引数	: 位置 ( X, Y, Z ) D3DXVECTOR3型
//	機能	: 位置設定
//=============================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;			// 位置設定
}

//=============================================================================
//	関数名	: SetRotition
//	戻り値	: なし
//	引数	: 向き( X, Y, Z ) float型
//	機能	: 向き設定
//=============================================================================
void CScene3D::SetRotiton(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);		// 向き設定
}

//=============================================================================
//	関数名	: SetRotition
//	戻り値	: なし
//	引数	: 向き( X, Y, Z ) D3DXVECTOR3型
//	機能	: 位置設定
//=============================================================================
void CScene3D::SetRotiton(D3DXVECTOR3 rot)
{
	m_rot = rot;		// 向き設定
}

//=============================================================================
//	関数名	: SetScale
//	戻り値	: なし
//	引数	: 大きさ( X, Y, Z ) float型 
//	機能	: 大きさ設定
//=============================================================================
void CScene3D::SetScale(float fSclX, float fSclY, float fSclZ)
{
	m_scl = D3DXVECTOR3(fSclX, fSclY, fSclZ);		// 大きさ設定
}

//=============================================================================
//	関数名	: SetScale
//	戻り値	: なし
//	引数	: 大きさ( X, Y, Z ) D3DXVECTOR3型 
//	機能	: 大きさ設定
//=============================================================================
void CScene3D::SetScale(D3DXVECTOR3 scl)
{
	m_scl = scl;		// 大きさ設定
}



