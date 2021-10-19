//-----------------------------------------------------------------------------
//
// �������� �N���X		[explosion.h]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2�d�C���N���[�h�h�~
//-----------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "object.h"

//-----------------------------------------------------------------------------
// �����̃N���X
//-----------------------------------------------------------------------------
class CExplosion : public CObject
{
public:
	typedef enum
	{
		STAR = 0,
		SQUARE,
		CIRCLE,
	};
	CExplosion(void);																// �����̐���
	~CExplosion(void);																// �����̔j��
	void Init(float fPosX, float fPosY);											// �����̏�����
	void Uninit(void);																// �����̔j��
	void Update(void);																// �����̍X�V
	void Draw(void);																// �����̕`��
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// �����̈ʒu�擾
	static CExplosion *Create(float fPosX, float fPosY);							// �����̐���
private:
	float m_fPosX;																	// �����̌��݈ʒuX
	float m_fPosY;																	// �����̌��݈ʒuY
	float m_fPosXOld;																// �����̌������ʒuX
	float m_fPosYOld;																// �����̌������ʒuY
	int	m_nTime;																	// ��������
	int m_nSelect;																	// �����̎��
	float m_fMoveX;																	// �����̑��xX
	float m_fMoveY;																	// �����̑��xY
};

#endif // BULLET
