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
#include "data.h"
#include "stage.h"

//=============================================================================
// 関数名	: stage
// 戻り値	: なし
// 引数値	: なし	
// 機能		: インスタンス生成
//=============================================================================
CStage::CStage(void)
{
	m_bLoad		= false;							// ステージデータ読み込みフラグ初期化
	m_pSky		= NULL;								// 空ポインタ初期化
	m_pMountain	= NULL;								// 山ポインタ初期化
	ZeroMemory(&m_pField, sizeof(MAX_OBJECT) );		// 地面ポインタ初期化
	ZeroMemory(&m_pWall, sizeof(MAX_OBJECT) );		// 壁ポインタ初期化
	ZeroMemory(&m_pTree	, sizeof(MAX_OBJECT) );		// 木ポインタ初期化
	ZeroMemory(&m_pGrass, sizeof(MAX_OBJECT) );		// 草ポインタ初期化
	ZeroMemory(&m_pOcean, sizeof(MAX_OBJECT) );		// 海ポインタ初期化
	m_Point		= 0;								// 現在指している位置
	m_nFiledVerPoint = 0;							// 地面の頂点を指している位置
	m_nSpeed	= 1;								// 移動速度
	ZeroMemory(&m_ObjNum, sizeof(OBJ_NUM) );		// オブジェクト数
	ZeroMemory(&m_DataField[0], sizeof(FIELD) );		// 地面データ
	ZeroMemory(&m_DataWall[0], sizeof(WALL) );			// 壁データ
	ZeroMemory(&m_DataTree[0], sizeof(BILLBOARD) );		// 木データ
	ZeroMemory(&m_DataGrass[0], sizeof(BILLBOARD) );	// 草データ
	ZeroMemory(&m_DataOcean[0], sizeof(OCEAN) );		// 海データ
	m_nSetObj	= FIELD_OBJ;						// 現在何を調節しているのか
	m_nTexNum	= 0;								// 画像番号
	m_nEditMode = EDITMODE_CREATE;					// エディットモード設定
	memset(&m_Polygon, 0, sizeof(m_Polygon) );		// オブジェクト設定
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
	m_pSky = CSky::Create(100, 200, 20, 20, 30000.0f, 0);
	if( !m_pSky )
	{
		return E_FAIL;
	}

	m_pMountain = CMountain::Create(300, 100, 20, 15, 12000.0f, 1);
	if( !m_pMountain )
	{
		return E_FAIL;
	}

	m_pMountain->SetPosition( D3DXVECTOR3(0.0f, -200.0f, 0.0f) );

	for( int obj = 0; obj < MAX_OBJECT; obj++ )
	{
		m_pField[obj] = NULL;
		m_pWall[obj] = NULL;
		m_pTree[obj] = NULL;
		m_pGrass[obj] = NULL;
		m_pOcean[obj] = NULL;
	}

	// ポリゴン
	m_Polygon.fWidth	= 10.0f;
	m_Polygon.fHeight	= 10.0f;
	m_Polygon.fLength	= 10.0f;
	m_Polygon.nNumX		= 1;
	m_Polygon.nNumY		= 1;
	m_Polygon.nNumZ		= 1;



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
	CScene::ReleaseAll();						// シーン全破棄
}

//=============================================================================
// 関数名	: Update
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージ更新
//=============================================================================
void CStage::Update(void)
{
	char			*strEditMode = NULL;		// 現在エディットモードの種類
	char			*strSetObj = NULL;			// 何を調節しているのかを知らせる文字列
	int				nMaxNum = 0;				// 調節しているオブジェの最大数

	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	bool			bDebug = CManager::GetDebug()->GetDebugMode();

	// デバッグモード切替処理
	if( bDebug == true )
	{
		switch( m_nEditMode )
		{
		case EDITMODE_CREATE:
			EditCreate(pKeyboard);
			strEditMode = "オブジェクト作成";
			break;
		
		case EDITMODE_DELETE:
			EditDelete(pKeyboard);
			strEditMode = "オブジェクト破棄";
			break;

		case EDITMODE_MOVE:
			EditMove(pKeyboard);
			strEditMode = "オブジェクト移動";
			break;

		case EDITMODE_CHENGE:
			EditChange(pKeyboard);
			strEditMode = "オブジェクト画像切替";
			break;
		default:
			break;
		}


		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			strSetObj = "地面";
			nMaxNum = m_ObjNum.nFieldMax;
			break;

		case WALL_OBJ:
			strSetObj = "壁";
			nMaxNum = m_ObjNum.nWallMax;
			break;

		case TREE_OBJ:
			strSetObj = "木";
			nMaxNum = m_ObjNum.nTreeMax;
			break;

		case GRASS_OBJ:
			strSetObj = "草";
			nMaxNum = m_ObjNum.nGrassMax;
			break;
		
		case OCEAN_OBJ:
			strSetObj = "海";
			nMaxNum = m_ObjNum.nOceanMax;
			break;

		case MAX_OBJ:
			break;

		default:
			break;
		}

		if( pKeyboard->KeyPush(DIK_7) )
		{
			m_nEditMode = EDITMODE_CREATE;
		}
		else if( pKeyboard->KeyPush(DIK_8) )
		{
			m_nEditMode = EDITMODE_DELETE;
		}
		else if( pKeyboard->KeyPush(DIK_9) )
		{
			m_nEditMode = EDITMODE_MOVE;
		}
		else if( pKeyboard->KeyPush(DIK_0) )
		{
			m_nEditMode = EDITMODE_CHENGE;
		}
		

		if( pKeyboard->KeyPush(DIK_F11) )
		{
			SALF_RELEASE(m_pSky);
			SALF_RELEASE(m_pSky);
			SALF_RELEASE(m_pMountain);

			for( int wall = 0; wall < m_ObjNum.nWallMax; wall++ )
			{
				SALF_RELEASE(m_pWall[wall]);
			}
			
			for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
			{
				SALF_RELEASE(m_pField[field]);
			}

			for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
			{
				SALF_RELEASE(m_pTree[tree]);
			}

			Load();
		}
	

		if( pKeyboard->KeyPush(DIK_UP) )
		{
			m_Point++;
		}
		else if( pKeyboard->KeyPush(DIK_DOWN) )
		{
			if( m_Point > 0 )
			{
				m_Point--;
			}
		}
	
		if( pKeyboard->KeyPush(DIK_F5) )
		{
			if( m_nSetObj < MAX_OBJ - 1 )
			{
				m_nSetObj++;
			}
			m_Point = 0;
		}
		else if( pKeyboard->KeyPush(DIK_F6) )
		{
			if( m_nSetObj > FIELD_OBJ )
			{
				m_nSetObj--;
			}
			m_Point = 0;
		}
	}
	

	CScene::UpdateAll();
	CManager::GetDebug()->Print("現在のエディットモード %s\n", strEditMode);	
	CManager::GetDebug()->Print("現在 %sを調節中\n", strSetObj);
	CManager::GetDebug()->Print("地面の数 : %d\n", m_ObjNum.nFieldMax);
	CManager::GetDebug()->Print("壁の数 : %d\n", m_ObjNum.nWallMax);
	CManager::GetDebug()->Print("木の数 : %d\n", m_ObjNum.nTreeMax);
	CManager::GetDebug()->Print("草の数 : %d\n", m_ObjNum.nGrassMax);
	CManager::GetDebug()->Print("海の数 : %d\n", m_ObjNum.nOceanMax);
	CManager::GetDebug()->Print("画像番号 %d\n", m_nTexNum);
	CManager::GetDebug()->Print("ポイント: %d\n", m_Point);
	CManager::GetDebug()->Print("移動速度 %d\n", m_nSpeed);
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
// 関数名	: Save
// 戻り値	: HRESULT
// 引数値	: なし
// 機能		: ステージデータ書き込み
//=============================================================================
HRESULT CStage::Save(void)
{
	FILE *fp		= NULL;
	FILE *fpDebug	= NULL;
	int	 nVtxMax	= 0;
	float *fY		= 0;

	// データ取得
	if( m_pSky )
	{
		
		m_DataMountain	= m_pMountain->GetData();	// 山のデータ取得
	}

	// ファイルを開く
	fp = fopen("DATA/TEXT/game/stage.dat", "wb");
	if( fp == NULL )
	{
		// ファイル読み込み失敗
		return E_FAIL;
	}
	
	// ステージデータの書き込み
	fwrite(&m_ObjNum, sizeof(OBJ_NUM), 1, fp);

	if( m_pSky )
	{
		m_DataSky		= m_pSky->GetData();		// 空のデータ取得
		fwrite(&m_DataSky, sizeof(SKY), 1, fp);
	}

	if( m_pMountain )
	{
		m_DataMountain = m_pMountain->GetData();
		fwrite(&m_DataMountain, sizeof(SKY), 1, fp);
	}

	if( m_ObjNum.nFieldMax > 0 )
	{
		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			m_DataField[field] = m_pField[field]->GetData();
		}

		fwrite(&m_DataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp); 

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = m_pField[field]->GetFieldHeight();										// 
			fwrite(&fY[0], sizeof(float), m_DataField[field].nVerMax, fp);				// 地面の書き込み
		}
	}

	if( m_ObjNum.nWallMax > 0 )
	{
		// 壁の書き込み
		for( int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_DataWall[w] = m_pWall[w]->GetData();
		}
		fwrite(&m_DataWall[0], sizeof(WALL), m_ObjNum.nWallMax, fp);
	}

	if( m_ObjNum.nOceanMax > 0 )
	{
		// 海の書き込み
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_DataOcean[ocean] = m_pOcean[ocean]->GetData();
		}
		fwrite(&m_DataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
	}

	if( m_ObjNum.nTreeMax > 0 )
	{
		// 木の書き込み
		for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_DataTree[tree] = m_pTree[tree]->GetData();
		}
		fwrite(&m_DataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		// 草の書き込み
		for( int grass = 0; grass < m_ObjNum.nGrassMax; grass++ )
		{
			m_DataGrass[grass] = m_pGrass[grass]->GetData();
		}
		fwrite(&m_DataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
	}

	// ファイルを閉じる
	fclose(fp);

	// ファイル書き込み成功
	return S_OK;
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

	CField **pField = NULL;
	CWall **pWall = NULL;
	CTree **pTree = NULL;
	CGrass **pGrass = NULL;
	COcean **pOcean = NULL;


	// ファイルを開く
	fp = fopen("DATA/TEXT/game/stage.dat", "rb");
	if( fp == NULL )
	{
		// 読み込み失敗
		return false;
	}

	// ステージデータ読み込み
	nData = fread(&m_ObjNum, sizeof(OBJ_NUM), 1, fp);
	if( nData <= 0 )
	{
		// データ読み込み失敗
		return false;
	}

	if( !m_pSky )
	{
		fread(&m_DataSky, sizeof(SKY), 1, fp);
		m_pSky = CSky::CreateLoad(m_DataSky, 0);
	}
	if( !m_pMountain )
	{
		fread(&m_DataMountain, sizeof(MOUNTAIN), 1, fp);
		m_pMountain = CMountain::CreateLoad(m_DataMountain, 1);
	}

	if( m_ObjNum.nFieldMax > 0 )
	{
		if( !m_pField )
		{
			NEW_TYPE_ARRAY(pField, CField*, m_ObjNum.nFieldMax);
		}
	
		// 読み込み
		nData = fread(&m_DataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = NULL;
			m_DataField[field].fY = NULL;
			NEW_TYPE_ARRAY(fY, float, m_DataField[field].nVerMax);
			NEW_TYPE_ARRAY(m_DataField[field].fY, float, m_DataField[field].nVerMax);
			for( int i = 0; i < m_DataField[field].nVerMax; i++ )
			{
				m_DataField[field].fY[i] = 0.0f;
			}
			m_pField[field] = CField::CreateLoad(m_DataField[field], 2);
			fread(&fY[0], sizeof(float), m_DataField[field].nVerMax, fp);
			m_pField[field]->SetHeight(&fY[0]);
		}
	}

	if( m_ObjNum.nWallMax > 0 )
	{
		for( int i = 0; i < m_ObjNum.nWallMax; i++ )
		{
			nData = fread(&m_DataWall[i], sizeof(WALL), 1, fp);
		}
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		NEW_TYPE_ARRAY(pWall, CWall*, m_ObjNum.nWallMax); 
		for(int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_pWall[w] = CWall::CreateLoad(m_DataWall[w]);
		}
	}

	if( m_ObjNum.nOceanMax > 0 )
	{		
		// 読み込み
		nData = fread(&m_DataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}

		NEW_TYPE_ARRAY(pOcean, COcean*, m_ObjNum.nOceanMax);
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_pOcean[ocean] = COcean::CreateLoad(m_DataOcean[ocean]);
		}
	}


	if( m_ObjNum.nTreeMax > 0 )
	{
		nData = fread(&m_DataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}
		
		NEW_TYPE_ARRAY(pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_pTree[tree] = CTree::CreateLoad(m_DataTree[tree]);
		}
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		nData = fread(&m_DataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
		if( nData <= 0 )
		{
			// データ読み込み失敗
			return false;
		}
		
		NEW_TYPE_ARRAY(pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int grass = 0; grass < m_ObjNum.nTreeMax; grass++ )
		{
			m_pTree[grass] = CTree::CreateLoad(m_DataTree[grass]);
		}
	}


	// ファイルを閉じる
	fclose(fp);

	// 読み込み成功
	return true;
}


//=============================================================================
// 関数名	: EditCreate
// 戻り値	: なし
// 引数値	: CInputKeyboard *pKeyboard
// 機能		: オブジェクト作成
//=============================================================================
void CStage::EditCreate(CInputKeyboard *pKeyboard)
{
	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_ObjNum.nFieldMax < MAX_OBJECT )
			{
				for( int field = 0; field < MAX_OBJECT; field++ )
				{
					if( !m_pField[field] )
					{
						m_pField[field] = CField::Create(m_Polygon.fWidth, m_Polygon.fLength, m_Polygon.nNumX, m_Polygon.nNumZ, 2);
						m_DataField[field] = m_pField[field]->GetData();
						m_ObjNum.nFieldMax++;
						break;
					}
				}
			}
			break;

		case WALL_OBJ:
			if( m_ObjNum.nWallMax < MAX_OBJECT )
			{
				for(int wall = 0; wall < MAX_OBJECT; wall++ )
				{
					if( !m_pWall[wall] )
					{
						m_pWall[wall] = CWall::Create(m_Polygon.fWidth, m_Polygon.fHeight, m_Polygon.nNumX, m_Polygon.nNumY, 3);
						m_DataWall[wall] = m_pWall[wall]->GetData();
						m_ObjNum.nWallMax++;
						break;
					}
				}
			}
			break;

		case TREE_OBJ:
			if( m_ObjNum.nTreeMax < MAX_OBJECT )
			{
				for(int tree = 0; tree < MAX_OBJECT; tree++ )
				{
					if( !m_pTree[tree] )
					{
						m_pTree[tree] = CTree::Create(m_Polygon.fWidth, m_Polygon.fHeight, 3);
						m_DataTree[tree] = m_pTree[tree]->GetData();
						m_ObjNum.nTreeMax++;
						break;
					}
				}
			}
			break;

		case GRASS_OBJ:
			if( m_ObjNum.nGrassMax < MAX_OBJECT )
			{
				for(int grass = 0; grass < MAX_OBJECT; grass++ )
				{
					if( !m_pGrass[grass] )
					{
						m_pGrass[grass] = CGrass::Create(200, 200, 3);
						m_DataGrass[grass] = m_pGrass[grass]->GetData();
						m_ObjNum.nGrassMax++;
						break;
					}
				}
			}
			break;

		case OCEAN_OBJ:
			if( m_ObjNum.nOceanMax < MAX_OBJECT )
			{
				for( int ocean = 0; ocean < MAX_OBJECT; ocean++ )
				{
					if( !m_pOcean[ocean] )
					{
						m_pOcean[ocean] = COcean::Create(m_Polygon.fWidth, m_Polygon.fLength, m_Polygon.nNumX, m_Polygon.nNumZ, 0);
						m_DataOcean[ocean] = m_pOcean[ocean]->GetData();
						m_ObjNum.nOceanMax++;
						break;
					}
				}
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}


	// ポリゴンの大きさ設定
	if( pKeyboard->KeyPush(DIK_Y) )
	{
		m_Polygon.fWidth += 10.0f;
	}
	else if( pKeyboard->KeyPush(DIK_H) )
	{
		if( m_Polygon.fWidth > 10.0f )
		{
			m_Polygon.fWidth -= 10.0f;
		}
	}

	if( pKeyboard->KeyPush(DIK_U) )
	{
		m_Polygon.fHeight += 10.0f;
		m_Polygon.fLength += 10.0f;
	}
	else if( pKeyboard->KeyPush(DIK_J) )
	{
		if( m_Polygon.fHeight > 10.0f )
		{
			m_Polygon.fHeight -= 10.0f;
			m_Polygon.fLength -= 10.0f;
		}
	}

	// ポリゴンの数設定
	if( pKeyboard->KeyPush(DIK_I) )
	{
		m_Polygon.nNumX++;
	}
	else if( pKeyboard->KeyPush(DIK_K) )
	{
		if(	m_Polygon.nNumX > 1 )
		{
			m_Polygon.nNumX--;
		}
	}
	if( pKeyboard->KeyPush(DIK_O) )
	{
		m_Polygon.nNumY++;
		m_Polygon.nNumZ++;
	}
	if( pKeyboard->KeyPush(DIK_L) )
	{
		if( m_Polygon.nNumY > 1 )
		{
			m_Polygon.nNumY--;
			m_Polygon.nNumZ--;
		}
	}
	CManager::GetDebug()->Print("ポリゴンの幅 : %.3f\n", m_Polygon.fWidth);
	CManager::GetDebug()->Print("ポリゴンの高さ : %.3f\n", m_Polygon.fHeight);
	CManager::GetDebug()->Print("ポリゴンの奥行き : %.3f\n", m_Polygon.fLength);
	CManager::GetDebug()->Print("ポリゴンの横数 : %d\n", m_Polygon.nNumX);
	CManager::GetDebug()->Print("ポリゴンの縦数 : %d\n", m_Polygon.nNumY);
	CManager::GetDebug()->Print("ポリゴンの奥数 : %d\n", m_Polygon.nNumZ);
}

//=============================================================================
// 関数名	: EditDelete
// 戻り値	: なし
// 引数値	: CInputKeyboard *pKeyboard
// 機能		: オブジェクト破棄
//=============================================================================
void CStage::EditDelete(CInputKeyboard *pKeyboard)
{
	// 全オブジェクト削除
	if( pKeyboard->KeyPush(DIK_F10) )
	{
		SALF_RELEASE(m_pSky);
		SALF_RELEASE(m_pMountain);

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			SALF_RELEASE(m_pField[field]);
		}
		m_ObjNum.nFieldMax = 0;

		for( int wall = 0; wall < m_ObjNum.nWallMax; wall++ )
		{
			SALF_RELEASE(m_pWall[wall]);
		}
		m_ObjNum.nWallMax = 0;
			
		for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			SALF_RELEASE(m_pTree[tree]);
		}
		m_ObjNum.nTreeMax = 0;

		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			SALF_RELEASE(m_pOcean[ocean]);
		}
		m_ObjNum.nOceanMax = 0;
	}

	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				SALF_RELEASE(m_pField[m_Point]);
				m_ObjNum.nFieldMax--;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				SALF_RELEASE(m_pWall[m_Point]);
				m_ObjNum.nWallMax--;
			}
			break;
		
		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				SALF_RELEASE(m_pTree[m_Point]);
				m_ObjNum.nTreeMax--;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				SALF_RELEASE(m_pGrass[m_Point]);
				m_ObjNum.nGrassMax--;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				SALF_RELEASE(m_pOcean[m_Point]);
				m_ObjNum.nOceanMax--;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}
}

//=============================================================================
// 関数名	: EditMove
// 戻り値	: なし
// 引数値	: CInputKeyboard *pKeyboard
// 機能		: オブジェクト移動
//=============================================================================
void CStage::EditMove(CInputKeyboard *pKeyboard)
{
	VERTEX_3D		*pVtx;						// 頂点数
	CCamera			*pCamera = CManager::GetCamera();
	float			rotCamera = pCamera->GetRot();

	if( pKeyboard->KeyState(DIK_U) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField )
			{
				if( m_pField[m_Point] )
				{
					m_DataField[m_Point].rot.y += D3DX_PI / 50;
				}
			}
			break;

		case WALL_OBJ:
			if( m_pWall )
			{
				if( m_pWall[m_Point] )
				{
					m_DataWall[m_Point].rot.y += D3DX_PI / 50;
				}
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}			
	}
	else if(  pKeyboard->KeyState(DIK_O) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			m_DataField[m_Point].rot.y -= D3DX_PI / 50;
			break;
				
		case WALL_OBJ:
			m_DataWall[m_Point].rot.y -= D3DX_PI / 50;
			break;

		case OCEAN_OBJ:
			m_DataOcean[m_Point].rot.y -= D3DX_PI / 50;
			break;

		case MAX_OBJ:
			// 処理なし
			break;
				
		default:
			// 処理なし
			break;
		}
	}

	if( pKeyboard->KeyState(DIK_I) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;
		

		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}
	else if(  pKeyboard->KeyState(DIK_K) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;
				

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}
	if( pKeyboard->KeyState(DIK_J) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;


		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}	
	}
	else if( pKeyboard->KeyState(DIK_L) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}

	if( pKeyboard->KeyState(DIK_Y) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.y += m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.y += m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.y += m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.y += m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.y += m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}

	}
	else if( pKeyboard->KeyState(DIK_N) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.y -= m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// 処理なし
			break;

		default:
			// 処理なし
			break;
		}
	}
	if( pKeyboard->KeyPush(DIK_1) )
	{
		m_nSpeed += 1;
	}
	else if( pKeyboard->KeyPush(DIK_2) )
	{
		if( m_nSpeed > 1 )
		{
			m_nSpeed -= 1;
		}
	}

	switch( (SET_OBJ)m_nSetObj )
	{
	case FIELD_OBJ:
		if( m_pField[m_Point] )
		{	
			m_pField[m_Point]->GetVertex()->Lock(0 , 0 , (void **)&pVtx , 0);
			if( pKeyboard->KeyState(DIK_P) )
			{
				pVtx[m_nFiledVerPoint].vtx.y += m_nSpeed;
			} 
			
			else if( pKeyboard->KeyState(DIK_M) )
			{
				if( m_pField[m_Point] )
				{
					pVtx[m_nFiledVerPoint].vtx.y -= m_nSpeed;
				}
			}

			if( pKeyboard->KeyPush(DIK_LEFT) )
			{
				if( m_nFiledVerPoint > 0 )
				{
					m_nFiledVerPoint--;
				}	
			}
			else if( pKeyboard->KeyPush(DIK_RIGHT) )
			{
				if( m_nFiledVerPoint < m_pField[m_Point]->GetData().nVerMax - 1 )
				{
					m_nFiledVerPoint++;
				}
			}
			m_pField[m_Point]->GetVertex()->Unlock();

			m_pField[m_Point]->SetRotition(m_DataField[m_Point].rot);
			m_pField[m_Point]->SetPosition(m_DataField[m_Point].pos);
			CManager::GetDebug()->Print("地面の位置 : %f %f %f\n", 
										m_DataField[m_Point].pos.x, 
										m_DataField[m_Point].pos.y, 
										m_DataField[m_Point].pos.z );

			CManager::GetDebug()->Print("頂点[%d] %f %f %f\n", m_nFiledVerPoint, 
											pVtx[m_nFiledVerPoint].vtx.x, 
											pVtx[m_nFiledVerPoint].vtx.y, 
											pVtx[m_nFiledVerPoint].vtx.z);

		}
		break;

	case WALL_OBJ:
		if( m_pWall[m_Point] )
		{
			m_pWall[m_Point]->SetRotition(m_DataWall[m_Point].rot);
			m_pWall[m_Point]->SetPosition(m_DataWall[m_Point].pos);
			CManager::GetDebug()->Print("壁の位置 : %f %f %f\n", 
										m_DataWall[m_Point].pos.x, 
										m_DataWall[m_Point].pos.y, 
										m_DataWall[m_Point].pos.z );
		}
		break;
		
	case TREE_OBJ:
		if( m_pTree[m_Point] )
		{
			m_pTree[m_Point]->SetPosition(m_DataTree[m_Point].pos);
			CManager::GetDebug()->Print("木の位置 : %f %f %f\n", 
										m_DataTree[m_Point].pos.x, 
										m_DataTree[m_Point].pos.y, 
										m_DataTree[m_Point].pos.z );
		}
		break;

	case GRASS_OBJ:
		if( m_pGrass[m_Point] )
		{
			m_pGrass[m_Point]->SetPosition(m_DataGrass[m_Point].pos);
			CManager::GetDebug()->Print("草の位置 : %f %f %f\n", 
										m_DataGrass[m_Point].pos.x, 
										m_DataGrass[m_Point].pos.y, 
										m_DataGrass[m_Point].pos.z );
		}
		break;

	case OCEAN_OBJ:
		if( m_pOcean[m_Point] )
		{
			m_pOcean[m_Point]->SetPosition(m_DataOcean[m_Point].pos);
			CManager::GetDebug()->Print("海の位置 : %f %f %f\n", 
										m_DataOcean[m_Point].pos.x, 
										m_DataOcean[m_Point].pos.y, 
										m_DataOcean[m_Point].pos.z );
		}

	case MAX_OBJ:
		// 処理なし
		break;

	default:
		// 処理なし
		break;
	}
		

}

//=============================================================================
// 関数名	: EditChange
// 戻り値	: なし
// 引数値	: CInputKeyboard *pKeyboard
// 機能		: オブジェクトの画像などを変更
//=============================================================================
void CStage::EditChange(CInputKeyboard *pKeyboard)
{
	if( pKeyboard->KeyPush(DIK_I) )
	{
		if( m_nTexNum < CManager::GetData()->GetTexture()->GetTextureNum() )
		m_nTexNum++;
	}
	else if( pKeyboard->KeyPush(DIK_K) )
	{
		if( m_nTexNum > 0 )
		{
			m_nTexNum--;
		}
	}
	else if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField )
			{
				if( m_pField[m_Point] )
				{
					m_pField[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case WALL_OBJ:
			if( m_pWall )
			{
				if( m_pWall[m_Point] )
				{
					m_pWall[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case TREE_OBJ:
			if( m_pTree )
			{
				if( m_pTree[m_Point] )
				{
					m_pTree[m_Point]->SetTextureNum(m_nTexNum);
				}
			}
			break;
			
		case OCEAN_OBJ:
			if( m_pOcean )
			{
				if( m_pOcean[m_Point] )
				{
					m_pOcean[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case MAX_OBJ:
			break;
		}
	}
}

	





