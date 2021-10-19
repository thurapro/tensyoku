//=============================================================================
//
// FAILE NAME [Player.h]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �v���C���[�̐ݒ�
//
//
//=============================================================================

//=============================================================================
// ��d�C���N���[�h�h�~
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>


//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_NUM			( 2 )			// �e�N�X�`���[�ԍ�	
#define PLAYER_SOUND		( 2 )
#define PLAYER_WIDTHINIT	( 90 )			// �v���C���[�̕��̏����l
#define PLAYER_HEIGHTINIT	( 120 )			// �v���C���[�̍����̏����l
#define PLAYER_POSX_INIT	( 0 )			// �v���C���[�̏����ʒuX���W
#define PLAYER_POSY_INIT	( 240 )
#define PLAYER_TEXVTEXX0	( 0.f )			// �v���C���[���[�V���������l( ���߂�X�� )
#define PLAYER_TEXVTEXY0	( 0.f )			// �v���C���[���[�V���������l( ���߂�Y�� )
#define PLAYER_TEXVTEXX1	( 1.f* 0.25f )	// �v���C���[���[�V���������l( �I����X�� )
#define PLAYER_TEXVTEXY1	( 1.0f * 0.5f )	// �v���C���[���[�V���������l( �I����Y�� )
#define ATTACK_CONTINUOUS	( 120 )			// �R���{���Ȃ��鎞��	
#define MOTION_WATE			( 120 )					


//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	float fPlayerPosX;						// �v���C���[�̃|�W�V����X( vtxX1�Ɠ��� )
	float fPlayerPosY;						// �v���C���[�̃|�W�V����Y( vtxY1�Ɠ��� )
	float fPlayerfWidth;					// �v���C���[�̕�( vtxX4�Ɠ��� )
	float fPlayerfHeight;					// �v���C���[�̍���( vtxY4�Ɠ��� )
	float fPlayerTexX0;						// �v���C���[�e�N�X�`���[X���W0
	float fPlayerTexY0;						// �v���C���[�e�N�X�`���[Y���W0
	float fPlayerTexX1;						// �v���C���[�e�N�X�`���[X���W1
	float fPlayerTexY1;						// �v���C���[�e�N�X�`���[Y���W1
	float fPlayerAngle;						// �v���C���[�̊p�x
	int	nPlayerHP;							// �v���C���[�̃��C�t
	BOOL bPlayerAlive;						// �v���C���[�������Ă��邩
	BOOL bPlayerAttack;						// �v���C���[�͍U����������
	BOOL bPlayerDefense;					// �v���C���[�͖h���������
	BOOL bContinuousAttack;					// �v���C���[�̘A���U���������������̊m�F
	BOOL bAttackMotion;
}PLAYER;

typedef struct
{
	float fPlayerRemainingX0;
	float fPlayerRemainingX1;
	float fPlayerRemainingY0;
	float fPlayerRemainingY1;
}PLAYERREMAINING;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void PlayerInit( void );					// �v���C���[�̏�����
void PlayerLeft( void );					// �v���C���[�̍��ړ�
void PlayerRight( void );					// �v���C���[�̉E�ړ�
void PlayerUp( void );						// �v���C���[�̏�ړ�
void PlayerDown( void );					// �v���C���[�̉��ړ�
void PlayerAngle( void );					// �v���C���[�̊p�x�ύX
void PlayerAttack( void );					// �v���C���[�̍U��
void PlayerDefense( void );					// �v���C���[�̖h��
void PlayerUpdate( void );					// �v���C���[�̍X�V
void PlayerDraw( void );					// �v���C���[�̕`��
void PlayerUninit( void );					// �v���C���[�̉��
PLAYER *PlayerGet( void );					// �v���C���[�Q�b�^�[
void PlayerSet( PLAYER * pPlayer );			// �v���C���[�Z�b�^�[
PLAYERREMAINING *RemainGet(void);
void RemainSet( PLAYERREMAINING *pRemain );

#endif //_PLAYER_H_