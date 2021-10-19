/**************************************************************************//**
* @file			Score.cpp
* @brief
* @author 		Hirai Yuuki
*****************************************************************************/
#include "Result.h"

#include "Application.h"
#include "Node.h"
#include "Sprite.h"
#include "SharedData.h"
#include "TextureComponent.h"

USING_MEEK

#define CNT_TIME (30)				// スコア回転時間
#define RANKIN_SCORE_S (5000)		// スコア5000点以上でSランク判定
#define RANKIN_SCORE_A (4000)		// スコア4000点以上でAランク判定
#define RANKIN_SCORE_B (3000)		// スコア3000点以上でBランク判定
#define RANKIN_SCORE_C (2000)		// スコア2000点以上でCランク判定
#define RANKIN_SCORE_D (1000)		// スコア1000点以上でDランク判定
#define MAIN_SCORE_POSY (260)		// MainScore表示位置Y
#define SAB_SCORE_POSY (140)		// SabScore表示位置Y
#define TOTAL_SCORE_POSY (25)		// TotalScore表示位置Y
#define GOOD_SCORE_POSY	(-130)		// GoodScore表示位置Y
#define BAD_SCORE_POSY (-250)		// BadScore表示位置Y
#define RANKING_CHAR_POSY (-75)		// ランク文字表示位置Y
#define BESTPHOTO_POSY (-180)		// BestPhoto表示位置Y
#define SIZEX (40)					// スコア大きさX
#define SIZEY (40)					// スコア大きさY
#define MAIN_SCORE_MAX (99999)		// MainScore上限
#define SAB_SCORE_MAX (99999)		// SabScore上限
#define TOTAL_SCORE_MAX (99999)		// TotalScore上限
#define GOOD_SCORE_MAX (99)			// GoodScore上限
#define BAD_SCORE_MAX (99)			// BadScore上限
#define AAA (100)

//=============================================================================
// コンストラクタ
//=============================================================================
Result::Result(){
	m_pos = NEW DirectX::SimpleMath::Vector3;
	m_rot = NEW DirectX::SimpleMath::Vector3;
	m_scl = NEW DirectX::SimpleMath::Vector3;

	m_nTime = 0;				// Result内時間

	m_nMainScoreBase = 0;		// MainScoreの値が入る
	m_nMainScore1 = 0;			// MainScoreの1桁目
	m_nMainScore2 = 0;			// MainScoreの2桁目
	m_nMainScore3 = 0;			// MainScoreの3桁目
	m_nMainScore4 = 0;			// MainScoreの4桁目
	m_nMainScore5 = 0;			// MainScoreの5桁目

	m_nSabScoreBase = 0;		// SabScoreの値が入る
	m_nSabScore1 = 0;			// SabScoreの1桁目
	m_nSabScore2 = 0;			// SabScoreの2桁目
	m_nSabScore3 = 0;			// SabScoreの3桁目
	m_nSabScore4 = 0;			// SabScoreの4桁目
	m_nSabScore5 = 0;			// SabScoreの5桁目

	m_nTotalScoreBase = 0;		// TotalScoreの値が入る
	m_nTotalScore1 = 0;			// TotalScoreの1桁目
	m_nTotalScore2 = 0;			// TotalScoreの2桁目
	m_nTotalScore3 = 0;			// TotalScoreの3桁目
	m_nTotalScore4 = 0;			// TotalScoreの4桁目
	m_nTotalScore5 = 0;			// TotalScoreの5桁目
	m_nTotalScore6 = 0;			// TotalScoreの6桁目

	m_nGoodScoreBase = 0;		// GoodScoreの値が入る
	m_nGoodScore1 = 0;			// GoodScoreの1桁目
	m_nGoodScore2 = 0;			// GoodScoreの2桁目

	m_nBadScoreBase = 0;		// BadScoreの値が入る
	m_nBadScore1 = 0;			// BadScoreの1桁目
	m_nBadScore2 = 0;			// BadScoreの2桁目

	m_nRankingChar = 0;			// ランクの値が入る
	m_nRankingChar1 = 0;		// 

	m_bMainScoreFlg[0] = true;
	m_bMainScoreFlg[1] = false;
	m_bMainScoreFlg[2] = false;
	m_bMainScoreFlg[3] = false;
	m_bMainScoreFlg[4] = false;

	m_bSabScoreFlg[0] = false;
	m_bSabScoreFlg[1] = false;
	m_bSabScoreFlg[2] = false;
	m_bSabScoreFlg[3] = false;
	m_bSabScoreFlg[4] = false;

	m_bTotalScoreFlg[0] = false;
	m_bTotalScoreFlg[1] = false;
	m_bTotalScoreFlg[2] = false;
	m_bTotalScoreFlg[3] = false;
	m_bTotalScoreFlg[4] = false;
	m_bTotalScoreFlg[5] = false;

	m_bGoodScoreFlg = false;
	m_bBadScoreFlg = false;

	m_bRankingCharFlg = false;
	m_bBestPhotoFlg = false;

	r = 1.0f, g = 1.0f, b = 1.0f, a = 0.0f;
	rr = 1.0f, gg = 1.0f, bb = 1.0f, aa = 0.0f;


	SetMainScore(0);
	SetSabScore(0);
	SetGoodScore(0);
	SetBadScore(0);
}


//=============================================================================
// デストラクタ
//=============================================================================
Result::~Result(){
}


//=============================================================================
// 初期化処理
//=============================================================================
void Result::Init(){
	//========================================================================
	// 数値
	//========================================================================
	// MainScore数値
	auto Main_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 1桁目
	Main_Score1->SetName("Main_Score1");
	auto Main_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 2桁目
	Main_Score2->SetName("Main_Score2");						 
	auto Main_Score3 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 3桁目
	Main_Score3->SetName("Main_Score3");						 
	auto Main_Score4 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 4桁目
	Main_Score4->SetName("Main_Score4");
	auto Main_Score5 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 5桁目
	Main_Score5->SetName("Main_Score5");

	// SabScore数値
	auto Sab_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score1->SetName("Sab_Score1");
	auto Sab_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score2->SetName("Sab_Score2");
	auto Sab_Score3 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score3->SetName("Sab_Score3");
	auto Sab_Score4 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score4->SetName("Sab_Score4");
	auto Sab_Score5 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score5->SetName("Sab_Score5");

	// TotalScore数値
	auto Total_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score1->SetName("Total_Score1");
	auto Total_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score2->SetName("Total_Score2");
	auto Total_Score3 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score3->SetName("Total_Score3");
	auto Total_Score4 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score4->SetName("Total_Score4");
	auto Total_Score5 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score5->SetName("Total_Score5");
	auto Total_Score6 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score6->SetName("Total_Score6");

	// Good数値
	auto Good_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score1->SetName("Good_Score1");
	auto Good_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score2->SetName("Good_Score2");

	// Bad数値
	auto Bad_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score1->SetName("Bad_Score1");
	auto Bad_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score2->SetName("Bad_Score2");





	//========================================================================
	// 文字
	//========================================================================
	// MainScore文字
	auto Main_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\main.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Main_Score_Char->SetName("Main_Score_Char");
	Main_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, MAIN_SCORE_POSY, 0));	// 表示位置

	// SabScore文字
	auto Sab_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\sub.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score_Char->SetName("Sab_Score_Char");
	Sab_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, SAB_SCORE_POSY, 0));	// 表示位置

	// TotalScore文字
	auto Total_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\total.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score_Char->SetName("Total_Score_Char");
	Total_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, TOTAL_SCORE_POSY, 0));	// 表示位置

	// ＋文字
	auto Purasu = NEW Sprite(64, 68, L"data\\texture\\result\\plus.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Purasu->SetName("Purasu");
	Purasu->SetPos(DirectX::SimpleMath::Vector3(150, 200, 0));	// 表示位置
	
	// ＝文字
	auto Ikoru = NEW Sprite(64, 68, L"data\\texture\\result\\equal.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Ikoru->SetName("Ikoru");
	Ikoru->SetPos(DirectX::SimpleMath::Vector3(150, 80, 0));	// 表示位置

	// ＊文字
	auto Kakeru1 = NEW Sprite(80, 80, L"data\\texture\\result\\peke.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Kakeru1->SetName("Kakeru1");
	Kakeru1->SetPos(DirectX::SimpleMath::Vector3(-215 + AAA, GOOD_SCORE_POSY, 0));	// 表示位置

	// ＊文字
	auto Kakeru2 = NEW Sprite(80, 80, L"data\\texture\\result\\peke.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Kakeru2->SetName("Kakeru2");
	Kakeru2->SetPos(DirectX::SimpleMath::Vector3(-215 + AAA, BAD_SCORE_POSY, 0));	// 表示位置

	// GoobScore文字
	auto Good_Score_Char = NEW Sprite(320, 142, L"data\\texture\\result\\good_r.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score_Char->SetName("Good_Score_Char");
	Good_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-440 + AAA, GOOD_SCORE_POSY, 0));	// 表示位置

	// BadScore文字
	auto Bad_Score_Char = NEW Sprite(320, 142, L"data\\texture\\result\\bad_r.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score_Char->SetName("Bad_Score_Char");
	Bad_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-440 + AAA, BAD_SCORE_POSY, 0));	// 表示位置


	// BestPhoto

	MeekH::TextureComponent::DestroyTexPool(L"z:\\WebCamera\\bestShot.jpg");
	auto BestPhoto = NEW Sprite(346, 260, L"z:\\WebCamera\\bestShot.jpg", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	BestPhoto->SetName("BestPhoto");
	BestPhoto->SetPos(DirectX::SimpleMath::Vector3(190 + AAA, BESTPHOTO_POSY, 0));	// 表示位置
	BestPhoto->SetColor(r, g, b, a);	// 色設定
	BestPhoto->SetPriority(3);			// 画像の優先順位

	// ランク文字
	auto Ranking_Char = NEW Sprite(426, 500, L"data\\texture\\ranking.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Ranking_Char->SetName("Ranking_Char");
	Ranking_Char->SetPos(DirectX::SimpleMath::Vector3(325 + AAA, RANKING_CHAR_POSY, -1));	// 表示位置
	Ranking_Char->SetColor(rr, gg, bb, aa);	// 色設定
	Ranking_Char->SetPriority(4);			// 画像の優先順位

	//========================================================================
	// 背景
	//========================================================================
	auto Back = NEW Sprite(1280, 720, L"data\\texture\\result\\resultwaku2.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Back->SetName("Back");
	Back->SetPos(DirectX::SimpleMath::Vector3(0, 0, 10));	// 表示位置
	//Back->SetPriority(1);





	DirectX::SimpleMath::Vector2 tex[4];
	float MainScore1, MainScore2, MainScore3, MainScore4, MainScore5,
		SabScore1, SabScore2, SabScore3, SabScore4, SabScore5,
		TotalScore1, TotalScore2, TotalScore3, TotalScore4, TotalScore5, TotalScore6,
		GoodScore1, GoodScore2,
		BadScore1, BadScore2,
		RankingChar;


	//========================================================================
	// MainScore
	//========================================================================
	MainScore1 = ((float)(m_nMainScore5 % 10) / 1);
	MainScore2 = ((float)(m_nMainScore4 % 10) / 1);
	MainScore3 = ((float)(m_nMainScore3 % 10) / 1);
	MainScore4 = ((float)(m_nMainScore2 % 10) / 1);
	MainScore5 = ((float)(m_nMainScore1 % 10) / 1);

	// 小数点にする計算
	MainScore1 *= 0.1f;
	MainScore2 *= 0.1f;
	MainScore3 *= 0.1f;
	MainScore4 *= 0.1f;
	MainScore5 *= 0.1f;

	// 横にズレル
	Main_Score1->AddTexCoordX((float)MainScore1);
	Main_Score2->AddTexCoordX((float)MainScore2);
	Main_Score3->AddTexCoordX((float)MainScore3);
	Main_Score4->AddTexCoordX((float)MainScore4);
	Main_Score5->AddTexCoordX((float)MainScore5);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score1->SetTexCoord(tex);

	// スコア表示位置

	int offset = 150;
	Main_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , MAIN_SCORE_POSY , 0 ) );	// 1桁目
	Main_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , MAIN_SCORE_POSY , 0 ) );	// 2桁目
	Main_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , MAIN_SCORE_POSY , 0 ) );	// 3桁目
	Main_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , MAIN_SCORE_POSY , 0 ) );	// 4桁目
	Main_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 +offset  ,MAIN_SCORE_POSY , 0 ) );	// 5桁目

	//========================================================================
	// SabScore
	//========================================================================
	SabScore1 = ((float)(m_nSabScore5 % 10) / 1);
	SabScore2 = ((float)(m_nSabScore4 % 10) / 1);
	SabScore3 = ((float)(m_nSabScore3 % 10) / 1);
	SabScore4 = ((float)(m_nSabScore2 % 10) / 1);
	SabScore5 = ((float)(m_nSabScore1 % 10) / 1);

	// 小数点にする計算
	SabScore1 *= 0.1f;
	SabScore2 *= 0.1f;
	SabScore3 *= 0.1f;
	SabScore4 *= 0.1f;
	SabScore5 *= 0.1f;

	// 横にズレル
	Sab_Score1->AddTexCoordX((float)SabScore1);
	Sab_Score2->AddTexCoordX((float)SabScore2);
	Sab_Score3->AddTexCoordX((float)SabScore3);
	Sab_Score4->AddTexCoordX((float)SabScore4);
	Sab_Score5->AddTexCoordX((float)SabScore5);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score1->SetTexCoord(tex);

	// スコア表示位置
	Sab_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 + offset , SAB_SCORE_POSY , 0 ) );





	//========================================================================
	// TotalScore
	//========================================================================
	TotalScore1 = ((float)(m_nTotalScore6 % 10) / 1);
	TotalScore2 = ((float)(m_nTotalScore5 % 10) / 1);
	TotalScore3 = ((float)(m_nTotalScore4 % 10) / 1);
	TotalScore4 = ((float)(m_nTotalScore3 % 10) / 1);
	TotalScore5 = ((float)(m_nTotalScore2 % 10) / 1);
	TotalScore6 = ((float)(m_nTotalScore1 % 10) / 1);

	// 小数点にする計算
	TotalScore1 *= 0.1f;
	TotalScore2 *= 0.1f;
	TotalScore3 *= 0.1f;
	TotalScore4 *= 0.1f;
	TotalScore5 *= 0.1f;
	TotalScore6 *= 0.1f;

	// 横にズレル
	Total_Score1->AddTexCoordX((float)TotalScore1);
	Total_Score2->AddTexCoordX((float)TotalScore2);
	Total_Score3->AddTexCoordX((float)TotalScore3);
	Total_Score4->AddTexCoordX((float)TotalScore4);
	Total_Score5->AddTexCoordX((float)TotalScore5);
	Total_Score6->AddTexCoordX((float)TotalScore6);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score6->SetTexCoord(tex);
	
	tex[0] = DirectX::SimpleMath::Vector2(TotalScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore6, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore6, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score1->SetTexCoord(tex);

	// スコア表示位置
	Total_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset + 15, TOTAL_SCORE_POSY , 0 ) );
	Total_Score2->SetPos(DirectX::SimpleMath::Vector3(40 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score3->SetPos(DirectX::SimpleMath::Vector3(0 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score4->SetPos(DirectX::SimpleMath::Vector3(-40 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score5->SetPos(DirectX::SimpleMath::Vector3(-80 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score6->SetPos(DirectX::SimpleMath::Vector3(-120 + offset + 15, TOTAL_SCORE_POSY, 0));





	//========================================================================
	// GoodScore
	//========================================================================
	GoodScore1 = ((float)(m_nGoodScoreBase % 10) / 1);
	GoodScore2 = ((float)(m_nGoodScoreBase % 10) / 1);

	// 小数点にする計算
	GoodScore1 *= 0.1f;
	GoodScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Good_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Good_Score1->SetTexCoord(tex);

	// スコア表示位置
	Good_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, GOOD_SCORE_POSY, 0));
	Good_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, GOOD_SCORE_POSY, 0));





	//========================================================================
	// BadScore
	//========================================================================
	BadScore1 = ((float)(m_nBadScoreBase % 10) / 1);
	BadScore2 = ((float)(m_nBadScoreBase % 10) / 1);

	// 小数点にする計算
	BadScore1 *= 0.1f;
	BadScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(BadScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Bad_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(BadScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Bad_Score1->SetTexCoord(tex);

	// スコア表示位置
	Bad_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, BAD_SCORE_POSY, 0));
	Bad_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, BAD_SCORE_POSY, 0));





	//========================================================================
	// ランク文字
	//========================================================================
	RankingChar = ((float)(m_nBadScoreBase % 10) / 1);

	// 小数点にする計算
	RankingChar *= 0.1f;

	// 横にズレル
	tex[0] = DirectX::SimpleMath::Vector2(RankingChar, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(RankingChar, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(RankingChar + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(RankingChar + 0.1f, 0.0f);
	// スコア画像分割
	//Ranking_Char->SetTexCoord(tex);





	AddChild(Back);
	AddChild(Purasu);
	AddChild(Ikoru);
	AddChild(Kakeru1);
	AddChild(Kakeru2);
	AddChild(Main_Score1);
	AddChild(Main_Score2);
	AddChild(Main_Score3);
	AddChild(Main_Score4);
	AddChild(Main_Score5);
	AddChild(Main_Score_Char);
	AddChild(Sab_Score1);
	AddChild(Sab_Score2);
	AddChild(Sab_Score3);
	AddChild(Sab_Score4);
	AddChild(Sab_Score5);
	AddChild(Sab_Score_Char);
	AddChild(Total_Score1);
	AddChild(Total_Score2);
	AddChild(Total_Score3);
	AddChild(Total_Score4);
	AddChild(Total_Score5);
	AddChild(Total_Score6);
	AddChild(Total_Score_Char);
	AddChild(Good_Score1);
	AddChild(Good_Score2);
	AddChild(Good_Score_Char);
	AddChild(Bad_Score1);
	AddChild(Bad_Score2);
	AddChild(Bad_Score_Char); 
	AddChild(Ranking_Char);
	AddChild(BestPhoto);
}


//=============================================================================
// 更新処理
//=============================================================================
void Result::Update(){
	Sprite *Back,
		*Main_Score1, *Main_Score2, *Main_Score3, *Main_Score4, *Main_Score5,
		*Sab_Score1, *Sab_Score2, *Sab_Score3, *Sab_Score4, *Sab_Score5,
		*Total_Score1, *Total_Score2, *Total_Score3, *Total_Score4, *Total_Score5, *Total_Score6,
		*Good_Score1, *Good_Score2,
		*Bad_Score1, *Bad_Score2,
		*Ranking_Char, *BestPhoto;

	Back = (Sprite*)GetChild("Back");

	Main_Score1 = (Sprite*)GetChild("Main_Score1");
	Main_Score2 = (Sprite*)GetChild("Main_Score2");
	Main_Score3 = (Sprite*)GetChild("Main_Score3");
	Main_Score4 = (Sprite*)GetChild("Main_Score4");
	Main_Score5 = (Sprite*)GetChild("Main_Score5");

	Sab_Score1 = (Sprite*)GetChild("Sab_Score1");
	Sab_Score2 = (Sprite*)GetChild("Sab_Score2");
	Sab_Score3 = (Sprite*)GetChild("Sab_Score3");
	Sab_Score4 = (Sprite*)GetChild("Sab_Score4");
	Sab_Score5 = (Sprite*)GetChild("Sab_Score5");

	Total_Score1 = (Sprite*)GetChild("Total_Score1");
	Total_Score2 = (Sprite*)GetChild("Total_Score2");
	Total_Score3 = (Sprite*)GetChild("Total_Score3");
	Total_Score4 = (Sprite*)GetChild("Total_Score4");
	Total_Score5 = (Sprite*)GetChild("Total_Score5");
	Total_Score6 = (Sprite*)GetChild("Total_Score6");

	Good_Score1 = (Sprite*)GetChild("Good_Score1");
	Good_Score2 = (Sprite*)GetChild("Good_Score2");

	Bad_Score1 = (Sprite*)GetChild("Bad_Score1");
	Bad_Score2 = (Sprite*)GetChild("Bad_Score2");

	Ranking_Char = (Sprite*)GetChild("Ranking_Char");
	BestPhoto = (Sprite*)GetChild("BestPhoto");


	DirectX::SimpleMath::Vector2 tex[4];
	float MainScore1, MainScore2, MainScore3, MainScore4, MainScore5,
		SabScore1, SabScore2, SabScore3, SabScore4, SabScore5,
		TotalScore1, TotalScore2, TotalScore3, TotalScore4, TotalScore5, TotalScore6,
		GoodScore1, GoodScore2,
		BadScore1, BadScore2,
		RankingChar;




	// Result内時間加算処理
	m_nTime++;
	


	//========================================================================
	// MainScore
	//========================================================================
	if (m_bMainScoreFlg[0] == true)
	{
		m_nMainScore1++;						// MainScoreの1桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore1 = m_nMainScoreBase;	// MainScoreを代入
			m_nMainScore1 /= 1;					// MainScoreの1桁目を取りだす
			m_bMainScoreFlg[0] = false;			// 現在の桁終了フラグ
			m_bMainScoreFlg[1] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[1] == true)
	{
		m_nMainScore2++;						// MainScoreの2桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore2 = m_nMainScoreBase;	// MainScoreを代入
			m_nMainScore2 /= 10;				// MainScoreの2桁目を取りだす
			m_bMainScoreFlg[1] = false;			// 現在の桁終了フラグ
			m_bMainScoreFlg[2] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[2] == true)
	{
		m_nMainScore3++;						// MainScoreの3桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore3 = m_nMainScoreBase;	// MainScoreを代入
			m_nMainScore3 /= 100;				// MainScoreの3桁目を取りだす
			m_bMainScoreFlg[2] = false;			// 現在の桁終了フラグ
			m_bMainScoreFlg[3] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[3] == true)
	{
		m_nMainScore4++;						// MainScoreの4桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore4 = m_nMainScoreBase;	// MainScoreを代入
			m_nMainScore4 /= 1000;				// MainScoreの4桁目を取りだす
			m_bMainScoreFlg[3] = false;			// 現在の桁終了フラグ
			m_bMainScoreFlg[4] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[4] == true)
	{
		m_nMainScore5++;						// MainScoreの5桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore5 = m_nMainScoreBase;	// MainScoreを代入
			m_nMainScore5 /= 10000;				// MainScoreの5桁目を取りだす
			m_bMainScoreFlg[4] = false;			// MainScore終了フラグ
			m_bSabScoreFlg[0] = true;			// SabScore開始フラグ
			m_nTime = 0;
		}
	}

	MainScore1 = ((float)(m_nMainScore5 % 10) / 1);
	MainScore2 = ((float)(m_nMainScore4 % 10) / 1);
	MainScore3 = ((float)(m_nMainScore3 % 10) / 1);
	MainScore4 = ((float)(m_nMainScore2 % 10) / 1);
	MainScore5 = ((float)(m_nMainScore1 % 10) / 1);

	// 小数点にする計算
	MainScore1 *= 0.1f;
	MainScore2 *= 0.1f;
	MainScore3 *= 0.1f;
	MainScore4 *= 0.1f;
	MainScore5 *= 0.1f;

	// 横にズレル
	Main_Score1->AddTexCoordX((float)MainScore1);
	Main_Score2->AddTexCoordX((float)MainScore2);
	Main_Score3->AddTexCoordX((float)MainScore3);
	Main_Score4->AddTexCoordX((float)MainScore4);
	Main_Score5->AddTexCoordX((float)MainScore5);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Main_Score1->SetTexCoord(tex);

	// スコア表示位置
	int offset = 150;
	Main_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , MAIN_SCORE_POSY , 0 ) );	// 1桁目
	Main_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , MAIN_SCORE_POSY , 0 ) );	// 2桁目
	Main_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , MAIN_SCORE_POSY , 0 ) );	// 3桁目
	Main_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , MAIN_SCORE_POSY , 0 ) );	// 4桁目
	Main_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 + offset , MAIN_SCORE_POSY , 0 ) );	// 5桁目





	//========================================================================
	// SabScore
	//========================================================================
	if (m_bSabScoreFlg[0] == true)
	{
		m_nSabScore1++;						// SabScoreの1桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore1 = m_nSabScoreBase;	// SabScoreを代入
			m_nSabScore1 /= 1;				// SabScoreの1桁目を取りだす
			m_bSabScoreFlg[0] = false;		// 現在の桁終了フラグ
			m_bSabScoreFlg[1] = true;		// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[1] == true)
	{
		m_nSabScore2++;						// SabScore2桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore2 = m_nSabScoreBase;	// SabScoreを代入
			m_nSabScore2 /= 10;				// SabScore2桁目を取りだす
			m_bSabScoreFlg[1] = false;		// 現在の桁終了フラグ
			m_bSabScoreFlg[2] = true;		// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[2] == true)
	{
		m_nSabScore3++;						// SabScoreの3桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore3 = m_nSabScoreBase;	// SabScoreを代入
			m_nSabScore3 /= 100;			// SabScoreの3桁目を取りだす
			m_bSabScoreFlg[2] = false;		// 現在の桁終了フラグ
			m_bSabScoreFlg[3] = true;		// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[3] == true)
	{
		m_nSabScore4++;						// SabScoreの4桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore4 = m_nSabScoreBase;	// SabScoreを代入
			m_nSabScore4 /= 1000;			// SabScoreの4桁目を取りだす
			m_bSabScoreFlg[3] = false;		// 現在の桁終了フラグ
			m_bSabScoreFlg[4] = true;		// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[4] == true)
	{
		m_nSabScore5++;						// SabScoreの5桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore5 = m_nSabScoreBase;	// SabScoreを代入
			m_nSabScore5 /= 10000;			// SabScoreの5桁目を取りだす
			m_bSabScoreFlg[4] = false;		// SabScore終了フラグ
			m_bTotalScoreFlg[0] = true;		// TotalScore開始フラグ
			m_nTime = 0;
		}
	}

	SabScore1 = ((float)(m_nSabScore5 % 10) / 1);
	SabScore2 = ((float)(m_nSabScore4 % 10) / 1);
	SabScore3 = ((float)(m_nSabScore3 % 10) / 1);
	SabScore4 = ((float)(m_nSabScore2 % 10) / 1);
	SabScore5 = ((float)(m_nSabScore1 % 10) / 1);

	// 小数点にする計算
	SabScore1 *= 0.1f;
	SabScore2 *= 0.1f;
	SabScore3 *= 0.1f;
	SabScore4 *= 0.1f;
	SabScore5 *= 0.1f;

	// 横にズレル
	Sab_Score1->AddTexCoordX((float)SabScore1);
	Sab_Score2->AddTexCoordX((float)SabScore2);
	Sab_Score3->AddTexCoordX((float)SabScore3);
	Sab_Score4->AddTexCoordX((float)SabScore4);
	Sab_Score5->AddTexCoordX((float)SabScore5);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Sab_Score1->SetTexCoord(tex);

	// スコア表示位置
	Sab_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 + offset , SAB_SCORE_POSY , 0 ) );





	//========================================================================
	// TotalScoreの計算
	//========================================================================
	m_nTotalScoreBase = m_nMainScoreBase + m_nSabScoreBase;

	SharedData::SetData(21, &m_nTotalScoreBase);

	//========================================================================
	// TotalScore
	//========================================================================
	if (m_bTotalScoreFlg[0] == true)
	{
		m_nTotalScore1++;						// TotalScoreの1桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore1 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore1 /= 1;				// TotalScoreの1桁目を取りだす
			m_bTotalScoreFlg[0] = false;		// 現在の桁終了フラグ
			m_bTotalScoreFlg[1] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[1] == true)
	{
		m_nTotalScore2++;						// TotalScoreの2桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore2 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore2 /= 10;				// TotalScoreの2桁目を取りだす
			m_bTotalScoreFlg[1] = false;		// 現在の桁終了フラグ
			m_bTotalScoreFlg[2] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[2] == true)
	{
		m_nTotalScore3++;						// TotalScoreの3桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore3 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore3 /= 100;				// TotalScoreの3桁目を取りだす
			m_bTotalScoreFlg[2] = false;		// 現在の桁終了フラグ
			m_bTotalScoreFlg[3] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[3] == true)
	{
		m_nTotalScore4++;						// TotalScoreの4桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore4 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore4 /= 1000;				// TotalScoreの4桁目を取りだす
			m_bTotalScoreFlg[3] = false;		// 現在の桁終了フラグ
			m_bTotalScoreFlg[4] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[4] == true)
	{
		m_nTotalScore5++;						// TotalScoreの5桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore5 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore5 /= 10000;			// TotalScoreの5桁目を取りだす
			m_bTotalScoreFlg[4] = false;		// 現在の桁終了フラグ
			m_bTotalScoreFlg[5] = true;			// 次の桁開始フラグ
			m_nTime = 0;
		}
	}

	if (m_bTotalScoreFlg[5] == true)
	{
		m_nTotalScore6++;						// TotalScoreの6桁目を回転させる処理

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore6 = m_nTotalScoreBase;	// TotalScoreを代入
			m_nTotalScore6 /= 100000;			// TotalScoreの6桁目を取りだす
			m_bTotalScoreFlg[5] = false;		// TotalScore終了フラグ
			m_bGoodScoreFlg = true;				// GoodScore開始フラグ
			m_nTime = 0;
		}
	}

	TotalScore1 = ((float)(m_nTotalScore6 % 10) / 1);
	TotalScore2 = ((float)(m_nTotalScore5 % 10) / 1);
	TotalScore3 = ((float)(m_nTotalScore4 % 10) / 1);
	TotalScore4 = ((float)(m_nTotalScore3 % 10) / 1);
	TotalScore5 = ((float)(m_nTotalScore2 % 10) / 1);
	TotalScore6 = ((float)(m_nTotalScore1 % 10) / 1);

	// 小数点にする計算
	TotalScore1 *= 0.1f;
	TotalScore2 *= 0.1f;
	TotalScore3 *= 0.1f;
	TotalScore4 *= 0.1f;
	TotalScore5 *= 0.1f;
	TotalScore6 *= 0.1f;

	// 横にズレル
	Total_Score1->AddTexCoordX((float)TotalScore1);
	Total_Score2->AddTexCoordX((float)TotalScore2);
	Total_Score3->AddTexCoordX((float)TotalScore3);
	Total_Score4->AddTexCoordX((float)TotalScore4);
	Total_Score5->AddTexCoordX((float)TotalScore5);
	Total_Score6->AddTexCoordX((float)TotalScore6);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score6->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 0.0f);
	// スコア画像分割4
	Total_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore6, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore6, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 0.0f);
	// スコア画像分割
	Total_Score1->SetTexCoord(tex);

	// スコア表示位置
	Total_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset + 15 , TOTAL_SCORE_POSY , 0 ) );
	Total_Score2->SetPos(DirectX::SimpleMath::Vector3(40 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score3->SetPos(DirectX::SimpleMath::Vector3(0 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score4->SetPos(DirectX::SimpleMath::Vector3(-40 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score5->SetPos(DirectX::SimpleMath::Vector3(-80 + offset + 15, TOTAL_SCORE_POSY, 0));
	Total_Score6->SetPos(DirectX::SimpleMath::Vector3(-120 + offset + 15, TOTAL_SCORE_POSY, 0));





	//========================================================================
	// GoodScore
	//========================================================================
	if (m_bGoodScoreFlg == true)
	{

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nGoodScore1 = m_nGoodScoreBase;	// GoodScoreを代入
			m_nGoodScore1 /= 1;					// GoodScoreの1桁目を取りだす

			m_nGoodScore2 = m_nGoodScoreBase;	// GoodScoreを代入
			m_nGoodScore2 /= 10;				// GoodScoreの2桁目を取りだす

			m_bGoodScoreFlg = false;			// GoodScore終了フラグ
			m_bBadScoreFlg = true;				// BadScore開始フラグ

			m_nTime = 0;
		}
	}

	GoodScore1 = ((float)(m_nGoodScore2 % 10) / 1);
	GoodScore2 = ((float)(m_nGoodScore1 % 10) / 1);

	// 小数点にする計算
	GoodScore1 *= 0.1f;
	GoodScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Good_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Good_Score1->SetTexCoord(tex);

	// スコア表示位置
	Good_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, GOOD_SCORE_POSY, 0));
	Good_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, GOOD_SCORE_POSY, 0));





	//========================================================================
	// BadScore
	//========================================================================
	if (m_bBadScoreFlg == true)
	{

		// CNT_TIME時間経過したら処理
		if (m_nTime >= CNT_TIME)
		{
			m_nBadScore2 = m_nBadScoreBase;	// BadScoreを代入
			m_nBadScore2 /= 1;				// BadScoreの1桁目を取りだす

			m_nBadScore1 = m_nBadScoreBase;	// BadScoreを代入
			m_nBadScore1 /= 10;				// BadScoreの2桁目を取りだす

			m_bBadScoreFlg = false;			// BadScore終了フラグ
			m_bBestPhotoFlg = true;			// BestPhoto開始フラグ

			m_nTime = 0;
		}
	}

	BadScore1 = ((float)(m_nBadScore1 % 10) / 1);
	BadScore2 = ((float)(m_nBadScore2 % 10) / 1);

	// 小数点にする計算
	BadScore1 *= 0.1f;
	BadScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(BadScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 0.0f);
	// スコア画像分割
	Bad_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(BadScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 0.0f);
	// スコア画像分割
	Bad_Score1->SetTexCoord(tex);

	// スコア表示位置
	Bad_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, BAD_SCORE_POSY, 0));
	Bad_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, BAD_SCORE_POSY, 0));





	//========================================================================
	// BestPhoto
	//========================================================================
	if (m_bBestPhotoFlg == true)
	{
		// BestPhotoが徐々に浮かび上がる
		a += 0.005f;

		// BestPhotoがクッキリ見えるまで処理
		if (a <= 1.0f)
		{
			BestPhoto->SetColor(r, g, b, a);
		}
		else
		{
			m_bBestPhotoFlg = false;			// BestPhoto終了フラグ
			m_bRankingCharFlg = true;			// RankingChar開始フラグ
		}
	}





	//========================================================================
	// ランク文字
	//========================================================================
	if (m_bRankingCharFlg == true)
	{
		// ランク判定S
		if (m_nTotalScoreBase >= RANKIN_SCORE_S)
		{
			m_nRankingChar1 = 8;
			Ranking_Char->SetTexture( L"data\\texture\\result\\S.png" );
		}
		// ランク判定A
		else if (m_nTotalScoreBase >= RANKIN_SCORE_A)
		{
			m_nRankingChar1 = 6;
			Ranking_Char->SetTexture( L"data\\texture\\result\\A.png" );
		}
		// ランク判定B
		else if (m_nTotalScoreBase >= RANKIN_SCORE_B)
		{
			m_nRankingChar1 = 4;
			Ranking_Char->SetTexture( L"data\\texture\\result\\B.png" );
		}
		// ランク判定C
		else if (m_nTotalScoreBase >= RANKIN_SCORE_C)
		{
			m_nRankingChar1 = 2;
			Ranking_Char->SetTexture( L"data\\texture\\result\\C.png" );
		}
		// ランク判定D
		else if (m_nTotalScoreBase >= RANKIN_SCORE_D)
		{
			m_nRankingChar1 = 0;
			Ranking_Char->SetTexture( L"data\\texture\\result\\D.png" );
		}
		// ランク判定D
		else
		{
			m_nRankingChar1 = 0;
			Ranking_Char->SetTexture( L"data\\texture\\result\\D.png" );

		}


		m_nRankingChar1 /= 1;				// RankingCharの1桁目を取りだす

		RankingChar = ((float)(m_nRankingChar1 % 10) / 1);

		// 小数点にする計算
		RankingChar *= 0.1f;

		tex[0] = DirectX::SimpleMath::Vector2(RankingChar, 1.0f);
		tex[1] = DirectX::SimpleMath::Vector2(RankingChar, 0.0f);
		tex[2] = DirectX::SimpleMath::Vector2(RankingChar + 0.2f, 1.0f);
		tex[3] = DirectX::SimpleMath::Vector2(RankingChar + 0.2f, 0.0f);
		// スコア画像分割
		//Ranking_Char->SetTexCoord(tex);

		// ランクが徐々に浮かび上がる
		aa += 0.0185f;

		// ランクのアルファー値調整
		if (aa <= 1.0f)
		{
			Ranking_Char->SetColor(rr, gg, bb, aa);
		}

		// ランク文字が一定の大きさまで処理
		if (m_scl->x >= -0.025f)
		{
			// 少しずつランク文字が縮小
			m_scl->x -= 0.0005f;
			m_scl->y -= 0.0005f;

			Ranking_Char->AddScale(DirectX::SimpleMath::Vector3(m_scl->x, m_scl->y, 1.0f));
		}
		// ランク文字が一定以上の大きさになったら処理
		else
		{
			aa = 1.0f;							// ランク文字をクッキリ表示
			Ranking_Char->SetColor(rr, gg, bb, aa);
			m_bRankingCharFlg = false;			// bRankingChar終了フラグ
		}

	}
}


//=============================================================================
// MainScoreを渡す処理
//=============================================================================
int Result::GetMainScore(void)
{
	return m_nMainScoreBase;
}
//=============================================================================
// MainScore加算処理
//=============================================================================
void Result::SetMainScore(int score)
{
	m_nMainScoreBase += score;
}

//=============================================================================
// SabScoreを渡す処理
//=============================================================================
int Result::GetSabScore(void)
{
	return m_nSabScoreBase;
}
//=============================================================================
// SabScore加算処理
//=============================================================================
void Result::SetSabScore(int score)
{
	m_nSabScoreBase += score;
}

//=============================================================================
// TotalScoreを渡す処理
//=============================================================================
int Result::GetTotalScore(void)
{
	return m_nTotalScoreBase;
}
//=============================================================================
// TotalScore加算処理
//=============================================================================
void Result::SetTotalScore(int score)
{
	m_nTotalScoreBase += score;
}

//=============================================================================
// GoodScoreを渡す処理
//=============================================================================
int Result::GetGoodScore(void)
{
	return m_nGoodScoreBase;
}
//=============================================================================
// GoodScore加算処理
//=============================================================================
void Result::SetGoodScore(int score)
{
	m_nGoodScoreBase = score;
}

//=============================================================================
// BadScoreを渡す処理
//=============================================================================
int Result::GetBadScore(void)
{
	return m_nBadScoreBase;
}
//=============================================================================
// BadScore加算処理
//=============================================================================
void Result::SetBadScore(int score)
{
	m_nBadScoreBase = score;
}