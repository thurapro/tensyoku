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
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_NUM			( 3 )		// �e�N�X�`���[�ԍ�
#define ENEMY_POSX			( 270 )		// �G�̂���X���W
#define ENEMY_POSY			( 250 )		// �G�̂���Y���W
#define ENEMY_WIDHTINIT		( 90 )		// �G�̕�
#define ENEMY_HEIGHTINIT	( 120 )		// �G�̍���
#define ENEMY_TEXVTEXX0		( 0.f )		// �G�̉摜���_���WX1
#define ENEMY_TEXVTEXY0		( 0.f )		// �G�̉摜���_���WY1
#define ENEMY_TEXVTEXX1		( 1.f )		// �G�̉摜���_���WX2
#define ENEMY_TEXVTEXY1		( 1.f )		// �G�̉摜���_���WY2
#define ENEMY_ANGLE			( 0.f )		// �G�̊p�x
#define RADIUS				( 180 )		// ���a
#define ANGLEADD			( 50.f )	// �p�x�𑫂�
#define ENEMY_MAX			( 2 )		// �G�̍ő吔

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	float	fEnemyPosX;					// �G�̃|�W�V����X( vtxX1�Ɠ��� )
	float	fEnemyPosY;					// �G�̃|�W�V����Y( vtxY1�Ɠ��� )
	float	fEnemyfWidth;				// �G�̕�( vtxX4�Ɠ��� )
	float	fEnemyfHeight;				// �G�̍���( vtxY4�Ɠ��� )
	float	fEnemyTexX0;				// �G�̃e�N�X�`���[X���W1
	float	fEnemyTexY0;				// �G�̃e�N�X�`���[Y���W1
	float	fEnemyTexX1;				// �G�̃e�N�X�`���[X���W2
	float	fEnemyTexY1;				// �G�̃e�N�X�`���[Y���W2
	float	fEnemyAngle;				// �G�̊p�x
	float	fEnemyOldX;					// �G�̌��̍��WX
	float	fEnemyOldY;					// �G�̌��̍��WY
	float	fEnemyOldWidth;				// �G�̌��̕�
	float	fEnemuOldHeight;			// �G�̌��̍���
	int		nEnemyWate;					// �G�̏o���҂�
	int		nDeadcount;					// �G�̎��񂾉�
	BOOL	bEnemyAlive;				// �G�������Ă��邩
	BOOL	bEnemyAttack;				// �G�͍U��������
	BOOL	bEnemyDefense;				// �G�͖h�䂵����
}ENEMY;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void EnemyInit( void );				// �G�̏�����		
void EnemyUpdate( void );			// �G�̍X�V
void EnemyLeft( void );				// �G�����Ɉړ�
void EnemyRight( void );			// �G���E�Ɉړ�
void EnemyDraw( void );				// �G�̕`��
void EnemyUninit( void );			// �G�̉��
ENEMY* EnemyGet( void );			// �G�̃Q�b�^�[
void EnemySet( ENEMY *pEnemy );		// �G�̃Z�b�^�[


#endif //_PLAYER_H_