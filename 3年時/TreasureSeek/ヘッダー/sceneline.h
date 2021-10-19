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
#ifndef _SCENELINE_H_
#define _SCENELINE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CSceneLine :public CScene 
{
public: 
	CSceneLine(int nPriority = 3);		// 3Dオブジェクトインスタンス生成
	~CSceneLine(void);					// 3Dオブジェクトインスタンス破棄
	HRESULT	Init(void);					// 3Dオブジェクト初期化
	HRESULT Init(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);
	void	Uninit(void);				// 3Dオブジェクト破棄
	void	Update(void);				// 3Dオブジェクトの更新
	void	Draw(void);					// 3Dオブジェクトの描画
	static CSceneLine *Create(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);		// 3Dオブジェクトの作成
private:
	// 頂点作成関数
	HRESULT MakeVerTex(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);	

	// 3Dポリゴンに必要な要素
	typedef struct
	{
		D3DXVECTOR3 vtx;						// 頂点
		D3DXVECTOR3 nor;						// ベクトルの向き(裏か表)向き
		D3DCOLOR	diffuse;					// 頂点色を設定
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ用変数

	D3DXMATRIX	m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 3Dオブジェクトの位置
	D3DXVECTOR3 m_rot;							// 3Dオブジェクトの向き
	D3DXVECTOR3 m_scl;							// 3Dオブジェクトの大きさ
};

#endif //_SCENELINE_H_