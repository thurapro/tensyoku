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
static Title g_Title;								// �^�C�g���ϐ�
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// ���_�o�b�t�@�[
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// �^�C�g���摜
static int g_nAnimeCnt = 0;
static LPDIRECTSOUNDBUFFER g_soundTitle;

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
static HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);	// ���_�o�b�t�@�[�쐬


//=============================================================================
// �^�C�g��������
//=============================================================================
HRESULT InitTitle(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	g_Title.fPosX = 0.0f;						// �摜��X���ʒu
	g_Title.fPosY = 0.0f;						// �摜��Y���ʒu
	g_Title.fWidth = (float)SCREEN_WIDTH;		// �摜�̕��ݒ�
	g_Title.fHeight = (float)SCREEN_HEIGHT;		// �摜�̍����ݒ�
	g_Title.fTexX0 = 0.0f;						// �摜���_
	g_Title.fTexY0 = 0.0f;						// �摜���_
	g_Title.fTexX1 = TEX_INIT_X;						// �摜���_
	g_Title.fTexY1 = 1.0f;						// �摜���_
	g_Title.fMoveX = TEX_SPEED_X;						// �摜�̓������x
	g_Title.fMoveY = 0.0f;						// �摜�̓������x
	g_nAnimeCnt = 0;
	SoundFileLoad( "DATA/Sound/Title.wav" , TITLE_SOUND );
	CreateSoundBuffer(&g_soundTitle, TITLE_SOUND);

	//------------------------
	// �e�N�X�`���[�̃��[�h
	hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Title.png" , &g_pD3DTex);
	
	//---------------------------------------
	// �e�N�X�`���[�����[�h�ł��Ȃ������ꍇ
	if( FAILED(hr) )
	{
		return hr;
	}

	//----------------------------------------
	// ���_�쐬
	hr = MakeVertexTitle(pDevice);

	//----------------------------------------
	// ���_�o�b�t�@�[���쐬�ł��Ȃ�������
	if( FAILED(hr) )
	{
		return hr;
	}

	g_soundTitle->Play(0,0,0);

	return hr;
}

//=============================================================================
// �^�C�g���j��
//=============================================================================
void UninitTitle(void)
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
	if(g_soundTitle != NULL)
	{
		g_soundTitle->Release();
		g_soundTitle = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V
//=============================================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	// �X�V
	if( KeyPush(DIK_RETURN) )
	{
		GameSelectSet(GAME);
	}
	else
	{
		if( g_nAnimeCnt > ANIMECNT_MAX )
		{
			if( g_Title.fTexX1 < TEX_MAX )
			{
				g_Title.fTexX0 += g_Title.fMoveX;
				g_Title.fTexX1 += g_Title.fMoveX;
			}
			else
			{
				g_Title.fTexX0 += g_Title.fMoveX;
				g_Title.fTexX1 += g_Title.fMoveX;
			}
			g_nAnimeCnt = 0;
		}
		else
		{
			g_nAnimeCnt++;
		}
		g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY0);
		pVtx[1].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY0);
		pVtx[2].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY1);
		pVtx[3].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY1);
		g_pD3DVBXYZBuffer->Unlock();
	}

}

//=============================================================================
// �^�C�g���`��
//=============================================================================
void DrawTitle(LPDIRECT3DDEVICE9 pDevice)
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
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
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
	pVtx[0].vtx = D3DXVECTOR3(g_Title.fPosX, g_Title.fPosY, 0);
	pVtx[1].vtx = D3DXVECTOR3(g_Title.fWidth, g_Title.fPosY, 0);
	pVtx[2].vtx = D3DXVECTOR3(g_Title.fPosX,g_Title.fHeight, 0);
	pVtx[3].vtx = D3DXVECTOR3(g_Title.fWidth, g_Title.fHeight, 0);
	
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
	pVtx[0].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY0);
	pVtx[1].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY0);
	pVtx[2].tex = D3DXVECTOR2(g_Title.fTexX0, g_Title.fTexY1);
	pVtx[3].tex = D3DXVECTOR2(g_Title.fTexX1, g_Title.fTexY1);

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






