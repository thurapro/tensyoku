//=============================================================================
// カメラ処理 [camera.h]
//
// 製作者	: 松尾 雄太
//
// 機能		: カメラの初期化
//			: 更新
//			: 描画
//			: ビュー取得
//			: 角度取得
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "camera.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE (20.0f)			// カメラの位置移動速度
#define MOVE_R (20.0f)
#define PLAYER_SCORPE (10)		// プレイヤーの向いている位置から10先をみる

//=============================================================================
// 関数名	: CCamera
// 戻り値	: なし
// 引数		: なし
// 機能		: カメラインスタンス生成
//=============================================================================
CCamera::CCamera(void)
{
	// インスタンス生成
}

//=============================================================================
// 関数名	: ~CCamera
// 戻り値	: なし
// 引数		: なし
// 機能		: カメラインスタンス破棄
//=============================================================================
CCamera::~CCamera(void)
{
	// インスタンス破棄
}

//=============================================================================
// 関数名	: Init
// 戻り値	: HRESULT
// 引数		: なし
// 機能		: カメラの初期化
//			: カメラの位置初期化
//			: カメラの注視点初期化
//			: カメラのベクトル初期化
//			: カメラの角度初期化
//=============================================================================
void CCamera::Init(void)
{
	///// カメラ位置初期化開始 /////
	m_posCameraP = D3DXVECTOR3(0.0f, 200.0f, -100.0f);	// カメラの位置初期化
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの注視点初期化
	m_vecCameraV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// カメラのベクトル初期化

	m_Length	= m_posCameraP - m_posCameraR;			// カメラの位置と注視点までの距離を計算
	m_rotCamera = m_posCameraR - m_posCameraP;			// カメラの向き
	
	// カメラの間隔
	m_fLengthInterval = sqrtf( (m_Length.x * m_Length.x) + (m_Length.y * m_Length.y) + (m_Length.z * m_Length.z) );

	// カメラの角度
	m_fRadian = 0;
}

//=============================================================================
// 関数名	: Uninit
// 戻り値	: なし
// 引数		: なし
// 機能		: カメラの終了処理	( 現在なし )
//=============================================================================
void CCamera::Uninit(void)
{
	// 終了処理
}

//=============================================================================
// 関数名	: Update
// 戻り値	: なし
// 引数		: なし
// 機能		: カメラの更新
//			: カメラの位置(視点変更)
//			: カメラの注視点
//			: カメラのベクトル
//			: カメラの角度
//=============================================================================
void CCamera::Update(void)
{
	///// カメラの更新開始 /////

	//変数宣言 
	CDebug *pDebug = CManager::GetDebug();						// デバッグポインタ取得
	CInputKeyboard *pInputKeyboard = CManager::GetKeyboard();	// 入力ポインタ取得
	D3DXVECTOR3 PlayerPosition;									// プレイヤー位置取得
	D3DXVECTOR3 PlayerRotition;									// プレイヤー向き取得
	int nStopCnt = 0;											// プレイヤーストップカウント取得

	// キーボード操作
	if( pInputKeyboard->KeyState(DIK_Q) )						// 左回転
	{
		m_fRadian -= D3DX_PI * 0.01f;
		if( m_fRadian < -6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else if( pInputKeyboard->KeyState(DIK_E) )					// 右回転
	{
		m_fRadian += D3DX_PI * 0.01f;
		if( m_fRadian > 6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else
	{
		if( nStopCnt > 200 )
		{
			if( m_fRadian < PlayerRotition.y )
			{		
				m_fRadian += PlayerRotition.y * 0.007f;
			}
		}
	}

	// 視点移動
	if( pInputKeyboard->KeyState(DIK_Z) )					// 視点を上に移動
	{
		if( !CManager::GetDebug()->GetDebugMode() )
		{
			if( m_posCameraR.y < 640.0f )
			{
				// 上に向ける上限
				m_posCameraR.y += 5.0f;
			}
		}
		m_posCameraR.y += MOVE_R;
	}
	else if( pInputKeyboard->KeyState(DIK_X) )				// 視点を下に移動
	{
		if( !CManager::GetDebug()->GetDebugMode() )
		{
			if( m_posCameraR.y > -180.0f )
			{
				m_posCameraR.y -= 5.0f;
			}
		}
		m_posCameraR.y -= MOVE_R;
	}

	if(pInputKeyboard->KeyState(DIK_W) )
	{
		m_move = MOVE;
		m_posCameraR.x += sinf(m_fRadian) * m_move;
		m_posCameraP.x += sinf(m_fRadian) * m_move;
		m_posCameraR.z += cosf(m_fRadian) * m_move;
		m_posCameraP.z += cosf(m_fRadian) * m_move;
	}
	else if(pInputKeyboard->KeyState(DIK_S) )
	{
		m_move = MOVE; 
		m_posCameraR.x -= sinf(m_fRadian) * m_move;
		m_posCameraP.x -= sinf(m_fRadian) * m_move;
		m_posCameraR.z -= cosf(m_fRadian) * m_move;
		m_posCameraP.z -= cosf(m_fRadian) * m_move;
	}

	if(pInputKeyboard->KeyState(DIK_A) )
	{
		m_move = MOVE; 
		m_posCameraR.x -= cosf(m_fRadian) * m_move;
		m_posCameraP.x -= cosf(m_fRadian) * m_move;
		m_posCameraR.z += sinf(m_fRadian) * m_move;
		m_posCameraP.z += sinf(m_fRadian) * m_move;
	}

	else if(pInputKeyboard->KeyState(DIK_D) )
	{
		m_move = MOVE; 
		m_posCameraR.x += cosf(m_fRadian) * m_move;
		m_posCameraP.x += cosf(m_fRadian) * m_move;
		m_posCameraR.z -= sinf(m_fRadian) * m_move;
		m_posCameraP.z -= sinf(m_fRadian) * m_move;
	}

	if( pInputKeyboard->KeyState(DIK_R) )
	{
		m_move = MOVE;
		m_posCameraP.y += m_move;
		m_posCameraR.y += m_move;
	}
	else if( pInputKeyboard->KeyState(DIK_C) )
	{
		m_posCameraP.y -= m_move;
		m_posCameraR.y -= m_move;
	}



	// デバッグコード
	if( pInputKeyboard->KeyPush(DIK_F7) )
	{
		Init();		// カメラ初期化
	}
	
	m_posCameraP.x		= m_posCameraR.x + sinf(m_fRadian) * -m_fLengthInterval;
	m_posCameraP.z		= m_posCameraR.z + cosf(m_fRadian) * -m_fLengthInterval;


	pDebug->Print("ストップカウント %d\n", nStopCnt);
	pDebug->Print("ｶﾒﾗP: x = %.3f y = %.3f z = %.3f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	pDebug->Print("ｶﾒﾗR: x = %.3f y = %.3f z = %.3f\n", m_posCameraR.x, m_posCameraR.y, m_posCameraR.z);
	pDebug->Print("ｶﾒﾗ向: %.3f \n", m_fRadian);
}

//=============================================================================
// 関数名	: Draw
// 戻り値	: なし
// 引数		: なし
// 機能		: カメラ描画
//			: ビューマトリックス作成
//			: プロジェクションマトリックス作成
//=============================================================================
void CCamera::Draw(void)
{
	///// カメラの描画処理開始 /////

	//--- 変数宣言 ---//
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxProjection;											// プロジェクション

	///// ビューマトリックス作成 /////
	D3DXMatrixIdentity(&m_mtxView);										// ビューマトリックス初期化
	D3DXMatrixLookAtLH(&m_mtxView,										// ビューマトリックス作成
					&m_posCameraP,										// カメラの位置(視点)
					&m_posCameraR,										// カメラの注視点
					&m_vecCameraV);										// カメラの上方ベクトル
 	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);						// ビューマトリックス設定

	///// プロジェクションマトリックス作成 /////
	D3DXMatrixIdentity(&mtxProjection);									// プロジェクションマトリックス初期化
	D3DXMatrixPerspectiveFovLH(&mtxProjection,							// プロジェクションマトリックス作成					
								D3DX_PI / 6.0f,							// 視野角設定
								(float)WINDOW_WIDTH / WINDOW_HEIGHT,	// 画面のアスペクト比
								1.0f,									// 前方投影面までの距離
								40000000.0f);							// 後方投影面までの距離
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);			// プロジェクションマトリックス設定

	CManager::GetDebug()->Print("カメラ移してるよ\n");	
}




///// end of file /////

