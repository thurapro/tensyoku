/******************************************************************************
/ 敵管理処理 [enemyManager.h]
/ 
/ 制作者 : 松尾 雄太
/
/ 制作日 : 2014年1月
******************************************************************************/

//============================================================================
// 2重インクルード
//============================================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

/*****************************************************************************
/ インクルード
*****************************************************************************/
#include "sceneModelGL.h"
#include "vector3D.h"
#include "enemy.h"

/*****************************************************************************
/ クラス宣言
*****************************************************************************/
class CEnemyManager
{
public:

	static CEnemyManager *Create();	// 敵マネージャ生成
	static void Release();			// 敵マネージャ破棄
	void Init(void);				// 初期化
	void UnInit(void);				// 終了
	void UpDate(void);				// 更新

	static CEnemyManager *GetInstance(void)
	{
		return m_pInstance;			// インスタンス取得
	}

	void CountEnemy( int nEnemy );			// 生成した敵の数を数える

private:	
	CEnemyManager(void);					// コンストラクタ
	~CEnemyManager(void);					// デストラクタ

	static CEnemyManager *m_pInstance;		// 自身のポインタ
	void			SetTimeRandom(CEnemy::TYPE type);	// 敵の出現時間設定
	int				m_nTime;				// マネージャー時間 ( 全体の時間 )
	int				m_nAlphaTime;			// アルファ出現時間
	int				m_nBetaTime;			// ベータ出現時間
	int				m_nGammaTime;			// ガンマ出現時間
	int				m_nDeltaTime;			// デルタ出現時間
};

#endif //_ENEMYMANAGER_H_

// EOF
