//=============================================================================
// 処理 [meshfield.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: メシュの多い地面生成
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "sceneline.h"
#include "data.h"
#include "field.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 自由に設定できる頂点フォーマット
#define TEX_XNUM			(30)		// テクスチャを何回フリップさせるか( X座標 )
#define TEX_YNUM			(30)		// テクスチャを何回フリップさせるか( Y座標 )

//=============================================================================
//	関数名	: CField
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス生成
//=============================================================================
CField::CField(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// インスタンス生成
	m_pVertexBuffer	= NULL;								// 頂点バッファ初期化
	m_pIndexBuffer	= NULL;								// インデックスバッファ初期化
	m_pTexture		= NULL;								// テクスチャポインタ初期化
	m_pNor			= NULL;								// 面の法線格納ポインタ初期化
	m_ppLine		= NULL;								// 法線ライン初期化
	m_nVerTexMax	= 0;								// 頂点数初期化
	m_nIndexMax		= 0;								// 添字数初期化
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 地面の位置初期化
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 地面の向き初期化
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 地面の大きさ初期化
	m_nPoint		= 0;								// 頂点ポイント初期化
	m_nSpeed		= 1;								// スピード初期化
	ZeroMemory(&m_DataField, sizeof(FIELD) );			// 地面データ初期化
	m_DataField.nTexNum		= -1;						// 画像番号初期化
}

//=============================================================================
//	関数名	: ~CField
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CField::~CField(void)
{
	// インスタンス破棄
}

//=============================================================================
//	関数名	: Init
//	戻り値	: 地面ポインタ
//	引数	: ポリゴンの大きさ(幅, 高さ), 枚数(横, 縦), テクスチャ番号
//	機能	: 地面の作成
//=============================================================================
CField *CField::Create( float fPolygonWidth , float fPolygonLength , 
						int nNumX , int nNumZ, USHORT nTexNum)
{
	// 変数宣言
	HRESULT hr;				// 結果
	CField *pField = NULL;	// 地面ポインタ	

	// 地面生成
	NEW_TYPE(pField, CField);			
	hr = pField->Init(fPolygonWidth, fPolygonLength, nNumX, nNumZ, nTexNum);	// 地面初期化
	if( FAILED(hr) )
	{
		// エラーチェック
		return NULL;		// エラーコード
	}
	return pField;			// 正常コード
}

//=============================================================================
//	関数名	: CreateLoad
//	戻り値	: 地面ポインタ
//	引数	: 地面データ, 地面の高さ, テクスチャ番号
//	機能	: 地面の作成
//=============================================================================
CField *CField::CreateLoad(FIELD dataField, USHORT nTexNum)
{
	// 変数宣言
	HRESULT hr;				// 結果
	CField *pField = NULL;	// 地面ポインタ	
	bool	bLoad = true;	// データが読み込めたか

	// メモリ確保
	NEW_TYPE(pField, CField);							// 地面生成

	// データ読み込み
	bLoad = pField->LoadData(dataField);		// 地面データ読み込み
	if( !bLoad )
	{
		// 読み込み失敗
		return NULL;
	}

	hr = pField->MakeVerTex(dataField.fWidth, dataField.fLength);
	if( FAILED(hr) )
	{
		return NULL;
	}

	pField->SetPosition(dataField.pos);
	pField->SetRotition(dataField.rot);

	// 地面生成成功
	return pField;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: HRESULT
//	引数	: ポリゴンの大きさ(幅, 高さ), 枚数(横, 縦), テクスチャ番号
//	機能	: 地面の初期化
//=============================================================================
HRESULT CField::Init(float fPolygonWidth, float fPolygonLength, 
					int nNumX, int nNumZ, USHORT nTexNum)
{
	///// 地面初期化処理開始 /////
	// 変数宣言
	HRESULT hr; 
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き初期化
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさ初期化

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

	m_DataField.nTexNum = nTexNum;						// テクスチャ番号保存
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataField.nTexNum || 
		m_DataField.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataField.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}
	
	// ポリゴンの大きさ保存
	m_DataField.fWidth = fPolygonWidth;	// ポリゴンの幅保存
	m_DataField.fLength = fPolygonLength;	// ポリゴンの高さ保存

	// ポリゴン数保存
	m_DataField.nNumX = nNumX;	// 横のポリゴン数保存
	m_DataField.nNumZ = nNumZ;	// 縦のポリゴン数保存

	// 位置保存
	m_DataField.pos = m_pos;	// 位置保存
	m_DataField.rot = m_rot;	// 向き保存
	m_DataField.scl = m_scl;	// 大きさ保存

	// 頂点数計算
	m_nVerTexMax = ( (m_DataField.nNumX + 1) * (m_DataField.nNumZ + 1) );	// 横のポリゴン数 + 1 * 縦のポリゴン数 + 1

	m_DataField.nVerMax = m_nVerTexMax;

	NEW_TYPE_ARRAY(m_DataField.fY, float, m_nVerTexMax);

	for( int y = 0; y < m_nVerTexMax; y++ )
	{
		m_DataField.fY[y] = 0.0f;
	}

	// 頂点作成
	hr = MakeVerTex(fPolygonWidth, fPolygonLength);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}


//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: 地面の破棄
//=============================================================================
void CField::Uninit(void)
{
	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		SALF_RELEASE(m_ppLine[l]);
	}
	SALF_RELEASE(m_pVertexBuffer);		// 頂点バッファ破棄
	SALF_RELEASE(m_pIndexBuffer);		// 添字バッファ破棄
	SALF_DELETE_ARRAY(m_pNor);			// 法線保存バッファ破棄
	SALF_DELETE_ARRAY(m_ppLine);		// 法線ライン破棄
	SALF_DELETE_ARRAY(m_DataField.fY);	// 頂点Y破棄
	Release();							// 地面破棄
}

//=============================================================================
//	関数名	: Update
//	引数	: なし
//	機能	: 地面の更新
//=============================================================================
void CField::Update(void)
{
	VERTEX_3D *pVtx;	// 頂点数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	/*if( CManager::GetInput()->KeyPush(DIK_F1) )
	{
		m_DataField.nTexNum++;
	}
	else if( CManager::GetInput()->KeyPush(DIK_F2) )
	{
		m_DataField.nTexNum--;
	}
	if( m_DataField.nTexNum < CGame::GetData()->GetTexture()->GetTextureNum() )
	{
		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_DataField.nTexNum);
	}
	else
	{
		m_pTexture = NULL;
	}*/

	if( CManager::GetDebug()->GetDebugMode() == true )
	{
		// デバッグモード
		if( pKeyboard->KeyPush(DIK_9) )
		{
			GetNormalVec();
		}

		m_pVertexBuffer->Lock(0 , 0 , (void **)&pVtx , 0);

		if( !m_ppLine[0] )
		{
			NEW_TYPE_ARRAY(m_ppLine, CSceneLine*, m_nVerTexMax);
			for( int line = 0; line < m_nVerTexMax; line++ )
			{
				m_ppLine[line] = CSceneLine::Create( pVtx[line].vtx  , pVtx[line].nor , 255, 255, 255, 255);
			}
		}
		for( int y = 0; y < m_nVerTexMax; y++ )
		{
			m_DataField.fY[y] = pVtx[y].vtx.y;
		}

		m_pVertexBuffer->Unlock();
	}
	else
	{
		if( m_ppLine )
		{
			// ラインが存在したら
			for( int line = 0; line < m_nVerTexMax; line++ )
			{
				SALF_RELEASE(m_ppLine[line]);
			}
		}
	}
}

//=============================================================================
//	関数名	: Draw
//	引数	: なし
//	機能	: 地面の描画
//			: 大きさ反映
//			: 向き反映
//			: 場所反映
//			: ワールドマトリックスの設定
//			: 頂点情報設定
//			: テクスチャセット
//=============================================================================
void CField::Draw(void)
{
	// 変数宣言
	D3DXMATRIX mtxScl;		// スケールマトリックス
	D3DXMATRIX mtxRot;		// ロットマトリックス
	D3DXMATRIX mtxTrans;	// トランスマトリックス
	
	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();		

	// ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);					

	// スケール反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
		
	// 回転反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックス設定
	pRenderer->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld );

	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// 頂点情報設定
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_3D);

	// 頂点バッファセット
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pRenderer->GetDevice()->SetIndices(m_pIndexBuffer);

	// プリミティブ表示
	pRenderer->GetDevice()->DrawIndexedPrimitive(
							CManager::GetDebug()->GetPolygonLine(),	// プリミティブの種類
							0,							// どこから書くか
							0,
							m_nVerTexMax,				// 頂点数分
							0,
							m_nIndexMax - 2);			// ポリゴン数(3角1つで1個)
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CField::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// 位置設定
	m_DataField.pos = m_pos;						// 現在位置保存
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 位置設定
//=============================================================================
void CField::SetPosition(D3DXVECTOR3 pos)
{ 
	m_pos = pos;				// 位置設定
	m_DataField.pos = m_pos;		// 位置保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 角度設定
//=============================================================================
void CField::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// 向き設定
	m_DataField.rot = m_rot;						// 現在向き保存
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 角度設定
//=============================================================================
void CField::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// 向き設定
	m_DataField.rot = m_rot;	// 現在向き保存
}

//=============================================================================
// 関数名	: SetHeight
// 戻り値	: なし
// 引数値	: 向き( X, Y, Z )
// 機能		: 地面の高さ設定
//=============================================================================
void CField::SetHeight(float *fY)
{
	VERTEX_3D *pVtx = NULL;

	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	for( int y = 0; y < m_DataField.nVerMax; y++ )
	{
		pVtx[y].vtx.y = fY[y];
	}

	GetNormalVec();					// 法線算出

	m_pVertexBuffer->Unlock();		// 
}

//=============================================================================
// 関数名	: SetTexNum
// 戻り値	: なし
// 引数値	: 画像番号
// 機能		: 画像設定
//=============================================================================
void	CField::SetTexNum(USHORT nTexNum)
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

	m_DataField.nTexNum = nTexNum;						// テクスチャ番号保存
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataField.nTexNum || 
		m_DataField.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataField.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}
}

//=============================================================================
// 関数名	: GetHeight
// 戻り値	: なし
// 引数値	: 位置( X, Y, Z )
// 機能		: 高さ取得
//=============================================================================
float CField::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;	// 頂点数
	float fCross = 0;
	int Num0 = 0;
	int Num1 = 0;
	int Num2 = 0;
	float fPolygonLength;

	D3DXVECTOR3 Vector0 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 Vector1 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 Vector2 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 HitVector = D3DXVECTOR3( 0, 0, 0 ); 

	int nCntPrimitive = 0;
		
	// 頂点ロック
	 m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for(int nCntZ = 0; nCntZ < m_DataField.nNumZ; nCntZ++)
	{
		for(int nCntX = 0; nCntX < m_DataField.nNumX; nCntX++)
		{

				/////////////////
				//＼           //
				//  ＼	--Vec1 //
	//	|-------//    ＼       //
	//	Vec0	//      ＼     //
	//			//        ＼   //
				//          ＼ //
				/////////////////
	//					|--Vec2
					
			Num0 = nCntZ * (m_DataField.nNumX + 1) + nCntX;
			Num1 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX;
			Num2 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX + 1;

			Vector0 = pVtx[ Num0 ].vtx - pVtx[ Num1 ].vtx;
			Vector1 = pVtx[ Num2 ].vtx - pVtx[ Num0 ].vtx;
			Vector2 = pVtx[ Num1 ].vtx - pVtx[ Num2 ].vtx;

			HitVector = pos - pVtx[ Num1 ].vtx;			// プレイヤーの位置 - 左下の頂点

			fCross = (HitVector.x * Vector0.z) - ( HitVector.z * Vector0.x);
			if(fCross >= 0.0f)
			{
				HitVector = pos - pVtx[ Num0 ].vtx;
				fCross = (HitVector.x * Vector1.z) - ( HitVector.z * Vector1.x);
				if(fCross >= 0.0f)
				{
					HitVector = pos - pVtx[ Num2 ].vtx;
					fCross = (HitVector.x * Vector2.z) - ( HitVector.z * Vector2.x);
					if(fCross >= 0.0f)
					{
						fPolygonLength = pVtx[Num1].vtx.y - ( (m_pNor[nCntPrimitive].x * (pos.x - pVtx[Num1].vtx.x) + m_pNor[nCntPrimitive].z *
								(pos.z - pVtx[Num1].vtx.z) ) / m_pNor[nCntPrimitive].y);

						return fPolygonLength;
					}
				}
			}
			nCntPrimitive++;

			// ベクトルを算出するための添字を計算
			Num0 = nCntZ * (m_DataField.nNumX + 1) + nCntX;				// ベクトル添字計算
			Num1 = nCntZ * (m_DataField.nNumX + 1) + nCntX + 1;			// ベクトル添字計算
			Num2 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX + 1;		// ベクトル添字計算
			
			Vector0 = pVtx[ Num0 ].vtx - pVtx[ Num1 ].vtx;				// ベクトル算出
			Vector1 = pVtx[ Num2 ].vtx - pVtx[ Num0 ].vtx;				// ベクトル算出
			Vector2 = pVtx[ Num1 ].vtx - pVtx[ Num2 ].vtx;				// ベクトル算出
			
			HitVector = pos - pVtx[ Num1 ].vtx;			// 引数として持ってきたものの位置 - 左下の頂点

			// 外積計算
			fCross = (HitVector.x * Vector0.z) - ( HitVector.z * Vector0.x);
			if(fCross <= 0.0f)
			{
				HitVector = pos - pVtx[ Num0 ].vtx;
				fCross = (HitVector.x * Vector1.z) - ( HitVector.z * Vector1.x);
				if(fCross <= 0.0f)
				{
					HitVector = pos - pVtx[ Num2 ].vtx;
					fCross = (HitVector.x * Vector2.z) - ( HitVector.z * Vector2.x);
					if(fCross <= 0.0f)
					{
						fPolygonLength = pVtx[Num1].vtx.y - ( (m_pNor[nCntPrimitive].x * (pos.x - pVtx[Num1].vtx.x) + m_pNor[nCntPrimitive].z *
								(pos.z - pVtx[Num1].vtx.z) ) / m_pNor[nCntPrimitive].y);
						
						return fPolygonLength;
					}
				}
			}
			nCntPrimitive++;
		}
	}

	m_pVertexBuffer->Unlock();

	return pos.y;
}

//=============================================================================
// 関数名	: LoadData
// 戻り値	: なし
// 引数値	: なし
// 機能		: ファイルデータロード
//=============================================================================
bool CField::LoadData(FIELD dataField)
{
	FILE *fp = NULL;			// ファイルポインタ
	int	nError = 0;				// エラーチェック

	m_DataField = dataField;	// データを代入

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
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataField.nTexNum || 
		m_DataField.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataField.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}

	return true;
}


//=============================================================================
//	関数名	: MakeVerTex
//	戻り値	: HRESULT
//	引数	: なし
//	機能	: 地面の頂点を作る
//=============================================================================
HRESULT CField::MakeVerTex( float fPolygonWidth , float fPolygonLength)
{	
	// 変数宣言 
	HRESULT hr;			// 結果変数
	VERTEX_3D *pVtx;	// 頂点数
	WORD *pIdx;			// 添え字数

	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// 頂点数計算
	m_nVerTexMax = ( (m_DataField.nNumX + 1) * (m_DataField.nNumZ + 1) );	// 横のポリゴン数 + 1 * 縦のポリゴン数 + 1

	// 頂点バッファ作成処理
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_3D) * m_nVerTexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	ERROR_CHACK(hr);	// エラーチェック

	m_ppLine = NULL;

	NEW_TYPE_ARRAY(m_ppLine, CSceneLine*, m_nVerTexMax);

	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		m_ppLine[l] = NULL;
	}

	// 頂点バッファのロック
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	// 頂点の変数
	float	fWidth	= (fPolygonWidth * m_DataField.nNumX) / 2;		// ポリゴンの幅
	float	fHeight	= (fPolygonLength * m_DataField.nNumZ) / 2;		// ポリゴンの奥行き
	float	fX		= -fWidth;								// 頂点座標のX軸
	float	fZ		= fHeight;								// 頂点座標のZ軸
	int		nP		= 0;									// ポリゴンカウンター 

	// 頂点座標設定
	for( int z = 0; z < m_DataField.nNumZ + 1; z++, fZ -= fPolygonLength)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataField.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// 横の枚数分
			pVtx[nP].vtx		= D3DXVECTOR3(fX, m_DataField.fY[nP], fZ);			// 頂点座標設定
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// 頂点色設定
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 法線設定
		}
		fX		= -fWidth;			// ポリゴン幅を初期化
	}

	nP = 0;		// ポリゴンカウンター初期化

	// テクスチャの変数
	float fTexX			= 0.0f;							// テクスチャ座標のX軸
	float fTexY			= 0.0f;							// テクスチャ座標のY軸
	float fTexWidth		= 1.0f / m_DataField.nNumX * TEX_XNUM;	// テクスチャの幅 * 何回フリップさせるか
	float fTexHeight	= 1.0f / m_DataField.nNumZ * TEX_YNUM;	// テクスチャの高さ * 何回フリップさせるか

	// テクスチャ座標設定
	for( int z = 0; z < m_DataField.nNumZ + 1; z++, fTexY -= fTexHeight)
	{
		// 縦の枚数分
		for( int x = 0; x < m_DataField.nNumX + 1; x++, nP++, fTexX += fTexWidth)
		{
			// 横の枚数分
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// テクスチャ座標設定
		}
		fTexX	= 0.0f;			// テクスチャ幅を初期化	
	}

	// 頂点バッファのロック解
	m_pVertexBuffer->Unlock();

	// 面の数
	int  PrimitiveNum = (m_DataField.nNumX * m_DataField.nNumZ) * 2;

	// 面の法線を格納
	m_pNor = NULL;

	m_pNor = NEW D3DXVECTOR3[PrimitiveNum];


	// 法線算出
	GetNormalVec();		// 法線を取得

	//					(横 + 1) の縦の数														
	m_nIndexMax = ( ( (m_DataField.nNumX + 1) * 2 ) * m_DataField.nNumZ ) + ( ( m_DataField.nNumZ - 1 ) * 2 );

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
		if( index ==  (( m_DataField.nNumX * 2 ) + 1)  + gyo )
		{
			// 縮退ポリゴンの生成
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataField.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataField.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataField.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataField.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// 偶数だった場合
			pIdx[index] =  (m_DataField.nNumX + 1) + nNum_Gusu;
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
// 関数名	: GetNormalVec
// 戻り値	: なし
// 引数値	: なし
// 機能		: 法線算出
//=============================================================================
void CField::GetNormalVec(void)
{
	VERTEX_3D *pVtx;	// 頂点数
	
	// 頂点ロック
	 m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		if( m_ppLine[l] )
		{
			m_ppLine[l]->Release();
			m_ppLine[l] = NULL;
		}
	}

	D3DXVECTOR3 Vector0;				// ベクトル
	D3DXVECTOR3 Vector1;				// ベクトル
	D3DXVECTOR3 CrossProduct;			// ベクトル
	float fLength;						// ベクトルの正規化

	int VectorNum0 = 0;
	int VectorNum1 = 0;
	int nCnt = 0;

	for(int i = 0; i < m_DataField.nNumZ ; i++)
	{
		for( int j = 0; j < m_DataField.nNumX; j++)
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
			VectorNum0 = i * (m_DataField.nNumX + 1) + j;

			// 引かれる頂点の番号計算
			VectorNum1 = (i + 1) * (m_DataField.nNumX + 1) + j;

			// ベクトルを求める
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// 引く頂点の番号計算
			VectorNum0 = (i + 1) * (m_DataField.nNumX + 1) + ( j + 1 );

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
			VectorNum0 = i * (m_DataField.nNumX + 1) + j;
			VectorNum1 = i * (m_DataField.nNumX + 1) + (j + 1);
			

			// ベクトルを求める
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// 引く頂点の番号計算
			VectorNum0 = (i + 1) * (m_DataField.nNumX + 1) + (j + 1);

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
	for(int i = 0; i < m_DataField.nNumZ + 1 ; i++)
	{
		for( int j = 0; j < m_DataField.nNumZ + 1; j++)
		{	
			Num0 = i * (m_DataField.nNumX * 2 ) + (j * 2) ;
			Num1 = Num0 - ( m_DataField.nNumX * 2 );
			if( i == 0 )
			{
				// 一段目の
				if( j == 0 )
				{
					// 一番左はし
					wark = ( m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 2;
				}
				else if( j == m_DataField.nNumX )
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
			else if( i == m_DataField.nNumZ )
			{
				// 最後の段の
				if( j == 0 )
				{
					// 一番左端
					wark = m_pNor[ Num1 + 1 ]; 	
				}
				else if( j == m_DataField.nNumX )
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
				else if( j == m_DataField.nNumX )
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
			
			if( CManager::GetDebug()->GetDebugMode() )
			{
				m_ppLine[nCnt] = CSceneLine::Create( pVtx[nCnt].vtx  , pVtx[nCnt].nor , 255, 255, 255, 255);
			}
			nCnt++;
		}
	}
	m_pVertexBuffer->Unlock();
}