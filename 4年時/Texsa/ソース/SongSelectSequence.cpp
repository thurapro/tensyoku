/**************************************************************************//**
 * @file		SongSelectSequence.cpp
 * @brief		
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#include "SongSelectSequence.h"
#include "Memory.h"
#include "Node.h"
#include "TransformComponent.h"
#include "ShaderComponent.h"
#include "SpriteComponent.h"
#include "DrawableComponent.h"
#include "ShaderGroup.h"
#include "Application.h"
#include "Camera.h"
#include "Sprite.h"
#include "audio.h"

#include <Windows.h>
#include "GameSequence.h"

#include "Input.h"
#include "WiiController.h"
#include "FadeSequence.h"

#define KATAMUKE_TIME (120)	// WiiÉRÉìÇåXÇØÇƒÇ¢ÇÈéûä‘

using MeekH::Sprite;
using DirectX::SimpleMath::Vector2;

SongSelectSequence::SongSelectSequence(){
	m_cnt1 = 0;

	auto camera2dLayer = NEW MeekH::Node();
	camera2dLayer->SetCamera( NEW MeekL::Camera( 1280 , 720 , MeekL::Camera::Type::OrthographicLH ) );
	
	auto bgm1 = NEW MeekH::Sprite(512, 64, L"data\\texture\\bgm1.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	bgm1->SetPos(0, 256, 0);
	bgm1->SetName("bgm1");
	bgm1->SetPriority(4);			// âÊëúÇÃóDêÊèáà 

	auto bgm2 = NEW MeekH::Sprite(512, 64, L"data\\texture\\bgm2.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	bgm2->SetPos(0, 256, 0);
	bgm2->SetName("bgm2");
	bgm2->SetPriority(3);			// âÊëúÇÃóDêÊèáà 

	auto bgm3 = NEW MeekH::Sprite(512, 64, L"data\\texture\\bgm3.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	bgm3->SetPos(0, 256, 0);
	bgm3->SetName("bgm3");
	bgm3->SetPriority(5);			// âÊëúÇÃóDêÊèáà 

	//auto song = NEW MeekH::Sprite(512, 64, L"data\\texture\\song.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	//Vector2 texCoord[4] = {
	//	Vector2(0,1) ,
	//	Vector2(0,0) ,
	//	Vector2(1/3.f,1) ,
	//	Vector2(1/3.f,0) ,

	//
	//};

	//song->SetTexCoord( texCoord );
	//song->SetPos(0,256,0);
	//song->SetName("song");

	auto easy = NEW MeekH::Sprite( 32*3 , 192 , L"data\\texture\\easy.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	easy->SetPos(-256,0,0);
	easy->SetName("easy");

	auto normal = NEW MeekH::Sprite( 32 * 3 , 192 , L"data\\texture\\normal.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	normal->SetPos( 0 , 0 , 0 );
	normal->SetName( "normal" );
	normal->SetScale( 1.4f , 1.4f , 1.4f );

	auto hard = NEW MeekH::Sprite( 32 * 3 , 192 , L"data\\texture\\hard.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	hard->SetPos( 256 , 0 , 0 );
	hard->SetName( "hard" );

	auto levelSelect = NEW MeekH::Sprite( 32 * 3 , 192 , L"data\\texture\\select.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	levelSelect->SetVisible(false);
	levelSelect->SetPos( 0 , 0 , -1 );
	levelSelect->SetName("levelSelect");
	levelSelect->SetScale( 1.4f , 1.4f , 1.4f );

	auto start_off = NEW MeekH::Sprite(256, 128, L"data\\texture\\start_off.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	start_off->SetName("start_off");
	start_off->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	start_off->SetPos(0, -256, 1);
	start_off->SetPriority(3);			// âÊëúÇÃóDêÊèáà 

	auto start_on = NEW MeekH::Sprite(256, 128, L"data\\texture\\start_on.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\Shader\\PixelShader_2D.hlsl");
	start_on->SetName("start_on");
	start_on->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	start_on->SetPos(0, -256, 1);
	start_on->SetPriority(4);			// âÊëúÇÃóDêÊèáà 

	float arrowSize = 20.f;
	auto arrow1 = NEW MeekH::Sprite( 4 * arrowSize , 3 * arrowSize , L"data\\texture\\arrow.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	arrow1->SetPos( 256 + 64 , 256 , 1 );
	arrow1->SetRotation( 0 , 0 , -3.14 / 2.f );

	auto arrow2 = NEW MeekH::Sprite( 4 * arrowSize , 3 * arrowSize , L"data\\texture\\arrow.png" , L"data\\shader\\VertexShader_2D.hlsl" , L"data\\Shader\\PixelShader_2D.hlsl" );
	arrow2->SetPos( -256 - 64 , 256 , 1 );
	arrow2->SetRotation( 0 , 0 , 3.14 / 2.f );

	// ÇΩÇ¢Ç‹Ç¬àÍî‘ç∂1
	auto taimatu_left1 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_left1->SetName("taimatu_left1");
	taimatu_left1->SetPos(-536, -256, 1);
	taimatu_left1->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬2
	auto taimatu_left2 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_left2->SetName("taimatu_left2");
	taimatu_left2->SetPos(-424, -256, 1);
	taimatu_left2->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬3
	auto taimatu_left3 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_left3->SetName("taimatu_left3");
	taimatu_left3->SetPos(-312, -256, 1);
	taimatu_left3->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬4
	auto taimatu_left4 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_left4->SetName("taimatu_left4");
	taimatu_left4->SetPos(-200, -256, 1);
	taimatu_left4->SetColor(1.0f, 1.0f, 1.0f, 0.3f);

	// ÇΩÇ¢Ç‹Ç¬àÍî‘âE1
	auto taimatu_light1 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_light1->SetName("taimatu_light1");
	taimatu_light1->SetPos(536, -256, 1);
	taimatu_light1->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬2
	auto taimatu_light2 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_light2->SetName("taimatu_light2");
	taimatu_light2->SetPos(424, -256, 1);
	taimatu_light2->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬3
	auto taimatu_light3 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_light3->SetName("taimatu_light3");
	taimatu_light3->SetPos(312, -256, 1);
	taimatu_light3->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	// ÇΩÇ¢Ç‹Ç¬4
	auto taimatu_light4 = NEW Sprite(120, 120, L"data\\texture\\taimatu_test.png", L"data\\shader\\VertexShader_2D.hlsl", L"data\\shader\\PixelShader_2D.hlsl");
	taimatu_light4->SetName( "taimatu_light4" );
	taimatu_light4->SetPos(200, -256, 1);
	taimatu_light4->SetColor(1.0f, 1.0f, 1.0f, 0.3f);


	//Vector2 startTexCoord[] = {
	//	Vector2( 0 , 1 ) ,
	//	Vector2( 0 , 0 ) ,
	//	Vector2( 1 / 5.f , 1 ) ,
	//	Vector2( 1 / 5.f , 0 ) ,

	//};

	//start->SetTexCoord( startTexCoord );


	//camera2dLayer->AddChild( song );
	camera2dLayer->AddChild( bgm1 );
	camera2dLayer->AddChild( bgm2 );
	camera2dLayer->AddChild( bgm3 );
	camera2dLayer->AddChild( easy );
	camera2dLayer->AddChild( normal );
	camera2dLayer->AddChild( hard );
	camera2dLayer->AddChild( levelSelect );
	camera2dLayer->AddChild(start_off);
	camera2dLayer->AddChild(start_on);
	camera2dLayer->AddChild(taimatu_left1);
	camera2dLayer->AddChild(taimatu_left2);
	camera2dLayer->AddChild(taimatu_left3);
	camera2dLayer->AddChild(taimatu_left4);
	camera2dLayer->AddChild(taimatu_light1);
	camera2dLayer->AddChild(taimatu_light2);
	camera2dLayer->AddChild(taimatu_light3);
	camera2dLayer->AddChild( taimatu_light4 );
	camera2dLayer->AddChild( arrow1 );
	camera2dLayer->AddChild( arrow2 );


	AddChild( camera2dLayer );

	m_mode = Mode::MODE_SONGSELECT;
	m_selectLevelIndex = 1;
	m_levelName[0] = easy->GetName();
	m_levelName[1] = normal->GetName();
	m_levelName[2] = hard->GetName();
	m_startFrame = 0;

	m_cnt = 0;
	m_startcnt = 0;
	m_bTest1 = false;
	m_bTest2 = false;
	m_bTest3 = false;


	// BGM
	m_bgmIndex = 1;
	m_soundObject[0] = NEW CSoundObject("data\\sound\\bgm1.wav");
	m_soundObject[1] = NEW CSoundObject( "data\\sound\\bgm2.wav" );
	m_soundObject[2] = NEW CSoundObject( "data\\sound\\bgm3.wav" );

	m_soundObject[m_bgmIndex]->Play();

	m_scaleAnimation = false;
	m_scaleAnimationFrame = 0;

	m_startWait = false;
	m_startWaitFrame = 0;

}
SongSelectSequence::~SongSelectSequence(){
	SAFE_DELETE( m_soundObject[0] );
	SAFE_DELETE( m_soundObject[1] );
	SAFE_DELETE( m_soundObject[2] );

}
void SongSelectSequence::Update(){
	Sprite *taimatu_left1, *taimatu_left2, *taimatu_left3, *taimatu_left4,
		*taimatu_light1, *taimatu_light2, *taimatu_light3, *taimatu_light4,
		*start_off , *start_on , *bgm1 , *bgm2 , *bgm3 , *levelSelect;

	taimatu_left1 = (Sprite*)GetChild("taimatu_left1");
	taimatu_left2 = (Sprite*)GetChild("taimatu_left2");
	taimatu_left3 = (Sprite*)GetChild("taimatu_left3");
	taimatu_left4 = (Sprite*)GetChild("taimatu_left4"); 
	taimatu_light1 = (Sprite*)GetChild("taimatu_light1");
	taimatu_light2 = (Sprite*)GetChild("taimatu_light2");
	taimatu_light3 = (Sprite*)GetChild("taimatu_light3");
	taimatu_light4 = (Sprite*)GetChild("taimatu_light4");
	start_off = (Sprite*)GetChild("start_off");
	start_on = (Sprite*)GetChild("start_on");
	bgm1 = (Sprite*)GetChild("bgm1");
	bgm2 = (Sprite*)GetChild("bgm2");
	bgm3 = (Sprite*)GetChild("bgm3");

	levelSelect = ( Sprite* )FindNode( "levelSelect" );

	CWiiController *Wii = CWiiController::GetInstance(0);
	Wii->Update();

	float addScale = 0.005f;

	switch( m_mode )
	{
		// BGMëIë
	case SongSelectSequence::Mode::MODE_SONGSELECT:

		//ägèk
		++m_scaleAnimationFrame;
		if( m_scaleAnimationFrame == 30 ){
			m_scaleAnimation = !m_scaleAnimation;
			m_scaleAnimationFrame = 0;
		}
		addScale = 0.002f;
		if( m_scaleAnimation ){
			static_cast< Sprite* >( FindNode( "bgm1" ) )->AddScale( addScale , addScale , 0 );
			static_cast< Sprite* >( FindNode( "bgm2" ) )->AddScale( addScale , addScale , 0 );
			static_cast< Sprite* >( FindNode( "bgm3" ) )->AddScale( addScale , addScale , 0 );

		}
		else{
			static_cast< Sprite* >( FindNode( "bgm1" ) )->AddScale( -addScale , -addScale , 0 );
			static_cast< Sprite* >( FindNode( "bgm2" ) )->AddScale( -addScale , -addScale , 0 );
			static_cast< Sprite* >( FindNode( "bgm3" ) )->AddScale( -addScale , -addScale , 0 );
		}


		//m_cnt++;
		// è≠Çµë“Ç¬
		//if (m_cnt > 0)
		//{
			// WiiÉRÉìÇâEÇ…åXÇØÇÈÇ∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RIGHT))
#if 1
			if (Wii->GetAccel().RawX > 150.0f)
			{
				// åXÇØÇƒÇ¢Çƒéûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;

					if (m_bTest1 == false)
					{
						static_cast<Sprite*>(FindNode("bgm1"))->SetPriority(5);
						static_cast<Sprite*>(FindNode("bgm2"))->SetPriority(4);
						static_cast<Sprite*>(FindNode("bgm3"))->SetPriority(3);
						m_soundObject[m_bgmIndex]->Stop();
						m_bgmIndex = 2;
						m_soundObject[m_bgmIndex]->Play();
						m_bTest1 = true;
						m_bTest2 = false;
						m_bTest3 = false;
					}
				}
			}
			// WiiÉRÉìÇç∂Ç…åXÇØÇÈÇ∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_LEFT))
			if (Wii->GetAccel().RawX < 110.0f)
			{
				// åXÇØÇƒÇ¢Çƒéûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;

					if (m_bTest2 == false)
					{
						static_cast<Sprite*>(FindNode("bgm1"))->SetPriority(3);
						static_cast<Sprite*>(FindNode("bgm2"))->SetPriority(4);
						static_cast<Sprite*>(FindNode("bgm3"))->SetPriority(5);
						m_soundObject[m_bgmIndex]->Stop();
						m_bgmIndex = 0;
						m_soundObject[m_bgmIndex]->Play();
						m_bTest1 = false;
						m_bTest2 = true;
						m_bTest3 = false;
					}
				}
			}

			// WiiÉRÉìÇåXÇØÇ»Ç¢Ç∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_UP))
			if (Wii->GetAccel().RawX > 120.0f && Wii->GetAccel().RawX < 140.0f)
			{
				// åXÇØÇƒÇ¢Ç»Ç¢Ç≈éûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;

					if (m_bTest3 == false)
					{
						static_cast<Sprite*>(FindNode("bgm1"))->SetPriority(4);
						static_cast<Sprite*>(FindNode("bgm2"))->SetPriority(3);
						static_cast<Sprite*>(FindNode("bgm3"))->SetPriority(5);
						m_soundObject[m_bgmIndex]->Stop();
						m_bgmIndex = 1;
						m_soundObject[m_bgmIndex]->Play();

						m_bTest1 = false;
						m_bTest2 = false;
						m_bTest3 = true;

					}
				}
			}
#endif

			// WiiÉRÉìècÉtÉäÇ≈åàíË
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN))
			if (Wii->GetAccel().Z > 3.2f)
			{
				m_cnt = 0;
				m_mode = Mode::MODE_LEVELSELECT;
				m_scaleAnimationFrame = 0;
				m_scaleAnimation = false;

			}
		//}
		break; 
		// ìÔà’ìxëIë
	case SongSelectSequence::Mode::MODE_LEVELSELECT:

		static_cast< Sprite* >( FindNode( "bgm1" ) )->SetScale( 1 , 1 , 1 );
		static_cast< Sprite* >( FindNode( "bgm2" ) )->SetScale( 1 , 1 , 1 );
		static_cast< Sprite* >( FindNode( "bgm3" ) )->SetScale( 1 , 1 , 1 );
		levelSelect->SetVisible(true);
		// è≠Çµë“Ç¬
		m_cnt++;
		if (m_cnt > 20)
		{
			// WiiÉRÉìÇåXÇØÇ»Ç¢Ç∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_UP))
			if (Wii->GetAccel().RawX > 120.0f && Wii->GetAccel().RawX < 140.0f)
			{
				// åXÇØÇƒÇ¢Ç»Ç¢Ç≈éûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;

					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1, 1, 1);
					m_selectLevelIndex = 1;

					static_cast<Sprite*>(FindNode("levelSelect"))->SetPos(-256 + 256.f * m_selectLevelIndex, 0, -1);
					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1.4f, 1.4f, 1.4f);
				}
			}

			// WiiÉRÉìÇç∂Ç…åXÇØÇÈÇ∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_LEFT))
			if (Wii->GetAccel().RawX < 110.0f)
			{
				// åXÇØÇƒÇ¢Çƒéûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;
					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1, 1, 1);
					--m_selectLevelIndex;

					// indexî‘çÜÇ™0ÇÊÇËè¨Ç≥Ç≠Ç»Ç¡ÇΩÇÁindexî‘çÜÇ™2Ç…Ç»ÇÈ
					if (m_selectLevelIndex < 0){
						//m_selectlevelindex = 2;
						m_selectLevelIndex = 0;
					}

					static_cast<Sprite*>(FindNode("levelSelect"))->SetPos(-256 + 256.f * m_selectLevelIndex, 0, -1);
					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1.4f, 1.4f, 1.4f);
				}

			}
			// WiiÉRÉìÇâEÇ…åXÇØÇÈÇ∆èàóù
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RIGHT))
			if (Wii->GetAccel().RawX > 150.0f)
			{
				// åXÇØÇƒÇ¢Çƒéûä‘Ç™êîïbåoâﬂÇµÇΩÇÁèàóù
				m_cnt1++;
				if (m_cnt1 >= KATAMUKE_TIME)
				{
					m_cnt1 = 0;
					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1, 1, 1);
					++m_selectLevelIndex;

					// Indexî‘çÜÇ™0ÇÊÇËëÂÇ´Ç≠Ç»Ç¡ÇΩÇÁIndexî‘çÜÇ™0Ç…Ç»ÇÈ
					if (2 < m_selectLevelIndex){
						//m_selectLevelIndex = 0;
						m_selectLevelIndex = 2;
					}

					static_cast<Sprite*>(FindNode("levelSelect"))->SetPos(-256 + 256.f * m_selectLevelIndex, 0, -1);
					static_cast<Sprite*>(FindNode(m_levelName[m_selectLevelIndex]))->SetScale(1.4f, 1.4f, 1.4f);
				}
			}

			// WiiÉRÉìècÉtÉäÇ≈åàíË
			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_RETURN))
			if (Wii->GetAccel().Z > 3.2f)
			{
				m_mode = Mode::MODE_START;
			}

			//if (CInput::GetInstance()->GetKeyboard()->IsKeyTrigger(DIK_BACKSPACE)){
			//	m_mode = Mode::MODE_SONGSELECT;
			//}
		}
		break;
		// ÉXÉ^Å[Ég
	case Mode::MODE_START:
		levelSelect->SetVisible( false );

		++m_scaleAnimationFrame;
		if( m_scaleAnimationFrame == 30 ){
			m_scaleAnimation = !m_scaleAnimation;
			m_scaleAnimationFrame = 0;
		}
		if( m_scaleAnimation ){
			static_cast< Sprite* >( FindNode( "start_off" ) )->AddScale( 0.01f , 0.01f ,0 );
		}
		else{
			static_cast<Sprite*>( FindNode( "start_off" ) )->AddScale( -0.01f , -0.01f ,0 );
		}

		if( m_startFrame % 60 == 0 ){
			m_startcnt++;

			// 1
			if (m_startcnt == 1)
			{
				static_cast<Sprite*>(FindNode("taimatu_left1"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				static_cast<Sprite*>(FindNode("taimatu_light1"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			// 2
			if (m_startcnt == 2)
			{
				static_cast<Sprite*>(FindNode("taimatu_left2"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				static_cast<Sprite*>(FindNode("taimatu_light2"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			// 3
			if (m_startcnt == 3)
			{
				static_cast<Sprite*>(FindNode("taimatu_left3"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				static_cast<Sprite*>(FindNode("taimatu_light3"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			// 4
			if (m_startcnt == 4)
			{
				static_cast<Sprite*>(FindNode("taimatu_left4"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				static_cast<Sprite*>(FindNode("taimatu_light4"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		++m_startFrame;
		if( m_startFrame == 60 * 4 -1 ){
			static_cast<Sprite*>(FindNode("start_off"))->SetPriority(4);
			static_cast<Sprite*>(FindNode("start_on"))->SetPriority(3);
			static_cast<Sprite*>(FindNode("start_on"))->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

			m_soundObject[m_bgmIndex]->Stop();
			m_startWait = true;
		}
		break;
	default:
		break;
	}
	
	if( m_startWait ){
		++m_startWaitFrame;
		if( m_startWaitFrame == 30 ){
			MeekH::Application::GetInstance()->ChangeSequence( NEW FadeSequence( NEW GameSequence() ) );
		}
	}
}