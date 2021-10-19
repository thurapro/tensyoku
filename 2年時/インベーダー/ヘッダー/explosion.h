//-----------------------------------------------------------------------------
//
// 爆発処理 クラス		[explosion.h]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2重インクルード防止
//-----------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "object.h"

//-----------------------------------------------------------------------------
// 爆発のクラス
//-----------------------------------------------------------------------------
class CExplosion : public CObject
{
public:
	typedef enum
	{
		STAR = 0,
		SQUARE,
		CIRCLE,
	};
	CExplosion(void);																// 爆発の生成
	~CExplosion(void);																// 爆発の破棄
	void Init(float fPosX, float fPosY);											// 爆発の初期化
	void Uninit(void);																// 爆発の破棄
	void Update(void);																// 爆発の更新
	void Draw(void);																// 爆発の描画
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// 爆発の位置取得
	static CExplosion *Create(float fPosX, float fPosY);							// 爆発の生成
private:
	float m_fPosX;																	// 爆発の現在位置X
	float m_fPosY;																	// 爆発の現在位置Y
	float m_fPosXOld;																// 爆発の元いた位置X
	float m_fPosYOld;																// 爆発の元いた位置Y
	int	m_nTime;																	// 爆発時間
	int m_nSelect;																	// 爆発の種類
	float m_fMoveX;																	// 爆発の速度X
	float m_fMoveY;																	// 爆発の速度Y
};

#endif // BULLET
