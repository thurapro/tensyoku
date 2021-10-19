//============================================================================
//�@�C���N���[�h
//============================================================================
#include <d3dx9.h>
#include <windows.h>
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Direct3DCreater.h"

//============================================================================
//�@�O���[�o���ϐ�
//============================================================================
static LPDIRECT3DTEXTURE9	g_pD3DTex[TEXTUREMAX] = {NULL};
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVBXYZBuffer = NULL;	// XYZ�̒��_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@

//============================================================================
//
// �֐���	:	TextLoad�֐�
//
// �߂�l	:	HRESULT�^�Ń��[�h�����e�L�X�`����Ԃ�
//
// ����		:	�e�L�X�`���̖��O(�`.jpg , �`.png��),�e�L�X�`��������
//
// �@�\		:	�e�L�X�`�������[�h
//			
//============================================================================
HRESULT TextureLoad( char *str, int Numof)
{
	// ���[�J��HRESULT�ϐ�
	HRESULT hr;

	// �������ꂽ�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// �e�N�X�`���̃��[�h
	hr = D3DXCreateTextureFromFile( pD3DDevice , str , &g_pD3DTex[Numof]);

	// �e�N�X�`���̒��g���Ȃ����
	if( FAILED( hr ) )
	{
		// �e�L�X�`�����Ȃ�����
		return (E_FAIL);
	}

	// �e�L�X�`����Ԃ�
	return (S_OK);
}


//=============================================================================
//
// �֐���	:	TextureUnit�֐�
//
// �߂�l	:	�Ȃ�
//
// ����		:	�e�L�X�`���̔ԍ�
//
// �@�\		:	�e�L�X�`���̉��
//			
//=============================================================================
void TextureUninit(int Numof)
{
	// �����e�N�X�`�����������Ă��Ȃ����
	if(g_pD3DTex[Numof] != NULL)
	{
		// �e�N�X�`���̉��
		g_pD3DTex[Numof]->Release();

		// �e�N�X�`���̕�����NULL��
		g_pD3DTex[Numof] = NULL;
	}
}

//==============================================================================
//
// �֐���	: GetD3DTexture�֐�
//
// �߂�l	: �e�N�X�`���̃A�h���X
//
// ����		: �e�N�X�`���̔ԍ�
//
//===============================================================================
LPDIRECT3DTEXTURE9* GetD3DTexture( int Num )
{
	// �e�N�X�`���𑗂�
	return &g_pD3DTex[Num];
}