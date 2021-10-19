#ifndef FADE_SEQUENCE
#define FADE_SEQUENCE

#include "TransitionSequence.h"

class FadeSequence:public MeekH::TransitionSequence{
public:
	FadeSequence( Sequence *next );
	void Init( Sequence *next )override;
	~FadeSequence();
	void Visit()override;
	void Update()override;
};
#endif