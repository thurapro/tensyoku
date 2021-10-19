//=============================================================================
//
// title処理 [title.h] 松尾 雄太
//
//=============================================================================

//=============================================================================
// 2重インクルード
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Font.h"
#include "InputKey.h"
#include "WinMain.h"
#include <dsound.h>
#include "Sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
typedef struct
{
	float fPosX;									// 画像の設置位置
	float fPosY;									// 画像の設置位置
	float fWidth;									// 画像の幅
	float fHeight;									// 画像の高さ
	float fTexX0;									// 画像の座標X
	float fTexY0;									// 画像の座標Y
	float fTexX1;									// 画像の座標X
	float fTexY1;									// 画像の座標Y
	float fMoveX;									// モーションの速度
	float fMoveY;									// モーション速度
}Title;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitTitle(LPDIRECT3DDEVICE9 pDevice);		// 初期化
void UninitTitle(void);								// 破棄
void UpdateTitle(void);								// 更新
void DrawTitle(LPDIRECT3DDEVICE9 pDevice);			// 描画

#endif // _TITLE_H_