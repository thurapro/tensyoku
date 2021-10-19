/******************************************************************************
/ �G���� [ enemy.cpp ]
/
/ �쐬�� : ���� �Y��
/
/ �쐬�� : 2014/02/10 @matsuo
/*****************************************************************************/

/*****************************************************************************
	�C���N���[�h
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
	�֐���	: CEnemy

	�߂�l	: �Ȃ�
	����	: �Ȃ�
	�@�\	: �G�C���X�^���X����
*****************************************************************************/
CEnemy::CEnemy(void)
{
	// ����������
	m_pCollision = NULL;
}

/*****************************************************************************
	�֐���	: �`CEnemy

	�߂�l	: �Ȃ�
	����	: �Ȃ�
	�@�\	: �G�C���X�^���X�j��
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

