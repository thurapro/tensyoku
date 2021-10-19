/**************************************************************************//**
 * @file		TitleSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "GameSequence.h"
#include "Memory.h"
#include "Node.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"

#include <Windows.h>
#include "SongSelectSequence.h"
#include "MarkerButton.h"
#include "CollisionBar.h"
#include "MarkerManager.h"
#include "WiiController.h"

#include "SoundObject.h"
#include "SoundSystem.h"

#include "Socket.h"
#include "SharedData.h"
#include "NetworkMessage.h"
#include <iostream>
#include "Input.h"
#include "FadeSequence.h"
#include "ResultSequence.h"
#include "hiraiSequence.h"
#include "Score.h"
#include "Window.h"
#include "RecvObj.h"
#include <mmsystem.h>
USING_MEEK

//wiimote *GameSequence::m_remote;

CComObject<VideoSprite> *g_video;
bool m_videoFirstTime = true;
GameSequence::GameSequence() :m_pSoundObj(nullptr), m_sequenceChange(nullptr){
	using DirectX::SimpleMath::Vector2;

	m_videoTime = 0;
	m_videoPause = false;
	auto camera2dLayer = NEW Node();
	
	auto camera = NEW Camera(1280, 720, Camera::Type::OrthographicLH);
	camera->SetPos(0, 0, -50);
	camera2dLayer->SetCamera( camera );
	camera2dLayer->SetName("Camera");
	AddChild( camera2dLayer );

	auto pMarkerManager = NEW MarkerManager;
	camera2dLayer->AddChild(pMarkerManager);
	pMarkerManager->SetPriority(5);

	pMarkerManager->Init("data\\musicscore\\test.csv");
	pMarkerManager->SetName("MarkerManager");

	auto BackGround = NEW Sprite(1280, 720, L"data\\texture\\back2.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	//camera2dLayer->AddChild(BackGround);
	BackGround->SetName("BG0");
	BackGround->SetPos(DirectX::SimpleMath::Vector3( 0 ,0 , 20 ) );
	//m_pSoundObj->Play();
	
	//ネットワーク関係
#if 0
	auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
	socket->SetThreadCallBack([this](void* sender)->DWORD{
		auto socket = static_cast<MeekL::Socket* >(sender);
		NetworkMessage msg;
		sockaddr_in fromAddr;
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		for (;;){
			memset(&msg, 0, sizeof(msg));
			socket->RecvFrom((char*)&msg, sizeof(msg), &fromAddr, sizeof(fromAddr));

			if (fromAddr.sin_port == mainGameAddr->sin_port){

				if( msg.messageID == 1 && msg.data[0] == 0xFF ){
					m_sequenceChange = true;
					break;
				}

				std::cout << "MessageID:" << msg.messageID << std::endl;
				std::cout << "Data:" << msg.data << std::endl;

			}
		}
		return 0;
	});

	socket->CreateThread();
#else

	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	recvObj->SetCallBack([this](NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket){
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		if (from.sin_port == mainGameAddr->sin_port){

			if (msg.messageID == 1 && msg.data[0] == 0xFF){
				m_sequenceChange = true;
			}
		}
	});

#endif
	if( m_videoFirstTime ){
		CComObject<VideoSprite>::CreateInstance( &g_video );
		HWND hwnd = MeekH::Application::GetInstance()->GetWindow()->GetHwnd();
		g_video->Init( hwnd , L"Space_3.mp4" );
		g_video->Start();
		m_videoFirstTime = false;

	}
	else{
		g_video->ReStart();

	}

	m_videoTime = timeGetTime();

	auto good = static_cast< int* >( SharedData::GetData( SharedData::GOOD_NUM ) );
	auto bad = static_cast< int* >( SharedData::GetData( SharedData::BAD_NUM ) );


	*good = 0;
	*bad = 0;
}

GameSequence::~GameSequence(){
	//auto socket = static_cast<MeekL::Socket* >( SharedData::GetData( 100 ) );
	//socket->CloseThread();
	//socket->SetThreadCallBack( nullptr );
	//g_video->Pause();
	SAFE_DELETE(m_pSoundObj);
}


void GameSequence::Update(){


	auto diff = timeGetTime() - m_videoTime;
	if( 155000 <  diff ){
		if (!m_videoPause)g_video->Pause();
		m_videoPause = true;
	}

	CollisionBar *ColBar = (CollisionBar *)GetChild("Camera")->GetChild("col");
	MarkerManager *Manager = (MarkerManager *)GetChild("Camera")->GetChild("MarkerManager");

	for (int i = 0; i < CWiiController::GetMaxNum(); i++)
	{
		CWiiController::GetInstance(i)->Update();
	}
	Manager->Update();

	if( 0 < Manager->GetComboNum() &&  (Manager->GetComboNum() % 10 ) == 0 ){
		auto socket = static_cast<MeekL::Socket* >( SharedData::GetData( 100 ) );
		sockaddr_in *mainGameAddr = ( sockaddr_in* )( SharedData::GetData( 101 ) );
		NetworkMessage msg;
		msg.messageID = 4;
		msg.data[0] = 0;
		socket->Sendto( (char*)&msg , sizeof(msg) , mainGameAddr , sizeof(sockaddr_in));
	}

	if (m_sequenceChange || CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN)){

		if ( !m_videoPause ){
			g_video->Pause();
			m_videoPause = true;

		}
		auto subGameScoreData = static_cast<Score*>(Manager->FindNode( "score" ))->GetScore();

		auto sharedScore = static_cast<int*>(SharedData::GetData(SharedData::SUBGAME_SCORE));
		if( !sharedScore ){
			sharedScore = NEW int;
			SharedData::SetData( SharedData::SUBGAME_SCORE , sharedScore );
		}
		*sharedScore = subGameScoreData;
		sharedScore = static_cast<int*>( SharedData::GetData( SharedData::SUBGAME_SCORE ) );
		MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW HiraiSequence() ));
	}
}

void GameSequence::Draw(){
	g_video->Render();
}