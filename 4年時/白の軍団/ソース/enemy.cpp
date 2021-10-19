/******************************************************************************
/ 敵処理 [ enemy.cpp ]
/
/ 作成者 : 松尾 雄太
/
/ 作成日 : 2014/02/10 @matsuo
/*****************************************************************************/

/*****************************************************************************
	インクルード
*****************************************************************************/
#include "sceneModelGL.h"
#include "player.h"
#include "cphaseMain.h"
#include "enemyAlpha.h"
#include "enemyBeta.h"
#include "enemyGamma.h"
#include "enemyDelta.h"
#include "enemy.h"

/*****************************************************************************
	関数名	: CEnemy

	戻り値	: なし
	引数	: なし
	機能	: 敵インスタンス生成
*****************************************************************************/
CEnemy::CEnemy(void)
{
	// 初期化処理
	m_pCollision = NULL;
}

/*****************************************************************************
	関数名	: ～CEnemy

	戻り値	: なし
	引数	: なし
	機能	: 敵インスタンス破棄
*****************************************************************************/
CEnemy *CEnemy::Create(TYPE typeEnemy, VECTOR3D pos)
{
	CPlayer *pPlayer = CPhaseMain::GetPlayer();
	pos.z += pPlayer->GetPosition().z - 60.0f;
	
	CEnemy *pEnemy;
	switch( typeEnemy )
	{
	case TYPE_NONE:
		break;
	case TYPE_ALPHA:
		pEnemy = CEnemyAlpha::Create( pos );
		break;
	case TYPE_BETA:
		pEnemy = CEnemyBeta::Create( pos );
		break;
	case TYPE_GAMMA:
		pEnemy = CEnemyGamma::Create( pos, "./data/model/teki4.obj" );
		break;

	case TYPE_DELTA:
		pEnemy = CEnemyDelta::Create( pos, "./data/model/teki3.obj" );
		break;

	default:
		break;
	}
	return pEnemy;
}

