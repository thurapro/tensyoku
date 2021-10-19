//============================================================================= 
// 2Dオブジェクト処理 [ scene2D.h ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: 2Dオブジェクト作成処理
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2Dテクスチャー設定

//=============================================================================
// クラス宣言
//=============================================================================
class CScene2D : public CScene		// CSceneの派生
{
public:		// 操作
	CScene2D(int nPriority = 5, OBJTYPE objType = OBJTYPE_2D);		// インスタンス生成
	~CScene2D(void);												// インスタンス破棄
	static CScene2D *Create(float fPosX, float fPosY, 
							float fWidth, float fHeight,
							unsigned short nTextureNumber);			// 2Dオブジェクト作成
	HRESULT	Init(void);												// 2Dオブジェクト初期化処理
	HRESULT Init(float fPosX, float fPosY, 
				 float fWidth, float fHeight,
				 unsigned short nTextureNumber);					// 2Dオブジェクト初期化処理
	void	Uninit(void);											// 2Dオブジェクト終了処理
	void	Update(void);											// 2Dオブジェクト更新処理
	void	Draw(void);												// 2Dオブジェクト描画処理

	void	SetPosition(float fPosX, float fPosY,
							float fWidth, float fHeigh);			// 位置設定
	void	SetColor(int nR, int nG, int nB, int nA);				// 色設定
	void	SetTexure(float fTexX, float fTexY,						// テクスチャ座標設定
						float fTexWidth, float fTexHeight );
	void	SetTexNum(unsigned short nTexNum);						// テクスチャ番号設定

	D3DXVECTOR2	GetPosition(void){return m_pos;}					// 位置取得

protected:	// 要素
	HRESULT MakeVertex( float fPosX, float fPosY, 
						float fWidth, float fHeight);				// 頂点作成


	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ
	unsigned short			m_nTextureNum;		// テクスチャ番号
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャ
	D3DXVECTOR2				m_pos;				// 位置
};
	


#endif // _SCENE2D_H_