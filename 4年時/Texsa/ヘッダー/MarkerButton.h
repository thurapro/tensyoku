/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ ���ʕ\���N���X
-----------------------------------------------------------------------------*/
#ifndef _MARKERBUTTON_H_
#define _MARKERBUTTON_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Node.h"
#include "../DirectXTK/Inc/SimpleMath.h"


//=============================================================================
// �N���X�錾
//=============================================================================
class CMarkerButton :public MeekH::Node{
public:
	typedef enum
	{
		BUTTON_LEFT = 0x0001,
		BUTTON_RIGHT = 0x0002,
		BUTTON_DOWN = 0x0004,
		BUTTON_UP = 0x0008,
		BUTTON_PLUS = 0x0010,
		BUTTON_TWO = 0x0100,
		BUTTON_ONE = 0x0200,
		BUTTON_B = 0x0400,
		BUTTON_A = 0x0800,
		BUTTON_MINUS = 0x1000,
		BUTTON_HOME = 0x8000,
		BUTTON_ACCEL = 1
	}BUTTON;

	typedef enum
	{
		TOKEN_0 = 0,	// �S����	( 4��[1����] )
		TOKEN_2 = 2,	// 2������	( 2�� )
		TOKEN_4 = 4,	// 4������	( 1�� )
		TOKEN_8 = 8,	// 8������	( 0.5�� )
		TOKEN_16 = 16,	// 16������	( 0.25�� )
		TOKEN_UNKNOWN
	}TOKEN_TYPE;

	CMarkerButton();									// �C���X�^���X����
	~CMarkerButton();								// �C���X�^���X�j��
	void Init(char TokenType, bool ScoreType, char ButtonType, int CountToken);		// �{�^���e�N�X�`��������
	void Update();									// �{�^���X�X�V
	void Draw();									// �`��;
	DirectX::SimpleMath::Vector3 *GetPosition();	
	bool GetAlive(){ return m_Alive; }
	bool GetSuccess(){ return m_success; }
	static void SetBpm(float BPM);

	static float m_speedTimes;			// ���{���Ȃ̂�


private:
	bool Collision(DirectX::SimpleMath::Vector3 MarkerPos,
		DirectX::SimpleMath::Vector2 MarkerScl,
		DirectX::SimpleMath::Vector3 ColPos,
		DirectX::SimpleMath::Vector2 ColScl);		// ���胉�C���ƃ{�^���̓����蔻��

	void SetButton(char ButtonType);				// �{�^����ސݒ�
	void SetToken(char TokenType, int CountToken);	// ������ސݒ�
	std::string GetButtonName(){ return m_Name; }

	DirectX::SimpleMath::Vector3 *m_speed;		// �ړ����x
	DirectX::SimpleMath::Vector3 *m_pos;		// �ʒu
	DirectX::SimpleMath::Vector2 *m_scl;		// �傫��
	DirectX::SimpleMath::Vector2 *m_colscl;		// �����蔻��̑傫��
	
	static float m_BPM;							

	BUTTON m_ButtonType;							// �{�^���̎��
	TOKEN_TYPE m_TokenType;							// �����̎��
	wchar_t *m_ButtonSprite;						// �{�^���̉摜
	static int m_TokenNum;							// ���݉��ڂȂ̂�
	int m_Index;									// �����̔ԍ�
	char m_Name[5];
	bool m_push;
	bool m_Alive;
	bool *m_ChildAlive;
	int m_nScoreSum;
	bool m_col;
	bool m_releas;
	bool m_success;									// ���萬��
};

#endif // _MARKERBUTTON_H_




