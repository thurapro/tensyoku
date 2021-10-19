//=============================================================================
//
// �e���� [Bullet.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Bullet.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static BULLET g_aBullet[BULLET_MAX];				// �e�̍\����
static D3DXVECTOR3 CameraRotSet;					// �J�����̃Z�b�g

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexBullet( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight);

//=============================================================================
//
//	�֐���	: BulletInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �e������
//
//=============================================================================
HRESULT BulletInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight)
{
	for( int i = 0;	i < BULLET_MAX; i++ )
	{
		//-------------------------------------------------------------------------
		// �e������
		g_aBullet[i].posBullet = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �e�̈ʒu
		g_aBullet[i].rotBullet = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �e�̌���
		g_aBullet[i].sclBullet = D3DXVECTOR3( 0.2f , 0.2f , 0.2f );		// �e�̑傫��
		g_aBullet[i].visible = false;									// �e���\������Ă��邩
		
		g_aBullet[i].fWidth = fPolygonWidth;
		g_aBullet[i].fHeight = fPolygonHeight;

		////-------------------------------------------------------------------------
		// �e�N�X�`���̃��[�h
		if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/bullet000.png" , &g_aBullet[i].pD3DTex) ) )
		{
			return E_FAIL;
		}
		SoundFileLoad("DATA/Sound/Shot.wav" , BULLET_SHOT);
		CreateSoundBuffer(&g_aBullet[i].soundBullet, BULLET_SHOT);
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexBullet(pD3DDevice , fPolygonWidth , fPolygonHeight) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
//
//	�֐���	: BulletUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �e�j��
//
//=============================================================================
void BulletUninit(void)
{
	for( int i = 0; i < BULLET_MAX; i++ )
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		if(g_aBullet[i].pD3DTex != NULL)
		{
			// �e�N�X�`���̉��
			g_aBullet[i].pD3DTex->Release();

			// �e�N�X�`���̕�����NULL��
			g_aBullet[i].pD3DTex = NULL;
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̉��
		if( g_aBullet[i].pD3DVBXYZBuffer != NULL )
		{
			g_aBullet[i].pD3DVBXYZBuffer->Release();
			g_aBullet[i].pD3DVBXYZBuffer = NULL; 
		}
		if(g_aBullet[i].soundBullet != NULL)
		{
			g_aBullet[i].soundBullet->Release();
			g_aBullet[i].soundBullet = NULL;
		}
	}
}

//=============================================================================
//
//	�֐���	: BulletUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �e�X�V
//
//=============================================================================
void BulletUpdate( void )
{
	MESH_WALL *aMeshWall = MeshWallGet();
	for( int i = 0; i < BULLET_MAX; i++ )
	{
		if( g_aBullet[i].visible == true )
		{
			g_aBullet[i].MemoryPos = g_aBullet[i].posBullet;
			g_aBullet[i].fMoveX = 8 * sin(g_aBullet[i].frotMove);
			g_aBullet[i].fMoveZ = 8 * cos(g_aBullet[i].frotMove);
			g_aBullet[i].posBullet.x -= g_aBullet[i].fMoveX;
			g_aBullet[i].posBullet.z -= g_aBullet[i].fMoveZ;
			EffectSet( g_aBullet[i].posBullet , g_aBullet[i].nType );
			g_aBullet[i].soundBullet->Play(0,0,0);
			ShadowUpdate(g_aBullet[i].posBullet , i, BULLET_TYPE);
			if( g_aBullet[i].posBullet.x <= aMeshWall[2].pos.x + 15|| 
				g_aBullet[i].posBullet.x > aMeshWall[1].pos.x - 15||
				g_aBullet[i].posBullet.z >= aMeshWall[0].pos.z - 15 ||
				g_aBullet[i].posBullet.z < aMeshWall[3].pos.z + 15)
			{
				ExplosionSet(g_aBullet[i].MemoryPos);
				g_aBullet[i].soundBullet->Stop();
				g_aBullet[i].posBullet.x = 0;
				g_aBullet[i].posBullet.z = 0;
				g_aBullet[i].visible = false;
				ShadowDelete(BULLET_TYPE , i);
			}

			
		}
	}

}

//=============================================================================
//
//	�֐���	: BulletDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �e�`��
//
//=============================================================================
void BulletDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	for( int i = 0; i < BULLET_MAX; i++ )
	{
		if( g_aBullet[i].visible == true )
		{
			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X
			D3DXMatrixIdentity( &g_aBullet[i].mtxWorld );		// ���[���h�}�g���b�N�X������

			D3DXMatrixInverse( &g_aBullet[i].mtxWorld , NULL , &mtxView );
			g_aBullet[i].mtxWorld._41 = 0.0f;
			g_aBullet[i].mtxWorld._42 = 0.0f;
			g_aBullet[i].mtxWorld._43 = 0.0f;

			//*********************************
			// �X�P�[�����f
			D3DXMatrixScaling( &mtxScl , g_aBullet[i].sclBullet.x , g_aBullet[i].sclBullet.y , g_aBullet[i].sclBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxScl );
			
			//*********************************
			// ��]���f
			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_aBullet[i].rotBullet.y , g_aBullet[i].rotBullet.x , g_aBullet[i].rotBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxRot );

			//*********************************
			// �ړ����f
			D3DXMatrixTranslation( &mtxTrans , g_aBullet[i].posBullet.x , g_aBullet[i].posBullet.y , g_aBullet[i].posBullet.z );
			D3DXMatrixMultiply( &g_aBullet[i].mtxWorld , &g_aBullet[i].mtxWorld , &mtxTrans );

			//-------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X�ݒ�
			pD3DDevice->SetTransform( D3DTS_WORLD , &g_aBullet[i].mtxWorld );

			//-------------------------------------------------------------------------
			// ���_���ݒ�
			pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

			//-------------------------------------------------------------------------
			//  ���_�o�b�t�@�̃Z�b�g
			pD3DDevice->SetStreamSource( 0 , g_aBullet[i].pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

			//-------------------------------------------------------------------------
			// �e�N�X�`���̃Z�b�g
			pD3DDevice->SetTexture( 0 , g_aBullet[i].pD3DTex );

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
// �֐��� : MakeVertexBullet
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexBullet( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight)
{
	for( int i = 0; i < BULLET_MAX; i++ )
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
											&g_aBullet[i].pD3DVBXYZBuffer,
											NULL );
		if( FAILED(hr) )
		{
			return (E_FAIL);
		}

		//-------------------------------------------------------------------------
		// ���_�o�b�t�@�̃��b�N
		hr = g_aBullet[i].pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

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
		g_aBullet[i].pD3DVBXYZBuffer->Unlock();
	}
	// �쐬����
	return (S_OK);
}

//=============================================================================
//
// �֐��� : BulletSet
// 
// �߂�l : �Ȃ�
//
// ���� : �ʒu
//		 �e�̑ł���
//
// �@�\ : �e���Z�b�g
//
//=============================================================================
void BulletSet(D3DXVECTOR3 position , float rotY , int nType)
{
	for( int i = 0; i < BULLET_MAX; i++ )						// �e���ő吔��
	{
		if( g_aBullet[i].visible == false )						// �g���Ă��Ȃ��e���o��
		{
			g_aBullet[i].posBullet = position;					// �e�̈ʒu���Z�b�g
			g_aBullet[i].posBullet.y = 12.f;					// �o���b�g����ɂ�����
			g_aBullet[i].frotMove = rotY;						// �e�̐i�ޕ������Z�b�g
			g_aBullet[i].visible = true;						// �e���g����
			g_aBullet[i].nType = nType;
			ShadowSet(g_aBullet[i].posBullet , BULLET_TYPE , i);// �e���Z�b�g
			break;												// ���[�v�E�o
		}
	}
}

BULLET *BulletPosGet(void)
{
	return &g_aBullet[0];
}