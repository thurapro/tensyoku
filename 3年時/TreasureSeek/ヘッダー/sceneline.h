//=============================================================================
// ���b�V��3D�I�u�W�F�N�g���� [cylinder.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: ���b�V���̑���3D�I�u�W�F�N�g���쐬
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _SCENELINE_H_
#define _SCENELINE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CSceneLine :public CScene 
{
public: 
	CSceneLine(int nPriority = 3);		// 3D�I�u�W�F�N�g�C���X�^���X����
	~CSceneLine(void);					// 3D�I�u�W�F�N�g�C���X�^���X�j��
	HRESULT	Init(void);					// 3D�I�u�W�F�N�g������
	HRESULT Init(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);
	void	Uninit(void);				// 3D�I�u�W�F�N�g�j��
	void	Update(void);				// 3D�I�u�W�F�N�g�̍X�V
	void	Draw(void);					// 3D�I�u�W�F�N�g�̕`��
	static CSceneLine *Create(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);		// 3D�I�u�W�F�N�g�̍쐬
private:
	// ���_�쐬�֐�
	HRESULT MakeVerTex(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha);	

	// 3D�|���S���ɕK�v�ȗv�f
	typedef struct
	{
		D3DXVECTOR3 vtx;						// ���_
		D3DXVECTOR3 nor;						// �x�N�g���̌���(�����\)����
		D3DCOLOR	diffuse;					// ���_�F��ݒ�
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@�p�ϐ�

	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// 3D�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_rot;							// 3D�I�u�W�F�N�g�̌���
	D3DXVECTOR3 m_scl;							// 3D�I�u�W�F�N�g�̑傫��
};

#endif //_SCENELINE_H_