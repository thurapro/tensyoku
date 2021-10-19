//=============================================================================
// テクスチャ保存処理	[ texture.h ]
//
// 作成者 : 松尾 雄太
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// クラス定義
//=============================================================================
class CTexture
{
public:
	CTexture();						// インスタンス生成
	~CTexture();					// インスタンス破棄
	HRESULT Init(char *FileName);	// テクスチャ初期化
	void Uninit(void);				// テクスチャ終了
	HRESULT LoardTexture(char *FileName); // テクスチャ読み込み

	unsigned int GetTextureNum(void){return m_nTextureNum - 1;}					// テクスチャ数
	LPDIRECT3DTEXTURE9 GetTexture(int nNumber){return m_ppTexture[nNumber];}	// テクスチャ取得
private:
	int	m_nTextureNum;					// テクスチャ数
	LPDIRECT3DTEXTURE9 *m_ppTexture;	// テクスチャ保存
};

#endif  // _TEXTURE_H_