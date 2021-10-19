/**************************************************************************//**
 * @file		RankigSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "RankingSequence.h"
#include "Memory.h"
#include "Node.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"

#include <Windows.h>
#include "TitleSequence.h"
#include "SharedData.h"
#include "RankBoard.h"
#include "Input.h"
#include "FadeSequence.h"
#include "TitleSequence.h"
#include "Socket.h"
#include "NetworkMessage.h"
#include "SoundObject.h"
#include "WiiController.h"
#include "../DirectXTK/Inc/SimpleMath.h"
#include "RankingData.h"
#include "ResultSequence.h"
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include <fstream>
#include "RecvObj.h"


#define VISIBLERANK (5)
#define MAX_RANKING (20)
//#define NEW_SEQUENCECHANGE


USING_MEEK

RankingData g_rankingData[MAX_RANKING];

RankingSequence::RankingSequence() :m_SequenceChange(false){
	using DirectX::SimpleMath::Vector2;

	auto camera2dLayer = NEW Node();
	camera2dLayer->SetCamera( NEW Camera( 1280 , 720 , Camera::Type::OrthographicLH ) );
	AddChild( camera2dLayer );
	camera2dLayer->SetName( "Camera" );

	auto back = NEW Sprite( 1280 , 720 , ( L"data//texture//back2.png" ) , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	back->SetPos(0,0,900);
	back->SetPriority(0);
	camera2dLayer->AddChild( back );

	RankBoard::SetRankMax( MAX_RANKING );

	m_bRankIn = NULL;
	m_bRankIn = NEW bool[MAX_RANKING];

	ZeroMemory( &m_bRankIn[0] , MAX_RANKING );

	for( int i = 0; i < MAX_RANKING; i++ )
	{
		m_Score[i] = ( int * )SharedData::GetData( i );
	}

	GetPrivateProfileString( L"PATH" , L"base" , L"" , m_bestShotBase , 64 , L"data\\setting\\bestShot.ini" );


	std::wstring lockPath = L"Z:\\ranking\\";
	lockPath += L"success";

	while (!PathFileExists(lockPath.c_str())){
		Sleep(1);
	}

	std::ifstream ifsScore("Z:\\ranking\\score");
	std::wifstream wifsPath("Z:\\ranking\\BestShotPath");

	for (int i = 0; i < MAX_RANKING; ++i){
		std::string scoreBuff;
		ifsScore >> scoreBuff;

		g_rankingData[i].m_score = std::stoi(scoreBuff);

		std::wstring name;
		wifsPath >> name;
		swprintf_s<64>(g_rankingData[i].m_bestShotPath, L"%s%s", m_bestShotBase, name.c_str());

		m_Score[i] = &g_rankingData[i].m_score;
		m_bestShot[i] = g_rankingData[i].m_bestShotPath;

	}

	if ( PathFileExists(L"Z:\\ranking\\rankin")){
		std::ifstream ifs("Z:\\ranking\\rankin");
		std::string str;
		ifs >> str;

		int rank;
		rank = std::stoi(str);
		m_bRankIn[rank] = true;
		DeleteFile(L"Z:\\ranking\\rankin");


	}

	DeleteFile(lockPath.c_str());


	
	//int *nCurRankData = (int *)SharedData::GetData(21);

	//for (int i = 0; i < MAX_RANKING; i++)
	//{
	//	// 大小確認
	//	if (nCurRankData > m_Score[i])
	//	{
	//		// 小さい場合はスコアをずらす
	//		for (int n = (MAX_RANKING - 1); n > i; n--)
	//		{
	//			m_Score[n] = m_Score[n - 1];
	//		}
	//		m_Score[i] = nCurRankData;
	//		break;
	//	}
	//}


	for (int i = MAX_RANKING - 1; i >= 0; i--)
	{
		if (m_Score[i] == m_Score[0])
		{
			//m_bRankIn[i] = true;
		}
		else
		{
			//m_bRankIn[i] = false;
		}
	}


	m_RankMax = RankBoard::GetRankMax();

	m_bChackPos = NEW bool[VISIBLERANK];

	m_RankNum = m_RankMax;

	m_VisibleRankNum = VISIBLERANK;

	int RankNum = 16;

	for (int i = 0; i < m_VisibleRankNum; i++)
	{
		if (i < m_RankMax)
		{
			char RankName[20];
			sprintf_s<20>(RankName, "RankBoard%d", m_RankNum);
			auto Rank = NEW RankBoard;
			camera2dLayer->AddChild(Rank);
			Rank->Init( m_RankNum , *m_Score[m_RankNum - 1] , m_bRankIn[m_RankNum - 1] , m_bestShot[m_RankNum-1] );
			Rank->SetName(RankName);
			m_RankNum--;
		}
		m_bChackPos[i] = false;
	}

	m_bgm = NEW CSoundObject("data\\sound\\ranking.wav");
	m_bgm->Looping(true);
	m_bgm->Play();


	auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
#ifndef NEW_SEQUENCECHANGE 
#if 0
	socket->SetThreadCallBack([this](void* sender)->DWORD{
		auto socket = static_cast<MeekL::Socket* >(sender);
		NetworkMessage msg;
		sockaddr_in fromAddr;
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		for (;;){
			memset(&msg, 0, sizeof(msg));
			socket->RecvFrom((char*)&msg, sizeof(msg), &fromAddr, sizeof(fromAddr));

			if (fromAddr.sin_port == mainGameAddr->sin_port){

				if (msg.messageID == 1 && msg.data[0] == 0xFF){
					m_SequenceChange = true;
					break;
				}
			}
		}
		return 0;
	});

	socket->CreateThread();
#endif
	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	recvObj->SetCallBack([this](NetworkMessage &msg, sockaddr_in &from, MeekL::Socket *socket){
		sockaddr_in *mainGameAddr = (sockaddr_in*)(SharedData::GetData(101));
		if (from.sin_port == mainGameAddr->sin_port){
			if (msg.messageID == 1 && msg.data[0] == 0xFF){
				m_SequenceChange = true;
			}
		}
	});

#endif
}

RankingSequence::~RankingSequence(){

	//auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
	//socket->DestroyThread();
	//socket->CloseThread();
	auto recvObj = static_cast<RecvObject*>(SharedData::GetData(500));
	//recvObj->SetCallBack(nullptr);

	SAFE_DELETE_ARRAY(m_bChackPos);
	SAFE_DELETE_ARRAY(m_bRankIn);
	SAFE_DELETE(m_bgm);
}

void RankingSequence::Update(){

#ifdef NEW_SEQUENCECHANGE


	if (PathFileExists(L"z:\\Network\\SequenceChange")){
		m_SequenceChange = true;
		DeleteFile(L"z:\\Network\\SequenceChange");
	}

#endif


	auto wii = CWiiController::GetInstance(0);
	if( wii )
	{
		wii->Update();
	}

	if (m_SequenceChange ||  CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN)){
		m_bgm->Stop();
		DeleteFile(L"z:\\Network\\SequenceChange");

		MeekH::Application::GetInstance()->ChangeSequence( NEW FadeSequence( NEW TitleSequence ) );
#if 0
		auto socket = static_cast<MeekL::Socket* >(SharedData::GetData(100));
		auto addr = static_cast<sockaddr_in * >(SharedData::GetData(101));
		NetworkMessage msg;
		msg.messageID = 1;	//画面遷移
		msg.data[0] = 0xFF;	//次の
		socket->Sendto((char*)&msg, sizeof(msg), addr, sizeof(sockaddr_in));
#endif
	}

	static RankBoard *pRankBoard[5];
	bool dead[5] = { false, false, false, false, false };

	for (int i = (m_VisibleRankNum - 1); i >= 0; i--)
	{
		char RankName[20];
		sprintf_s<20>(RankName, "RankBoard%d", m_RankNum  + (i + 1) );
		pRankBoard[i] = (RankBoard *)GetChild("Camera")->GetChild(RankName);
	} 

	for (int i = (m_VisibleRankNum - 1); i >= 0; i--)
	{
		if (pRankBoard[i])
		{
			if (!pRankBoard[i]->GetBoolPos())
			{
				if (i == (m_VisibleRankNum - 1))
				{
					pRankBoard[i]->Update();
				}
				else if (pRankBoard[i + 1])
				{
					if (pRankBoard[i + 1]->GetBoardPos().x <= -400)
					{
						pRankBoard[i]->Update();
						m_bChackPos[i + 1] = true;
					}
					if (i == 0)
					{
						if (pRankBoard[i]->GetBoardPos().x <= -400)
						{
							m_bChackPos[i] = true;
						}
					}
				}
			}
			else
			{
				pRankBoard[i]->Update();

				if (!pRankBoard[i]->GetAlive())
				{
					pRankBoard[i]->GetParent()->RemoveChild(pRankBoard[i]);
					SAFE_DELETE(pRankBoard[i]);
					m_bChackPos[i] = false;
					dead[i] = false;
				}
			}
		}
		else
		{
			dead[i] = true;
		}
	}

	if (wii)
	{
		if (wii->GetAccel().Orientation.Z > 2.0f)
		{
			DeleteFile(L"z:\\Network\\SequenceChange");

			MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW TitleSequence()));
		}
	}
	else
	{
		if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_SPACE))
		{
			for (int i = (m_VisibleRankNum - 1); i >= 0; i--)
			{
				if (pRankBoard[i])
				{
					pRankBoard[i]->SetRankSpeedChange(true);
				}
			}
		}
	}


	if (m_VisibleRankNum >= 5)
	{
		if (m_bChackPos[0] &&
			m_bChackPos[1] &&
			m_bChackPos[2] &&
			m_bChackPos[3] &&
			m_bChackPos[4])
		{
			for (int i = 0; i < m_VisibleRankNum; i++)
			{
				if (pRankBoard[i])
				{
					pRankBoard[i]->SetBoolPos(true);
				}
			}
		}
	}
	else
	{
		if (m_bChackPos[0])
		{
			for (int i = 0; i < m_VisibleRankNum; i++)
			{
				if (pRankBoard[i])
				{
					pRankBoard[i]->SetBoolPos(true);
				}
			}
		}
	}

	if (m_VisibleRankNum > 2)
	{
		if (dead[0] &&
			dead[1] &&
			dead[2] &&
			dead[3] &&
			dead[4])
		{
			if (m_RankNum < 6)
			{
				m_VisibleRankNum = 1;
			}

			for (int i = 0; i < m_VisibleRankNum; i++)
			{
				if (m_RankNum > 0)
				{
					char RankName[20];
					sprintf_s<20>(RankName, "RankBoard%d", m_RankNum);
					auto Rank = NEW RankBoard;
					GetChild("Camera")->AddChild(Rank);
					Rank->Init( m_RankNum , *m_Score[m_RankNum - 1] , m_bRankIn[m_RankNum - 1] , m_bestShot[m_RankNum-1] );
					Rank->SetName(RankName);
					m_RankNum--;
				}
			}
		}
	}
	else
	{
		if (dead[0])
		{
			for (int i = 0; i < m_VisibleRankNum; i++)
			{
				if (m_RankNum > 0)
				{
					char RankName[20];
					sprintf_s<20>(RankName, "RankBoard%d", m_RankNum);
					auto Rank = NEW RankBoard;
					GetChild("Camera")->AddChild(Rank);
					Rank->Init( m_RankNum , *m_Score[m_RankNum - 1] , m_bRankIn[m_RankNum - 1] , m_bestShot[m_RankNum - 1] );
					Rank->SetName(RankName);
					m_RankNum--;
				}
			}
		}
	}
}

void RankingSequence::ChangeSequence()
{
	MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW TitleSequence()));
}
