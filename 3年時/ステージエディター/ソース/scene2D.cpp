//============================================================================= 
// 2Dオブジェクト処理 [ scene2D.cpp ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: 2Dオブジェクト作成処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================

#include "manager.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	POLYGON_NUM		(2)		// ポリゴン数
#define START_VERTEX	(0)		// 書き始める頂点
#define MAX_VERTEX		(4)		// 最大頂点数
#define TEXTURE_NUM		(-1)	// テクスチャ番号初期化

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// 関数名	: CScene
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス生成	( 初期化 )
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer = NULL;			// 頂点バッファ初期化
	m_nTextureNum	= TEXTURE_NUM;	// テクスチャ初期化
	m_pTexture		= NULL;			// テクスチャポインタ初期化
}

//=============================================================================
// 関数名	: ~CScene
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄	(終了処理)
//=============================================================================
CScene2D::~CScene2D(void)
{
}

//=============================================================================
// 関数名	: Create
// 戻り値	: CScene2D
// 引数値	: 作る座標( X軸, Y軸 ) 大きさ( 幅 , 高さ ), どのテクスチャを使うか
// 機能		: 2Dオブジェクトを作る
//=============================================================================
CScene2D *CScene2D::Create(float fPosX, float fPosY,
							float fWidth, float fHeight,
							unsigned short nTexturenNumber)
{		
	HRESULT hr;									// エラーチェック変数
	CScene2D *pScene2D = NULL;					// 2Dオブジェクト変数

	// もし2Dオブジェクトが作られていなければ
	NEW_TYPE(pScene2D, CScene2D);				// インスタンス生成
	hr = pScene2D->Init(fPosX, fPosY,		 
						fWidth, fHeight, 
						nTexturenNumber);		// 2Dオブジェクトの初期化
	if( FAILED(hr) )
	{
		// 2Dオブジェクト作成失敗
		return NULL;							// NULLを返す
	}

	// 作成成功
	return pScene2D;							// 作られた2Dを返す
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: なし
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// 処理は特になし
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数値	: 作る座標( X軸, Y軸 ) 大きさ( 幅 , 高さ ), どのテクスチャを使うか
// 機能		: 2Dオブジェクトを作る
//=============================================================================
HRESULT CScene2D::Init(float fPosX, float fPosY, 
						 float fWidth, float fHeight,
						 unsigned short nTextureNumber)
{
	HRESULT hr;						// エラーチェック変数

	m_nTextureNum = nTextureNumber;	// テクスチャ番号保存

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:
	//	if( m_nTextureNum > CLogo::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		m_pTexture = NULL;
	//	}
	//	else
	//	{
	//		m_pTexture = CLogo::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TITLE:
	//	if( m_nTextureNum > CTitle::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CTitle::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TUTORIAL:
	//	if( m_nTextureNum > CTutorial::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CTutorial::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_GAME:
	//	if( m_nTextureNum > CGame::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//case CManager::MODE_RESULT:
	//	if( m_nTextureNum > CResult::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CResult::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//case CManager::MODE_RANKING:
	//	if( m_nTextureNum > CRanking::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CRanking::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//default :
	//	return E_FAIL;
	//	break;
	//}

	// 頂点作成
	hr = MakeVertex(fPosX, fPosY, fWidth, fHeight);
	ERROR_CHACK(hr);	// エラーチェック

	return S_OK;		// 正常に初期化された
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: 2Dオブジェクト破棄
//=============================================================================
void CScene2D::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);	// 頂点バッファ破棄
	Release();						// シーンリスト構造から自分を破棄
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数値	: なし
// 機能		: 2Dオブジェクト更新
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: 2Dオブジェクト描画
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	// 頂点フォーマットをセット
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D_TEX);
	
	// 頂点バッファーのセット
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
	
	// テクスチャーセット
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// プリミティブ
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, START_VERTEX, POLYGON_NUM);

	// 今回のテクスチャが残らないようにNULLを代入
	pRenderer->GetDevice()->SetTexture(0, NULL);
}

//=============================================================================
// 関数名	: MakeVertex
// 戻り値	: HRESULT
// 引数値	: 作る座標( X軸, Y軸 ) 大きさ( 幅 , 高さ )
// 機能		: 2Dオブジェクトの頂点作成
//=============================================================================
HRESULT CScene2D::MakeVertex(float fPosX, float fPosY, float fWidth, float fHeight)
{
	HRESULT		hr;					// エラーチェック変数
	VERTEX_2D	*pVtx;				// 頂点作成用の格納変数
	CRenderer *pRenderer = NULL;	// レンダラーポインタ
	
	// レンダラー取得
	pRenderer = CManager::GetRenderer();	
	
	// 頂点バッファ作成
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_2D) * MAX_VERTEX,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_2D_TEX,
													D3DPOOL_MANAGED,
													&m_pVertexBuffer,
													NULL );
	ERROR_CHACK(hr);	// 作成できたのかチェック
	
	// 頂点バッファーロック
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// 大きさ調節
	fWidth += fPosX;	// 幅を調節
	fHeight += fPosY;	// 高さを調節

	// 頂点バッファー位置セット
	pVtx[0].Vertex = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].Vertex = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].Vertex = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].Vertex = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色情報
	pVtx[0].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャー座標設定
	pVtx[0].Texture = D3DXVECTOR2(0, 0);
	pVtx[1].Texture = D3DXVECTOR2(1, 0);
	pVtx[2].Texture = D3DXVECTOR2(0, 1);
	pVtx[3].Texture = D3DXVECTOR2(1, 1);

	// 位置の保存
	m_pos.x = fPosX;	// X軸の位置保存	
	m_pos.y = fPosY;	// Y軸の位置保存

	// ロック解除
	hr = m_pVertexBuffer->Unlock();

	return S_OK;		// 正常に頂点作成できた
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 配置する座標( X軸, Y軸 ) 大きさ( 幅 , 高さ )
// 機能		: 座標設定
//=============================================================================
void CScene2D::SetPosition(float fPosX, float fPosY,
							float fWidth, float fHeight)
{
	VERTEX_2D	*pVtx;		// 頂点作成用の格納変数
	
	// 大きさ調節
	fWidth += fPosX;		// 幅の調節		
	fHeight += fPosY;		// 高さの調節

	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点バッファー位置セット
	pVtx[0].Vertex = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].Vertex = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].Vertex = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].Vertex = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// 位置の設定
	m_pos.x = fPosX;		// X位置設定
	m_pos.y = fPosY;		// Y位置設定

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}

//=============================================================================
// 関数名	: SetColor
// 戻り値	: なし
// 引数値	: 色設定 ( 赤, 緑, 青, 透明度 )
// 機能		: 色設定
//=============================================================================
void CScene2D::SetColor(int nR, int nG, int nB, int nA)
{
	VERTEX_2D	*pVtx;				// 頂点作成用の格納変数
	
	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点の色設定
	pVtx[0].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[1].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[2].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[3].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}

//=============================================================================
// 関数名	: SetTexture
// 戻り値	: なし
// 引数値	: 配置する座標( X軸, Y軸 ) 大きさ( 幅 , 高さ )
// 機能		: テクスチャ座標設定
//=============================================================================
void CScene2D::SetTexure(float fTexX, float fTexY, 
							float fTexWidth, float fTexHeight)
{
	VERTEX_2D	*pVtx;				// 頂点作成用の格納変数
	
	// 頂点バッファーロック
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	
	// テクスチャー座標設定
	pVtx[0].Texture = D3DXVECTOR2(fTexX, fTexY);
	pVtx[1].Texture = D3DXVECTOR2(fTexWidth, fTexY);
	pVtx[2].Texture = D3DXVECTOR2(fTexX, fTexHeight);
	pVtx[3].Texture = D3DXVECTOR2(fTexWidth, fTexHeight);

	m_pVertexBuffer->Unlock();		// 頂点アンロック
}

//=============================================================================
// 関数名	: SetTexNum
// 戻り値	: なし
// 引数値	: テクスチャ番号
// 機能		: テクスチャ番号設定
//=============================================================================
void CScene2D::SetTexNum(unsigned short nTexNum)
{
	m_nTextureNum = nTexNum;		// テクスチャ番号保存
	
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:
	//	if( m_nTextureNum > CLogo::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		m_pTexture = NULL;
	//	}
	//	else
	//	{
	//		m_pTexture = CLogo::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TITLE:
	//	if( m_nTextureNum > CTitle::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CTitle::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_GAME:
	//	if( m_nTextureNum > CGame::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_RESULT:
	//	if( m_nTextureNum > CResult::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// テクスチャが存在しない
	//		m_pTexture = NULL;				// エラーコード
	//	}
	//	else
	//	{
	//		m_pTexture = CResult::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//}
}