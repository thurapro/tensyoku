//-----------------------------------------------------------------------------
//
// �G���� �N���X		[enemy.h]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2�d�C���N���[�h�h�~
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "object.h"
#include "common.h"
#include "bullet.h"

//-----------------------------------------------------------------------------
// �G�N���X
//-----------------------------------------------------------------------------
class CEnemy : public CObject
{
public:
	CEnemy(void);																// �R���X�g���N�^
	~CEnemy(void);																// �f�X�g���N�^
	void Init(float fPosX, float fPosY);										// �G�̏�����
	void Uninit(void);															// �G�̔j��
	void Update(void);															// �G�̍X�V
	void Draw(void);															// �G�̕`��
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// �����̈ʒu�擾
	static void GetNum(int *nCnt){*nCnt = m_nNumCnt;}
	static CEnemy *Create(float fPosX, float fPosY);							// �G�̍쐬
private:
	float m_fPosX;																// �G�̃|�W�V����X
	float m_fPosY;																// �G�̃|�W�V����Y
	float m_fPosXOld;															// �G�̑O�ɂ������WX
	float m_fPosYOld;															// �G�̑O�ɂ������WY
	float m_fMoveX;																// �G�̑��xX���� 
	float m_fMoveY;																// �G�̑��xY����
	bool m_bAlive;																// �G���|���ꂽ��
	int m_nShotTime;															// �e��łԊu
	static int m_nNumCnt;														// �G�̐�
};
#endif // _ENEMY_H_


