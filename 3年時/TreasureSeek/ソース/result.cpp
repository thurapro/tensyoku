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
#include "data.h"
#include "manager.h"
#include "scene2D.h"
#include "timer.h"
#include "renderer.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "result.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RESULT ("./DATA/TEXT/result.txt")

//=============================================================================
// 静的メンバ変数
//=============================================================================
CData		*CResult::m_pData;							// データの実体生成
CScene2D	*CResult::m_pTitleScene;					// タイトル画像

//=============================================================================
// 関数名	: CResult
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス生成
//=============================================================================
CResult::CResult(void)
{
	m_pData			= NULL;		// データ初期化
	m_pTitleScene	= NULL;		// タイトル画像
	m_pTimer		= NULL;		// タイマー
	m_bFace			= false;	// 次のモード移動フラグ
}

//=============================================================================
// 関数名	: ~CResult
// 戻り値	: なし
// 引数		: なし
// 機能		: ゲームインスタンス破棄
//=============================================================================
CResult::~CResult(void)
{
	// なし
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: ウィンドウハンドル
// 機能		: 初期化
//=============================================================================
HRESULT CResult::Init(HWND hWnd)
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

	if( m_pData == NULL )
	{
		// データが作成されていなければ
		m_pData = NEW CData;				// データインスタンス生成
		hr = m_pData->Init(hWnd, RESULT);	// データ初期化
		ERROR_CHACK(hr);					// データが作成されているか
	}

	m_pTitleScene = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if( m_pTitleScene == NULL )
	{
		return E_FAIL;
	}

	m_pTimer = CTimer::Create(100, 100, 100, 100, 1);
	if( m_pTimer == NULL )
	{
		return E_FAIL;
	}

	CNumber **pNumber = m_pTimer->GetNumber();
	for(int i = 0; i < MAX_TIMER; i++ )
	{
		pNumber[i]->SetNumColor(0, 0, 0, 255);
	}

	m_pTimer->SetTimer( CManager::GetRankScore() );

	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: 終了
//=============================================================================
void CResult::Uninit(void)
{
	// メモリの開放
	CScene::ReleaseAll();		// シーン破棄
	CLASS_DELETE(m_pData);		// データ破棄
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: 更新
//=============================================================================
void CResult::Update(void)
{
	int nColor = CManager::GetFade()->GetColor();					// フェードの色取得

	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE )
	{
		// フェードが行われていなければ
		if( CManager::GetInput()->KeyPush(DIK_RETURN) )
		{
			m_bFace = true;									// 移動フラグON
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// フェード設定
		}
	}

	// 画面遷移処理
	if( nColor >= 255 && m_bFace == true )
	{
		// フェードの色が0(黒)で次のフェーズ移動フラグがONであれば
		CManager::SetMode(CManager::MODE_RANKING);			// リザルトヘ移行
	}
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: 描画
//=============================================================================
void CResult::Draw(void)
{
	CScene::DrawAll();
}
