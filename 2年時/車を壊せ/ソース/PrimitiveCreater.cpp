//================================
// �C���N���[�h
//================================
#include <d3dx9.h>
#include <windows.h>
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/common.h"
#include "../hedder/Direct3DCreater.h"
#include "../hedder/Texture.h"
#include "../hedder/InputKey.h"
#include "../hedder/common.h"
#include "../hedder/math.h"

//============================================================================
// �O���[�o���ϐ�
//============================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer[BUFFERMAX] = {NULL};	// XYZ�̒��_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer[BUFFERMAX] = {NULL};		// �C���f�b�N�X�o�b�t�@
static VTEX g_Vtex;
static float g_fWidth	= 0;
static float g_fHeight	= 0;
static float g_fAngle	= 0;
static float g_fPosX	= 0;
static float g_fPosY	= 0;

//=============================================================================
//
// �֐���	:	PrimitiveInit
//
// �߂�l	:	���������邱�Ƃ��ł����� BOOL
//
// ����		:	�Ȃ�
//
// �@�\		:	���_�o�b�t�@�[�쐬
//				�C���f�b�N�X�o�b�t�@�[�쐬
//
//=============================================================================
BOOL PrimitiveInit( void )
{
	// �R��
	HRESULT hr;

	// �v���~�e�B�u�`��
	VERTEX_2D *pVtx;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9	pD3DDevice  = Direct3ddeviceGetDevice();

	WORD *pIdx;

	for( int i = 0; i < MAXID; i++)
	{
		// ���_�o�b�t�@���쐬
		hr = pD3DDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * VTEXMAX,
											D3DUSAGE_WRITEONLY,
											D3DFMT_VERTEXDATA,
											D3DPOOL_MANAGED,
											&g_pD3DVBXYZBuffer[i],
											NULL );
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// �C���f�b�N�X�o�b�t�@���쐬
		hr = pD3DDevice->CreateIndexBuffer( sizeof(WORD) * VTEXMAX , 
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_pIndexBuffer[i],
											NULL);
		if( FAILED( hr ) )
		{
			return FALSE;
		}


		// ���_�o�b�t�@�̃��b�N
		hr = g_pD3DVBXYZBuffer[i]->Lock( 0 , 0 , (void **)&pVtx , 0);
		
		// ���_�o�b�t�@�����b�N�ł��Ă��Ȃ����
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// ���_�o�b�t�@�̍��W�ݒ�
		pVtx[LEFTTOP_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// ����̒��_

		pVtx[RIGHTTOP_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// �E��̒��_

		pVtx[LEFTBOTTOM_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );		// �E���̒��_

		pVtx[RIGHTBOTTOM_VTEX].vtx = D3DXVECTOR3( 0 , 0 , 0.f );	// �����̒��_
		

		// rhw�̐ݒ�
		pVtx[LEFTTOP_VTEX].rhw = 1.f;

		pVtx[RIGHTTOP_VTEX].rhw = 1.f;

		pVtx[LEFTBOTTOM_VTEX].rhw = 1.f;

		pVtx[RIGHTBOTTOM_VTEX].rhw = 1.f;


		// �F���̐ݒ�					( �� , �� , �� , �����x)
		pVtx[LEFTTOP_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[RIGHTTOP_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[LEFTBOTTOM_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );

		pVtx[RIGHTBOTTOM_VTEX].diffuse = D3DCOLOR_RGBA( RED_MAX , GREEN_MAX , BLUE_MAX , ALPHA_MAX );


		// �e�N�X�`���̍��W�ݒ�
		pVtx[LEFTTOP_VTEX].tex = D3DXVECTOR2(0.f, 0.f);						// ����̃e�N�X�`�����_�ݒ�

		pVtx[RIGHTTOP_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// �E��̃e�N�X�`�����_�ݒ�

		pVtx[LEFTBOTTOM_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// �E���̃e�N�X�`�����_�ݒ�

		pVtx[RIGHTBOTTOM_VTEX].tex = D3DXVECTOR2(0.f, 0.f);					// �����̃e�N�X�`�����_�ݒ�


		// ���_�o�b�t�@�̃��b�N����
		g_pD3DVBXYZBuffer[i]->Unlock();

		// �C���f�b�N�X�o�b�t�@�̃��b�N
		hr = g_pIndexBuffer[i]->Lock( 0 , 0 , (void **)&pIdx , 0);

		// ���b�N����Ȃ������ꍇ
		if( FAILED( hr ) )
		{
			return FALSE;
		}

		// �C���f�b�N�X�̏�������
		pIdx[LEFTTOP_VTEX] = LEFTTOP_VTEX;

		pIdx[RIGHTTOP_VTEX] = RIGHTTOP_VTEX;

		pIdx[LEFTBOTTOM_VTEX] = LEFTBOTTOM_VTEX;

		pIdx[RIGHTBOTTOM_VTEX] = RIGHTBOTTOM_VTEX;

		// �C���f�b�N�X�o�b�t�@�̃��b�N����
		g_pIndexBuffer[i]->Unlock();
		
	}
	return TRUE;
}


//============================================================================
//
// �֐���	:	PrimitiveGetDevice�֐�
//
// �߂�l	:	�f�o�C�X��Ԃ�
//
// ����		:	�e�L�X�`���̔ԍ�
//				���_���W�n�_(x , y)
//				���_���W�I�_(x , y)
//				�e�L�X�`���n�_���W(x , y)
//				�e�L�X�`���I�_���W(x , y)
//
// �@�\		:	�v���~�e�B�u�̐���
//			
//
//============================================================================
void PrimitiveCreate(	int ID,										// �ǂ̃v���~�e�B�u����肽����
						int VtxType	,								// �v���~�e�B�u����]���邩(1) , ���Ȃ���(2)
						int TextureNum ,							// �e�N�X�`���̔ԍ�
						float fAngle ,								// �e�N�X�`���̊p�x
						float fPosX , float fPosY,					// ���_�|�W�V�����w��
						float fWidth , float fHeight,				// ���ƍ����w��
						float texx0 , float texy0,					// �e�L�X�`���[�̎n�_���W
						float texx1 , float texy1 )					// �e�L�X�`���[�̏I�_���W
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pD3DDevice  = Direct3ddeviceGetDevice();

	// �e�N�X�`���̃|�C���^��`
	LPDIRECT3DTEXTURE9 *pD3DTex;

	// �e�N�X�`���������Ă���
	pD3DTex = GetD3DTexture(TextureNum);

	// �v���~�e�B�u�`��
	VERTEX_2D *pVtx;

	// ���_�̒l��ݒ�ł������̃t���O
	BOOL bVtex = FALSE;

	// ���̐ݒ�
	g_fWidth	= fWidth ;

	// �����̐ݒ�
	g_fHeight	= fHeight;

	// �p�x�̐ݒ�
	g_fAngle	= fAngle;

	// �ʒu�ݒ�
	g_fPosX		= fPosX;

	// �ʒu�ݒ�
	g_fPosY		= fPosY;

	// ���_�����`���ł��邩
	// ���_�����Ȃ��`���ł���̂�
	switch( VtxType )
	{
		// ��钸�_�ݒ�
	case ROTATION	: VtexRotation();

		// ���_���W����ɐݒ肳�ꂽ
		bVtex = TRUE;
		break;
	
		// ���Ȃ����_�ݒ�
	case KUNCLE	: VtexKnuckle();

		// ���_���W����ɐݒ肳�ꂽ
		bVtex = TRUE;
		break;

	default :
		break;
	}

	if( bVtex == FALSE )
	{
		return ;
	}



	// ���_�o�b�t�@�̃��b�N
	g_pD3DVBXYZBuffer[ID]->Lock( 0 , 0 , (void **)&pVtx , 0);

	
	// ���_�o�b�t�@�̍��W�ݒ�
	pVtx[LEFTTOP_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx1 + fPosX  , g_Vtex.fVtexy1 + fPosY, 0.f );	// ����̒��_

	pVtx[RIGHTTOP_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx2  + fPosX , g_Vtex.fVtexy2 + fPosY , 0.f );	// �E��̒��_

	pVtx[LEFTBOTTOM_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx3  + fPosX , g_Vtex.fVtexy3 + fPosY , 0.f );	// �E���̒��_

	pVtx[RIGHTBOTTOM_VTEX].vtx = D3DXVECTOR3( g_Vtex.fVtexx4  + fPosX , g_Vtex.fVtexy4 + fPosY , 0.f );	// �����̒��_
	

	// �e�N�X�`���̍��W�ݒ�
	pVtx[LEFTTOP_VTEX].tex = D3DXVECTOR2(texx0, texy0);							// ����̃e�N�X�`�����_�ݒ�

	pVtx[RIGHTTOP_VTEX].tex = D3DXVECTOR2(texx1, texy0);							// �E��̃e�N�X�`�����_�ݒ�

	pVtx[LEFTBOTTOM_VTEX].tex = D3DXVECTOR2(texx0, texy1);							// �E���̃e�N�X�`�����_�ݒ�

	pVtx[RIGHTBOTTOM_VTEX].tex = D3DXVECTOR2(texx1, texy1);							// �����̃e�N�X�`�����_�ݒ�

	// ���_�o�b�t�@�̃��b�N����
	g_pD3DVBXYZBuffer[ID]->Unlock();


	// ���_�t�H�[�}�b�g��ݒ�
	pD3DDevice->SetFVF( FVF_VERTEX_2D_TEX );	// ���_�t�H�[�}�b�g��2D���W�ƐF�ɐݒ�

	//  ���_�o�b�t�@�̃Z�b�g
	pD3DDevice->SetStreamSource( 0 , g_pD3DVBXYZBuffer[ID] , 0 ,sizeof(VERTEX_2D) );

	// �C���f�b�N�X�o�b�t�@�̃Z�b�g
	pD3DDevice->SetIndices(g_pIndexBuffer[ID]);

	// �e�N�X�`���̃Z�b�g
	pD3DDevice->SetTexture( 0 , *pD3DTex );
	
	// �v���~�e�B�u�\��
	pD3DDevice->DrawIndexedPrimitive
				( D3DPT_TRIANGLESTRIP ,			// �v���~�e�B�u�̎��
				0 ,								// �O�p�`�̐�
				0 ,
				VTEXMAX ,						// ���_�̌�
				0 ,
				2 );
	
}

//=============================================================================
//
// �֐���	: PrimitiveUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���~�e�B�u�̉��
//
//=============================================================================
void PrimitiveUninit( void )
{
	for( int i = 0; i < MAXID; i++ )
	{
		// ���_�o�b�t�@�̉��
		if( g_pD3DVBXYZBuffer[i] != NULL )
		{
			g_pD3DVBXYZBuffer[i]->Release();
			g_pD3DVBXYZBuffer[i] = NULL; 
		}

		// �C���f�b�N�X�o�b�t�@�̉��
		if( g_pIndexBuffer[i] != NULL )
		{
			g_pIndexBuffer[i]->Release();
			g_pIndexBuffer[i] = NULL;
		}
	}
}

//=============================================================================
//
// �֐���	: VTexRatation�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ��钸�_�ݒ�
//
//=============================================================================
void VtexRotation( void )
{
	// �p�x�����߂�
	float AngleOld = AngleMath( g_fWidth , g_fHeight );

	// ���a�����߂�
	float Raidus = RaidusMath();

	// ���SX�����߂鎮
	float CenterX = g_fWidth  * 0.5f ;

	// ���SY�����߂鎮
	float CenterY = g_fHeight * 0.5f ;

	// ���_1��X���W��ݒ�
	g_Vtex.fVtexx1 = CenterX - sinf( AngleOld - g_fAngle ) * Raidus;

	// ���_1��Y���W��ݒ�
	g_Vtex.fVtexy1 = CenterY - cosf( AngleOld - g_fAngle ) * Raidus;

	// ���_2��X���W��ݒ�
	g_Vtex.fVtexx2 = CenterX + sinf( AngleOld + g_fAngle ) * Raidus;

	// ���_2��Y���W��ݒ�
	g_Vtex.fVtexy2 = CenterY - cosf( AngleOld + g_fAngle ) * Raidus;

	// ���_3��X���W��ݒ�
	g_Vtex.fVtexx3 = CenterX - sinf( AngleOld + g_fAngle ) * Raidus;

	// ���_3��Y���W��ݒ�
	g_Vtex.fVtexy3 = CenterY + cosf( AngleOld + g_fAngle ) * Raidus;

	// ���_4��X���W��ݒ�
	g_Vtex.fVtexx4 = CenterX + sinf( AngleOld - g_fAngle ) * Raidus;

	// ���_4��Y���W��ݒ�
	g_Vtex.fVtexy4 = CenterY + cosf( AngleOld - g_fAngle ) * Raidus;
}

//=============================================================================
//
// �֐���	: VTexKnuckle�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ����Ȃ����_�ݒ�
//
//=============================================================================
void VtexKnuckle( void )
{
	g_Vtex.fVtexx1 = g_fPosX;
	g_Vtex.fVtexy1 = g_fPosY;
	g_Vtex.fVtexx2 = g_fWidth;
	g_Vtex.fVtexy2 = g_fPosY;
	g_Vtex.fVtexx3 = g_fPosX;
	g_Vtex.fVtexy3 = g_fHeight;
	g_Vtex.fVtexx4 = g_fWidth;
	g_Vtex.fVtexy4 = g_fHeight;
}