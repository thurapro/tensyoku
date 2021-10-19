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
#include "manager.h"
#include "data.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "item.h"
#include "stage.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "pose.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SOCRE	( 5 )			// 得点

//=============================================================================
// 静的メンバ変数
//=============================================================================
CCamera		*CGame::m_pCamera;		// カメラポインタ宣言
CLight		*CGame::m_pLight;		// ライトポインタ宣言
CData		*CGame::m_pData;		// データポインタ宣言
CStage		*CGame::m_pStage;		// ステージポインタ宣言
CPlayer		*CGame::m_pPlayer;		// プレイヤーポインタ宣言
CEnemy		**CGame::m_ppEnemy;		// 敵ポインタ宣言
CScore		*CGame::m_pScore;		// スコアーポインタ宣言
CTimer		*CGame::m_pTimer;		// タイマーポインタ宣言
CItem		**CGame::m_pItem;		// アイテムポインタ宣言
bool		CGame::m_bPose;			// ポーズフラグ宣言
bool		CGame::m_bFace;			// フェーズフラグ宣言

//=============================================================================
// 関数名	: Game
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス生成
//=============================================================================
CGame::CGame(void)
{
	m_pCamera	= NULL;		// カメラポインタ初期化
	m_pLight	= NULL;		// ライトポインタ初期化
	m_pData		= NULL;		// データポインタ初期化
	m_pStage	= NULL;		// ステージポインタ初期化
	m_pPlayer	= NULL;		// プレイヤーポインタ初期化
	m_ppEnemy	= NULL;		// 敵ポインタ初期化
	m_pScore	= NULL;		// スコアーポインタ初期化
	m_pTimer	= NULL;		// タイマーポインタ初期化
	m_pItem		= NULL;		// アイテムポインタ初期化
	m_pClear	= NULL;		// クリア画像ポインタ初期化
	m_bFace		= false;	// 次のモード移動
	m_pPose		= NULL;		// ポーズ初期化
	m_bPose		= false;	// ポーズ
}

//=============================================================================
// 関数名	: ~CGame
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス破棄
//=============================================================================
CGame::~CGame(void)
{
	// なし
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: ウィンドウハンドル
// 機能		: 初期化
//=============================================================================
HRESULT CGame::Init(HWND hWnd)
{
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//----------------------------------------------------------------------------
	// レンダリングステートの初期化設定
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//

	//-------------------------------------------------------------------------
	// サンプラーステートの初期化設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if( m_pCamera == NULL )
	{
		// カメラが作成されていなければ
		m_pCamera = NEW CCamera;			// カメラインスタンス生成
		m_pCamera->Init();					// カメラ初期化
	}

	if( m_pLight == NULL )
	{
		// ライトが作成されていなければ
		m_pLight = NEW CLight;				// ライトインスタンス生成
		hr = m_pLight->Init();				// ライト初期化
		ERROR_CHACK(hr);					// ライトが作成されているか
	}
	
	if( m_pData == NULL )
	{
		// データが作成されていなければ
		m_pData = NEW CData;								// データインスタンス生成
		hr = m_pData->Init(hWnd, "data/text/game.txt");		// データ初期化
		ERROR_CHACK(hr);									// データが作成されたか
	}

	NEW_TYPE(m_pStage, CStage);
	hr = m_pStage->Init();
	ERROR_CHACK(hr);

	if( m_pPlayer == NULL )
	{
		// プレイヤーが作成されていなければ
		m_pPlayer = CPlayer::Create(500, 0, 500, 3, 18);
		if(  m_pPlayer == NULL )
		{
			return E_FAIL;
		}
		m_pPlayer->SetScale( 1.0f, 1.0f, 1.0f);
	}

	if( m_pScore == NULL )
	{
		// スコアが作成されていなければ
		m_pScore = CScore::Create(0, 40, 0, 40, 12);			// スコアインスタンス生成
		if( m_pScore == NULL )
		{
			// スコアが作成されていなければ
			return E_FAIL;		// エラーコード
		}
	}

	if( m_pTimer == NULL )
	{
		m_pTimer = CTimer::Create(350, 40, 0, 40, 12);		// タイマーインスタンス生成
		if( m_pTimer == NULL )
		{
			// エラーチェック
			return E_FAIL;		// エラーコード
		}
	}

	m_pItem = NEW CItem*[MAX_ITEM];

	for( int item = 0; item < MAX_ITEM; item++ )
	{
		// アイテムが作られていなければ
		m_pItem[item] = CItem::Create(30, 0, 500, 3, 18);
		if( m_pItem == NULL )
		{
			// エラーチェック
			return E_FAIL;
		}
		m_pItem[item]->SetScale(1.0f, 1.0f, 1.0f);
	}
	m_pItem[1]->SetPosition(80, 0, -500);
	m_pItem[2]->SetPosition(-200, 0, -80);
	m_pItem[3]->SetPosition(400, 0, -800);
	m_pItem[4]->SetPosition(-400, 0, -500);

	if( m_pPose == NULL )
	{
		m_pPose = NEW CPose;
		hr = m_pPose->Init();
		ERROR_CHACK(hr);
	}

	m_pData->GetSound()->Play(1);

	return S_OK;		// 正常コード
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: 終了
//=============================================================================
void CGame::Uninit(void)
{
	// メモリ解放
	CScene::ReleaseAll();			// シーン破棄
	CLASS_DELETE(m_pStage);			// ステージインスタンス破棄
	CLASS_DELETE(m_pCamera);		// カメラインスタンス破棄
	CLASS_DELETE(m_pLight);			// ライトインスタンス破棄
	CLASS_DELETE(m_pData);			// データインスタンス破棄
}

//=============================================================================
// 関数名	: Updata
// 戻り値	: なし
// 引数		: なし
// 機能		: 更新
//=============================================================================
void CGame::Update(void)
{
	int score = 0;											// 得点
	CScene2D **pPose = m_pPose->GetPose();
	unsigned short nPoseNum = m_pPose->GetPoseNum();
	int Time = 0;

	if( CManager::GetInput()->KeyPush(DIK_P) )
	{
		if( m_pPose->GetTutorialFlag() == false )
		{

			if( m_bPose == true )
			{
				m_bPose = false;
				for( int i = 0; i < MAX_POSE; i++ )
				{
					pPose[i]->SetColor(0, 0, 0, 0);
					pPose[i]->SetTexNum(-1);
				}
				m_pPose->SetPoseNum(2);
			}
			else
			{
				m_bPose = true;
				pPose[0]->SetColor(0, 0, 0, 125);
				pPose[1]->SetColor(192, 192, 192, 255);

				for( int i = 2; i < MAX_POSE; i++ )
				{
					pPose[i]->SetColor(255, 255, 255, 255);
				}
				pPose[2]->SetTexNum(20);
				pPose[3]->SetTexNum(21);
				pPose[4]->SetTexNum(22);
				pPose[5]->SetTexNum(23);
				pPose[6]->SetTexNum(24);
			}
		}
	}
	if( m_bPose == false )
	{
		for( int i = 0; i < MAX_POSE; i++ )
		{
			pPose[i]->SetColor(0, 0, 0, 0);
			pPose[i]->SetTexNum(-1);
		}
		m_pCamera->Update();								// カメラの更新
		m_pLight->Update();
		CScene::UpdateAll();								// ゲーム更新
		
		score = m_pScore->GetScore();						// 得点取得
		Time = m_pTimer->GetTime();
		if( score >= MAX_SOCRE )
		{
			// 最低条件得点に達していたら
			if( m_pClear == NULL )
			{
				// クリア画像が作られていなければ
				CManager::SetRankScore(m_pTimer->GetTime());
				m_pClear = CScene2D::Create(60, 30, 500, 300, 17);			// クリア作成
				m_bFace = true;												//　移動フラグをONへ
				CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// フェードモードを設定
			}
		}
		else if( Time >= 60 )
		{
			if( m_pClear == NULL )
			{
				m_pClear = CScene2D::Create(60, 30, 500, 300, 17);			// クリア作成
				m_bFace = true;												//　移動フラグをONへ
				CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// フェードモードを設定
			}
		}
	}
	else
	{
		m_pPose->Update();
	}
	
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE && m_bFace == true )
	{
		if( nPoseNum == 3 )
		{
			CManager::SetMode(CManager::MODE_GAME);
		}
		else if( nPoseNum == 4 )
		{
			CManager::SetMode(CManager::MODE_TITLE);
		}
		else
		{
			// フェードの色が0(黒)で次のフェーズ移動フラグがONであれば
			CManager::SetMode(CManager::MODE_RESULT);			// リザルトヘ移行
		}
	}
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: 描画
//=============================================================================
void CGame::Draw(void)
{
	// フェードモードでなければ
	m_pCamera->Draw();
	CScene::DrawAll();
}
