//=============================================================================
//
// FAILE NAME [Explosion.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �����G�t�F�N�g
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Explosion.h"
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/common.h"
#include "../hedder/Sound.h"
#include "../hedder/Player.h"
#include <dsound.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static EXPLOSION		g_Explosion[EXPLOSION_STRUCTMAX] = { NULL };// �����ϐ�
static LPDIRECTSOUNDBUFFER	g_SoundEx = NULL;							// ������
static BOOL g_bPlayerTex = FALSE;
static BOOL g_bExplosionTex[EXPLOSION_MAX] = {FALSE};
static BOOL g_bExplosionSou = FALSE;

//=============================================================================
//
// �֐���	: ExplosionInit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �����̏�����
//
//=============================================================================
void ExplosionInit( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{

		// �����e�N�X�`���[�̓ǂݍ���
		TextureLoad("photo/Explosion.png" , EXPLOSION_NUM + i );

		// �����̏ꏊX���W
		g_Explosion[i].fExplosionPosX = 0;

		// �����̏ꏊY���W
		g_Explosion[i].fExplosionPosY = 0;

		// �����̕�
		g_Explosion[i].fExplosionWidth = EXPLOSION_WIDTHINIT;

		// �����̍���
		g_Explosion[i].fExplosionHeight = EXPLOSION_HEIGHTINIT;
		
		// �����̃e�N�X�`��X���W0
		g_Explosion[i].fExplosionTexX0 = EXPLOSION_TEXVTEXX0;

		// �����̃e�N�X�`��Y���W0
		g_Explosion[i].fExplosionTexY0 = EXPLOSION_TEXVTEXY0;

		// �����̃e�N�X�`��X���W1
		g_Explosion[i].fExplosionTexX1 = EXPLOSION_TEXVTEXX1;

		// �����̃e�N�X�`��Y���W1
		g_Explosion[i].fExplosionTexY1 = EXPLOSION_TEXVTEXY1;

		// �����̑҂�����
		g_Explosion[i].iExplosionWate	= 0;

		// �������g���Ă��邩
		g_Explosion[i].bExplosionAppear = FALSE;
	}

	TextureLoad( "photo/out.png" , OUTPLAYER_NUM ); 
	g_Explosion[OUTPLAYER].fExplosionTexX0 = OUTPLAYER_MOTIONX0;
	g_Explosion[OUTPLAYER].fExplosionTexY0 = OUTPLAYER_MOTIONY0;
	g_Explosion[OUTPLAYER].fExplosionTexX1 = OUTPLAYER_MOTIONX1;
	g_Explosion[OUTPLAYER].fExplosionTexY1 = OUTPLAYER_MOTIONY1;
	g_Explosion[OUTPLAYER].iExplosionWate = 0;
	g_Explosion[OUTPLAYER].bExplosionAppear = FALSE;

	// �T�E���h�t�@�C�����[�h
	if( !SoundFileLoad( "sound/Explosion.wav" , EXPLOSION_SOUNDNUM ) )
	{
		return;
	}

	// �T�E���h�o�b�t�@�쐬
	if( !CreateSoundBuffer( &g_SoundEx , EXPLOSION_SOUNDNUM ) )
	{
		return;
	}
}

void ExplosionPosSet( float fPosX , float fPosY , float fWidth , float fHeight )
{
	PLAYER *pPlayer;
	pPlayer = PlayerGet();

	if( pPlayer->bPlayerAlive == FALSE )
	{
		// ������X���W��ݒ�
		g_Explosion[OUTPLAYER].fExplosionPosX = fPosX;

		// ������Y���W��ݒ�
		g_Explosion[OUTPLAYER].fExplosionPosY = fPosY;

		// �����̍ő�X���W
		g_Explosion[OUTPLAYER].fExplosionWidth = fWidth;

		// �����̍ő�Y���W
		g_Explosion[OUTPLAYER].fExplosionHeight = fHeight;

		g_Explosion[OUTPLAYER].bExplosionAppear = TRUE;
	}

	else
	{
		for( int i = 0; i < EXPLOSION_MAX; i++ )
		{
			if( g_Explosion[i].bExplosionAppear == FALSE )
			{
				// ������X���W��ݒ�
				g_Explosion[i].fExplosionPosX = fPosX;

				// ������Y���W��ݒ�
				g_Explosion[i].fExplosionPosY = fPosY;

				// �����̍ő�X���W
				g_Explosion[i].fExplosionWidth = fWidth;

				// �����̍ő�Y���W
				g_Explosion[i].fExplosionHeight = fHeight;

				// �������g��ꂽ
				g_Explosion[i].bExplosionAppear = TRUE;
				break;
			}
		}
	}
}


//=============================================================================
//
// �֐���	: ExplosionUpdate�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �����̍X�V
//
//=============================================================================
void ExplosionUpdate( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_Explosion[i].bExplosionAppear == TRUE )
		{
			if( g_Explosion[i].iExplosionWate ==  EXPLOSION_WATE )
			{
				// �����̉摜X���W0�ύX
				g_Explosion[i].fExplosionTexX0 += EXPLOSION_TEXVTEXXADD;

				if( g_Explosion[i].fExplosionTexX0 > EXPLOSION_TEXVTEXX0MAX )
				{
					// �����̉摜X���W0�������ʒu��
					g_Explosion[i].fExplosionTexX0 = EXPLOSION_TEXVTEXX0;
				}

				// �����̉摜X���W1�ύX
				g_Explosion[i].fExplosionTexX1 += EXPLOSION_TEXVTEXXADD;

				if( g_Explosion[i].fExplosionTexX1 > EXPLOSION_TEXVTEXX1MAX )
				{
					// �����̉摜X���W1�������ʒu��
					g_Explosion[i].fExplosionTexX1 = EXPLOSION_TEXVTEXX1;

					g_Explosion[i].bExplosionAppear = FALSE;
				}

				// �����̑҂��^�C�}�[���Z�b�g
				g_Explosion[i].iExplosionWate = 0;
			}
			// �����̑҂��^�C�}�[�J�E���g
			g_Explosion[i].iExplosionWate++;
		}
		g_Explosion[i].fExplosionPosX -= 0.40f;
	}

	if( g_Explosion[OUTPLAYER].bExplosionAppear == TRUE )
	{
		if( g_Explosion[OUTPLAYER].iExplosionWate ==  EXPLOSION_WATE )
		{
			// �����̉摜X���W0�ύX
			g_Explosion[OUTPLAYER].fExplosionTexX0 += OUTPLAYER_MOTIONX1;
			
			g_Explosion[OUTPLAYER].fExplosionTexX1 += OUTPLAYER_MOTIONX1;
			if( g_Explosion[OUTPLAYER].fExplosionTexX1 > OUTPLAYER_MOTIONXMAX1 )
			{
				g_Explosion[OUTPLAYER].fExplosionTexX0 = OUTPLAYER_MOTIONX0;
				g_Explosion[OUTPLAYER].fExplosionTexX1 = OUTPLAYER_MOTIONX1;
				g_Explosion[OUTPLAYER].bExplosionAppear = FALSE;
			}
			// �����̑҂��^�C�}�[���Z�b�g
			g_Explosion[OUTPLAYER].iExplosionWate = 0;
		}
		g_Explosion[OUTPLAYER].iExplosionWate++;
		g_Explosion[OUTPLAYER].fExplosionPosX += 0.40f;
	}
	
}

//=============================================================================
//
// �֐���	: ExplosionDraw�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �����̕`�� , ����
//
//=============================================================================
void ExplosionDraw( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_Explosion[i].bExplosionAppear == TRUE )
		{
			// �����̕`��
			PrimitiveCreate(	EXPLOSIONID						,	//�ǂ̃v���~�e�B�u���쐬���邩
								ROTATION						,	// ��]���钸�_�� , ��]���Ȃ����_��
								EXPLOSION_NUM					,	// �e�N�X�`���ԍ�
								0								,	// �p�x ����]���Ȃ��ꍇ��0
								g_Explosion[i].fExplosionPosX	,	// ������X���W�ݒ�
								g_Explosion[i].fExplosionPosY	,	// ������Y���W�ݒ�
								g_Explosion[i].fExplosionWidth	,	// �����̕��ݒ�
								g_Explosion[i].fExplosionHeight	,	// �����̍����ݒ�
								g_Explosion[i].fExplosionTexX0	,	// �����̉摜X���W0�ݒ�
								g_Explosion[i].fExplosionTexY0	,	// �����̉摜Y���W0�ݒ�
								g_Explosion[i].fExplosionTexX1	,	// �����̉摜X���W1�ݒ�
								g_Explosion[i].fExplosionTexY1	);	// �����̉摜Y���W1�ݒ�

			// �������̍Đ�
			g_SoundEx->Play( 0 , 0 , 0 );
		}

	}

	if( g_Explosion[OUTPLAYER].bExplosionAppear == TRUE )
	{
		// �����̕`��
		PrimitiveCreate(	EXPLOSIONID						,	//�ǂ̃v���~�e�B�u���쐬���邩
							ROTATION						,	// ��]���钸�_�� , ��]���Ȃ����_��
							OUTPLAYER_NUM					,	// �e�N�X�`���ԍ�
							0								,	// �p�x ����]���Ȃ��ꍇ��0
							g_Explosion[OUTPLAYER].fExplosionPosX	,	// ������X���W�ݒ�
							g_Explosion[OUTPLAYER].fExplosionPosY	,	// ������Y���W�ݒ�
							g_Explosion[OUTPLAYER].fExplosionWidth	,	// �����̕��ݒ�
							g_Explosion[OUTPLAYER].fExplosionHeight	,	// �����̍����ݒ�
							g_Explosion[OUTPLAYER].fExplosionTexX0	,	// �����̉摜X���W0�ݒ�
							g_Explosion[OUTPLAYER].fExplosionTexY0	,	// �����̉摜Y���W0�ݒ�
							g_Explosion[OUTPLAYER].fExplosionTexX1	,	// �����̉摜X���W1�ݒ�
							g_Explosion[OUTPLAYER].fExplosionTexY1	);	// �����̉摜Y���W1�ݒ�
	
	}
}


//=============================================================================
//
// �֐���	: ExplosionUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �����̉��
//
//=============================================================================
void ExplosionUninit( void )
{
	g_bPlayerTex = FALSE;

	g_bExplosionSou = FALSE;

	// �e�N�X�`���̉��
	TextureUninit( EXPLOSION_NUM );
	TextureUninit( OUTPLAYER_NUM );

	// �T�E���h�o�b�t�@�̉��
	if( g_SoundEx != NULL )
	{
		g_SoundEx->Release();
		g_SoundEx = NULL;
	}
}

//=============================================================================
//
// �֐���	: ExplosionGet�֐�
//
// �߂�l	: EXPLOSION
//
// ����		: �Ȃ�
//
// �@�\		: �����̃Q�b�^�[
//
//=============================================================================
EXPLOSION *ExplosionGet( void )
{
	return &g_Explosion[0];
}