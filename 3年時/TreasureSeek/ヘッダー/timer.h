//=============================================================================
// 時間処理[timer.h]
//
// 製作者 : 松尾 雄太
//
// 機能 :  タイマー
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "number.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2Dテクスチャー設定
#define MAX_TIMER			(3)											// 桁数(百秒)
#define MAX_TIME_COUNT		(16)										// 1秒に変換

//=============================================================================
// クラス宣言
//=============================================================================
class CTimer : public CScene2D
{
public:
	CTimer(void);								// スコアインスタンス生成
	~CTimer(void);								// スコアインスタンス破棄

	HRESULT CTimer::Init(void);					// 初期化

	// スコア初期化処理 オーバーロード
	HRESULT Init(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum);
	void Uninit(void);							// スコア終了処理
	void Update(void);							// スコア更新処理
	void Draw(void);							// スコア描画処理
	static CTimer *CTimer::Create(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum);
	unsigned int GetTime(void){return m_nTime;}
	CNumber  **GetNumber(void){return &m_pNumber[0];}
	
	// テクスチャ座標位置セット 
	void SetTimer(unsigned nNumber);
private:
	CNumber				*m_pNumber[MAX_TIMER];			// スコアの番号
	unsigned int		m_nTimerCnt;					// 1秒間に変更
	unsigned int		m_nTime;						// 時間
	unsigned int		m_nTexNum;						// テクスチャ番号	
};

#endif // _TIMER_H