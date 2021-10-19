//=============================================================================
// 描画処理 [scene.cpp]
//
// 製作者	: 松尾 雄太
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "number.h"
#include "Timer.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CTimer::CTimer(void)
{
	// 各メンバ変数初期化
	ZeroMemory(m_pNumber, sizeof(m_pNumber) );		// 番号を桁数だけNULL初期化
	m_pVertexBuffer = NULL;							// 頂点バッファをNULL初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CTimer::~CTimer(void)
{
	// なし
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTimer::Init(void)
{	
	return S_OK;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTimer::Init(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum)
{
	// 画像を読み込み
	m_pTexture = NULL;							// テクスチャNULL初期化
	m_nTimerCnt = 0;							// 時間を1秒に変換	
	m_nTime = 0;								// 現在の時間

	m_nTexNum = nTexNum;						//　テクスチャ番号

	
	//CTexture *pTex = CGame::GetData()->GetTexture();		// ゲームで使われる画像取得

	//int  i	=  pTex->GetTextureNum();
	//if( pTex->GetTextureNum() < m_nTexNum ||
	//	m_nTexNum < 0 )
	//{
	//	return E_FAIL;
	//}

	D3DXVECTOR3 Pos[4];
	float PosX = fPosX;
	float Width = fWidth;
	float PosY = fPosY;
	float Height = fPosY + fHeight;
	float fMinPosX[MAX_TIMER];
	float fMin = fPosX;
	float fMaxPosX[MAX_TIMER];
	float fMax = fPosX + fWidth;

	for( int i = 0; i < MAX_TIMER; i++ )
	{
		fMinPosX[i] = fMin;
		fMaxPosX[i] = fMax;
		fMin = fMaxPosX[i];
		fMax += Width;
	}

	for( int nScore = 0; nScore < MAX_TIMER; nScore++ )
	{
		for( int pos = 0; pos < 4; pos++)
		{
		
			Pos[pos] = D3DXVECTOR3(PosX, PosY, 0.0f);
			if( PosX >= fMaxPosX[nScore] )
			{
				PosX = fMinPosX[nScore];
			}
			else
			{
				PosX += Width;
			}
			if( pos > 0)
			{
				PosY = Height;
			}
			else
			{
				PosY = fPosY;
			}
		}
		PosX = fMaxPosX[nScore];
		PosY = fPosY;

		m_pNumber[nScore] = CNumber::Create(Pos[0], Pos[1], Pos[2], Pos[3], m_nTexNum);
		if( m_pNumber == NULL )
		{
			return E_FAIL;
		}
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	// 2Dオブジェクト破棄
	CScene2D::Uninit();
	
	for( int i = 0; i < MAX_TIMER; i++ )
	{
		if(m_pNumber[i] != NULL )
		{	
			// タイマーに使った番号破棄
			m_pNumber[i]->Uninit();			// 番号破棄
			m_pNumber[i] = NULL;			// 番号の変数をNULLへ
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTimer::Update(void)
{
	m_nTimerCnt++;
	if( m_nTimerCnt % 60 == 0 )
	{
		m_nTime++;
		m_nTimerCnt = 0;
	}
	
	SetTimer(m_nTime);
}

//=============================================================================
// 描画処理
//=============================================================================
void CTimer::Draw(void)
{
	for( int i = 0; i < MAX_TIMER; i++ )
	{
		// 桁数だけ描画
		m_pNumber[i]->Draw();		// 番号を描画
	}
}

//=============================================================================
// タイマーセット
//=============================================================================
void CTimer::SetTimer( unsigned int nNumber )
{
	int Num = 0;								// 桁を取り出す処理
	int Ket = nNumber;							// 今指定している数
	for( int i = MAX_TIMER - 1; i >= 0; i-- )
	{	
   		Num = Ket % 10;							// 0～9までの番号を取り出す
		Ket = Ket / 10;							// 桁数を取り出し
		m_pNumber[i]->SetNumberTexture( Num );	// 番号をセット
	}
}

//=============================================================================
// タイマーを作成
//=============================================================================
CTimer *CTimer::Create(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum)
{
	HRESULT hr;
	CTimer *pTimer;
	pTimer = NEW CTimer;
	hr = pTimer->Init(fPosX, fWidth, fPosY, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return NULL;
	}
	else
	{
		return pTimer;
	}
}

