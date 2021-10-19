/******************************************************************************
/ 敵処理 [ enemy.cpp ]
/
/ 制作者 : 松尾 雄太
/
/ 制作日 : 2014/01/20
******************************************************************************/

/*****************************************************************************
/ インクルード
*****************************************************************************/
#include "manager.h"
#include "DirectInput.h"
#include "enemyManager.h"
//#include "enemyAlpha.h"
//#include "enemyBeta.h"
//#include "enemyGamma.h"
//#include "enemyDelta.h"

/*****************************************************************************
/ マクロ定義
*****************************************************************************/
#define MAX_ENEMY ( 1 )			// 敵の最大数

/*****************************************************************************
/ 固定変数
*****************************************************************************/
static const int nTimer[] = { 100, 80, 300, 500 };
static const int nTimeAlpha[] = { 60, 100, 400, 300 };	// アルファの出現時間
static const int nTimeBeta[] = { 80, 200, 150, 400 };		// ベータの出現時間
static const int nTimeGamma[] = { 340, 500, 300, 60 };		// ガンマの出現時間
static const int nTimeDelta[] = { 5, 20, 30, 5 };		// デルタの出現時間

/*****************************************************************************
/ 静的メンバ変数
*****************************************************************************/
CEnemyManager	*CEnemyManager::m_pInstance = NULL;		// 自身のポインタ

/*****************************************************************************
/ 関数名	: CEnemy
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵インスタンス生成
*****************************************************************************/
CEnemyManager::CEnemyManager(void)
{
	// 敵の種類によっての出現時間設定
}

/*****************************************************************************
/ 関数名	: ~CEnemy
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵のインスタンス破棄
*****************************************************************************/
CEnemyManager::~CEnemyManager(void)
{
	// 特に処理なし
}

/*****************************************************************************
/ 関数名	: Create
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵マネージャ生成
*****************************************************************************/
CEnemyManager *CEnemyManager::Create(void)
{
	if( !m_pInstance )
	{
		// インスタンスがない場合
		m_pInstance = new CEnemyManager;	// 敵マネージャインスタンス生成
		m_pInstance->Init();				// 敵マネージャ初期化
		return m_pInstance;					// 敵マネージャを返す
	}
	return NULL;
}

/*****************************************************************************
/ 関数名	: Release
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵マネージャ破棄
*****************************************************************************/
void CEnemyManager::Release(void)
{
	if( m_pInstance )
	{
		// インスタンスがある場合
		delete m_pInstance;		// インスタンス破棄
		m_pInstance = NULL;		// NULL初期化
	}
}

/*****************************************************************************
/ 関数名	: UnInit
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 終了
*****************************************************************************/
void CEnemyManager::Init( void )
{
	SetTimeRandom(CEnemy::TYPE_ALPHA);
	SetTimeRandom(CEnemy::TYPE_BETA);
	SetTimeRandom(CEnemy::TYPE_DELTA);
	SetTimeRandom(CEnemy::TYPE_GAMMA);
	m_nTime = 0;
}

/*****************************************************************************
/ 関数名	: UnInit
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 終了
*****************************************************************************/
void CEnemyManager::UnInit(void)
{
	if( m_pInstance )
	{
		// インスタンスが存在していた場合
		delete m_pInstance;	// 敵マネージャインスタンス破棄
		m_pInstance = NULL;
	}
}

/*****************************************************************************
/ 関数名	: Update
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 更新
*****************************************************************************/
void CEnemyManager::UpDate(void)
{
	//// プレイヤーの位置取得
	// CPlayer *pPlayer = 0;
	// pPlayer = CManager::GetPlayer();

	CINPUTKEYBOARD *pKeyboard = CManager::GetKeyboard();
	CEnemy *pInstance = NULL;

	//-----------------------------------------------------------------
	// デバッグコード
	if( pKeyboard->Push( DIK_1 ) )
	{
		CEnemy::Create( CEnemy::TYPE_ALPHA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_2 ) )
	{
		CEnemy::Create( CEnemy::TYPE_BETA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_3 ) )
	{
		CEnemy::Create( CEnemy::TYPE_GAMMA, VECTOR3D(0, 0, 0) );
	}

	if( pKeyboard->Push( DIK_4 ) )
	{
		CEnemy::Create( CEnemy::TYPE_DELTA, VECTOR3D(0, 0, 0) );
	}

	//----------------------------------------------------------------------------------

	float fAngle = rand() % 200 / 100.0f;
	float fRadius = rand() % 100 / 10.0f;

	float fPosX = cosf(fAngle * CSceneGL::PI) * fRadius;
	float fPosY = sinf(fAngle * CSceneGL::PI) * fRadius;

	if( (m_nTime % m_nAlphaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_ALPHA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_ALPHA );
	}

	if( (m_nTime % m_nBetaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_BETA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(1.0f, 1.0f, 1.0f) );
		SetTimeRandom( CEnemy::TYPE_BETA );
	}

	if( (m_nTime % m_nDeltaTime) == 0 )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_DELTA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_DELTA );
	}

	if( (m_nTime % m_nGammaTime) == 0  )
	{
		pInstance = CEnemy::Create( CEnemy::TYPE_GAMMA, VECTOR3D(fPosX, fPosY, 0) );
		pInstance->SetScl( VECTOR3D(0.1f, 0.1f, 0.1f) );
		SetTimeRandom( CEnemy::TYPE_GAMMA );
	}


	m_nTime++;
}


/*****************************************************************************
/ 関数名	: SetTimeRandom
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵の出現時間をランダムで決める
*****************************************************************************/
void CEnemyManager::SetTimeRandom( CEnemy::TYPE type )
{
	int n = 0;					// ランダムで出た値の保管用
	int size = 0;
	switch( type )
	{
	case CEnemy::TYPE_ALPHA:
		{
			// ランダムで時間を設定
			size = ( sizeof( nTimeAlpha ) / sizeof( nTimeAlpha[0] ) );

			n = rand() % size;

			// アルファタイプの敵出現時間設定
			m_nAlphaTime = nTimeAlpha[n];
			break;
		}
	case CEnemy::TYPE_BETA:
		{
			size = ( sizeof( nTimeBeta ) / sizeof( nTimeBeta[0] ) );

			n = rand() % size;
	
			// アルファタイプの敵出現時間設定
			m_nBetaTime = nTimeBeta[n];
			break;
		}
	case CEnemy::TYPE_DELTA:
		{
			size = ( sizeof( nTimeDelta ) / sizeof( nTimeDelta[0] ) ); 

			n = rand() % size;
	
			// アルファタイプの敵出現時間設定
			m_nDeltaTime = nTimeDelta[n];
			break;
		}
	case CEnemy::TYPE_GAMMA:
		{
			size = ( sizeof( nTimeDelta ) / sizeof( nTimeDelta[0] ) );

			n = rand() %  size;

			// アルファタイプの敵出現時間設定
			m_nGammaTime = nTimeGamma[n];
			break;
		}
	}
}

