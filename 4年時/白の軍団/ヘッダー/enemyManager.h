/******************************************************************************
/ �G�Ǘ����� [enemyManager.h]
/ 
/ ����� : ���� �Y��
/
/ ����� : 2014�N1��
******************************************************************************/

//============================================================================
// 2�d�C���N���[�h
//============================================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

/*****************************************************************************
/ �C���N���[�h
*****************************************************************************/
#include "sceneModelGL.h"
#include "vector3D.h"
#include "enemy.h"

/*****************************************************************************
/ �N���X�錾
*****************************************************************************/
class CEnemyManager
{
public:

	static CEnemyManager *Create();	// �G�}�l�[�W������
	static void Release();			// �G�}�l�[�W���j��
	void Init(void);				// ������
	void UnInit(void);				// �I��
	void UpDate(void);				// �X�V

	static CEnemyManager *GetInstance(void)
	{
		return m_pInstance;			// �C���X�^���X�擾
	}

	void CountEnemy( int nEnemy );			// ���������G�̐��𐔂���

private:	
	CEnemyManager(void);					// �R���X�g���N�^
	~CEnemyManager(void);					// �f�X�g���N�^

	static CEnemyManager *m_pInstance;		// ���g�̃|�C���^
	void			SetTimeRandom(CEnemy::TYPE type);	// �G�̏o�����Ԑݒ�
	int				m_nTime;				// �}�l�[�W���[���� ( �S�̂̎��� )
	int				m_nAlphaTime;			// �A���t�@�o������
	int				m_nBetaTime;			// �x�[�^�o������
	int				m_nGammaTime;			// �K���}�o������
	int				m_nDeltaTime;			// �f���^�o������
};

#endif //_ENEMYMANAGER_H_

// EOF
