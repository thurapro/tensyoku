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
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CScene3D :public CScene 
{
public: 
	CScene3D(int nPriority = 2, OBJTYPE objType = OBJTYPE_3D);							// 3D�I�u�W�F�N�g�C���X�^���X����
	~CScene3D(void);																	// 3D�I�u�W�F�N�g�C���X�^���X�j��
	static CScene3D *Create(float fPosX, float fPosY, float fPosZ, 
							float fWidth, float fHeight, float fLength,
							unsigned int nTexNum);										// 3D�I�u�W�F�N�g�̍쐬
	HRESULT	Init(void);																	// 3D�I�u�W�F�N�g������
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				float fWidth, float fHeight, float fLength,
				unsigned int nTexNum);													// 3D�I�u�W�F�N�g������
	void	Uninit(void);																// 3D�I�u�W�F�N�g�j��
	void	Update(void);																// 3D�I�u�W�F�N�g�̍X�V
	void	Draw(void);																	// 3D�I�u�W�F�N�g�̕`��

	void	SetPosition(float fPosX, float fPosY, float fPosZ);							// �ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);												// �ʒu�ݒ�
	void	SetRotiton(float fRotX, float fRotY, float fRotZ);							// �����ݒ�
	void	SetRotiton(D3DXVECTOR3 rot);												// �����ݒ�
	void	SetScale(float fSclX, float fSclY, float fSclZ);							// �傫���ݒ�
	void	SetScale(D3DXVECTOR3 scl);													// �傫���ݒ�

	D3DXVECTOR3 GetPotition(void){return m_pos;}										// �ʒu�擾
	D3DXVECTOR3 GetRotition(void){return m_rot;}										// �����擾
	D3DXVECTOR3 GetScale(void){return m_scl;}											// �傫���擾
	unsigned int GetTexNum(void){return m_nTexNum;}										// �e�N�X�`���̔ԍ��擾

protected:
	// ���_�쐬�֐�
	HRESULT MakeVerTex(float fPosX, float fPosY, float fPosZ, 
						float fWidth, float fHeight, float fLength);	

	// 3D�|���S���ɕK�v�ȗv�f
	typedef struct
	{
		D3DXVECTOR3 vtx;						// ���_
		D3DXVECTOR3 nor;						// �x�N�g���̌���(�����\)����
		D3DCOLOR	diffuse;					// ���_�F��ݒ�
		D3DXVECTOR2	tex;						// �e�N�X�`�����_
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��

	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// 3D�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_rot;							// 3D�I�u�W�F�N�g�̌���
	D3DXVECTOR3 m_scl;							// 3D�I�u�W�F�N�g�̑傫��

	unsigned int m_nTexNum;						// �e�N�X�`���ԍ��擾

};

#endif //_SCENE3D_H_