//=============================================================================
// 壁処理 [Meshwall.cpp]
//
// 名前	: 松尾 雄太
//
// 機能 : メッシュの多い壁
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "scene3D.h"
#include "wall.h"
#include "field.h"
#include "data.h"
#include "stage.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 自由に設定できる頂点フォーマット
#define TEX_XNUM			(1)		// テクスチャを何回フリップさせるか( X座標 )
#define TEX_YNUM			(1)		// テクスチャを何回フリップさせるか( Y座標 )

//=============================================================================
//	関数名	: CWall
//	戻り値	: 初期化できたか結果
//	引数	: 優先順位, オブジェのタイプ
//	機能	: インスタンス生成
//=============================================================================
CWall::CWall(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer	= NULL;								// 頂点バッファ初期化
	m_pIndexBuffer	= NULL;								// インデックスバッファ初期化
	m_pTexture		= NULL;								// テクスチャポインタ初期化
	m_nVerTexMax	= 0;								// 頂点数初期化
	m_nIndexMax		= 0;								// 添字数初期化
	m_DataWall.nTexNum		= -1;								// テクスチャ番号初期化
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 壁の位置初期化
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 壁の向き初期化
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 壁の大きさ初期化
	ZeroMemory(&m_DataWall, sizeof(WALL) );				// 壁データ初期化
}

//=============================================================================
//	関数名	: MeshWallInit
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CWall::~CWall(void)
{
}

//=============================================================================
//	関数名	: Create
//	戻り値	: 壁ポインタ
//	引数	: ポリゴンの大きさ( 幅, 高さ ) ポリゴン数( 横, 縦 )
//	機能	: 壁初期化
//=============================================================================
CWall *CWall::Create(float fPolygonWidth, float fPolygonHeight, int nNumX, int nNumY, 
					 USHORT nTexNum)
{
	// 変数宣言
	HRESULT hr;				// 結果
	CWall *pWall = NULL;	// 壁ポインタ

	NEW_TYPE(pWall, CWall);	// 壁インスタンス生成
	hr = pWall->Init(fPolygonWidth, fPolygonHeight, nNumX, nNumY, nTexNum);		// 壁初期化
	if( FAILED(hr) )
	{
		// エラーチェック
		return NULL;		// エラー
	}
	return pWall;			// 正常コード
}

//=============================================================================
//	関数名	: CreateLoad
//	戻り値	: 壁ポインタ
//	引数	: 壁データ, 画像番号
//	機能	: 壁初期化
//=============================================================================
CWall* CWall::CreateLoad(WALL dataWall)
{
	// 変数宣言
	HRESULT	hr;					// 結果
	CWall *pWall = NULL;		// 壁ポインタ
	
	// メモリ確保
	NEW_TYPE(pWall, CWall);		// 壁クラス

	// 初期化
	pWall->LoadData(dataWall);	// 壁データ読み込み

	hr = pWall->Init(dataWall.fWidth, dataWall.fHeight,
					dataWall.nNumX, dataWall.nNumY, 
					dataWall.nTexNum);			// 壁初期化
	
	pWall->SetPosition(dataWall.pos);
	pWall->SetRotition(dataWall.rot);

	if( FAILED(hr) )
	{
		// 初期化失敗
		return NULL;
	}
	return pWall;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: 初期化
//=============================================================================
HRESULT CWall::Init(void)
{
	return S_OK;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: 初期化できたか結果
//	引数	: デバイス
//	機能	: 壁初期化
//=============================================================================
HRESULT CWall::Init(float fPolygonWidth, float fPolygonHeight, int nNumX, int nNumY, 
					USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;				// データ取得用
	CTexture	*pTex	= NULL;				// テクスチャ取得用

	// 壁初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);		// 壁の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 壁の向き
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f );		// 壁の大きさ


	pTex = CManager::GetData()->GetTexture();

	// テクスチャのロード
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// タイトル
	//	pData	= CTitle::GetData();		// タイトルからデータ取得
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// タイトルからテクスチャ取得
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

	m_DataWall.nTexNum	= nTexNum;						// テクスチャ番号保存

	if( pTex )
	{
		// テクスチャが取得できた
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			m_pTexture = NULL;							// テクスチャをNULLへ
		}
		else
		{
			m_pTexture	= pTex->GetTexture(m_DataWall.nTexNum);	// テクスチャ取得
		}
	}
	else
	{
		// テクスチャ取得ならず
		m_pTexture = NULL;								// テクスチャをNULLへ
	}

	// ポリゴンの大きさ保存
	m_DataWall.fWidth	= fPolygonWidth;	// ポリゴンの幅保存
	m_DataWall.fHeight	= fPolygonHeight;	// ポリゴンの高さ保存

	// ポリゴン数保存
	m_DataWall.nNumX = nNumX;				// 横のポリゴン数保存
	m_DataWall.nNumY = nNumY;				// 縦のポリゴン数保存
		
	m_DataWall.nTexNum = nTexNum;			// 画像番号保存

	m_DataWall.pos = m_pos;					// 位置保存
	m_DataWall.rot = m_rot;					// 向き保存
	m_DataWall.scl = m_scl;					// 大きさ保存

	// 頂点情報作成
	hr = MakeVerTex(fPolygonWidth , fPolygonHeight);		
	ERROR_CHACK(hr);	// エラーチェック

	return S_OK;		// 正常コード
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: 壁破棄
//=============================================================================
void CWall::Uninit(void)
{	
	SALF_RELEASE(m_pVertexBuffer);		// 頂点バッファの解放
	SALF_RELEASE(m_pIndexBuffer);		// インデックスバッファの解放					
	Release();							// 壁をシーンリスト構造から破棄
}

//=============================================================================
//	関数名	: Update
//	戻り値	: なし
//	引数	: なし
//	機能	: 壁更新
//=============================================================================
void CWall::Update(void)
{
	// 地面取得
	CStage *pStage  = CManager::GetStage();
	CField **pField = pStage->GetField();
	int		nFieldNum = 0;
	pStage->GetFieldNum(nFieldNum);

	if( pField )
	{
		for( int field = 0; field < nFieldNum; field++ )
		{
			// 地面の高さ取得
			m_DataWall.pos.y = pField[field]->GetHeight(m_DataWall.pos);
		}
	}
	m_DataWall.pos.y += (m_DataWall.fHeight / 4);
	SetPosition(m_DataWall.pos);
}

//=============================================================================
//	関数名	: Draw
//	戻り値	: なし
//	引数	: なし
//	機能	: 壁描画
//=============================================================================
void CWall::Draw(void)
{
	// 変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	// ワールドマトリックス
	D3DXMatrixIdentity( &m_mtxWorld );		// ワールドマトリックス初期化

	// スケール反映
	D3DXMatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	D3DXMatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );
		
	// 回転反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld , &mtxRot );

	// 移動反映
	D3DXMatrixTranslation( &mtxTrans, m_pos.x, m_pos.y, m_pos.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans );

	// ワールドマトリックス設定
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );	

	// 頂点情報設定
	pDevice->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

	//  頂点バッファのセット
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pIndexBuffer);

	// テクスチャのセット
	pDevice->SetTexture(0, m_pTexture);

	// プリミティブ表示
	pDevice->DrawIndexedPrimitive
				( CManager::GetDebug()->GetPolygonLine() ,	// プリミティブの種類
				0 ,											// 三角形の数
				0 ,
				m_nVerTexMax ,								// 頂点の個数（頂点バッファ）
				0 ,
				m_nIndexMax - 2 );							// プリミティブの数

	//CManager::GetDebug()->Print("壁映してるよ\n");
}

//=============================================================================
// 関数名	: SetTextureNum
// 戻り値	: なし
// 引数値	: 画像番号
// 機能		: 画像を変更
//=============================================================================
void CWall::SetTextureNum(USHORT nTexNum)
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
	//		pTex = pData->GetTexture();		// タイトルからテクスチャ取得
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

	if( pTex )
	{
		// テクスチャが取得できた
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			// 画像番号の最大数より少なければ
			// 画像番号が0より大きければ
			m_pTexture = NULL;							// テクスチャをNULLへ
		}
		else
		{
			// それ以外であるなら
			m_DataWall.nTexNum	= nTexNum;						// 画像番号保存
			m_pTexture	= pTex->GetTexture(m_DataWall.nTexNum);	// テクスチャ取得
		}
	}
	else
	{
		// テクスチャ取得ならず
		m_pTexture = NULL;								// テクスチャをNULLへ
	}
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CWall::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// 位置設定
	m_DataWall.pos = m_pos;						// 現在の位置保存
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CWall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;				// 位置設定
	m_DataWall.pos = m_pos;		// 現在の位置保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 角度設定
//=============================================================================
void CWall::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// 向き設定
	m_DataWall.rot = m_rot;						// 現在の向き保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CWall::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// 向き設定
	m_DataWall.rot = m_rot;		// 現在の向き保存
}

//=============================================================================
// 関数名	: SetTexNum
// 戻り値	: なし
// 引数値	: 画像番号
// 機能		: 画像設定
//=============================================================================
void CWall::SetTexNum(USHORT nTexNum)
{
	// テクスチャ取得
	CTexture *pTex = NULL;

	pTex = CManager::GetData()->GetTexture();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:
	//	pTex = CTitle::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_GAME:
	//	pTex = CGame::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_RESULT:
	//	pTex = CResult::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_RANKING:
	//	pTex = CRanking::GetData()->GetTexture();
	//	break;
	//default:
	//	break;
	//}

	m_DataWall.nTexNum = nTexNum;						// テクスチャ番号保存
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataWall.nTexNum || 
		m_DataWall.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataWall.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}
}

//=============================================================================
// 関数名	: LoadData
// 戻り値	: なし
// 引数値	: 壁データ
// 機能		: 壁データ読み込み
//=============================================================================
void CWall::LoadData(WALL dataWall)
{
	m_DataWall = dataWall;		// データ読み込み
}

//=============================================================================
// 関数名 : MakeVertex
// 戻り値 : HRESULT
// 引数 : デバイス 
// 機能 : 頂点バッファ作成
//=============================================================================
HRESULT CWall::MakeVerTex(float fPolygonWidth , float fPolygonHeight)
{
	// 変数宣言 
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	WORD *pIdx;			// 添え字数

	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// 頂点数計算
	m_nVerTexMax = ( (m_DataWall.nNumX + 1) * (m_DataWall.nNumY + 1) );	// 横のポリゴン数 + 1 * 縦のポリゴン数 + 1

	// 頂点バッファ作成処理
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_3D) * m_nVerTexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	ERROR_CHACK(hr);	// エラーチェック

	// 頂点バッファのロック
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	// 頂点の変数
	float	fWidth	= (fPolygonWidth * m_DataWall.nNumX) / 2;		// ポリゴンの幅
	float	fHeight	= (fPolygonHeight * m_DataWall.nNumY) / 2;		// ポリゴンの高さ
	float	fX		= -fWidth;										// 頂点座標のX軸
	float	fY		= fPolygonHeight * m_DataWall.nNumY;			// 頂点座標のY軸
	int		nP		= 0;											// ポリゴンカウンター 

	// 頂点座標設定
	for( int y = 0; y < m_DataWall.nNumY + 1; y++, fY -= fPolygonHeight)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataWall.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// 横の枚数分
			pVtx[nP].vtx		= D3DXVECTOR3(fX, fY, 0);				// 頂点座標設定
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// 頂点色設定
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 法線設定
		}
		fX		= -fWidth;			// ポリゴン幅を初期化
	}

	nP = 0;		// ポリゴンカウンター初期化

	// テクスチャの変数
	float fTexX			= 0.0f;									// テクスチャ座標のX軸
	float fTexY			= 0.0f;									// テクスチャ座標のY軸
	float fTexWidth		= 1.0f / m_DataWall.nNumX * TEX_XNUM;	// テクスチャの幅 * 何回フリップさせるか
	float fTexHeight	= 1.0f / m_DataWall.nNumY * TEX_YNUM;	// テクスチャの高さ * 何回フリップさせるか

	// テクスチャ座標設定
	for( int y = 0; y < m_DataWall.nNumY + 1; y++, fTexY += fTexHeight)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataWall.nNumX + 1; x++, nP++, fTexX -= fTexWidth)
		{
			// 横の枚数分
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// テクスチャ座標設定
		}
		fTexX	= 0.0f;			// テクスチャ幅を初期化	
	}

	// インデックスの数													
	m_nIndexMax = ( ( (m_DataWall.nNumX + 1) * 2 ) * m_DataWall.nNumY ) + ( ( m_DataWall.nNumY - 1 ) * 2 );

	// インデックスバッファ作成
	hr = pRenderer->GetDevice()->CreateIndexBuffer( sizeof(WORD) * m_nIndexMax, 
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&m_pIndexBuffer,
										NULL );
	ERROR_CHACK(hr);		// エラーチェック
	
	// インデックスバッファのロック
	hr = m_pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

	int index = 0;			// インデックス番号
	int gyo = 0;			// 行数
	int polygon = 0;		// ポリゴン番号
	int nNum_Kisu = 0;		// 奇数
	int nNum_Gusu = 0;		// 偶数

	while( index < m_nIndexMax )
	{
		// 折り返し地点だった場合
		if( index ==  (( m_DataWall.nNumX * 2 ) + 1)  + gyo )
		{
			// 縮退ポリゴンの生成
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataWall.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataWall.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataWall.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataWall.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// 偶数だった場合
			pIdx[index] =  (m_DataWall.nNumX + 1) + nNum_Gusu;
			nNum_Gusu++;
			index++;
		}
		else if(  index % 2 == 1 )
		{
			// 奇数だった場合
			pIdx[index] = nNum_Kisu;
			nNum_Kisu++;
			index++;
		}
	}
			
	// インデックスバッファのロック解除
	m_pIndexBuffer->Unlock();
		
	// 作成成功
	return (S_OK);
}



