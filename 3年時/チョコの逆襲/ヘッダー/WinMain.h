//=============================================================================
// メイン処理[WinMain.h]
// 松尾 雄太
//=============================================================================

//=============================================================================
// 2重インクルード
//=============================================================================
#ifndef _WINMAIN_H_
#define _WINMAIN_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "meshwall.h"
#include "InputKey.h"
#include "FPS.h"
#include "Field.h"
#include "Player.h"
#include "WndProc.h"
#include "common.h"
#include "Light.h"
#include "Camera.h"
#include "Bullet.h"
#include "Shadow.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Effect.h"
#include "title.h"
#include "clear.h"
#include "Font.h"
#include "EnemyLife.h"
#include "Over.h"
#include "Sound.h"
#include "Explain.h"
#include "Lank.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow);

void GameSelectSet( int Select );
int GameTimerGet(void);
bool GameStop(void);

#endif // _WINMAIN_H_