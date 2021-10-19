//=============================================================================
//
// �t�B�[���h���� [Shadow.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Shadow.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SHADOW_MAX (100)					// �e�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static SHADOW g_aShadow[SHADOW_MAX];		// �e�ϐ�

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pD3DDevice,float fShadowWidth,float fShadowHeight);

//=============================================================================
//
//	�֐���	: ShadowInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �e������
//
//=============================================================================
HRESULT ShadowInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fShadowWidth,float fShadowHeight)
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// �e���̊���
		g_aShadow[i].posShadow = D3DXVECTOR3( 0.0f , 0.1f , 0.0f );		// �e�̈ʒu
		g_aShadow[i].rotShadow = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �e�̌���
		g_aShadow[i].sclShadow = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// �e�̑傫��
		g_aShadow[i].visible = false;

		//-------------------------------------------------------------------------
		// �e�N�X�`���̃��[�h
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/shadow000.jpg" , &g_aShadow[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexShadow(pD3DDevice , fShadowWidth , fShadowHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: ShadowUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �e�j��
//
//=============================================================================
void ShadowUninit( void )
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		if(g_aShadow[i].pD3DTex != NULL)
		{
			// �e�N�X�`���̉��
			g_aShadow[i].pD3DTex->Release();

			// �e�N�X�`���̕�����NULL��
			g_aShadow[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̉��
		if( g_aShadow[i].pD3DVBXYZBuffer != NULL )
		{
			g_aShadow[i].pD3DVBXYZBuffer->Release();
			g_aShadow[i].pD3DVBXYZBuffer = NULL;
			
		}
	}

}

//=============================================================================
//
//	�֐���	: ShadowUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �ʒu
//			 ���̉e��
//
//	�@�\	: �e�X�V
//
//=============================================================================
void ShadowUpdate(D3DXVECTOR3 position , int nNum, int nType)
{
	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		if(g_aShadow[i].visible == true)
		{
			if( g_aShadow[i].nNum == nNum)
			{
				if( g_aShadow[i].nType == nType )
				{
					g_aShadow[i].posShadow = position;
					g_aShadow[i].posShadow.y = 0.1f;
					break;
				}
			}
		}
	}
}

//=============================================================================
//
//	�֐���	: ShadowDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �f�o�C�X
//
//	�@�\	: �e�`��
//
//=============================================================================
void ShadowDraw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < SHADOW_MAX; i++ )
	{	
		if( g_aShadow[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X
			D3DXMatrixIdentity( &g_aShadow[i].mtxWorld );		// ���[���h�}�g���b�N�X������

			//*********************************
			// �X�P�[�����f
			D3DXMatrixScaling( &mtxScl , g_aShadow[i].sclShadow.x , g_aShadow[i].sclShadow.y , g_aShadow[i].sclShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxScl );
			
			//*********************************
			// ��]���f
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aShadow[i].rotShadow.y , g_aShadow[i].rotShadow.x , g_aShadow[i].rotShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxRot );

			//*********************************
			// �ړ����f
			D3DXMatrixTranslation( &mtxTrans , g_aShadow[i].posShadow.x , g_aShadow[i].posShadow.y , g_aShadow[i].posShadow.z );
			D3DXMatrixMultiply( &g_aShadow[i].mtxWorld , &g_aShadow[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X�ݒ�
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aShadow[i].mtxWorld );	

			//-------------------------------------------------------------------------
			// �����_�[�X�e�[�g
			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE );

			//-------------------------------------------------------------------------
			// ���_���ݒ�
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

			//-------------------------------------------------------------------------
			//  ���_�o�b�t�@�̃Z�b�g
			pD3DDevice->SetStreamSource( 0 , g_aShadow[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// �e�N�X�`���̃Z�b�g
			pD3DDevice->SetTexture( 0 , g_aShadow[i].pD3DTex );
	
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//-------------------------------------------------------------------------
			// �v���~�e�B�u�\��
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
						0 ,								// �ŏ��ɏ������_�͉����H
						2 );							// �v���~�e�B�u�̐�

			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
		}
	}
}

//=============================================================================
//
// �֐��� : MakeVertexShadow
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//		 �e�̕�
//		 �e�̍���
//
// �@�\ : �e�̒��_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pD3DDevice,float fShadowWidth,float fShadowHeight)
{
	//---------------------
	// �ϐ��錾
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��

	int PrimitiveMax = (int)(fShadowWidth + 1) + (int)(fShadowHeight + 1);

	for( int i = 0; i < SHADOW_MAX; i++ )
	{
		//---------------------------------------------------------------------
		// ���_�o�b�t�@�쐬����
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aShadow[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N
		hr = g_aShadow[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		if( FAILED( hr ) )
		{
			return (E_FAIL);
		}

		float Width = fShadowWidth * 0.5f;
		
		//-------------------------------------------------------------------------
		// ���_�o�b�t�@��
		pVtx[0].vtx = D3DXVECTOR3(-Width , 0 , -fShadowHeight);
		pVtx[1].vtx = D3DXVECTOR3(-Width , 0 , fShadowHeight);
		pVtx[2].vtx = D3DXVECTOR3(Width , 0 , -fShadowHeight);
		pVtx[3].vtx = D3DXVECTOR3(Width , 0 , fShadowHeight);

		//-------------------------------------------------------------------------
		// nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[1].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[2].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[3].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

		//---------------------------------------------------------------------
		// �F���̐ݒ�	( �� , �� , �� , �����x)
		pVtx[0].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[1].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[2].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);
		pVtx[3].diffuse = D3DCOLOR_RGBA(RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX);

		//-------------------------------------------------------------------------
		// �e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2( 0.f, 1.f );					// ����̃e�N�X�`�����_�ݒ�
		pVtx[1].tex = D3DXVECTOR2( 0.f, 0.f );					// �E��̃e�N�X�`�����_�ݒ�
		pVtx[2].tex = D3DXVECTOR2( 1.f, 1.f );					// �E���̃e�N�X�`�����_�ݒ�
		pVtx[3].tex = D3DXVECTOR2( 0.f, 1.f );					// �����̃e�N�X�`�����_�ݒ�

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N��
		g_aShadow[i].pD3DVBXYZBuffer->Unlock();
	}

	// �쐬����
	return (S_OK);
}

//=============================================================================
//
// �֐��� : ShadowSet
//
// �߂�l : �Ȃ�
//
// ���� : �ʒu
//		 ���̉e��
//
// �@�\ : �e���Z�b�g
//
//=============================================================================
void ShadowSet(D3DXVECTOR3 position , int nType, int nNum)
{
	for( int i = 0; i < SHADOW_MAX; i++ )				// �e���ő吔����
	{
		if( g_aShadow[i].visible != true )				// �e���g���Ă��Ȃ�����
		{
			g_aShadow[i].posShadow = position;			// �e�̈ʒu���Z�b�g
			if( nType == BULLET_TYPE )
			{
				g_aShadow[i].sclShadow = D3DXVECTOR3(0.4f , 0.4f , 0.4f);
			}
			g_aShadow[i].nType = nType;
			g_aShadow[i].visible = true;				// �e���g��ꂽ
			g_aShadow[i].nNum = nNum;
			break;										// ���[�v��E�o
		}
	}
}

//=============================================================================
//
// �֐��� : ShadowDelete
//
// �߂�l : �Ȃ�
//
// ���� : ���̉e��
//
// �@�\ : �e���폜
//
//=============================================================================
void ShadowDelete(int nType , int nNum)
{
	for(int i = 0; i < SHADOW_MAX; i++)
	{
		if( g_aShadow[i].nType == nType )
		{
			if( g_aShadow[i].nNum == nNum )
			{
				g_aShadow[i].posShadow = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
				g_aShadow[i].visible = false;
				g_aShadow[i].nNum = -1;
				break;
			}
		}
	}
}