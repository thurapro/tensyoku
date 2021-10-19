//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
// 改良日　: 2013.6.23
//
// 改良した場所 : LoardSoundを追加
//
// 改良者	: 松尾 雄太
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>
#include <stdio.h>

//*********************************************************
// サウンドクラス
//*********************************************************
class CSound
{
public:
	CSound();
	~CSound();

	HRESULT Init(HWND hWnd, char *FileName);
	void Uninit(void);
	HRESULT Play(unsigned int nNum);
	void Stop(unsigned int nNum);
	void Stop(void);
	USHORT GetSoundNum(void){return m_nSoundNum - 1;}

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		bool bLoop;			// ループするかどうか
	} PARAM;

	HRESULT LoardSound(char *FileName);
	HRESULT InitSoundData(char *SoundFileName, unsigned int nCntSound); 
	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2;					// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice		**m_apSourceVoice;				// ソースボイス
	BYTE					**m_apDataAudio;				// オーディオデータ
	DWORD					*m_aSizeAudio;					// オーディオデータサイズ
	USHORT					m_nSoundNum;					// サウンド数
};

#endif
