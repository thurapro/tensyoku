/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ 譜面表示クラス
-----------------------------------------------------------------------------*/

//=============================================================================
// インクルード
//=============================================================================
#include "MarkerButton.h"
#include "Application.h"
#include "Sprite.h"
#include "CollisionBar.h"
#include "GameSequence.h"
#include "WiiController.h"
#include <stdlib.h>
#include <stdio.h>
#include "MarkerManager.h"
#include "Score.h"

USING_MEEK

int CMarkerButton::m_TokenNum = 0;
float CMarkerButton::m_BPM = 0.0f;
float CMarkerButton::m_speedTimes = 1.0f;

//=============================================================================
// インスタンス生成
//=============================================================================
CMarkerButton::CMarkerButton()
{
	m_pos = NEW DirectX::SimpleMath::Vector3(-510, -200, 5);
	m_scl = NEW DirectX::SimpleMath::Vector2(60, 80);
	m_speed = NEW DirectX::SimpleMath::Vector3(0, 0, 0);
	m_colscl = NEW DirectX::SimpleMath::Vector2;
	m_ButtonType = BUTTON_A;
	m_TokenType = TOKEN_UNKNOWN;
	m_Index = m_TokenNum; 
	sprintf_s(m_Name, "%d", m_Index);
	m_TokenNum++;
	m_Alive = true;
	m_nScoreSum = 20;
	m_col = false;
	m_success = false;
}

//=============================================================================
// インスタンス破棄
//=============================================================================
CMarkerButton::~CMarkerButton()
{
	SAFE_DELETE(m_pos);
	SAFE_DELETE(m_scl);
	SAFE_DELETE(m_speed);
	SAFE_DELETE_ARRAY(m_ChildAlive);
}

//=============================================================================
// 初期化
//=============================================================================
void CMarkerButton::Init(char TokenType, bool ScoreType, char ButtonType, int CountToken)
{
	// 速度を設定
	m_speed->x = ((60.0f / m_BPM) / 4 * (m_scl->x * m_speedTimes));

	//// 音符タイプ設定
	SetToken(TokenType, CountToken);

	// ボタンタイプを設定
	SetButton(ButtonType);

	auto Button = NEW Sprite(m_scl->x, m_scl->y, m_ButtonSprite, L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	Button->SetTexture(m_ButtonSprite);
	Button->SetPriority(7);

	AddChild(Button);

	Button->SetName(m_Name);
	Button->SetPos(*m_pos);

	m_colscl->x = m_scl->x * 0.5f;
	m_colscl->y = m_scl->y;

	if (ScoreType)
	{
		Button->SetVisible(false);
	}

	m_ChildAlive = NEW bool[CWiiController::GetMaxNum()];
	for (int i = 0; i < CWiiController::GetMaxNum(); i++)
	{
		m_ChildAlive[i] = true;
	}

	auto pMarkerManager = (MarkerManager *)GetParent();
	pMarkerManager->SetVisibleToken(1);
}

//=============================================================================
// 更新
//=============================================================================
void CMarkerButton::Update(void)
{
	auto pScore = (Score *)GetParent()->GetChild("score");
	auto Button = (Sprite *)GetChild(m_Name);

	m_pos->x -= m_speed->x;

	if (Button)
	{
		auto pMarkerManager = (MarkerManager *)GetParent();
		CollisionBar *ColBar = (CollisionBar *)GetParent()->GetChild("col");

		auto Pos = ColBar->GetPos();
		auto Scl = ColBar->GetScl();

		int WiiMaxNum = CWiiController::GetMaxNum();

		for (int i = 0; i < WiiMaxNum; i++)
		{
			if (m_ChildAlive[i])
			{
				CWiiController *Wii = CWiiController::GetInstance(i);
				if (!m_col)
				{
					if (Collision(*m_pos, *m_colscl, Pos, Scl))
					{
						m_col = true;
						m_releas = false;
					}
				}
				if (!Collision(*m_pos, *m_colscl, Pos, Scl))
				{
					m_releas = true;
				}
				if (m_col)
				{
					if (m_ButtonType != BUTTON_ACCEL)
					{
						// 同じボタンが指定されていたら
						if (Wii->Trigger(CWiiController::BUTTON_A))
						{
							if (m_ButtonType == Wii->GetButton())
							{
								if (Collision(*m_pos, *m_colscl, Pos, Scl))
								{
									pMarkerManager->GetChild("Bad")->SetVisible(false);
									pMarkerManager->GetChild("Good")->SetVisible(false);
									Button->SetTexture(L"data\\texture\\A_Button.png");
									//pScore->SetScore(m_nScoreSum);
									pMarkerManager->AddComboNum(1);
									//pMarkerManager->AddGoodNum(1);
									m_ChildAlive[i] = false;
									m_success = true;
								}
							}
						}
					}
					else
					{
						if (Wii->GetAccel().Z > 3.2f)
						{
							if (Collision(*m_pos, *m_colscl, Pos, Scl))
							{
								pMarkerManager->GetChild("Bad")->SetVisible(false);
								pMarkerManager->GetChild("Good")->SetVisible(false);
								Button->SetTexture(L"data\\texture\\shake_out.png");
								pScore->SetScore(m_nScoreSum);
								pMarkerManager->AddComboNum(1);
								//pMarkerManager->AddGoodNum( 1 );

								m_ChildAlive[i] = false;
								m_success = true;
								//}
							}
						}
					}
				}
			}
			if (m_col && m_releas)
			{
				if (!m_success)
				{
					pMarkerManager->GetChild("Bad")->SetVisible(false);
					pMarkerManager->GetChild("Good")->SetVisible(false);
					pMarkerManager->SetComboNum(0);
					//pMarkerManager->AddBadNum( 1 );

				}
			}
		}
		Button->SetPos(*m_pos);
		if (m_pos->x < -700)
		{
			m_Alive = false;
		}
	}
}

void CMarkerButton::Draw()
{
	Node::Draw();
}


//=============================================================================
// 矩形当たり判定
//=============================================================================
bool CMarkerButton::Collision(DirectX::SimpleMath::Vector3 MarkerPos,
	DirectX::SimpleMath::Vector2 MarkerScl,
	DirectX::SimpleMath::Vector3 ColPos,
	DirectX::SimpleMath::Vector2 ColScl)
{
	// マーカボタン用の頂点算出
	DirectX::SimpleMath::Vector3 Marker;

	// 当たるもの用の頂点算出
	DirectX::SimpleMath::Vector3 Col;

	Marker = DirectX::SimpleMath::Vector3((-MarkerScl.x * 0.5f) + MarkerPos.x, (-MarkerScl.y * 0.5f) + MarkerPos.y, 0.0f);

	Col = DirectX::SimpleMath::Vector3((-ColScl.x * 0.5f) + ColPos.x, (-ColScl.y * 0.5f) + ColPos.y, 0.0f);

	if ( (Col.x < Marker.x + (MarkerScl.x * 0.8f) ) &&
		 (Marker.x < Col.x + (ColScl.x * 0.8f) )   &&
		 (Col.y < Marker.y + MarkerScl.y) &&
		 (Marker.y < Col.y + ColScl.y)	   )
	{
		// 当たった
		return true;
	}
	// 外れた
	return false;
}

//=============================================================================
// ボタンの種類設定
//=============================================================================
void CMarkerButton::SetButton(char ButtonType)
{
	if (ButtonType == 'A')
	{
		m_ButtonType = BUTTON_A;
		m_ButtonSprite = L"data\\texture\\A_Button_out.png";
	}
	else if (ButtonType == 'C')
	{
		m_ButtonType = BUTTON_ACCEL;
		m_ButtonSprite = L"data\\texture\\shake.png";
	}
}

//=============================================================================
// 音符の種類設定
//=============================================================================
void CMarkerButton::SetToken(char TokenType, int CountToken)
{
	int index = CountToken - 1;
	DirectX::SimpleMath::Vector3 PrevPos = *m_pos;
	char ButtonName[20] = "Button";
	char ButtonIndex[5] = { NULL, NULL, NULL, NULL, NULL };
	std::string ChildButtonName;
	double pos = 0;

	int i = 0;

	if (CountToken > 0 && index != CountToken)
	{
		itoa(index, ButtonIndex, 10);
		strcat(ButtonName, ButtonIndex);

		auto pMarkerButton = (CMarkerButton*)GetParent()->GetChild(ButtonName);
		ChildButtonName = pMarkerButton->GetButtonName();
		auto pSprite = (Sprite *)pMarkerButton->GetChild(ChildButtonName);

		PrevPos = pSprite->GetPos();
		i = 1;
	}

	if (TokenType == '0')
	{
		pos = (m_BPM / 60) * 256;

		m_TokenType = TOKEN_0;
		m_pos->x = PrevPos.x;
		m_pos->x += (m_speed->x * 1) * pos;
	}
	else if (TokenType == '2')
	{
		pos = (60.0f / m_BPM) * 128;
		m_TokenType = TOKEN_2;
		m_pos->x = PrevPos.x;
		m_pos->x += ( m_speed->x * pos);
	}
	else if (TokenType == '4')
	{
		pos = (60 / m_BPM) * 64;
		m_TokenType = TOKEN_4;
		m_pos->x = PrevPos.x;
		m_pos->x += ( m_speed->x * pos);
	}
	else if (TokenType == '8')
	{
		pos = (60 / m_BPM) * 32;
		m_TokenType = TOKEN_8;
		m_pos->x = PrevPos.x;
		m_pos->x += (m_speed->x * pos);
	}
	else if (TokenType == 'F')
	{
		pos = (60 / m_BPM) * 16;
		m_TokenType = TOKEN_16;
		m_pos->x = PrevPos.x;
		m_pos->x += (m_speed->x * pos);
	}
	else
	{
		m_TokenType = TOKEN_UNKNOWN;
	}

	m_Alive = true;
}

void CMarkerButton::SetBpm(float Bpm)
{
	m_BPM = Bpm;
}


