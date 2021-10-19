//============================================================================= 
// オブジェクトリスト処理 [ scene.cpp ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: オブジェクトリスト管理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================

#include "scene.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScene *CScene::m_pTop[MAX_LIST] = {NULL};		// 先頭位置NULL 初期化
CScene *CScene::m_pCur[MAX_LIST] = {NULL};		// 現在位置NULL 初期化 

//=============================================================================
// 関数名	: CScene
// 戻り値	: なし 
// 引数値	: int 優先順位  OBJTYPE オブジェクトの種類
// 機能		: インスタンス生成
//=============================================================================
CScene::CScene(int nPriority, CScene::OBJTYPE objType)
{
	LinkList(nPriority, objType);
}

//=============================================================================
// 関数名	: UpdateAll
// 戻り値	: なし 
// 引数値	: なし
// 機能		: リスト内のオブジェクトをすべて更新
//=============================================================================
void CScene::UpdateAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// リスト分回す
		CScene *pScene = m_pTop[nList];			// 一番先頭にいるオブジェクトを保存
		while(pScene)							// オブジェクトが存在しなくなるまでループ
		{
			CScene *pNext = pScene->m_pNext;	// 次のオブジェクトを保存
			pScene->Update();					// 現在のオブジェクトを更新
			pScene = pNext;						// 次のオブジェクトに移動
		}
	}

	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// リスト分回す
		CScene *pScene = m_pTop[nList];			// 先頭位置を保存
		while( pScene )							// オブジェクトが存在しなくなるまでループ
		{
			// 次のオブジェクトが存在したら
			CScene *pNext = pScene->m_pNext;	// 次のオブジェクト保存
			if(pScene->m_bDethFlag == true)
			{
				// フラグが立っていたら
				pScene->Uninit();
				pScene->UnlinckList();			// リストから外す		
			}
			pScene = pNext;						// 次のオブジェクトに移動
		}
	}
}


//=============================================================================
// 関数名	: DrawAll
// 戻り値	: なし 
// 引数値	: なし
// 機能		: リスト内のオブジェクトをすべて描画
//=============================================================================
void CScene::DrawAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// リスト分回す
		CScene *pScene = m_pTop[nList];			// 一番先頭にいるオブジェクトを保存
		while( pScene )							// オブジェクトが存在しなくなるまでループ
		{
			CScene *pNext = pScene->m_pNext;	// 次のオブジェクトを保存
			pScene->Draw();						// 現在のオブジェクトを描画
			pScene = pNext;						// 次のオブジェクトに移動
		}
	}
}

//=============================================================================
// 関数名	: ReleaseAll
// 戻り値	: なし 
// 引数値	: なし
// 機能		: リスト内のオブジェクトをすべて破棄
//=============================================================================
void CScene::ReleaseAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// リスト分回す
		CScene *pScene = m_pTop[nList];			// 一番先頭にいるオブジェクトを保存
		while( pScene )							// オブジェクトが存在しなくなるまでループ
		{
			CScene *pNext = pScene->m_pNext;	// 次のオブジェクトを保存
			pScene->Uninit();					// 現在のオブジェクトの終了処理
			pScene->Release();					// オブジェクトを破棄
			pScene = pNext;						// 次のオブジェクトに移動
		}
	}

	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// リスト分回す
		CScene *pScene = m_pTop[nList];			// 先頭位置を保存
		while( pScene )							// オブジェクトが存在しなくなるまでループ
		{
			// 次のオブジェクトが存在したら
			CScene *pNext = pScene->m_pNext;	// 次のオブジェクト保存
			if(pScene->m_bDethFlag == true)
			{
				// フラグが立っていたら
				pScene->UnlinckList();			// リストから外す
			}
			pScene = pNext;						// 次のオブジェクトに移動
		}
	}

}

//=============================================================================
// 関数名	: LinkList
// 戻り値	: なし 
// 引数値	: int 優先順位  OBJTYPE オブジェクトの種類
// 機能		: リストに登録
//=============================================================================
void CScene::LinkList(int nPriority, CScene::OBJTYPE objType)
{
	if( m_pTop[nPriority] == NULL )
	{
		// もし先頭になんのリストも登録されていなければ
		m_pTop[nPriority] = this;		// 先頭は自分である
	}
	if( m_pCur[nPriority] == NULL )
	{
		// もし最後になんのリストも登録されていなければ
		m_pCur[nPriority] = this;		// 最後は自分である
	}

	m_pCur[nPriority]->m_pNext = this;	// 最後のリストの後に自分を登録

	if( m_pCur[nPriority] == this )
	{
		// もし最後が自分であるのなら後ろに誰も居ないのだから
		this->m_pPrev = NULL;			// 自分の後ろをNULLにする
	}
	else
	{
		m_pPrev = m_pCur[nPriority];
	}

	m_pCur[nPriority] = this;			// 最後を自分にする
	
	this->m_pNext = NULL;				// 自分の次は居ない
	
	m_nPriority = nPriority;			// 自分の優先番号を保存
	m_objType	= objType;				// 自分がどのオブジェなのか保存
	m_bDethFlag = false;				// 自分は生きているとする 
}

//=============================================================================
// 関数名	: UnlinkList
// 戻り値	: なし 
// 引数値	: なし
// 機能		: リストから外す
//=============================================================================
void CScene::UnlinckList(void)
{
	CScene *pScene;		// 現在のオブジェクトを代入用
	CScene *pNext;		// 自分の次のオブジェクトを保存用
	CScene *pPrev;		// 自分の前のオブジェクトを保存用
	pScene = m_pTop[m_nPriority];	// 同じ優先度の一番最初のオブジェクトを代入
	while( pScene )
	{
		pNext = pScene->m_pNext;		// 現在のオブジェクトの次のオブジェクトを保存
		if( pScene == this )
		{
			// もし先頭が自分だった場合
			if(pScene->m_pPrev)
			{
				// 現在のオブジェクトの前のオブジェクトがNULLな場合
				pScene->m_pPrev->m_pNext = pScene->m_pNext;		// 現在の前のオブジェクトの次のオブジェクトに現在のオブジェの次のオブジェクトを代入
			}
			if( pScene->m_pNext )
			{
				// 現在のオブジェクトの次のオブジェクトがNULLな場合
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;		// 現在の次のオブジェクトの前のオブジェクトに現在のオブジェクトの前のオブジェクトを代入
			}
			if(pScene == m_pTop[m_nPriority])
			{
				// 現在のオブジェクトが先頭のオブジェクトであるのなら
				m_pTop[m_nPriority] = pNext;					// 先頭のオブジェクトに次のオブジェクトを代入
			}
			pScene = pNext;
		}
		pScene = m_pCur[m_nPriority];	// 同じ優先度のオブジェクトの一番後ろのオブジェクトを代入
		while( pScene )
		{
			pPrev = pScene->m_pPrev;	// 現在のオブジェクトの前のオブジェクトを保存
			if( pScene == this)
			{
				// もし現在のオブジェクトが自分なら
				if(pScene->m_pPrev)
				{
					// 現在のオブジェクトの前のオブジェクトがNULLな場合
					pScene->m_pPrev->m_pNext = pScene->m_pNext;		// 現在のオブジェクトの前のオブジェクトの次のオブジェクトに現在のオブジェクトの次のオブジェクトを代入
				}
				if(pScene->m_pNext)
				{
					// 現在のオブジェクトの次のオブジェクトがNULLな場合
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;		// 現在のオブジェクトの次のオブジェクトの前のオブジェクトに現在のオブジェクトの前のオブジェクトを代入
				}
				if(pScene == m_pCur[m_nPriority])
				{
					// 現在のオブジェクトが最後のオブジェクトであるなら
					m_pCur[m_nPriority] = pPrev;					// 最後のオブジェクトに前のオブジェクトを代入
				}
		}
		pScene = pPrev;
		}
	}
	delete this;
}

//=============================================================================
// 関数名	: Release
// 戻り値	: なし 
// 引数値	: なし
// 機能		: リストから破棄
//=============================================================================
void CScene::Release(void)
{
	m_bDethFlag = true;
}
