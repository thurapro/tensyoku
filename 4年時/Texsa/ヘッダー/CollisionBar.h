/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ ������o�[�\���N���X
-----------------------------------------------------------------------------*/
#ifndef _COLLISIONBAR_H_
#define _COLLISIONBAR_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <Node.h>

//=============================================================================
// �O���Q��
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
// �N���X�錾
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