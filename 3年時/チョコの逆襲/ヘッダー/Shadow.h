//=============================================================================
//
// �t�B�[���h���� [Field.h]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "InputKey.h"
#include "Field.h"
#include "Player.h"
#include "Bullet.h"

//=============================================================================
// �e�\����
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ���[���h
	D3DXVECTOR3 posShadow;						// �e�̈ʒu
	D3DXVECTOR3 rotShadow;						// �e�̌���
	D3DXVECTOR3 sclShadow;						// �e�̑傫��
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZ�̒��_�o�b�t�@
	LPDIRECT3DTEXTURE9 pD3DTex;					// �e�N�X�`��
	int nType;									// ���̉e�Ȃ̂�
	bool visible;								// �\���ϐ�
	int nNum;
}SHADOW;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT ShadowInit(LPDIRECT3DDEVICE9 pD3DDevice ,float fShadowWidth , float fShadowHeight);	// �e�̏�����
void ShadowUninit(void);										// �e�j��
void ShadowUpdate(D3DXVECTOR3 position , int nNum, int nType);			// �e�̍X�V
void ShadowDraw(LPDIRECT3DDEVICE9 pD3DDevice);					// �e�̕`��
void ShadowSet(D3DXVECTOR3 position , int nType , int nNum);	// �e�̃Z�b�g
void ShadowDelete(int nType , int nNum);						// �e�̍폜

#endif	// _SHADOW_H_
