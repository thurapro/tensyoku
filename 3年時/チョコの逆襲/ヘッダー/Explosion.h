//=============================================================================
//
// �����̏��� [Explosion.h]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Camera.h"
#include "InputKey.h"
#include "clear.h"
#include "Sound.h"

//=============================================================================
// �����̍\����
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ���[���h
	D3DXVECTOR3 posExplosion;					// �����̈ʒu
	D3DXVECTOR3 rotExplosion;					// �����̌���
	D3DXVECTOR3 sclExplosion;					// �����̑傫��
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZ�̒��_�o�b
	LPDIRECT3DTEXTURE9 pD3DTex;					// �e�N�X�`��
	int nVertexMax;								// ���_�o�b�t�@��
	bool visible;								// �\�����邩���Ȃ���
	float fAnimesionLeft;						// �����A�j���[�V���������W�
	float fAnimesionRight;						// �����A�j���[�V�����E���W�
	LPDIRECTSOUNDBUFFER soundExplosion;
}EXPLOSION;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT ExplosionInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// �����̏�����
void ExplosionUninit(void);											// �����j��
void ExplosionUpdate(void);											// �����̍X�V
void ExplosionDraw(LPDIRECT3DDEVICE9 pD3DDevice);					// �����X�V
void ExplosionSet(D3DXVECTOR3 position);							// �����̃Z�b�g

#endif	// _EXPLOSION_H_
