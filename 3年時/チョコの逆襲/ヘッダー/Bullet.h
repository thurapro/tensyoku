//=============================================================================
//
// �e�̏��� [Bullet.h]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "Sound.h"
#include "common.h"
#include "Camera.h"
#include "InputKey.h"
#include "Shadow.h"
#include "Field.h"
#include "Explosion.h"
#include "Effect.h"
#include "meshwall.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define BULLET_TYPE	(1)							// �^�C�v
#define BULLET_NUM	(i)						// �e�̔ԍ�
#define BULLET_MAX (40)							// �e�̐�

//=============================================================================
// �e�̍\����
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;						// ���[���h
	D3DXVECTOR3 posBullet;						// �e�̈ʒu
	D3DXVECTOR3 rotBullet;						// �e�̌���
	D3DXVECTOR3 sclBullet;						// �e�̑傫��
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	// XYZ�̒��_�o�b
	LPDIRECT3DTEXTURE9 pD3DTex;					// �e�N�X�`��
	LPDIRECTSOUNDBUFFER soundBullet;			// �T�E���h
	int nVertexMax;								// ���_�o�b�t�@��
	bool visible;								// �\�����邩���Ȃ���
	float frotMove;								// �i�ޕ���
	float fMoveX;
	float fMoveZ;
	D3DXVECTOR3 MemoryPos;						// �O�ɂ������ꏊ
	float fWidth;
	float fHeight;
	int nType;
}BULLET;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT BulletInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight);		// �e�̏�����
void BulletUninit(void);											// �e�j��
void BulletUpdate(void);											// �e�̍X�V
void BulletDraw(LPDIRECT3DDEVICE9 pD3DDevice);						// �e�X�V
void BulletSet(D3DXVECTOR3 position , float rot , int nType);					// �e�̃Z�b�g
BULLET *BulletPosGet(void);											// �e�̈ʒu�擾

#endif	// _BULLET_H_
