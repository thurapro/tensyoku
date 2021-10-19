//============================================================================= 
// 一括管理処理 [ common.h ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: ヘッダーなどを一括管理
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _COMMON_H_
#define _COMMON_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include <Windows.h>
#include <crtdbg.h>

//=============================================================================
// マクロ定義
//=============================================================================
#pragma warning (disable : 4996)

#define NEW											new(	_NORMAL_BLOCK,	__FILE__,	__LINE__	)	// newマクロ
#define NEW_TYPE( p , Class )						{ if(!p){ (p) = NEW Class; } }						// メモリ確保
#define NEW_TYPE_ARRAY( p, Class, num )				{ if(!p){ (p) = NEW Class[num]; } }					// メモリ確保(配列)
#define NEW_PRIOBJTYPE( p, Class, pri, objType )	{ if(!p){ (p) = NEW Class(pri, objType) }			// メモリ確保(優先度, 種類)
#define SALF_RELEASE( p )							{ if(p){ (p)->Release(); (p) = NULL; } } 			// Releseマクロ
#define SALF_DELETE( p )							{ if(p){ delete (p); (p) = NULL; } }				// deleteマクロ
#define SALF_DELETE_ARRAY( p )						{ if(p){ delete[] (p); (p) = NULL; } }				// 配列deleteマクロ
#define CLASS_DELETE( c )							{ if(c){ (c)->Uninit(); delete (c); (c) = NULL; } }	// クラスのdeleteマクロ
#define ERROR_CHACK( hr )							{ if(FAILED(hr)){return E_FAIL;} }					// エラーチェック

#endif // _COMMON_H_

// end of file
