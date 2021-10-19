//=========================================================================
//
// �t�H���g�\�� [font.cpp]
//
//�w�� 10304 �@���� ���� �Y��
//
//==========================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Direct3DCreater.h"
#include "../hedder/Font.h"
#include <d3dx9.h>
#include <windows.h>

//==========================================================================
// �O���[�o���ϐ�
//==========================================================================
static LPD3DXFONT g_pD3DFont = NULL;

//==========================================================================
//
// �֐���	: FontInit
//
// �@�\		: �t�H���g�̏�����(�N���G�C�g)
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
//==========================================================================
void FontInit(	INT		Height		,		// �t�H���g�̍���
				UINT	Width		,		// �t�H���g�̕�
				UINT	Weight		,		// �t�H���g�̑���
				LPCSTR	pFaceName	)		// �t�H���g���ێ�
{

	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// �����Ŏ����Ă���Font�̑��
	D3DXCreateFont( pD3DDevice	,		// �f�o�C�X
					Height		,		// �t�H���g�̍���
					Width		,		// �t�H���g�̕�
					Weight		,		// �t�H���g�̑���
					0			,
					FALSE		,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					pFaceName	,		// �t�H���g���ێ�
					&g_pD3DFont );

}

//==========================================================================
//
// �֐���	: FontDraw
//
// �@�\		: �t�H���g�̕`��
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
//==========================================================================
void FontDraw(	LONG fLeft,			// ��
				LONG fTop,			// ��
				LONG fRight,		// �E
				LONG fBottom,		// ��
				CHAR *str )			// �\��������������
{
	// �`��͈́@X��( fLeft - fRight ),�@Y��( fBottom - fTop )
	RECT rect = { fLeft , fTop , fRight , fBottom };
	g_pD3DFont->DrawTextA(	NULL	,
							str		,
							-1		,
							&rect	,
							DT_LEFT	,
							D3DCOLOR_ARGB( 255, 0, 0, 255 ) );
}


void FontUninit( void )
{
	if( g_pD3DFont != NULL )
	{
		g_pD3DFont->Release();
		g_pD3DFont = NULL;
	}
}