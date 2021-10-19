//=============================================================================
// file : WiiController.h
//
// another : Yuta Matsuo 
//
//
// 機能説明 : Wiiリモコン操作 
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _WIICONTROLLER_H_
#define _WIICONTROLLER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "wii\wiimote.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CWiiController : public wiimote
{
public:

	CWiiController();
	~CWiiController();

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
	}BUTTON;

	/*-----------------------------------------
	/ void Create
	/
	/ 戻り値	: なし
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコンの生成、初期化
	-----------------------------------------*/
	static	void Create(int i);

	/*-----------------------------------------
	/ void Uninit
	/
	/ 戻り値	: なし
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコン破棄
	-----------------------------------------*/
	static void	Uninit(int i);

	/*-----------------------------------------
	/ void Update
	/
	/ 戻り値	: なし
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコン更新
	-----------------------------------------*/
	void	Update();

	/*-----------------------------------------
	/ CWiiController GetInstance
	/
	/ 戻り値	: なし
	/
	/ 引数		: wiiのインスタンス
	/
	/ 機能		: wiiのインスタンス取得
	-----------------------------------------*/
	static CWiiController *GetInstance(int i);

	/*-----------------------------------------
	/ void Push
	/
	/ 戻り値	: なし
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコンが押されている間
	-----------------------------------------*/
	bool Push(BUTTON Button);

	/*-----------------------------------------
	/ void Release
	/
	/ 戻り値	: 押されたのか
	/
	/ 引数		: ボタン指定
	/
	/ 機能		: wiiリモコンが離した瞬間
	-----------------------------------------*/
	bool	Release(BUTTON Button);

	/*-----------------------------------------
	/ void Trigger
	/
	/ 戻り値	: 押されたのか
	/
	/ 引数		: ボタン指定
	/
	/ 機能		: wiiリモコンが押した瞬間
	-----------------------------------------*/
	bool	Trigger(BUTTON Button);

	/*-----------------------------------------
	/ void Repeat
	/
	/ 戻り値	: ボタンを離した
	/
	/ 引数		: ボタン指定
	/
	/ 機能		: wiiリモコンが押している間の間隔
	-----------------------------------------*/
	bool	Repeat(BUTTON Button);

	/*-----------------------------------------
	/ float GetAngle
	/
	/ 戻り値	: wiiリモコンの角度( 0°〜 360°)
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコンの角度[ラジアン値]取得
	-----------------------------------------*/
	float GetAngle();

	/*-----------------------------------------
	/ float GetAngleHalf
	/
	/ 戻り値	: wiiリモコンの角度( -180°〜 180°)
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコンの角度[ラジアン値]取得
	-----------------------------------------*/
	float GetAngleHalf();

	/*-----------------------------------------
	/ bool GetTurn
	/
	/ 戻り値	: 回転したのか
	/
	/ 引数		: なし
	/
	/ 機能		: 回転したのかしてないのか
	-----------------------------------------*/
	bool GetTurn();

	/*-----------------------------------------
	/ void SetTurn
	/
	/ 戻り値	: なし
	/
	/ 引数		: bool 回転を強制的に調節
	/
	-----------------------------------------*/
	void SetTurn(bool Turn);

	/*-----------------------------------------
	/ WORD GetButton
	/
	/ 戻り値	: どのボタンが押されているか
	/
	/ 引数		: なし
	/
	/ 機能		: どのボタンが押されているか
	-----------------------------------------*/
	WORD GetButton();

	/*-----------------------------------------
	/ WORD GetPich
	/
	/ 戻り値	: どのボタンが押されているか
	/
	/ 引数		: なし
	/
	/ 機能		: どのボタンが押されているか
	-----------------------------------------*/
	wiimote::acceleration GetAccel();

	/*-----------------------------------------
	/ int GetMaxNum
	/
	/ 戻り値	: コントローラの数
	/
	/ 引数		: なし
	/
	-----------------------------------------*/
	static int GetMaxNum();

	/*-----------------------------------------
	/ wiimote GetWii
	/
	/ 戻り値	: wiiコントローラの情報
	/
	/ 引数		: なし
	/
	-----------------------------------------*/
	wiimote *GetWii();

	/*-----------------------------------------
	/ void GetTurn
	/
	/ 戻り値	: 回転したのか
	/
	/ 引数		: なし
	/
	-----------------------------------------*/

private:
	/*-----------------------------------------
	/ void Init
	/
	/ 戻り値	: なし
	/
	/ 引数		: なし
	/
	/ 機能		: wiiリモコン初期化
	-----------------------------------------*/
	void	Init(int i);

	static CWiiController	*m_pInstance[5];	// 自身のインスタンス
	wiimote					*m_pWii;		// Wiiコントローラ
	WORD					m_Trigger;		// ボタンが押された
	WORD					m_Release;		// ボタンが離された
	float					m_fAngle;		// リモコンの角度(0~360)
	float					m_fAngleHalf;	// リモコンの角度(-180~180)
	int						m_TurnNum;		// 何回転
	WORD					m_Button;		// 現在のボタン
	wiimote::acceleration	m_accel;		// 加速度
	int						m_index;		// インデックス
	static int				m_WiiMax;		// wiiコントローラ数
	bool					m_bTurnCheck[4];// 回転しているかのチェック
	int						m_TurnSpeed;	// 回転スピード
	bool					m_bTurn;		// 回転したのか
	int						m_nTurnCount;	// 回転時間のカウント
};


#endif // _WIICONTROLLER_H_

// end of file