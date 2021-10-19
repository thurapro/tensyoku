//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
// ���Ǔ��@: 2013.6.23
//
// ���ǂ����ꏊ : LoardSound��ǉ�
//
// ���ǎ�	: ���� �Y��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>
#include <stdio.h>

//*********************************************************
// �T�E���h�N���X
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
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		bool bLoop;			// ���[�v���邩�ǂ���
	} PARAM;

	HRESULT LoardSound(char *FileName);
	HRESULT InitSoundData(char *SoundFileName, unsigned int nCntSound); 
	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2;					// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		**m_apSourceVoice;				// �\�[�X�{�C�X
	BYTE					**m_apDataAudio;				// �I�[�f�B�I�f�[�^
	DWORD					*m_aSizeAudio;					// �I�[�f�B�I�f�[�^�T�C�Y
	USHORT					m_nSoundNum;					// �T�E���h��
};

#endif
