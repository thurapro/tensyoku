//=============================================================================
//
// �t�B�[���h���� [Effect.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Effect.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define EFFECT_MAX		( 200 )				// �G�t�F�N�g�̏�����

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static EFFECT g_aEffect[EFFECT_MAX];

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pD3DDevice,float fEffectWidth,float fEffectHeight);

//=============================================================================
//
//	�֐���	: EffectInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �G�t�F�N�g������
//
//=============================================================================
HRESULT EffectInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fEffectWidth,float fEffectHeight)
{
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		//-------------------------------------------------------------------------
		// �G�t�F�N�g���̊���
		g_aEffect[i].posEffect = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );		// �G�t�F�N�g�̈ʒu
		g_aEffect[i].rotEffect = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �G�t�F�N�g�̌���
		g_aEffect[i].sclEffect = D3DXVECTOR3( 0.4f , 0.4f , 0.4f );		// �G�t�F�N�g�̑傫��
		g_aEffect[i].nAlpha = ALPHA_MAX;
		g_aEffect[i].visible = false;									// �\������Ă��邩

		//-------------------------------------------------------------------------
		// �e�N�X�`���̃��[�h
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/effect000.jpg" , &g_aEffect[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexEffect(pD3DDevice , fEffectWidth , fEffectHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: EffectUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�j��
//
//=============================================================================
void EffectUninit( void )
{
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		if(g_aEffect[i].pD3DTex != NULL)
		{
			// �e�N�X�`���̉��
			g_aEffect[i].pD3DTex->Release();

			// �e�N�X�`���̕�����NULL��
			g_aEffect[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̉��
		if( g_aEffect[i].pD3DVBXYZBuffer != NULL )
		{
			g_aEffect[i].pD3DVBXYZBuffer->Release();
			g_aEffect[i].pD3DVBXYZBuffer = NULL; 
		}
	}

}

//=============================================================================
//
//	�֐���	: EffectUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�X�V
//
//=============================================================================
void EffectUpdate(void)
{
	VERTEX_3D *pVtx;	// ���_��
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		if( g_aEffect[i].visible == true )
		{
			if(g_aEffect[i].nAlpha > 0 )
			{
				if( g_aEffect[i].nType == 0 )
				{
					g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
					pVtx[0].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[1].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[2].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					pVtx[3].diffuse = D3DCOLOR_RGBA( 0, 0, 255, g_aEffect[i].nAlpha );
					g_aEffect[i].pD3DVBXYZBuffer->Unlock();
					g_aEffect[i].nAlpha -= 50; 
				}
				else
				{
					g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
					pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, g_aEffect[i].nAlpha );
					g_aEffect[i].pD3DVBXYZBuffer->Unlock();
					g_aEffect[i].nAlpha -= 50; 
				}
			}
			else
			{
				g_aEffect[i].nAlpha = ALPHA_MAX;
				g_aEffect[i].visible = false;
			}
		}
	}
}

//=============================================================================
//
//	�֐���	: EffectDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �t�B�[���h�`��
//
//=============================================================================
void EffectDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < EFFECT_MAX; i++ )
	{	
		if( g_aEffect[i].visible == true )
		{
			//-----------------------------------
			// ���[���h�}�g���b�N�X
			D3DXMatrixIdentity( &g_aEffect[i].mtxWorld );		// ���[���h�}�g���b�N�X������

			D3DXMatrixInverse( &g_aEffect[i].mtxWorld , NULL , &mtxView );
			g_aEffect[i].mtxWorld._41 = 0.0f;
			g_aEffect[i].mtxWorld._42 = 0.0f;
			g_aEffect[i].mtxWorld._43 = 0.0f;

			//*********************************
			// �X�P�[�����f
			D3DXMatrixScaling( &mtxScl , g_aEffect[i].sclEffect.x , g_aEffect[i].sclEffect.y , g_aEffect[i].sclEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxScl );
			
			//*********************************
			// ��]���f
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aEffect[i].rotEffect.y , g_aEffect[i].rotEffect.x , g_aEffect[i].rotEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxRot );

			//*********************************
			// �ړ����f
			D3DXMatrixTranslation( &mtxTrans , g_aEffect[i].posEffect.x , g_aEffect[i].posEffect.y , g_aEffect[i].posEffect.z );
			D3DXMatrixMultiply( &g_aEffect[i].mtxWorld , &g_aEffect[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X�ݒ�
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aEffect[i].mtxWorld );	

			//-------------------------------------------------------------------------
			// ���_���ݒ�
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

			//-------------------------------------------------------------------------
			//  ���_�o�b�t�@�̃Z�b�g
			pD3DDevice->SetStreamSource( 0 , g_aEffect[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// �e�N�X�`���̃Z�b�g
			pD3DDevice->SetTexture( 0 , g_aEffect[i].pD3DTex );
			

			//-------------------------------------------------------------------------
			// �����_�[�X�e�[�g
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

			//-------------------------------------------------------------------------
			// �v���~�e�B�u�\��
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
						0 ,								// �ŏ��ɏ������_�͉����H
						2 );							// �v���~�e�B�u�̐�

			pD3DDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
	}
}

//=============================================================================
//
// �֐��� : MakeVertexEffect
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pD3DDevice,float fEffectWidth,float fEffectHeight)
{
	//---------------------
	// �ϐ��錾
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��

	int PrimitiveMax = (int)(fEffectWidth + 1) + (int)(fEffectHeight + 1);

	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		//---------------------------------------------------------------------
		// ���_�o�b�t�@�쐬����
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aEffect[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N
		hr = g_aEffect[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		if( FAILED( hr ) )
		{
			return (E_FAIL);
		}

		//float Width = fEffectWidth * 0.5f;
		
		//-------------------------------------------------------------------------
		// ���_�o�b�t�@��
		pVtx[0].vtx = D3DXVECTOR3(-fEffectWidth , fEffectHeight , 0);
		pVtx[1].vtx = D3DXVECTOR3(fEffectWidth , fEffectHeight, 0);
		pVtx[2].vtx = D3DXVECTOR3(-fEffectWidth , -fEffectHeight , 0);
		pVtx[3].vtx = D3DXVECTOR3(fEffectWidth , -fEffectHeight , 0);

		//-------------------------------------------------------------------------
		// nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[1].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[2].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );
		pVtx[3].nor = D3DXVECTOR3( 0.f , 1.0f , 0.f );

		//---------------------------------------------------------------------
		// �F���̐ݒ�	( �� , �� , �� , �����x)
		pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
													BLUE_MAX , ALPHA_MAX );
		pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , 
													 BLUE_MAX , ALPHA_MAX );
		pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX ,
														BLUE_MAX , ALPHA_MAX );
		pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX ,
														BLUE_MAX , ALPHA_MAX );

		//-------------------------------------------------------------------------
		// �e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2( 0.f, 1.f );					// ����̃e�N�X�`�����_�ݒ�
		pVtx[1].tex = D3DXVECTOR2( 0.f, 0.f );					// �E��̃e�N�X�`�����_�ݒ�
		pVtx[2].tex = D3DXVECTOR2( 1.f, 1.f );					// �E���̃e�N�X�`�����_�ݒ�
		pVtx[3].tex = D3DXVECTOR2( 0.f, 1.f );					// �����̃e�N�X�`�����_�ݒ�

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N��
		g_aEffect[i].pD3DVBXYZBuffer->Unlock();
	}

	
	// �쐬����
	return (S_OK);
}

void EffectSet( D3DXVECTOR3 position , int nType )
{
	for( int i = 0; i < EFFECT_MAX; i++ )
	{
		if( g_aEffect[i].visible != true )
		{
			g_aEffect[i].posEffect = position;
			g_aEffect[i].nType = nType;
			g_aEffect[i].visible = true;
			break;
		}
	}
}


