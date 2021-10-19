//=============================================================================
// メッシュ3Dオブジェクト処理 [cylinder.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: メッシュの多い3Dオブジェクトを作成
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CScene3D :public CScene 
{
public: 
	CScene3D(int nPriority = 2, OBJTYPE objType = OBJTYPE_3D);							// 3Dオブジェクトインスタンス生成
	~CScene3D(void);																	// 3Dオブジェクトインスタンス破棄
	static CScene3D *Create(float fPosX, float fPosY, float fPosZ, 
							float fWidth, float fHeight, float fLength,
							unsigned int nTexNum);										// 3Dオブジェクトの作成
	HRESULT	Init(void);																	// 3Dオブジェクト初期化
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				float fWidth, float fHeight, float fLength,
				unsigned int nTexNum);													// 3Dオブジェクト初期化
	void	Uninit(void);																// 3Dオブジェクト破棄
	void	Update(void);																// 3Dオブジェクトの更新
	void	Draw(void);																	// 3Dオブジェクトの描画

	void	SetPosition(float fPosX, float fPosY, float fPosZ);							// 位置設定
	void	SetPosition(D3DXVECTOR3 pos);												// 位置設定
	void	SetRotiton(float fRotX, float fRotY, float fRotZ);							// 向き設定
	void	SetRotiton(D3DXVECTOR3 rot);												// 向き設定
	void	SetScale(float fSclX, float fSclY, float fSclZ);							// 大きさ設定
	void	SetScale(D3DXVECTOR3 scl);													// 大きさ設定

	D3DXVECTOR3 GetPotition(void){return m_pos;}										// 位置取得
	D3DXVECTOR3 GetRotition(void){return m_rot;}										// 向き取得
	D3DXVECTOR3 GetScale(void){return m_scl;}											// 大きさ取得
	unsigned int GetTexNum(void){return m_nTexNum;}										// テクスチャの番号取得

protected:
	// 頂点作成関数
	HRESULT MakeVerTex(float fPosX, float fPosY, float fPosZ, 
						float fWidth, float fHeight, float fLength);	

	// 3Dポリゴンに必要な要素
	typedef struct
	{
		D3DXVECTOR3 vtx;						// 頂点
		D3DXVECTOR3 nor;						// ベクトルの向き(裏か表)向き
		D3DCOLOR	diffuse;					// 頂点色を設定
		D3DXVECTOR2	tex;						// テクスチャ頂点
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャ

	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 3Dオブジェクトの位置
	D3DXVECTOR3 m_rot;							// 3Dオブジェクトの向き
	D3DXVECTOR3 m_scl;							// 3Dオブジェクトの大きさ

	unsigned int m_nTexNum;						// テクスチャ番号取得

};

#endif //_SCENE3D_H_