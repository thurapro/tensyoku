//=============================================================================
//
// title���� [title.cpp]  �����@�Y��
//
//=============================================================================

//=============================================================================
// �w�b�_�[�ǂݍ���
//=============================================================================
#include "../hedder/Over.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�
#define TEX_INIT_X			(1.0f / 5.0f)
#define TEX_MAX				(1.0f)
#define ANIMECNT_MAX		(40)
#define TEX_SPEED_X			(1.0f / 5.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static Over g_Over;									// �^�C�g���ϐ�
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// ���_�o�b�t�@�[
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// �^�C�g���摜
static int g_nAnimeCnt = 0;
static LPDIRECTSOUNDBUFFER g_soundOver;

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
static HRESULT MakeVertexOver(LPDIRECT3DDEVICE9 pDevice);	// ���_�o�b�t�@�[�쐬

//=============================================================================
// �^�C�g��������
//=============================================================================
HRESULT InitOver(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	g_Over.fPosX = 0.0f;						// �摜��X���ʒu
	g_Over.fPosY = 0.0f;						// �摜��Y���ʒu
	g_Over.fWidth = (float)SCREEN_WIDTH;		// �摜�̕��ݒ�
	g_Over.fHeight = (float)SCREEN_HEIGHT;		// �摜�̍����ݒ�
	g_Over.fTexX0 = 0.0f;						// �摜���_
	g_Over.fTexY0 = 0.0f;						// �摜���_
	g_Over.fTexX1 = TEX_INIT_X;					// �摜���_
	g_Over.fTexY1 = 1.0f;						// �摜���_
	g_Over.fMoveX = TEX_SPEED_X;				// �摜�̓������x
	g_Over.fMoveY = 0.0f;						// �摜�̓������x
	g_nAnimeCnt = 0;

	//------------------------
	// �e�N�X�`���[�̃��[�h
	hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Over.png" , &g_pD3DTex);
	
	//---------------------------------------
	// �e�N�X�`���[�����[�h�ł��Ȃ������ꍇ
	if( FAILED(hr) )
	{
		return hr;
	}

	//----------------------------------------
	// ���_�쐬
	hr = MakeVertexOver(pDevice);

	//----------------------------------------
	// ���_�o�b�t�@�[���쐬�ł��Ȃ�������
	if( FAILED(hr) )
	{
		return hr;
	}
	SoundFileLoad("DATA/Sound/Over.wav", 30);
	CreateSoundBuffer(&g_soundOver, 30);
	return hr;
}

//=============================================================================
// �^�C�g���j��
//=============================================================================
void UninitOver(void)
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
	if(g_soundOver != NULL)
	{
		g_soundOver->Release();
		g_soundOver = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V
//=============================================================================
void UpdateOver(void)
{
	VERTEX_2D *pVtx;
	// �X�V
	if( KeyPush(DIK_RETURN) )
	{
		GameSelectSet(TITLE);
	}
	else
	{
		if( g_nAnimeCnt > ANIMECNT_MAX )
		{
			if( g_Over.fTexX1 < TEX_MAX )
			{
				g_Over.fTexX0 += g_Over.fMoveX;
				g_Over.fTexX1 += g_Over.fMoveX;
			}
			else
			{
				g_Over.fTexX0 += g_Over.fMoveX;
				g_Over.fTexX1 += g_Over.fMoveX;
			}
			g_nAnimeCnt = 0;
		}
		else
		{
			g_nAnimeCnt++;
		}
		g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(g_Over.fTexX0, g_Over.fTexY0);
		pVtx[1].tex = D3DXVECTOR2(g_Over.fTexX1, g_Over.fTexY0);
		pVtx[2].tex = D3DXVECTOR2(g_Over.fTexX0, g_Over.fTexY1);
		pVtx[3].tex = D3DXVECTOR2(g_Over.fTexX1, g_Over.fTexY1);
		g_pD3DVBXYZBuffer->Unlock();
	}
	g_soundOver->Play(0,0,0);
}

//=============================================================================
// �^�C�g���`��
//=============================================================================
void DrawOver(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�t�H�[�}�b�g���Z�b�g
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// ���_�o�b�t�@�[�̃Z�b�g
	pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	
	// �e�N�X�`���[�Z�b�g
	pDevice->SetTexture(0, g_pD3DTex);

	// �v���~�e�B�u
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �^�C�g���̒��_�o�b�t�@�[�쐬
//=============================================================================
HRESULT MakeVertexOver(LPDIRECT3DDEVICE9 pDevice)
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
	pVtx[0].vtx = D3DXVECTOR3(g_Over.fPosX, g_Over.fPosY, 0);
	pVtx[1].vtx = D3DXVECTOR3(g_Over.fWidth, g_Over.fPosY, 0);
	pVtx[2].vtx = D3DXVECTOR3(g_Over.fPosX,g_Over.fHeight, 0);
	pVtx[3].vtx = D3DXVECTOR3(g_Over.fWidth, g_Over.fHeight, 0);
	
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
	pVtx[0].tex = D3DXVECTOR2(g_Over.fTexX0, g_Over.fTexY0);
	pVtx[1].tex = D3DXVECTOR2(g_Over.fTexX1, g_Over.fTexY0);
	pVtx[2].tex = D3DXVECTOR2(g_Over.fTexX0, g_Over.fTexY1);
	pVtx[3].tex = D3DXVECTOR2(g_Over.fTexX1, g_Over.fTexY1);

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






