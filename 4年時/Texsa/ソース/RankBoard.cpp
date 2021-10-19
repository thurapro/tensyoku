/****************************************************************************
* @file			RankBoard.h
* @brief
* @author 		Yuta Matsuo
*****************************************************************************/

//=============================================================================
// インクルード
//=============================================================================
#include "RankBoard.h"
#include "Score.h"
#include "Application.h"
#include "Node.h"
#include "Sprite.h"
#include "SharedData.h"
#include "Score.h"
#include <stdlib.h>
#include <stdio.h>
#include "Texture.h"
#include "Sequence.h"
#include "TitleSequence.h"
#include "FadeSequence.h"

USING_MEEK

//=============================================================================
// マクロ
//=============================================================================
#define SCORE_MAX (6)
#define VISIBLE_TIME (20)

int RankBoard::m_RankMax = 20;

//=============================================================================
// コンストラクタ
//=============================================================================
RankBoard::RankBoard()
{
	m_RankBackSprite = NULL;
	m_RankSprite = NULL;
	m_PhotoSprite = NULL;
	m_pScore = NEW Sprite*[SCORE_MAX];
	ZeroMemory(m_pScore, sizeof(m_pScore));
	m_pos = DirectX::SimpleMath::Vector3(200, 0, 0);
	m_size = DirectX::SimpleMath::Vector2(30, 30);
	m_bAlive = true;
	m_bSetPos = false;
	m_StopCount = 0;
	m_visible = true;
	m_RankSpeedChange = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
RankBoard::~RankBoard()
{
	m_RankMax--;
}

//=============================================================================
// 初期化
//=============================================================================
void RankBoard::Init(int Rank, int score, bool bRankIn , wchar_t *bestShot)
{
	SetRank(Rank);
	char name[20];
	sprintf_s<20>(name, "rank%d", Rank);

	//m_RankBackSprite = NEW Sprite(1, 1, (L"NULL"), L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	//AddChild(m_RankBackSprite);
	//m_RankBackSprite->SetSize(1200, 400);
	//m_RankBackSprite->SetPos(DirectX::SimpleMath::Vector3(1200, 10, Rank));
	//m_RankBackSprite->SetColor(0.0f, 0.0f, 0.0f, 0.0f);

	if (Rank > 5)
	{
		m_RankSprite = NEW Sprite(1, 1, m_RankTexPath, L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
		AddChild(m_RankSprite);

		m_RankSprite->SetSize(133, 100);
		m_RankSprite->AddPos(m_pos);
		m_RankSprite->SetName(name);

		sprintf_s<20>(name, "photo%d", Rank);
		m_PhotoSprite = NEW Sprite( m_RankSprite->GetSize().x , m_RankSprite->GetSize().y , bestShot , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
		AddChild(m_PhotoSprite);
		m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 100, m_pos.y, 0));
		m_PhotoSprite->SetName(name);

		for (int i = 0; i < SCORE_MAX; i++)
		{
			char numName[20];
			sprintf_s<20>(numName, "rank%dnum%d", Rank, i + 1);
			m_pScore[i] = NEW Sprite(1, 1, L"data\\texture\\nomber111.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
			AddChild(m_pScore[i]);
			SetName(numName);
			if (Rank > 5)
			{
				m_pScore[i]->SetSize(DirectX::SimpleMath::Vector2(60, 60));
			}
			else
			{
				m_pScore[i]->SetSize(DirectX::SimpleMath::Vector2(100, 100));
			}
		}
	}
	else if (m_Rank <= 5)
	{
		m_RankSprite = NEW Sprite(1, 1, m_RankTexPath, L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
		AddChild(m_RankSprite);
		m_RankSprite->SetSize(200, 150);
		m_RankSprite->SetPos(DirectX::SimpleMath::Vector3(800, 0, Rank));

		m_RankSprite->SetName(name);

		if (m_Rank < 4)
		{
			m_RankBackSprite = NEW Sprite(1, 1, m_RankTexPath, L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
			AddChild(m_RankBackSprite);
			m_RankBackSprite->SetSize(1200, 400);
			m_RankBackSprite->SetPos(DirectX::SimpleMath::Vector3(1200, 10, Rank));
			m_RankSprite->SetVisible(false);
		}
		sprintf_s<20>(name, "photo%d", Rank);
		m_PhotoSprite = NEW Sprite( m_RankSprite->GetSize().x , m_RankSprite->GetSize().y , bestShot , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
		AddChild(m_PhotoSprite);
 		m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x, m_pos.y, 0));
		m_PhotoSprite->SetName(name);

		for (int i = 0; i < SCORE_MAX; i++)
		{
			char numName[20];
			sprintf_s<20>(numName, "rank%dnum%d", Rank, i + 1);
			m_pScore[i] = NEW Sprite(1, 1, L"data\\texture\\nomber111.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
			AddChild(m_pScore[i]);
			SetName(numName);
			if (Rank > 5)
			{
				m_pScore[i]->SetSize(DirectX::SimpleMath::Vector2(60, 60));
			}
			else
			{
				m_pScore[i]->SetSize(DirectX::SimpleMath::Vector2(100, 100));
			}
		}
	}

	DirectX::SimpleMath::Vector2 tex[4];

	float Score[SCORE_MAX];

	Score[0] = ((score % 1000000) / 100000);
	Score[1] = ((score % 100000) / 10000);
	Score[2] = ((score % 10000) / 1000);
	Score[3] = ((score % 1000) / 100);
	Score[4] = ((score % 100) / 10);
	Score[5] = ((score % 10) / 1);

	Score[0] *= 0.1;
	Score[1] *= 0.1;
	Score[2] *= 0.1;
	Score[3] *= 0.1;
	Score[4] *= 0.1;
	Score[5] *= 0.1;


	DirectX::SimpleMath::Vector3 pos;

	pos = DirectX::SimpleMath::Vector3(m_PhotoSprite->GetPos().x + 100, 0, 0);

	// 横にズレル
	for (int i = 0; i < SCORE_MAX; i++)
	{
		DirectX::SimpleMath::Vector2 tex[4];
		m_pScore[i]->AddTexCoordX((float)Score[i]);
		tex[0] = DirectX::SimpleMath::Vector2(Score[i], 1.0f);
		tex[1] = DirectX::SimpleMath::Vector2(Score[i], 0.0f);
		tex[2] = DirectX::SimpleMath::Vector2(Score[i] + 0.1f, 1.0f);
		tex[3] = DirectX::SimpleMath::Vector2(Score[i] + 0.1f, 0.0f);
		m_pScore[i]->SetTexCoord(tex);
		m_pScore[i]->SetPos(pos.x, m_pos.y, 0);
		pos.x += m_pScore[i]->GetSize().x;
	}
	m_size.y += m_RankSprite->GetSize().y;
	m_Rankin = bRankIn;
	if (m_Rank < 6 )
	{
		m_StopCount = 150;
	}
	if (m_Rank == 1)
	{
		m_StopCount = 200;
	}
}

void RankBoard::Update()
{
	if (m_Rank > 5)
	{
		if (m_pos.x > -400)
		{
			if (m_RankSpeedChange)
			{
				m_pos.x = -400;
			}
			m_pos.x -= 20;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 100, m_pos.y, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);

			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x, m_pos.y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
		}
		else if (m_pos.x <= -400 && m_bSetPos)
		{
			m_pos.y -= 10;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 100, m_pos.y, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);

			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x, m_pos.y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
		}
	}
	else if ( m_Rank <= 5 && m_Rank > 3 )
	{
		if (m_pos.x > -400)
		{
			if (m_RankSpeedChange)
			{
				m_pos.x = -400;
			}
			m_pos.x -= 20;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 50, m_pos.y, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);

			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x, m_pos.y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
			m_bSetPos = true;
		}
		else if (m_pos.x <= -400 && m_bSetPos && m_StopCount < 0)
		{
			m_pos.y -= 10;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 50, m_pos.y, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);

			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x, m_pos.y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
		}
		if (m_bSetPos)
		{
			m_StopCount--;
		}
	}
	else
	{
		if (m_pos.x > -500)
		{
			if (m_RankSpeedChange)
			{
				m_pos.x = -500;
				m_RankBackSprite->SetPos(0, 0, 20);
			}

			if (m_RankBackSprite)
			{
				m_RankBackSprite->AddPos(DirectX::SimpleMath::Vector3(-20, 0, 10));
			}
			m_pos.x -= 20;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 20, m_pos.y + 50, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);
			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x + 20, m_PhotoSprite->GetPos().y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
			m_bSetPos = true;
		}
		else if (m_pos.x <= -500 && m_bSetPos && m_StopCount < 0)
		{
			if (m_RankBackSprite)
			{
				m_RankBackSprite->AddPos(DirectX::SimpleMath::Vector3(0, -10, 0));
			}
			m_pos.y -= 10;
			m_RankSprite->SetPos(m_pos);
			m_PhotoSprite->SetPos(DirectX::SimpleMath::Vector3(m_pos.x + m_RankSprite->GetSize().x + 20, m_pos.y + 50, 0));
			DirectX::SimpleMath::Vector3 pos(m_PhotoSprite->GetPos().x + 160, 0, 0);
			for (int i = 0; i < SCORE_MAX; i++)
			{
				m_pScore[i]->SetPos(pos.x + 20, m_PhotoSprite->GetPos().y, 0);
				pos.x += m_pScore[i]->GetSize().x;
			}
		}
		if (m_bSetPos)
		{
			m_StopCount--;
		}
	}

	if (m_Rankin)
	{
		for (int i = 0; i < SCORE_MAX; i++)
		{
			m_pScore[i]->SetVisible(m_visible);
			if (m_visibleTime < 0)
			{
				m_visibleTime = VISIBLE_TIME;
				m_visible = !m_visible;
			}
		}
		m_visibleTime--;
	}


	if (m_bSetPos && m_StopCount <= 0)
	{
		if (m_Rank < 4)
		{
			float posY = m_RankBackSprite->GetPos().y;
			if (posY <= -500)
			{
				if (m_RankBackSprite)
				{
					RemoveChild(m_RankBackSprite);
					SAFE_DELETE(m_RankBackSprite);
				}
				RemoveChild(m_RankSprite);
				SAFE_DELETE(m_RankSprite);
				RemoveChild(m_PhotoSprite);
				SAFE_DELETE(m_PhotoSprite);
				for (int i = 0; i < SCORE_MAX; i++)
				{
					RemoveChild(m_pScore[i]);
					SAFE_DELETE(m_pScore[i]);
				}
				SAFE_DELETE_ARRAY(m_pScore);
				m_bAlive = false;

				if (m_Rank == 1)
				{
					MeekH::Application::GetInstance()->ChangeSequence(NEW FadeSequence(NEW TitleSequence()));
				}
			}
		}
		else
		{
			if (m_pos.y <= -300)
			{
				if (m_RankBackSprite)
				{
					RemoveChild(m_RankBackSprite);
					SAFE_DELETE(m_RankBackSprite);
				}
				RemoveChild(m_RankSprite);
				SAFE_DELETE(m_RankSprite);
				RemoveChild(m_PhotoSprite);
				SAFE_DELETE(m_PhotoSprite);
				for (int i = 0; i < SCORE_MAX; i++)
				{
					RemoveChild(m_pScore[i]);
					SAFE_DELETE(m_pScore[i]);
				}
				SAFE_DELETE_ARRAY(m_pScore);
				m_bAlive = false;
			}
		}
	}



}

//=============================================================================
// 順位を設定
//=============================================================================
void RankBoard::SetRank(int Rank)
{
	swprintf_s<128>(m_RankTexPath, L"data\\texture\\%d.png", Rank);

	m_Rank = Rank;

	if (Rank == 16)
	{
		int ii = 0;
		ii++;
	}

	if (Rank < m_RankMax)
	{
		char RankName[20];
		sprintf_s<20>(RankName, "RankBoard%d", Rank + 1);
		auto rankBoard = (RankBoard *)GetParent()->GetChild(RankName);
		auto pos = rankBoard->GetBoardPos();
		auto size = rankBoard->GetBoardSize();
		m_pos = pos;
		m_pos.y += size.y;
		//m_pos.z -= Rank;
	}
	else 
	{
		if (Rank > 5)
		{
			m_pos.x = 700;
			m_pos.y = -250;
			//m_pos.z += Rank;
		}
		else
		{
			m_pos.x = 700;
			m_pos.y = -45;
			//m_pos.z += Rank;
		}
	}
}

//=============================================================================
// ランキングボードの位置取得
//=============================================================================
DirectX::SimpleMath::Vector3 RankBoard::GetBoardPos()
{
	return m_pos;
}

//=============================================================================
// ランキングボードの位置設定
//=============================================================================
void RankBoard::SetBoardPos(DirectX::SimpleMath::Vector3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ランキングボードのサイズ取得
//=============================================================================
DirectX::SimpleMath::Vector3 RankBoard::GetBoardSize()
{
	return m_size;
}

//=============================================================================
// ランキングボードのサイズ設定
//=============================================================================
void RankBoard::SetBoardSize(DirectX::SimpleMath::Vector2 size)
{
	m_size = size;
}

//=============================================================================
// ランキングボードの最大数取得
//=============================================================================
int RankBoard::GetRankMax()
{
	return m_RankMax;
}

//=============================================================================
// ランキングボードの最大数を設定
//=============================================================================
void RankBoard::SetRankMax(int i)
{
	m_RankMax = i;
}

//=============================================================================
// ランキングボードを取得
//=============================================================================
bool RankBoard::GetAlive()
{
	return m_bAlive;
}

//=============================================================================
// ランキングボードの指定場所についたかを取得
//=============================================================================
bool RankBoard::GetBoolPos()
{
	return m_bSetPos;
}

//=============================================================================
// ランキングボードの指定場所についたかを設定
//=============================================================================
void RankBoard::SetBoolPos(bool bMovePos)
{
	m_bSetPos = bMovePos;
}

//=============================================================================
// ランキングボードの指定場所についたかを取得
//=============================================================================
bool RankBoard::GetRankSpeedChange()
{
	return m_RankSpeedChange;
}

//=============================================================================
// ランキングボードの指定場所についたかを設定
//=============================================================================
void RankBoard::SetRankSpeedChange(bool bChange)
{
	m_RankSpeedChange = bChange;
}