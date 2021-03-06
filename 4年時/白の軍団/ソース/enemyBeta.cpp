/******************************************************************************
/ 敵処理 [ enemyBeta.cpp ]
/
/ 制作者 : 松尾 雄太
/
/ 制作日 : 2014/01/20
******************************************************************************/

/*****************************************************************************
/ インクルード
*****************************************************************************/
#include "enemyBeta.h"
#include "score.h"
#include <math.h>

/*****************************************************************************
/ マクロ定義
*****************************************************************************/
#define BETA_HP		( 3 )		// 体力量
#define BETA_ATTACK	( 1 )		// 攻撃量

/*****************************************************************************
/ 関数名	: CEnemyBeta
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵インスタンス生成
*****************************************************************************/
CEnemyBeta::CEnemyBeta(void)
{
	m_pos = VECTOR3D( 0, 0, 0 );			// 位置
	m_move = VECTOR3D( 0, 0, 0 );			// 移動
	m_nHP = 0;								// 体力初期化	
	m_nAttack = 0;							// 攻撃力初期化
	m_nStopTime = 0;						// 移動停止時間
}


/*****************************************************************************
/ 関数名	: Create
/ 
/ 戻り値	: Enemyポインタ
/ 引数		: モデルパス,　位置
/ 機能		: 敵生成
*****************************************************************************/
CEnemyBeta *CEnemyBeta::Create( VECTOR3D pos )
{
	CEnemyBeta *pEnemy;

	pEnemy = new CEnemyBeta;
	pEnemy->Init( pos );
	return pEnemy;
}

/*****************************************************************************
/ 関数名	: Init
/ 
/ 戻り値	: なし
/ 引数		: モデルテキスト,　位置
/ 機能		: 初期化
*****************************************************************************/
void CEnemyBeta::Init( VECTOR3D pos )
{
	CSceneModelGL::Init( pos, "./data/model/teki2.obj" );
	m_move.x = 0.2f;
	m_fAngle = 0;

	// 衝突設定
	m_pCollision = CCollision::SetCollision( this,
										&m_pos,
										&m_move,
										CCollision::COL_SHAPE_SPHERE,
										COL_TYPE_PLAYER|
										COL_TYPE_PLBULLET,
										VECTOR3D( 1.0f, 1.0f, 1.0f ) );
										

	// 自身の種類
	m_colStatus.colType = COL_TYPE_ENEMY;
}


/*****************************************************************************
/ 関数名	: Update
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 更新
*****************************************************************************/
void CEnemyBeta::UpDate(void)
{
	CPlayer *pPlayer = CPhaseMain::GetPlayer();

	m_move.z = 0;
	
	m_move.x = cos( m_fAngle ) * 0.2;
	m_move.y = sin( m_fAngle ) * 0.2;
	m_move.z += 0.05; 

	m_pos += m_move;

	m_fAngle -= 4 * PI / 180;
	
	if( m_nHP < 0 )
	{
		Release();				// 存在を消す
		
		// @スコアー加算
	}

	else if( m_pos.z > pPlayer->GetPosition().z + 10 )
	{
		// 画面外に行ったら
		Release();				// 存在を消す
	}
}

/*****************************************************************************
/ 関数名	: Draw
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 描画
*****************************************************************************/
void CEnemyBeta::Draw(void)
{
	CSceneModelGL::Draw();
}



