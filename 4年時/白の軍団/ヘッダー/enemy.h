/******************************************************************************
/ �G���� [ enemy.h ]
/
/ �쐬�� : ���� �Y��
/
/ �쐬�� : 2014/02/10 @matsuo
/*****************************************************************************/

/*****************************************************************************
	2�d�C���N���[�h�h�~
******************************************************************************/
#ifndef _ENEMY_H_
#define _ENEMY_H_

/*****************************************************************************
	�C���N���[�h
*****************************************************************************/
#include "sceneModelGL.h"
#include "collision.h"
#include "DebugProc.h"
#include "score.h"
#include "cphaseMain.h"
#include "player.h"
#include "sceneExplosion.h"

/*****************************************************************************
	�O���Q��
*****************************************************************************/	

/*****************************************************************************
	�N���X�錾
*****************************************************************************/
class CEnemy : public CSceneModelGL
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ALPHA,			// ���E�ړ�
		TYPE_BETA,			// ��]���Ȃ���ړ�
		TYPE_GAMMA,			// �ǔ�
		TYPE_DELTA,			// ���E�ړ�
		TYPE_MAX
	}TYPE;					// �G�̎��

	static CEnemy *Create(TYPE typeEnemy, VECTOR3D pos);	// �G�̐��� 
	CEnemy(void);					// �G�C���X�^���X����
	virtual ~CEnemy(void)
	{
		if( m_pCollision )
		{	
			m_pCollision->Release();
			m_pCollision = NULL;
		}
	}								// �G�C���X�^���X�j��
	void Init(){};					// �G������
	virtual void UnInit(void){};	// �G�I��

	virtual void UpDate(void) = 0;		// �G�X�V
	virtual void Draw(void) = 0;		// �G�`��

	virtual void OnHit( int tag, COLDETAIL detail, COLSTATUS colStatus )
	{
		switch( colStatus.colType )
		{
		case COL_TYPE_PLAYER:
			{
				colStatus.damage = 30;
				int nScore = CPhaseMain::GetScore()->GetScore();
				nScore -= colStatus.damage;
				CPhaseMain::GetScore()->SetScore(nScore);
				break;
			}
		case COL_TYPE_PLBULLET:
			{
				// ���_���[�W
				colStatus.damage = 1;

				m_nHP -= colStatus.damage;
				if( m_nHP < 1 )
				{
					CSceneExplosionGL::Create( 1.0f, 8.0f, 8.0f, m_pos.x, m_pos.y, m_pos.z );
					Release();
				}
				break;
			}
		}
	}

protected:
	CCollision*	m_pCollision;	// �Փ˃N���X
	int		m_nHP;				// �G�̗�
	int		m_nAttack;			// �G�U����
	float	m_nStopTime;		// �G�̒�~����

private:
};


#endif // _ENEMY_H_