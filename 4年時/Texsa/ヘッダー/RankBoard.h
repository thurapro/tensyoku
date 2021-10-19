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
	* �����N�{�[�h������
	* �����N, �����N�C�������̂�
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
	 * ���ʂƂ���ɍ��킹���摜��ݒ�
	*/
	void SetRank(int Rank);

	bool GetBoolPos();
	void SetBoolPos(bool bMovePos);
	 
	bool GetRankSpeedChange();
	void SetRankSpeedChange(bool bChange);



private:
	MeekH::Sprite *m_RankBackSprite;		// �w�i
	MeekH::Sprite *m_RankSprite;			// ����
	MeekH::Sprite *m_PhotoSprite;			// �ʐ^
	MeekH::Sprite **m_pScore;				// �X�R�A
	DirectX::SimpleMath::Vector3 m_pos;		// �ʒu
	DirectX::SimpleMath::Vector3 m_rot;		// ��]
	DirectX::SimpleMath::Vector2 m_size;	// �T�C�Y
	int m_Rank;								// ����
	wchar_t m_RankTexPath[128];				// ���ʉ摜�̃p�X
	bool	m_Rankin;						// �����N�C�������̂�
	int		m_RankInNum;					// �����N�C����������
	static int m_RankMax;					//
	bool	m_bAlive;						// �����Ă��邩
	bool	m_bSetPos;						// ����̈ʒu�ɂ�����
	int		m_StopCount;					// �����L���O�X�g�b�v
	bool	m_visible;						// �_��
	int		m_visibleTime;					// �_�Ŏ���
	bool	m_RankSpeedChange;				// �����ɓ���ւ�
};

#endif //RANKBOARD_H