/**************************************************************************//**
 * @file		hiraiSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "hiraiSequence.h"
#include "Memory.h"
#include "Node.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"
#include "Input.h"
#include "Application.h"
#include "RankingSequence.h"
#include "FadeSequence.h"
#include "Socket.h"
#include "NetworkMessage.h"
#include "SharedData.h"

#include <Windows.h>
#include "SongSelectSequence.h"
#include "RecvObj.h"

// 新しく作った
#include "Score.h"
#include "Result.h"

USING_MEEK

HiraiSequence::HiraiSequence(){
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

	int subScore = *static_cast< int * >( SharedData::GetData( SharedData::SUBGAME_SCORE ) );
	result->SetSabScore( subScore );


	camera2dLayer->SetCamera( NEW Camera( 1280 , 720 , Camera::Type::OrthographicLH ) );
	camera2dLayer->AddChild(result);
	camera2dLayer->SetName("camera");

	AddChild( camera2dLayer );
	
#if 0
	//ネットワーク関係
	auto socket = static_cast<MeekL::Socket* >( SharedData::GetData( 100 ) );
	socket->SetThreadCallBack( [ this , result , subScore ]( void* sender )->DWORD{
		auto socket = static_cast<MeekL::Socket* >( sender );
		NetworkMessage msg;
		sockaddr_in fromAddr;
		sockaddr_in *mainGameAddr = ( sockaddr_in* )( SharedData::GetData( 101 ) );
		for( ;; ){
			memset( &msg , 0 , sizeof( msg ) );
			socket->RecvFrom( ( char* )&msg , sizeof( msg ) , &fromAddr , sizeof( fromAddr ) );

			if( fromAddr.sin_port == mainGameAddr->sin_port ){

				if( msg.messageID == 1 && msg.data[0] == 0xFF ){
					m_sequenceChange = true;
					break;
				}

				if ( msg.messageID == 3){
					m_mainGameScore = ( ( int* )msg.data )[0];
					if (!m_dataInit){
						result->SetMainScore(m_mainGameScore);
					}
					NetworkMessage sendMsg;
					sendMsg.messageID = 3;
					( ( int* )sendMsg.data )[0] = subScore;

					auto mainScoreShared = static_cast< int * >( SharedData::GetData( SharedData::MAINGAME_SCORE ) );
					*mainScoreShared = m_mainGameScore;

					socket->Sendto( ( char* )&sendMsg , sizeof( sendMsg ) , &fromAddr , sizeof( fromAddr ) );
					m_dataInit = true;

				}

			}
		}
		return 0;
	} );

	socket->CreateThread();
#else

	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	recvObj->SetCallBack([this, result, subScore](NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket){
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		if (from.sin_port == mainGameAddr->sin_port){

			if (msg.messageID == 1 && msg.data[0] == 0xFF){
				m_sequenceChange = true;
			}

			if (msg.messageID == 3){
				m_mainGameScore = ((int*)msg.data)[0];
				if (!m_dataInit){
					result->SetMainScore(m_mainGameScore);
				}
				NetworkMessage sendMsg;
				sendMsg.messageID = 3;
				((int*)sendMsg.data)[0] = subScore;

				auto mainScoreShared = static_cast< int * >(SharedData::GetData(SharedData::MAINGAME_SCORE));
				*mainScoreShared = m_mainGameScore;

				socket->Sendto((char*)&sendMsg, sizeof(sendMsg), &from, sizeof(from));
				m_dataInit = true;

			}

		}
	});

#endif
	//m_dataInit = true;
	
	auto goodScore = static_cast< int* >( SharedData::GetData( SharedData::GOOD_NUM ) );
	result->SetGoodScore( *goodScore );

	auto badScore = static_cast< int* >( SharedData::GetData( SharedData::BAD_NUM ) );
	result->SetBadScore( *badScore );


}
HiraiSequence::~HiraiSequence(){
	auto socket = static_cast<MeekL::Socket* >( SharedData::GetData( 100 ) );
	//socket->CloseThread();
	//socket->SetThreadCallBack(nullptr);

}
void HiraiSequence::Update(){

	if( !m_dataInit ){
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

	if( CInput::GetInstance()->GetKeyboard()->IsKeyTrigger( DIK_RETURN ) || m_sequenceChange ){
		Application::GetInstance()->ChangeSequence( NEW FadeSequence( NEW RankingSequence()) );
	}
}