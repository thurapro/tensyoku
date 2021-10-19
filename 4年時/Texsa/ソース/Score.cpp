/**************************************************************************//**
* @file			Score.cpp
* @brief
* @author 		Hirai Yuuki
*****************************************************************************/
#include "Score.h"

#include "Application.h"
#include "Node.h"
#include "Sprite.h"

USING_MEEK

#define POSY (292)				// �X�R�A�\���ʒuY
#define SIZEX (40)				// �X�R�A�傫��X
#define SIZEY (40)				// �X�R�A�傫��Y
#define SCORE_MAX (99999)		// �X�R�A���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Score::Score(){
	m_pos = NEW DirectX::SimpleMath::Vector3;
	m_rot = NEW DirectX::SimpleMath::Vector3;
	m_scl = NEW DirectX::SimpleMath::Vector3;

	m_nScore = 0;
	m_bFlg = false;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Score::~Score(){
}


//=============================================================================
// ����������
//=============================================================================
void Score::Init(){
	// �X�R�A���l
	auto Num1 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Num1->SetName("num1");
	auto Num2 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Num2->SetName("num2");
	auto Num3 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Num3->SetName("num3");
	auto Num4 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Num4->SetName("num4");
	auto Num5 = NEW Sprite(SIZEX, SIZEY, L"data\\texture\\nomber.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	Num5->SetName("num5");

	// �X�R�A����
	auto ScoreChar = NEW Sprite(800, 114, L"data\\texture\\score.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	ScoreChar->SetName("scorechar");

	//�X�R�A�����\���ʒu
	ScoreChar->SetPos(DirectX::SimpleMath::Vector3(0, 300, 0));


	DirectX::SimpleMath::Vector2 tex[4];

	float Score[5];

	Score[0] = ((m_nScore % 100000) / 10000);
	Score[1] = ((m_nScore % 10000) / 1000);
	Score[2] = ((m_nScore % 1000) / 100);
	Score[3] = ((m_nScore % 100) / 10);
	Score[4] = ((m_nScore % 10) / 1);

	Score[0] *= 0.1;
	Score[1] *= 0.1;
	Score[2] *= 0.1;
	Score[3] *= 0.1;
	Score[4] *= 0.1;

	// ���ɃY����
	Num1->AddTexCoordX((float)Score[0]);
	Num2->AddTexCoordX((float)Score[1]);
	Num3->AddTexCoordX((float)Score[2]);
	Num4->AddTexCoordX((float)Score[3]);
	Num5->AddTexCoordX((float)Score[4]);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[0], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[0], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[0] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[0] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num5->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[1], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[1], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[1] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[1] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num4->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[2], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[2], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[2] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[2] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num3->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[3], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[3], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[3] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[3] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num2->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[4], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[4], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[4] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[4] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num1->SetTexCoord(tex);

	// �X�R�A�\���ʒu
	Num1->SetPos(DirectX::SimpleMath::Vector3(80, POSY, 0));
	Num2->SetPos(DirectX::SimpleMath::Vector3(40, POSY, 0));
	Num3->SetPos(DirectX::SimpleMath::Vector3(0, POSY, 0));
	Num4->SetPos(DirectX::SimpleMath::Vector3(-40, POSY, 0));
	Num5->SetPos(DirectX::SimpleMath::Vector3(-80, POSY, 0));

	AddChild(Num1);
	AddChild(Num2);
	AddChild(Num3);
	AddChild(Num4);
	AddChild(Num5);
	AddChild(ScoreChar);
}


//=============================================================================
// �X�V����
//=============================================================================
void Score::Update(){
	Sprite *Num1, *Num2, *Num3, *Num4, *Num5;
	Num1 = (Sprite*)GetChild("num1");
	Num2 = (Sprite*)GetChild("num2");
	Num3 = (Sprite*)GetChild("num3");
	Num4 = (Sprite*)GetChild("num4");
	Num5 = (Sprite*)GetChild("num5");

	DirectX::SimpleMath::Vector2 tex[4];

	float Score[5];
	//m_nScore++;		// ���Z����

	Score[0] = ((m_nScore % 100000) / 10000);
	Score[1] = ((m_nScore % 10000) / 1000);
	Score[2] = ((m_nScore % 1000) / 100);
	Score[3] = ((m_nScore % 100) / 10);
	Score[4] = ((m_nScore % 10) / 1);

	Score[0] *= 0.1;
	Score[1] *= 0.1;
	Score[2] *= 0.1;
	Score[3] *= 0.1;
	Score[4] *= 0.1;

	// ���ɃY����
	Num1->AddTexCoordX((float)Score[0]);
	Num2->AddTexCoordX((float)Score[1]);
	Num3->AddTexCoordX((float)Score[2]);
	Num4->AddTexCoordX((float)Score[3]);
	Num5->AddTexCoordX((float)Score[4]);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[0], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[0], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[0] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[0] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num5->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[1], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[1], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[1] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[1] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num4->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[2], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[2], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[2] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[2] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num3->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[3], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[3], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[3] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[3] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num2->SetTexCoord(tex);

	// N
	tex[0] = DirectX::SimpleMath::Vector2(Score[4], 1.0f);
	tex[1] = DirectX::SimpleMath::Vector2(Score[4], 0.0f);
	tex[2] = DirectX::SimpleMath::Vector2(Score[4] + 0.1f, 1.0f);
	tex[3] = DirectX::SimpleMath::Vector2(Score[4] + 0.1f, 0.0f);
	// �X�R�A�摜����
	Num1->SetTexCoord(tex);

	// �X�R�A�������
	if (m_nScore >= SCORE_MAX)
	{
		m_nScore = SCORE_MAX;
	}
}


//=============================================================================
// �X�R�A��n������
//=============================================================================
int Score::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// �X�R�A���Z����
//=============================================================================
void Score::SetScore(int nScore)
{
	m_nScore += nScore;
}