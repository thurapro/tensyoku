/*****************************************************************************
/ �C���N���[�h
*****************************************************************************/
#include "enemy.h"

/*****************************************************************************
/ �N���X�錾
*****************************************************************************/
class CEnemyGamma : public CEnemy
{
public:
	CEnemyGamma(void);			// �R���X�g���N�^
	void Init(void){}			// ������

	static CEnemyGamma *Create( VECTOR3D pos, const char *tex);		// �G����

	void Init( VECTOR3D pos, const char *tex);		// ������
	void UpDate(void);			// �X�V
	void Draw(void);			// �`��

private:
	float m_fAngle;				// ��]�p�x

};