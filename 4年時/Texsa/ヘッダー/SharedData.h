/**************************************************************************//**
 * @file		SharedData.h
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include <map>

class SharedData{
public:

	enum{
		SOCKET			= 100,
		ADDR			= 101,
		MAINGAME_SCORE	= 200,
		SUBGAME_SCORE	= 201,
		GOOD_NUM		= 202,
		BAD_NUM			= 203,
		COMBO			= 300,
	};

	static void InitData();
	static void UninitData();
	static void SetData(int id, void* data);
	static void* GetData(int id );

protected:
private:

	static std::map<int, void*> m_data;

};
#endif //SHAREDDATA_H