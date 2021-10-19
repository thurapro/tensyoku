/**************************************************************************//**
* @file			Result.h
* @brief
* @author 		Hirai Yuuki
*****************************************************************************/
#ifndef	RESULT_H
#define RESULT_H

#include "Node.h"

namespace DirectX
{
	namespace SimpleMath
	{
		struct Vector2;
		struct Vector3;
	}
}

class Result :public MeekH::Node{
public:
	Result();
	~Result();
	void Init();
	void Update();

	void SetMainScore(int score);
	int GetMainScore();
	void SetSabScore(int score);
	int GetSabScore();
	void SetTotalScore(int score);
	int GetTotalScore();
	void SetGoodScore(int score);
	int GetGoodScore();
	void SetBadScore(int score);
	int GetBadScore();

private:
	DirectX::SimpleMath::Vector3 *m_pos;		// �\���ʒu�̒��S���W
	DirectX::SimpleMath::Vector3 *m_rot;		// ��]�p
	DirectX::SimpleMath::Vector3 *m_scl;		// �T�C�Y
	int m_nMainScoreBase;						// MainScore�̒l������
	int m_nMainScore1;							// MainScore��1����
	int m_nMainScore2;							// MainScore��2����
	int m_nMainScore3;							// MainScore��3����
	int m_nMainScore4;							// MainScore��4����
	int m_nMainScore5;							// MainScore��5����

	int m_nSabScoreBase;						// SabScore�̒l������
	int m_nSabScore1;							// SabScore��1����
	int m_nSabScore2;							// SabScore��2����
	int m_nSabScore3;							// SabScore��3����
	int m_nSabScore4;							// SabScore��4����
	int m_nSabScore5;							// SabScore��5����

	int m_nTotalScoreBase;						// TotalScore�̒l������
	int m_nTotalScore1;							// TotalScore��1����
	int m_nTotalScore2;							// TotalScore��2����
	int m_nTotalScore3;							// TotalScore��3����
	int m_nTotalScore4;							// TotalScore��4����
	int m_nTotalScore5;							// TotalScore��5����
	int m_nTotalScore6;							// TotalScore��6����

	int m_nGoodScoreBase;						// GoodScore�̒l������
	int m_nGoodScore1;							// GoodScore��1����
	int m_nGoodScore2;							// GoodScore��2����

	int m_nBadScoreBase;						// BadScore�̒l������
	int m_nBadScore1;							// BadScore��1����
	int m_nBadScore2;							// BadScore��2����
	
	int m_nRankingChar;							// �����N�̒l������
	int m_nRankingChar1;

	int m_nTime;								// Result������
	bool m_bMainScoreFlg[5];					// 1�����̌v�Z�Ɏg���t���O
	bool m_bSabScoreFlg[5];						// 1�����̌v�Z�Ɏg���t���O
	bool m_bTotalScoreFlg[6];					// 1�����̌v�Z�Ɏg���t���O
	bool m_bGoodScoreFlg;						// GoodScore�������Ɏg���t���O
	bool m_bBadScoreFlg;						// BadScore�������Ɏg���t���O
	bool m_bRankingCharFlg;						// RankingChar�������Ɏg���t���O
	bool m_bBestPhotoFlg;						// BestPhoto�������Ɏg���t���O

	float r, g, b, a;
	float rr, gg, bb, aa;

};
#endif //RESULT_H