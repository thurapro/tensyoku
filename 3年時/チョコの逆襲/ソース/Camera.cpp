//=============================================================================
//
// カメラ処理 [Camera.cpp]
//
// 名前	: 松尾 雄太
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Camera.h"
#include <math.h>

//=============================================================================
// グローバル変数
//=============================================================================
static D3DXVECTOR3 g_posCameraP;			// カメラ視点
static D3DXVECTOR3 g_posCameraR;			// カメラ注視点
static D3DXVECTOR3 g_vecCameraV;			// 上方向ベクトル
static D3DXVECTOR3 g_rotCamera;				// カメラの回転
static D3DXMATRIX g_mtxView;				// ビュー	
static D3DXMATRIX g_mtxProjection;			// プロジェクション
static float g_Anglemove  = 0.0f;			// 角度変換値
static float g_Raidus;						// ラジアン角度
static float g_moveX = 0.0f;				// X軸に動く値

//=============================================================================
//
//	関数名	: カメラ初期化
//	
//	戻り値	: なし
//
//	引数	: なし
//
//	機能	: カメラ初期化
//
//=============================================================================
void CameraInit( void )
{
	//-------------------------------------------------------------------------
	// カメラ視点 , 注視点 , ベクトルすべて初期化
	g_posCameraP = D3DXVECTOR3( 0.0f , 50.0f , -200.0f );	// 視点
	g_posCameraR = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// 注視点
	g_vecCameraV = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// ベクトル

	//--------------------------------------------------------------------------
	// 角度を求める　√( X * X ) + ( Y * Y )
	g_Raidus = sqrt( (g_posCameraP.z * g_posCameraP.z) + (g_posCameraP.x * g_posCameraP.x) );
}

void CameraUpdate( void )
{
	bool bStop = GameStop();

	if( bStop == false )
	{
		g_posCameraR = PlayerPosGet();
		g_posCameraP = D3DXVECTOR3( PlayerPosGet().x + 0 , PlayerPosGet().y + 50.0f , PlayerPosGet().z - 200.0f );
	}

	
	else
	{
		//-------------------------------------------------------------------------
		// 視点変更
		if( KeyState(DIK_Q) )	// 左旋回
		{
			g_rotCamera.y -= 0.05f;
			g_posCameraP.x = g_posCameraR.x - sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraP.z = g_posCameraR.z - cosf( g_rotCamera.y )* g_Raidus ;
		}
		if( KeyState(DIK_E) )	// 右旋回
		{
			g_rotCamera.y += 0.05f;
			g_posCameraP.x = g_posCameraR.x - sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraP.z = g_posCameraR.z - cosf( g_rotCamera.y )* g_Raidus ;
		}

		if( KeyState(DIK_W) )	// 上移動
		{
			g_moveX = 1.0f; 
			g_posCameraR.x += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z += cosf(g_rotCamera.y) * g_moveX;
		}
		
		if( KeyState(DIK_S) )	// 後ろ移動
		{
			g_moveX = 1.0f; 
			g_posCameraR.x -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z -= cosf(g_rotCamera.y) * g_moveX;
		}

		if( KeyState(DIK_A) )	// 左移動
		{
			g_moveX = 1.0f; 
			g_posCameraR.x -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z += sinf(g_rotCamera.y) * g_moveX;
		}

		if( KeyState(DIK_D) )	// 右移動
		{
			g_moveX = 1.0f; 
			g_posCameraR.x += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z -= sinf(g_rotCamera.y) * g_moveX;
		}

		//-------------------------------------------------------------------------
		// 注視点
		if( KeyState(DIK_Z) )	// 左旋回
		{
			g_rotCamera.y += 0.05f;
			g_posCameraR.x = g_posCameraP.x + sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraR.z = g_posCameraP.z + cosf( g_rotCamera.y )* g_Raidus ;
		}
		
		if( KeyState(DIK_C) )	// 右旋回
		{
			g_rotCamera.y -= 0.05f;
			g_posCameraR.x = g_posCameraP.x + sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraR.z = g_posCameraP.z + cosf( g_rotCamera.y )* g_Raidus ;
		}
	}
}


//=============================================================================
//
//	関数名	: カメラ描画
//	
//	戻り値	: カメラ視点 ,　注視点 ,　方向
//
//	引数	: なし
//
//	機能	: カメラ初期化
//
//=============================================================================
void CameraDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// ビューマトリックス
	D3DXMatrixIdentity( &g_mtxView );								// ビューマトリックス初期化
	D3DXMatrixLookAtLH( &g_mtxView , &g_posCameraP ,
						&g_posCameraR , &g_vecCameraV );			// マトリックス作成
	pD3DDevice->SetTransform( D3DTS_VIEW , &g_mtxView );			// マトリックス設定

	//-------------------------------------------------------------------------
	// プロジェクションマトリックス
	D3DXMatrixIdentity( &g_mtxProjection );							// プロジェクションマトリックス初期化
	D3DXMatrixPerspectiveFovLH( &g_mtxProjection ,
								D3DX_PI / 4 , 
								(float)SCREEN_WIDTH / SCREEN_HEIGHT ,
								1.0f ,
								2000.0f );		// プロジェクションマトリックス作成
	pD3DDevice->SetTransform(D3DTS_PROJECTION , &g_mtxProjection);	// マトリックス設定
}

//=============================================================================
// カメラのビュー取得
//=============================================================================
D3DXMATRIX CameraView(void)
{
	return g_mtxView;
}

//=============================================================================
// カメラの回転取得
//=============================================================================
D3DXVECTOR3 CameraRotGet(void)
{
	return g_rotCamera;
}