//=============================================================================
//
// �t�B�[���h���� [meshwall.h]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include "common.h"
#include "Field.h"
#include "Bullet.h"
#include "WinMain.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define WALL_MAX (4)

//==============================================================================
// �ǂ̍\����
//==============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9 pD3DTexture;
	LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;	
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	int nNumBlockX;
	int nNumBlockY;
	int nNumVertex;
	int nNumIdx;
	int nNumPolygon;
	BOOL bUse;
	float fSizeBlockX;
	float fSizeBlockY;
}MESH_WALL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MeshWallInit(LPDIRECT3DDEVICE9 pD3DDevice , float fPolygonWidth , float fPolygonHeight , int nWallScl_X , int nWallScl_Y);		// �ǂ̏�����
void MeshWallUninit(void);								// �ǔj��
void MeshWallUpdate(void);								// �ǂ̍X�V
void MeshWallDraw(LPDIRECT3DDEVICE9 pD3DDevice);		// �ǍX�V
MESH_WALL *MeshWallGet(void);							// �ǂ̈ʒu�Q�b�g

#endif	// _FIELD_H_