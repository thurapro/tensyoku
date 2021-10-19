//=============================================================================
// 処理 [meshfield.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: メシュの多い3Dオブジェクト生成
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "sceneline.h"
#include "data.h"
#include "ocean.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 自由に設定できる頂点フォーマット
#define ANGLE_INIT			(180)															// 初期角度

//=============================================================================
//	関数名	: COcean
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス生成
//=============================================================================
COcean::COcean(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// インスタンス生成
	m_pTexture	= NULL;							// テクスチャNULL初期化
	m_nTexNum	= -1;							// テクスチャ番号初期化
	m_fAngle	= D3DX_PI / 2;					// 海の角度
	m_nTimeCnt	= 0;							// 波が上がる時間
	m_pVertex	= NULL;							// 頂点作成
	m_pNor		= NULL;							// 面の法線
	ZeroMemory(&m_DataOcean, sizeof(OCEAN));	// 構造体初期化
}

//=============================================================================
//	関数名	: ~COcean
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
COcean::~COcean(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: 海ポインタ
// 引数値	: ポリゴンの大きさ(幅, 奥行), ポリゴンの数(縦, 横), 画像番号
// 機能		: 海を作成
//=============================================================================
COcean *COcean::Create(float fPolygonWidth, float fPolygonLength, 
					   int nNumX , int nNumZ, USHORT nTexNum)
{
	HRESULT hr;
	COcean *pOcean = NULL;
	NEW_TYPE(pOcean, COcean);
	hr = pOcean->Init(fPolygonWidth, fPolygonLength, nNumX, nNumZ, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pOcean;
}

//=============================================================================
// 関数名	: CreateLoad
// 戻り値	: 海ポインタ
// 引数値	: 海データ
// 機能		: 海を作成 & 読み込み
//=============================================================================
COcean *COcean::CreateLoad(OCEAN dataOcean)
{
	// 変数宣言
	COcean	*pOcean = NULL;
	bool	bLoad = false;
	
	// 海インスタンス生成
	NEW_TYPE(pOcean, COcean);

	// 海データ読み込み
	bLoad = pOcean->LoadData(dataOcean);

	if( bLoad == false )
	{
		// 読み込み失敗
		return NULL;		// エラーコード
	}

	return pOcean;			// 正常コード
}

//=============================================================================
//	関数名	: Init
//	戻り値	: なし
//	引数	: なし
//	機能	: 3Dオブジェクトの初期化
//=============================================================================
HRESULT COcean::Init(float fPolygonWidth, float fPolygonLength, 
					int nNumX, int nNumZ, 
					USHORT nTexNum)
{
	///// 3Dオブジェクト初期化処理開始 /////
	// 変数宣言
	HRESULT hr; 
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き初期化
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさ初期化

	SetTexNum(nTexNum);

	// データ保存
	m_DataOcean.fWidth = fPolygonWidth;			// ポリゴンの幅
	m_DataOcean.fLength = fPolygonLength;		// ポリゴンの奥行

	m_DataOcean.nNumX = nNumX;					// ポリゴン数(横)
	m_DataOcean.nNumZ = nNumZ;					// ポリゴン数(縦)

	m_nTexNum = nTexNum;						// テクスチャ番号保存

	m_nVerTexMax = ( (m_DataOcean.nNumX + 1) * (m_DataOcean.nNumZ + 1) );

	hr = MakeVerTex(fPolygonWidth, fPolygonLength);
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	SetPosition(m_DataOcean.pos);
	SetRotition(m_DataOcean.rot);

	return S_OK;
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: 3Dオブジェクトの破棄
//=============================================================================
void COcean::Uninit(void)
{
	SALF_RELEASE(m_pIndexBuffer);			// 添字破棄
	SALF_RELEASE(m_pVertexBuffer);			// 頂点バッファ破棄
	SALF_DELETE_ARRAY(m_pVertex);			// 頂点保存用変数破棄
	SALF_DELETE_ARRAY(m_pNor);				// 法線保存用変数破棄
	Release();								// 海破棄
}

//=============================================================================
//	関数名	: Update
//	引数	: なし
//	機能	: 3Dオブジェクトの更新
//=============================================================================
void COcean::Update(void)
{
	VERTEX_3D *pVtx;										// 頂点数
	int		nCnt = 0;
	int i = 0;

	if( m_nTimeCnt > 30 )
	{
		m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
		while( i < m_nVerTexMax )
		{
			pVtx[i].vtx = D3DXVECTOR3( m_pVertex[i].x,
								sinf(m_fAngle) * cosf(m_fAngle) * 100,
									 m_pVertex[i].z);
						
			if( m_fAngle <= D3DX_PI / 6 )
			{
				m_fAngle = D3DX_PI / 2;
			}
			else
			{
				m_fAngle -= D3DX_PI / 10;
			}
			i++;
		}
		m_nTimeCnt = 0;
		NorVertex();
	}
	else
	{
		m_nTimeCnt++;
	}
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
void COcean::Draw(void)
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

	pDevice->SetTexture(0, m_pTexture);

	///// 頂点情報設定 /////
	pDevice->SetFVF(FVF_VERTEX_3D);

	///// 頂点バッファセット /////
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pIndexBuffer);

	// プリミティブ表示
	pDevice->DrawIndexedPrimitive(
							CManager::GetDebug()->GetPolygonLine(),	// プリミティブの種類
							0,										// どこから書くか
							0,
							m_nVerTexMax,
							0,
							m_nIndexMax - 2);						// ポリゴン数(3角1つで1個)
							
}

//=============================================================================
//	関数名	: MakeVerTexCylinder
//	戻り値	: HRESULT
//	引数	: なし
//	機能	: 3Dオブジェクトの頂点を作る
//=============================================================================
HRESULT COcean::MakeVerTex(float fPolygonWidth , float fPolygonLength)
{
	///// 共通変数宣言 /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	///// 頂点用変数宣言 /////
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;		// 頂点数
	WORD *pIdx;			// 添え字数


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
	float	fWidth	= (fPolygonWidth * m_DataOcean.nNumX) / 2;		// ポリゴンの幅
	float	fHeight	= (fPolygonLength * m_DataOcean.nNumZ) / 2;		// ポリゴンの奥行き
	float	fX		= -fWidth;										// 頂点座標のX軸
	float	fZ		= fHeight;										// 頂点座標のZ軸
	int		nP		= 0;											// ポリゴンカウンター 

	NEW_TYPE_ARRAY(m_pVertex, D3DXVECTOR3, m_nVerTexMax);

	// 頂点座標設定
	for( int z = 0; z < m_DataOcean.nNumZ + 1; z++, fZ -= fPolygonLength)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataOcean.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// 横の枚数分
			pVtx[nP].vtx		= D3DXVECTOR3(fX, 0, fZ);				// 頂点座標設定
			m_pVertex[nP]		= pVtx[nP].vtx;							// 頂点格納
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// 頂点色設定
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 法線設定
		}
		fX		= -fWidth;			// ポリゴン幅を初期化
	}

	nP = 0;		// ポリゴンカウンター初期化

	// テクスチャの変数
	float fTexX			= 0.0f;									// テクスチャ座標のX軸
	float fTexY			= 0.0f;									// テクスチャ座標のY軸
	float fTexWidth		= 1.0f / m_DataOcean.nNumX * 1;			// テクスチャの幅 * 何回フリップさせるか
	float fTexHeight	= 1.0f / m_DataOcean.nNumZ * 1;			// テクスチャの高さ * 何回フリップさせるか

	// テクスチャ座標設定
	for( int z = 0; z < m_DataOcean.nNumZ + 1; z++, fTexY -= fTexHeight )
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataOcean.nNumX + 1; x++, nP++, fTexX += fTexWidth )
		{
			// 横の枚数分
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// テクスチャ座標設定
		}
		fTexX	= 0.0f;			// テクスチャ幅を初期化	
	}

	// 頂点バッファのロック解
	m_pVertexBuffer->Unlock();

	// 面の数
	int  PrimitiveNum = (m_DataOcean.nNumX * m_DataOcean.nNumZ) * 2;

	// 面の法線を格納
	m_pNor = NULL;

	m_pNor = NEW D3DXVECTOR3[PrimitiveNum];

	// 法線算出
	NorVertex();		// 法線を取得

	// インデックス数														
	m_nIndexMax = ( ( (m_DataOcean.nNumX + 1) * 2 ) * m_DataOcean.nNumZ ) + ( ( m_DataOcean.nNumZ - 1 ) * 2 );

	// インデックスバッファ作成
	hr = pRenderer->GetDevice()->CreateIndexBuffer( sizeof(WORD) * m_nIndexMax , 
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
		if( index ==  (( m_DataOcean.nNumX * 2 ) + 1)  + gyo )
		{
			// 縮退ポリゴンの生成
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataOcean.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataOcean.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataOcean.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataOcean.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// 偶数だった場合
			pIdx[index] =  (m_DataOcean.nNumX + 1) + nNum_Gusu;
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

//=============================================================================
// 位置設定
//=============================================================================
void COcean::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos.x = fPosX;
	m_pos.y = fPosY;
	m_pos.z = fPosZ;
	m_DataOcean.pos = m_pos;
}

//=============================================================================
// 位置設定
//=============================================================================
void COcean::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_DataOcean.pos = m_pos;
}

//=============================================================================
// 角度設定
//=============================================================================
void COcean::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot.x = fRotX;
	m_rot.y = fRotY;
	m_rot.z = fRotZ;
	m_DataOcean.rot = m_rot;
}

//=============================================================================
// 角度設定
//=============================================================================
void COcean::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;
	m_DataOcean.rot = m_rot;
}

//=============================================================================
// 関数名	: SetTexNum
// 戻り値	: なし
// 引数値	: 画像番号
// 機能		: 画像番号変更
//=============================================================================
void COcean::SetTexNum(USHORT nTexNum)
{
	// テクスチャ取得
	CTexture *pTex = NULL;
	
	pTex = CManager::GetData()->GetTexture();

	/*switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pTex = CTitle::GetData()->GetTexture();
		break;
	case CManager::MODE_GAME:
		pTex = CGame::GetData()->GetTexture();
		break;
	case CManager::MODE_RESULT:
		pTex = CResult::GetData()->GetTexture();
		break;
	default:
		break;
	}*/

	if( pTex->GetTextureNum() < nTexNum || 
	m_nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = pTex->GetTexture(nTexNum);
	}

	m_DataOcean.nTexNum = nTexNum;
}


void COcean::NorVertex(void)
{
	VERTEX_3D *pVtx;					// 頂点数
	D3DXVECTOR3 Vector0;				// ベクトル
	D3DXVECTOR3 Vector1;				// ベクトル
	D3DXVECTOR3 CrossProduct;			// ベクトル
	float fLength;						// ベクトルの正規化

	int VectorNum0 = 0;
	int VectorNum1 = 0;
	int nCnt = 0;

	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for(int i = 0; i < m_DataOcean.nNumZ; i++)
	{
		for( int j = 0; j < m_DataOcean.nNumX; j++)
		{	
			////////////////////
			// ＼			  //
			// 　＼           //
		//--//　　 ＼         //
		//V	//       ＼       //
		//e	//  ここ   ＼     //
		//c	//           ＼   //
		//0	//             ＼ //
			////////////////////
						// |--Vec1
			// 計算式

			// 引く頂点の番号計算
			VectorNum0 = i * (m_DataOcean.nNumX + 1) + j;

			// 引かれる頂点の番号計算
			VectorNum1 = (i + 1) * (m_DataOcean.nNumX + 1) + j;

			// ベクトルを求める
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// 引く頂点の番号計算
			VectorNum0 = (i + 1) * (m_DataOcean.nNumX + 1) + ( j + 1 );

			// ベクトルを求める
			Vector1 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;
				
			// 法線ベクトルを求める
			CrossProduct.x = (Vector0.y * Vector1.z) - (Vector0.z * Vector1.y);
			CrossProduct.y = (Vector0.z * Vector1.x) - (Vector0.x * Vector1.z);
			CrossProduct.z = (Vector0.x * Vector1.y) - (Vector0.y * Vector1.x);

			// 法線ベクトルの正規化
			fLength = sqrtf( (CrossProduct.x * CrossProduct.x) + (CrossProduct.y * CrossProduct.y) + (CrossProduct.z * CrossProduct.z));

			// 法線ベクトルを格納
			m_pNor[nCnt].x = CrossProduct.x / fLength;
			m_pNor[nCnt].y = CrossProduct.y / fLength;
			m_pNor[nCnt].z = CrossProduct.z / fLength;
			nCnt++;

			
				// |---Vec0
			////////////////////
			// ＼			  //
			// 　＼ 　ここ    //
			//　　 ＼         //---Vec1
			//       ＼       //
			//  　　   ＼     //
			//           ＼   //
			//             ＼ //
			////////////////////

			// 計算式

			// 引く頂点の番号計算
			VectorNum0 = i * (m_DataOcean.nNumX + 1) + j;
			VectorNum1 = i * (m_DataOcean.nNumX + 1) + (j + 1);
			
			// ベクトルを求める
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// 引く頂点の番号計算
			VectorNum0 = (i + 1) * (m_DataOcean.nNumX + 1) + (j + 1);

			// ベクトルを求める
			Vector1 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// 法線ベクトルを求める
			CrossProduct.x = (Vector0.z * Vector1.y) - (Vector0.y * Vector1.z);
			CrossProduct.y = (Vector0.x * Vector1.z) - (Vector0.z * Vector1.x);
			CrossProduct.z = (Vector0.y * Vector1.x) - (Vector0.x * Vector1.y);

			// 法線ベクトルの正規化
			fLength = sqrtf( (CrossProduct.x * CrossProduct.x) + (CrossProduct.y * CrossProduct.y) + (CrossProduct.z * CrossProduct.z));

			// 法線ベクトルを格納
			m_pNor[nCnt].x = CrossProduct.x / fLength;
			m_pNor[nCnt].y = CrossProduct.y / fLength;
			m_pNor[nCnt].z = CrossProduct.z / fLength;
			nCnt++;
		}
	}

	nCnt = 0;
	D3DXVECTOR3 wark;
	int Num0 = 0;
	int Num1 = 0;

	// 各頂点の法線を求める
	for(int i = 0; i < m_DataOcean.nNumZ + 1 ; i++)
	{
		for( int j = 0; j < m_DataOcean.nNumX + 1; j++)
		{	
			Num0 = i * (m_DataOcean.nNumX * 2 ) + (j * 2) ;
			Num1 = Num0 - ( m_DataOcean.nNumX * 2 );
			if( i == 0 )
			{
				// 一段目の
				if( j == 0 )
				{
					// 一番左はし
					wark = ( m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 2;
				}
				else if( j == m_DataOcean.nNumX )
				{
					// 一番右はし
					wark = m_pNor[ Num0 + 1]; 
				}
				else
				{
					// それ以外
					wark = ( m_pNor[ Num0 - 1 ] + m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 3;
				}
			}
			else if( i == m_DataOcean.nNumZ )
			{
				// 最後の段の
				if( j == 0 )
				{
					// 一番左端
					wark = m_pNor[ Num1 + 1 ]; 	
				}
				else if( j == m_DataOcean.nNumX )
				{
					// 一番右端
					wark = ( m_pNor[ Num1 - 2 ] + m_pNor[ Num1 -1 ] ) / 2; 
				}
				else
				{
					// それ以外
					wark = ( m_pNor[ Num1 ] + m_pNor[ Num1 - 1 ] + m_pNor[ Num1 - 2 ] ) / 3;
				}
			}
			else
			{
				// 一番でも最後の段でもない段の
				if( j == 0 )
				{
					// 一番左端	
					wark = ( m_pNor[ Num1 ] + m_pNor[ Num0 + 1 ] + m_pNor[ Num0 ] ) / 3; 	
				}
				else if( j == m_DataOcean.nNumX )
				{
					// 一番右端
					wark = ( m_pNor[ Num1 - 1 ] + m_pNor[ Num1 - 2 ] + m_pNor[ Num0 - 1 ]  ) / 3; 
				}
				else
				{
					// それ以外
					wark = ( m_pNor[ Num1 ] + m_pNor[Num1 ] + m_pNor[ Num1 - 2 ] + m_pNor[ Num0 - 1 ] + m_pNor[ Num0 ] + m_pNor[ Num0 + 1] ) / 6;
				}
			}
			pVtx[nCnt].nor.x = wark.x;	// 法線を代入
			pVtx[nCnt].nor.y = wark.y;	// 法線を代入
			pVtx[nCnt].nor.z = wark.z;	// 法線を代入
			nCnt++;
		}
	} 

	// 頂点バッファのロック解
	m_pVertexBuffer->Unlock();
}

//=============================================================================
// 関数名	: LoadData 
// 戻り値	: 読み込みできたか
// 引数値	: 海データ
// 機能		: データ読み込み
//=============================================================================
bool COcean::LoadData(OCEAN dataOcean)
{
	HRESULT hr;

	// データを代入
	m_DataOcean = dataOcean;
	
	// 初期化処理
	hr = Init(m_DataOcean.fWidth, m_DataOcean.fLength,
		 m_DataOcean.nNumX, m_DataOcean.nNumZ, m_DataOcean.nTexNum);

	if( FAILED(hr) )
	{
		return false;		// エラーコード
	}
	return true;			// 正常コード
}