//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : AKIRA TANAKA
//
// 改良日　: 2013.6.23
//
// 改良した場所 : LoardSoundを追加
//
// 改良者	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_STR		(1024)

//=============================================================================
// コンストラクタ
//=============================================================================
CSound::CSound()
{
	m_pXAudio2			= NULL;		// XAudio2オブジェクトへのインターフェイス初期化
	m_pMasteringVoice	= NULL;		// マスターボイス初期化
	m_apSourceVoice		= NULL;		// ソースボイス初期化
	m_apDataAudio		= NULL;		// オーディオデータ初期化
	m_aSizeAudio		= NULL;		// オーディオデータサイズ初期化
	m_nSoundNum			= 0;		// サウンド数初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CSound::~CSound()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSound::Init(HWND hWnd, char *FileName)
{
	HRESULT hr;
	hr = LoardSound(FileName);		// サウンドファイル読み込み
	ERROR_CHACK(hr);				// エラーチェック
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSound::Uninit(void)
{
	// 一時停止
	for( int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++ )
	{
		if( m_apSourceVoice[nCntSound] )
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	if( m_pMasteringVoice )
	{
		m_pMasteringVoice->DestroyVoice();
		m_pMasteringVoice = NULL;
	}
	
	if( m_nSoundNum > 0 )
	{
		// COMライブラリの終了処理
		CoUninitialize();
	}
	SALF_RELEASE(m_pXAudio2);				// Xオーディオ破棄
	SALF_DELETE_ARRAY(m_apSourceVoice);		// ソースボイズ破棄
	SALF_DELETE_ARRAY(m_apDataAudio);		// データオーディオ破棄
	SALF_DELETE_ARRAY(m_aSizeAudio);		// サイズオーディオ破棄
}

//=============================================================================
// セグメント再生(停止)
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

	// 状態取得
	m_apSourceVoice[nNum]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[nNum]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[nNum]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[nNum]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[nNum]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(unsigned int nNum)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[nNum]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[nNum]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[nNum]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(void)
{
	// 一時停止
	for(unsigned int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// ファイルロード
//=============================================================================
HRESULT CSound::LoardSound(char *FileName)
{
	HRESULT hr;
	FILE *fp;								// ファイルポインタ
	char strFile[MAX_STR] = {NULL};			// ファイル名確保用

	// ファイルオープ
	fopen_s(&fp, FileName, "r");
	if( fp == NULL )
	{
		// ファイルが存在しなかった
		return E_FAIL;
	}

	// サウンド数取得
	while(true)
	{
		// ファイルの行数取得
		if(fscanf(fp, "%s", &strFile) != EOF)
		{
			// 行数 = サウンド数
			m_nSoundNum++;	// 行数カウント
		}
		else
		{
			// ファイルの中身が無くなった
			break;
		}
	}

	// ファイルを元の位置に戻す
	fseek(fp, 0, SEEK_SET);

	if( m_nSoundNum > 0 )
	{
		NEW_TYPE_ARRAY(m_apSourceVoice, IXAudio2SourceVoice*, m_nSoundNum);
		NEW_TYPE_ARRAY(m_apDataAudio, BYTE*, m_nSoundNum);
		NEW_TYPE_ARRAY(m_aSizeAudio, DWORD, m_nSoundNum);
	}

	// テクスチャ読み込み
	for( int i = 0; i < m_nSoundNum; i++ )
	{
		// テクスチャの名前を取得
		if( fscanf(fp, "%s", &strFile) != EOF )
		{
			// ファイル名保存
			hr = InitSoundData(strFile,i);
			if( FAILED(hr) )
			{
				fclose(fp);
				return E_FAIL;
			}
		}
	}
	fclose(fp);		// ファイル閉じる
	return S_OK;	// 正常終了
}

HRESULT CSound::InitSoundData( char *SoundFileName, unsigned int nCntSound )
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if(FAILED(hr))
	{
		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if(FAILED(hr))
	{
		if(m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(SoundFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	// WAVEファイルのチェック
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
	
	// フォーマットチェック
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

	// オーディオデータ読み込み
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
	
	// ソースボイスの生成
	m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[nCntSound];
	buffer.pAudioData = m_apDataAudio[nCntSound];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// オーディオバッファの登録
	m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	return S_OK;
}

	


//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクタイプの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分進める
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
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}
