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

#define CNT_TIME (30)				// �X�R�A��]����
#define RANKIN_SCORE_S (5000)		// �X�R�A5000�_�ȏ��S�����N����
#define RANKIN_SCORE_A (4000)		// �X�R�A4000�_�ȏ��A�����N����
#define RANKIN_SCORE_B (3000)		// �X�R�A3000�_�ȏ��B�����N����
#define RANKIN_SCORE_C (2000)		// �X�R�A2000�_�ȏ��C�����N����
#define RANKIN_SCORE_D (1000)		// �X�R�A1000�_�ȏ��D�����N����
#define MAIN_SCORE_POSY (260)		// MainScore�\���ʒuY
#define SAB_SCORE_POSY (140)		// SabScore�\���ʒuY
#define TOTAL_SCORE_POSY (25)		// TotalScore�\���ʒuY
#define GOOD_SCORE_POSY	(-130)		// GoodScore�\���ʒuY
#define BAD_SCORE_POSY (-250)		// BadScore�\���ʒuY
#define RANKING_CHAR_POSY (-75)		// �����N�����\���ʒuY
#define BESTPHOTO_POSY (-180)		// BestPhoto�\���ʒuY
#define SIZEX (40)					// �X�R�A�傫��X
#define SIZEY (40)					// �X�R�A�傫��Y
#define MAIN_SCORE_MAX (99999)		// MainScore���
#define SAB_SCORE_MAX (99999)		// SabScore���
#define TOTAL_SCORE_MAX (99999)		// TotalScore���
#define GOOD_SCORE_MAX (99)			// GoodScore���
#define BAD_SCORE_MAX (99)			// BadScore���
#define AAA (100)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Result::Result(){
	m_pos = NEW DirectX::SimpleMath::Vector3;
	m_rot = NEW DirectX::SimpleMath::Vector3;
	m_scl = NEW DirectX::SimpleMath::Vector3;

	m_nTime = 0;				// Result������

	m_nMainScoreBase = 0;		// MainScore�̒l������
	m_nMainScore1 = 0;			// MainScore��1����
	m_nMainScore2 = 0;			// MainScore��2����
	m_nMainScore3 = 0;			// MainScore��3����
	m_nMainScore4 = 0;			// MainScore��4����
	m_nMainScore5 = 0;			// MainScore��5����

	m_nSabScoreBase = 0;		// SabScore�̒l������
	m_nSabScore1 = 0;			// SabScore��1����
	m_nSabScore2 = 0;			// SabScore��2����
	m_nSabScore3 = 0;			// SabScore��3����
	m_nSabScore4 = 0;			// SabScore��4����
	m_nSabScore5 = 0;			// SabScore��5����

	m_nTotalScoreBase = 0;		// TotalScore�̒l������
	m_nTotalScore1 = 0;			// TotalScore��1����
	m_nTotalScore2 = 0;			// TotalScore��2����
	m_nTotalScore3 = 0;			// TotalScore��3����
	m_nTotalScore4 = 0;			// TotalScore��4����
	m_nTotalScore5 = 0;			// TotalScore��5����
	m_nTotalScore6 = 0;			// TotalScore��6����

	m_nGoodScoreBase = 0;		// GoodScore�̒l������
	m_nGoodScore1 = 0;			// GoodScore��1����
	m_nGoodScore2 = 0;			// GoodScore��2����

	m_nBadScoreBase = 0;		// BadScore�̒l������
	m_nBadScore1 = 0;			// BadScore��1����
	m_nBadScore2 = 0;			// BadScore��2����

	m_nRankingChar = 0;			// �����N�̒l������
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
// �f�X�g���N�^
//=============================================================================
Result::~Result(){
}


//=============================================================================
// ����������
//=============================================================================
void Result::Init(){
	//========================================================================
	// ���l
	//========================================================================
	// MainScore���l
	auto Main_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 1����
	Main_Score1->SetName("Main_Score1");
	auto Main_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 2����
	Main_Score2->SetName("Main_Score2");						 
	auto Main_Score3 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 3����
	Main_Score3->SetName("Main_Score3");						 
	auto Main_Score4 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 4����
	Main_Score4->SetName("Main_Score4");
	auto Main_Score5 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");	// 5����
	Main_Score5->SetName("Main_Score5");

	// SabScore���l
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

	// TotalScore���l
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

	// Good���l
	auto Good_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score1->SetName("Good_Score1");
	auto Good_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score2->SetName("Good_Score2");

	// Bad���l
	auto Bad_Score1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score1->SetName("Bad_Score1");
	auto Bad_Score2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\result\\r_nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score2->SetName("Bad_Score2");





	//========================================================================
	// ����
	//========================================================================
	// MainScore����
	auto Main_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\main.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Main_Score_Char->SetName("Main_Score_Char");
	Main_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, MAIN_SCORE_POSY, 0));	// �\���ʒu

	// SabScore����
	auto Sab_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\sub.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Sab_Score_Char->SetName("Sab_Score_Char");
	Sab_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, SAB_SCORE_POSY, 0));	// �\���ʒu

	// TotalScore����
	auto Total_Score_Char = NEW Sprite(400, 73, L"data\\texture\\result\\total.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Total_Score_Char->SetName("Total_Score_Char");
	Total_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-370 + AAA, TOTAL_SCORE_POSY, 0));	// �\���ʒu

	// �{����
	auto Purasu = NEW Sprite(64, 68, L"data\\texture\\result\\plus.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Purasu->SetName("Purasu");
	Purasu->SetPos(DirectX::SimpleMath::Vector3(150, 200, 0));	// �\���ʒu
	
	// ������
	auto Ikoru = NEW Sprite(64, 68, L"data\\texture\\result\\equal.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Ikoru->SetName("Ikoru");
	Ikoru->SetPos(DirectX::SimpleMath::Vector3(150, 80, 0));	// �\���ʒu

	// ������
	auto Kakeru1 = NEW Sprite(80, 80, L"data\\texture\\result\\peke.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Kakeru1->SetName("Kakeru1");
	Kakeru1->SetPos(DirectX::SimpleMath::Vector3(-215 + AAA, GOOD_SCORE_POSY, 0));	// �\���ʒu

	// ������
	auto Kakeru2 = NEW Sprite(80, 80, L"data\\texture\\result\\peke.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Kakeru2->SetName("Kakeru2");
	Kakeru2->SetPos(DirectX::SimpleMath::Vector3(-215 + AAA, BAD_SCORE_POSY, 0));	// �\���ʒu

	// GoobScore����
	auto Good_Score_Char = NEW Sprite(320, 142, L"data\\texture\\result\\good_r.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Good_Score_Char->SetName("Good_Score_Char");
	Good_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-440 + AAA, GOOD_SCORE_POSY, 0));	// �\���ʒu

	// BadScore����
	auto Bad_Score_Char = NEW Sprite(320, 142, L"data\\texture\\result\\bad_r.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Bad_Score_Char->SetName("Bad_Score_Char");
	Bad_Score_Char->SetPos(DirectX::SimpleMath::Vector3(-440 + AAA, BAD_SCORE_POSY, 0));	// �\���ʒu


	// BestPhoto

	MeekH::TextureComponent::DestroyTexPool(L"z:\\WebCamera\\bestShot.jpg");
	auto BestPhoto = NEW Sprite(346, 260, L"z:\\WebCamera\\bestShot.jpg", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	BestPhoto->SetName("BestPhoto");
	BestPhoto->SetPos(DirectX::SimpleMath::Vector3(190 + AAA, BESTPHOTO_POSY, 0));	// �\���ʒu
	BestPhoto->SetColor(r, g, b, a);	// �F�ݒ�
	BestPhoto->SetPriority(3);			// �摜�̗D�揇��

	// �����N����
	auto Ranking_Char = NEW Sprite(426, 500, L"data\\texture\\ranking.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Ranking_Char->SetName("Ranking_Char");
	Ranking_Char->SetPos(DirectX::SimpleMath::Vector3(325 + AAA, RANKING_CHAR_POSY, -1));	// �\���ʒu
	Ranking_Char->SetColor(rr, gg, bb, aa);	// �F�ݒ�
	Ranking_Char->SetPriority(4);			// �摜�̗D�揇��

	//========================================================================
	// �w�i
	//========================================================================
	auto Back = NEW Sprite(1280, 720, L"data\\texture\\result\\resultwaku2.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Back->SetName("Back");
	Back->SetPos(DirectX::SimpleMath::Vector3(0, 0, 10));	// �\���ʒu
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

	// �����_�ɂ���v�Z
	MainScore1 *= 0.1f;
	MainScore2 *= 0.1f;
	MainScore3 *= 0.1f;
	MainScore4 *= 0.1f;
	MainScore5 *= 0.1f;

	// ���ɃY����
	Main_Score1->AddTexCoordX((float)MainScore1);
	Main_Score2->AddTexCoordX((float)MainScore2);
	Main_Score3->AddTexCoordX((float)MainScore3);
	Main_Score4->AddTexCoordX((float)MainScore4);
	Main_Score5->AddTexCoordX((float)MainScore5);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu

	int offset = 150;
	Main_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , MAIN_SCORE_POSY , 0 ) );	// 1����
	Main_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , MAIN_SCORE_POSY , 0 ) );	// 2����
	Main_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , MAIN_SCORE_POSY , 0 ) );	// 3����
	Main_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , MAIN_SCORE_POSY , 0 ) );	// 4����
	Main_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 +offset  ,MAIN_SCORE_POSY , 0 ) );	// 5����

	//========================================================================
	// SabScore
	//========================================================================
	SabScore1 = ((float)(m_nSabScore5 % 10) / 1);
	SabScore2 = ((float)(m_nSabScore4 % 10) / 1);
	SabScore3 = ((float)(m_nSabScore3 % 10) / 1);
	SabScore4 = ((float)(m_nSabScore2 % 10) / 1);
	SabScore5 = ((float)(m_nSabScore1 % 10) / 1);

	// �����_�ɂ���v�Z
	SabScore1 *= 0.1f;
	SabScore2 *= 0.1f;
	SabScore3 *= 0.1f;
	SabScore4 *= 0.1f;
	SabScore5 *= 0.1f;

	// ���ɃY����
	Sab_Score1->AddTexCoordX((float)SabScore1);
	Sab_Score2->AddTexCoordX((float)SabScore2);
	Sab_Score3->AddTexCoordX((float)SabScore3);
	Sab_Score4->AddTexCoordX((float)SabScore4);
	Sab_Score5->AddTexCoordX((float)SabScore5);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
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

	// �����_�ɂ���v�Z
	TotalScore1 *= 0.1f;
	TotalScore2 *= 0.1f;
	TotalScore3 *= 0.1f;
	TotalScore4 *= 0.1f;
	TotalScore5 *= 0.1f;
	TotalScore6 *= 0.1f;

	// ���ɃY����
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
	// �X�R�A�摜����
	Total_Score6->SetTexCoord(tex);
	
	tex[0] = DirectX::SimpleMath::Vector2(TotalScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore6, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore6, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
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

	// �����_�ɂ���v�Z
	GoodScore1 *= 0.1f;
	GoodScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Good_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Good_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Good_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, GOOD_SCORE_POSY, 0));
	Good_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, GOOD_SCORE_POSY, 0));





	//========================================================================
	// BadScore
	//========================================================================
	BadScore1 = ((float)(m_nBadScoreBase % 10) / 1);
	BadScore2 = ((float)(m_nBadScoreBase % 10) / 1);

	// �����_�ɂ���v�Z
	BadScore1 *= 0.1f;
	BadScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(BadScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Bad_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(BadScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Bad_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Bad_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, BAD_SCORE_POSY, 0));
	Bad_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, BAD_SCORE_POSY, 0));





	//========================================================================
	// �����N����
	//========================================================================
	RankingChar = ((float)(m_nBadScoreBase % 10) / 1);

	// �����_�ɂ���v�Z
	RankingChar *= 0.1f;

	// ���ɃY����
	tex[0] = DirectX::SimpleMath::Vector2(RankingChar, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(RankingChar, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(RankingChar + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(RankingChar + 0.1f, 0.0f);
	// �X�R�A�摜����
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
// �X�V����
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




	// Result�����ԉ��Z����
	m_nTime++;
	


	//========================================================================
	// MainScore
	//========================================================================
	if (m_bMainScoreFlg[0] == true)
	{
		m_nMainScore1++;						// MainScore��1���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore1 = m_nMainScoreBase;	// MainScore����
			m_nMainScore1 /= 1;					// MainScore��1���ڂ���肾��
			m_bMainScoreFlg[0] = false;			// ���݂̌��I���t���O
			m_bMainScoreFlg[1] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[1] == true)
	{
		m_nMainScore2++;						// MainScore��2���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore2 = m_nMainScoreBase;	// MainScore����
			m_nMainScore2 /= 10;				// MainScore��2���ڂ���肾��
			m_bMainScoreFlg[1] = false;			// ���݂̌��I���t���O
			m_bMainScoreFlg[2] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[2] == true)
	{
		m_nMainScore3++;						// MainScore��3���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore3 = m_nMainScoreBase;	// MainScore����
			m_nMainScore3 /= 100;				// MainScore��3���ڂ���肾��
			m_bMainScoreFlg[2] = false;			// ���݂̌��I���t���O
			m_bMainScoreFlg[3] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[3] == true)
	{
		m_nMainScore4++;						// MainScore��4���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore4 = m_nMainScoreBase;	// MainScore����
			m_nMainScore4 /= 1000;				// MainScore��4���ڂ���肾��
			m_bMainScoreFlg[3] = false;			// ���݂̌��I���t���O
			m_bMainScoreFlg[4] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bMainScoreFlg[4] == true)
	{
		m_nMainScore5++;						// MainScore��5���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nMainScore5 = m_nMainScoreBase;	// MainScore����
			m_nMainScore5 /= 10000;				// MainScore��5���ڂ���肾��
			m_bMainScoreFlg[4] = false;			// MainScore�I���t���O
			m_bSabScoreFlg[0] = true;			// SabScore�J�n�t���O
			m_nTime = 0;
		}
	}

	MainScore1 = ((float)(m_nMainScore5 % 10) / 1);
	MainScore2 = ((float)(m_nMainScore4 % 10) / 1);
	MainScore3 = ((float)(m_nMainScore3 % 10) / 1);
	MainScore4 = ((float)(m_nMainScore2 % 10) / 1);
	MainScore5 = ((float)(m_nMainScore1 % 10) / 1);

	// �����_�ɂ���v�Z
	MainScore1 *= 0.1f;
	MainScore2 *= 0.1f;
	MainScore3 *= 0.1f;
	MainScore4 *= 0.1f;
	MainScore5 *= 0.1f;

	// ���ɃY����
	Main_Score1->AddTexCoordX((float)MainScore1);
	Main_Score2->AddTexCoordX((float)MainScore2);
	Main_Score3->AddTexCoordX((float)MainScore3);
	Main_Score4->AddTexCoordX((float)MainScore4);
	Main_Score5->AddTexCoordX((float)MainScore5);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(MainScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(MainScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(MainScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Main_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	int offset = 150;
	Main_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , MAIN_SCORE_POSY , 0 ) );	// 1����
	Main_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , MAIN_SCORE_POSY , 0 ) );	// 2����
	Main_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , MAIN_SCORE_POSY , 0 ) );	// 3����
	Main_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , MAIN_SCORE_POSY , 0 ) );	// 4����
	Main_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 + offset , MAIN_SCORE_POSY , 0 ) );	// 5����





	//========================================================================
	// SabScore
	//========================================================================
	if (m_bSabScoreFlg[0] == true)
	{
		m_nSabScore1++;						// SabScore��1���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore1 = m_nSabScoreBase;	// SabScore����
			m_nSabScore1 /= 1;				// SabScore��1���ڂ���肾��
			m_bSabScoreFlg[0] = false;		// ���݂̌��I���t���O
			m_bSabScoreFlg[1] = true;		// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[1] == true)
	{
		m_nSabScore2++;						// SabScore2���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore2 = m_nSabScoreBase;	// SabScore����
			m_nSabScore2 /= 10;				// SabScore2���ڂ���肾��
			m_bSabScoreFlg[1] = false;		// ���݂̌��I���t���O
			m_bSabScoreFlg[2] = true;		// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[2] == true)
	{
		m_nSabScore3++;						// SabScore��3���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore3 = m_nSabScoreBase;	// SabScore����
			m_nSabScore3 /= 100;			// SabScore��3���ڂ���肾��
			m_bSabScoreFlg[2] = false;		// ���݂̌��I���t���O
			m_bSabScoreFlg[3] = true;		// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[3] == true)
	{
		m_nSabScore4++;						// SabScore��4���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore4 = m_nSabScoreBase;	// SabScore����
			m_nSabScore4 /= 1000;			// SabScore��4���ڂ���肾��
			m_bSabScoreFlg[3] = false;		// ���݂̌��I���t���O
			m_bSabScoreFlg[4] = true;		// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bSabScoreFlg[4] == true)
	{
		m_nSabScore5++;						// SabScore��5���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nSabScore5 = m_nSabScoreBase;	// SabScore����
			m_nSabScore5 /= 10000;			// SabScore��5���ڂ���肾��
			m_bSabScoreFlg[4] = false;		// SabScore�I���t���O
			m_bTotalScoreFlg[0] = true;		// TotalScore�J�n�t���O
			m_nTime = 0;
		}
	}

	SabScore1 = ((float)(m_nSabScore5 % 10) / 1);
	SabScore2 = ((float)(m_nSabScore4 % 10) / 1);
	SabScore3 = ((float)(m_nSabScore3 % 10) / 1);
	SabScore4 = ((float)(m_nSabScore2 % 10) / 1);
	SabScore5 = ((float)(m_nSabScore1 % 10) / 1);

	// �����_�ɂ���v�Z
	SabScore1 *= 0.1f;
	SabScore2 *= 0.1f;
	SabScore3 *= 0.1f;
	SabScore4 *= 0.1f;
	SabScore5 *= 0.1f;

	// ���ɃY����
	Sab_Score1->AddTexCoordX((float)SabScore1);
	Sab_Score2->AddTexCoordX((float)SabScore2);
	Sab_Score3->AddTexCoordX((float)SabScore3);
	Sab_Score4->AddTexCoordX((float)SabScore4);
	Sab_Score5->AddTexCoordX((float)SabScore5);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(SabScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(SabScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(SabScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Sab_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Sab_Score1->SetPos( DirectX::SimpleMath::Vector3( 80 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score2->SetPos( DirectX::SimpleMath::Vector3( 40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score3->SetPos( DirectX::SimpleMath::Vector3( 0 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score4->SetPos( DirectX::SimpleMath::Vector3( -40 + offset , SAB_SCORE_POSY , 0 ) );
	Sab_Score5->SetPos( DirectX::SimpleMath::Vector3( -80 + offset , SAB_SCORE_POSY , 0 ) );





	//========================================================================
	// TotalScore�̌v�Z
	//========================================================================
	m_nTotalScoreBase = m_nMainScoreBase + m_nSabScoreBase;

	SharedData::SetData(21, &m_nTotalScoreBase);

	//========================================================================
	// TotalScore
	//========================================================================
	if (m_bTotalScoreFlg[0] == true)
	{
		m_nTotalScore1++;						// TotalScore��1���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore1 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore1 /= 1;				// TotalScore��1���ڂ���肾��
			m_bTotalScoreFlg[0] = false;		// ���݂̌��I���t���O
			m_bTotalScoreFlg[1] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[1] == true)
	{
		m_nTotalScore2++;						// TotalScore��2���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore2 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore2 /= 10;				// TotalScore��2���ڂ���肾��
			m_bTotalScoreFlg[1] = false;		// ���݂̌��I���t���O
			m_bTotalScoreFlg[2] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[2] == true)
	{
		m_nTotalScore3++;						// TotalScore��3���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore3 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore3 /= 100;				// TotalScore��3���ڂ���肾��
			m_bTotalScoreFlg[2] = false;		// ���݂̌��I���t���O
			m_bTotalScoreFlg[3] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[3] == true)
	{
		m_nTotalScore4++;						// TotalScore��4���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore4 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore4 /= 1000;				// TotalScore��4���ڂ���肾��
			m_bTotalScoreFlg[3] = false;		// ���݂̌��I���t���O
			m_bTotalScoreFlg[4] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}
	if (m_bTotalScoreFlg[4] == true)
	{
		m_nTotalScore5++;						// TotalScore��5���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore5 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore5 /= 10000;			// TotalScore��5���ڂ���肾��
			m_bTotalScoreFlg[4] = false;		// ���݂̌��I���t���O
			m_bTotalScoreFlg[5] = true;			// ���̌��J�n�t���O
			m_nTime = 0;
		}
	}

	if (m_bTotalScoreFlg[5] == true)
	{
		m_nTotalScore6++;						// TotalScore��6���ڂ���]�����鏈��

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nTotalScore6 = m_nTotalScoreBase;	// TotalScore����
			m_nTotalScore6 /= 100000;			// TotalScore��6���ڂ���肾��
			m_bTotalScoreFlg[5] = false;		// TotalScore�I���t���O
			m_bGoodScoreFlg = true;				// GoodScore�J�n�t���O
			m_nTime = 0;
		}
	}

	TotalScore1 = ((float)(m_nTotalScore6 % 10) / 1);
	TotalScore2 = ((float)(m_nTotalScore5 % 10) / 1);
	TotalScore3 = ((float)(m_nTotalScore4 % 10) / 1);
	TotalScore4 = ((float)(m_nTotalScore3 % 10) / 1);
	TotalScore5 = ((float)(m_nTotalScore2 % 10) / 1);
	TotalScore6 = ((float)(m_nTotalScore1 % 10) / 1);

	// �����_�ɂ���v�Z
	TotalScore1 *= 0.1f;
	TotalScore2 *= 0.1f;
	TotalScore3 *= 0.1f;
	TotalScore4 *= 0.1f;
	TotalScore5 *= 0.1f;
	TotalScore6 *= 0.1f;

	// ���ɃY����
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
	// �X�R�A�摜����
	Total_Score6->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score5->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore3, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore3, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore3 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score4->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore4, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore4, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore4 + 0.1f, 0.0f);
	// �X�R�A�摜����4
	Total_Score3->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore5, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore5, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore5 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(TotalScore6, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(TotalScore6, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(TotalScore6 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Total_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
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

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nGoodScore1 = m_nGoodScoreBase;	// GoodScore����
			m_nGoodScore1 /= 1;					// GoodScore��1���ڂ���肾��

			m_nGoodScore2 = m_nGoodScoreBase;	// GoodScore����
			m_nGoodScore2 /= 10;				// GoodScore��2���ڂ���肾��

			m_bGoodScoreFlg = false;			// GoodScore�I���t���O
			m_bBadScoreFlg = true;				// BadScore�J�n�t���O

			m_nTime = 0;
		}
	}

	GoodScore1 = ((float)(m_nGoodScore2 % 10) / 1);
	GoodScore2 = ((float)(m_nGoodScore1 % 10) / 1);

	// �����_�ɂ���v�Z
	GoodScore1 *= 0.1f;
	GoodScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Good_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(GoodScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(GoodScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(GoodScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Good_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Good_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, GOOD_SCORE_POSY, 0));
	Good_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, GOOD_SCORE_POSY, 0));





	//========================================================================
	// BadScore
	//========================================================================
	if (m_bBadScoreFlg == true)
	{

		// CNT_TIME���Ԍo�߂����珈��
		if (m_nTime >= CNT_TIME)
		{
			m_nBadScore2 = m_nBadScoreBase;	// BadScore����
			m_nBadScore2 /= 1;				// BadScore��1���ڂ���肾��

			m_nBadScore1 = m_nBadScoreBase;	// BadScore����
			m_nBadScore1 /= 10;				// BadScore��2���ڂ���肾��

			m_bBadScoreFlg = false;			// BadScore�I���t���O
			m_bBestPhotoFlg = true;			// BestPhoto�J�n�t���O

			m_nTime = 0;
		}
	}

	BadScore1 = ((float)(m_nBadScore1 % 10) / 1);
	BadScore2 = ((float)(m_nBadScore2 % 10) / 1);

	// �����_�ɂ���v�Z
	BadScore1 *= 0.1f;
	BadScore2 *= 0.1f;

	tex[0] = DirectX::SimpleMath::Vector2(BadScore1, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore1, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore1 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Bad_Score2->SetTexCoord(tex);

	tex[0] = DirectX::SimpleMath::Vector2(BadScore2, 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(BadScore2, 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(BadScore2 + 0.1f, 0.0f);
	// �X�R�A�摜����
	Bad_Score1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Bad_Score1->SetPos(DirectX::SimpleMath::Vector3(-90 + AAA, BAD_SCORE_POSY, 0));
	Bad_Score2->SetPos(DirectX::SimpleMath::Vector3(-120 + AAA, BAD_SCORE_POSY, 0));





	//========================================================================
	// BestPhoto
	//========================================================================
	if (m_bBestPhotoFlg == true)
	{
		// BestPhoto�����X�ɕ����яオ��
		a += 0.005f;

		// BestPhoto���N�b�L��������܂ŏ���
		if (a <= 1.0f)
		{
			BestPhoto->SetColor(r, g, b, a);
		}
		else
		{
			m_bBestPhotoFlg = false;			// BestPhoto�I���t���O
			m_bRankingCharFlg = true;			// RankingChar�J�n�t���O
		}
	}





	//========================================================================
	// �����N����
	//========================================================================
	if (m_bRankingCharFlg == true)
	{
		// �����N����S
		if (m_nTotalScoreBase >= RANKIN_SCORE_S)
		{
			m_nRankingChar1 = 8;
			Ranking_Char->SetTexture( L"data\\texture\\result\\S.png" );
		}
		// �����N����A
		else if (m_nTotalScoreBase >= RANKIN_SCORE_A)
		{
			m_nRankingChar1 = 6;
			Ranking_Char->SetTexture( L"data\\texture\\result\\A.png" );
		}
		// �����N����B
		else if (m_nTotalScoreBase >= RANKIN_SCORE_B)
		{
			m_nRankingChar1 = 4;
			Ranking_Char->SetTexture( L"data\\texture\\result\\B.png" );
		}
		// �����N����C
		else if (m_nTotalScoreBase >= RANKIN_SCORE_C)
		{
			m_nRankingChar1 = 2;
			Ranking_Char->SetTexture( L"data\\texture\\result\\C.png" );
		}
		// �����N����D
		else if (m_nTotalScoreBase >= RANKIN_SCORE_D)
		{
			m_nRankingChar1 = 0;
			Ranking_Char->SetTexture( L"data\\texture\\result\\D.png" );
		}
		// �����N����D
		else
		{
			m_nRankingChar1 = 0;
			Ranking_Char->SetTexture( L"data\\texture\\result\\D.png" );

		}


		m_nRankingChar1 /= 1;				// RankingChar��1���ڂ���肾��

		RankingChar = ((float)(m_nRankingChar1 % 10) / 1);

		// �����_�ɂ���v�Z
		RankingChar *= 0.1f;

		tex[0] = DirectX::SimpleMath::Vector2(RankingChar, 1.0f);
		tex[1] = DirectX::SimpleMath::Vector2(RankingChar, 0.0f);
		tex[2] = DirectX::SimpleMath::Vector2(RankingChar + 0.2f, 1.0f);
		tex[3] = DirectX::SimpleMath::Vector2(RankingChar + 0.2f, 0.0f);
		// �X�R�A�摜����
		//Ranking_Char->SetTexCoord(tex);

		// �����N�����X�ɕ����яオ��
		aa += 0.0185f;

		// �����N�̃A���t�@�[�l����
		if (aa <= 1.0f)
		{
			Ranking_Char->SetColor(rr, gg, bb, aa);
		}

		// �����N���������̑傫���܂ŏ���
		if (m_scl->x >= -0.025f)
		{
			// �����������N�������k��
			m_scl->x -= 0.0005f;
			m_scl->y -= 0.0005f;

			Ranking_Char->AddScale(DirectX::SimpleMath::Vector3(m_scl->x, m_scl->y, 1.0f));
		}
		// �����N���������ȏ�̑傫���ɂȂ����珈��
		else
		{
			aa = 1.0f;							// �����N�������N�b�L���\��
			Ranking_Char->SetColor(rr, gg, bb, aa);
			m_bRankingCharFlg = false;			// bRankingChar�I���t���O
		}

	}
}


//=============================================================================
// MainScore��n������
//=============================================================================
int Result::GetMainScore(void)
{
	return m_nMainScoreBase;
}
//=============================================================================
// MainScore���Z����
//=============================================================================
void Result::SetMainScore(int score)
{
	m_nMainScoreBase += score;
}

//=============================================================================
// SabScore��n������
//=============================================================================
int Result::GetSabScore(void)
{
	return m_nSabScoreBase;
}
//=============================================================================
// SabScore���Z����
//=============================================================================
void Result::SetSabScore(int score)
{
	m_nSabScoreBase += score;
}

//=============================================================================
// TotalScore��n������
//=============================================================================
int Result::GetTotalScore(void)
{
	return m_nTotalScoreBase;
}
//=============================================================================
// TotalScore���Z����
//=============================================================================
void Result::SetTotalScore(int score)
{
	m_nTotalScoreBase += score;
}

//=============================================================================
// GoodScore��n������
//=============================================================================
int Result::GetGoodScore(void)
{
	return m_nGoodScoreBase;
}
//=============================================================================
// GoodScore���Z����
//=============================================================================
void Result::SetGoodScore(int score)
{
	m_nGoodScoreBase = score;
}

//=============================================================================
// BadScore��n������
//=============================================================================
int Result::GetBadScore(void)
{
	return m_nBadScoreBase;
}
//=============================================================================
// BadScore���Z����
//=============================================================================
void Result::SetBadScore(int score)
{
	m_nBadScoreBase = score;
}