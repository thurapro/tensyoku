//=============================================================================
//
// FAILE NAME [Over.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �^�C�g���\��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Over.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Texture.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/Judgment.h"
#include <d3dx9.h>
#include <dsound.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static DRAWOVER				g_Over;
static LPDIRECTSOUNDBUFFER	g_lpOver = NULL;

//=============================================================================
//
//	�֐���	:	OverInit
//	
//	�߂�l	:	�Ȃ�
//
//	����	:	�Ȃ�
//
//	�@�\	:	�^�C�g���e�N�X�`���[���[�h
//				�^�C�g���T�E���h���[�h
//				�^�C�g���̂��ꂼ��̏����l�ݒ�
//
//=============================================================================
void OverInit( void )
{
	// �摜�̃��[�h
	TextureLoad( "photo/Over.png" , OVERNUM );

	// �摜�̈ʒu�ݒ�
	g_Over.fOverPosX = 0;

	// �摜�̈ʒu�ݒ�
	g_Over.fOverPosY = 0;

	// �摜�̕��ݒ�
	g_Over.fOverWidth = SCREEN_WIDTH;

	// �摜�̍����ݒ�
	g_Over.fOverHeight = SCREEN_HEIGHT;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Over.fOverTexX0 = OVERTEXX0;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Over.fOverTexY0 = OVERTEXY0;

	// �摜���[�V�����Ō�̐ݒ�
	g_Over.fOverTexX1 = OVERTEXX1;

	// �摜���[�V�����Ō�̐ݒ�
	g_Over.fOverTexY1 = OVERTEXY1;

	if( !SoundFileLoad( "sound/Over.wav" , OVERSOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_lpOver , OVERSOUND ) )
	{
		return ;
	}
}

//=============================================================================
//
//	�֐���	:	OverUpdate
//	
//	�߂�l	:	�Ȃ�
//
//	����	:	�Ȃ�
//
//	�@�\	:	�^�C�g���e�N�X�`���[���[�V�����X�V
//
//=============================================================================
void OverUpdate( void )
{
	// �v���C���[�R���g���[��
	PlayerControlJudg( );
}

void OverDraw( void )
{
	PrimitiveCreate( OVERID ,
					 KUNCLE ,
					 OVERNUM ,
					 0			,
					 g_Over.fOverPosX ,
					 g_Over.fOverPosY ,
					 g_Over.fOverWidth ,
					 g_Over.fOverHeight ,
					 g_Over.fOverTexX0 ,
					 g_Over.fOverTexY0 ,
					 g_Over.fOverTexX1 ,
					 g_Over.fOverTexY1 );

	g_lpOver->Play( 0 , 0 , 0 );
}

void OverUninit( void )
{
	TextureUninit( OVERNUM );

	if( g_lpOver != NULL )
	{
		g_lpOver->Release();
		g_lpOver = NULL;
	}
}
						

