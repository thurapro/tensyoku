/**************************************************************************//**
 * @file		MusicScoreLoader.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "MusicScoreLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include <sstream>

MusicScore MusicScoreLoader::ReadFile( std::string fileName ){

	MusicScore musicScore;
	musicScore.noteNum = 0;

	std::ifstream ifs( fileName );
	std::string str;
	int datai[5];
	float dataf[5];

	int lineCnt = 0;
	if( !ifs ) {
		std::cout << "Error:Input data file not found" << std::endl;
		return musicScore;
	}

	std::string token;
	std::stringstream ssInt;

	//ヘッダ読み込み
	getline( ifs , str );
	std::istringstream stream( str );

	//BPMは必ず存在する
	getline( stream , token , ',' );
	ssInt << token;
	ssInt >> musicScore.header.bpm;

	while( getline( stream , token , ',' )){
		musicScore.header.data.push_back(token);
	}
	
	//譜面データ読み込み
	while( getline( ifs , str ) ){
		int i = 1;
		std::istringstream stream( str );
		datai[0] = 0;
		dataf[0] = 0;

		while( getline( stream , token , ',' ) ) {
			std::stringstream ssInt , ssFloat;
			if( token[0] == 'r' ){
				token[0] = '0';
				datai[0] = 1;
				dataf[0] = 1;
			}
			ssInt << token;
			ssInt >> datai[i];

			ssFloat << token;
			ssFloat >> dataf[i];
			++i;
		}

		Note note;
		note.ScoreType = static_cast<ScoreType>( datai[0] );
		note.scoreLength = static_cast<ScoreLength>( datai[1] );
		note.rot = dataf[2];
		note.mainGameScoreMode = static_cast<MainGameMusicScoreMode>( datai[3] );
		note.subGameScoreMode = static_cast<SubGameMusicScoreMode>( datai[4] );
		musicScore.note.push_back(note);
		++lineCnt;
	}

	musicScore.noteNum = lineCnt;

	return musicScore;
}
