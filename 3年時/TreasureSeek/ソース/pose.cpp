//=============================================================================
// 処理 [game.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: 
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "game.h"
#include "pose.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TIME		( 1000 )
#define INIT_TEX_Y		( 0.0f )
#define INIT_TEX_HEIGHT	( 1.0f / 2.0f )
#define NUMBER_INIT		( 2 )
#define MAX_NUNBER		( 5 )

//=============================================================================
// 関数名	: pose
// 戻り値	: なし
// 引数		: なし
// 機能		: ポーズインスタンス生成
//=============================================================================
CPose::CPose(void)
{
	ZeroMemory(m_apPose, sizeof(m_apPose) );			// タイトル画像初期化
	ZeroMemory(m_pTutorial, sizeof(m_pTutorial) );		// チュートリアル
	m_fTexY			= INIT_TEX_Y;						// それぞれの初期テクスチャY座標
	m_fTexHeight	= INIT_TEX_HEIGHT;					// それぞれの初期テクスチャの高さ
	m_nNumber		= NUMBER_INIT;						// どこを指しているか
	m_bTutorial		= false;
}

//=============================================================================
// 関数名	: ~CPose
// 戻り値	: なし
// 引数		: なし
// 機能		: ポーズインスタンス破棄
//=============================================================================
CPose::~CPose(void)
{
	// なし
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: 初期化
//=============================================================================
HRESULT CPose::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	for( int i = 0; i < MAX_POSE; i++ )
	{
		m_apPose[i] = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, -1);
		m_apPose[i]->SetColor(0, 0, 0, 0);
	}

	// バックポリゴン
	m_apPose[1]->SetPosition( (float)WINDOW_WIDTH / 5.0f, (float)WINDOW_HEIGHT / 7.0f);
	
	// コンティニュー
	m_apPose[2]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 6.5f);
	m_apPose[2]->SetTexure(0.0f, 0.0f, 1.0f, 0.5f); 

	// リトライ
	m_apPose[3]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 4.5f);
	m_apPose[3]->SetTexure(0.0f, 0.0f, 1.0f, 0.5f);

	// タイトルへ
	m_apPose[4]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 3.2f);
	m_apPose[4]->SetTexure(0.0f, 0.0, 1.0f, 0.5f);

	// チュートリアル
	m_apPose[5]->SetPosition( (float)WINDOW_WIDTH / 3.5f, (float)WINDOW_HEIGHT / 2.7f);
	m_apPose[5]->SetTexure(0.0f, 0.0, 1.0f, 0.5f);

	float fPointerPosX = m_apPose[m_nNumber]->GetPosition().x - 30;
	float fPointerPosY = m_apPose[m_nNumber]->GetPosition().y + 20;

	// カーソル
	m_apPose[6]->SetPosition(fPointerPosX , fPointerPosY);
	return S_OK;
}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 終了
//=============================================================================
void CPose::Uninit(void)
{
	CScene::ReleaseAll();		// シーン破棄
}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 更新
//=============================================================================
void CPose::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();		// キーボードを取得
	
	if( m_bTutorial == false )
	{
		if( pKeyboard->KeyPush(DIK_W) )
		{
			if( m_nNumber > NUMBER_INIT )
			{
				m_nNumber--;
			}
		}
		else if( pKeyboard->KeyPush(DIK_S) )
		{
			if( m_nNumber < (MAX_POSE - 2) )
			{
				m_nNumber++;
			}
		}
	}
	float fPointerPosX = m_apPose[m_nNumber]->GetPosition().x - 30;
	float fPointerPosY = m_apPose[m_nNumber]->GetPosition().y + 20;
	m_apPose[6]->SetPosition(fPointerPosX , fPointerPosY);
	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		if( m_nNumber > 2  && m_nNumber < (MAX_POSE - 2) )
		{
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);
			CGame::SetFaceFlag(true);
		}
		else if( m_nNumber == 2 )
		{
			CGame::SetPoseFlag(false);
		}
		else if( m_nNumber == (MAX_POSE - 2) )
		{
			for( int tutorial = 0; tutorial < 2; tutorial++ )
			{
				if( m_pTutorial[tutorial] == NULL )
				{
					m_pTutorial[tutorial] = CScene2D::Create( 0.0f, 0.0f, 640, 480, -1);
					m_pTutorial[tutorial]->SetColor(255, 255, 255, 255);
					m_bTutorial = true;
				}
				else
				{
					m_pTutorial[tutorial]->SetColor(0, 0, 0, 0);
					m_pTutorial[tutorial]->SetTexNum(-1);
					m_pTutorial[tutorial]->Release();
					m_pTutorial[tutorial] = NULL;
					m_bTutorial = false;
				}
			}
			if( m_pTutorial[1] != NULL )
			{
				m_pTutorial[1]->SetColor(0, 0, 255, 255);
				m_pTutorial[1]->SetTexNum(25);
			}
		}
	}
}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 描画
//=============================================================================
void CPose::Draw(void)
{
	CScene::DrawAll();
}
