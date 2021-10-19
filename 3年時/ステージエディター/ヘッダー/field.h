//=============================================================================
// 処理 [meshfield.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: メシュの多い地面生成
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================

// 前方参照
#include "sceneline.h"

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	float			fWidth;		// ポリゴンの幅
	float			fLength;	// ポリゴンの奥行
	int				nNumX;		// ポリゴン数(横)
	int				nNumZ;		// ポリゴン数(縦)
	float			*fY;		// 高さ
	int				nVerMax;	// 頂点数
	USHORT			nTexNum;	// 画像番号
	D3DXVECTOR3		pos;		// 地面の位置
	D3DXVECTOR3		rot;		// 地面の向き
	D3DXVECTOR3		scl;		// 地面の大きさ
}FIELD;

//=============================================================================
// クラス宣言
//=============================================================================
class CField : public CScene
{
public: 
	CField(int nPriority = 4, OBJTYPE objType = OBJTYPE_FIELD);						// 地面インスタンス生成
	~CField(void);																	// 地面インスタンス破棄
	static CField *Create(float fPolygonWidth, float fPolygonHeight, 
							int nNumX, int nNumZ,	USHORT nTexNum);				// 地面の作成
	static CField *CreateLoad(FIELD dataField, USHORT nTexNum);						// 地面生成と読み込み
	HRESULT	Init(void){ return S_OK; }												// 地面初期化
	HRESULT Init(float fPolygonWidth, float fPolygonHeight, 
				int nNumX, int nNumZ,	USHORT nTexNum);							// 初期化処理(通常)

	void	Uninit(void);															// 地面破棄
	void	Update(void);															// 地面の更新
	void	Draw(void);																// 地面の描画

	void	SetPosition(float fPosX, float fPosY, float fPosZ);						// 地面の位置設定
	void	SetPosition(D3DXVECTOR3 pos);											// 地面の位置設定
	void	SetRotition(float fRotX, float fRotY, float fRotZ);						// 地面の向き設定
	void	SetRotition(D3DXVECTOR3 rot);											// 地面の向き設定
	void	SetHeight(float *fY);													// 地面の高さ設定
	void	SetTexNum(USHORT nTexNum);

	D3DXVECTOR3 GetPosition(void){ return m_pos; }									// 地面の位置取得
	D3DXVECTOR3 GetRotition(void){ return m_rot; }									// 地面の向き取得
	D3DXVECTOR3 *GetVector(void){ return &m_pNor[0]; }								// 地面の法線ベクトル取得
	float		GetHeight(D3DXVECTOR3 pos);											// 地面の高さ取得
	FIELD		GetData(void){ return m_DataField; }								// 地面データ取得
	float		*GetFieldHeight(void){ return &m_DataField.fY[0]; }					// 地面の高さを保存
	LPDIRECT3DVERTEXBUFFER9	 GetVertex(void){ return m_pVertexBuffer;}				// 頂点バッファ取得

private:
	bool	LoadData(FIELD dataField);												// 地面のマップ読み込み
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight);					// 頂点作成関数	
	void	GetNormalVec(void);														// 法線算出

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ用変数
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// 添字バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャ
	D3DXVECTOR3				*m_pNor;			// 法線ベクトル格納
	CSceneLine				**m_ppLine;			// 法線ライン
	int						m_nVerTexMax;		// 頂点最大個数
	int						m_nIndexMax;		// 添字最大個数
	USHORT					m_nTexNum;			// テクスチャ番号保存
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3				m_pos;				// 地面の位置
	D3DXVECTOR3				m_rot;				// 地面の向き
	D3DXVECTOR3				m_scl;				// 地面の大きさ
	FIELD					m_DataField;		// 地面データ
	int						m_nPoint;			// 設定する頂点の添字
	int						m_nSpeed;			// 地面をあげる速度
};	// class End

#endif //_MESHFIELD_H_