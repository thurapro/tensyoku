//-----------------------------------------------------------------------------
//
// player処理 クラス		[player.h]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2重インクルード防止
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "object.h"
#include "CScreen.h"
#include "common.h"
#include "main.h"

//-----------------------------------------------------------------------------
// プレイヤークラス 派生クラス名 : アクセス指定子 基本クラス名
//-----------------------------------------------------------------------------
class CPlayer : public CObject
{
public:
	CPlayer();											// コンストラクタ
	~CPlayer();											// デストラクタ
	void Init(float fPosX, float fPosY);				// プレイヤーの位置初期化
	void Uninit(void);									// 終了処理
	void Update(void);									// プレイヤーの更新
	void Draw(void);									// プレイヤーの描画
	void GetPos(float *pPosX, float *pPosY){*pPosX = m_fPosX; *pPosY = m_fPosY;}		// プレイヤーの位置
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// 爆発の位置取得
	static CPlayer *Create(float fPosX, float fPosY);	// プレイヤーの生成
private:
	float m_fPosX;										// プレイヤーのX座標
	float m_fPosY;										// プレイヤーのY座標
	float m_fPosXOld;									// プレイヤーの前にいたX座標
	float m_fPosYOld;									// プレイヤーの前にきたY座標
	float m_fMoveX;										// プレイヤーのx移動量
	float m_fMoveY;										// プレイヤーのy移動量
	bool m_bMove;										// プレイヤーが移動したかしてないか
};

#endif //_PLAYER_H_
