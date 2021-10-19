/**************************************************************************//**
 * @file		RankingSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	RANKINGSEQUENCE_H
#define RANKINGSEQUENCE_H

#include "Sequence.h"
#include "Application.h"
#include <atomic>

class Score;

class CSoundObject;
class RankingSequence:public MeekH::Sequence{
public:
	RankingSequence();
	~RankingSequence();
	void Update()override;

private:
	int m_RankNum;
	int m_RankMax;
	bool *m_bChackPos;					// ����̈ʒu�ɂ��Ă���̂�
	int	*m_Score[20];
	wchar_t *m_bestShot[20];
	wchar_t m_bestShotBase[64];
	CSoundObject *m_bgm;
	int		m_VisibleRankNum;			// �����L���O����������
	int		m_RankInNum;
	bool *m_bRankIn;
	void ChangeSequence();
	bool m_SequenceChange;

};

#endif //RANKINGSEQUENCE_H
