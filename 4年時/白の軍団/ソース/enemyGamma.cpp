/******************************************************************************
/ 敵処理 [ enemyGamma.cpp ]
/
/ 制作者 : 松尾 雄太
/
/ 制作日 : 2014/01/20
/
/ 機能  : プレイヤーを途中まで追尾する
******************************************************************************/

/*****************************************************************************
/ インクルード
*****************************************************************************/
#include "enemyGamma.h"
#include "score.h"
#include "cphaseMain.h"
#include "player.h"
#include <math.h>

/*****************************************************************************
/ マクロ定義
*****************************************************************************/
#define GAMMA_HP		( 3 )		// 体力量
#define GAMMA_ATTACK	( 1 )		// 攻撃量

/*****************************************************************************
/ 関数名	: CEnemyGamma
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 敵インスタンス生成
*****************************************************************************/
CEnemyGamma::CEnemyGamma(void)
{
	m_pos = VECTOR3D( 0, 0, 0 );			// 位置
	m_move = VECTOR3D( 0, 0, 0 );			// 移動
	m_nHP = 0;								// 体力初期化	
	m_nAttack = 0;							// 攻撃力初期化
	m_nStopTime = 0;						// 移動停止時間

	m_fAngle = 0.2f;						

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
/ 関数名	: Create
/ 
/ 戻り値	: Enemyポインタ
/ 引数		: モデルパス,　位置
/ 機能		: 敵生成
*****************************************************************************/
CEnemyGamma *CEnemyGamma::Create( VECTOR3D pos, const char *tex )
{
	CEnemyGamma *pEnemy;

	pEnemy = new CEnemyGamma;
	pEnemy->Init( pos, tex );
	return pEnemy;
}

/*****************************************************************************
/ 関数名	: Init
/ 
/ 戻り値	: なし
/ 引数		: モデルテキスト,　位置
/ 機能		: 初期化
*****************************************************************************/
void CEnemyGamma::Init( VECTOR3D pos, const char *tex  )
{
	CSceneModelGL::Init( pos, tex );
	m_move.z = 0.5f;
}


/*****************************************************************************
/ 関数名	: Update
/ 
/ 戻り値	: なし
/ 引数		: なし
/ 機能		: 更新
*****************************************************************************/
void CEnemyGamma::UpDate(void)
{
	//// プレイヤーの位置取得
	CPlayer *pPlayer = CPhaseMain::GetPlayer();
	 VECTOR3D pos = pPlayer->GetPosition();

	//// プレイヤーと自分との距離を算出
	VECTOR3D Length = m_pos - pos;

	// 正数へ変換
	if( abs( Length.x ) > 0 )
	{
		m_move.x = -Length.x * 0.04f;
	}
	else if( abs( Length.x ) < 1 )
	{
		m_move.x = Length.x * 0.04f;
	}

	if( abs( Length.y ) > 0 )
	{
		m_move.y = -Length.y * 0.04f;
	}
	else if( abs( Length.y ) < 1 )
	{
		m_move.y = Length.y * 0.04f;
	}

	m_pos += m_move;

	if( m_pos.z > pPlayer->GetPosition().z + 10 )
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
void CEnemyGamma::Draw(void)
{
	CSceneModelGL::Draw();
}



