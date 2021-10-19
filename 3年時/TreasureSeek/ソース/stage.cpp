//=============================================================================
// ステージ処理 [ stage.cpp ]
//
// 製作者	: 松尾 雄太
//
// 機能		: ステージ設定
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "game.h"
#include "debugproc.h"
#include "stage.h"

//=============================================================================
// 関数名	: stage
// 戻り値	: なし
// 引数値	: なし	
// 機能		: インスタンス生成
//=============================================================================
CStage::CStage(void)
{
	m_bLoad		= false;	// ステージデータ読み込みフラグ初期化
	m_pSky		= NULL;		// 空ポインタ初期化
	m_pMountain	= NULL;		// 山ポインタ初期化
	m_pField	= NULL;		// 地面ポインタ初期化
	m_pWall		= NULL;		// 壁ポインタ初期化
	m_pTree		= NULL;		// 木ポインタ初期化
	m_pGrass	= NULL;		// 草ポインタ初期化
	m_pOcean	= NULL;		// 海ポインタ初期化
	m_Point		= 0;		// 現在指している位置
	m_nFiledVerPoint = 0;	// 地面の頂点を指している位置
	m_nSpeed	= 1;		// 移動速度
	ZeroMemory(&m_DataSky, sizeof(SKY) );					// 空データ
	ZeroMemory(&m_DataMountain, sizeof(MOUNTAIN) );			// 山データ
	m_pDataWall  = NULL;	// 壁データ
	m_pDataField = NULL;	// 地面データ
	m_pDataTree = NULL;		// 木データ
	m_pDataGrass = NULL;	// 草データ
	m_pDataOcean = NULL;	// 海データ
	m_nSetObj	= FIELD_OBJ; // 現在何を調節しているのか
	m_nTexNum	= 0;		 // 画像番号
}

//=============================================================================
// 関数名	: ~stage
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄
//=============================================================================
CStage::~CStage(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージ初期化
//=============================================================================
HRESULT CStage::Init(void)
{		
		// 空作成
		/*m_pSky = CSky::Create(100, 200, 20, 20, 90000.0f, 0);
		if( !m_pSky )
		{
			return E_FAIL;
		}

		m_pMountain = CMountain::Create(300, 100, 20, 10, 15000.0f, 1);
		if( !m_pMountain )
		{
			return E_FAIL;
		}
	
		NEW_TYPE_ARRAY(m_pOcean, COcean*, 1);

		m_pOcean[0] = COcean::Create(200, 200, 10, 10, 7);*/


	Load();

	
	// 地面作成
	/*m_pField = CField::Create(50, 50, 6, 6, 2);
	if( !m_pField )
	{
		return E_FAIL;
	}*/

	// 壁の数確保
	//NEW_TYPE_ARRAY(m_pDataWall, WALL, m_pDatanWallMax); 
	//NEW_TYPE_ARRAY(m_pWall, CWall*, MAX_WALL);

	//// 壁作成
	//for( int w = 0; w < m_pDatanWallMax; w++ )
	//{
	//	m_pWall[w] = CWall::Create(50, 50, 2, 2, 3);
	//	if( !m_pWall[w] )
	//	{
	//		return E_FAIL;
	//	}
	//}

	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージ破棄
//=============================================================================
void CStage::Uninit(void)
{
	CScene::ReleaseAll();					// シーン全破棄
	SALF_DELETE_ARRAY(m_pDataField);		// 地面の確保したメモリ分破棄(地面データ)
	SALF_DELETE_ARRAY(m_pField);			// 地面の確保したメモリ分破棄
	SALF_DELETE_ARRAY(m_pDataWall);			// 壁の確保したメモリ分破棄(壁データ)
	SALF_DELETE_ARRAY(m_pWall);				// 壁の確保したメモリ分破棄
}

//=============================================================================
// 関数名	: Update
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージ更新
//=============================================================================
void CStage::Update(void)
{
	char			*strSetObj = NULL;			// 何を調節しているのかを知らせる文字列
	int				nMaxNum = 0;				// 調節しているオブジェの最大数

	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera			*pCamera = CGame::GetCamera();
	float			rotCamera = pCamera->GetRot();
	bool			bDebug = CManager::GetDebug()->GetDebugMode();

	CScene::UpdateAll();
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージ描画
//=============================================================================
void CStage::Draw(void)
{
	CScene::DrawAll();	
}

//=============================================================================
// 関数名	: GetFieldNum
// 戻り値	: なし
// 引数値	: 数を格納するためのポインタ
// 機能		: 地面の数取得
//=============================================================================
void CStage::GetFieldNum(int &nFieldNum)
{
	nFieldNum = m_ObjNum.nFieldMax;
}

//=============================================================================
// 関数名	: GetWallNum
// 戻り値	: なし
// 引数値	: 数を格納するためのポインタ
// 機能		: 壁の数取得
//=============================================================================
void CStage::GetWallNum(int &nWallNum)
{
	nWallNum = m_ObjNum.nWallMax;
}

//=============================================================================
// 関数名	: Load
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージデータ読み込み
//=============================================================================
bool CStage::Load(void)
{
	FILE *fp = NULL;
	int	 nData = 0;

	// ファイルを開く
	fp = fopen("DATA/TEXT/game/stage.dat", "rb");
	if( fp == NULL )
	{
		// 読み込み失敗
		return false;
	}

	// オブジェクトの数読み込み
	nData = fread(&m_ObjNum, sizeof(OBJ_NUM), 1, fp); 

	// 空データ読み込み
	nData = fread(&m_DataSky, sizeof(SKY), 1, fp);
	if( nData <= 0 )
	{
		// データ読み込み失敗
		return false;
	}
	if( !m_pSky )
	{
		m_pSky = CSky::CreateLoad(m_DataSky, 0);
	}

	// 山データ読み込み
	nData = fread(&m_DataMountain, sizeof(MOUNTAIN), 1, fp);
	if( nData <= 0 )
	{
		// データ読み込み失敗
		return false;
	}
	if( !m_pMountain )
	{
		m_pMountain = CMountain::CreateLoad(m_DataMountain, 1);
	}

	if( nData <= 0 )
	{
		// データ読み込み失敗
		return false;
	}
	if( m_ObjNum.nFieldMax > 0 )
	{
		m_pDataField = NULL;
		NEW_TYPE_ARRAY(m_pDataField, FIELD, m_ObjNum.nFieldMax);
		
		// 読み込み
		nData = fread(&m_pDataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		NEW_TYPE_ARRAY(m_pField, CField*, m_ObjNum.nFieldMax);

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = NULL;
			m_pDataField[field].fY = NULL;
			NEW_TYPE_ARRAY(fY, float, m_pDataField[field].nVerMax);
			NEW_TYPE_ARRAY(m_pDataField[field].fY, float, m_pDataField[field].nVerMax);
			for( int i = 0; i < m_pDataField[field].nVerMax; i++ )
			{
				m_pDataField[field].fY[i] = 0.0f;
			}
			m_pField[field] = CField::CreateLoad(m_pDataField[field], 2);
			fread(&fY[0], sizeof(float), m_pDataField[field].nVerMax, fp);
			m_pField[field]->SetHeight(&fY[0]);
		}
	}


	if( m_ObjNum.nWallMax > 0 )
	{
		NEW_TYPE_ARRAY(m_pDataWall, WALL, m_ObjNum.nWallMax);

		for( int i = 0; i < m_ObjNum.nWallMax; i++ )
		{
			nData = fread(&m_pDataWall[i], sizeof(WALL), 1, fp);
		}
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		NEW_TYPE_ARRAY(m_pWall, CWall*, m_ObjNum.nWallMax); 
		for(int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_pWall[w] = CWall::CreateLoad(m_pDataWall[w]);
		}
	}

	if( m_ObjNum.nOceanMax > 0 )
	{
		m_pDataOcean = NULL;
		NEW_TYPE_ARRAY(m_pDataOcean, OCEAN, m_ObjNum.nOceanMax);
		
		// 読み込み
		nData = fread(&m_pDataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		NEW_TYPE_ARRAY(m_pOcean, COcean*, m_ObjNum.nOceanMax);
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_pOcean[ocean] = COcean::CreateLoad(m_pDataOcean[ocean]);
		}
	}


	if( m_ObjNum.nTreeMax > 0 )
	{
		m_pDataTree = NULL;
		NEW_TYPE_ARRAY(m_pDataTree, BILLBOARD, m_ObjNum.nTreeMax);
		nData = fread(&m_pDataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}
		NEW_TYPE_ARRAY(m_pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_pTree[tree] = CTree::CreateLoad(m_pDataTree[tree]);
		}
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		m_pDataGrass = NULL;
		NEW_TYPE_ARRAY(m_pDataGrass, BILLBOARD, m_ObjNum.nGrassMax);
		nData = fread(&m_pDataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}
		NEW_TYPE_ARRAY(m_pGrass, CGrass*, m_ObjNum.nGrassMax); 
		for(int grass = 0; grass < m_ObjNum.nGrassMax; grass++ )
		{
			m_pGrass[grass] = CGrass::CreateLoad(m_pDataGrass[grass]);
		}
	}

	// ファイルを閉じる
	fclose(fp);

	// 読み込み成功
	return true;
}
	

	





