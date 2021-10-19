//=============================================================================
// 処理 [player.cpp]
//
// 製作者	: 松尾 雄太
//
// 機能		: プレイヤー処理
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "common.h"
#include "manager.h"
#include "camera.h"
#include "item.h"
#include "field.h"
#include "score.h"
#include "shadow.h"
#include "game.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "debugproc.h"
#include "stage.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define JUMP_SPEED	( 10 )						// ジャンプ速度
#define GRAVITY		( 0.6f )					// 重力
#define MOVE_X		( 5 )						// 速度

//=============================================================================
// 関数名	: CPlayer
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス生成
//=============================================================================
CPlayer::CPlayer(int nPriority = 3, OBJTYPE objType):CSceneX(nPriority, objType)
{
	// インスタン生成
	m_pShadow = NULL;
}

//=============================================================================
// 関数名	: ~CPlayer
// 戻り値	: なし
// 引数		: なし
// 機能		: インスタンス破棄
//=============================================================================
CPlayer::~CPlayer(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Create
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー生成
//=============================================================================
CPlayer *CPlayer::Create(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	CPlayer *pPlayer;		// プレイヤー宣言
	pPlayer = NEW CPlayer;	// プレイヤー生成
	hr = pPlayer->Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// プレイヤー初期化
	if( FAILED(hr) )
	{
		// プレイヤー生成失敗
		return NULL;		// エラーコード
	}
	return pPlayer;			// プレイヤーを戻す
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: プレイヤー初期化
//=============================================================================
HRESULT CPlayer::Init(void)
{
	return S_OK;
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: プレイヤー初期化
//=============================================================================
HRESULT CPlayer::Init(float fPosX, float fPosY, float fPosZ, unsigned int nModelNum, unsigned int nTexNum)
{
	HRESULT hr;
	hr = CSceneX::Init(fPosX, fPosY, fPosZ, nModelNum, nTexNum);	// プレイヤー初期化
	ERROR_CHACK(hr);												// エラーチェック
	m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI;							// プレイヤーの向きを設定	
	m_rotVector = m_pos - m_oldpos;									// プレイヤーの方向ベクトル計算
	D3DXVec3Normalize(&m_rotVector, &m_rotVector);					// 方向ベクトルを単位ベクトル化
	m_bJump		= false;											// ジャンプフラグ初期化				
	m_bMove		= false;											// 移動フラグ初期化
	m_nStopCnt	= 0;												// 静止カウント初期化
	m_fRadius	= 15.0f;											// プレイヤーの半径
	if( m_pShadow == NULL )
	{
		// 影を初期化
		m_pShadow =CShadow::Create(m_pos.x, m_pos.y, m_pos.z, 10, 0, 10, 5);
	}
	return S_OK;		// 正常終了
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー終了
//=============================================================================
void CPlayer::Uninit(void)
{
	CSceneX::Uninit();	// 終了処理
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー更新
//=============================================================================
void CPlayer::Update(void)
{
	CCamera *pCamera = NULL;
	CDebug *pDebug = CManager::GetDebug();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CField **pField = NULL;
	int		FieldMax = 0;
	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_GAME:
		pField = CGame::GetStage()->GetField();
		pCamera = CGame::GetCamera();
		break;
	case CManager::MODE_RESULT:
		break;
	}

	float fHeight = 0;
	float fRotition = 0;
	float fAngle = 0;

	m_fMoveY -= GRAVITY;

	// 今回の位置を保存
	m_oldpos = m_pos;

	D3DXVECTOR3 NextPos = m_pos;

	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE )
	{
		// プレイヤーの方向ベクトル
		if(pKeyboard->KeyState(DIK_W))
		{	
			m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI;
			m_pos.x += sinf(m_rot.y  - D3DX_PI) * MOVE_X;
			m_pos.z += cosf(m_rot.y  - D3DX_PI) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_S))
		{
			m_rot.y = CGame::GetCamera()->GetRot();
			m_pos.x -= sinf(m_rot.y) * MOVE_X;
			m_pos.z -= cosf(m_rot.y) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_A))
		{
			m_rot.y = CGame::GetCamera()->GetRot() + D3DX_PI / 2;
			m_pos.x -= cosf(m_rot.y - D3DX_PI / 2) * MOVE_X;
			m_pos.z += sinf(m_rot.y - D3DX_PI / 2) * MOVE_X;
			m_bMove = true;
		}
		else if(pKeyboard->KeyState(DIK_D))
		{
			m_rot.y = CGame::GetCamera()->GetRot() - D3DX_PI / 2;
			m_pos.x += cosf(m_rot.y + D3DX_PI / 2) * MOVE_X;
			m_pos.z -= sinf(m_rot.y + D3DX_PI / 2) * MOVE_X;
			m_bMove = true;
		}
		else
		{
			m_bMove = false;
		}
		
		CGame::GetStage()->GetFieldNum(FieldMax);

		
		for( int field = 0; field < FieldMax; field++ )
		{
			if(pField[field])
			{
				// 地面が取得できたのなら
				fHeight = pField[field]->GetHeight(m_pos);	// 地面の高さを取得
			}
		}
		if(pKeyboard->KeyPush(DIK_SPACE))
		{
			// ジャンプキーが押されたら
			if( m_bJump == false )
			{
				m_fMoveY = JUMP_SPEED;			// ジャンプを速度
				m_bJump = true;					// ジャンプしている
			}
			m_bMove = true;						// プレイヤーが動いた
		}
		if(m_bJump == true )
		{
			// もしジャンプしているのなら
			m_pos.y += m_fMoveY;				// ジャンプ分あげる
		}
		else
		{
			// ジャンプしていなければ
			m_pos.y = fHeight;					// 地面との当たり判定			
		}
		if( fHeight >= m_pos.y && m_bJump == true )
		{
			// 地面の高さよりも下で、ジャンプフラグが立っていたら
			m_bJump = false;					// ジャンプしていないとする
		}
		if( m_bMove == false )
		{
			// プレイヤーが動かなければ
			m_nStopCnt++;						// プレイヤーの静止カウントをあげる
		}
		else
		{
			// プレイヤーが動いたら
			m_nStopCnt = 0;						// プレイヤーの静止カウントを0に初期化
		}
	}

	m_rotVector = m_pos - m_oldpos;									// プレイヤーの方向ベクトル計算
	D3DXVec3Normalize(&m_rotVector, &m_rotVector);					// 方向ベクトルを単位ベクトル化

	m_pShadow->SetPosition( m_pos.x, fHeight + 1, m_pos.z);

	pDebug->Print("プ位置 x:%.2f y:%.2f z:%.2f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebug->Print("プ向き x:%.2f y:%.2f z:%.2f\n", m_rot.x, m_rot.y, m_rot.z);
	pDebug->Print("プ方向ベクトル x: %.2f y: %.2f z: %.2f\n", m_rotVector.x, m_rotVector.y, m_rotVector.z);
	pDebug->Print("プ前位 x:%.2f y:%.2f z:%.2f\n", m_oldpos.x, m_oldpos.y, m_oldpos.z);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: プレイヤー描画
//=============================================================================
void CPlayer::Draw(void)
{
	CSceneX::Draw();	// 描画処理
}


float CPlayer::PlayerRotition(D3DXVECTOR3 rot, D3DXVECTOR3 Next)
{
	float fDotProduct = 0;
	float fRadian = 0;
	float fCrossProduct = 0;

	fDotProduct = (rot.x * Next.x) + (rot.y * Next.y) + (rot.z * Next.z);

	if( fDotProduct < -1.0f )
	{
		fDotProduct = -1.0f;
	}
	if( fDotProduct > 1.0f )
	{
		fDotProduct = 1.0f;
	}

	fRadian = acos(fDotProduct);
	fRadian *= 0.1f;
	
	fCrossProduct = (rot.z * Next.x) - (rot.x * Next.z);

	if( fCrossProduct < 0 )
	{
		fRadian *= -1;
	}
	if( fCrossProduct > 1)
	{
		fRadian *= 1;
	}
	return fRadian;
}

///// end of file /////