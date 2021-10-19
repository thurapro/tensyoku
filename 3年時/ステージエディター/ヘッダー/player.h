//=============================================================================
// プレイヤー処理 [player.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: プレイヤー処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "sceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================
class CShadow;				// マクロ定義

//=============================================================================
// クラス宣言
//=============================================================================
class CPlayer: public CSceneX
{
public:
	enum
	{
		LEFT = 0,
		RIGHT,
		TOP,
		BOTTOM,
		MAX_DIRECTION
	};
	CPlayer(int nPriority, OBJTYPE objType = OBJTYPE_PLAYER);					// プレイヤーインスタンス生成
	~CPlayer(void);																// プレイヤーインスタンス破棄
	static CPlayer *Create(float fPosX, float fPosY, float fPosZ, 
								unsigned int nModelNum, unsigned int nTexNum);	// プレイヤー生成
	HRESULT Init(void);															// プレイヤー初期化
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum);					// プレイヤー初期化
	void Uninit(void);															// プレイヤー終了
	void Update(void);															// プレイヤー更新
	void Draw(void);															// プレイヤー描画
	void SetPosition(D3DXVECTOR3 pos);											// プレイヤーの位置設定
	D3DXVECTOR3		GetRotVector(void){return m_rotVector;}						// プレイヤーの方向ベクトル
	unsigned int	GetStopCnt(void){return m_nStopCnt;}						// プレイヤーが動かなかった時間
	float PlayerRotition(D3DXVECTOR3 rot, D3DXVECTOR3 Next);					// プレイヤーの回る角度

private:
	D3DXVECTOR3		m_rotVector;				// プレイヤーの方向ベクトル
	float			m_fAngle;					// プレイヤーの角度
	float			m_fMoveX;					// 進む量　X座標
	float			m_fMoveY;					// 進む量　Y座標
	float			m_fMoveZ;					// 進む量　Z座標
	bool			m_bJump;					// ジャンプしているかのフラグ
	bool			m_bMove;					// プレイヤーが進んだか
	bool			m_bOutMove[4];					// 進めるかどうか
	unsigned int	m_nStopCnt;					// プレイヤーが動かなかった時間	
	CShadow			*m_pShadow;					// 影ポインタ
};

///// end of file /////