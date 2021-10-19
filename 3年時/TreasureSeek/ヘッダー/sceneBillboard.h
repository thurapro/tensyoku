//=============================================================================
// 処理 [sceneBillboard.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: ビルボード作成
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

typedef struct
{
	float		fWidth;		// ポリゴンの幅
	float		fHeight;	// ポリゴンの高さ	
	USHORT		nTexNum;	// ポリゴンの大きさ
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3 scl;		// 大きさ
}BILLBOARD;

//=============================================================================
// クラス宣言
//=============================================================================
class CBillboard : public CScene 
{
public:
	CBillboard(int nPriority = 4, OBJTYPE objType = OBJTYPE_BILLBOARD);		// ビルボードインスタンス生成
	~CBillboard(void);														// ビルボードインスタンス破棄
	static CBillboard *Create(float fWidth, float fHeight, 
								USHORT nTexNum);							// ビルボード作成
	static CBillboard *CreateLoad(BILLBOARD dataBillboard);					// ビルボード作成	
	HRESULT Init(void);														// ビルボード初期化
	HRESULT Init(float fWidth, float fHeight, 
						USHORT nTexNum);									// ビルボード初期化
	HRESULT Init(BILLBOARD dataBillboard);									// ビルボード初期化
	void Uninit(void);														// ビルボード終了
	void Update(void);														// ビルボード更新
	void Draw(void);														// ビルボード描画

	void		SetPosition(float fPosX, float fPosY, float fPosZ);			// ビルボードの位置設定
	void		SetPosition(D3DXVECTOR3 pos);								// ビルボードの位置設定
	void		SetScale(float fSclX, float fSclY, float fSclZ);			// ビルボードの大きさ設定
	void		SetScale(D3DXVECTOR3 scl);									// ビルボードの大きさ設定
	void		SetTexturePos(float fTexX, float fTexY,				
								float fTexWidth, float fTexHeight);			// テクスチャ座標設定
	void		SetTextureNum(USHORT nTexNum);								// 画像番号設定

	D3DXVECTOR3 GetPosition(void){return m_pos;}							// 位置取得
	BILLBOARD	GetData(void){return m_DataBillboard;}						// ビルボードデータ取得

protected:
	bool LoadData(BILLBOARD dataBillboard);									// ビルボードデータ読み込み
	D3DXVECTOR3				m_pos;											// 位置
	D3DXVECTOR3				m_rot;											// 向き
	D3DXVECTOR3				m_scl;											// 大きさ
	BILLBOARD				m_DataBillboard;								// ビルボードデータ

private:
	HRESULT MakeVertex(float fWidth, float fHeight);						// 頂点バッファ作成 
	
	D3DXMATRIX				m_mtxWorld;										// ワールド
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								// 頂点バッファ
	LPDIRECT3DTEXTURE9		m_pTexture;										// テクスチャ
	USHORT					m_nTexNum;										// テクスチャ番号
};

#endif // _BILLBOARD_H_