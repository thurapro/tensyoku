/**************************************************************************//**
 * @file		SharedData.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/

#include "SharedData.h"
#include "Memory.h"
std::map<int, void*> SharedData::m_data;

void SharedData::InitData(){
	int *maingameScore = NEW int;
	int *subgamescore = NEW int;
	int *goodNum = NEW int;
	int *badNum = NEW int;
	int *mainGameCombo = NEW int;

	*maingameScore = -1;
	*subgamescore = -1;
	*goodNum = 0;
	*badNum = 0;
	*mainGameCombo = 0;

	SetData( 200 , maingameScore );
	SetData( 201 , subgamescore );
	SetData( 202 , goodNum );
	SetData( 203 , badNum );
	SetData( 300 , mainGameCombo );


}
void SharedData::UninitData(){
	int *maingameScore	= static_cast<int*>(GetData( 200 ));
	int *subgamescore	= static_cast<int*>(GetData( 201 ));
	int *goodNum		= static_cast<int*>(GetData( 202 ));
	int *badNum			= static_cast<int*>( GetData( 203 ) );
	int *mainGameCombo	= static_cast<int*>( GetData( 300 ) );

	SAFE_DELETE( maingameScore );
	SAFE_DELETE( subgamescore );
	SAFE_DELETE( goodNum );
	SAFE_DELETE( badNum );
	SAFE_DELETE( mainGameCombo );

}

void SharedData::SetData(int id, void* data){
	m_data[id] = data;
}
void* SharedData::GetData(int id){
	return m_data[id];
}