/**************************************************************************//**
 * @file		TitleSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	TITLESEQUENCE_H
#define TITLESEQUENCE_H

#include "Sequence.h"

class wiimote;
class TitleSequence:public MeekH::Sequence{
public:
	TitleSequence();
	~TitleSequence();
	void Update()override;

private:
	void ChangeSequence();
	bool m_flag;
	bool m_nextRanking;
	wiimote *m_remote;
};
#endif //TITLESEQUENCE_H
