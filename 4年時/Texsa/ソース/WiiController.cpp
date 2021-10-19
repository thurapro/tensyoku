//=============================================================================
// file : WiiController.h
//
// another : Yuta Matsuo 
//
//
// 機能説明 : Wiiリモコン操作 
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "WiiController.h"
#include <Memory.h>
#include <mmsystem.h>

#define PI (3.141592653589793f)
#define MAX_CHECK (4)
#define TURN_FRAME (100)

//=============================================================================
// 静的メンバ変数
//=============================================================================
CWiiController *CWiiController::m_pInstance[5] = { NULL, NULL, NULL, NULL, NULL };
int CWiiController::m_WiiMax = 0;

//=============================================================================
// wiiリモコンインスタンス生成
//=============================================================================
CWiiController::CWiiController()
{
	m_pWii = NULL;
	m_fAngle = 0.0f;
	m_TurnNum = 0;
	m_nTurnCount = 0;
	m_bTurn = false;
	ZeroMemory(m_bTurnCheck, sizeof(m_bTurnCheck));
}

//=============================================================================
// wiiリモコンインスタンス破棄
//=============================================================================
CWiiController::~CWiiController()
{
	// wiiリモコン破棄
	if (m_pWii)
	{
		if( m_pWii->IsConnected() ){
			m_pWii->SetLEDs( m_index - 1 );
			m_pWii->Disconnect();
		}
		SAFE_DELETE(m_pWii);
	}
}

//=============================================================================
// wiiコントローラ生成
//=============================================================================
void CWiiController::Create(int i)
{
	// wiiリモコンインスタンス生成
	m_pInstance[i] = NEW CWiiController;

	// wiiリモコン初期化
	m_pInstance[i]->Init(i);

}

//=============================================================================
// wiiコントローラ破棄
//=============================================================================
void CWiiController::Uninit(int i)
{
	// インスタンス破棄
	SAFE_DELETE(m_pInstance[i]);
}

//=============================================================================
// wiiコントローラ初期化
//=============================================================================
void CWiiController::Init(int i)
{
	// wiiリモコン生成
	m_pWii = NEW wiimote;

	bool WiiConnect = false;

	int frame = 0;
	while (true)
	{
		// wiiリモコンのコネクション
		WiiConnect = m_pWii->Connect(wiimote::FIRST_AVAILABLE);
		if (WiiConnect)
		{
			m_WiiMax++;
			break;
		}
		if (frame == 50)
		{
			int ret = MessageBoxA(nullptr, "リトライしますか？", "WiiConnectTimeout", MB_YESNO);
			if (ret == IDNO){
				if (m_WiiMax < 0)
				{
					exit(1);
				}
				else
				{
					break;
				}
			}
			else if (ret == IDYES){
				frame = 0;
			}
		}
		frame++;
	}

	if (WiiConnect)
	{
		m_index = i + 1;
		//printf("connetion\n");
		m_pWii->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);

	}
	else
	{
		//Uninit(i);
	}
}

//=============================================================================
// wiiコントローラ更新
//=============================================================================
void CWiiController::Update()
{

	if( !m_pWii->IsConnected() ){
		return;
	}
	// 前のボタン保存用
	WORD oldBits;
	float oldAngle = 0;
	float a = 0;

	// 前のボタン保存
	oldBits = m_pWii->Button.Bits;

	// 前の角度取得
	oldAngle = abs(m_pWii->Acceleration.X);

	// Wiiリモコンの現在の状況取得
	m_pWii->RefreshState();

	// ボタンを保存
	m_Button = m_pWii->Button.Bits;

	// Triggerのビット計算
	m_Trigger = (m_pWii->Button.Bits ^ oldBits) & m_pWii->Button.Bits;

	// Releaseのビット計算
	m_Release = (m_pWii->Button.Bits ^ oldBits) & oldBits;

	m_accel = m_pWii->Acceleration;

	m_fAngleHalf = acosf(m_accel.Orientation.X);

	// 角度をDegree変換
	float RagRot = /*acosf(m_accel.Orientation.X)*/m_fAngleHalf;
	float DegRot;
	if (m_accel.Orientation.Y > 0)
	{
		DegRot = m_fAngleHalf * 180 / PI;
		DegRot = 180 + (180 - m_fAngleHalf);
		m_fAngle = PI + (PI - m_fAngleHalf);
	}
	else
	{
		DegRot = RagRot * ( 180 / PI);
		m_fAngle = m_fAngleHalf;
	}

	float speed = 100;

	if (m_bTurnCheck[0] &&
		m_bTurnCheck[1] &&
		m_bTurnCheck[2] &&
		m_bTurnCheck[3])
	{
		// 全てのチェックポイントを通過していたら
		// 現在の回転数を加算
		m_bTurn = true;
		ZeroMemory(m_bTurnCheck, sizeof(m_bTurnCheck));
	}
	else
	{
		if (m_bTurnCheck[0] ||
			m_bTurnCheck[1] ||
			m_bTurnCheck[2] ||
			m_bTurnCheck[3])
		{
			if (m_nTurnCount >= TURN_FRAME)
			{
				m_bTurn = false;
				ZeroMemory(m_bTurnCheck, sizeof(m_bTurnCheck));
				m_nTurnCount = 0;
			}
			m_nTurnCount++;
		}

		if (!m_bTurnCheck[0])
		{
			if (m_bTurnCheck[3])
			{
				if (DegRot >= 90.0f - speed && DegRot <= 90.0f + speed)
				{
					m_bTurnCheck[0] = true;
					m_nTurnCount = 0;
				}
			}
		}
		if (!m_bTurnCheck[1])
		{
			if (DegRot >= 180.0f - speed && DegRot <= 180.0f + speed)
			{
				m_bTurnCheck[1] = true;
				m_nTurnCount = 0;
			}
		}
		if (!m_bTurnCheck[2])
		{
			if (DegRot >= 270.0f - speed && DegRot <= 270.0f + speed)
			{
				m_bTurnCheck[2] = true;
				m_nTurnCount = 0;
			}
		}
		if (!m_bTurnCheck[3])
		{
			if (m_bTurnCheck[2])
			{
				if (DegRot >= 0.0f && DegRot <= 0.0f + speed ||
					DegRot >= 360.0f - speed && DegRot <= 360.0f)
				{
					m_bTurnCheck[3] = true;
					m_nTurnCount = 0;
				}
			}
		}
	}
}

//=============================================================================
// wiiのインスタンス取得
//=============================================================================
CWiiController *CWiiController::GetInstance(int i)
{
	return m_pInstance[i];
}

//=============================================================================
// ボタンが押されている間
//=============================================================================
bool CWiiController::Push(BUTTON Button)
{
	return (Button & m_pWii->Button.Bits);
}

//=============================================================================
// ボタンが押されたか
//=============================================================================
bool CWiiController::Trigger(BUTTON Button)
{
	return (m_Trigger & Button);
}

//=============================================================================
// ボタンが離されたか
//=============================================================================
bool CWiiController::Release(BUTTON Button)
{
	return (m_Release & Button);
}

//=============================================================================
// wiiリモコンが回転したのか
//=============================================================================
bool CWiiController::GetTurn()
{
	return m_bTurn;
}

//=============================================================================
// wiiリモコンの回転を強制的に変更
//=============================================================================
void CWiiController::SetTurn(bool Turn)
{
	m_bTurn = Turn;
}

//=============================================================================
// wiiリモコンのボタンを取得
//=============================================================================
WORD CWiiController::GetButton()
{
	return m_Button;
}


//=============================================================================
// wiiリモコンの角度
//=============================================================================
float CWiiController::GetAngle()
{
	return m_fAngle;
}

//=============================================================================
// wiiリモコンの加速度を取得
//=============================================================================
wiimote::acceleration CWiiController::GetAccel()
{
	return m_accel;
}

//=============================================================================
// wiiリモコンの数取得
//=============================================================================
int CWiiController::GetMaxNum()
{
	return m_WiiMax;
}

//=============================================================================
// wiiリモコンの情報取得
//=============================================================================
wiimote *CWiiController::GetWii()
{
	return m_pWii;
}


