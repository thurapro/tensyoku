//=============================================================================
//
// FAILE NAME [.h]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: 
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include <dsound.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define SOUNDNAME		("")
#define SOUND_RATE		( DSSCL_EXCLUSIVE|DSSCL_PRIORITY )
#define SOUND_FLAG		( DSBCAPS_PRIMARYBUFFER )
#define SOUND_STATUS	( WAVE_FORMAT_PCM )
#define SOUND_BIT		( 16 )								// bit設定
#define SOUND_QUALITY	( 44100 )							// 音質の設定(何KBYTE?)
#define SOUND_MONAURAL	( 1	)								// モノラルチャンネル
#define SOUND_STEREO	( 2 )								// ステレオチャンネル
#define SOUND_SETTING	( MMIO_ALLOCBUF|MMIO_READ|MMIO_COMPAT )

#define SOUND_BUFF		( DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER ) 


//=============================================================================
// プロトタイプ宣言
//=============================================================================
BOOL SoundInit( HWND hWnd );								// 音楽初期化
BOOL CreatePrimaryBuff( void );								// プライマリサウンドバッファの作成
BOOL SoundFileLoad( char *pFileName , 
					int SoundNum);							// サウンドのロード

BOOL CreateSoundBuffer(  LPDIRECTSOUNDBUFFER *dsb , 
								int SoundNum );				// サウンドバッファ作成

void UninitSound( void );									// サウンドに関するものをすべて解放

#endif	// SOUND_H_
