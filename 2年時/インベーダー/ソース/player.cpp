//-----------------------------------------------------------------------------
//
// player処理 クラス		[player.cpp]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "player.h"
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "enemy.h"
#include "input.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_SPEEDX	(0.3f)			// プレイヤーのX座標移動量
#define PLAYER_SPEEDY	(0.0f)			// プレイヤーのY座標移動量
#define BULLET_SPEEDX	(0)				// 弾の速度X
#define BULLET_SPEEDY	(-0.5f)			// 弾の速度Y
#define BULLET_TIME		(20)			// 弾の間隔

//-----------------------------------------------------------------------------
// 静的メンバー変数定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プレイヤーコンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer(void)
{
	m_fPosX = 0.0f;			// プレイヤーの現在X座標
	m_fPosY = 0.0f;			// プレイヤーの現在Y座標
	m_fPosXOld = 0.0f;		// プレイヤーの元いたX座標
	m_fPosYOld = 0.0f;		// プレイヤーの元いたY座標
	m_fMoveX = 0.0f;		// プレイヤーの移動量X
	m_fMoveY = 0.0f;		// プレイヤーの移動量Y
	m_bMove = false;		// プレイヤーが移動したか
	CObject::SetObjType(OBJTYPE_PLAYER);
}

//-----------------------------------------------------------------------------
// プレイヤーデストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer(void)
{
	// プレイヤークラス破棄
}

//-----------------------------------------------------------------------------
// プレイヤー初期化
//-----------------------------------------------------------------------------
void CPlayer::Init(float fPosX , float fPosY)
{
	m_fPosX = fPosX;		// プレイヤーの現在X座標
	m_fPosY = fPosY;		// プレイヤーの現在Y座標
	m_fPosXOld = 0.0f;		// プレイヤーの元いたX座標
	m_fPosYOld = 0.0f;		// プレイヤーの元いたY座標
	m_fMoveX = 0.5f;		// プレイヤーの移動量X
	m_fMoveY = 0.0f;		// プレイヤーの移動量Y
	m_bMove = false;		// プレイヤーが動いたか
}

//-----------------------------------------------------------------------------
// プレイヤー終了
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// 終了処理
}

//-----------------------------------------------------------------------------
// プレイヤー更新
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{
	m_fPosXOld = m_fPosX;				// 元の座標X
	m_fPosYOld = m_fPosY;				// 元の座標Y
	CInput *pInput = CManager::GetInput();	// キー取得
	int nNum;							// 敵の数取得
	CEnemy::GetNum(&nNum);
	if(nNum <= 0)
	{
		// 敵が全滅していれば
		CManager::SetMode(CManager::MODE_RESULT);
	}
	else
	{
		if(pInput->GetKeyboardPress(PK_A))
		{
			// Aボタンが押されたら
			if( m_fPosX > SCREEN_WIDTH_MIN )
			{
				// 左画面外を超えていたら
				m_fPosX -= m_fMoveX;		// プレイヤーを左に移動
			}
		}
		else if(pInput->GetKeyboardPress(PK_D))
		{
			// Dボタンが押されたら
			if( m_fPosX < SCREEN_WIDTH_MAX )
			{
				// 右画面外を超えてなければ
				m_fPosX += m_fMoveX;		// プレイヤーを右に移動
			}
		}
		if(pInput->GetKeyboardTrigger(PK_SP))
		{
			// スペースが押されたら
			// 弾の生成
			if( CBullet::Create(m_fPosX, m_fPosY, BULLET_SPEEDX, BULLET_SPEEDY) == NULL )
			{
				return;
			}
		}
		if( m_fPosX != m_fPosXOld || m_fPosY != m_fPosYOld )
		{
			
			// 前の座標と現在の座標が変わっていたら
			m_bMove = true;					// プレイヤーは動いた
		}
	}
}
//-----------------------------------------------------------------------------
// プレイヤー描画
//-----------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	if( m_bMove == true )
	{
		LOCATE((int)m_fPosXOld , (int)m_fPosYOld);	// プレイヤーの座標セット
		printf(" ");								// プレイヤーの元いた場所を消す
	}
	LOCATE((int)m_fPosX , (int)m_fPosY);			// プレイヤーの座標セット
	printf("A");									// プレイヤー描画
}

//-----------------------------------------------------------------------------
// プレイヤー作成
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(float fPosX, float fPosY)
{
	// プレイヤーポインター
	CPlayer *pPlayer;

	// プレイヤー生成
	pPlayer = new CPlayer;

	// プレイヤーの初期化
	pPlayer->Init(fPosX , fPosY);

	return pPlayer;
}
