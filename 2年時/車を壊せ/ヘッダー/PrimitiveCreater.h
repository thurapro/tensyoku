#ifndef	_PRIMITIVE_H_
#define _PRIMITIVE_H_

//===========================================================================
// �C���N���[�h
//===========================================================================
#include <d3dx9.h>
#include <windows.h>

//============================================================================
// �}�N����`
//============================================================================		
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define ROTATION			( 1 )				// ��]���_
#define KUNCLE				( 2 )				// ����]���_
#define BUFFERMAX			( 20 )				// �o�b�t�@�̍ő吔
#define VTEXMAX				( 4 )				// ���_�̍ő吔
#define RED_MAX				( 255 )				// �ԐF�̍ő�F
#define GREEN_MAX			( 255 )				// �ΐF�̍ő�F
#define BLUE_MAX			( 255 )				// �F�̍ő�F
#define ALPHA_MAX			( 255 )				// �����x�̍ő�
#define LEFTTOP_VTEX		( 0 )				// ���_���W����
#define RIGHTTOP_VTEX		( 1 )				// ���_���W�E��
#define LEFTBOTTOM_VTEX		( 2 )				// ���_���W����
#define RIGHTBOTTOM_VTEX	( 3 )				// ���_���W�E��

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DVECTOR	vtx;							// ���_���W(x,y,z)
	float		rhw;							// reciprocal homogeneous w(�������W��w�v�f�̋t��)
	D3DCOLOR	diffuse;						// �F�̏��
	D3DXVECTOR2	tex	;							// �摜���\��
}VERTEX_2D;

typedef struct
{
	float fVtexx1;								// �e�N�X�`�����_1
	float fVtexy1;								// �e�N�X�`�����_1
	float fVtexx2;								
	float fVtexy2;
	float fVtexx3;
	float fVtexy3;
	float fVtexx4;
	float fVtexy4;
}VTEX;


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
BOOL PrimitiveInit( void );						// �v���~�e�B�u�̏�����

void PrimitiveCreate(	int ID			,		// �ǂ̃v���~�e�B�u����邩
						int VtxType		,		// �v���~�e�B�u����]���邩(1),���Ȃ���(2)
						int TextureNum	,		// �e�N�X�`���̔ԍ�
						float fAngle	,		// �e�N�X�`���̊p�x�����Ȃ��ꍇ�͂O
						float fPosX		,		// ���_1�̐ݒ�
						float fPosY		,		// ���_1�̐ݒ�
						float ffWidth	,		// ���_2�̐ݒ�
						float ffHeight	,		// ���_2�̐ݒ�
						float texx0		,		// �e�N�X�`���n�_���W
						float texy0		,		// �e�N�X�`���n�_���W
						float texx1		,		// �e�N�X�`���I�_���W
						float texy1		);		// �e�N�X�`���I�_���W

void PrimitiveUninit( void );					// �v���~�e�B�u�̉��

void VtexRotation( void );						// ��钸�_

void VtexKnuckle( void );						// ���Ȃ����_

#endif // _PRIMITIVE_H_


