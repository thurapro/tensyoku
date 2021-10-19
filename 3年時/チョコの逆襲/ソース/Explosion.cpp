//=============================================================================
//
// �������� [Explosion.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_MAX (40)							// �����̐�

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static EXPLOSION g_aExplosion[EXPLOSION_MAX];		// �����̍\����
static D3DXVECTOR3 CameraRotSet;					// �J�����̃Z�b�g
static int g_nAnimetionTimer;						// �����̑҂�����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight);

//=============================================================================
//
//	�֐���	: ExplosionInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: ����������
//
//=============================================================================
HRESULT ExplosionInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight )
{
	for( int i = 0;	i < EXPLOSION_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// ����������
		g_aExplosion[i].posExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �����̈ʒu
		g_aExplosion[i].rotExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �����̌���
		g_aExplosion[i].sclExplosion = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// �����̑傫��
		g_aExplosion[i].visible = false;										// �������\������Ă��邩
		g_aExplosion[i].fAnimesionLeft = 0.0f;									// �A�j���[�V����(�e�N�X�`���[���WX)
		g_aExplosion[i].fAnimesionRight = 0.1f;

		////-------------------------------------------------------------------------
		// �e�N�X�`���̃��[�h
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/Explosion.png" , &g_aExplosion[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
		SoundFileLoad("DATA/Sound/Explosion.wav", EXPLOSION_END );
		CreateSoundBuffer(&g_aExplosion[i].soundExplosion, EXPLOSION_END);
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexExplosion(pD3DDevice , fPolygonWidth , fPolygonHeight) ) )
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
//
//	�֐���	: ExplosionUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �����j��
//
//=============================================================================
void ExplosionUninit( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		if(g_aExplosion[i].pD3DTex != NULL)
		{
			// �e�N�X�`���̉��
			g_aExplosion[i].pD3DTex->Release();

			// �e�N�X�`���̕�����NULL��
			g_aExplosion[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̉��
		if( g_aExplosion[i].pD3DVBXYZBuffer != NULL )
		{
			g_aExplosion[i].pD3DVBXYZBuffer->Release();
			g_aExplosion[i].pD3DVBXYZBuffer = NULL; 
		}

		if(g_aExplosion[i].soundExplosion != NULL)
		{
			g_aExplosion[i].soundExplosion->Release();
			g_aExplosion[i].soundExplosion = NULL;
		}
	}
	
}

//=============================================================================
//
//	�֐���	: ExplosionUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �����X�V
//
//=============================================================================
void ExplosionUpdate( void )
{
	CameraRotSet = CameraRotGet();
	VERTEX_3D *pVtx;	// ���_��
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == true )
		{
			if( g_nAnimetionTimer > 0 )
			{
				if( g_aExplosion[i].fAnimesionRight < 1.0f )
				{
					g_aExplosion[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0 );			// ���_�o�b�t�@���b�N
					g_aExplosion[i].fAnimesionLeft += 0.1f;
					g_aExplosion[i].fAnimesionRight += 0.1f;
					pVtx[0].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionLeft , 0.0f );				// �e�N�X�`�����W�X�V(�A�j���[�V����)
					pVtx[1].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionRight , 0.0f );			// �e�N�X�`�����W�X�V( �A�j���[�V����)
					pVtx[2].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionLeft , 1.0f );				// �e�N�X�`�����W�X�V( �A�j���[�V����)
					pVtx[3].tex = D3DXVECTOR2( g_aExplosion[i].fAnimesionRight , 1.0f );			// �e�N�X�`�����W�X�V( �A�j���[�V����)
					g_nAnimetionTimer = 0;
				}
				else
				{
					g_aExplosion[i].fAnimesionRight = 0.1f;
					g_aExplosion[i].fAnimesionLeft = 0;
					g_aExplosion[i].visible = false;
					g_aExplosion[i].soundExplosion->Stop();
				}
			}
			else
			{
				g_nAnimetionTimer++;
			}
			
		}
	}
}

//=============================================================================
//
//	�֐���	: ExplosionDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �����`��
//
//=============================================================================
void ExplosionDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X
			D3DXMatrixIdentity( &g_aExplosion[i].mtxWorld );		// ���[���h�}�g���b�N�X������

			D3DXMatrixInverse( &g_aExplosion[i].mtxWorld , NULL , &mtxView );
			g_aExplosion[i].mtxWorld._41 = 0.0f;
			g_aExplosion[i].mtxWorld._42 = 0.0f;
			g_aExplosion[i].mtxWorld._43 = 0.0f;

			//*********************************
			// �X�P�[�����f
			D3DXMatrixScaling( &mtxScl , g_aExplosion[i].sclExplosion.x , g_aExplosion[i].sclExplosion.y , g_aExplosion[i].sclExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxScl );
			
			//*********************************
			// ��]���f
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aExplosion[i].rotExplosion.y , g_aExplosion[i].rotExplosion.x , g_aExplosion[i].rotExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxRot );

			//*********************************
			// �ړ����f
			D3DXMatrixTranslation( &mtxTrans , g_aExplosion[i].posExplosion.x , g_aExplosion[i].posExplosion.y , g_aExplosion[i].posExplosion.z );
			D3DXMatrixMultiply( &g_aExplosion[i].mtxWorld , &g_aExplosion[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X�ݒ�
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aExplosion[i].mtxWorld );

			//-------------------------------------------------------------------------
			// ���_���ݒ�
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

			//-------------------------------------------------------------------------
			//  ���_�o�b�t�@�̃Z�b�g
			pD3DDevice->SetStreamSource( 0 , g_aExplosion[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// �e�N�X�`���̃Z�b�g
			pD3DDevice->SetTexture( 0 , g_aExplosion[i].pD3DTex );

			
			pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
			pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
			pD3DDevice->SetRenderState( D3DRS_ALPHAREF , 253 );
			pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );

			//-------------------------------------------------------------------------
			// �v���~�e�B�u�\��
			pD3DDevice->DrawPrimitive
						( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
						0 ,								// �O�p�`�̐�
						2 );							// �v���~�e�B�u�̐�
			pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
			pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
		}
	}
}

//=============================================================================
//
// �֐��� : MakeVertexExplosion
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight )
{
	
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		//---------------------
		// �ϐ��錾
		HRESULT hr;			// ���ʕϐ�
		VERTEX_3D *pVtx;	// ���_��

		//---------------------------------------------------------------------
		// ���_�o�b�t�@�쐬����
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 4 ,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_aExplosion[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N
		hr = g_aExplosion[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̍��W��
		pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0);
		pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0);
		pVtx[2].vtx = D3DXVECTOR3(-fWidth, 0, 0);
		pVtx[3].vtx = D3DXVECTOR3(fWidth, 0, 0);

		//-------------------------------------------------------------------------
		// nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		//---------------------------------------------------------------------
		// �F���̐ݒ�	( �� , �� , �� , �����x)
		pVtx[0].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[1].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[2].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );
		pVtx[3].diffuse = D3DCOLOR_RGBA( RED_MAX, GREEN_MAX, BLUE_MAX, ALPHA_MAX );

		//-------------------------------------------------------------------------
		// �e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2( 0.0f, 0.0f);			// ����̃e�N�X�`�����_�ݒ�
		pVtx[1].tex = D3DXVECTOR2( 1.0f, 0.0f);			// �E��̃e�N�X�`�����_�ݒ�
		pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);			// �E���̃e�N�X�`�����_�ݒ�
		pVtx[3].tex = D3DXVECTOR2( 1.f, 1.0f);			// �����̃e�N�X�`�����_�ݒ�

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N��
		g_aExplosion[i].pD3DVBXYZBuffer->Unlock();
	}
	
	
	// �쐬����
	return (S_OK);
}

//=============================================================================
// �r���{�[�h�ʒu�擾
//=============================================================================
void ExplosionSet(D3DXVECTOR3 position)
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_aExplosion[i].visible == false )
		{
			g_aExplosion[i].posExplosion = position;
			g_aExplosion[i].posExplosion.y -= 10.f;
			g_aExplosion[i].visible = true;
			g_aExplosion[i].soundExplosion->Play(0,0,0);
			break;
		}
	}
}