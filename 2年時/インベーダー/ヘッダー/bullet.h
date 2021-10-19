//-----------------------------------------------------------------------------
//
// �e���� �N���X		[bullet.h]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2�d�C���N���[�h�h�~
//-----------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "CScreen.h"
#include "common.h"
#include "object.h"
#include "explosion.h"

//-----------------------------------------------------------------------------
// �e�̃N���X
//-----------------------------------------------------------------------------
class CBullet  : public CObject
{
public:
	CBullet(void);																	// �e�̐���
	~CBullet(void);																	// �e�̔j��
	void Init(float fPosX, float fPosY, float fMoveX, float fMoveY);				// �e�̏�����
	void Uninit(void);																// �e�̔j��
	void Update(void);																// �e�̍X�V
	void Draw(void);																// �e�̕`��
	void GetPos(float *pPosX, float *pPosY){*pPosX = m_fPosX; *pPosY = m_fPosY;}	// �e�̌��݈ʒu���擾
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// �����̈ʒu�擾
	static CBullet *Create(float fPosX, float fPosY, float fMoveX, float fMoveY);	// �e�̐���
private:
	float m_fPosX;																	// �e�̌��݈ʒuX
	float m_fPosY;																	// �e�̌��݈ʒuY
	float m_fPosXOld;																// �e�̌������ʒuX
	float m_fPosYOld;																// �e�̌������ʒuY
	float m_fMoveX;																	// �e�̑��xX
	float m_fMoveY;																	// �e�̑��xY
	int m_nType;																	// �e���N�̂�
};

#endif // BULLET
