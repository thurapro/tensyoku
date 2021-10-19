//=============================================================================
// 影の処理 [shadow.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: 影の作成 
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 関数名	: CShadow
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス生成( 初期化 )
//=============================================================================
CShadow::CShadow(int nPriority, OBJTYPE objType):CScene3D(nPriority, objType)
{
	// インスタンス生成
}

//=============================================================================
// 関数名	: ~CShadow
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄( 終了 )
//=============================================================================
CShadow::~CShadow(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: 影 ( 失敗 NULL )
// 引数値	: 位置 ( X, Y, Z ), 大きさ( 幅 , 高さ, 奥行), テクスチャ番号
// 機能		: 影の生成
//=============================================================================
CShadow *CShadow::Create(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						unsigned int nTexNum)
{
	HRESULT hr;						// エラーチェック変数
	CShadow *pShadow = NULL;		// 影ポインタ
	if( pShadow == NULL )
	{
		// 作られていなければ
		pShadow = NEW CShadow;		// 影インスタンス生成
		hr = pShadow->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength, nTexNum);	// 初期化
		if( FAILED(hr) )	
		{
			// エラーチェック
			return NULL;		// エラーコード
		}
	}
	return pShadow;				// 影を返す
}

//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数値	: 位置 ( X, Y, Z ), 大きさ( 幅 , 高さ, 奥行), テクスチャ番号
// 機能		: 影の初期化処理
//=============================================================================
HRESULT CShadow::Init(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						unsigned int nTexNum)
{
	HRESULT hr;			// エラーチェック変数
	hr = CScene3D::Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength, nTexNum);
	ERROR_CHACK(hr);	// エラーチェック
	return S_OK;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: 影の終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	CScene3D::Uninit();		// 影の終了処理
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数値	: なし
// 機能		: 影の更新処理
//=============================================================================
void CShadow::Update(void)
{
	// 影の更新
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: 影の描画処理
//=============================================================================
void CShadow::Draw(void)
{
	// 影の描画
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// デバイス取得
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE );
	CScene3D::Draw();
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);				// 減算処理
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);			// 加算処理
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);		
}


