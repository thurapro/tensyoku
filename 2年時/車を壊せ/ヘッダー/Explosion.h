//=============================================================================
//
// FAILE NAME [Explosion.h]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �����G�t�F�N�g�̃}�N��,�\����,�v���g�^�C�v�錾
//
//=============================================================================

//=============================================================================
// ��d�C���N���[�h�h�~
//=============================================================================
#ifndef _EXPLOSION_H_
#define	_EXPLOSION_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_NUM			( 7 )			// �����e�N�X�`���ԍ� 9�`14
#define EXPLOSION_WIDTHINIT		( 30 )			// �����̏�����
#define EXPLOSION_HEIGHTINIT	( 30 )			// �����̏�������
#define EXPLOSION_TEXVTEXX0		( 0.025f )		// �����摜��X���W0
#define EXPLOSION_TEXVTEXY0		( 0.3f )		// �����摜��Y���W0
#define EXPLOSION_TEXVTEXX1		( 0.1f )		// �����摜��X���W1
#define EXPLOSION_TEXVTEXY1		( 0.70f )		// �����摜��Y���W1
#define EXPLOSION_TEXVTEXXADD	( 0.1f )		// �����摜��X���W���ړ�
#define EXPLOSION_TEXVTEXX0MAX	( 0.9f )		// �����摜��X���W0�ő�ʒu	
#define EXPLOSION_TEXVTEXX1MAX	( 1.f )			// �����摜��X���W1�ő�ʒu
#define EXPLOSION_WIDTHSUB		( 3 )			// ���̈����Z
#define EXPLOSION_HEIGHTSUB		( 3 )			// �����̈����Z
#define EXPLOSION_TEXTUREMOVEX	( 0.1f )		// �e�N�X�`���̍��WX�ړ�
#define EXPLOSION_TEXTUREMOVE	( 0 )			// �e�N�X�`���̍��WY�ړ�
#define EXPLOSION_SOUNDNUM		( 3 )			// ������
#define EXPLOSION_STRUCTMAX		( 4 )
#define EXPLOSION_MAX			( 3 )			// �����̍ő吔
#define EXPLOSION_WATE			( 20 )			// �����҂�����
#define OUTPLAYER				( 3 )
#define OUTPLAYER_NUM			( 10 )			// �v���C���[�̂���ꃂ�[�V����
#define OUTPLAYER_MOTIONX0		( 0.f )	
#define OUTPLAYER_MOTIONY0		( 0.f )
#define OUTPLAYER_MOTIONX1		( 1.f * 0.25 )
#define OUTPLAYER_MOTIONY1		( 1.f )
#define OUTPLAYER_MOTIONXMAX0	( 0.75f )
#define OUTPLAYER_MOTIONXMAX1	( 1.f )



//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	float	fExplosionPosX	;					// �����̈ʒuX���W
	float	fExplosionPosY	;					// �����̈ʒuY���W
	float	fExplosionWidth	;					// �����̕�
	float	fExplosionHeight;					// �����̍���
	float	fExplosionTexX0	;					// �����̉摜X���W0
	float	fExplosionTexY0	;					// �����̉摜Y���W0
	float	fExplosionTexX1	;					// �����̉摜X���W1
	float	fExplosionTexY1	;					// �����̉摜Y���W1
	int		iExplosionWate	;					// �����̑҂�����
	BOOL	bExplosionAppear;					// �������\������Ă��邩

}EXPLOSION;


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void ExplosionInit( void )	;					// �����̏�����

void ExplosionPosSet( float fPosX	,			// �����̃|�W�V�����Z�b�gX���W
					  float fPosY	,			// �����̃|�W�V�����Z�b�gY���W
					  float fWidth	,			// �����̃|�W�V�����Z�b�g�ő�X���W
					  float fHeight);			// �����̃|�W�V�����Z�b�g�ő�Y���W

void ExplosionUpdate( void );					// �����̍X�V

void ExplosionDraw( void )	;					// �����̕`��
void ExplosionUninit( void );					// �������
EXPLOSION *ExplosionGet( void );				// �����Q�b�^�[

#endif // EXPLOSION_H_