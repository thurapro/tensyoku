#include "FadeSequence.h"
#include "Memory.h"
#include "Sprite.h"
#include "ShaderGroup.h"
#include "../DirectXTK/Inc/SimpleMath.h"
#include "ShaderBatch.h"
#include "Model.h"
#include "Camera.h"
#include "Renderer.h"
#include "Application.h"

static float speed = 0.01f;

FadeSequence::FadeSequence( Sequence *next ) :TransitionSequence( next ){

	using DirectX::SimpleMath::Vector2;
	using DirectX::SimpleMath::Vector3;
	using DirectX::SimpleMath::Vector4;
	using DirectX::SimpleMath::Matrix;

	auto camera2DLayer = NEW MeekH::Node();
	auto camera2D = NEW MeekL::Camera( 1280 , 720 , MeekL::Camera::Type::OrthographicLH );
	camera2DLayer->SetCamera( camera2D );
	camera2DLayer->SetName( "camera2DLayer" );

	auto fade = NEW MeekH::Sprite( 1280 , 720 , L"data\\texture\\fade.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	fade->SetName( "fade" );
	fade->SetPos(0,0,-10);
	fade->SetColor(0,0,0,0);

	camera2DLayer->AddChild(fade);
	AddChild(camera2DLayer);

	speed = 0.1f;
}
FadeSequence::~FadeSequence(){

}

void FadeSequence::Visit(){
	if( m_current ){
		m_current->Visit();

	}
	Sequence::Visit();

}
void FadeSequence::Update(){
	
	auto fade = static_cast<MeekH::Sprite*>( FindNode( "fade" ) );
	fade->AddColor( 0 , 0 , 0 , speed );
	if( 1 < fade->GetColor().w ){
		SAFE_DELETE( m_current );
		m_current = m_next;
		speed = -0.01f;
	}
	if( fade->GetColor().w < 0 ){
		MeekH::Application::GetInstance()->ChangeSequence(m_current);
	}

}

void FadeSequence::Init( Sequence *current ){
	TransitionSequence::Init( current );
}
