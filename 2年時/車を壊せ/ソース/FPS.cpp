//=============================================================================
//
// FAILE NAME [FPS.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: FPS�̌Œ�
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/FPS.h"
#include <windows.h>
#include <d3dx9.h>

//=============================================================================
// �O���[�o���錾
//=============================================================================
static	int g_nExecLastTime;		// �Ō�̎���
static	int g_nFPSLastTime;			// FPS�I������
static	int g_nCurrentTime;			// ���݂̎���
static	int g_nFrameCount;			// �t���[���J�E���g

//=============================================================================
//
// �֐���	: FPSinit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: FPS�̏�����
//
//=============================================================================
void FPSInit( void )
{
	// ����\��ݒ�
	timeBeginPeriod(1);

	g_nExecLastTime = 
	g_nFPSLastTime = timeGetTime();
	g_nCurrentTime = 
	g_nFrameCount = 0;
}

//=============================================================================
//
// �֐���	: FPSFixing�֐�
//
// �߂�l	: ���Ԃ͐��m�ɌŒ肳�ꂽ��
//
// ����		: �Ȃ�
//
// �@�\		: FPS�̌Œ艻
//
//=============================================================================
BOOL FPSFixing( void )
{
	g_nCurrentTime = timeGetTime();
	if( ( g_nCurrentTime - g_nFPSLastTime ) >= 500 )
	{
		g_nFPSLastTime = g_nCurrentTime;
		g_nFrameCount = 0;
	}

	if( ( g_nCurrentTime - g_nExecLastTime ) >= FPS_FIXING )
	{
		g_nExecLastTime = g_nCurrentTime;
		return TRUE;
	}
	return FALSE;
}


void SetFrameTime( int nFrameCount )
{
	g_nFrameCount = nFrameCount;
}