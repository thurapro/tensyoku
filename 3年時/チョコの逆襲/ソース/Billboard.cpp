//=============================================================================
//
// �t�B�[���h���� [Billboard.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Billboard.h"
	
//==============================================================================
// �}�N����`
//==============================================================================
#define MOVE_Z			( 1.0f )

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static D3DXMATRIX g_mtxWorld;						// ���[���h
static D3DXVECTOR3 g_posBillboard;					// �e�̈ʒu
static D3DXVECTOR3 g_rotBillboard;					// �e�̌���
static D3DXVECTOR3 g_sclBillboard;					// �e�̑傫��
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZ�̒��_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
static LPDIRECT3DTEXTURE9 g_pD3DTex = NULL;			// �e�N�X�`��
static int g_nVertexMax;							// ���_�o�b�t�@��
static int g_nIndexMax;
static D3DXVECTOR3 CameraRotSet;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexBillboard( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y);

//=============================================================================
//
//	�֐���	: BillboardInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �t�B�[���h������
//
//=============================================================================
HRESULT BillboardInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nBillboardScl_X , int nBillboardScl_Y)
{
	//-------------------------------------------------------------------------
	// �t�B�[���h������
	g_posBillboard = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );	// �e�̈ʒu
	g_rotBillboard = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// �e�̌���
	g_sclBillboard = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �e�̑傫��

	//-------------------------------------------------------------------------
	// �e�N�X�`���̃��[�h
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/tako.png" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexBillboard(pD3DDevice , fPolygonWidth , fPolygonHeight , nBillboardScl_X , nBillboardScl_Y) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: BillboardUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�j��
//
//=============================================================================
void BillboardUninit( void )
{
	// �����e�N�X�`�����������Ă��Ȃ����
	if(g_pD3DTex != NULL)
	{
		// �e�N�X�`���̉��
		g_pD3DTex->Release();

		// �e�N�X�`���̕�����NULL��
		g_pD3DTex = NULL;
	}

	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̉��
	if( g_pD3DVBXYZBuffer != NULL )
	{
		g_pD3DVBXYZBuffer->Release();
		g_pD3DVBXYZBuffer = NULL; 
	}
	
}

//=============================================================================
//
//	�֐���	: BillboardUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�X�V
//
//=============================================================================
void BillboardUpdate( void )
{
	CameraRotSet = CameraRotGet();

	if( KeyState(DIK_UP))
	{
		g_posBillboard.x += sinf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z += cosf( CameraRotSet.y ) * MOVE_Z;
	}
	
	if( KeyState(DIK_DOWN))
	{
		g_posBillboard.x -= sinf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z -= cosf( CameraRotSet.y ) * MOVE_Z;
	}

	if( KeyState(DIK_LEFT) )
	{
		g_posBillboard.x -= cosf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z += sinf( CameraRotSet.y ) * MOVE_Z;
	}

	if( KeyState(DIK_RIGHT) )
	{
		g_posBillboard.x += cosf( CameraRotSet.y ) * MOVE_Z;
		g_posBillboard.z -= sinf( CameraRotSet.y ) * MOVE_Z;
	}

}

//=============================================================================
//
//	�֐���	: BillboardDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�`��
//
//=============================================================================
void BillboardDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	HRESULT hr;
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &g_mtxWorld );		// ���[���h�}�g���b�N�X������

	D3DXMatrixInverse( &g_mtxWorld , NULL , &mtxView );
	g_mtxWorld._41 = 0.0f;
	g_mtxWorld._42 = 0.0f;
	g_mtxWorld._43 = 0.0f;

	//*********************************
	// �X�P�[�����f
	D3DXMatrixScaling( &mtxScl , g_sclBillboard.x , g_sclBillboard.y , g_sclBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// ��]���f
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotBillboard.y , g_rotBillboard.x , g_rotBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// �ړ����f
	D3DXMatrixTranslation( &mtxTrans , g_posBillboard.x , g_posBillboard.y , g_posBillboard.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X�ݒ�
	pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );

	//-------------------------------------------------------------------------
	// ���_���ݒ�
	pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//-------------------------------------------------------------------------
	//  ���_�o�b�t�@�̃Z�b�g
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );
	hr = pD3DDevice->SetIndices( g_pIndexBuffer );

	//-------------------------------------------------------------------------
	// �e�N�X�`���̃Z�b�g
	pD3DDevice->SetTexture( 0 , g_pD3DTex );

	pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
	
	//-------------------------------------------------------------------------
	// �v���~�e�B�u�\��
	pD3DDevice->DrawPrimitive
				( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
				0 ,								// �O�p�`�̐�
				2 );							// �v���~�e�B�u�̐�

	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
}

//=============================================================================
//
// �֐��� : MakeVertexBillboard
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexBillboard( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y)
{
	//---------------------
	// �ϐ��錾
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	float fX = 0;
	float fY = 0;
	g_nVertexMax = ( (nScl_X + 1) * (nScl_Y + 1) );
	int nVertexHalf = (nScl_X + 1);
	float fTexX = 0.f;
	float fTexY = 0.f;
	float fTexWidth = 0.f;
	float fTexHeight = 0.f;
	int nScl_YMax = 1;
	int nNum_Kisu = 0;
	int nNum_Gusu = 0;

	for( int nCnt = 0; nCnt < nScl_Y; nCnt++ )
	{
		nScl_YMax *= 2;
	}

	//---------------------------------------------------------------------
	// ���_�o�b�t�@�쐬����
	hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * g_nVertexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&g_pD3DVBXYZBuffer,
										NULL );
	if( FAILED(hr) )
	{
		return (E_FAIL);
	}

	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̃��b�N
	hr = g_pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̍��W��
	
	float A = (float)nScl_X/2;
	float B = -A * fWidth;

	int i = 0;
	while( i < g_nVertexMax )
	{
		for( int j = 0; j < nVertexHalf; j++ )
		{
			pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , (-B - fY ) , 0.f );

			//-------------------------------------------------------------------------
			// �����̐ݒ�
			pVtx[i].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

			//---------------------------------------------------------------------
			// �F���̐ݒ�	( �� , �� , �� , �����x)
			pVtx[i].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
														BLUE_MAX , ALPHA_MAX );
			
			pVtx[i].tex = D3DXVECTOR2( fTexX + fTexWidth , fTexY + fTexHeight );

			//-------------------------------------------------------------------------
			// �����L����
			fX += fWidth;
			fTexWidth += 1.f;

			i++;
		}
			
		//-------------------------------------------------------------------------
		// ���������l��
		fX = 0;
		fTexWidth = 0.f;
	
		//--------------------------------------------------------------------------
		// �������L����
		fY += fHeight;
		fTexHeight += 1.f;
	}

	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̃��b�N��
	g_pD3DVBXYZBuffer->Unlock();
	
	
	// �쐬����
	return (S_OK);
}

//=============================================================================
// �r���{�[�h�ʒu�擾
//=============================================================================
D3DXVECTOR3 BillboardPosGet(void)
{
	return g_posBillboard;
}