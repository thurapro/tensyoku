/**************************************************************************//**
 * @file		MusicScoreLoader.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef	MUSICSCORELOADER_H
#define MUSICSCORELOADER_H

#include <string>
#include <vector>

struct MusicScoreHeader{
	int bpm;
	std::vector<std::string> data;
};

enum class ScoreType{
	NOTE = 0,	//‰¹•„
	REST = 1		//‹x•„


};

enum class ScoreLength{
	WHOLE		= 0 ,	//‘S
	HALF		= 2 ,	//2•ª		
	QUARTER		= 4 ,	//4•ª
	EIGHTH		= 8 ,	//8•ª
	SIXTEENTH	= 16 ,	//16•ª

};

enum class MainGameMusicScoreMode{
	ARCH ,
	CLOCKWISE ,
	ANTICLOCKWISE ,
	ACCELERATION ,
};
enum class SubGameMusicScoreMode{
	A_BUTTON ,
	B_BUTTON ,
	ACCELERATION ,
};


struct Note{
	ScoreType ScoreType;
	ScoreLength scoreLength;
	float rot;
	MainGameMusicScoreMode mainGameScoreMode;
	SubGameMusicScoreMode subGameScoreMode;
};


struct MusicScore{

	MusicScoreHeader header;
	std::vector<Note> note;
	int noteNum;

};

class MusicScoreLoader{
public:

	MusicScoreLoader(){}
	~MusicScoreLoader(){}
	MusicScore ReadFile( std::string fileName );

protected:
private:


};
#endif //MUSICSCORELOADER_H
