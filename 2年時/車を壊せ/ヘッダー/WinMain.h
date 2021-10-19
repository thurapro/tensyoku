#ifndef _WINMAIN_H_
#define _WINMAIN_H_

int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow);

int GameSelectGet( void );

void GameSelectSet( int Select );

#endif // _WINMAIN_H_