//=============================================================================
//
// FAILE NAME	[Clear.h]
//
// ���O		:	���� �Y��
//
// �N���X	:	AT12C283
//
// �@�\		:	�Q�[���N���A�p�}�N��
//				�\����
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _CLEAR_H_
#define _CLEAR_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define CLEARNUM		( 11 )					// �e�N�X�`���ԍ�
#define CLEARSOUND		( 6 )					// �T�E���h�ԍ�
#define CLEARTEXX0		( 0.f )					// �e�N�X�`�����WX( ���߂̍��W ) 
#define CLEARTEXX1		( 1.f )					// �e�N�X�`�����WX( �I���̍��W )
#define CLEARTEXY0		( 0.f )					// �e�N�X�`�����WY( ���߂̍��W )
#define CLEARTEXY1		( 1.f )					// �e�N�X�`�����WY( �I���̍��W )
#define CLEARTEXXMAX	( 1.f )					// �e�N�X�`�����WX�̍ő�l
#define CLEARTEXYMAX	( 1.f )					// �e�N�X�`�����WY�̍ő�l

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	float fClearPosX;
	float fClearPosY;
	float fClearWidth;
	float fClearHeight;
	float fClearCLEARTEXX0;
	float fClearCLEARTEXY0;
	float fClearCLEARTEXX1;
	float fClearCLEARTEXY1;
}DRAWCLEAR;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

void ClearInit( void );
void ClearUpdate( void );
void ClearDraw( void );
void ClearUninit( void );

#endif	// _ClearE_H_
