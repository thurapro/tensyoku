//=============================================================================
//
// �t�B�[���h���� [Billboard.h]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Camera.h"
#include "InputKey.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT BillboardInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nBillboardScl_X , int nBillboardScl_Y);		// �e�̏�����
void BillboardUninit(void);	// �e�j��
void BillboardUpdate(void);	// �e�̍X�V
void BillboardDraw(LPDIRECT3DDEVICE9 pD3DDevice);		// �e�X�V
D3DXVECTOR3 BillboardPosGet(void);


#endif	// _EFFECT_H_
