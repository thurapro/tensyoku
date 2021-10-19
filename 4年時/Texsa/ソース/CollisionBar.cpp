/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ ������o�[�\���N���X
-----------------------------------------------------------------------------*/

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CollisionBar.h"
#include "Application.h"
#include "Sprite.h"
#include "Texture.h"

USING_MEEK

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CollisionBar::CollisionBar()
{
	m_pos = NEW DirectX::SimpleMath::Vector3;
	m_scl = NEW DirectX::SimpleMath::Vector2;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CollisionBar::~CollisionBar()
{
	delete m_pos;
	m_pos = NULL;

	delete m_scl;
	m_scl = NULL;
}

//=============================================================================
// ������
//=============================================================================
void CollisionBar::Init()
{
	*m_scl = DirectX::SimpleMath::Vector2(50, 180);
	auto ColBar = NEW Sprite(127, 250, L"data\\texture\\taiming.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	*m_pos = DirectX::SimpleMath::Vector3(-510, -200, 14);
	ColBar->SetPriority(6);
	ColBar->SetName("CollisionBar");
	ColBar->SetPos(*m_pos);
	AddChild(ColBar);
}

//=============================================================================
// �X�V
//=============================================================================
void CollisionBar::Update()
{

}

DirectX::SimpleMath::Vector3 CollisionBar::GetPos()
{
	return *m_pos;
}


DirectX::SimpleMath::Vector2 CollisionBar::GetScl()
{
	return *m_scl;
}
