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
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "data.h"
#include "fade.h"
#include "title.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE			("data/text/title.txt")
#define MAX_TIME		( 1000 )
#define CHAR_POSY		( 0 )
#define CHAR_HEIGHT		( 0 )
#define CHAR_SPEED		( 1 )
#define INIT_TEX_X		( 0.0f )
#define INIT_TEX_WIDTH	( 1.0f / 4.0f )
#define TEX_SPEED		( 1.0f / 4.0f )
#define CLEAN_TIME		( 0 )

//=============================================================================
// 静的メンバ変数
//=============================================================================
CData		*CTitle::m_pData;						// 画像の実体生成

//=============================================================================
// 関数名	: Game
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス生成
//=============================================================================
CTitle::CTitle(void)
{
	m_pData			= NULL;								// データ初期化
	ZeroMemory(m_pTitleScene, sizeof(m_pTitleScene) );	// タイトル画像初期化
	m_bFace			= false;							// 次のモード移動フラグ
	m_fPosY			= CHAR_POSY;						// 宝キャラクタのY座標位置 
	m_fHeight		= CHAR_HEIGHT;						// 宝キャラクタの高さ
	m_fSpeed		= CHAR_SPEED;						// 宝キャラクタの速度
	m_fTexX			= INIT_TEX_X;						// PushEnterの初期テクスチャX座標
	m_fTexWidth		= INIT_TEX_WIDTH;					// PushEnterの初期テクスチャの幅
	m_fSpeedTex		= TEX_SPEED;						// PushEnterのアニメーション速度
	m_nTimeCnt		= CLEAN_TIME;						// PushEnterのアニメーション速度抑制カウント
}

//=============================================================================
// 関数名	: ~CTitle
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス破棄
//=============================================================================
CTitle::~CTitle(void)
{
	// なし
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: 初期化
//=============================================================================
HRESULT CTitle::Init(HWND hWnd)
{
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//----------------------------------------------------------------------------
	// レンダリングステートの初期化設定
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//

	////-------------------------------------------------------------------------
	//// サンプラーステートの初期化設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if( m_pData == NULL )
	{
		// データがなかった
		NEW_TYPE(m_pData, CData);				// データをインスタンス生成
		hr = m_pData->Init(hWnd, TITLE);	// データを初期化
		ERROR_CHACK(hr);					// エラーチェック
	}

	m_pTitleScene[0] = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 5);
	if( m_pTitleScene[0] == NULL )
	{
		return NULL;
	}

	// タイトルフォントシーン2D
	m_pTitleScene[1] = CScene2D::Create(40, 0, 500, 300, 2);
	if( m_pTitleScene[1] == NULL )
	{
		// テクスチャ
		return E_FAIL;
	}
	
	// 宝箱シーン2D
	m_pTitleScene[2] = CScene2D::Create(0, 150, WINDOW_WIDTH, 160, 1);
	if( m_pTitleScene[2] == NULL )
	{
		// テクスチャ
		return E_FAIL;
	}

	// 宝キャラ用 変数
	m_fPosY = 130;					// 位置Y
	m_fHeight = 120;				// 高さ

	// 宝キャラシーン2D
	m_pTitleScene[3] = CScene2D::Create(120, m_fPosY, 300, m_fHeight, 3);
	if( m_pTitleScene[3] == NULL )
	{
		// テクスチャ
		return E_FAIL;
	}

	// PushEnterフォント2D
	m_pTitleScene[4] = CScene2D::Create(40, 300, 400, 100, 4);
	if( m_pTitleScene[4] == NULL )
	{
		// テクスチャ
		return E_FAIL;
	}

	// PushEnterフォント2Dのテクスチャ座標設定
	m_pTitleScene[4]->SetTexure(m_fTexX, 0.0f, m_fTexWidth, 1.0f);

	return S_OK;
}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 終了
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();		// シーン破棄
	CLASS_DELETE(m_pData);		// タイトルで使ったデータ破棄
}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 更新
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();		// キーボードを取得
	int nColor = CManager::GetFade()->GetColor();						// 現在のフェードの色取得
	
	// フェード中のボタン押しガード
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE  )
	{
		// フェードしていなければ			
		if( m_fPosY <= 80 )
		{
			// 20より値小さくになったら
			 m_fSpeed = 1;						// 宝キャラを上に移動させる
		}
		if( m_fPosY >= 140 )
		{
			// 
			m_fSpeed = -1;						// 宝キャラを下に移動させる
		}
		m_fPosY += m_fSpeed;					// 宝キャラの上下移動

		// 速度の抑制
		if( m_nTimeCnt > MAX_TIME)
		{
			// タイムカウントが最高時間をこえていたら
			if( m_fTexWidth >= 1.0f)
			{
				// テクスチャのX座標が1.0fを超えたら
				m_fTexX = INIT_TEX_X;			// テクスチャ座標位置を初期化
				m_fTexWidth = INIT_TEX_WIDTH;		// テクスチャ座標位置を初期化
			}
			else
			{
				m_fTexX += m_fSpeedTex;			// テクスチャ座標を動かす
				m_fTexWidth += m_fSpeedTex;		// テクスチャ座標を動かす
			}
			m_nTimeCnt = 0;						// 抑制カウントを初期化
		}
		m_nTimeCnt += 16;						// 抑制カウントをカウントアップ

		// 宝キャラを移動させる
		m_pTitleScene[3]->SetPosition(0, m_fPosY);
		
		// PushEnterのロゴをアニメーションさせる 
		m_pTitleScene[4]->SetTexure(m_fTexX, 0.0f, m_fTexWidth, 1.0f); 
		CScene::UpdateAll();							// シーンを更新
		if( pKeyboard->KeyPush(DIK_RETURN) )
		{
			// ENTERキーがおされたら
			m_bFace = true;								// 次のフェーズフラグをONへ
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);	// フェードのモード設定
		}
	}

	CManager::GetFade()->Update();

	// 画面遷移処理
	if( nColor >= 255 && m_bFace == true )
	{
		// フェードの色が０(黒)であれり次のフェーズフラグがONであれば
		CManager::SetMode(CManager::MODE_TUTORIAL);		// ゲーム画面に遷移
	}

}

//=============================================================================
// 関数名	: 
// 戻り値	:
// 引数		:
// 機能		: 描画
//=============================================================================
void CTitle::Draw(void)
{
	CScene::DrawAll();
}
