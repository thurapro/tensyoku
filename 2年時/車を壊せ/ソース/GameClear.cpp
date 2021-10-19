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
#include "../hedder/Clear.h"
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
static DRAWCLEAR g_Clear;
static LPDIRECTSOUNDBUFFER g_lpClear = NULL;
static BOOL g_bClearCLEARTEXLoad = FALSE;
static BOOL g_bClearSouLoad = FALSE;

//=============================================================================
//
//	�֐���	:	TitleInit
//	
//	�߂�l	:	�Ȃ�
//
//	����	:	�Ȃ�
//
//	�@�\	:	�N���A�e�N�X�`���[���[�h
//				�N���A�T�E���h���[�h
//				�N���A�̂��ꂼ��̏����l�ݒ�
//
//=============================================================================
void ClearInit( void )
{
	if( g_bClearCLEARTEXLoad == FALSE )
	{
		// �摜�̃��[�h
		TextureLoad( "photo/GameClear.png" , CLEARNUM );
		g_bClearCLEARTEXLoad = TRUE;
	}

	// �摜�̈ʒu�ݒ�
	g_Clear.fClearPosX = 0;

	// �摜�̈ʒu�ݒ�
	g_Clear.fClearPosY = 0;

	// �摜�̕��ݒ�
	g_Clear.fClearWidth = SCREEN_WIDTH;

	// �摜�̍����ݒ�
	g_Clear.fClearHeight = SCREEN_HEIGHT;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Clear.fClearCLEARTEXX0 = CLEARTEXX0;

	// �摜���[�V�����ŏ��̐ݒ�
	g_Clear.fClearCLEARTEXY0 = CLEARTEXY0;

	// �摜���[�V�����Ō�̐ݒ�
	g_Clear.fClearCLEARTEXX1 = CLEARTEXX1;

	// �摜���[�V�����Ō�̐ݒ�
	g_Clear.fClearCLEARTEXY1 = CLEARTEXY1;



		if( !SoundFileLoad( "sound/Clear.wav" , CLEARSOUND ) )
		{
			return ;
		}

		if( !CreateSoundBuffer( &g_lpClear , CLEARSOUND ) )
		{
			return ;
		}

		g_bClearSouLoad = TRUE;
	

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
void ClearUpdate( void )
{
	PlayerControlJudg();

}

void ClearDraw( void )
{
	PrimitiveCreate( CLEARID ,
					 KUNCLE ,
					 CLEARNUM ,
					 0			,
					 g_Clear.fClearPosX ,
					 g_Clear.fClearPosY ,
					 g_Clear.fClearWidth ,
					 g_Clear.fClearHeight ,
					 g_Clear.fClearCLEARTEXX0 ,
					 g_Clear.fClearCLEARTEXY0 ,
					 g_Clear.fClearCLEARTEXX1 ,
					 g_Clear.fClearCLEARTEXY1 );

	g_lpClear->Play( 0 , 0 , 0 );
}

void ClearUninit( void )
{
	g_bClearCLEARTEXLoad = FALSE;

	g_bClearSouLoad = FALSE;

	TextureUninit( CLEARNUM );

	if( &g_lpClear != NULL )
	{
		g_lpClear->Release();
		g_lpClear = NULL;
	}
}
						

