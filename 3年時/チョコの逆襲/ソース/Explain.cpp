//=============================================================================
//
// title���� [title.cpp]  �����@�Y��
//
//=============================================================================

//=============================================================================
// �w�b�_�[�ǂݍ���
//=============================================================================
#include "../hedder/title.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�
#define TEX_INIT_X			(0.25f)
#define TEX_MAX				(1.0f)
#define ANIMECNT_MAX		(40)
#define TEX_SPEED_X			(0.25f)
#define TITLE_SOUND			(0)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// ���_�o�b�t�@�[
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// �^�C�g���摜
static int g_nTime = 0;
static int g_faide = 255;
static LPDIRECTSOUNDBUFFER g_soundExplain;

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	D3DVECTOR	vtx;						// ���_���W
	float		rhw;						// �������W�̋t��
	D3DCOLOR	diffuse;					// �F���
	D3DXVECTOR2	tex;						// �e�N�X�`���[���W
}VERTEX_2D;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
static HRESULT MakeVertexExplain(LPDIRECT3DDEVICE9 pDevice);	// ���_�o�b�t�@�[�쐬

//=============================================================================
// �^�C�g��������
//=============================================================================
HRESULT InitExplain(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	g_nTime = 0;
	g_faide = 255;
	//------------------------
	// �e�N�X�`���[�̃��[�h
	hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Player.png" , &g_pD3DTex);
	
	//---------------------------------------
	// �e�N�X�`���[�����[�h�ł��Ȃ������ꍇ
	if( FAILED(hr) )
	{
		return hr;
	}

	//----------------------------------------
	// ���_�쐬
	hr = MakeVertexExplain(pDevice);

	//----------------------------------------
	// ���_�o�b�t�@�[���쐬�ł��Ȃ�������
	if( FAILED(hr) )
	{
		return hr;
	}

	return hr;
}

//=============================================================================
// �^�C�g���j��
//=============================================================================
void UninitExplain(void)
{
	if(g_pD3DVBXYZBuffer != NULL)
	{
		g_pD3DVBXYZBuffer->Release();
		g_pD3DVBXYZBuffer = NULL;
	}
	if(g_pD3DTex != NULL)
	{
		g_pD3DTex->Release();
		g_pD3DTex = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V
//=============================================================================
void UpdateExplain(void)
{
	VERTEX_2D *pVtx;

	if(g_faide > 0)
	{
		g_faide -= 1;
	}
	else
	{
		GameSelectSet(GAME);
	}
	g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[1].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[2].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	pVtx[3].diffuse = D3DCOLOR_RGBA(g_faide, g_faide, g_faide, g_faide);
	g_pD3DVBXYZBuffer->Unlock();
}

//=============================================================================
// �^�C�g���`��
//=============================================================================
void DrawExplain(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�t�H�[�}�b�g���Z�b�g
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// ���_�o�b�t�@�[�̃Z�b�g
	pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	
	// �e�N�X�`���[�Z�b�g
	pDevice->SetTexture(0, g_pD3DTex);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);

	// �v���~�e�B�u
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �^�C�g���̒��_�o�b�t�@�[�쐬
//=============================================================================
HRESULT MakeVertexExplain(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�[�쐬
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&g_pD3DVBXYZBuffer,
									NULL);
	//-----------------------
	// �쐬�ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}

	// ���_�o�b�t�@�[���b�N
	hr = g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);

	//-----------------------
	// ���b�N�ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}

	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx = D3DXVECTOR3(0, 0, 0);
	pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
	pVtx[2].vtx = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
	pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F���
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���[���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���b�N����
	hr = g_pD3DVBXYZBuffer->Unlock();

	//-----------------------
	// ���b�N�����ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}
	return hr;
}	






