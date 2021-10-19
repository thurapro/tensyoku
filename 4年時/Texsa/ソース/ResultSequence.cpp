/**************************************************************************//**
 * @file		ResultSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "ResultSequence.h"
#include "Memory.h"
#include "Node.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"

#include <Windows.h>
#include "SongSelectSequence.h"
#include "Socket.h"
#include "NetworkMessage.h"
#include "SharedData.h"

// 新しく作った
#include "Score.h"
#include "Result.h"
#include "Input.h"
#include "TitleSequence.h"
#include "Application.h"
#include "FadeSequence.h"
#include "RankingSequence.h"
#include "SoundObject.h"
#include "RecvObj.h"
USING_MEEK

ResultSequence::ResultSequence(){
	using DirectX::SimpleMath::Vector2;

	// カメラ生成
	auto camera2dLayer = NEW Node();



	// スコア生成
	//Score *score = NEW Score;
	//score->Init();
	//score->SetName("score");

	// リザルト生成
	Result *result = NEW Result;
	result->Init();
	result->SetName("result");

	auto pSubScore = static_cast<int*>(SharedData::GetData(SharedData::SUBGAME_SCORE));
	int subScore = *pSubScore;

	result->SetSabScore(subScore);

	camera2dLayer->SetCamera( NEW Camera( 1280 , 720 , Camera::Type::OrthographicLH ) );
	camera2dLayer->AddChild(result);
	camera2dLayer->SetName("camera");

	AddChild( camera2dLayer );

	m_dataInit = false;
	m_mainGameScore = 0;

#if 0
	auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(SharedData::SOCKET));

	socket->SetThreadCallBack([this, result](void* sender)->DWORD{
		auto socket = static_cast<MeekL::Socket* >(sender);
		NetworkMessage msg;
		sockaddr_in fromAddr;
		sockaddr_in *subGameAddr = (sockaddr_in*)(SharedData::GetData(SharedData::ADDR));
		for (;;){
			memset(&msg, 0, sizeof(msg));
			socket->RecvFrom((char*)&msg, sizeof(msg), &fromAddr, sizeof(fromAddr));

			if (fromAddr.sin_addr.S_un.S_addr == subGameAddr->sin_addr.S_un.S_addr){

				if (msg.messageID == 1 && msg.data[0] == 0xFF){
					m_SequenceChange = true;
					break;
				}
				if ( !m_dataInit && msg.messageID == 3){
					m_mainGameScore = ((int*)msg.data)[0];
					result->SetMainScore(m_mainGameScore);

					auto mainScore = static_cast<int*>(SharedData::GetData(SharedData::MAINGAME_SCORE));

					*mainScore = m_mainGameScore;
					m_dataInit = true;
				}
				//std::cout << "MessageID:" << msg.messageID << std::endl;
				//std::cout << "Data:" << msg.data << std::endl;

			}

			//break;
		}
		return 0;
	});

	socket->CreateThread();
#else

	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	recvObj->SetCallBack([this, result](NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket){
		sockaddr_in *subGameAddr = (sockaddr_in*)(SharedData::GetData(SharedData::ADDR));
		if (from.sin_addr.S_un.S_addr == subGameAddr->sin_addr.S_un.S_addr){

			if (msg.messageID == 1 && msg.data[0] == 0xFF){
				m_SequenceChange = true;
			}
			if (!m_dataInit && msg.messageID == 3){
				m_mainGameScore = ((int*)msg.data)[0];
				result->SetMainScore(m_mainGameScore);

				auto mainScore = static_cast<int*>(SharedData::GetData(SharedData::MAINGAME_SCORE));

				*mainScore = m_mainGameScore;
				m_dataInit = true;
			}
			//std::cout << "MessageID:" << msg.messageID << std::endl;
			//std::cout << "Data:" << msg.data << std::endl;

		}
	});

#endif
	m_bgm = NEW CSoundObject("data\\sound\\Result.wav");
	m_bgm->Looping(true);
	m_bgm->Play();

#if 0
	m_subGameScore = rand()%100;
	result->SetSabScore(m_subGameScore);
	auto subScore = static_cast<int*>( SharedData::GetData( 201 ) );
	if( !subScore ){
		subScore = NEW int;
		SharedData::SetData( 201 , subScore );

	}
	*subScore = m_subGameScore;
	m_dataInit = true;

#endif

	auto goodScore = static_cast<int*>( SharedData::GetData( SharedData::GOOD_NUM ) );
	auto badScore = static_cast<int*>( SharedData::GetData( SharedData::BAD_NUM ) );
	result->SetGoodScore( *goodScore );
	result->SetBadScore( *badScore );

}
ResultSequence::~ResultSequence(){
	m_bgm->Stop();
	SAFE_DELETE(m_bgm);
}
void ResultSequence::Update(){
	if (!m_dataInit){
		//Score送る
		auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(SharedData::SOCKET));
		auto addr = static_cast<sockaddr_in * >(SharedData::GetData(SharedData::ADDR));
		NetworkMessage msg;
		int subScore = *static_cast<int*>(SharedData::GetData(SharedData::SUBGAME_SCORE));

		msg.messageID = 3;
		((int*)msg.data)[0] = subScore;
		socket->Sendto((char*)&msg, sizeof(msg), addr, sizeof(sockaddr_in));


		return;
	}

	//// スコア
	//Score *score;
	//score = (Score*)GetChild("camera")->GetChild("score");	// カメラにスコアをくっつける

	// リザルト
	Result *result;
	result = (Result*)GetChild("camera")->GetChild("result");	// リザルトにスコアをくっつける

	// 更新
	//score->Update();	// スコア

	result->Update();	// リザルト
	if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN) || m_SequenceChange){
		m_bgm->Stop();
		MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW RankingSequence));

		auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
		auto addr = static_cast<sockaddr_in * >(SharedData::GetData(101));
		NetworkMessage msg;
		msg.messageID = 1;	//画面遷移
		msg.data[0] = 0xFF;	//次の
		socket->Sendto((char*)&msg, sizeof(msg), addr, sizeof(sockaddr_in));

	}
}