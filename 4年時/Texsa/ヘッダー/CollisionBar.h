/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ 当たりバー表示クラス
-----------------------------------------------------------------------------*/
#ifndef _COLLISIONBAR_H_
#define _COLLISIONBAR_H_

//=============================================================================
// インクルード
//=============================================================================
#include <Node.h>

//=============================================================================
// 前方参照
//=============================================================================
namespace DirectX
{
	namespace SimpleMath
	{
		struct Vector2;
		struct Vector3;
	}
}

//=============================================================================
// クラス宣言
//=============================================================================
class CollisionBar:public MeekH::Node{
public:
	CollisionBar();
	~CollisionBar();
	void Init();
	void Update();
	
	DirectX::SimpleMath::Vector3 GetPos();
	DirectX::SimpleMath::Vector2 GetScl();

private:
	DirectX::SimpleMath::Vector3 *m_pos;
	DirectX::SimpleMath::Vector2 *m_scl;
};

#endif // _COLLISIONBAR_H_