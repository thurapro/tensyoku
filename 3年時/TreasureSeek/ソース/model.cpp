//=============================================================================
// テクスチャ保存 [ texture.cpp ]
//
// 製作者 : 松尾 雄太
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "renderer.h"
#include "model.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_STR		(1024)				// 最大文字数
#define DIRECTORY	("DATA/MODEL/");	// ディレクトリ

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel(void)
{
	m_pModel = NULL;		// モデルデータポインタ初期化
	m_nModelNum = 0;		// モデル番号初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel(void)
{
	// インスタンス破棄
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CModel::Init(char *FileName)
{
	HRESULT hr;

	// モデルデータを読み込む
	hr = LoardModelData(FileName);
	ERROR_CHACK(hr);					// エラーチェック

	return S_OK;	// 正常終了
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	for(unsigned int i = 0; i < m_nModelNum; i++)
	{
		SALF_RELEASE(m_pModel[i].pMesh);
		SALF_RELEASE(m_pModel[i].pMatBuff);
	}
	SALF_DELETE_ARRAY(m_pModel);
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CModel::LoardModelData(char *FileName)
{
	// 変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();
	
	// デバイス初期化
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	// 結果
	HRESULT hr;

	// ファイル名
	char strFile[MAX_STR] = { NULL };

	// ファイルポインタ 初期化
	FILE *fp = NULL;							

	// ファイル読み込み
	fp = fopen(FileName, "r");
	if( fp == NULL)
	{
		// ファイルがない場合
		return E_FAIL;
	}

	// ファイル行数取得
	while(true)
	{
		// ファイルの行数取得
		if(fscanf(fp, "%s", &strFile) != EOF)
		{
			// 行数 = テクスチャの枚数
			m_nModelNum++;	// 行数カウント
		}
		else
		{
			// ファイルの中身が無くなった
			break;
		}
	}

	// テクスチャ変数　動的確保
	m_pModel = NEW X_FILE[m_nModelNum];

	// ファイルを読み込む
	fseek(fp, 0, SEEK_SET);

	// テクスチャ読み込み
	for( unsigned int i = 0; i < m_nModelNum; i++)
	{
		// テクスチャの名前を取得
		if(fscanf(fp, "%s", strFile) != EOF)
		{
			// ディレクトリ
			char Directory[MAX_STR]  = DIRECTORY;

			// ファイル名とディレクトリを配列する
			strcat(Directory, strFile);
			

			// テクスチャ読み込み
			hr = D3DXLoadMeshFromX( Directory ,				// ファイル名
									D3DXMESH_SYSTEMMEM,		// メッシュの書き方
									pDevice,				// デバイス
									NULL,					// 隣接性情報を受け取る
									&m_pModel[i].pMatBuff,	// マテリアルバッファの情報を受け取る
									NULL,					// 不明
									&m_pModel[i].nNumMat,	// 総マテリアル数
									&m_pModel[i].pMesh );	// メッシュ
			if( FAILED(hr) )
			{
				// 指定したテクスチャが存在しなければ
				fclose(fp);			// ファイルを閉じる
				return E_FAIL;		// 結果
			}
		}
	}

	// ファイルを閉じる
	fclose(fp);
	return S_OK;					// 結果
}
