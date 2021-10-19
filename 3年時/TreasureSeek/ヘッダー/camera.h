//=============================================================================
// カメラ処理 [camera.cpp]
//
// 名前	: 松尾 雄太
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// クラス定義
//=============================================================================
class CCamera
{
public:
	CCamera(void);												// カメラインスタンス生成
	~CCamera(void);												// カメラインスタンス破棄
	void		Init(void);										// カメラ初期化
	void		Uninit(void);									// カメラの終了処理
	void		Update(void);									// カメラ更新
	void		Draw(void);										// カメラ描画
	D3DXMATRIX	GetView(void){return m_mtxView;}				// カメラビュー取得
	float		GetRot(void){return m_fRadian;}					// カメラの角度
	float		CameraRotition(D3DXVECTOR3 Vector0, D3DXVECTOR3 Vector1);

private:
	D3DXVECTOR3 m_posCameraP;								// カメラ視点
	D3DXVECTOR3 m_posCameraR;								// カメラ注視点
	D3DXVECTOR3 m_vecCameraV;								// 上方向ベクトル
	D3DXVECTOR3 m_rotCamera;								// カメラの向き
	D3DXVECTOR3	m_rotSave;									// カメラの向きの保存
	D3DXVECTOR3 m_Length;									// カメラの視点と注視点の距離
	D3DXMATRIX m_mtxView;									// ビューマトリックス
	float	m_fLengthInterval;								// カメラの間隔
	float	m_fRadian;										// ラジアン角度
	float	m_move;											// カメラの移動
};

#endif // _CAMERA_H_

///// end of file /////