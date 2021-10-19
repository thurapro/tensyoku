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
#include "data.h"
#include "game.h"
#include "score.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority, OBJTYPE objType):CScene2D(nPriority, objType)
{
	// 各メンバ変数初期化

	ZeroMemory(m_pNumber, sizeof(m_pNumber) );		// 番号を桁数だけNULL初期化
	m_pVertexBuffer = NULL;							// 頂点バッファをNULL初期化
	m_nScore = 0;									// スコア初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore(void)
{
	// なし
}

//=============================================================================
// スコアーを作成
//=============================================================================
CScore *CScore::Create(float fPosX, float fWidth, float fPosY, 
						float fHeight, unsigned int nTexNum)
{
	HRESULT hr;
	CScore *pScore;
	pScore = NEW CScore;
	hr = pScore->Init(fPosX, fWidth, fPosY, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return NULL;
	}
	else
	{
		return pScore;
	}
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CScore::Init(void)
{	
	return S_OK;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CScore::Init(float fPosX, float fWidth, float fPosY, 
						float fHeight, unsigned int nTexNum)
{
	CTexture *pTex = CGame::GetData()->GetTexture();		// ゲームで使われる画像取得

	// 画像を読み込み
	m_pTexture = NULL;										// テクスチャNULL初期化

	D3DXVECTOR3 Pos[4];
	float PosX = fPosX;
	float Width = fWidth;
	float PosY = fPosY;
	float Height = fHeight;
	float fMinPosX[MAX_SCORE];
	float fMin = fPosX;
	float fMaxPosX[MAX_SCORE];
	float fMax = fPosX + fWidth;

	for( int i = 0; i < MAX_SCORE; i++ )
	{
		fMinPosX[i] = fMin;
		fMaxPosX[i] = fMax;
		fMin = fMaxPosX[i];
		fMax += Width;
	}

	for( int nScore = 0; nScore < MAX_SCORE; nScore++ )
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
				PosY = fHeight;
			}
			else
			{
				PosY = fPosY;
			}
		}
		PosX = fMaxPosX[nScore];
		PosY = fPosY;

		m_pNumber[nScore] = CNumber::Create(Pos[0], Pos[1], Pos[2], Pos[3], nTexNum);
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
void CScore::Uninit(void)
{
	// 2Dオブジェクト破棄
	CScene2D::Uninit();
	
	for( int i = 0; i < MAX_SCORE; i++ )
	{
		if(m_pNumber[i] != NULL )
		{	
			// スコアーに使った番号破棄
			m_pNumber[i]->Uninit();			// 番号破棄
			m_pNumber[i] = NULL;			// 番号の変数をNULLへ
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for( int i = 0; i < MAX_SCORE; i++ )
	{
		// 桁数だけ描画
		m_pNumber[i]->Draw();		// 番号を描画
	}
}

//=============================================================================
// スコアーセット
//=============================================================================
void CScore::SetScore( unsigned int nNumber )
{
	m_nScore += nNumber;						// スコアを加点 
	int Num = 0;								// 桁を取り出す処理
	int Ket = m_nScore;							// 今指定している数
	for( int i = MAX_SCORE - 1; i >= 0; i-- )
	{	
   		Num = Ket % 10;							// 0～9までの番号を取り出す
		Ket = Ket / 10;							// 桁数を取り出し
		m_pNumber[i]->SetNumberTexture( Num );	// 番号をセット
	}
}


