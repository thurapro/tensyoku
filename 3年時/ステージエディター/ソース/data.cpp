//=============================================================================
// データ一括管理 [ data.cpp ]
//
// 製作者	: 松尾 雄太
//
// 機能		: データ一括管理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "data.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEXT	(1024)

//=============================================================================
// 関数名	: CData
// 戻り値	: なし
// 引数値	: ない
// 機能		: インスタンス生成 ( 初期化 )
//=============================================================================
CData::CData(void)
{
	m_pTexture	= NULL;			// テクスチャポインタ初期化
	m_pModel	= NULL;			// モデルポインタ初期化
	m_pSound	= NULL;			// サウンドポインタ初期化
}

//=============================================================================
// 関数名	: ~CData
// 戻り値	: なし
// 引数値	: ない
// 機能		: インスタンス破棄 ( 終了処理 )
//=============================================================================
CData::~CData(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数値	: ウィンドウハンドル  ファイル名 
// 機能		: データ初期化処理
//=============================================================================
HRESULT CData::Init(HWND hWnd, const char *FileName)
{
	HRESULT hr;			// エラーチェック変数

	// データを一括ロード
	hr = LoardData(hWnd, FileName);
	ERROR_CHACK(hr);			// エラーチェック

	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: データ終了処理
//=============================================================================
void CData::Uninit(void)
{
	CLASS_DELETE(m_pTexture);	// テクスチャポインタ破棄
	CLASS_DELETE(m_pModel);		// モデルポインタ破棄
	CLASS_DELETE(m_pSound);		// サウンドポインタ破棄
}

//=============================================================================
// 関数名	: Save
// 戻り値	: なし
// 引数値	: なし
// 機能		: データ保存
//=============================================================================
void CData::Save(void)
{
	FILE *fp = NULL;		// ファイルポインタ
	
	// ファイルオープン
	fp = fopen("data/TEXT/Data.txt", "wt");
	if( fp == NULL )
	{
		return ;
	}

	fclose(fp);
}

//=============================================================================
// 関数名	: LoardData
// 戻り値	: なし
// 引数値	: ウィンドウハンドル  ファイル名
// 機能		: データ保存
//=============================================================================
HRESULT CData::LoardData(HWND hWnd, const char *FileName)
{
	HRESULT hr;					// エラーチェック変数
	FILE	*fp = NULL;			// ファイルポインタ初期化
	char	strFile[1024];		// ファイル名取得用

	// ファイルを開く
	fopen_s(&fp, FileName, "r");
	if( fp == NULL )
	{
		// ファイルが開けなければ
		return E_FAIL;		// エラーコード
	}

	// ファル名取得
	while(true)
	{
		if( fscanf(fp, "%s", strFile) != EOF)
		{
			if( strstr(strFile, "texture.txt") != 0 )
			{
				// 検出した文字列がテクスチャだった場合
				NEW_TYPE(m_pTexture, CTexture);		// テクスチャインスタンス生成
				hr = m_pTexture->Init(strFile);		// テクスチャ初期化
				if( FAILED(hr) )
				{
					// 生成に失敗した場合
					fclose(fp);			// ファイルを閉じる
					return E_FAIL;		// エラーコード
				}
			}
			else if( strstr(strFile, "model.txt") != 0 )
			{
				// 検出した文字列がモデルだった場合
				NEW_TYPE(m_pModel, CModel);		// モデルインスタンス生成
				hr = m_pModel->Init(strFile);	// モデル初期化
				if( FAILED(hr) )
				{
					// 生成に失敗した場合
					fclose(fp);			// ファイルを閉じる
					return E_FAIL;		// エラーコード
				}
			}
			else if( strstr(strFile, "sound.txt") != 0 )
			{
				// 検出した文字列がサウンドだった場合
				NEW_TYPE(m_pSound, CSound);				// サウンドインスタンス生成
				hr = m_pSound->Init(hWnd, strFile);		// サウンド初期化
				if( FAILED(hr) )
				{
					// 生成に失敗した場合
					fclose(fp);			// ファイルを閉じる
					return E_FAIL;		// エラーコード
				}
			}
		/*	else if( strstr(strFile, "rankdata.txt") != 0 )
			{
				for(int i = 0; i < MAX_RANKING; i++)
				{
					int score;
					CRanking *pRankData = CManager::GetRanking();
					fscanf(fp, "%d\n", &score);
					pRankData->SetRankData(score, i);
				}
			}*/
		}
		else
		{
			break;
		}
	}
	fclose(fp);
	return S_OK;
}	