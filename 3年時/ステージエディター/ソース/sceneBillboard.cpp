//=============================================================================
// 処理 [sceneBillboard.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: ビルボード作成
//=============================================================================
#include "manager.h"
#include "data.h"
#include "stage.h"
#include "sceneBillboard.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_BILLBOARD	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 自由に設定できる頂点フォーマット
#define VERTEX_MAX				( 2 )																// 頂点バッファ設定容量

//=============================================================================
// 関数名	: CBillboard
// 戻り値	: なし
// 引数		: プライオリティ番号
// 機能		: インスタンス生成
//=============================================================================
CBillboard::CBillboard(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// インスタンス生成
	m_pTexture = NULL;

	// ビルボードデータ初期化
	ZeroMemory(&m_DataBillboard, sizeof(BILLBOARD) );
}

//=============================================================================
// 関数名	: CBillboard
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス破棄
//=============================================================================
CBillboard::~CBillboard(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: float fWidth : 幅
//			: float fHeight: 高さ
// 機能		: ビルボード作成
//=============================================================================
CBillboard *CBillboard::Create(float fWidth, float fHeight, 
								USHORT nTexNum)
{
	HRESULT	hr;
	CBillboard *pBillboard;
	pBillboard = NEW CBillboard;
	hr = pBillboard->Init(fWidth, fHeight, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pBillboard;
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: float fWidth : 幅
//			: float fHeight: 高さ
// 機能		: ビルボード作成
//=============================================================================
CBillboard *CBillboard::CreateLoad(BILLBOARD dataBillboard)
{
	// 変数宣言
	HRESULT	hr;
	bool		bLoad = true;
	CBillboard *pBillboard = NULL;
	
	// メモリ確保
	NEW_TYPE(pBillboard, CBillboard);	// ビルボードインスタンス生成

	// データ読み込み
	bLoad = pBillboard->LoadData(dataBillboard);
	if( bLoad == false )
	{
		return NULL;		// エラーコード
	}

	// 初期化
	hr = pBillboard->Init(dataBillboard.fWidth, dataBillboard.fHeight, 
							dataBillboard.nTexNum);
	if( FAILED(hr) )
	{
		return NULL;		// エラーコード
	}

	return pBillboard;		// 正常コード
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: なし
// 機能		: ビルボード初期化
//=============================================================================
HRESULT CBillboard::Init(void)
{
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数		: D3DXVECTOR3 位置( X, Y, Z )
//			: float fWidth : 幅
//			: float fHeight: 高さ , テクスチャ番号
// 機能		: ビルボード初期化
//=============================================================================
HRESULT CBillboard::Init(float fWidth, float fHeight, USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;				// データ取得用
	CTexture	*pTex	= NULL;				// テクスチャ取得用

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き設定
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 大きさ設定

	pData = CManager::GetData();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// タイトル
	//	pData	= CTitle::GetData();		// タイトルからデータ取得
	//	break;
	//case CManager::MODE_GAME:				// ゲーム
	//	pData	= CGame::GetData();			// ゲームからデータ取得
	//	break;
	//case CManager::MODE_RESULT:				// リザルト
	//	pData	= CResult::GetData();		// リザルトからデータ取得
	//	break;
	//}

	if( pData )
	{
		pTex = pData->GetTexture();		// テクスチャ取得
	}

	if( pTex )
	{
		// テクスチャが取得できた
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			m_pTexture = NULL;							// テクスチャをNULLへ
		}
		else
		{
			m_nTexNum	= nTexNum;						// テクスチャ番号保存
			m_pTexture	= pTex->GetTexture(m_nTexNum);	// テクスチャ取得
		}
	}
	else
	{
		// テクスチャが取得できなかった
		m_pTexture = NULL;								// テクスチャをNULLへ
	}

	// データ保存
	m_DataBillboard.fWidth = fWidth;					// 幅
	m_DataBillboard.fHeight = fHeight;					// 高さ
	m_DataBillboard.nTexNum = nTexNum;					// 画像番号

	m_pos = m_DataBillboard.pos;

	hr = MakeVertex(fWidth, fHeight);					// 頂点作成
	ERROR_CHACK(hr);									// エラーチェック
	return S_OK;										// 正常コード
}


//=============================================================================
// 関数名	: Load
// 戻り値	: データが読み込めたか読み込めなかったか
// 引数		: ビルボードデータ
// 機能		: ビルボードデータ読み込み
//=============================================================================
bool CBillboard::LoadData(BILLBOARD dataBillboard)
{
	m_DataBillboard = dataBillboard;	// データ代入
	return true;						// 正常コード
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: ビルボード終了
//=============================================================================
void CBillboard::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// 頂点を破棄 
	Release();							// リリース
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: ビルボード更新
//=============================================================================
void CBillboard::Update(void)
{
	CStage *pStage = CManager::GetStage();
	
	CField **pField = pStage->GetField();
	int		nFieldNum = 0;
	pStage->GetFieldNum(nFieldNum);

	if( pField )
	{
		for( int field = 0; field < nFieldNum; field++ )
		{
			// 地面の高さ取得
			m_DataBillboard.pos.y = pField[field]->GetHeight(m_DataBillboard.pos);
		}
	}
	SetPosition(m_DataBillboard.pos);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: ビルボード描画
//=============================================================================
void CBillboard::Draw(void)
{
	// デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	CCamera *pCamera = NULL;
	D3DXMATRIX mtxView; //= pCamera->GetView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	pCamera = CManager::GetCamera();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// タイトル
	//	//pCamera	= CTitle::GetCamera();		// タイトルからカメラ取得
	//	break;
	//case CManager::MODE_GAME:				// ゲーム
	//	pCamera	= CGame::GetCamera();		// ゲームからカメラ取得
	//	break;
	//case CManager::MODE_RESULT:				// リザルト
	//	//pCamera	= CResult::GetCamera();		// リザルトからカメラ取得
	//	break;
	//}

	if( pCamera ) 
	{
		 mtxView = pCamera->GetView();
	}

	// ワールドマトリックス
	D3DXMatrixIdentity( &m_mtxWorld );		// ワールドマトリックス初期化

	D3DXMatrixInverse( &m_mtxWorld , NULL , &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// スケール反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);					// 大きさを設定
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);					// マトリックス合成
			
	// 回転反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		// 向きを設定
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);					// マトリックス合成

	// 移動反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);			// 位置を設定
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans);				// マトリックス合成

	// レンダーステート設定
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// アルファーブレンド使用
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 250 );					// アルファー値設定
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 250より上であるのなら描画しない
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティング無効

	// ワールドマトリックス設定
	pRenderer->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);	

	// 頂点情報設定
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_BILLBOARD);	// 頂点フォーマットは3D座標と色に設定

	//  頂点バッファのセット
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0,sizeof(VERTEX_3D) );

	// テクスチャのセット
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// プリミティブ表示
	pRenderer->GetDevice()->DrawPrimitive(
				CManager::GetDebug()->GetPolygonLine(),	// プリミティブの種類
				0 ,										// 最初に書く頂点は何処？
				2);										// プリミティブの数

	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライティング有効
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// アルファーテスト無効
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数		: float型 位置(X, Y, Z)
// 機能		: 位置設定
//=============================================================================
void CBillboard::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// 位置設定
	m_DataBillboard.pos = m_pos;					// 位置保存
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数		: D3DXVECTOR3型 位置(X, Y, Z)
// 機能		: 位置設定
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;					// 位置設定
	m_DataBillboard.pos = m_pos;	// 位置保存
}

//=============================================================================
// 関数名	: SetScale
// 戻り値	: なし
// 引数		: float型 大きさ(X, Y, Z)
// 機能		: 大きさ設定
//=============================================================================
void CBillboard::SetScale(float fSclX, float fSclY, float fSclZ)
{
	m_scl = D3DXVECTOR3(fSclX, fSclY, fSclZ);	// 大きさ設定
	m_DataBillboard.scl	= m_scl;				// 大きさ保存
}

//=============================================================================
// 関数名	: SetScale
// 戻り値	: なし
// 引数		: D3DXVECTOR3型 大きさ(X, Y, Z)
// 機能		: 大きさ設定
//=============================================================================
void CBillboard::SetScale(D3DXVECTOR3 scl)
{
	m_scl = scl;					// 大きさ設定
	m_DataBillboard.scl	= m_scl;	// 大きさ保存
}

//=============================================================================
// 関数名	: SetTexture
// 戻り値	: なし
// 引数		: float型 テクスチャ座標 位置( X, Y ), 幅 高さ 
// 機能		: 大きさ設定
//=============================================================================
void CBillboard::SetTexturePos(float fTexX, float fTexY, float fTexWidth, float fTexHeight)
{
	VERTEX_3D *pVtx;	// 頂点数

	// 頂点ロック
	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	pVtx[0].tex = D3DXVECTOR2(fTexX, fTexHeight);
	pVtx[1].tex = D3DXVECTOR2(fTexX, fTexY);
	pVtx[2].tex = D3DXVECTOR2(fTexWidth, fTexHeight);
	pVtx[3].tex = D3DXVECTOR2(fTexWidth, fTexY);

	m_pVertexBuffer->Unlock();		// 頂点ロック解除
}



//=============================================================================
// 関数名	: SetTextureNum
// 戻り値	: なし
// 引数値	: 画像番号
// 機能		: 画像を変更
//=============================================================================
void CBillboard::SetTextureNum(USHORT nTexNum)
{
	CData		*pData	= NULL;					// データ取得用
	CTexture	*pTex	= NULL;					// テクスチャ取得用

	pTex = CManager::GetData()->GetTexture();	// 画像取得

	// テクスチャのロード
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// タイトル
	//	pData	= CTitle::GetData();		// タイトルからデータ取得
	//	if( pData )
	//	{
	//		
	//	}
	//	break;
	//case CManager::MODE_GAME:				// ゲーム
	//	pData	= CGame::GetData();			// ゲームからデータ取得
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// ゲームからテクスチャ取得
	//	}
	//	break;
	//case CManager::MODE_RESULT:				// リザルト
	//	pData	= CResult::GetData();		// リザルトからデータ取得
	//	if( pData )
	//	{	
	//		pTex = pData->GetTexture();		// リザルトからテクスチャ取得
	//	}
	//	break;
	//}

	if( pData )
	{
		pTex = pData->GetTexture();		// テクスチャ取得
	}

	if( pTex )
	{
		// テクスチャが取得できた
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			// 画像番号の最大数より少なければ
			// 画像番号が0より大きければ
			m_pTexture = NULL;											// テクスチャをNULLへ
		}
		else
		{
			// それ以外であるなら
			m_DataBillboard.nTexNum	= nTexNum;							// 画像番号保存
			m_pTexture	= pTex->GetTexture(m_DataBillboard.nTexNum);	// テクスチャ取得
		}
	}
	else
	{
		// テクスチャ取得ならず
		m_pTexture = NULL;								// テクスチャをNULLへ
	}

	// テクスチャ番号保存
	m_DataBillboard.nTexNum = nTexNum; 
}


//=============================================================================
// 関数名	: MakeVertex
// 戻り値	: HRESUL
// 引数		: 大きさ ( 幅, 高さ )
// 機能		: ビルボード頂点作成
//=============================================================================
HRESULT CBillboard::MakeVertex(float fWidth, float fHeight)
{
	// 変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();

	HRESULT hr;					// 結果変数
	VERTEX_3D *pVtx;			// 頂点数

	// 頂点バッファ作成処理
	hr = pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_BILLBOARD,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL);
	ERROR_CHACK(hr);					

	fWidth /= 2;

	// 頂点バッファのロック
	hr = m_pVertexBuffer->Lock(0 , 0 , (void **)&pVtx , 0);
	
	// 頂点バッファの
	pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0);
	pVtx[2].vtx = D3DXVECTOR3(-fWidth, 0, 0);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, 0, 0);

	// norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 色情報の設定	( 赤 , 緑 , 青 , 透明度)
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			// 左上のテクスチャ頂点設定
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			// 右上のテクスチャ頂点設定
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			// 右下のテクスチャ頂点設定
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			// 左下のテクスチャ頂点設定

	hr = m_pVertexBuffer->Unlock();					// 頂点バッファのロック解除

	// 作成成功
	return S_OK;
}