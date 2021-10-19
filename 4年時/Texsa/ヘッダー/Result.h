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
	DirectX::SimpleMath::Vector3 *m_pos;		// 表示位置の中心座標
	DirectX::SimpleMath::Vector3 *m_rot;		// 回転角
	DirectX::SimpleMath::Vector3 *m_scl;		// サイズ
	int m_nMainScoreBase;						// MainScoreの値が入る
	int m_nMainScore1;							// MainScoreの1桁目
	int m_nMainScore2;							// MainScoreの2桁目
	int m_nMainScore3;							// MainScoreの3桁目
	int m_nMainScore4;							// MainScoreの4桁目
	int m_nMainScore5;							// MainScoreの5桁目

	int m_nSabScoreBase;						// SabScoreの値が入る
	int m_nSabScore1;							// SabScoreの1桁目
	int m_nSabScore2;							// SabScoreの2桁目
	int m_nSabScore3;							// SabScoreの3桁目
	int m_nSabScore4;							// SabScoreの4桁目
	int m_nSabScore5;							// SabScoreの5桁目

	int m_nTotalScoreBase;						// TotalScoreの値が入る
	int m_nTotalScore1;							// TotalScoreの1桁目
	int m_nTotalScore2;							// TotalScoreの2桁目
	int m_nTotalScore3;							// TotalScoreの3桁目
	int m_nTotalScore4;							// TotalScoreの4桁目
	int m_nTotalScore5;							// TotalScoreの5桁目
	int m_nTotalScore6;							// TotalScoreの6桁目

	int m_nGoodScoreBase;						// GoodScoreの値が入る
	int m_nGoodScore1;							// GoodScoreの1桁目
	int m_nGoodScore2;							// GoodScoreの2桁目

	int m_nBadScoreBase;						// BadScoreの値が入る
	int m_nBadScore1;							// BadScoreの1桁目
	int m_nBadScore2;							// BadScoreの2桁目
	
	int m_nRankingChar;							// ランクの値が入る
	int m_nRankingChar1;

	int m_nTime;								// Result内時間
	bool m_bMainScoreFlg[5];					// 1桁ずつの計算に使うフラグ
	bool m_bSabScoreFlg[5];						// 1桁ずつの計算に使うフラグ
	bool m_bTotalScoreFlg[6];					// 1桁ずつの計算に使うフラグ
	bool m_bGoodScoreFlg;						// GoodScore処理時に使うフラグ
	bool m_bBadScoreFlg;						// BadScore処理時に使うフラグ
	bool m_bRankingCharFlg;						// RankingChar処理時に使うフラグ
	bool m_bBestPhotoFlg;						// BestPhoto処理時に使うフラグ

	float r, g, b, a;
	float rr, gg, bb, aa;

};
#endif //RESULT_H