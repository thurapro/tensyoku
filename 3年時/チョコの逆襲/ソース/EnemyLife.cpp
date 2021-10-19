//=============================================================================
//
// �G�̖{������ [EnemyLife.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/EnemyLife.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SPEED_X			(3)
#define SPEED_Z			(3)
#define TEX_SPEED_X		(0.25f)
#define TEX_MAX			(1.0f)
#define ANIMECNT_MAX	(30)
#define TEX_INIT		(0.25f)
#define TYPE_LIFE		(4)
#define DAMAGE			(3)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static D3DXMATRIX mtxWorld;						// ���[���h
static D3DXVECTOR3 g_posEnemyLife;				// �G�̖{���̈ʒu
static D3DXVECTOR3 g_rotEnemyLife;				// �G�̖{���̌���
static D3DXVECTOR3 g_sclEnemyLife;				// �G�̖{���̑傫��
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// XYZ�̒��_�o�b�t�@
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// �e�N�X�`��
static float g_fmoveX;
static float g_fmoveZ;
static float g_fLeftTop;
static float g_fRightTop;
static float g_fLeftBottom;
static float g_fRightBottom;
static int nAnimeCnt;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexEnemyLife( LPDIRECT3DDEVICE9 pD3DDevice, float fWidth, float fHeight);

//=============================================================================
//
//	�֐���	: EnemyLifeInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �G�̖{��������
//
//=============================================================================
HRESULT EnemyLifeInit(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//-------------------------------------------------------------------------
	// �G�̖{��������
	g_posEnemyLife = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �G�̖{���̈ʒu
	g_rotEnemyLife = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );		// �G�̖{���̌���
	g_sclEnemyLife = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );		// �G�̖{���̑傫��

	g_fmoveX = SPEED_X;
	g_fmoveZ = SPEED_Z;

	g_fLeftTop = 0.0f;
	g_fRightTop = TEX_INIT;
	g_fLeftBottom = 0.0f;
	g_fRightBottom = TEX_INIT;
	nAnimeCnt = 0;


	////-------------------------------------------------------------------------
	// �e�N�X�`���̃��[�h
	if( FAILED( D3DXCreateTextureFromFile(pD3DDevice , "DATA/Texture/hart.png" , &g_pD3DTex) ) )
	{
		return E_FAIL;
	}

	//-------------------------------------------------------------------------
	// ���_���쐬
	if( FAILED( MakeVertexEnemyLife(pD3DDevice, 20, 30) ) )
	{
		return E_FAIL;
	}
	
	ShadowSet(g_posEnemyLife, TYPE_LIFE, 60);

	return S_OK;
}

//=============================================================================
//
//	�֐���	: EnemyLifeUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �G�̖{���j��
//
//=============================================================================
void EnemyLifeUninit(void)
{
	for( int i = 0; i < BULLET_MAX; i++ )
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
	
}

//=============================================================================
//
//	�֐���	: EnemyLifeUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �G�̖{���X�V
//
//=============================================================================
void EnemyLifeUpdate( void )
{
	//----------------
	// �ϐ��錾
	VERTEX_3D *pVtx;	// ���_��

	BULLET *pBullet = BulletPosGet();
	int nLife = EnemyLifeGet();

	if( nLife > 1 )
	{
		// ���_�o�b�t�@�[���b�N
		g_pD3DVBXYZBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

		pVtx[0].tex = D3DXVECTOR2( g_fLeftTop , 0.0f);			// ����̃e�N�X�`�����_�ݒ�
		pVtx[1].tex = D3DXVECTOR2( g_fRightTop, 0.0f);			// �E��̃e�N�X�`�����_�ݒ�
		pVtx[2].tex = D3DXVECTOR2( g_fLeftBottom, 1.0f);			// �E���̃e�N�X�`�����_�ݒ�
		pVtx[3].tex = D3DXVECTOR2( g_fRightBottom, 1.0f);			// �����̃e�N�X�`�����_�ݒ�
		
		g_pD3DVBXYZBuffer->Unlock();
		
		if( nAnimeCnt > ANIMECNT_MAX)
		{
			if( g_fLeftBottom < TEX_MAX )
			{
				g_fLeftTop += TEX_SPEED_X;
				g_fRightTop += TEX_SPEED_X;
				g_fLeftBottom += TEX_SPEED_X;
				g_fRightBottom += TEX_SPEED_X;
			}
			else
			{
				g_fLeftTop = 0.0f;
				g_fRightTop = TEX_INIT;
				g_fLeftBottom = 0.0f;
				g_fRightBottom = TEX_INIT;
			}
			nAnimeCnt = 0;
		}
		else
		{
			nAnimeCnt++;
		}
		for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
		{
			if( pBullet[nCntBullet].visible == true )
			{
				if( pBullet[nCntBullet].nType == PLAYER_TYPE )
				{
					if( g_posEnemyLife.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
						pBullet[nCntBullet].posBullet.x < ( g_posEnemyLife.x + 20 ) &&
						g_posEnemyLife.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight) &&
						pBullet[nCntBullet].posBullet.z < g_posEnemyLife.z + 30)
					{
						pBullet[nCntBullet].visible = false;
						pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
						pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
						ExplosionSet( pBullet[nCntBullet].MemoryPos);
						ShadowDelete( BULLET_TYPE , nCntBullet);
						EnemyLifeSet( DAMAGE );
					}
				}
			}
		}
	}
	else
	{
		g_sclEnemyLife= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionSet(g_posEnemyLife);
	}
}

//=============================================================================
//
//	�֐���	: EnemyLifeDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �G�̖{���`��
//
//=============================================================================
void EnemyLifeDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxView = CameraView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &mtxWorld );		// ���[���h�}�g���b�N�X������

	D3DXMatrixInverse( &mtxWorld , NULL , &mtxView );
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//*********************************
	// �X�P�[�����f
	D3DXMatrixScaling( &mtxScl , g_sclEnemyLife.x , g_sclEnemyLife.y , g_sclEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );
	
	//*********************************
	// ��]���f
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotEnemyLife.y , g_rotEnemyLife.x , g_rotEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxRot );

	//*********************************
	// �ړ����f
	D3DXMatrixTranslation( &mtxTrans , g_posEnemyLife.x , g_posEnemyLife.y , g_posEnemyLife.z );
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X�ݒ�
	pD3DDevice->SetTransform( D3DTS_WORLD , &mtxWorld );

	//-------------------------------------------------------------------------
	// ���_���ݒ�
	pD3DDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//-------------------------------------------------------------------------
	//  ���_�o�b�t�@�̃Z�b�g
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer , 0 ,sizeof(VERTEX_3D) );

	//-------------------------------------------------------------------------
	// �e�N�X�`���̃Z�b�g
	pD3DDevice->SetTexture( 0 , g_pD3DTex );

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

//=============================================================================
//
// �֐��� : MakeVertexEnemyLife
//
// �߂�l : HRESULT
//
// ���� : �f�o�C�X 
//
// �@�\ : ���_�o�b�t�@�쐬
//
//=============================================================================
HRESULT MakeVertexEnemyLife( LPDIRECT3DDEVICE9 pD3DDevice , float fWidth , float fHeight)
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
	pVtx[1].tex = D3DXVECTOR2( 0.25f, 0.0f);			// �E��̃e�N�X�`�����_�ݒ�
	pVtx[2].tex = D3DXVECTOR2( 0.0f, 1.0f);			// �E���̃e�N�X�`�����_�ݒ�
	pVtx[3].tex = D3DXVECTOR2( 0.25f, 1.0f);			// �����̃e�N�X�`�����_�ݒ�
	
	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̃��b�N��
	g_pD3DVBXYZBuffer->Unlock();

	// �쐬����
	return (S_OK);
}

