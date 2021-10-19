//=============================================================================
// file : WiiController.h
//
// another : Yuta Matsuo 
//
//
// �@�\���� : Wii�����R������ 
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "WiiController.h"
#include <Memory.h>
#include <mmsystem.h>

#define PI (3.141592653589793f)
#define MAX_CHECK (4)
#define TURN_FRAME (100)

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CWiiController *CWiiController::m_pInstance[5] = { NULL, NULL, NULL, NULL, NULL };
int CWiiController::m_WiiMax = 0;

//=============================================================================
// wii�����R���C���X�^���X����
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
// wii�����R���C���X�^���X�j��
//=============================================================================
CWiiController::~CWiiController()
{
	// wii�����R���j��
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
// wii�R���g���[������
//=============================================================================
void CWiiController::Create(int i)
{
	// wii�����R���C���X�^���X����
	m_pInstance[i] = NEW CWiiController;

	// wii�����R��������
	m_pInstance[i]->Init(i);

}

//=============================================================================
// wii�R���g���[���j��
//=============================================================================
void CWiiController::Uninit(int i)
{
	// �C���X�^���X�j��
	SAFE_DELETE(m_pInstance[i]);
}

//=============================================================================
// wii�R���g���[��������
//=============================================================================
void CWiiController::Init(int i)
{
	// wii�����R������
	m_pWii = NEW wiimote;

	bool WiiConnect = false;

	int frame = 0;
	while (true)
	{
		// wii�����R���̃R�l�N�V����
		WiiConnect = m_pWii->Connect(wiimote::FIRST_AVAILABLE);
		if (WiiConnect)
		{
			m_WiiMax++;
			break;
		}
		if (frame == 50)
		{
			int ret = MessageBoxA(nullptr, "���g���C���܂����H", "WiiConnectTimeout", MB_YESNO);
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
// wii�R���g���[���X�V
//=============================================================================
void CWiiController::Update()
{

	if( !m_pWii->IsConnected() ){
		return;
	}
	// �O�̃{�^���ۑ��p
	WORD oldBits;
	float oldAngle = 0;
	float a = 0;

	// �O�̃{�^���ۑ�
	oldBits = m_pWii->Button.Bits;

	// �O�̊p�x�擾
	oldAngle = abs(m_pWii->Acceleration.X);

	// Wii�����R���̌��݂̏󋵎擾
	m_pWii->RefreshState();

	// �{�^����ۑ�
	m_Button = m_pWii->Button.Bits;

	// Trigger�̃r�b�g�v�Z
	m_Trigger = (m_pWii->Button.Bits ^ oldBits) & m_pWii->Button.Bits;

	// Release�̃r�b�g�v�Z
	m_Release = (m_pWii->Button.Bits ^ oldBits) & oldBits;

	m_accel = m_pWii->Acceleration;

	m_fAngleHalf = acosf(m_accel.Orientation.X);

	// �p�x��Degree�ϊ�
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
		// �S�Ẵ`�F�b�N�|�C���g��ʉ߂��Ă�����
		// ���݂̉�]�������Z
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
// wii�̃C���X�^���X�擾
//=============================================================================
CWiiController *CWiiController::GetInstance(int i)
{
	return m_pInstance[i];
}

//=============================================================================
// �{�^����������Ă����
//=============================================================================
bool CWiiController::Push(BUTTON Button)
{
	return (Button & m_pWii->Button.Bits);
}

//=============================================================================
// �{�^���������ꂽ��
//=============================================================================
bool CWiiController::Trigger(BUTTON Button)
{
	return (m_Trigger & Button);
}

//=============================================================================
// �{�^���������ꂽ��
//=============================================================================
bool CWiiController::Release(BUTTON Button)
{
	return (m_Release & Button);
}

//=============================================================================
// wii�����R������]�����̂�
//=============================================================================
bool CWiiController::GetTurn()
{
	return m_bTurn;
}

//=============================================================================
// wii�����R���̉�]�������I�ɕύX
//=============================================================================
void CWiiController::SetTurn(bool Turn)
{
	m_bTurn = Turn;
}

//=============================================================================
// wii�����R���̃{�^�����擾
//=============================================================================
WORD CWiiController::GetButton()
{
	return m_Button;
}


//=============================================================================
// wii�����R���̊p�x
//=============================================================================
float CWiiController::GetAngle()
{
	return m_fAngle;
}

//=============================================================================
// wii�����R���̉����x���擾
//=============================================================================
wiimote::acceleration CWiiController::GetAccel()
{
	return m_accel;
}

//=============================================================================
// wii�����R���̐��擾
//=============================================================================
int CWiiController::GetMaxNum()
{
	return m_WiiMax;
}

//=============================================================================
// wii�����R���̏��擾
//=============================================================================
wiimote *CWiiController::GetWii()
{
	return m_pWii;
}


