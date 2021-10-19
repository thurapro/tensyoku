//=============================================================================
//
// FAILE NAME [Title.cpp]
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
#include "../hedder/Title.h"
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
static DRAWTITLE g_Title;
static int g_TitleTimer = 0;
static int g_TitleWate = 0;
static LPDIRECTSOUNDBUFFER g_lpTitle = NULL;

//=============================================================================
//
//	�֐���	:	TitleInit
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
void TitleInit( void )
{
	// �摜�̃��[�h
	TextureLoad( "photo/Title.png" , TITLENUM );

	// �摜�̈ʒu�ݒ�
	g_Title.fTitlePosX = 0;

	// �摜�̈ʒu�ݒ�
	g_Title.fTitlePosY = 0;

	// �摜�̕��ݒ�
	g_Title.fTitleWidth = SCREEN_WIDTH;

	// �摜�̍����ݒ�
	g_Title.fTitleHeight = SCREEN_HEIGHT;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Title.fTitleTexX0 = TEXX0;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Title.fTitleTexY0 = TEXY0;

	// �摜���[�V�����Ō�̐ݒ�
	g_Title.fTitleTexX1 = TEXX1;

	// �摜���[�V�����Ō�̐ݒ�
	g_Title.fTitleTexY1 = TEXY1;

	if( !SoundFileLoad( "sound/Title.wav" , TITLESOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_lpTitle , TITLESOUND ) )
	{
		return ;
	}

}

//=============================================================================
//
//	�֐���	:	TitleUpdate
//	
//	�߂�l	:	�Ȃ�
//
//	����	:	�Ȃ�
//
//	�@�\	:	�^�C�g���e�N�X�`���[���[�V�����X�V
//
//=============================================================================
void TitleUpdate( void )
{
	// �v���C���[�R���g���[��
	PlayerControlJudg();

	// 1�b��������
	if( g_TitleTimer == TITLEWATE )
	{
		// �e�N�X�`�����W�ύX
		g_Title.fTitleTexX0 += TEXX1;

		// �e�N�X�`�����W�ύX
		g_Title.fTitleTexX1 += TEXX1;

		// �^�C�}�[�����Z�b�g
		g_TitleTimer = 0;
	}

	// �^�C�g���̃e�N�X�`�����W( X , Y )���ő吔�𒴂��Ă�����
	if( g_Title.fTitleTexX1 == TEXXMAX && g_Title.fTitleTexY1 == TEXYMAX )
	{
		// �e�N�X�`�����W��������
		g_Title.fTitleTexX0 = TEXX0;

		// �e�N�X�`�����W��������
		g_Title.fTitleTexY0 = TEXY0;

		// �e�N�X�`�����W��������
		g_Title.fTitleTexX1 = TEXX1;

		// �e�N�X�`�����W��������
		g_Title.fTitleTexY1 = TEXY1;	
	}

	// ����
	else if( g_Title.fTitleTexX0 < 0.5f && g_Title.fTitleTexX1 > 1.f )
	{
		g_Title.fTitleTexX0 = TEXX0;
		g_Title.fTitleTexY0 = TEXY1;
		g_Title.fTitleTexX1 = TEXX1;
		g_Title.fTitleTexY1 += TEXY1;
	}

	g_TitleTimer++;

}

void TitleDraw( void )
{
	PrimitiveCreate( TITLEID ,
					 KUNCLE ,
					 TITLENUM ,
					 0			,
					 g_Title.fTitlePosX ,
					 g_Title.fTitlePosY ,
					 g_Title.fTitleWidth ,
					 g_Title.fTitleHeight ,
					 g_Title.fTitleTexX0 ,
					 g_Title.fTitleTexY0 ,
					 g_Title.fTitleTexX1 ,
					 g_Title.fTitleTexY1 );

	g_lpTitle->Play( 0 , 0 , 0 );
}

void TitleUninit( void )
{
	TextureUninit( TITLENUM );

	if( g_lpTitle != NULL )
	{
		g_lpTitle->Release();
		g_lpTitle = NULL;
	}
}
						

