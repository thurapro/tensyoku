/**************************************************************************//**
 * @file		ResultSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	RESULTSEQUENCE_H
#define RESULTSEQUENCE_H

#include "Sequence.h"
#include <atomic>

class CSoundObject;
class ResultSequence :public MeekH::Sequence{
public:
	ResultSequence();
	~ResultSequence();
	void Update()override;

private:
	std::atomic<bool> m_SequenceChange;
	std::atomic<bool> m_dataInit;
	int m_mainGameScore;
	CSoundObject *m_bgm;

};
#endif //RESULTSEQUENCE_H
