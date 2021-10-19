//=============================================================================
// 処理 [meshwall.h]
//
// 製作者	: 松尾 雄太
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"
#include "sceneline.h"

class CSceneLine;

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	float					fWidth;			// ポリゴンの幅
	float					fHeight;		// ポリゴンの高さ
	int						nNumX;			// ブロックの数 X
	int						nNumY;			// ブロックの数	Z
	USHORT					nTexNum;		// 画像番号
	D3DXVECTOR3				pos;			// 壁オブジェクトの位置
	D3DXVECTOR3				rot;			// 壁オブジェクトの向き
	D3DXVECTOR3				scl;			// 壁オブジェクトの大きさ
}WALL;
	
//=============================================================================
// クラス宣言
//=============================================================================
class CWall : public CScene
{
public:
	CWall(int nPriority = 3, OBJTYPE objType = OBJTYPE_WALL);		// 壁オブジェクトインスタンス生成
	~CWall(void);													// 壁オブジェクトインスタンス破棄
	static CWall *Create(float fPolygonWidth, float fPolygonHeight,
						int nNumX, int nNumY, USHORT nTexNum);		// 壁オブジェクトの作成
	static CWall *CreateLoad(WALL dataWall);						// 壁オブジェクトの作成と読み込み
	HRESULT	Init(void);												// 壁オブジェクト初期化
	HRESULT Init(float fPolygonWidth, float fPolygonHeight, 
				int nNumX, int nNumY, USHORT nTexNum);				// 壁オブジェクト初期化
	void	Uninit(void);											// 壁オブジェクト破棄
	void	Update(void);											// 壁オブジェクトの更新
	void	Draw(void);												// 壁オブジェクトの描画

	WALL	GetData(void){ return m_DataWall; }						// 壁データ取得 

	void	SetTextureNum(USHORT nTexNum);							// 画像番号設定
	void	SetPosition(float fPosX, float fPosY, float fPosZ);		// 壁の位置設定
	void	SetPosition(D3DXVECTOR3 pos);							// 壁の位置設定
	void	SetRotition(float fPosX, float fPosY, float fPosZ);		// 壁の向き設定
	void	SetRotition(D3DXVECTOR3 rot);							// 壁の向き設定
	void	SetTexNum(USHORT nTexNum);								// 画像番号設定

	D3DXVECTOR3 GetPosition(void){return m_pos;}					// 壁の位置取得
	D3DXVECTOR3 GerRotition(void){return m_rot;}					// 壁の角度取得

private:
	void	LoadData(WALL dataWall);								// 壁データ読み込み
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight);	// 頂点作成関数	

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// 頂点バッファ用変数
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// 添字バッファ用変数
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャ	
	int						m_nVerTexMax;		// 頂点最大個数
	int						m_nIndexMax;		// 添字最大個数
	USHORT					m_nTexNum;			// テクスチャ番号保存
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3				m_pos;				// 壁オブジェクトの位置
	D3DXVECTOR3				m_rot;				// 壁オブジェクトの向き
	D3DXVECTOR3				m_scl;				// 壁オブジェクトの大きさ
	WALL					m_DataWall;			// 壁データ
};

#endif // _WALL_H_