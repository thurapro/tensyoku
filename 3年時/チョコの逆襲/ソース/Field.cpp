//=============================================================================
//
// �t�B�[���h���� [Field.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Field.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static D3DXMATRIX g_mtxView;						// �r���[	
static D3DXMATRIX g_mtxProjection;					// �v���W�F�N�V����
static D3DXMATRIX g_mtxWorld;						// ���[���h
static D3DXVECTOR3 g_posField;						// �e�̈ʒu
static D3DXVECTOR3 g_rotField;						// �e�̌���
static D3DXVECTOR3 g_sclField;						// �e�̑傫��
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZ�̒��_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
static LPDIRECT3DTEXTURE9 g_pD3DTex = NULL;			// �e�N�X�`��
static int g_nVertexMax;							// ���_�o�b�t�@��
static int g_nIndexMax;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexField( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y);

//=============================================================================
//
//	�֐���	: FieldInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �t�B�[���h������
//
//=============================================================================
HRESULT FieldInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nFieldScl_X , int nFieldScl_Y)
{
	//-------------------------------------------------------------------------
	// �t�B�[���h������
	g_posField = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// �n�ʂ̈ʒu
	g_rotField = D3DXVECTOR3( 0.f , 0.f , 0.f );	// �n�ʂ̌���
	g_sclField = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �n�ʂ̑傫��

	//-------------------------------------------------------------------------
	// �e�N�X�`���̃��[�h
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/field.jpg" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexField(pD3DDevice , fPolygonWidth , fPolygonHeight , nFieldScl_X , nFieldScl_Y) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: FieldUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�j��
//
//=============================================================================
void FieldUninit( void )
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

	//-------------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�̉��
	if( g_pIndexBuffer != NULL )
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

//=============================================================================
//
//	�֐���	: FieldUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�X�V
//
//=============================================================================
void FieldUpdate( void )
{
	/*//---------------------------------
	// �E�ړ�
	if( KeyState( DIK_D ) )
	{
		g_posField.x += 3;
	}

	//---------------------------------
	// ���ړ�
	if( KeyState( DIK_A ) )
	{
		g_posField.x -= 3;
	}

	//---------------------------------
	// ���ړ�
	if( KeyState( DIK_W ) )
	{
		g_posField.z += 3;
	}

	//---------------------------------
	// ��O�ړ�
	if( KeyState( DIK_S ) )
	{
		g_posField.z -= 3;
	}

	//---------------------------------
	// ��ړ�
	if( KeyState( DIK_UP ) )
	{
		g_posField.y += 2;
	}

	//---------------------------------
	// ���ړ�
	if( KeyState( DIK_DOWN ) )
	{
		g_posField.y -= 2;
	}*/
}

//=============================================================================
//
//	�֐���	: FieldDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�`��
//
//=============================================================================
void FieldDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	HRESULT hr;
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &g_mtxWorld );		// ���[���h�}�g���b�N�X������

	//*********************************
	// �X�P�[�����f
	D3DXMatrixScaling( &mtxScl , g_sclField.x , g_sclField.y , g_sclField.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// ��]���f
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotField.y , g_rotField.x , g_rotField.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// �ړ����f
	D3DXMatrixTranslation( &mtxTrans , g_posField.x , g_posField.y , g_posField.z );
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
	
	//-------------------------------------------------------------------------
	// �v���~�e�B�u�\��
	pD3DDevice->DrawIndexedPrimitive
				( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
				0 ,								// �O�p�`�̐�
				0 ,
				g_nVertexMax ,							// ���_�̌��i���_�o�b�t�@�j
				0 ,
				g_nIndexMax - 2 );							// �v���~�e�B�u�̐�
}

//=============================================================================
//
// �֐��� : MakeVertexField
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexField( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y)
{
	//---------------------
	// �ϐ��錾
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������
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
			pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , 0.f , (-B - fY ) );

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

	g_nIndexMax = ( ( g_nVertexMax - 2 ) * 2 );


	//-------------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�쐬
	hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * g_nIndexMax , 
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&g_pIndexBuffer,
										NULL );
	// �쐬���s�����ꍇ
	if( FAILED(hr) )
	{
		// �o�b�t�@�쐬���s
		return (E_FAIL);
	}
	
	//---------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	hr = g_pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

	int index = 0;
	int gyo = 0;
	int polygon = 0;
	while( index < g_nIndexMax )
	{
		// �܂�Ԃ��n�_�������ꍇ
		if( index ==  (( nScl_X * 2 ) + 1)  + gyo )
		{
			for( int k = 0; k < 2; k++ )
			{
				if( index != g_nIndexMax )
				{ 
					pIdx[index] = nScl_X + polygon;
					index++;
				}
			}

			if( index < g_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( nScl_X + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (nScl_X + 1 )+ 1) * 2;
				polygon += (nScl_X + 1);
			}
		}
		// �����������ꍇ
		else if( index % 2 == 0 )
		{
			pIdx[index] =  (nScl_X + 1) + nNum_Gusu;
			nNum_Gusu++;
			index++;
		}

		// ��������ꍇ
		else if(  index % 2 == 1 )
		{
			pIdx[index] = nNum_Kisu;
			nNum_Kisu++;
			index++;
		}
	}
			

	//---------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�̃��b�N����
	g_pIndexBuffer->Unlock();
	
	// �쐬����
	return (S_OK);
}

D3DXVECTOR3 FieldPosGet(void)
{
	return g_posField;
}
