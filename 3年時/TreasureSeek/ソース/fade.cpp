//=============================================================================
// フェード処理 [ fade.h ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: フェード処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//=============================================================================
// 関数名	: CFade
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス生成		( 初期化 )
//=============================================================================
CFade::CFade(void)
{
	m_pVertexBuffer = NULL;				// 頂点バッファ初期化
	m_fadeMode		= FADEMODE_IN;		// フェードモード初期化
	m_nTime			= 0;				// フェードの時間
	m_nTimeCnt		= 0;				// 時間カウント
	m_nRed			= 0;				// 赤値初期化
	m_nGreen		= 0;				// 緑値初期化
	m_nBlue			= 0;				// 青値初期化
	m_nAlpha		= 255;				// アルファー値初期化
}

//=============================================================================
// 関数名	: ~CFade
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄		( 終了 )
//=============================================================================
CFade::~CFade(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: CFade		( 失敗　NULL )
// 引数値	: 何秒でフェードするか
// 機能		: フェード作成
//=============================================================================
CFade *CFade::Create(unsigned int nTime)
{
	HRESULT hr;					// エラーチェック
	CFade	*pFade = NULL;		// フェードポインタ
	if( pFade == NULL )
	{
		// フェードが作成されていなければ
		pFade = NEW CFade;			// フェードインスタンス生成
		hr = pFade->Init(nTime);	// フェード初期化
		if( FAILED(hr) )
		{
			// フェード初期化に問題あり
			return NULL;			// エラーコード
		}
	}
	return pFade;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数値	: 何秒でフェードするか
// 機能		: フェード初期化
//=============================================================================
HRESULT CFade::Init(unsigned int nTime)
{
	HRESULT hr;			// エラーチェック変数
	m_nTime = nTime;	// 時間を保存
	
	m_fadeMode = FADEMODE_IN;	// フェードモード設定 
	
	// 頂点作成
	hr = MakeVerTex();	// 頂点作成
	ERROR_CHACK(hr);	// エラーチェック
	return S_OK;		// 正常コード
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: フェード終了
//=============================================================================
void CFade::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// 頂点バッファ破棄
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数値	: なし
// 機能		: フェードイン , フェードアウト 更新
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	switch( m_fadeMode )
	{
	case FADEMODE_IN:			// フェードイン
		m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);							// 頂点ロック
		pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		m_pVertexBuffer->Unlock();												// 頂点アンロック
		if( m_nAlpha <= 0 )
		{
			// アルファー値が0以下になったら
			m_nAlpha		= 0;
			m_fadeMode = FADEMODE_NONE;			// フェードモードをNONEに変更
		}
		else
		{
			// アルファー値が0より大きければ
			if( m_nTimeCnt >= m_nTime )
			{
				// 設定された時間を超えていれば
				m_nAlpha	-= 5;
				m_nTimeCnt	= 0;					// タイマーカウントを０へ
			}
			else
			{
				// 設定された時間を超えていなければ
				m_nTimeCnt++;					// タイマーカウントを上げる
			}
		}
		break;

	case FADEMODE_OUT:		// フェードアウト
		m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);							// 頂点ロック
		pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// 頂点色変更
		m_pVertexBuffer->Unlock();
		if( m_nAlpha >= 255 )
		{
			// アルファー値が0以下になったら
			m_nAlpha		= 255;
			m_fadeMode = FADEMODE_NONE;			// フェードモードをNONEに変更
		}
		else
		{
			// アルファー値が0より大きければ
			if( m_nTimeCnt > m_nTime )
			{
				// 設定された時間を超えていれば
				m_nAlpha	+= 5;
				m_nTimeCnt = 0;					// タイマーカウントを０へ
			}
			else
			{
				// 設定された時間を超えていなければ
				m_nTimeCnt++;					// タイマーカウントを上げる
			}
		}
		break;
	case FADEMODE_NONE:							// フェードモードNONE
		break;									// 処理なし
	default:									// それ以外
		break;									// 処理なし
	}
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: フェード描画
//=============================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点フォーマットをセット
	pDevice->SetFVF(FVF_VERTEX_2D_FADE);
	
	// 頂点バッファーのセット
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
		
	// テクスチャーセット
	pDevice->SetTexture(0, NULL);

	// プリミティブ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 関数名	: MakeVerTex
// 戻り値	: なし
// 引数値	: なし
// 機能		: フェード頂点作成
//=============================================================================
void CFade::SetFadeMode(FADEMODE fadeMode)
{
	m_fadeMode = fadeMode;
}

//=============================================================================
// 関数名	: MakeVerTex
// 戻り値	: なし
// 引数値	: なし
// 機能		: フェード頂点作成
//=============================================================================
HRESULT CFade::MakeVerTex(void)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファー作成
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_FADE,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// 作成できなかったら
	if(FAILED(hr))
	{
		return hr;
	}

	// 頂点バッファーロック
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// 頂点バッファー位置セット
	pVtx[0].vtx = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pVtx[1].vtx = D3DXVECTOR3( (float)WINDOW_WIDTH, 0.0f, 0.0f );
	pVtx[2].vtx = D3DXVECTOR3( 0.0f, (float)WINDOW_HEIGHT, 0.0f );
	pVtx[3].vtx = D3DXVECTOR3( (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
	
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色情報
	pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	// ロック解除
	hr = m_pVertexBuffer->Unlock();	
	ERROR_CHACK(hr);	// エラーチェック
	return S_OK;
}


// end of file //