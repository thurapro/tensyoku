//=============================================================================
// 番号処理[number.h]
//
// 製作者 : 松尾 雄太
//
// 機能 :  スコアー・タイマーなど 
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// インクルード
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2Dテクスチャー設定

//=============================================================================
// クラス宣言
//=============================================================================
class CNumber
{
public:
	CNumber(void);											// 番号インスタンス生成
	~CNumber(void);											// 番号インスタンス破棄

	static CNumber	*Create(D3DXVECTOR3 fPosLeftTop, 
							D3DXVECTOR3 fPosRightTop, 
							D3DXVECTOR3 fPosLeftBottom, 
							D3DXVECTOR3 fPosRightBottom,
							unsigned int nTexNum);			// 番号作成

	static CNumber	*Create(float fPosX, float fPosY, 
							float fWidth, float fHeight, 
							unsigned int nTexNum);			// 番号作成

	HRESULT Init(D3DXVECTOR3 fTexPosLeftTop, 
				D3DXVECTOR3 fPosRightTop, 
				D3DXVECTOR3 fPosLeftBottom, 
				D3DXVECTOR3 fPosRightBottom,
				unsigned int nTexNum);						// 番号初期化処理

	HRESULT Init(float fPosX, float fPosY,
				float fWidth, float fHeight,
				unsigned int nTexNum);						// 番号初期化処理

	void Uninit(void);										// 番号終了処理
	void Update(void);										// 番号更新処理
	void Draw(void);										// 番号描画処理

	// テクスチャ座標位置セット 
	void SetNumberTexture(unsigned int nNumber);
	
	void SetPosition(float fPosX, float fPosY,
					float fWidht, float fHeight);
	
	void SetPosHeight(float fPosY, float fHeight);
	void SetNumColor(int nR, int nG, int nB, int nA); 

	unsigned int GetNumber(void){return m_nNumber;}

private:
	// 頂点作成
	HRESULT MakeVerTex(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom);
	HRESULT	MakeVerTex(float fPosX, float fPosY, float fWidth, float fHeight);

	// 2D構造体宣言
	typedef struct
	{
		D3DVECTOR	vtx;						// 頂点座標
		float		rhw;						// 同次座標の逆数
		D3DCOLOR	diffuse;					// 色情報
		D3DXVECTOR2	tex;						// テクスチャー座標
	}VERTEX_2D;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	// 頂点バッファー
	LPDIRECT3DTEXTURE9		m_pTexture;			// タイトル画像
	unsigned int			m_nNumber;
};

#endif // _NUMBER_H_