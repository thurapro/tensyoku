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
#include "scene.h"
#include "scene2D.h"
#include "number.h"
#include "data.h"
#include "timer.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "game.h"

#include "ranking.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RANKING ("data/text/ranking.txt")

//=============================================================================
// 静的メンバ変数
//=============================================================================
CData		*CRanking::m_pData;							// データの実体生成

//=============================================================================
// 関数名	: CRanking
// 戻り値	: なし
// 引数		: なし
// 機能		: ランキングインスタンス生成
//=============================================================================
CRanking::CRanking(void)
{
	m_pData			= NULL;							// データ初期化
	m_pRankBack		= NULL;							// ランキング背景
	ZeroMemory(m_pRanking, sizeof(m_pRanking) );	// ランキング初期化
	for( int i = 0; i < MAX_RANKING; i++ )
	{
		m_nNumber[i] = 100;
	}
	m_bFace			= false;						// 次のモード移動フラグ
}

//=============================================================================
// 関数名	: ~CRanking
// 戻り値	: なし
// 引数		: なし
// 機能		: ランキングインスタンス破棄
//=============================================================================
CRanking::~CRanking(void)
{
	// なし
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: ウィンドウハンドル
// 機能		: 初期化
//=============================================================================
HRESULT CRanking::Init(HWND hWnd)
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
		hr = m_pData->Init(hWnd, RANKING);	// データ初期化
		ERROR_CHACK(hr);					// データが作成されているか
	}

	m_pRankBack = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if( m_pRankBack == NULL )
	{
		return E_FAIL;
	}

	m_pRanking[0] = CTimer::Create(WINDOW_WIDTH / 2, 30, 10, 60, 1);
	m_pRanking[1] = CTimer::Create(WINDOW_WIDTH / 2, 30, 100, 60, 1);
	m_pRanking[2] = CTimer::Create(WINDOW_WIDTH / 2, 30, 190, 60, 1);
	m_pRanking[3] = CTimer::Create(WINDOW_WIDTH / 2, 30, 280, 60, 1);
	m_pRanking[4] = CTimer::Create(WINDOW_WIDTH / 2, 30, 370, 60, 1);

	int nCurRankData = CManager::GetRankScore();

	for(int i = 0; i < MAX_RANKING; i++ )
	{
		// 大小確認
		if( nCurRankData < m_nNumber[i] )
		{
			// 小さい場合はスコアをずらす
			for( int n = (MAX_RANKING - 1); n > i; n-- )
			{
				m_nNumber[n] = m_nNumber[n - 1]; 
			}
			m_nNumber[i] = nCurRankData;
			break;
		}
	}

	FILE *fp;
	fopen_s(&fp, "data/text/ranking/rankdata.txt", "w+");
	
	for( int i = 0; i < MAX_RANKING; i++ )
	{
		m_pRanking[i]->SetTimer(m_nNumber[i]);
		fprintf(fp, "%d\n", m_nNumber[i]);
	}

	fclose(fp);

	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: 終了
//=============================================================================
void CRanking::Uninit(void)
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
void CRanking::Update(void)
{
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
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE && m_bFace == true )
	{
		// フェードの色が0(黒)で次のフェーズ移動フラグがONであれば
		CManager::SetMode(CManager::MODE_LOGO);			// リザルトヘ移行
	}
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: 描画
//=============================================================================
void CRanking::Draw(void)
{
	CScene::DrawAll();
}
