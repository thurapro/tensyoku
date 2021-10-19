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
#include "../hedder/Font.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define FONT_MAX (3)

//==========================================================================
// �O���[�o���ϐ�
//==========================================================================
static LPD3DXFONT g_pD3DFont[FONT_MAX] = {NULL};

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
void FontInit(	LPDIRECT3DDEVICE9 pDevice,
				INT		Height		,		// �t�H���g�̍���
				UINT	Width		,		// �t�H���g�̕�
				UINT	Weight		,		// �t�H���g�̑���
				LPCSTR	pFaceName	,		// �t�H���g���ێ�
				INT		nType		)		// �ǂ��Ŏg����
{
	// �����Ŏ����Ă���Font�̑��
	D3DXCreateFont( pDevice	,		// �f�o�C�X
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
					&g_pD3DFont[nType] );

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
				INT	 A		,		// �����x( 255�͕s���� 0�͓��� )
				INT	 R		,		// �ԐF�̓x����
				INT	 G		,		// �ΐF�̓x����
				INT	 B		,		// �F�̓x����
				CHAR *str	,		// �\��������������
				INT  nType )		// �ǂ��Ŏg����
{
	// �`��͈́@X��( fLeft - fRight ),�@Y��( fBottom - fTop )
	RECT rect = { fLeft , fTop , fRight , fBottom };
	g_pD3DFont[nType]->DrawTextA(	NULL	,
							str		,
							-1		,
							&rect	,
							DT_LEFT	,
							D3DCOLOR_ARGB( R, G, B, A ) );
}


void FontUninit( INT nType )
{
	if( g_pD3DFont[nType] != NULL )
	{
		g_pD3DFont[nType]->Release();
		g_pD3DFont[nType] = NULL;
	}
}

void FontAllUninit(void)
{
	for(int i = 0; i < FONT_MAX; i++)
	{
		if( g_pD3DFont[i] != NULL )
		{
			g_pD3DFont[i]->Release();
			g_pD3DFont[i] = NULL;
		}
	}
}