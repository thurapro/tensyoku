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
#ifndef _SCENEX_H_
#define _SCENEX_H_

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "model.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 0, OBJTYPE objType = OBJTYPE_MODEL);		// インスタンス生成
	~CSceneX(void);														// インスタンス破棄
	static CSceneX *Create(float fPosX, float fPosY, float fPosZ, 
							USHORT m_nModelNum,
							USHORT m_nTextureNum);						// Xオブジェクト作成	
	HRESULT	Init(void);													// Xオブジェクト初期化
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				 USHORT m_nModelNum,
				 USHORT m_nTexturenNum);								// Xオブジェクト初期化
	void	Uninit(void);												// Xオブジェクト破棄
	void	Update(void);												// Xオブジェクト更新
	void	Draw(void);													// Xオブジェクト描画

	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// Xオブジェクトの位置設定
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// Xオブジェクトの向き設定
	void	SetScale(float fPosX, float fPosY, float fPosZ);			// Xオブジェクトの大きさ設定

	D3DXVECTOR3 GetPosition(void){return m_pos;}						// Xオブジェクトの位置取得
	D3DXVECTOR3	GetRotition(void){return m_rot;}						// Xオブジェクトの向き取得
	D3DXVECTOR3	GetScale(void){return m_scl;}							// Xオブジェクトの大きさ取得
	float		GetRadius(void){return m_fRadius;}						// Xオブジェクトの半径取得

protected:
	D3DXVECTOR3			m_pos;			// Xオブジェクトの現在位置
	D3DXVECTOR3			m_oldpos;		// Xオブジェクトの前回位置
	D3DXVECTOR3			m_rot;			// Xオブジェクトの現在向き
	D3DXVECTOR3			m_oldrot;		// Xオブジェクトの前回向き
	D3DXVECTOR3			m_scl;			// Xオブジェクトの現在の大きさ
	D3DXVECTOR3			m_oldscl;		// Xオブジェクトの前回の大きさ
	D3DXMATRIX			m_mtxWorld;		// ワールドマトリックス
	float				m_fRadius;		// Xオブジェクトの半径 
	USHORT				m_nModelNum;	// モデル番号
	USHORT				m_nTextureNum;	// テクスチャ番号
	LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャデータ

private:
	DWORD				m_nNumMat;		// 総マテリアル数
	LPD3DXMESH			m_pMesh;		// メッシュポインタ
	LPD3DXBUFFER		m_pMatBuff;		// マテリアルバッファ
	CModel::X_FILE		m_pXmodel;		// モデルデータ
};

#endif // _SCENEX_H_
