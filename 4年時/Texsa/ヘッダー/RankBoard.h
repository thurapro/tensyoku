/****************************************************************************
* @file			RankBoard.h
* @brief
* @author 		Yuta Matsuo
*****************************************************************************/
#ifndef	RANKBOARD_H
#define RANKBOARD_H

#include "Node.h"
#include "../../DirectXTK/Inc/SimpleMath.h"

namespace MeekH
{
	class Sprite;
}

class Score;


class RankBoard : public MeekH::Node{
public:
	RankBoard();
	~RankBoard();
	/*
	* ランクボード初期化
	* ランク, ランクインしたのか
	*/
	void Init( int Rank , int Score , bool bRankin , wchar_t *bestShot );
	void Update();

	DirectX::SimpleMath::Vector3 GetBoardPos();
	void SetBoardPos(DirectX::SimpleMath::Vector3 pos);
	
	DirectX::SimpleMath::Vector3 GetBoardSize();
	void SetBoardSize(DirectX::SimpleMath::Vector2 size);

	static void SetRankMax(int i);
	static int GetRankMax();

	bool GetAlive();

	/*
	 * 順位とそれに合わせた画像を設定
	*/
	void SetRank(int Rank);

	bool GetBoolPos();
	void SetBoolPos(bool bMovePos);
	 
	bool GetRankSpeedChange();
	void SetRankSpeedChange(bool bChange);



private:
	MeekH::Sprite *m_RankBackSprite;		// 背景
	MeekH::Sprite *m_RankSprite;			// 順位
	MeekH::Sprite *m_PhotoSprite;			// 写真
	MeekH::Sprite **m_pScore;				// スコア
	DirectX::SimpleMath::Vector3 m_pos;		// 位置
	DirectX::SimpleMath::Vector3 m_rot;		// 回転
	DirectX::SimpleMath::Vector2 m_size;	// サイズ
	int m_Rank;								// 順位
	wchar_t m_RankTexPath[128];				// 順位画像のパス
	bool	m_Rankin;						// ランクインしたのか
	int		m_RankInNum;					// ランクインした順位
	static int m_RankMax;					//
	bool	m_bAlive;						// 生きているか
	bool	m_bSetPos;						// 所定の位置についたか
	int		m_StopCount;					// ランキングストップ
	bool	m_visible;						// 点滅
	int		m_visibleTime;					// 点滅時間
	bool	m_RankSpeedChange;				// すぐに入れ替え
};

#endif //RANKBOARD_H