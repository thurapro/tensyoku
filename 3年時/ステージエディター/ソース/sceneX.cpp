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
#include "manager.h"
#include "data.h"
#include "sceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_NUM_INIT		( -1 )		// モデル番号初期化
#define TEXTURE_NUM_INIT	( -1 )		// テクスチャ番号初期化

//=============================================================================
//	関数名	: CSceneX
//	戻り値	: なし
//	引数	: nPriority 優先順位  objType オブジェクトの種類
//	機能	: インスタンス生成 ( 初期化 )
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの位置
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの向き
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// Xオブジェクトの大きさ
	m_oldpos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの前回位置
	m_oldrot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの前回向き
	m_oldscl		= D3DXVECTOR3(1.0f, 1.0f, 0.0f);		// Xオブジェクトの前回の大きさ
	m_nModelNum		= MODEL_NUM_INIT;						// モデル番号
	m_nTextureNum	= TEXTURE_NUM_INIT;						// テクスチャ番号
}

//=============================================================================
//	関数名	: ~CSceneX
//	戻り値	: なし
//	引数	: なし
//	機能	: インスタンス破棄
//=============================================================================
CSceneX::~CSceneX(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: Xオブジェクト ( 失敗した場合NULL )
// 引数値	: fPosX　表示位置X軸  fPosY 表示位置Y軸 fPosZ 表示位置Z軸
//				nModelNum モデル番号 nTextureNum テクスチャ番号 
// 機能		: Xオブジェクト作成
//=============================================================================
CSceneX *CSceneX::Create(float fPosX, float fPosY, float fPosZ, 
						USHORT nModelNum, USHORT nTextureNum)
{
	HRESULT hr;											// エラーチェック変数
	CSceneX *pSceneX = NULL;							// Xオブジェクトクラス変数
	NEW_TYPE(pSceneX, CSceneX);							// Xオブジェクトインスタンス生成
	hr = pSceneX->Init(fPosX, fPosY, fPosZ,	
						nModelNum, nTextureNum);		// Xオブジェクト初期化
	if( FAILED(hr) )
	{
		// Xオブジェクトの初期化失敗
		return NULL;									// 何も返さない
	}
	return pSceneX;										// Xオブジェクトを返す
}

//=============================================================================
//	関数名	: Init
//	戻り値	: なし
//	引数	: なし
//	機能	: Xオブジェクトの初期化
//=============================================================================
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//	関数名	: Init
//	戻り値	: エラーまたは正常
//	引数	: fPosX　表示位置X軸　fPosY 表示位置Y軸 fPosZ 表示位置Z軸
//				nModelNum モデル番号　nTextrueNum テクスチャ番号
//	機能	: Xオブジェクトの初期化
//=============================================================================
HRESULT CSceneX::Init(float fPosX, float fPosY, float fPosZ, 
					USHORT nModelNum, USHORT nTextureNum)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// Xオブジェクトの位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// Xオブジェクトの向き
	m_scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);			// Xオブジェクトの大きさ
	
	CData	*pData		= NULL;				// データ取得用
	
	// 今だけ
	pData = CManager::GetData();			// データ取得	


	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:				// ロゴの場合
	//	pData	= CLogo::GetData();			// ロゴからデータ取得
	//	break;

	//case CManager::MODE_TITLE:				// タイトルの場合
	//	pData = CTitle::GetData();			// タイトルからデータ取得
	//	break;

	//case CManager::MODE_TUTORIAL:			// チュートリアルの場合
	//	pData	= CTutorial::GetData();		// チュートリアルからデータ取得
	//	break;

	//case CManager::MODE_GAME:				// ゲームの場合
	//	pData = CGame::GetData();			// ゲームからデータ取得
	//	break;

	//case CManager::MODE_RESULT:				// リザルトの場合
	//	pData = CResult::GetData();			// リザルトからデータ取得
	//	break;

	//case CManager::MODE_RANKING:			// ランキングの場合
	//	pData = CRanking::GetData();		// ランキングからデータ取得
	//	break;

	//default:
	//	break;
	//}

	CModel			*pModel		= pData->GetModel();	// モデル取得
	CTexture		*pTexture	= pData->GetTexture();	// テクスチャ取得

	// モデル番号をセット
	m_nModelNum = nModelNum;	// モデル番号
	if( m_nModelNum >pData->GetModel()->GetNumber() 
		|| m_nModelNum < 0 )
	{
		// モデル番号が存在しなければ
		m_pTexture = NULL;			// エラーコード
	}
	else
	{
		// モデルデータ取得
		m_pXmodel = pModel->GetObj(m_nModelNum);
	}

	// テクスチャ番号をセット
	m_nTextureNum = nTextureNum;	// テクスチャ番号
	if( m_nTextureNum > pTexture->GetTextureNum() 
		|| m_nTextureNum < 0 )
	{
		// テクスチャが存在しない
		m_pTexture = NULL;				// エラーコード
	}
	else
	{
		// テクスチャデータ取得
		m_pTexture = pTexture->GetTexture(m_nTextureNum);
	}

	return S_OK;
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: Xオブジェクトの破棄
//=============================================================================
void CSceneX::Uninit(void)
{
	Release();
}

//=============================================================================
//	関数名	: Update
//	引数	: なし
//	機能	: Xオブジェクトの更新
//=============================================================================
void CSceneX::Update(void)
{
	CData	*pData		= NULL;		// データ取得用
	/*switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData = CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData = CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData = CResult::GetData();
		break;
	default:
		break;
	}*/

	// 今だけ
	pData = CManager::GetData();

	if( CManager::GetKeyboard()->KeyPush(DIK_1) )
	{
		m_nModelNum += 1;
		if( pData->GetModel()->GetNumber() < m_nModelNum )
		{
			m_nModelNum = 0;
		}
		m_pXmodel = pData->GetModel()->GetObj(m_nModelNum);
	}

	if( CManager::GetKeyboard()->KeyPush(DIK_2) )
	{
		m_nTextureNum++;
		if( m_nTextureNum >pData->GetTexture()->GetTextureNum() )
		{
			m_nTextureNum = 0;
		}
		m_pXmodel = pData->GetModel()->GetObj(m_nModelNum);
	}
}

//=============================================================================
//	関数名	: Draw
//	引数	: なし
//	機能	: Xオブジェクトの描画
//			: 大きさ反映
//			: 向き反映
//			: 場所反映
//			: ワールドマトリックスの設定
//			: 頂点情報設定
//			: テクスチャセット
//=============================================================================
void CSceneX::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	// 変数宣言
	D3DXMATRIX mtxScl ;			// 大きさの設定
	D3DXMATRIX mtxRot ;			// 向きの設定
	D3DXMATRIX mtxTrans;		// 位置の設定
	D3DXMATERIAL *pD3DMat;		// マテリアル設定

	// ワールドマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);					// ワールドマトリックス初期化

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

	// レンダーステート設定
	pRenderer->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Xオブジェクト設定
	pD3DMat = (D3DXMATERIAL *)m_pXmodel.pMatBuff->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_pXmodel.nNumMat; nCntMat++)
	{
		pRenderer->GetDevice()->SetMaterial(&pD3DMat[nCntMat].MatD3D );
		pRenderer->GetDevice()->SetTexture(0, m_pTexture);
		m_pXmodel.pMesh->DrawSubset(nCntMat);
	}

	// レンダーステート初期化設定
	pRenderer->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
// 関数名	: SetPosition
// 戻り値	: なし
// 引数		: なし
// 機能		: 位置セット
//=============================================================================
void CSceneX::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}

//=============================================================================
// 関数名	: SetRotition
// 戻り値	: なし
// 引数		: なし
// 機能		: 向きセット
//=============================================================================
void CSceneX::SetRotition(float fPosX, float fPosY, float fPosZ)
{
	m_rot = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}

//=============================================================================
// 関数名	: SetScale
// 戻り値	: なし
// 引数		: なし
// 機能		: 大きさセット
//=============================================================================
void CSceneX::SetScale(float fPosX, float fPosY, float fPosZ)
{
	m_scl = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}