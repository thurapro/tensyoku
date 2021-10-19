//=============================================================================
// スコア処理[score.h]
//
// 製作者 : 松尾 雄太
//
// 機能 :  スコアー
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "number.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2Dテクスチャー設定
#define MAX_SCORE			(3)

//=============================================================================
// クラス宣言
//=============================================================================
class CScore : public CScene2D
{
public:
	CScore(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);								// スコアインスタンス生成
	~CScore(void);								// スコアインスタンス破棄

	static CScore *CScore::Create(float fPosX, float fWidth, float fPosY, 
									float fHeight, unsigned int nTexNum);	// スコアー作成
	HRESULT CScore::Init(void);					// 初期化
	HRESULT Init(float fPosX, float fWidth, float fPosY, 
					float fHeight, unsigned int nTexNum);	// 初期化
	void Uninit(void);										// スコア終了処理
	void Update(void);										// スコア更新処理
	void Draw(void);										// スコア描画処理
	
	// テクスチャ座標位置セット 
	void SetScore(unsigned nNumber);
	unsigned int GetScore(void){return m_nScore;}	// スコア何番
private:
	unsigned int m_nScore;						// スコア
	CNumber	*m_pNumber[MAX_SCORE];				// スコアの番号
	unsigned int m_nTexNum;						// テクスチャ番号
};

#endif // _SCORE_H_