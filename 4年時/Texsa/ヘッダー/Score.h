/**************************************************************************//**
* @file			Score.h
* @brief
* @author 		Hirai Yuuki
*****************************************************************************/
#ifndef	SCORE_H
#define SCORE_H

#include "Node.h"


namespace DirectX
{
	namespace SimpleMath
	{
		struct Vector2;
		struct Vector3;
	}
}

class Score :public MeekH::Node{
public:
	Score();
	~Score();
	void Init();
	void Update();

	int GetScore(void);
	void SetScore(int nScore);

private:
	DirectX::SimpleMath::Vector3 *m_pos;		// �\���ʒu�̒��S���W
	DirectX::SimpleMath::Vector3 *m_rot;		// ��]�p
	DirectX::SimpleMath::Vector3 *m_scl;		// �T�C�Y
	int m_nScore;
	bool m_bFlg;
};
#endif //SCORE_H