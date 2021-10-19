/*****************************************************************************
/ インクルード
*****************************************************************************/
#include "enemy.h"

/*****************************************************************************
/ クラス宣言
*****************************************************************************/
class CEnemyGamma : public CEnemy
{
public:
	CEnemyGamma(void);			// コンストラクタ
	void Init(void){}			// 初期化

	static CEnemyGamma *Create( VECTOR3D pos, const char *tex);		// 敵生成

	void Init( VECTOR3D pos, const char *tex);		// 初期化
	void UpDate(void);			// 更新
	void Draw(void);			// 描画

private:
	float m_fAngle;				// 回転角度

};