//=============================================================================
//
// FAILE NAME [.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: 
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Sound.h"
#include <d3dx9.h>
#include <dsound.h>

//=============================================================================
// グローバル変数
//=============================================================================
static LPDIRECTSOUND8			g_lpDS = NULL;				// DirectSound8
static LPDIRECTSOUNDBUFFER		g_lpPrimary = NULL;			// プライマリサウンドバッファ
static HMMIO					g_hSrc[10];						// ファイルロード用

//=============================================================================
//
//	関数名	: SoundInit
//	
//	戻り値	: BOOL
//
//	引数	: なし
//
//	機能	: 音楽の初期化
//
//=============================================================================
BOOL SoundInit( HWND hWnd )
{
	// 作成できたか判定
	HRESULT sound;

	// DirectSound8
	sound = DirectSoundCreate8( NULL , &g_lpDS, NULL );
	if( FAILED(sound) )
	{
		return FALSE;
	}
	
	// 協調モード
	sound = g_lpDS->SetCooperativeLevel( hWnd , SOUND_RATE );
	if( FAILED( sound ) )
	{
		return FALSE;
	}
	return TRUE;
}

//=============================================================================
//
//	関数名	: CreatePrimaryBuff
//	
//	戻り値	: BOOL
//
//	引数	: なし
//
//	機能	: プライマリバッファの作成
//
//=============================================================================
BOOL CreatePrimaryBuff( void )
{
	// バッファ作成できたか判断
	HRESULT Pbuff;

	// ファーマットテクス
	WAVEFORMATEX	wf;

	// プライマリサウンド作成
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

	// プライマリバッファのステータス決定
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
//	関数名	: SoundFileLoad
//	
//	戻り値	: BOOL ロードできたか
//
//	引数	: char *　ファイル名
//
//	機能	: サウンドファイルのロード
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
//	関数名	: CreateSoundBuffer
//	
//	戻り値	: BOOL サウンドバッファが作成できたか
//
//	引数	: なし
//
//	機能	: サウンドバッファ作成
//			  ロック , アンロック
//
//=============================================================================
BOOL CreateSoundBuffer(  LPDIRECTSOUNDBUFFER *dsb , int SoundNum )
{
	HRESULT Sbuff;

	// WAVEファイル
	MMCKINFO mSrcWaveFile;

	// WAVEフォーマット
	MMCKINFO mSrcWaveFmt;

	// WAVEデータ
	MMCKINFO mSrcWaveData;

	// ファーマットテクス
	LPWAVEFORMATEX	wf;

	// 'WAVE' チャンクチェック
	ZeroMemory( &mSrcWaveFile , sizeof(mSrcWaveFile) );
	
	Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveFile , NULL , MMIO_FINDRIFF );
	if( mSrcWaveFile.fccType != mmioFOURCC( 'W' , 'A' , 'V' , 'E' ) )
	{
		// WAVEチャンクチェックエラー

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// ' fmt 'チャンクチェック
	ZeroMemory( &mSrcWaveFmt , sizeof(mSrcWaveFmt) );

	Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveFmt , &mSrcWaveFile , MMIO_FINDCHUNK );

	if( mSrcWaveFmt.ckid != mmioFOURCC( 'f' , 'm' , 't' , ' ') )
	{
		// fmtチャンクチェックエラー

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if( iSrcHeaderSize < sizeof(WAVEFORMATEX) )
	{
		iSrcHeaderSize = sizeof(WAVEFORMATEX);
	}

	// ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc( iSrcHeaderSize );
	if( !wf )
	{
		// ヘッダメモリ確保失敗

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}
	ZeroMemory( wf , iSrcHeaderSize);

	// WAVEフォーマットのロード
	Sbuff = mmioRead( g_hSrc[SoundNum] , (char *)wf, mSrcWaveFmt.cksize );
	if( FAILED( Sbuff ) )
	{
		free( wf );
		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// チャンネル数

	// サンプリングレート

	// ビットレート

	// fmtチャックを探す
	mmioAscend( g_hSrc[SoundNum] , &mSrcWaveFmt , 0 );

	// dataチャックを探す
	while(1)
	{
		// 検索
		Sbuff = mmioDescend( g_hSrc[SoundNum] , &mSrcWaveData , &mSrcWaveFile , 0 );
		if( FAILED(Sbuff) )
		{
			// データチャンクが見当たらない
			free( wf );

			mmioClose( g_hSrc[SoundNum] , 0 );

			return FALSE;
		}
		if( mSrcWaveData.ckid == mmioStringToFOURCC( "data" , 0 ))
		{
			break;
		}

		// 次のチャックへ
		Sbuff = mmioAscend( g_hSrc[SoundNum] , &mSrcWaveData ,0 );
	}

	// データサイズ

	// サウンドバッファの作成
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
		// サウンドバッファ作成失敗

		free( wf );

		mmioClose( g_hSrc[SoundNum] , 0 );
		return FALSE;
	}

	// ロック開始
	LPVOID pMem1 , pMem2;

	DWORD dwSize1 , dwSize2;

	Sbuff = (*dsb)->Lock( 0 , mSrcWaveData.cksize , &pMem1 , &dwSize1 ,
									&pMem2 , &dwSize2 , 0 );

	if( FAILED( Sbuff ) )
	{
		// ロック失敗

		free( wf );
		return FALSE;
	}

	// データ書き込み
	mmioRead( g_hSrc[SoundNum] , (char *)pMem1 , dwSize1 );
	mmioRead( g_hSrc[SoundNum] , (char *)pMem2 , dwSize2 );

	// ロック解除
	(*dsb)->Unlock( pMem1 , dwSize1 , pMem2 , dwSize2 );

	// ヘッダ用メモリを解放
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
