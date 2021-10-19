//=============================================================================
//
// title���� [title.cpp]  �����@�Y��
//
//=============================================================================

//=============================================================================
// �w�b�_�[�ǂݍ���
//=============================================================================
#include "../hedder/Lank.h"

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
static Lank g_Lank;								// �^�C�g���ϐ�
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer;	// ���_�o�b�t�@�[
static LPDIRECT3DTEXTURE9 g_pD3DTex;				// �^�C�g���摜
static int g_nAnimeCnt = 0;
static LPDIRECTSOUNDBUFFER g_soundLank;
static int g_nGameTimer;
static int g_nLank[3];
static bool g_bLank = false;

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
static HRESULT MakeVertexLank(LPDIRECT3DDEVICE9 pDevice);	// ���_�o�b�t�@�[�쐬

//=============================================================================
// �^�C�g��������
//=============================================================================
HRESULT InitLank(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	//g_Lank.fPosX = 0.0f;						// �摜��X���ʒu
	//g_Lank.fPosY = 0.0f;						// �摜��Y���ʒu
	//g_Lank.fWidth = (float)SCREEN_WIDTH;		// �摜�̕��ݒ�
	//g_Lank.fHeight = (float)SCREEN_HEIGHT;		// �摜�̍����ݒ�
	//g_Lank.fTexX0 = 0.0f;						// �摜���_
	//g_Lank.fTexY0 = 0.0f;						// �摜���_
	//g_Lank.fTexX1 = TEX_INIT_X;						// �摜���_
	//g_Lank.fTexY1 = 1.0f;						// �摜���_
	//g_Lank.fMoveX = TEX_SPEED_X;						// �摜�̓������x
	//g_Lank.fMoveY = 0.0f;						// �摜�̓������x
	//g_nAnimeCnt = 0;
	//SoundFileLoad( "DATA/Sound/Clear.wav" , LANK );
	//CreateSoundBuffer(&g_soundLank, LANK);

	//if( g_bLank == false )
	//{
	//	for( int i = 0; i < 3; i++)
	//	{
	//		g_nLank[i] = 0;
	//	}
	//	g_bLank = true;
	//}
	////------------------------
	//// �e�N�X�`���[�̃��[�h
	//hr = D3DXCreateTextureFromFile(pDevice, "DATA/Texture/Lank.png" , &g_pD3DTex);
	//
	////---------------------------------------
	//// �e�N�X�`���[�����[�h�ł��Ȃ������ꍇ
	//if( FAILED(hr) )
	//{
	//	return hr;
	//}

	////----------------------------------------
	//// ���_�쐬
	//hr = MakeVertexLank(pDevice);

	////----------------------------------------
	//// ���_�o�b�t�@�[���쐬�ł��Ȃ�������
	//if( FAILED(hr) )
	//{
	//	return hr;
	//}

	return hr;
}

//=============================================================================
// �^�C�g���j��
//=============================================================================
void UninitLank(void)
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
	if(g_soundLank != NULL)
	{
		g_soundLank->Release();
		g_soundLank = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V
//=============================================================================
void UpdateLank(void)
{
	//VERTEX_2D *pVtx;
	//// �X�V
	//if( KeyPush(DIK_RETURN) )
	//{
	//	GameSelectSet(TITLE);
	//}
	//else
	//{
	//	if( g_nAnimeCnt > ANIMECNT_MAX )
	//	{
	//		if( g_Lank.fTexX1 < TEX_MAX )
	//		{
	//			g_Lank.fTexX0 += g_Lank.fMoveX;
	//			g_Lank.fTexX1 += g_Lank.fMoveX;
	//		}
	//		else
	//		{
	//			g_Lank.fTexX0 += g_Lank.fMoveX;
	//			g_Lank.fTexX1 += g_Lank.fMoveX;
	//		}
	//		g_nAnimeCnt = 0;
	//	}
	//	else
	//	{
	//		g_nAnimeCnt++;
	//	}
	//	g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);
	//	pVtx[0].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY0);
	//	pVtx[1].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY0);
	//	pVtx[2].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY1);
	//	pVtx[3].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY1);
	//	g_pD3DVBXYZBuffer->Unlock();
	//}
	//g_soundLank->Play(0,0,0);
}

//=============================================================================
// �^�C�g���`��
//=============================================================================
void DrawLank(LPDIRECT3DDEVICE9 pDevice)
{
	//char strKing[1024] = "1�� : ";
	//char strSecond[1024] = "2�� : ";
	//char strTherd[1024] = "3�� : ";

	//char strChangeKing[40] = {NULL};
	//char strChangeSecond[50] = {NULL};
	//char strChangeTherd[50] = {NULL};

	//g_nGameTimer = GameTimerGet();

	//for( int i = 0; i < 3; i++ )
	//{
	//	g_nLank[i] = g_nGameTimer;
	//	break;
	//}
	//// ���_�t�H�[�}�b�g���Z�b�g
	//pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	//
	//// ���_�o�b�t�@�[�̃Z�b�g
	//pDevice->SetStreamSource(0, g_pD3DVBXYZBuffer, 0, sizeof(VERTEX_2D));
	//
	//// �e�N�X�`���[�Z�b�g
	//pDevice->SetTexture(0, g_pD3DTex);

	//// �v���~�e�B�u
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//itoa(g_nLank[0], strChangeKing, 10);
	//itoa(g_nLank[1], strChangeSecond, 10);
	//itoa(g_nLank[2], strChangeTherd, 10);

	//strcat(strKing, strChangeKing);
	//strcat(strSecond, strChangeSecond);
	//strcat(strTherd, strChangeTherd);

	//strcat(strKing, "�b");
	//strcat(strSecond, "�b");
	//strcat(strTherd, "�b");

	//FontDraw(250, 40, SCREEN_WIDTH, SCREEN_HEIGHT, strKing);
	//FontDraw(250, 100, SCREEN_WIDTH, SCREEN_HEIGHT, strSecond);
	//FontDraw(250, 160, SCREEN_WIDTH, SCREEN_HEIGHT, strTherd);
}

//=============================================================================
// �^�C�g���̒��_�o�b�t�@�[�쐬
//=============================================================================
HRESULT MakeVertexLank(LPDIRECT3DDEVICE9 pDevice)
{
	//HRESULT hr;
	//VERTEX_2D *pVtx;

	//// ���_�o�b�t�@�[�쐬
	//hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
	//								D3DUSAGE_WRITEONLY,
	//								FVF_VERTEX_2D_TEX,
	//								D3DPOOL_MANAGED,
	//								&g_pD3DVBXYZBuffer,
	//								NULL);
	////-----------------------
	//// �쐬�ł��Ȃ�������
	//if(FAILED(hr))
	//{
	//	return hr;
	//}

	//// ���_�o�b�t�@�[���b�N
	//hr = g_pD3DVBXYZBuffer->Lock(0, 0, (void **)&pVtx, 0);

	////-----------------------
	//// ���b�N�ł��Ȃ�������
	//if(FAILED(hr))
	//{
	//	return hr;
	//}

	//// ���_�o�b�t�@�[�ʒu�Z�b�g
	//pVtx[0].vtx = D3DXVECTOR3(g_Lank.fPosX, g_Lank.fPosY, 0);
	//pVtx[1].vtx = D3DXVECTOR3(g_Lank.fWidth, g_Lank.fPosY, 0);
	//pVtx[2].vtx = D3DXVECTOR3(g_Lank.fPosX,g_Lank.fHeight, 0);
	//pVtx[3].vtx = D3DXVECTOR3(g_Lank.fWidth, g_Lank.fHeight, 0);
	//
	//// rhw�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// �F���
	//pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// �e�N�X�`���[���W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY0);
	//pVtx[1].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY0);
	//pVtx[2].tex = D3DXVECTOR2(g_Lank.fTexX0, g_Lank.fTexY1);
	//pVtx[3].tex = D3DXVECTOR2(g_Lank.fTexX1, g_Lank.fTexY1);

	//// ���b�N����
	//hr = g_pD3DVBXYZBuffer->Unlock();

	////-----------------------
	//// ���b�N�����ł��Ȃ�������
	//if(FAILED(hr))
	//{
	//	return hr;
	//}
	//return hr;
}	






