/**************************************************************************//**
 * @file		TokiSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	TOKISEQUENCE_H
#define TOKISEQUENCE_H

#include "Sequence.h"

class TokiSequence :public MeekH::Sequence{
public:
	TokiSequence();
	~TokiSequence();
	void Update()override;
};
#endif //TOKISEQUENCE_H
