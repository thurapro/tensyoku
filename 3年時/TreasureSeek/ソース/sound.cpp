//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : AKIRA TANAKA
//
// ���Ǔ��@: 2013.6.23
//
// ���ǂ����ꏊ : LoardSound��ǉ�
//
// ���ǎ�	: ���� �Y��
//
//=============================================================================
#include "sound.h"

#define MAX_STR		(1024)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSound::CSound()
{
	m_pXAudio2 = NULL;
	m_aSizeAudio = NULL;
	m_pMasteringVoice = NULL;
	m_apSourceVoice = NULL;
	m_apDataAudio = NULL;
	m_nSoundNum = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSound::~CSound()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSound::Init(HWND hWnd, char *FileName)
{
	HRESULT hr;

	hr = LoardSound(FileName);
	if( FAILED(hr) )
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for(unsigned int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	if( m_pMasteringVoice != NULL )
	{
		m_pMasteringVoice->DestroyVoice();
		m_pMasteringVoice = NULL;
	}
	
	if(m_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	if( m_nSoundNum > 0 )
	{
		// COM���C�u�����̏I������
		CoUninitialize();
	}
	
	if( m_apSourceVoice != NULL )
	{
		delete[] m_apSourceVoice;
		m_apSourceVoice = NULL;
	}
	
	if( m_apDataAudio != NULL )
	{
		delete[] m_apDataAudio;
		m_apDataAudio = NULL;
	}

	if( m_aSizeAudio != NULL )
	{
		delete[] m_aSizeAudio;
		m_aSizeAudio = NULL;
	}
}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT CSound::Play(unsigned int nNum)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[nNum];
	buffer.pAudioData = m_apDataAudio[nNum];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// ��Ԏ擾
	m_apSourceVoice[nNum]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[nNum]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[nNum]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[nNum]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[nNum]->Start(0);

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::Stop(unsigned int nNum)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[nNum]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[nNum]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[nNum]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::Stop(void)
{
	// �ꎞ��~
	for(unsigned int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// �t�@�C�����[�h
//=============================================================================
HRESULT CSound::LoardSound(char *FileName)
{
	HRESULT hr;
	FILE *fp;								// �t�@�C���|�C���^
	char strFile[MAX_STR] = {NULL};			// �t�@�C�����m�ۗp

	// �t�@�C���I�[�v
	fp = fopen(FileName, "r");
	if( fp == NULL )
	{
		// �t�@�C�������݂��Ȃ�����
		return E_FAIL;
	}

	// �T�E���h���擾
	while(true)
	{
		// �t�@�C���̍s���擾
		if(fscanf(fp, "%s", &strFile) != EOF)
		{
			// �s�� = �T�E���h��
			m_nSoundNum++;	// �s���J�E���g
		}
		else
		{
			// �t�@�C���̒��g�������Ȃ���
			break;
		}
	}

	int nError;		// �G���[�`�F�b�N

	// �t�@�C�������̈ʒu�ɖ߂�
	nError = fseek(fp, 0, SEEK_SET);
	if( nError != 0 )
	{
		return E_FAIL;
	}

	if( m_nSoundNum > 0 )
	{
		m_apSourceVoice  = NEW IXAudio2SourceVoice*[m_nSoundNum];
		m_apDataAudio = NEW BYTE*[m_nSoundNum];
		m_aSizeAudio = NEW DWORD[m_nSoundNum];
	}

	// �e�N�X�`���ǂݍ���
	for( unsigned int i = 0; i < m_nSoundNum; i++)
	{
		// �e�N�X�`���̖��O���擾
		if(fscanf(fp, "%s", &strFile) != EOF)
		{
			// �t�@�C�����ۑ�
			hr = InitSoundData(strFile,i);
			if( FAILED(hr) )
			{
				fclose(fp);
				return E_FAIL;
			}
		}
	}
	fclose(fp);		// �t�@�C������
	return S_OK;	// ����I��
}

HRESULT CSound::InitSoundData( char *SoundFileName, unsigned int nCntSound )
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if(FAILED(hr))
	{
		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if(FAILED(hr))
	{
		if(m_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(SoundFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}
	if(dwFiletype != 'EVAW')
	{
		return S_FALSE;
	}
	
	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}
	m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
	hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
	if(FAILED(hr))
	{
		return S_FALSE;
	}
	
	// �\�[�X�{�C�X�̐���
	m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[nCntSound];
	buffer.pAudioData = m_apDataAudio[nCntSound];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	return S_OK;
}

	


//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�^�C�v�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���i�߂�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof( DWORD ) * 2;
		if(dwChunkType == dwFormat)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}
