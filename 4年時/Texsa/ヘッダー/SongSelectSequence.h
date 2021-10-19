/**************************************************************************//**
 * @file		SongSelectSequence.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	SONGSELECTSEQUENCE_H
#define SONGSELECTSEQUENCE_H

#include "Sequence.h"
#include <string>

class CSoundObject;
class SongSelectSequence:public MeekH::Sequence{
public:

	enum class Mode{
		MODE_SONGSELECT,
		MODE_LEVELSELECT,
		MODE_START

	};
	SongSelectSequence();
	~SongSelectSequence();
	void Update()override;
private:
	Mode m_mode;
	int m_selectLevelIndex;
	std::string m_levelName[3];
	int m_startFrame;
	int m_cnt;	// 何フレームか待つカウント
	int m_cnt1;	// 
	int m_startcnt;	// 
	bool m_bTest1, m_bTest2, m_bTest3;

	CSoundObject *m_soundObject[3];
	int m_bgmIndex;
	bool m_scaleAnimation;
	int m_scaleAnimationFrame;
	bool m_startWait;
	int m_startWaitFrame;


};
#endif //SONGSELECTSEQUENCE_H
