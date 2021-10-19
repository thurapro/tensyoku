/**************************************************************************//**
 * @file		GameSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	GAMESEQUENCE_H
#define GAMESEQUENCE_H

#include "Sequence.h"
#include "VideoSprite.h"

class wiimote;
class MarkerManager;
class CSoundObject;

class GameSequence :public MeekH::Sequence{
public:
	GameSequence();
	~GameSequence();
	void Update()override;
	void Draw()override;

	//CSoundObject **GetSound(){ return &m_pSoundObj; }

private:
	wiimote *m_remote;
	CSoundObject *m_pSoundObj;
	bool m_sequenceChange;
	unsigned long m_videoTime;
	bool m_videoPause;
};
#endif //GAMESEQUENCE_H
