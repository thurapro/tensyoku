/**************************************************************************//**
 * @file		TitleSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	HIRAISEQUENCE_H
#define HIRAISEQUENCE_H

#include "Sequence.h"
#include <atomic>
class HiraiSequence:public MeekH::Sequence{
public:
	HiraiSequence();
	~HiraiSequence();
	void Update()override;

private:

	std::atomic<bool> m_sequenceChange;
	std::atomic<bool> m_dataInit;
	int m_mainGameScore;
};
#endif //HIRAISEQUENCE_H
