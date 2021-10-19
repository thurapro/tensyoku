//-----------------------------------------------------------------------------
//
// 敵処理 クラス		[enemy.h]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2重インクルード防止
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "object.h"
#include "common.h"
#include "bullet.h"

//-----------------------------------------------------------------------------
// 敵クラス
//-----------------------------------------------------------------------------
class CEnemy : public CObject
{
public:
	CEnemy(void);																// コンストラクタ
	~CEnemy(void);																// デストラクタ
	void Init(float fPosX, float fPosY);										// 敵の初期化
	void Uninit(void);															// 敵の破棄
	void Update(void);															// 敵の更新
	void Draw(void);															// 敵の描画
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// 爆発の位置取得
	static void GetNum(int *nCnt){*nCnt = m_nNumCnt;}
	static CEnemy *Create(float fPosX, float fPosY);							// 敵の作成
private:
	float m_fPosX;																// 敵のポジションX
	float m_fPosY;																// 敵のポジションY
	float m_fPosXOld;															// 敵の前にいた座標X
	float m_fPosYOld;															// 敵の前にいた座標Y
	float m_fMoveX;																// 敵の速度X方向 
	float m_fMoveY;																// 敵の速度Y方向
	bool m_bAlive;																// 敵が倒されたか
	int m_nShotTime;															// 弾を打つ間隔
	static int m_nNumCnt;														// 敵の数
};
#endif // _ENEMY_H_


