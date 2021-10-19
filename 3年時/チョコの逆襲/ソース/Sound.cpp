//=============================================================================
//
// FAILE NAME [.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: 
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Sound.h"
#include <d3dx9.h>
#include <dsound.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static LPDIRECTSOUND8			g_lpDS = NULL;				// DirectSound8
static LPDIRECTSOUNDBUFFER		g_lpPrimary = NULL;			// �v���C�}���T�E���h�o�b�t�@
static HMMIO					g_hSrc[10];						// �t�@�C�����[�h�p

//=============================================================================
//
//	�֐���	: SoundInit
//	
//	�߂�l	: BOOL
//
//	����	: �Ȃ�
//
//	�@�\	: ���y�̏�����
//
//=============================================================================
BOOL SoundInit( HWND hWnd )
{
	// �쐬�ł���������
	HRESULT sound;

	// DirectSound8
	sound = DirectSoundCreate8( NULL , &g_lpDS, NULL );
	if( FAILED(sound) )
	{
		return FALSE;
	}
	
	// �������[�h
	sound = g_lpDS->SetCooperativeLevel( hWnd , SOUND_RATE );
	if( FAILED( sound ) )
	{
		return FALSE;
	}
	return TRUE;
}

//=============================================================================
//
//	�֐���	: CreatePrimaryBuff
//	
//	�߂�l	: BOOL
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C�}���o�b�t�@�̍쐬
//
//=============================================================================
BOOL CreatePrimaryBuff( void )
{
	// �o�b�t�@�쐬�ł��������f
	HRESULT Pbuff;

	// �t�@�[�}�b�g�e�N�X
	WAVEFORMATEX	wf;

	// �v���C�}���T�E���h�쐬
	DSBUFFERDESC dsdesc;

	ZeroMemory( &dsdesc , sizeof(DSBUFFERDESC) );

	dsdesc.dwSize = sizeof( DSBUFFERDESC );

	dsdesc.dwFlags = SOUND_FLAG;

	dsdesc.dwBufferBytes = 0;

	dsdesc.lpwfxFormat = NULL;

	Pbuff = g_lpDS->CreateSoundBuffer( &dsdesc, &g_lpPrimary, NULL );

	if( FAILED( Pbuff) )
	{
		return FALSE;
	}

	// �v���C�}���o�b�t�@�̃X�e�[�^�X����
	wf.cbSize = sizeof( WAVEFORMATEX );

	wf.wFormatTag = SOUND_STATUS;

	wf.nChannels = SOUND_STEREO;

	wf.nSamplesPerSec = SOUND_QUALITY;

	wf.wBitsPerSample = SOUND_BIT;

	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;

	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

	Pbuff = g_lpPrimary->SetFormat( &wf );
	if( FAILED(Pbuff) )
	{
		return FALSE;
	}

	return TRUE;
}


//=============================================================================
//
//	�֐���	: SoundFileLoad
//	
//	�߂�l	: BOOL ���[�h�ł�����
//
//	����	: char *�@�t�@�C����
//
//	�@�\	: �T�E���h�t�@�C���̃��[�h
//
//=============================================================================
BOOL SoundFileLoad(  char *pFileName , int SoundNum )
{
	g_hSrc[SoundNum] = mmioOpen( pFileName , NULL , SOUND_SETTING );
	if( !g_hSrc[SoundNum] )
	{
		return FALSE;
	}
	return TRUE;
}


//=============================================================================
//
//	�֐���	: CreateSoundBuffer
//	
//	�߂�l	: BOOL �T�E���h�o�b�t�@���쐬�ł�����
//
//	����	: �Ȃ�
//
//	�@�\	: �T�E���h�o�b�t�@�쐬
//			  ���b�N , �A�����b�N
//
//=============================================================================
BOOL CreateSoundBuffer(  LPDIRECTSOUNDBUFFER *dsb , int SoundNum )
{
	HRESULT Sbuff;

	// WAVE�t�@�C��
	MMCKINFO mSrcWaveFile;

	// WAVE�t�H�[�}�b�g
	MMCKINFO mSrcWaveFmt;

	// WAVE�f�[�^
	MMCKINFO mSrcWaveData;

	// �t�@�[�}�b�g�e�N�X
	LPWAVEFORMATEX	wf;

	// 'WAVE' �`�����N�`�F�b�N
	ZeroMemory( &mSrcWaveFile , sizeof(mSrcWaveFile) );
	
	Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveFile , NULL , MMIO_FINDRIFF );
	if( mSrcWaveFile.fccType != mmioFOURCC( 'W' , 'A' , 'V' , 'E' ) )
	{
		// WAVE�`�����N�`�F�b�N�G���[

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// ' fmt '�`�����N�`�F�b�N
	ZeroMemory( &mSrcWaveFmt , sizeof(mSrcWaveFmt) );

	Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveFmt , &mSrcWaveFile , MMIO_FINDCHUNK );

	if( mSrcWaveFmt.ckid != mmioFOURCC( 'f' , 'm' , 't' , ' ') )
	{
		// fmt�`�����N�`�F�b�N�G���[

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if( iSrcHeaderSize < sizeof(WAVEFORMATEX) )
	{
		iSrcHeaderSize = sizeof(WAVEFORMATEX);
	}

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc( iSrcHeaderSize );
	if( !wf )
	{
		// �w�b�_�������m�ێ��s

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}
	ZeroMemory( wf , iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	Sbuff = mmioRead( g_hSrc[SoundNum] , (char *)wf, mSrcWaveFmt.cksize );
	if( FAILED( Sbuff ) )
	{
		free( wf );
		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// �`�����l����

	// �T���v�����O���[�g

	// �r�b�g���[�g

	// fmt�`���b�N��T��
	mmioAscend( g_hSrc[SoundNum] , &mSrcWaveFmt , 0 );

	// data�`���b�N��T��
	while(1)
	{
		// ����
		Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveData , &mSrcWaveFile , 0 );
		if( FAILED(Sbuff) )
		{
			// �f�[�^�`�����N����������Ȃ�
			free( wf );

			mmioClose( g_hSrc[SoundNum] , 0 );

			return FALSE;
		}
		if( mSrcWaveData.ckid == mmioStringToFOURCC( "data" , 0 ))
		{
			break;
		}

		// ���̃`���b�N��
		Sbuff = mmioAscend( g_hSrc[SoundNum] , &mSrcWaveData ,0 );
	}

	// �f�[�^�T�C�Y

	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;

	ZeroMemory( &dsdesc , sizeof(DSBUFFERDESC) );
	dsdesc.dwSize = sizeof( DSBUFFERDESC );

	dsdesc.dwFlags = SOUND_BUFF;

	dsdesc.dwBufferBytes = mSrcWaveData.cksize;

	dsdesc.lpwfxFormat = wf;

	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	Sbuff = g_lpDS->CreateSoundBuffer( &dsdesc ,  dsb , NULL );

	if( FAILED( Sbuff ) )
	{
		// �T�E���h�o�b�t�@�쐬���s

		free( wf );

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// ���b�N�J�n
	LPVOID pMem1 , pMem2;

	DWORD dwSize1 , dwSize2;

	Sbuff = (*dsb)->Lock( 0 , mSrcWaveData.cksize , &pMem1 , &dwSize1 ,
									&pMem2 , &dwSize2 , 0 );

	if( FAILED( Sbuff ) )
	{
		// ���b�N���s

		free( wf );
		return FALSE;
	}

	// �f�[�^��������
	mmioRead( g_hSrc[SoundNum] , (char *)pMem1 , dwSize1 );
	mmioRead( g_hSrc[SoundNum] , (char *)pMem2 , dwSize2 );

	// ���b�N����
	(*dsb)->Unlock( pMem1 , dwSize1 , pMem2 , dwSize2 );

	// �w�b�_�p�����������
	free( wf );

	return TRUE;
}

void UninitSound( void )
{
	if( g_lpPrimary != NULL )
	{
		g_lpPrimary->Release();
		g_lpPrimary = NULL;
	}

	if( g_lpDS = NULL )
	{
		g_lpDS->Release();
		g_lpDS = NULL;
	}

}
