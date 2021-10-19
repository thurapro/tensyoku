//*********************************************************************
// 																	 **
// Wall001�̏���[ Wall001.cpp ]										 **
// 																	 **
//*********************************************************************
//-------------------------------
// �w�b�_�[�t�@�C��
//-------------------------------
#include "main.h"

/*-------------------------------------------------------------------
�֐���:	CHouse
�֐��̐���:	House�̃R���X�g���N�^

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
CHouse::CHouse( void )
{
	m_pos = VECTOR3D( 0, 0, 0 );
	m_offset = VECTOR3D( 0, 0, 0 );
	m_move = VECTOR3D( 0, 0, 0 );
}

/*-------------------------------------------------------------------
�֐���:	~CHouse
�֐��̐���:	CHouse�̃f�X�g���N�^

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
CHouse::~CHouse( void )
{
}

/*-------------------------------------------------------------------
�֐���:	Init
�֐��̐���:	CHouse�̏�����

�߂�l:	HRESULT�@
  ����: LPDIRECT3DDEVICE9
-------------------------------------------------------------------*/
HRESULT CHouse::Init( void )
{
	// �����蔻��n�̏�����
	m_pCollision = CCollision::SetCollision( this, 
											 CCollision::COL_BOX_AABB, 
											 CCollision::OBJ_PLAYER |
											 CCollision::OBJ_PLBULLET |
											 CCollision::OBJ_GIMMICK |
											 CCollision::OBJ_SHADOW |
											 CCollision::OBJ_ENEMY,
											 VECTOR3D( 14, 100, 14 ) );
	m_pCollision->SetPosPtr( &m_pos );

	// �Փˎ��X�e�[�^�X�̏�����
	m_colStatus.objType = CCollision::OBJ_GIMMICK;
	m_colStatus.damage = 0;
	m_colStatus.e = 1.05f;
	m_colStatus.mass = 1.0f;
	m_colStatus.velocity = m_move;
	m_colStatus.action = CCollision::ACTION_NONE;

	return S_OK;
}

/*-------------------------------------------------------------------
�֐���:	Uninit
�֐��̐���:	CHouse�̏I������

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
void CHouse::Uninit( void )
{
	SAFE_RELEASE( m_pHouse )
	SAFE_RELEASE( m_pCollision )
}

/*-------------------------------------------------------------------
�֐���:	Update
�֐��̐���:	Wall001�̍X�V����

�߂�l:	void�@
  ����: void
-------------------------------------------------------------------*/
void CHouse::Update( void )
{
	m_pos += m_move;

	m_move = VECTOR3D( 0, 0, 0 );
	//m_move.x *= 0.71f;
	//m_move.z *= 0.71f;

	m_pHouse->SetPosWorld( m_pos );
}

/*-------------------------------------------------------------------
�֐���:	OnHit
�֐��̐���:	�Փˎ�����

�߂�l:	void
  ����: VECTOR3D	colPos		: �Փˈʒu
		COLSTATUS	m_colStatus	: �Փˑ���̏Փ˃p�����[�^ 
-------------------------------------------------------------------*/
void CHouse::OnHit( VECTOR3D colPos, VECTOR3D objPos, VECTOR3D objOffset, COLSTATUS colStatus )
{
	int a;
	a= 0;
};
/*-------------------------------------------------------------------
�֐���:	Create
�֐��̐���:	�C���X�^���X�̐���

�߂�l:	CHouse*
  ����: RES_TEX		resTex		: �e�N�X�`���ԍ�
		VECTOR3D	vecPos		: �������W
		VECTOR3D	move		: �ړ���
-------------------------------------------------------------------*/
CHouse* CHouse::Create( int nPriority, char *pFileName, VECTOR3D vecPos )
{
	CHouse *pHouse = new CHouse();
	pHouse->m_pos = vecPos;
	pHouse->m_pHouse = CDrawModel::Create( CDraw::PRI_MODELFIRST, pFileName, vecPos );

	pHouse->Init();

	return pHouse;
};
// EOF