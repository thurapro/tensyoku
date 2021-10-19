/******************************************************************************
/ �G���� [ enemyGamma.cpp ]
/
/ ����� : ���� �Y��
/
/ ����� : 2014/01/20
/
/ �@�\  : �v���C���[��r���܂Œǔ�����
******************************************************************************/

/*****************************************************************************
/ �C���N���[�h
*****************************************************************************/
#include "enemyGamma.h"
#include "score.h"
#include "cphaseMain.h"
#include "player.h"
#include <math.h>

/*****************************************************************************
/ �}�N����`
*****************************************************************************/
#define GAMMA_HP		( 3 )		// �̗͗�
#define GAMMA_ATTACK	( 1 )		// �U����

/*****************************************************************************
/ �֐���	: CEnemyGamma
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �G�C���X�^���X����
*****************************************************************************/
CEnemyGamma::CEnemyGamma(void)
{
	m_pos = VECTOR3D( 0, 0, 0 );			// �ʒu
	m_move = VECTOR3D( 0, 0, 0 );			// �ړ�
	m_nHP = 0;								// �̗͏�����	
	m_nAttack = 0;							// �U���͏�����
	m_nStopTime = 0;						// �ړ���~����

	m_fAngle = 0.2f;						

	// �Փːݒ�
	m_pCollision = CCollision::SetCollision( this,
										&m_pos,
										&m_move,
										CCollision::COL_SHAPE_SPHERE,
										COL_TYPE_PLAYER|
										COL_TYPE_PLBULLET,
										VECTOR3D( 1.0f, 1.0f, 1.0f ) );
										

	// ���g�̎��
	m_colStatus.colType = COL_TYPE_ENEMY;

}


/*****************************************************************************
/ �֐���	: Create
/ 
/ �߂�l	: Enemy�|�C���^
/ ����		: ���f���p�X,�@�ʒu
/ �@�\		: �G����
*****************************************************************************/
CEnemyGamma *CEnemyGamma::Create( VECTOR3D pos, const char *tex )
{
	CEnemyGamma *pEnemy;

	pEnemy = new CEnemyGamma;
	pEnemy->Init( pos, tex );
	return pEnemy;
}

/*****************************************************************************
/ �֐���	: Init
/ 
/ �߂�l	: �Ȃ�
/ ����		: ���f���e�L�X�g,�@�ʒu
/ �@�\		: ������
*****************************************************************************/
void CEnemyGamma::Init( VECTOR3D pos, const char *tex  )
{
	CSceneModelGL::Init( pos, tex );
	m_move.z = 0.5f;
}


/*****************************************************************************
/ �֐���	: Update
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �X�V
*****************************************************************************/
void CEnemyGamma::UpDate(void)
{
	//// �v���C���[�̈ʒu�擾
	CPlayer *pPlayer = CPhaseMain::GetPlayer();
	 VECTOR3D pos = pPlayer->GetPosition();

	//// �v���C���[�Ǝ����Ƃ̋������Z�o
	VECTOR3D Length = m_pos - pos;

	// �����֕ϊ�
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
		// ��ʊO�ɍs������
		Release();				// ���݂�����
	}

}

/*****************************************************************************
/ �֐���	: Draw
/ 
/ �߂�l	: �Ȃ�
/ ����		: �Ȃ�
/ �@�\		: �`��
*****************************************************************************/
void CEnemyGamma::Draw(void)
{
	CSceneModelGL::Draw();
}



