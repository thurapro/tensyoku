//=============================================================================
//
// フィールド処理 [Field.h]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "InputKey.h"
#include "common.h"
#include "Shadow.h"
#include "Bullet.h"
#include "meshWall.h"
#include "Font.h"
#include "Sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_TYPE (0)									// プレイヤータイプ

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT PlayerInit( LPDIRECT3DDEVICE9 pD3DDevice );		// モデルの初期化
void PlayerUninit( void );								// モデルの破棄
void PlayerUpdate( void );								// モデルの更新
void PlayerDraw( LPDIRECT3DDEVICE9 pD3DDevice );			// 影更新
D3DXVECTOR3 PlayerPosGet( void );							// モデルの位置取得
D3DXVECTOR3 PlayerRotGet(void);								// プレイヤーの向き
bool PlayerStop(bool bStop );

#endif	// _MODEL_H_
