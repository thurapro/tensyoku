/**************************************************************************//**
 * @file		TokiSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "TokiSequence.h"
#include "Memory.h"
#include "Node.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"

#include <Windows.h>
#include "TitleSequence.h"

USING_MEEK

TokiSequence::TokiSequence(){
	using DirectX::SimpleMath::Vector2;

	auto camera2dLayer = NEW Node();
	auto spriteNode = NEW Sprite(100, 100, L"data\\texture\\Result.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");

	camera2dLayer->SetCamera(NEW Camera(1280, 720, Camera::Type::OrthographicLH));
	camera2dLayer->AddChild(spriteNode);
	AddChild(camera2dLayer);
}

TokiSequence::~TokiSequence(){

}

void TokiSequence::Update(){

}