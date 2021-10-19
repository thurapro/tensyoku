//ライブラリ読み込み
#ifdef _DEBUG
#pragma comment(lib , "meekL_d.lib" )
#pragma comment(lib , "MeekH_d.lib" )
#else
#pragma comment(lib , "meekL.lib" )
#pragma comment(lib , "meekH.lib" )
#endif

#pragma comment(lib ,"winmm.lib")

#include <Windows.h>

#include "Application.h"
#include "TitleSequence.h"

#include "../Meek/H/include/Version.h"
#include "../Meek/L/include/Version.h"

#include "hiraiSequence.h"
#include "GameSequence.h"
#include "WiiController.h"
#include "SharedData.h"

#include "SoundSystem.h"
#include "SoundObject.h"
#include "SharedData.h"
#include "SongSelectSequence.h"
#include "Result.h"

#include "Network.h"
#include "Socket.h"
#include "../../src/NetworkMessage.h"
#include <iostream>
#include "Memory.h"
#include <atomic>
#include "Window.h"
#include "RecvObj.h"

RecvObject g_recvObj;

//このマクロが定義されていると、メインゲームとの通信が確立しないと起動しません
#define NetworkControl		

static MeekL::Socket *g_socket;
static sockaddr_in g_mainGameAddr;
static std::atomic<bool> g_initNetwork = false;
void InitNetwork(){
	MeekL::Network::Init();

	g_socket = NEW MeekL::Socket(INADDR_ANY, SUBGAME_PORT); //サブゲームで受信設定
	g_socket->Bind();

#if 0

	g_socket->SetThreadCallBack([](void* sender)->DWORD{
		auto socket = (MeekL::Socket*)sender;
		NetworkMessage recvMsg;
		sockaddr_in fromAddr;
		for (;;){
			memset(&recvMsg, 0, sizeof(recvMsg));
			socket->RecvFrom((char*)&recvMsg, sizeof(recvMsg), &fromAddr, sizeof(fromAddr));
			if (recvMsg.messageID == 0xFF){
				//MessageBox(nullptr,L"",L"",MB_OK);
				std::cout << "メインゲームの検索要求到着(ﾟдﾟ)！" << std::endl;
				NetworkMessage sendMsg;
				sendMsg.messageID = -0xFF;
				g_mainGameAddr = fromAddr;
				g_mainGameAddr.sin_port = htons(MAINGAME_PORT);	//メインゲームに送信
				socket->Sendto( ( char* )&sendMsg , sizeof( sendMsg ) , &fromAddr , sizeof( fromAddr ) );
				socket->Sendto( ( char* )&sendMsg , sizeof( sendMsg ) , &fromAddr , sizeof( fromAddr ) );
				socket->Sendto( ( char* )&sendMsg , sizeof( sendMsg ) , &fromAddr , sizeof( fromAddr ) );
				g_initNetwork = true;
				break;
			}
		}

		return 0;
	});
	g_socket->CreateThread();
#endif

	g_recvObj.CreateRecv(g_socket);
	g_recvObj.SetCallBack([]( NetworkMessage &msg , sockaddr_in &from , MeekL::Socket *socket ){
		if (msg.messageID == 0xFF){
			//MessageBox(nullptr,L"",L"",MB_OK);
			std::cout << "メインゲームの検索要求到着(ﾟдﾟ)！" << std::endl;
			NetworkMessage sendMsg;
			sendMsg.messageID = -0xFF;
			g_mainGameAddr = from;
			g_mainGameAddr.sin_port = htons(MAINGAME_PORT);	//メインゲームに送信
			socket->Sendto((char*)&sendMsg, sizeof(sendMsg), &from, sizeof(from));
			socket->Sendto((char*)&sendMsg, sizeof(sendMsg), &from, sizeof(from));
			socket->Sendto((char*)&sendMsg, sizeof(sendMsg), &from, sizeof(from));
			g_initNetwork = true;
		}

	});
	SharedData::SetData(100, g_socket);
	SharedData::SetData(101, &g_mainGameAddr);

}

void UninitNetwork(){
	g_recvObj.Destroy();
	g_socket->Close();
	//g_socket->CloseThread();
	SAFE_DELETE(g_socket);
}

/**
* エントリーポイント
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);	// 未使用宣言
	UNREFERENCED_PARAMETER(lpCmdline);		// 未使用宣言
	UNREFERENCED_PARAMETER(nCmdShow);		// 未使用宣言

	std::string meekHVersion = MeekH::GetVersion();
	std::string meekLVersion = MeekL::GetVersion();
	
	OutputDebugStringA("meekHVersion:");
	OutputDebugStringA(meekHVersion.c_str());
	OutputDebugStringA("\n");

	OutputDebugStringA("meekLVersion:");
	OutputDebugStringA(meekLVersion.c_str());
	OutputDebugStringA("\n");

	SharedData::SetData( 500 , &g_recvObj );

	CWiiController::Create(0);
	CWiiController::Create(1);
	CWiiController::Create(2);
	CWiiController::Create(3);
	CWiiController::Create(4);

	int r[20];
	int max = 19;

	for (int i = 0; i < 20; i++)
	{
		r[i] = i;
		SharedData::SetData(max, (void *)&r[i]);
		max--;
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	CWiiController::Create(i);
	//}

	InitNetwork();
#ifdef NetworkControl
	while (!g_initNetwork);
#endif
	//g_socket->CloseThread();
	g_socket->SetThreadCallBack(nullptr);

	SharedData::InitData();

	auto app = new MeekH::Application(hInstance);
	app->GetWindow()->SetWindowTextW(L"Texas");
	g_recvObj.SetCallBack(nullptr);
	app->Run(new TitleSequence);
	delete app;

	//for (int i = 0; i < CWiiController::GetMaxNum(); i++)
	//{
	//	CWiiController::Uninit(i);
	//}

	MeekL::Network::UnInit();

	return 0;
}
