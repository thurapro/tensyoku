//*********************************************************************
// 																	 **
// Player�̏���[ player.cpp ]										 **
// 																	 **
//*********************************************************************
//-------------------------------
// �w�b�_�[�t�@�C��
//-------------------------------
#include "main.h"
#include "calculation.h"

//-------------------------------
// �}�N����`
//-------------------------------
#define JUMP_POWER ( 3 )
#define GRAVITY ( 0.03f )

//-------------------------------
// �ÓI�����o�ϐ�
//-------------------------------
CPlayer* CPlayer::m_pInstance;


/*-------------------------------------------------------------------
�֐���:	CPlayer
�֐��̐���:	Player�̃R���X�g���N�^

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
CPlayer::CPlayer( void )
{
	m_move = VECTOR3D( 0, 0, 0 );
	m_rotStraw = VECTOR3D( 0, 0, 0 );
	m_pPlayerBody = NULL;
	m_pShadow = NULL;
	m_pCollision = NULL;
	m_bFlagJunp = false;
	m_fJumpPower = JUMP_POWER;

	m_color[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_color[1] = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_color[2] = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_color[3] = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	m_color[4] = D3DXCOLOR(0.3f, 0.0f, 0.8f, 1.0f);
	m_color[5] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	m_colorPoint = 0;
}

/*-------------------------------------------------------------------
�֐���:	~CPlayer
�֐��̐���:	Player�̃f�X�g���N�^

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
CPlayer::~CPlayer( void )
{
}

/*-------------------------------------------------------------------
�֐���:	Init
�֐��̐���:	Player�̏�����

�߂�l:	HRESULT�@
  ����: void
-------------------------------------------------------------------*/
HRESULT CPlayer::Init( void )
{
	// �v���C���[�̑̂𐶐�	
	m_pPlayerBody = CAnimeModel::Create( CDraw::PRI_MODELFIRST, VECTOR3D( 0, 100, 0 ) );
	m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_NEUTRAL );

	// �e�̐���
	m_pShadow = CShadow::Create( CDraw::PRI_SHADOW, "Data/Model/shadow000.x", m_pos );
	
	m_rotStraw = VECTOR3D( 0, 0, 0 ); 


	// �����蔻��̐���
	m_pCollision = CCollision::SetCollision( this,
											 CCollision::COL_SPHERE,
											 CCollision::OBJ_ENEMY |
											 CCollision::OBJ_STATICMESH |
											 CCollision::OBJ_GIMMICK,
											 VECTOR3D( PLAYER_OFFSET_X, PLAYER_OFFSET_X, PLAYER_OFFSET_X ));
	
	m_colStatus.objType = CCollision::OBJ_PLAYER;	// ���g�̃I�u�W�F�^�C�v

	return S_OK;
}

/*-------------------------------------------------------------------
�֐���:	Uninit
�֐��̐���:	Player�̏I������

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
void CPlayer::Uninit( void )
{
	SAFE_RELEASE( m_pPlayerBody )

	SAFE_RELEASE( m_pShadow )

	SAFE_RELEASE( m_pCollision )

	// �C���X�^���X�̃|�C���^��NULL��
	m_pInstance = NULL;
}

/*-------------------------------------------------------------------
�֐���:	Update
�֐��̐���:	Player�̍X�V����

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
void CPlayer::Update( void )
{
	m_posPrev = m_pos;	// �O����W��ۑ�

	// �J�����̌������擾
	float rotCamera = CCameraMain::GetInstance()->GetRotation().y;
	
	if( ( CKeyboard::GetInstance()->isPress( DIK_W ) ) ||
		( CKeyboard::GetInstance()->isPress( DIK_D ) ) ||
		( CKeyboard::GetInstance()->isPress( DIK_S ) ) ||
		( CKeyboard::GetInstance()->isPress( DIK_A ) ) ||
		( abs( CJoypad::GetInstance()->GetStick1().x ) >= 0.1 ) ||
		( abs( CJoypad::GetInstance()->GetStick1().y ) >= 0.1 ) )
	{
		// �ړ�
		if( CKeyboard::GetInstance()->isPress( DIK_W ) )
		{
			m_move.x += cosf( rotCamera );
			m_move.z += sinf( rotCamera );
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}
		if( CKeyboard::GetInstance()->isPress( DIK_S ) )
		{
			m_move.x += -cosf( rotCamera );
			m_move.z += -sinf( rotCamera );
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}
		if( CKeyboard::GetInstance()->isPress( DIK_A ) )
		{
			m_move.x += cosf( rotCamera + D3DX_PI / 2 );
			m_move.z += sinf( rotCamera + D3DX_PI / 2 );
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}
		if( CKeyboard::GetInstance()->isPress( DIK_D ) )
		{
			m_move.x += cosf( rotCamera - D3DX_PI / 2 );
			m_move.z += sinf( rotCamera - D3DX_PI / 2 );
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}	

		// �W���C�p�b�h�ł̈ړ�����
		if( abs( CJoypad::GetInstance()->GetStick1().x ) >= 0.1 )
		{
			m_move.x += -cosf( rotCamera + D3DX_PI / 2  ) * CJoypad::GetInstance()->GetStick1().x;
			m_move.z += -sinf( rotCamera + D3DX_PI / 2  ) * CJoypad::GetInstance()->GetStick1().x;
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}
		if( abs( CJoypad::GetInstance()->GetStick1().y ) >= 0.1 )
		{
			m_move.x += -cosf( rotCamera ) * CJoypad::GetInstance()->GetStick1().y;
			m_move.z += -sinf( rotCamera ) * CJoypad::GetInstance()->GetStick1().y;
			m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_WALK );
		}
		
		// ��������ۑ�
		m_direction.y = atan2f( m_move.x, m_move.z );
	}
	else
	{
		m_pPlayerBody->SetMotion( CAnimeModel::MOTIONTYPE_NEUTRAL );
	}

	CDebugProc::GetInstance()->Print( "move:x %f\n", m_move.x );
	CDebugProc::GetInstance()->Print( "move:z %f\n", m_move.z );
	CDebugProc::GetInstance()->Print( "move:y %f\n", m_move.y );
	
	// �X�g���[����

	// �X�g���[����
	// �W���C�p�b�h�ł̑���
	if( abs( CJoypad::GetInstance()->GetStick2().x ) >= 0.02f ||
		abs( CJoypad::GetInstance()->GetStick2().y ) >= 0.02f )
	{
		m_rotStraw.y = STRAW_ROT_MAX * CJoypad::GetInstance()->GetStick2().x;
		m_rotStraw.x = STRAW_ROT_MAX * CJoypad::GetInstance()->GetStick2().y;
	}

	// �L�[�{�[�h�ł̑���
	else if( CKeyboard::GetInstance()->isPress( DIK_RIGHT ))
	{
		m_moveStrow = STRAW_ROT;
		m_rotStraw.y += m_moveStrow;
			
		if( m_rotStraw.y >= STRAW_ROT_MAX )
		{
			m_rotStraw.y = STRAW_ROT_MAX;
		}
	}
	else if( CKeyboard::GetInstance()->isPress( DIK_LEFT ))
	{	
		m_moveStrow = STRAW_ROT;
		m_rotStraw.y -= m_moveStrow;
			
		if( m_rotStraw.y <= -STRAW_ROT_MAX )
		{
			m_rotStraw.y = -STRAW_ROT_MAX;
		}
	}

	if( CKeyboard::GetInstance()->isPress( DIK_UP ))
	{
		m_moveStrow = STRAW_ROT;
		m_rotStraw.x -= m_moveStrow;

		if( m_rotStraw.x <= -STRAW_ROT_MAX )
		{
			m_rotStraw.x = -STRAW_ROT_MAX;
		}
	}
	else if( CKeyboard::GetInstance()->isPress( DIK_DOWN ))
	{
		m_moveStrow = STRAW_ROT;
		m_rotStraw.x += m_moveStrow;
			
		if( m_rotStraw.x >= STRAW_ROT_MAX )
		{
			m_rotStraw.x = STRAW_ROT_MAX;
		}
	}
	if( CKeyboard::GetInstance()->isTrigger( DIK_SPACE ) )
	{
		if( m_bFlagJunp == false )
		{
			m_bFlagJunp = true;
			m_fJumpPower = JUMP_POWER;
		}
	}

	if( m_bFlagJunp )
	{
		m_move.y += m_fJumpPower;
		if( m_pos.y < 100 )
		{
			m_bFlagJunp = false;
			m_pos.y = 100;
			m_move.y = 0;
		}
	}


	// �d��
	m_move.y *= 0.904f;
	m_fJumpPower -= 0.08f;
	m_move.x *= 0.87f;
	m_move.z *= 0.87f;

	m_colStatus.velocity = m_move;

	
	//*********************
	// ��]����
	//*********************

	// �i�s�����x�N�g���̌������p�x�ɕۑ�
	m_rot.y = m_direction.y;
	

	//**************
	// ��������
	//**************
	if( m_pos.y <= -300 )
	{
		m_pos = VECTOR3D( 0, 100, 0 );
	}	

	// �F�ϊ�
	if( CKeyboard::GetInstance()->isTrigger( DIK_UP ) )
	{
		m_colorPoint ++;
		if( m_colorPoint > MAX_COLOR - 1 )
		{
			m_colorPoint = MAX_COLOR - 1;
		}
		m_pPlayerBody->SetMaterialColor(m_color[m_colorPoint]);
	}

	if( CKeyboard::GetInstance()->isTrigger( DIK_DOWN ) )
	{
		m_colorPoint --;
		if( m_colorPoint < 0  )
		{
			m_colorPoint = 0;
		}
		m_pPlayerBody->SetMaterialColor(m_color[m_colorPoint]);
	}


}

void CPlayer::Reflect( void )
{
	// �ړ����x�𔽉f
	m_pos += m_move;

	// �e�̈ʒu�X�V
	m_pShadow->SetPosWorld( m_pos );

	// ���f���Ɉʒu�Ɖ�]���𔽉f
	m_pPlayerBody->SetPosWorld( m_pos );
	m_pPlayerBody->SetRotation( VECTOR3D( 0, m_rot.y + D3DX_PI, 0 ));
	
	m_pPlayerBody->Update();

	VECTOR3D tempRot = m_rotStraw;
	tempRot.x *= -1;
	m_pPlayerBody->SetPartsRotation( 1, tempRot );
	
	CDebugProc::GetInstance()->Print( "pos:x %f\n", m_pos.x );
	CDebugProc::GetInstance()->Print( "pos:y %f\n", m_pos.y );
	CDebugProc::GetInstance()->Print( "pos:z %f\n", m_pos.z );
}
// EOF