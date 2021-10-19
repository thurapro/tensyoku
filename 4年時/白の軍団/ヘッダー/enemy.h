/******************************************************************************
/ 敵処理 [ enemy.h ]
/
/ 作成者 : 松尾 雄太
/
/ 作成日 : 2014/02/10 @matsuo
/*****************************************************************************/

/*****************************************************************************
	2重インクルード防止
******************************************************************************/
#ifndef _ENEMY_H_
#define _ENEMY_H_

/*****************************************************************************
	インクルード
*****************************************************************************/
#include "sceneModelGL.h"
#include "collision.h"
#include "DebugProc.h"
#include "score.h"
#include "cphaseMain.h"
#include "player.h"
#include "sceneExplosion.h"

/*****************************************************************************
	前方参照
*****************************************************************************/	

/*****************************************************************************
	クラス宣言
*****************************************************************************/
class CEnemy : public CSceneModelGL
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ALPHA,			// 左右移動
		TYPE_BETA,			// 回転しながら移動
		TYPE_GAMMA,			// 追尾
		TYPE_DELTA,			// 左右移動
		TYPE_MAX
	}TYPE;					// 敵の種類

	static CEnemy *Create(TYPE typeEnemy, VECTOR3D pos);	// 敵の生成 
	CEnemy(void);					// 敵インスタンス生成
	virtual ~CEnemy(void)
	{
		if( m_pCollision )
		{	
			m_pCollision->Release();
			m_pCollision = NULL;
		}
	}								// 敵インスタンス破棄
	void Init(){};					// 敵初期化
	virtual void UnInit(void){};	// 敵終了

	virtual void UpDate(void) = 0;		// 敵更新
	virtual void Draw(void) = 0;		// 敵描画

	virtual void OnHit( int tag, COLDETAIL detail, COLSTATUS colStatus )
	{
		switch( colStatus.colType )
		{
		case COL_TYPE_PLAYER:
			{
				colStatus.damage = 30;
				int nScore = CPhaseMain::GetScore()->GetScore();
				nScore -= colStatus.damage;
				CPhaseMain::GetScore()->SetScore(nScore);
				break;
			}
		case COL_TYPE_PLBULLET:
			{
				// 仮ダメージ
				colStatus.damage = 1;

				m_nHP -= colStatus.damage;
				if( m_nHP < 1 )
				{
					CSceneExplosionGL::Create( 1.0f, 8.0f, 8.0f, m_pos.x, m_pos.y, m_pos.z );
					Release();
				}
				break;
			}
		}
	}

protected:
	CCollision*	m_pCollision;	// 衝突クラス
	int		m_nHP;				// 敵体力
	int		m_nAttack;			// 敵攻撃力
	float	m_nStopTime;		// 敵の停止時間

private:
};


#endif // _ENEMY_H_