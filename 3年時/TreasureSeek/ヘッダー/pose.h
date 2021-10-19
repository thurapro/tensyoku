//=============================================================================
// ポーズ処理 [pose.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: ポーズ機能
//=============================================================================

//=============================================================================
// 2重インクルードの防止
//=============================================================================
#ifndef _POSE_H_
#define _POSE_H_

//=============================================================================
// マクロ定義
//=============================================================================
class CScene2D;				// 2Dポリゴン
#define MAX_POSE	( 7 )		// 2D画像の数

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CPose
{
public:	
	CPose(void);												// ポーズインスタンス生成
	~CPose(void);												// ポーズインスタンス破棄
	HRESULT Init(void);											// ポーズ初期化処理
	void	Uninit(void);										// ポーズ終了処理
	void	Update(void);										// ポーズ更新処理
	void	Draw(void);											// ポーズ描画
	void	SetPoseNum(unsigned short nNum){m_nNumber = nNum;}
	bool	GetTutorialFlag(void){return m_bTutorial;}
	CScene2D **GetPose(void){return &m_apPose[0];}
	unsigned short GetPoseNum(void){return  m_nNumber;}
private:	
	CScene2D			*m_apPose[MAX_POSE];	// ポーズ画面
	CScene2D			*m_pTutorial[2];		// チュートリアル画面
	float				m_fPosY;				// 位置Y
	float				m_fHeight;				// 高さ
	float				m_fTexY;				// テクスチャ座標X
	float				m_fTexHeight;			// テクスチャの幅
	unsigned short		m_nNumber;				// どこを指しているか
	bool				m_bTutorial;			// チュートリアルフラグ
};

#endif	// _POSE_H_
