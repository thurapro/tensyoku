//=============================================================================
// 木処理 [Tree.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: 木作成
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "stage.h"
#include "tree.h"

//=============================================================================
// 関数名	: Tree
// 戻り値	: なし
// 引数値	: 優先度 オブジェの種類
// 機能		: 木のインスタンス生成
//=============================================================================
CTree::CTree(int nPriority, OBJTYPE objType):CBillboard(nPriority, objType)
{
}

//=============================================================================
// 関数名	: ~Tree
// 戻り値	: なし
// 引数値	: なし
// 機能		: 木のインスタンス破棄
//=============================================================================
CTree::~CTree(void)
{
	// 処理なし
}

//=============================================================================
// 関数名	: Create
// 戻り値	: 木のポインタ
// 引数値	: ポリゴンの大きさ(幅、高さ), 画像番号
// 機能		: 木作成
//=============================================================================
CTree *CTree::Create(float fWidth, float fHeight, USHORT nTexNum)
{
	// 変数宣言
	HRESULT hr = S_OK;
	CTree *pTree = NULL;						// 木のポインタ
	NEW_TYPE(pTree, CTree);						// 初期化

	// 初期化
	hr = pTree->Init(fWidth, fHeight, nTexNum);	// 木初期化
	if( FAILED(hr) )
	{
		return NULL;							// エラーコード
	}

	return pTree;								// 正常コード
}

//=============================================================================
// 関数名	: CreateLoad
// 戻り値	: 木のポインタ
// 引数値	: 木のデータ
// 機能		: 木の作成 & データ読み込み
//=============================================================================
CTree *CTree::CreateLoad(BILLBOARD dataTree)
{
	// 変数宣言
	HRESULT hr = S_OK;
	bool bLoad = true;
	CTree *pTree = NULL;
	
	NEW_TYPE(pTree, CTree);						// 初期化

	
	// 木のデータ読み込み
	bLoad = pTree->LoadData(dataTree);
	if( bLoad = false )
	{
		return NULL;		// エラーコード
	}

	// 初期化
	hr = pTree->Init(dataTree.fWidth, dataTree.fHeight, 
						dataTree.nTexNum);		// 木初期化
	if( FAILED(hr) )
	{
		return NULL;							// エラーコード
	}
	
	return pTree;
}


//=============================================================================
// 関数名	: Init
// 戻り値	: なし
// 引数値	: なし
// 機能		: 木の初期化
//=============================================================================
HRESULT CTree::Init(float fWidth, float fHeight, USHORT nTexNum)
{
	// 変数宣言
	HRESULT hr = S_OK;		// 判定
	
	// 初期化処理
	hr = CBillboard::Init(fWidth, fHeight, nTexNum);
	ERROR_CHACK(hr);		// エラーチェック
	
	return S_OK;
}

//=============================================================================
// 関数名	: Uninit 
// 戻り値	: なし
// 引数値	: なし
// 機能		: 木破棄
//=============================================================================
void CTree::Uninit(void)
{
	CBillboard::Uninit();	// 終了処理
}

//=============================================================================
// 関数名	: Updata
// 戻り値	: なし
// 引数値	: なし
// 機能		: 木の更新
//=============================================================================
void CTree::Update(void)
{
	CStage *pStage = CManager::GetStage();
	
	CField **pField = pStage->GetField();
	int		nFieldNum = 0;
	pStage->GetFieldNum(nFieldNum);

	if( pField )
	{
		for( int field = 0; field < nFieldNum; field++ )
		{
			// 地面の高さ取得
			m_DataBillboard.pos.y = pField[field]->GetHeight(m_DataBillboard.pos);
		}
	}

	m_pos.y = m_DataBillboard.pos.y;
	SetPosition(m_pos);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数値	: なし
// 機能		: 木の描画
//=============================================================================
void CTree::Draw(void)
{
	CBillboard::Draw();
}

// end of file