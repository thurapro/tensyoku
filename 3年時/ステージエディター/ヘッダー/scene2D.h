//============================================================================= 
// 2D�I�u�W�F�N�g���� [ scene2D.h ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: 2D�I�u�W�F�N�g�쐬����
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�

//=============================================================================
// �N���X�錾
//=============================================================================
class CScene2D : public CScene		// CScene�̔h��
{
public:		// ����
	CScene2D(int nPriority = 5, OBJTYPE objType = OBJTYPE_2D);		// �C���X�^���X����
	~CScene2D(void);												// �C���X�^���X�j��
	static CScene2D *Create(float fPosX, float fPosY, 
							float fWidth, float fHeight,
							unsigned short nTextureNumber);			// 2D�I�u�W�F�N�g�쐬
	HRESULT	Init(void);												// 2D�I�u�W�F�N�g����������
	HRESULT Init(float fPosX, float fPosY, 
				 float fWidth, float fHeight,
				 unsigned short nTextureNumber);					// 2D�I�u�W�F�N�g����������
	void	Uninit(void);											// 2D�I�u�W�F�N�g�I������
	void	Update(void);											// 2D�I�u�W�F�N�g�X�V����
	void	Draw(void);												// 2D�I�u�W�F�N�g�`�揈��

	void	SetPosition(float fPosX, float fPosY,
							float fWidth, float fHeigh);			// �ʒu�ݒ�
	void	SetColor(int nR, int nG, int nB, int nA);				// �F�ݒ�
	void	SetTexure(float fTexX, float fTexY,						// �e�N�X�`�����W�ݒ�
						float fTexWidth, float fTexHeight );
	void	SetTexNum(unsigned short nTexNum);						// �e�N�X�`���ԍ��ݒ�

	D3DXVECTOR2	GetPosition(void){return m_pos;}					// �ʒu�擾

protected:	// �v�f
	HRESULT MakeVertex( float fPosX, float fPosY, 
						float fWidth, float fHeight);				// ���_�쐬


	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@
	unsigned short			m_nTextureNum;		// �e�N�X�`���ԍ�
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��
	D3DXVECTOR2				m_pos;				// �ʒu
};
	


#endif // _SCENE2D_H_