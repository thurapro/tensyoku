//=============================================================================
// メッシュの多い空処理 [ sky.cpp ]
//
// 製作者	: 松尾 雄太
//
// 機能		: 空作成
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "data.h"
#include "sky.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 自由に設定できる頂点フォーマット
#define POLYGON_ANGLE_XZ	(0.0f)	// XとZの初期角度
#define POLYGON_ANGLE_XYZ	(0.0f)	// XとYとZの初期角度
#define CHANGE_SKY			(1)		// 上か下かの反転
#define TEX_XNUM			(3)		// テクスチャを何回フリップさせるか( X座標 )
#define TEX_YNUM			(2)		// テクスチャを何回フリップさせるか( Y座標 )

//=============================================================================
//	関数名	: CSky
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス生成
//=============================================================================
CSky::CSky(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer	= NULL;								// 頂点バッファ初期化
	m_pIndexBuffer	= NULL;								// インデックスバッファ初期化
	m_pTexture		= NULL;								// テクスチャポインタ初期化
	m_nVerTexMax	= 0;								// 頂点数初期化
	m_nIndexMax		= 0;								// 添字数初期化
	m_nTexNum		= -1;								// テクスチャ番号初期化
	m_pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 空の位置初期化
	m_rot	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 空の向き初期化
	m_scl	= D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// 空の大きさ初期化
	ZeroMemory(&m_DataSky, sizeof(m_DataSky) );			// 空データ初期化
}

//=============================================================================
//	関数名	: CSky
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CSky::~CSky(void)
{
	// インスタンス破棄
}

//=============================================================================
//	関数名	: Create
//	戻り値	: 空のポインタ
//	引数	: ポリゴン(幅、高さ), ポリゴンの数(横、縦), ポリゴンの半径, テクスチャ番号 
//	機能	: 空の初期化
//=============================================================================
CSky* CSky::Create(float fPolygonWidth, float fPolygonHeight,		
					int nNumX, int nNumY, float fR, 
					USHORT nTexNum)
{
	HRESULT hr;			// 結果			
	CSky *pSky = NULL;	// 空ポインタ宣言
	
	// 空インスタンス生成
	NEW_TYPE(pSky, CSky);								// メモリ確保
	hr = pSky->Init(fPolygonWidth, fPolygonHeight, 
					 nNumX, nNumY, fR, nTexNum);		// 空初期化 
	if( FAILED(hr) )									// エラーチェック
	{
		return NULL;									// エラーコード
	}
	return pSky;										// 正常コード
}

//=============================================================================
//	関数名	: CreateLoad
//	戻り値	: 空のポインタ
//	引数	: 空データ, 画像番号 
//	機能	: 空の作成 & データ読み込み, 画像番号設定
//=============================================================================
CSky* CSky::CreateLoad(SKY dataSky, USHORT nTexNum)
{
	HRESULT hr;						// 結果			
	CSky *pSky = NULL;	// 空ポインタ宣言
	
	// メモリ確保
	NEW_TYPE(pSky, CSky);	

	// データ読み込み
	pSky->LoadData(dataSky);	// 空データ読み込み
	
	// 初期化
	hr = pSky->Init(dataSky.fWidth, dataSky.fHeight,
					dataSky.nNumX,  dataSky.nNumY, 
					dataSky.fR, nTexNum);	// 空初期化
	
	pSky->SetPosition(dataSky.pos);			// 位置設定
	pSky->SetRotition(dataSky.rot);			// 向き設定

	if( FAILED(hr) )
	{
		// 初期化失敗
		return NULL;
	}
	return pSky;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: HRESULT
//	引数	: ポリゴン(幅、高さ), ポリゴンの数(横、縦), ポリゴンの半径, 上に作るのか,テクスチャ番号
//	機能	: 空の初期化
//=============================================================================
HRESULT CSky::Init(float fPolygonWidth, float fPolygonHeight,		
					int nNumX, int nNumY, float fR, 
					USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;					// データ取得用
	CTexture	*pTex	= NULL;					// テクスチャ取得用

	// 空初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);		// 空の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 空の向き
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 空の大きさ

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
		// テクスチャ取得ならず
		m_pTexture = NULL;								// テクスチャをNULLへ
	}

	// ポリゴンの大きさ保存
	m_DataSky.fWidth = fPolygonWidth;	// ポリゴンの幅保存
	m_DataSky.fHeight = fPolygonHeight;	// ポリゴンの高さ保存

	// ポリゴン数保存
	m_DataSky.nNumX = nNumX;			// 横のポリゴン数保存
	m_DataSky.nNumY = nNumY;			// 縦のポリゴン数保存

	// ポリゴンの半径保存
	m_DataSky.fR = fR;					// 半径保存
	
	// 頂点情報作成
	hr = MakeVerTex(fPolygonWidth , fPolygonHeight, fR);		
	ERROR_CHACK(hr);	// エラーチェック

	return S_OK;		// 正常コード
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: 空の破棄
//=============================================================================
void CSky::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// 頂点バッファ破棄
	SALF_RELEASE(m_pIndexBuffer);		// インデックスバッファ破棄
	Release();							// 空をリスト構造から破棄
}

//=============================================================================
//	関数名	: Update
//	戻り値	: なし
//	引数	: なし
//	機能	: 空の更新
//=============================================================================
void CSky::Update(void)
{

}

//=============================================================================
//	関数名	: Draw
//	戻り値	: なし
//	引数	: なし
//	機能	: 空の描画
//=============================================================================
void CSky::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

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
	pRenderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_mtxWorld );	

	// レンダーステートと設定
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		// ライト無効化

	// 頂点情報設定
	pRenderer->GetDevice()->SetFVF( FVF_VERTEX_3D );	// 頂点フォーマットは3D座標と色に設定

	//  頂点バッファのセット
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pRenderer->GetDevice()->SetIndices(m_pIndexBuffer);

	// テクスチャのセット
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// プリミティブ表示
	pRenderer->GetDevice()->DrawIndexedPrimitive
				( CManager::GetDebug()->GetPolygonLine() ,	// プリミティブの種類
				0 ,								// 三角形の数
				0 ,
				m_nVerTexMax ,					// 頂点の個数（頂点バッファ）
				0 ,
				m_nIndexMax - 2 );				// プリミティブの数

	// レンダーステートを初期化設定に戻す
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);	// ライト有効化

	CManager::GetDebug()->Print("空映してるよ\n");
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CSky::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// 位置設定
	m_DataSky.pos = m_pos;						// 現在位置保存
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CSky::SetPosition(D3DXVECTOR3 pos)
{ 
	m_pos = pos;				// 位置設定
	m_DataSky.pos = m_pos;		// 位置保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 角度設定
//=============================================================================
void CSky::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// 向き設定
	m_DataSky.rot = m_rot;						// 現在向き保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 角度設定
//=============================================================================
void CSky::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// 向き設定
	m_DataSky.rot = m_rot;		// 現在向き保存
}

//=============================================================================
// 関数名	: LoadData
// 戻り値	: HRESULT
// 引数値	: 空データ
// 機能		: 空データ読み込み
//=============================================================================
void CSky::LoadData(SKY dataSky)
{
	m_DataSky = dataSky;	// 空データ代入
}

//=============================================================================
// 関数名 : MakeVerTex
// 戻り値 : HRESULT
// 引数 : ポリゴン(幅, 高さ), 半径 
// 機能 : 頂点バッファ作成
//=============================================================================
HRESULT CSky::MakeVerTex(float fPolygonWidth , float fPolygonHeight, float fR)
{
	// 変数宣言 
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	WORD *pIdx;			// 添え字数

	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// 頂点数計算
	m_nVerTexMax = ( (m_DataSky.nNumX + 1) * (m_DataSky.nNumY + 1) );	// 横のポリゴン数 + 1 * 縦のポリゴン数 + 1

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
	float	fAngleXZ		= POLYGON_ANGLE_XZ;			// XとZの角度		円柱にする
	float	fAngleXYZ		= POLYGON_ANGLE_XYZ;		// XとYとZの角度	球体にする
	float	fAngleXZSum		= (D3DX_PI * 2) / m_DataSky.nNumX;	// XとYの角度加算
	float	fAngleXYZSum	= D3DX_PI / m_DataSky.nNumY;		// XとYとZの角度加算
	int		nP				= 0;						// ポリゴンカウンター 

	// 頂点座標設定
	for( int y = 0; y < m_DataSky.nNumY + 1; y++, fAngleXYZ += fAngleXYZSum )
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataSky.nNumX + 1; x++, nP++, fAngleXZ += fAngleXZSum )
		{
			// 横の枚数分
			pVtx[nP].vtx		= D3DXVECTOR3( -cosf(fAngleXYZ) * cosf(fAngleXZ) * fR, 
												sin(fAngleXYZ)  * fR, 
												cosf(fAngleXYZ) * sinf(fAngleXZ) * fR);	// 頂点座標設定

			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);							// 頂点色設定
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);								// 法線設定
		}
		fAngleXZ	= POLYGON_ANGLE_XZ;		// 角度を初期化
	}

	nP = 0;		// ポリゴンカウンター初期化

	// テクスチャの変数
	float fTexX			= 0.0f;							// テクスチャ座標のX軸
	float fTexY			= 0.0f;							// テクスチャ座標のY軸
	float fTexWidth		= 1.0f / m_DataSky.nNumX * TEX_XNUM;	// テクスチャの幅 * 何回フリップさせるか
	float fTexHeight	= 1.0f / m_DataSky.nNumY * TEX_YNUM;	// テクスチャの高さ * 何回フリップさせるか

	// テクスチャ座標設定
	for( int y = 0; y < m_DataSky.nNumY + 1; y++, fTexY += fTexHeight)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataSky.nNumX + 1; x++, nP++, fTexX += fTexWidth)
		{
			// 横の枚数分
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// テクスチャ座標設定
		}
		fTexX	= 0.0f;			// テクスチャ幅を初期化	
	}

	// インデックスの数													
	m_nIndexMax = ( ( (m_DataSky.nNumX + 1) * 2 ) * m_DataSky.nNumY ) + ( ( m_DataSky.nNumY - 1 ) * 2 );

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
		if( index ==  (( m_DataSky.nNumX * 2 ) + 1)  + gyo )
		{
			// 縮退ポリゴンの生成
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataSky.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataSky.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataSky.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataSky.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// 偶数だった場合
			pIdx[index] =  (m_DataSky.nNumX + 1) + nNum_Gusu;
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