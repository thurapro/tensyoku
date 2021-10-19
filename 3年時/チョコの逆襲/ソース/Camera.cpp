//=============================================================================
//
// �J�������� [Camera.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Camera.h"
#include <math.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static D3DXVECTOR3 g_posCameraP;			// �J�������_
static D3DXVECTOR3 g_posCameraR;			// �J���������_
static D3DXVECTOR3 g_vecCameraV;			// ������x�N�g��
static D3DXVECTOR3 g_rotCamera;				// �J�����̉�]
static D3DXMATRIX g_mtxView;				// �r���[	
static D3DXMATRIX g_mtxProjection;			// �v���W�F�N�V����
static float g_Anglemove  = 0.0f;			// �p�x�ϊ��l
static float g_Raidus;						// ���W�A���p�x
static float g_moveX = 0.0f;				// X���ɓ����l

//=============================================================================
//
//	�֐���	: �J����������
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �J����������
//
//=============================================================================
void CameraInit( void )
{
	//-------------------------------------------------------------------------
	// �J�������_ , �����_ , �x�N�g�����ׂď�����
	g_posCameraP = D3DXVECTOR3( 0.0f , 50.0f , -200.0f );	// ���_
	g_posCameraR = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// �����_
	g_vecCameraV = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// �x�N�g��

	//--------------------------------------------------------------------------
	// �p�x�����߂�@��( X * X ) + ( Y * Y )
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
		// ���_�ύX
		if( KeyState(DIK_Q) )	// ������
		{
			g_rotCamera.y -= 0.05f;
			g_posCameraP.x = g_posCameraR.x - sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraP.z = g_posCameraR.z - cosf( g_rotCamera.y )* g_Raidus ;
		}
		if( KeyState(DIK_E) )	// �E����
		{
			g_rotCamera.y += 0.05f;
			g_posCameraP.x = g_posCameraR.x - sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraP.z = g_posCameraR.z - cosf( g_rotCamera.y )* g_Raidus ;
		}

		if( KeyState(DIK_W) )	// ��ړ�
		{
			g_moveX = 1.0f; 
			g_posCameraR.x += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z += cosf(g_rotCamera.y) * g_moveX;
		}
		
		if( KeyState(DIK_S) )	// ���ړ�
		{
			g_moveX = 1.0f; 
			g_posCameraR.x -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z -= cosf(g_rotCamera.y) * g_moveX;
		}

		if( KeyState(DIK_A) )	// ���ړ�
		{
			g_moveX = 1.0f; 
			g_posCameraR.x -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x -= cosf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z += sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z += sinf(g_rotCamera.y) * g_moveX;
		}

		if( KeyState(DIK_D) )	// �E�ړ�
		{
			g_moveX = 1.0f; 
			g_posCameraR.x += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraP.x += cosf(g_rotCamera.y) * g_moveX;
			g_posCameraR.z -= sinf(g_rotCamera.y) * g_moveX;
			g_posCameraP.z -= sinf(g_rotCamera.y) * g_moveX;
		}

		//-------------------------------------------------------------------------
		// �����_
		if( KeyState(DIK_Z) )	// ������
		{
			g_rotCamera.y += 0.05f;
			g_posCameraR.x = g_posCameraP.x + sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraR.z = g_posCameraP.z + cosf( g_rotCamera.y )* g_Raidus ;
		}
		
		if( KeyState(DIK_C) )	// �E����
		{
			g_rotCamera.y -= 0.05f;
			g_posCameraR.x = g_posCameraP.x + sinf( g_rotCamera.y )* g_Raidus ;
			g_posCameraR.z = g_posCameraP.z + cosf( g_rotCamera.y )* g_Raidus ;
		}
	}
}


//=============================================================================
//
//	�֐���	: �J�����`��
//	
//	�߂�l	: �J�������_ ,�@�����_ ,�@����
//
//	����	: �Ȃ�
//
//	�@�\	: �J����������
//
//=============================================================================
void CameraDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// �r���[�}�g���b�N�X
	D3DXMatrixIdentity( &g_mtxView );								// �r���[�}�g���b�N�X������
	D3DXMatrixLookAtLH( &g_mtxView , &g_posCameraP ,
						&g_posCameraR , &g_vecCameraV );			// �}�g���b�N�X�쐬
	pD3DDevice->SetTransform( D3DTS_VIEW , &g_mtxView );			// �}�g���b�N�X�ݒ�

	//-------------------------------------------------------------------------
	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMatrixIdentity( &g_mtxProjection );							// �v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixPerspectiveFovLH( &g_mtxProjection ,
								D3DX_PI / 4 , 
								(float)SCREEN_WIDTH / SCREEN_HEIGHT ,
								1.0f ,
								2000.0f );		// �v���W�F�N�V�����}�g���b�N�X�쐬
	pD3DDevice->SetTransform(D3DTS_PROJECTION , &g_mtxProjection);	// �}�g���b�N�X�ݒ�
}

//=============================================================================
// �J�����̃r���[�擾
//=============================================================================
D3DXMATRIX CameraView(void)
{
	return g_mtxView;
}

//=============================================================================
// �J�����̉�]�擾
//=============================================================================
D3DXVECTOR3 CameraRotGet(void)
{
	return g_rotCamera;
}