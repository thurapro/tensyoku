/**************************************************************************//**
 * @file		TitleSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "TitleSequence.h"
#include "Memory.h"
#include "Node.h"
#include "TransformComponent.h"
#include "ShaderComponent.h"
#include "SpriteComponent.h"
#include "DrawableComponent.h"
#include "ShaderGroup.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"

#include <Windows.h>
#include "GameSequence.h"
#include "../../DirectXTK/Inc/SimpleMath.h"
#include "Input.h"
#include "FadeSequence.h"
#include "WiiController.h"
#include "Socket.h"
#include "SharedData.h"
#include "NetworkMessage.h"
#include <iostream>
#include "SongSelectSequence.h"
#include "RankingSequence.h"
#include <Shlwapi.h>
#include <fstream>
#include "RecvObj.h"

using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;
//#define NEW_SEQUENCECHANGE

TitleSequence::TitleSequence() :m_flag(false){

	auto camera2dLayer = NEW MeekH::Node();
	auto titleImage = NEW MeekH::Sprite( 1280 , 720 , L"data\\texture\\title.jpg" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );

	titleImage->SetPos( Vector3( 0 , 0 , 0 ) );

	auto camera2D = NEW MeekL::Camera(1280, 720, MeekL::Camera::Type::OrthographicLH);
	camera2dLayer->SetCamera(camera2D);
	camera2dLayer->AddChild( titleImage );
	AddChild( camera2dLayer );

	auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
#ifndef NEW_SEQUENCECHANGE
#if 0
	socket->SetThreadCallBack([this]( void* sender )->DWORD{
		auto socket = static_cast<MeekL::Socket* >(sender);
		NetworkMessage msg;
		sockaddr_in fromAddr;
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		for (;;){
			memset(&msg, 0, sizeof(msg));
			socket->RecvFrom((char*)&msg, sizeof(msg), &fromAddr, sizeof(fromAddr));

			if (fromAddr.sin_port == mainGameAddr->sin_port){

				if (msg.messageID == 1 && msg.data[0] == 0xFF /*&& msg.data[1] != 4*/){
					m_flag = true;
					break;
				}
				if (msg.messageID == 1 && msg.data[0] == 4){
 					m_nextRanking = true;
					break;
				}

				std::cout << "MessageID:" << msg.messageID << std::endl;
				std::cout << "Data:" << msg.data << std::endl;

			}
		}
		return 0;
	});

	socket->CreateThread();
#endif
	
	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	recvObj->SetCallBack([this](NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket){
		if (msg.messageID == 1 && msg.data[0] == 0xFF /*&& msg.data[1] != 4*/){
			m_flag = true;
		}
		if (msg.messageID == 1 && msg.data[0] == 4){
			m_nextRanking = true;
		}
	});

#endif
	m_nextRanking = false;
}
TitleSequence::~TitleSequence(){
	//auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
	//socket->DestroyThread();

	//socket->CloseThread();
	//socket->SetThreadCallBack(nullptr);

	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	//recvObj->SetCallBack(nullptr);
}
void TitleSequence::Update(){
	CWiiController::GetInstance(0)->Update();

#ifdef NEW_SEQUENCECHANGE
	if (PathFileExists(L"z:\\Network\\SequenceChange")){
		std::ifstream ifs("z:\\Network\\SequenceChange");
		std::string str;
		ifs >> str;
		if ( str == "4"){
			m_nextRanking = true;
		}
		else{
			m_flag = true;
		}
		DeleteFile(L"z:\\Network\\SequenceChange");
	}

#endif

	auto updateAge = CWiiController::GetInstance(0)->GetAccel().Orientation.UpdateAge;

	if (m_flag || CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN)){
		ChangeSequence();
	}

	if (m_nextRanking){
		MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW RankingSequence()));

	}

}

void TitleSequence::ChangeSequence(){
	MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW GameSequence()));

}
