//=============================================================================
//
// �t�B�[���h���� [Effect.h]
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
#include "WinMain.h"

//=============================================================================
// �G�t�F�N�g�\����
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ���[���h
	D3DXVECTOR3 posEffect;						// �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 rotEffect;						// �G�t�F�N�g�̌���
	D3DXVECTOR3 sclEffect;						// �G�t�F�N�g�̑傫��
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZ�̒��_�o�b�t�@
	LPDIRECT3DTEXTURE9 pD3DTex;					// �e�N�X�`��
	bool visible;								// �\���ϐ�
	int nAlpha;									// �A���t�@�[�l
	int nType;
}EFFECT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT EffectInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// �G�t�F�N�g�̏�����
void EffectUninit(void);																			// �G�t�F�N�g�j��
void EffectUpdate(void);																			// �G�t�F�N�g�̍X�V
void EffectDraw(LPDIRECT3DDEVICE9 pD3DDevice);														// �G�t�F�N�g�X�V
void EffectSet( D3DXVECTOR3 position , int nType );

#endif	// _EFFECT_H_
