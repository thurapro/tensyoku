/*-----------------------------------------------------------------------------
/ another : Yuta Matsuo
/
/ 譜面表示クラス
-----------------------------------------------------------------------------*/
#ifndef _MARKERBUTTON_H_
#define _MARKERBUTTON_H_

//=============================================================================
// インクルード
//=============================================================================
#include "Node.h"
#include "../DirectXTK/Inc/SimpleMath.h"


//=============================================================================
// クラス宣言
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
		TOKEN_0 = 0,	// 全音符	( 4拍[1小節] )
		TOKEN_2 = 2,	// 2分音符	( 2拍 )
		TOKEN_4 = 4,	// 4分音符	( 1拍 )
		TOKEN_8 = 8,	// 8分音符	( 0.5拍 )
		TOKEN_16 = 16,	// 16分音符	( 0.25拍 )
		TOKEN_UNKNOWN
	}TOKEN_TYPE;

	CMarkerButton();									// インスタンス生成
	~CMarkerButton();								// インスタンス破棄
	void Init(char TokenType, bool ScoreType, char ButtonType, int CountToken);		// ボタンテクスチャ初期化
	void Update();									// ボタンス更新
	void Draw();									// 描画;
	DirectX::SimpleMath::Vector3 *GetPosition();	
	bool GetAlive(){ return m_Alive; }
	bool GetSuccess(){ return m_success; }
	static void SetBpm(float BPM);

	static float m_speedTimes;			// 何倍速なのか


private:
	bool Collision(DirectX::SimpleMath::Vector3 MarkerPos,
		DirectX::SimpleMath::Vector2 MarkerScl,
		DirectX::SimpleMath::Vector3 ColPos,
		DirectX::SimpleMath::Vector2 ColScl);		// 判定ラインとボタンの当たり判定

	void SetButton(char ButtonType);				// ボタン種類設定
	void SetToken(char TokenType, int CountToken);	// 音符種類設定
	std::string GetButtonName(){ return m_Name; }

	DirectX::SimpleMath::Vector3 *m_speed;		// 移動速度
	DirectX::SimpleMath::Vector3 *m_pos;		// 位置
	DirectX::SimpleMath::Vector2 *m_scl;		// 大きさ
	DirectX::SimpleMath::Vector2 *m_colscl;		// 当たり判定の大きさ
	
	static float m_BPM;							

	BUTTON m_ButtonType;							// ボタンの種類
	TOKEN_TYPE m_TokenType;							// 音符の種類
	wchar_t *m_ButtonSprite;						// ボタンの画像
	static int m_TokenNum;							// 現在何個目なのか
	int m_Index;									// 自分の番号
	char m_Name[5];
	bool m_push;
	bool m_Alive;
	bool *m_ChildAlive;
	int m_nScoreSum;
	bool m_col;
	bool m_releas;
	bool m_success;									// 判定成功
};

#endif // _MARKERBUTTON_H_




