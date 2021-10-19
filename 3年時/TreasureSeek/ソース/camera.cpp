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
#include "common.h"
#include "main.h"
#include "manager.h"
#include "game.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "player.h"
#include "renderer.h"
#include "camera.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE (15.0f)
#define PLAYER_SCORPE (10) 

//=============================================================================
// 静的メンバ変数定義
//=============================================================================

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
	m_posCameraP = D3DXVECTOR3(0.0f, 100.0f, -300.0f);	// カメラの位置初期化
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// カメラの注視点初期化
	m_vecCameraV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// カメラのベクトル初期化

	m_Length = 	m_posCameraP - m_posCameraR;			// カメラの位置と注視点までの距離を計算
	m_rotCamera = m_posCameraR - m_posCameraP;
	
	// カメラの間隔
	m_fLengthInterval = sqrtf( (m_Length.x * m_Length.x) + (m_Length.y * m_Length.y) + (m_Length.z * m_Length.z) );

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
	CDebug *pDebug = CManager::GetDebug();
	CInputKeyboard *pInputKeyboard = CManager::GetInput();	// 入力ポインタ
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPosition;
	D3DXVECTOR3 PlayerRotition;
	int nStopCnt = 0;

	// カメラ位置から注視点に向かうベクトルを再設定
	if( pPlayer )
	{
		PlayerPosition	= pPlayer->GetPosition();			// プレイヤーの位置を取得
		PlayerRotition	= pPlayer->GetRotition();			// プレイヤーの方向ベクトルを取得
		nStopCnt		= pPlayer->GetStopCnt();			// プレイヤーカウント
	}

	m_posCameraR		= PlayerPosition;
	m_posCameraR.y		+= 100.0f;

	if( m_posCameraR.y	< 100.0f || m_posCameraR.y > 40.0f )
	{
		m_posCameraR.y = 50.0f;
	}


	if( CManager::GetInput()->KeyState(DIK_L) )
	{
		m_fRadian += D3DX_PI * 0.01f;
		if( m_fRadian > 6.28f )
		{
			m_fRadian = 0.0f;
		}
	}
	else if( CManager::GetInput()->KeyState(DIK_J) )
	{
		m_fRadian -= D3DX_PI * 0.01f;
		if( m_fRadian < -6.28f )
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
	m_posCameraP.x		= m_posCameraR.x + sinf(m_fRadian) * -m_fLengthInterval;
	m_posCameraP.z		= m_posCameraR.z + cosf(m_fRadian) * -m_fLengthInterval;


	pDebug->Print("ストップカウント %d\n", nStopCnt);
	pDebug->Print("ｶﾒﾗP: x = %.3f y = %.3f z = %.3f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	pDebug->Print("ｶﾒﾗR: x = %.3f y = %.3f z = %.3f\n", m_posCameraR.x, m_posCameraR.y, m_posCameraR.z);
	pDebug->Print("ｶﾒﾗ向: %.3f \n", m_fRadian);
	
	///// カメラの注視点 /////
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
								40000000.0f);								// 後方投影面までの距離
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);			// プロジェクションマトリックス設定
}


float CCamera::CameraRotition(D3DXVECTOR3 Vector0, D3DXVECTOR3 Vector1)
{
	// 単位ベクトル保存用
	D3DXVECTOR3 shortVec0, shortVec1;
	float		fLength0, fLength1;
	float		fDotProduct = 0;
	float		fRadian = 0;
	float		fCrossProduct = 0;

	// Vector0を単位ベクトル化
	fLength0 = sqrtf( (Vector0.x * Vector0.x) + (Vector0.y * Vector0.y) + (Vector0.z *Vector0.z) );
	shortVec0.x = Vector0.x / fLength0;
	shortVec0.y = Vector0.y / fLength0;
	shortVec0.z = Vector0.z / fLength0;

	// Vector1を単位ベクトル化
	fLength1 = sqrtf( (Vector1.x * Vector1.x) + (Vector1.y * Vector1.y) + (Vector1.z *Vector1.z) );
	shortVec1.x = Vector1.x / fLength1;
	shortVec1.y = Vector1.y / fLength1;
	shortVec1.z = Vector1.z / fLength1;
	
	// 内積計算で角度を計算
	fDotProduct = (shortVec0.x * shortVec1.x) + (shortVec0.y * shortVec1.y) + (shortVec0.z * shortVec1.z);

	// 内積計算誤差修正
	if( fDotProduct < -1.0f )
	{
		fDotProduct = -1.0f;
	}
	if( fDotProduct > 1.0f )
	{
		fDotProduct = 1.0f;
	}

	fRadian = cosf(fDotProduct);
	fRadian *= 0.01f;
	fCrossProduct = shortVec0.z * shortVec1.x - shortVec0.x * shortVec1.z;
	if( fCrossProduct < 0 )
	{
		fRadian *= -1; 
	}
	return fRadian;
}


///// end of file /////

