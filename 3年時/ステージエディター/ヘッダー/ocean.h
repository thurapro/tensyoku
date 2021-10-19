//=============================================================================
// 処理 [Ocean.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: メシュの多い海生成
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _OCEAN_H_
#define _OCEAN_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// 構造体設定
//=============================================================================
typedef struct
{
	float			fWidth;			// 幅
	float			fLength;		// 大きさ
	int				nNumX;			// 横の数
	int				nNumZ;			// 縦の数
	int				nSpeed;			// 波のうつスピード
	USHORT			nTexNum;		// 画像番号
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 向き
}OCEAN;
	
//=============================================================================
// クラス宣言
//=============================================================================
class COcean : public CScene
{
public: 
	COcean(int nPriority = 4, OBJTYPE objType = OBJTYPE_OCEAN);						// 海インスタンス生成
	~COcean(void);																	// 海インスタンス破棄
	static COcean *Create(float fPolygonWidth, float fPolygonLength, 
							int nNumX, int nNumZ, 
							USHORT nTexNum);										// 海の作成
	static COcean *CreateLoad(OCEAN dataOcean);										// 海データ作成、読み込み
	HRESULT	Init(void){return S_OK;}												// 海初期化
	HRESULT Init(float fPolygonWidth, float fPolygonLength, 
				int nNumX, int nNumZ, 
				USHORT nTexNum);													// 初期化処理
	void	Uninit(void);															// 海破棄
	void	Update(void);															// 海の更新
	void	Draw(void);																// 海の描画
	void	SetPosition(float fPosX, float fPosY, float fPosZ);						// 海の位置設定
	void	SetPosition(D3DXVECTOR3 pos);											// 海の位置設定
	void	SetRotition(float fRotX, float fRotY, float fRotZ);						// 海の向き設定
	void	SetRotition(D3DXVECTOR3 rot);											// 海の向き設定
	void	SetTexNum(USHORT nTexNum);												// 海の画像張替え

	D3DXVECTOR3 GetPosition(void){return m_pos;}									// 海の位置取得
	D3DXVECTOR3 GetRotition(void){return m_rot;}									// 海の向き取得
	OCEAN	GetData(void){return m_DataOcean;}										// 海データ取得

private:
	HRESULT MakeVerTex( float fPolygonWidth , float fPolygonLength);				// 頂点作成関数
	void	NorVertex(void);														// 法線作成
	bool	LoadData(OCEAN dataOcean);												// 海データ読み込み

	// 3Dポリゴンに必要な要素
	typedef struct
	{
		D3DXVECTOR3 vtx;						// 頂点
		D3DXVECTOR3 nor;						// ベクトルの向き(裏か表)向き
		D3DCOLOR	diffuse;					// 頂点色を設定
		D3DXVECTOR2	tex;						// テクスチャ頂点
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ用変数
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// 添字バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャ
	
	D3DXVECTOR3 *m_pVertex;						// 頂点格納
	D3DXVECTOR3 *m_pNor;						// 法線ベクトル格納
	
	int		m_nVerTexMax;						// 頂点最大個数
	int		m_nIndexMax;						// 添字最大個数
	USHORT	m_nTexNum;							// テクスチャ番号保存
	
	D3DXMATRIX	m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 海の位置
	D3DXVECTOR3 m_rot;							// 海の向き
	D3DXVECTOR3 m_scl;							// 海の大きさ
	int			m_nTimeCnt;
	float		m_fAngle;						// 角度
	OCEAN		m_DataOcean;					// 海データ
};

#endif //_OCEAN_H_