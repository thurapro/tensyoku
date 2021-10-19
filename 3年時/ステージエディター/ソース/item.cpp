//=============================================================================
// アイテム処理[item.cpp]
//
// 製作者 : 松尾 雄太
//
// 機能 :  アイテム
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "manager.h"
#include "field.h"
#include "shadow.h"
#include "item.h"
#include "data.h"
#include "scene.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_NUM_INIT		(-1)		// モデル初期値
#define TEXTURE_NUM_INIT	(-1)		// 画像初期値

//=============================================================================
// 関数名	: CItem
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス生成
//=============================================================================
CItem::CItem(int nPriority, OBJTYPE objType):CSceneX(nPriority, objType)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// Xオブジェクトの向き
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// Xオブジェクトの大きさ
	m_nModelNum		= MODEL_NUM_INIT;			// モデル番号
	m_nTextureNum	= TEXTURE_NUM_INIT;			// テクスチャ番号
	m_pTexture		= NULL;						// テクスチャデータ
	m_pShadow		= NULL;						// 影の初期化
}

//=============================================================================
// 関数名	: ~CItem
// 戻り値	: なし
// 引数値	: なし
// 機能		: インスタンス破棄
//=============================================================================
CItem::~CItem(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: CItem		(エラー NULL) 
// 引数値	: 表示位置 ( X , Y, Z ) , テクスチャ番号
// 機能		: なし
//=============================================================================
CItem *CItem::Create(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;					// エラーチェック変数
	CItem *pItem = NULL;		// アイテム初期化
	pItem = NEW CItem;			// アイテムインスタンス生成
	hr = pItem->Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);
	if( FAILED(hr) )
	{
		// エラーチェック
		return NULL;		// 作成失敗
	}
	return pItem;			// アイテムを返す
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT 
// 引数値	: 表示位置 ( X , Y, Z ) , テクスチャ番号
// 機能		: なし
//=============================================================================
HRESULT CItem::Init(void)
{
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT 
// 引数値	: 表示位置 ( X , Y, Z ) , モデル番号 , テクスチャ番号
// 機能		: なし
//=============================================================================
HRESULT CItem::Init(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;		// エラーチェック変数
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// アイテム初期化
	m_fRadius	= 5.0f;
	ERROR_CHACK(hr);	// エラーチェック

	if( m_pShadow == NULL )
	{
		m_pShadow = CShadow::Create(m_pos.x, m_pos.y, m_pos.z, 10, 0, 10, 5);
	}

	return S_OK;		// 正常コード
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数値	: なし
// 機能		: アイテム終了処理
//=============================================================================
void CItem::Uninit(void)
{
	CSceneX::Uninit();		// アイテム破棄
	m_pShadow->Uninit();
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数値	: なし
// 機能		: アイテム更新処理
//=============================================================================
void CItem::Update(void)
{
	float fHeight = 0;
	CField	*pField = NULL;
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:
	//	//pField = CManager::GetTitle();
	//	break;
	//case CManager::MODE_GAME:
	//	pField = CManager::GetGame()->GetField();
	//	break;
	//default:
	//	break;
	//}
	if( pField )
	{
		fHeight = pField->GetHeight(m_pos);
		m_pos.y = fHeight + m_fRadius;
	}

	m_pShadow->SetPosition(m_pos.x, fHeight + 1, m_pos.z);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: アイテム描画
//=============================================================================
void CItem::Draw(void)
{
	CSceneX::Draw();		// 描画
}

// end of file