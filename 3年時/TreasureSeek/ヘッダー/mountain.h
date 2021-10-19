//=============================================================================
// メッシュの多い山処理 [ mountain.h ]
//
// 製作者	: 松尾 雄太
//
// 機能		: 山を作成
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _MONTAIN_H_
#define _MONTAIN_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"		// クラスCScene

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	float			fWidth;		// ポリゴンの幅
	float			fHeight;	// ポリゴンの高さ
	int				nNumX;		// ブロックの数 X
	int				nNumY;		// ブロックの数	Y				
	float			fR;			// 半径
	D3DXVECTOR3		pos;		// 山の位置
	D3DXVECTOR3		rot;		// 山の向き
	D3DXVECTOR3		scl;		// 山の大きさ
}MOUNTAIN;

//=============================================================================
// クラス宣言
//=============================================================================
class CMountain : public CScene
{
public:	// 操作
	CMountain(int nPriority = 3, OBJTYPE objType = OBJTYPE_MOUNTAIN);	// インスタンス生成
	~CMountain(void);													// インスタンス破棄
	static CMountain* Create(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum);							// 山の生成
	static CMountain* CreateLoad( MOUNTAIN dataMountain, USHORT nTexNum);
	
	HRESULT Init(void){ return S_OK; }									// 山の初期化
	HRESULT Init(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum);							// 山の初期化
	void	Uninit(void);												// 山の破棄
	void	Update(void);												// 山の更新
	void	Draw(void);													// 山の描画

	void	SetTextureNum(USHORT nTexNum);								// 画像番号設定
	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// 山の位置設定
	void	SetPosition(D3DXVECTOR3 pos);								// 山の位置設定
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// 山の向き設定
	void	SetRotition(D3DXVECTOR3 rot);								// 山の向き設定

	D3DXVECTOR3	GetPosition(void){ return m_DataMountain.pos; }			// 山の位置取得
	D3DXVECTOR3	GerRotition(void){ return m_DataMountain.rot; }			// 山の角度取得
	MOUNTAIN	GetData(void){ return m_DataMountain; }					// 山データを取得 


private: // 要素
	void LoadData(MOUNTAIN dataMountain);										// 山データ生成&読み込み
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight, float fR);	// 頂点作成

	// 3Dポリゴンに必要な要素
	typedef struct
	{
		D3DXVECTOR3 vtx;								// 頂点
		D3DXVECTOR3 nor;								// ベクトルの向き(裏か表)向き
		D3DCOLOR	diffuse;							// 頂点色を設定
		D3DXVECTOR2	tex;								// テクスチャ頂点
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;			// 頂点バッファ用変数
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;				// 添字バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャ
	int						m_nVerTexMax;				// 頂点最大個数
	int						m_nIndexMax;				// 添字最大個数
	USHORT					m_nTexNum;					// テクスチャ番号保存
	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3				m_pos;						// 山の位置
	D3DXVECTOR3				m_rot;						// 山の向き
	D3DXVECTOR3				m_scl;						// 山の大きさ
	MOUNTAIN				m_DataMountain;				// 山データ
}; // class End  


#endif // _MOUNTAIN_H_