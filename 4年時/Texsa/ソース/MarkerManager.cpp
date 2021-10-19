//=============================================================================
// MarkerManager.cpp
//
// another: Yuta Matsuo
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "MarkerManager.h"
#include "Application.h"
#include "MarkerButton.h"
#include "Memory.h"
#include "Sprite.h"
#include "MusicScoreLoader.h"
#include "Score.h"
#include "SharedData.h"
#include "GameSequence.h"
#include "SoundObject.h"
#include "CollisionBar.h"

USING_MEEK

//=============================================================================
// コンストラクタ
//=============================================================================
MarkerManager::MarkerManager()
{

	m_MaxToken		= 0;	// 最大音符数
	m_MusicScore	= NULL;
	m_CountToken = 0;
	m_VisibleToken = 0;
	m_StartToken = 0;
	m_nMaxSpeed = 1;
	m_bMarkerSuccess = false;
	m_nComboNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
MarkerManager::~MarkerManager()
{
	SAFE_DELETE(m_MusicScore);
}

//=============================================================================
// 譜面初期化
//=============================================================================
void MarkerManager::Init(char *FilePath)
{
	// 譜面読み込み
	Load(FilePath);

	m_pScore = NEW Score;
	AddChild(m_pScore);
	m_pScore->Init();
	m_pScore->SetName("score");

	auto Good = NEW Sprite(100, 50, L"data\\texture\\Good.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	Good->SetName("Good");
	Good->SetVisible(false);
	AddChild(Good);

	auto Bad = NEW Sprite(100, 50, L"data\\texture\\Bad.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	Bad->SetName("Bad");
	Bad->SetVisible(false);
	AddChild(Bad);
	
	auto Marker = NEW Sprite(1260, 200, L"data\\texture\\gakuhu.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	Marker->SetPos(DirectX::SimpleMath::Vector3(0, -200, 18));
	Marker->SetPriority(4);
	Marker->SetName("Marker");
	AddChild(Marker);

	auto Wave = NEW Sprite(1260, 150, L"data\\texture\\wave_bar.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	Wave->SetPos(DirectX::SimpleMath::Vector3(0, -200, 16));
	Wave->SetPriority(5);
	Wave->SetName("Wave");
	AddChild(Wave);


	auto ColBar = NEW CollisionBar;
	AddChild(ColBar);
	ColBar->SetPriority(6);

	ColBar->Init();
	ColBar->SetName("col");

	while (m_VisibleToken < 25)
	{	
		if (m_CountToken < m_MaxToken)
		{
			char ChildButtonName[20];
			sprintf_s<20>(ChildButtonName, "Button%d", m_CountToken);
			char TokenType = (char)m_MusicScore->note[m_CountToken].scoreLength;
			if (TokenType != 16)
			{
				TokenType += 48;
			}
			else
			{
				TokenType = 'F';
			}
			auto Button = NEW CMarkerButton;
			AddChild(Button);
			Button->SetPriority(7);
			char ButtonType = (char)m_MusicScore->note[m_CountToken].subGameScoreMode;
			ButtonType = 'C';
			Button->Init(TokenType, (bool)m_MusicScore->note[m_CountToken].ScoreType, ButtonType, m_CountToken);
			Button->SetName(ChildButtonName);
			m_CountToken++;
		}
		else
		{
			break;
		}
	}

}

//=============================================================================
// 譜面更新
//=============================================================================
void MarkerManager::Update()
{
	for (int i = m_StartToken; i < m_CountToken; i++)
	{
		char ChildButtonName[20];
		sprintf_s<20>(ChildButtonName, "Button%d", i);
		auto ChildButton = (CMarkerButton *)GetChild(ChildButtonName);

		if (ChildButton)
		{
			ChildButton->Update();
			if( !ChildButton->GetAlive() )
			{ 
				if (ChildButton->GetSuccess()){
					AddGoodNum(1);
				}
				else{
					AddBadNum(1);
				}
				RemoveChild(ChildButton);
				delete ChildButton;
				m_VisibleToken--;
				m_StartToken++;
				if (m_CountToken < m_MaxToken )
				{
					char ChildButtonName[20];
					sprintf_s<20>(ChildButtonName, "Button%d", m_CountToken);
					char TokenType = (char)m_MusicScore->note[m_CountToken].scoreLength;
					if (TokenType != 16)
					{
						TokenType += 48;
					}
					else
					{
						TokenType = 'F';
					}
					auto Button = NEW CMarkerButton;
					AddChild(Button);
					Button->SetPriority(7);
					char ButtonType = (char)m_MusicScore->note[m_CountToken].subGameScoreMode;
					ButtonType += 65;
					Button->Init(TokenType, (bool)m_MusicScore->note[m_CountToken].ScoreType, ButtonType, m_CountToken);
					Button->SetName(ChildButtonName);
					m_CountToken++;
					m_VisibleToken++;
				}
			}
		}
	}

	auto Wave = (Sprite *)GetChild("Wave");
	DirectX::SimpleMath::Vector2 tex[4];
	float Speed = (m_nMaxSpeed % 10) / 1;
	Speed *= 0.1f;

	if (Wave)
	{
		Wave->AddTexCoordX(Speed);
		tex[0] = DirectX::SimpleMath::Vector2(Speed, 1.0f);
		tex[1] = DirectX::SimpleMath::Vector2(Speed, 0.0f);
		tex[2] = DirectX::SimpleMath::Vector2(Speed + 0.1f, 1.0f);
		tex[3] = DirectX::SimpleMath::Vector2(Speed + 0.1f, 0.0f);
		Wave->SetTexCoord(tex);
		m_nMaxSpeed++;
	}

	m_pScore->Update();
}


//=============================================================================
// 譜面保存
//=============================================================================
float MarkerManager::GetTokenSpeed()
{
	return m_fTokenSpeed;
}

//=============================================================================
// 譜面読み込み
//=============================================================================
void MarkerManager::Load(char *FilePath)
{
	FILE *file;

	int Horizon_Token = 0;
	int Vertical_Token = 0;
	int ch = 0;

	m_MusicScore = NEW MusicScore;

	auto pMusicScore = NEW MusicScoreLoader;
	*m_MusicScore = pMusicScore->ReadFile(FilePath);

	m_MaxToken = m_MusicScore->noteNum;
	m_MaxToken--;
	
	auto GameSquence = (GameSequence *)GetParent()->GetParent();
	//auto Sound = GameSquence->GetSound();

	//*Sound = NEW CSoundObject("data\\a.wav");

	CMarkerButton::SetBpm( (float)m_MusicScore->header.bpm);
}

//=============================================================================
// 出現している音符数を取得
//=============================================================================
void MarkerManager::SetVisibleToken(int count)
{
	m_VisibleToken += count;
}

//=============================================================================
// 出現している音符数を取得
//=============================================================================
void MarkerManager::SetStartToken(int count)
{
	m_StartToken += count;
}

//=============================================================================
// ボタン判定が成功したのか
//=============================================================================
void MarkerManager::SetMarkerSuccess(bool Success)
{
	m_bMarkerSuccess = Success;
}

//=============================================================================
// コンボ数設定
//=============================================================================
void MarkerManager::SetComboNum(int i)
{
	m_nComboNum = i;
}

//=============================================================================
// コンボ数加算
//=============================================================================
void MarkerManager::AddComboNum(int i)
{
	m_nComboNum += i;
}

//=============================================================================
// コンボ数取得
//=============================================================================
int MarkerManager::GetComboNum()
{
	return m_nComboNum;
}

void MarkerManager::AddGoodNum( int i ){
	auto good = static_cast< int* >( SharedData::GetData(SharedData::GOOD_NUM) );
	( *good ) += i;
}
void MarkerManager::AddBadNum( int i ){
	auto bad = static_cast< int* >( SharedData::GetData( SharedData::BAD_NUM ) );
	( *bad ) += i;
}
