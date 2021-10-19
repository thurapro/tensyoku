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
#include "../hedder/meshwall.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static MESH_WALL g_aMeshWall[WALL_MAX];
static int g_nNumMeshWall = 0;						// �ǂ̑傫��
static int g_nVertexMax;							// ���_�o�b�t�@��
static int g_nIndexMax;								// �C���f�b�N�X�o�b�t�@��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y );

//=============================================================================
//
//	�֐���	: MeshWallInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �t�B�[���h������
//
//=============================================================================
HRESULT MeshWallInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nWallScl_X , int nWallScl_Y)
{
	float fPos_X = (fPolygonWidth * nWallScl_X) / 2;
	float fPos_Y = (fPolygonHeight * nWallScl_Y) / 2;

	float fPos_Z = (fPolygonHeight * nWallScl_Y) / 2;

	//-------------------------------------------------------------------------
	// �Ǐ�����
	g_aMeshWall[0].pos = D3DXVECTOR3( 0.0f , fPos_Y , fPos_Z );	// �ǂ̈ʒu
	g_aMeshWall[0].rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	// �ǂ̌���
	g_aMeshWall[0].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �ǂ̑傫��

	g_aMeshWall[1].pos = D3DXVECTOR3( fPos_X , fPos_Y , 0.0f );	// �ǂ̈ʒu
	g_aMeshWall[1].rot = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );	// �ǂ̌���
	g_aMeshWall[1].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �ǂ̑傫��

	g_aMeshWall[2].pos = D3DXVECTOR3( -fPos_X , fPos_Y , 0.0f );	// �ǂ̈ʒu
	g_aMeshWall[2].rot = D3DXVECTOR3( 0.0f , D3DX_PI * -0.5f , 0.0f );	// �ǂ̌���
	g_aMeshWall[2].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �ǂ̑傫��

	g_aMeshWall[3].pos = D3DXVECTOR3( 1.0f , fPos_Y , -fPos_Z);	// �ǂ̈ʒu
	g_aMeshWall[3].rot = D3DXVECTOR3( 0.0f , D3DX_PI * 1.0f , 0.0f );	// �ǂ̌���
	g_aMeshWall[3].scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );	// �ǂ̑傫��

	//-------------------------------------------------------------------------
	// �e�N�X�`���̃��[�h
	for( int i = 0; i < WALL_MAX; i++ )
	{
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/fa.jpg" , &g_aMeshWall[i].pD3DTexture) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexMeshWall(pD3DDevice , fPolygonWidth , fPolygonHeight , nWallScl_X ,  nWallScl_Y ) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: MeshWallUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �ǔj��
//
//=============================================================================
void MeshWallUninit( void )
{
	for( int i = 0; i < WALL_MAX; i++ )
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		if(g_aMeshWall[i].pD3DTexture != NULL)
		{
			// �e�N�X�`���̉��
			g_aMeshWall[i].pD3DTexture->Release();

			// �e�N�X�`���̕�����NULL��
			g_aMeshWall[i].pD3DTexture = NULL;
		}

		//-------------------------------------------------------------------------
		// �C���f�b�N�X�o�b�t�@�̉��
		if( g_aMeshWall[i].pIndexBuffer != NULL )
		{
			g_aMeshWall[i].pIndexBuffer->Release();
			g_aMeshWall[i].pIndexBuffer = NULL;
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̉��
		if( g_aMeshWall[i].pD3DVBXYZBuffer != NULL )
		{
			g_aMeshWall[i].pD3DVBXYZBuffer->Release();
			g_aMeshWall[i].pD3DVBXYZBuffer = NULL; 
		}
	}
}

//=============================================================================
//
//	�֐���	: MeshWallUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �ǍX�V
//
//=============================================================================
void MeshWallUpdate( void )
{

}

//=============================================================================
//
//	�֐���	: MeshWallDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �Ǖ`��
//
//=============================================================================
void MeshWallDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	HRESULT hr;
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < WALL_MAX; i++)
	{
		//-------------------------------------------------------------------------
		// ���[���h�}�g���b�N�X
		D3DXMatrixIdentity( &g_aMeshWall[i].mtxWorld );		// ���[���h�}�g���b�N�X������

		//*********************************
		// �X�P�[�����f
		D3DXMatrixScaling( &mtxScl , g_aMeshWall[i].scl.x , g_aMeshWall[i].scl.y , g_aMeshWall[i].scl.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxScl );
		
		//*********************************
		// ��]���f
		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aMeshWall[i].rot.y , g_aMeshWall[i].rot.x , g_aMeshWall[i].rot.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxRot );

		//*********************************
		// �ړ����f
		D3DXMatrixTranslation( &mtxTrans , g_aMeshWall[i].pos.x , g_aMeshWall[i].pos.y , g_aMeshWall[i].pos.z );
		D3DXMatrixMultiply( &g_aMeshWall[i].mtxWorld , &g_aMeshWall[i].mtxWorld , &mtxTrans );

		//-------------------------------------------------------------------------
		// ���[���h�}�g���b�N�X�ݒ�
		pD3DDevice->SetTransform( D3DTS_WORLD , &g_aMeshWall[i].mtxWorld );	

		//-------------------------------------------------------------------------
		// ���_���ݒ�
		pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

		//-------------------------------------------------------------------------
		//  ���_�o�b�t�@�̃Z�b�g
		pD3DDevice->SetStreamSource( 0 , g_aMeshWall[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );
		hr = pD3DDevice->SetIndices( g_aMeshWall[i].pIndexBuffer );

		//-------------------------------------------------------------------------
		// �e�N�X�`���̃Z�b�g
		pD3DDevice->SetTexture( 0 , g_aMeshWall[i].pD3DTexture );

		if(i == 4)
		{
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		
		//-------------------------------------------------------------------------
		// �v���~�e�B�u�\��
		pD3DDevice->DrawIndexedPrimitive
					( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
					0 ,								// �O�p�`�̐�
					0 ,
					g_nVertexMax ,					// ���_�̌��i���_�o�b�t�@�j
					0 ,
					g_nIndexMax - 2 );				// �v���~�e�B�u�̐�
		if(i == 4)
		{
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}

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
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight , int nScl_X , int nScl_Y )
{
	//---------------------
	// �ϐ��錾
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������
	for( int nNum = 0; nNum < WALL_MAX; nNum++ )
	{
		float fX = 0;
		float fY = 0;
		g_nVertexMax = ( (nScl_X + 1) * (nScl_Y + 1) );
		int nVertexHalf = (nScl_X + 1);
		float fTexX = 0.f;
		float fTexY = 0.f;
		float fTexWidth = 0.f;
		float fTexHeight = 0.f;

		//---------------------------------------------------------------------
		int nScl_YMax = 1;
		int nNum_Kisu = 0;
		int nNum_Gusu = 0;


		//---------------------------------------------------------------------
		// ���_�o�b�t�@�쐬����
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * g_nVertexMax ,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aMeshWall[nNum].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N
		hr = g_aMeshWall[nNum].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̍��W��
		
		float A = (float)nScl_X/2;
		float B = -A * fWidth;
		
		for( int i = 0; i < g_nVertexMax; )
		{
			for( int j = 0; j < nVertexHalf; j++ )
			{
				pVtx[i].vtx = D3DXVECTOR3( (B + fX ) , (-B - fY) , 0.0f );

				//-------------------------------------------------------------------------
				// �����̐ݒ�
				pVtx[i].nor = D3DXVECTOR3( 0.f , 0.f , -1.f );

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
		g_aMeshWall[nNum].pD3DVBXYZBuffer->Unlock();

		g_nIndexMax = ( ( g_nVertexMax - 2 ) * 2 );


		//-------------------------------------------------------------------------
		// �C���f�b�N�X�o�b�t�@�쐬
		hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * g_nIndexMax , 
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_aMeshWall[nNum].pIndexBuffer,
											NULL );
		// �쐬���s�����ꍇ
		if( FAILED(hr) )
		{
			// �o�b�t�@�쐬���s
			return (E_FAIL);
		}
		
		//---------------------------------------------------------------------
		// �C���f�b�N�X�o�b�t�@�̃��b�N
		hr = g_aMeshWall[nNum].pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

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
		g_aMeshWall[nNum].pIndexBuffer->Unlock();
	}
		
	// �쐬����
	return (S_OK);
}

MESH_WALL *MeshWallGet(void)
{
	return &g_aMeshWall[0];
}
