//*********************************************************************
// 																	 
// �v���C���[�̏���[ player.h ]											 
// �v���C���[�̏������s��(�V���O���g��)
// �J�����N���X���v���C���[�Ƀt�H�[�J�X����ׁA
// ��{�I�Ƀ��[�h�J�ڈȊO�ŉ���͂��Ȃ����ƁI
// 																	 
// Date:2013/06/20 NAME:YUKI SATO									 
// 																		
//*********************************************************************
//---------------------------
// �C���N���[�h�K�[�h
//---------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//--------------------------
// �w�b�_�[�t�@�C��
//--------------------------
#include "drawModel.h"

//-------------------------------
// �}�N��
//-------------------------------
#define PLAYER_MOVE			( 0.02f )				// �v���C���[�ړ���
#define PLAYER_ROT			( 0.02f )				// �v���C���[��]��
#define PLAYER_OFFSET_X		( 15.0f )				// �v���C���[�I�t�Z�b�g
#define COL_VALUE			( 10.0f )				// �����蔻��␳�l
#define STRAW_ROT			( 0.06f )				// �X�g���[��]��
#define STRAW_ROT_MAX		( D3DX_PI * 0.3f )		// �X�g���[��]�ő�l
#define STRAW_ROT_DEFAULT	( VECTOR3D( D3DX_PI * 0.5f, 0, 0 ) )	// �X�g���[�f�t�H���g�p�x
#define STRAW_ROT_LOOKDOWN	( D3DX_PI * 0.5f - 0.2f )				// �������������̃X�g���[�ő�p�x
#define MAX_COLOR			( 6 )

//-------------------------------
// �N���X�錾
//-------------------------------
class CPlayer : public CObject
{
public:
	HRESULT Init( void );	// ����������
	void Uninit( void );	// �I������
	void Update( void );	// �X�V����
	void Reflect( void );	// ���f����

	// �Փˏ���
	void OnHit( int tag, COLDETAIL detail, COLSTATUS colStatus )
	{
		//****************
		// ���ˏ���
		//****************
		float norValue;
		VECTOR3D vecMove;

		// ���������I�u�W�F�N�g���̏���
		switch( colStatus.objType )
		{
		// �ÓI���b�V���̏ꍇ
		case CCollision::OBJ_STATICMESH:

			// �Փˈʒu����c��̈ړ���̑��x������o��
			vecMove = m_move * detail.colTime;
		
			vecMove = m_pos + m_move - detail.colPos;

			// ���K�������@���x�N�g���ƃI�u�W�F�N�g�̐i�s�����x�N�g������@���x�N�g���̒����𓾂�
			norValue = Vec3DDotProduct( detail.colNor, vecMove );

			if( abs( norValue ) >= 5.0f )
			{
				// �@���x�N�g���𔽎˃x�N�g���Ƃ��Ĉړ��x�N�g���ɕ␳����
				m_move -= ( detail.colNor * norValue ) * 2;
				m_move *= 0.76f;
			}
			else
			{
				// �ǂÂ�v�Z
				m_move -= ( detail.colNor * norValue );
			}
			break;
		default:
			
			// ���W���Փˈʒu�ɖ߂�
			if( detail.colTime <= 1.0f && detail.colTime >= -10.0f )
				m_pos = m_pos + ( m_move * detail.colTime );

			// �ǒ݂菈��
			m_move = Vec3DWallHanging( detail.colNor, m_move );
			break;
		}
	};

	static CPlayer *Create( void )
	{
		m_pInstance = new CPlayer();
		m_pInstance->Init();
		m_pInstance->m_scl = VECTOR3D( 2.0f, 2.0f, 2.0f );
	
		return m_pInstance;
	};

	static CPlayer *GetInstance( void )
	{
		return m_pInstance;
	};

private:
	CPlayer( void );				// �R���X�g���N�^(�V���O���g��)
	~CPlayer( void );				// �f�X�g���N�^
	static CPlayer	 *m_pInstance;	// ���g�̃C���X�^���X�|�C���^
	CAnimeModel		 *m_pPlayerBody;// �v���C���̃��f��
	class CShadow	 *m_pShadow;	// �e
	CCollision		 *m_pCollision;	// �����蔻��
	
	VECTOR3D		 m_direction;			// �������
	float			 m_moveStrow;			// �X�g���[��]���x
	VECTOR3D		 m_rotStraw;			// �X�g���[��]�p�x�ۑ��p
	QUATERNION		 m_quatStraw;			// ��]�N�H�[�^�^�j�I��
	bool			 m_bFlagJunp;			// �W�����v�t���O
	float			 m_fJumpPower;			// �W�����v��
	float			 m_fGravity;			// �d��
	D3DXCOLOR		 m_color[MAX_COLOR];	// �F
	int				 m_colorPoint;			// �w�肵�Ă���F
};

#endif
// EOF