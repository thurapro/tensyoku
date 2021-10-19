//=============================================================================
// 敵の処理[ enemy.cpp ]
//
// 製作者 : 松尾 雄太
//
// 機能 : 敵の処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "manager.h"
#include "camera.h"
#include "item.h"
#include "score.h"
#include "shadow.h"
#include "game.h"
#include "stage.h"
#include "enemy.h"

//=============================================================================
// 関数名	: CEnemy
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス生成
//=============================================================================
CEnemy::CEnemy(int nPriority, OBJTYPE objType):CSceneX(nPriority, objType)
{
	// インスタン生成
	m_pShadow = NULL;
}

//=============================================================================
// 関数名	: ~CEnemy
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス破棄
//=============================================================================
CEnemy::~CEnemy(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー生成
//=============================================================================
CEnemy *CEnemy::Create(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	CEnemy *pPlayer;		// プレイヤー宣言
	pPlayer = NEW CEnemy;	// プレイヤー生成
	hr = pPlayer->Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// プレイヤー初期化
	if( FAILED(hr) )
	{
		// プレイヤー生成失敗
		return NULL;		// エラーコード
	}
	return pPlayer;			// プレイヤーを戻す
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: プレイヤー初期化
//=============================================================================
HRESULT CEnemy::Init(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// プレイヤー初期化
	ERROR_CHACK(hr);												// エラーチェック
	m_rot.y = CGame::GetCamera()->GetRot();							// プレイヤーの向きを設定	
	m_fRadius	= 10.5f;											// プレイヤーの半径
	if( m_pShadow == NULL )
	{
		// 影を初期化
		m_pShadow =CShadow::Create(m_pos.x, m_pos.y, m_pos.z, 10, 0, 10, 5);
	}
	return S_OK;		// 正常終了
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー終了
//=============================================================================
void CEnemy::Uninit(void)
{
	CSceneX::Uninit();	// 終了処理
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー更新
//=============================================================================
void CEnemy::Update(void)
{
	CCamera *pCamera = NULL;
	CDebug *pDebug = CManager::GetDebug();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CField **pField = NULL;
	int		FieldMax = 0;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_GAME:
		pField = CGame::GetStage()->GetField();
		pCamera = CGame::GetCamera();
		break;
	case CManager::MODE_RESULT:
		break;
	}

	float fHeight = 0;
	float fRotition = 0;
	float fAngle = 0;

	CGame::GetStage()->GetFieldNum(FieldMax);

	if(pField)
	{
		// 地面が取得できたのなら
		for( int field = 0; field < FieldMax; field++ )
		{
			fHeight = pField[field]->GetHeight(m_pos);	// 地面の高さを取得
		}
	}
	
	m_pShadow->SetPosition( m_pos.x, fHeight + 1, m_pos.z);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー描画
//=============================================================================
void CEnemy::Draw(void)
{
	CSceneX::Draw();	// 描画処理
}

///// end of file /////