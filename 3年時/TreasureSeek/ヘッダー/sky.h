//=============================================================================
// メッシュの多い空処理 [ sky.h ]
//
// 製作者	: 松尾 雄太
//
// 機能		: 空作成
//=============================================================================


//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

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
	D3DXVECTOR3		pos;		// 空の位置
	D3DXVECTOR3		rot;		// 空の向き
	D3DXVECTOR3		scl;		// 空の大きさ
}SKY;

//=============================================================================
// クラス宣言
//=============================================================================
class CSky : public CScene
{
public:	// 操作
	CSky(int nPriority = 2, OBJTYPE objType = OBJTYPE_SKY);				// インスタンス生成
	~CSky(void);														// インスタンス破棄
	static CSky* Create(float fPolygonWidth, float fPolygonHeight,		
						int nNumX, int nNumY, float fR, 
						USHORT nTexNum);								// 空の生成
	static CSky* CreateLoad(SKY dataSky, USHORT nTexNum);				// 空の生成、読み込み 

	HRESULT Init(void){return S_OK;}									// 空の初期化
	HRESULT Init(float fPolygonWidth, float fPolygonHeight,		
				int nNumX, int nNumY, float fR, 
				USHORT nTexNum);										// 空の初期化
	void	Uninit(void);												// 空の破棄
	void	Update(void);												// 空の更新
	void	Draw(void);													// 空の描画

	void	SetTextureNum(USHORT nTexNum);								// 画像番号設定
	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// 空の位置設定
	void	SetPosition(D3DXVECTOR3 pos);								// 空の位置設定
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// 空の向き設定
	void	SetRotition(D3DXVECTOR3 rot);								// 空の向き設定

	D3DXVECTOR3	GetPosition(void){ return m_DataSky.pos; }				// 空の位置取得
	D3DXVECTOR3	GerRotition(void){ return m_DataSky.rot; }				// 空の角度取得
	SKY			GetData(void){ return m_DataSky; }						// 空データを取得 

private: // 要素
	void LoadData(SKY dataSKy);													// 空データ生成&読み込み
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight, float fR);	// 頂点作成

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;							// 頂点バッファ用変数
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;								// 添字バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャ
	D3DXVECTOR3				*m_pVtx;									// 頂点位置格納
	int						m_nVerTexMax;								// 頂点最大個数
	int						m_nIndexMax;								// 添字最大個数
	USHORT					m_nTexNum;									// テクスチャ番号保存
	D3DXMATRIX				m_mtxWorld;									// ワールドマトリックス
	D3DXVECTOR3				m_pos;										// 空の位置
	D3DXVECTOR3				m_rot;										// 空の向き
	D3DXVECTOR3				m_scl;										// 空の大きさ
	SKY						m_DataSky;									// 空のデータ
}; // class End  

#endif // _SKY_H_

// end of file
