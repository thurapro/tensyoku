//=============================================================================
// ���b�V���̑����R���� [ mountain.h ]
//
// �����	: ���� �Y��
//
// �@�\		: �R���쐬
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _MONTAIN_H_
#define _MONTAIN_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"		// �N���XCScene

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	float			fWidth;		// �|���S���̕�
	float			fHeight;	// �|���S���̍���
	int				nNumX;		// �u���b�N�̐� X
	int				nNumY;		// �u���b�N�̐�	Y				
	float			fR;			// ���a
	D3DXVECTOR3		pos;		// �R�̈ʒu
	D3DXVECTOR3		rot;		// �R�̌���
	D3DXVECTOR3		scl;		// �R�̑傫��
}MOUNTAIN;

//=============================================================================
// �N���X�錾
//=============================================================================
class CMountain : public CScene
{
public:	// ����
	CMountain(int nPriority = 3, OBJTYPE objType = OBJTYPE_MOUNTAIN);	// �C���X�^���X����
	~CMountain(void);													// �C���X�^���X�j��
	static CMountain* Create(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum);							// �R�̐���
	static CMountain* CreateLoad( MOUNTAIN dataMountain, USHORT nTexNum);
	
	HRESULT Init(void){ return S_OK; }									// �R�̏�����
	HRESULT Init(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum);							// �R�̏�����
	void	Uninit(void);												// �R�̔j��
	void	Update(void);												// �R�̍X�V
	void	Draw(void);													// �R�̕`��

	void	SetTextureNum(USHORT nTexNum);								// �摜�ԍ��ݒ�
	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// �R�̈ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);								// �R�̈ʒu�ݒ�
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// �R�̌����ݒ�
	void	SetRotition(D3DXVECTOR3 rot);								// �R�̌����ݒ�

	D3DXVECTOR3	GetPosition(void){ return m_DataMountain.pos; }			// �R�̈ʒu�擾
	D3DXVECTOR3	GerRotition(void){ return m_DataMountain.rot; }			// �R�̊p�x�擾
	MOUNTAIN	GetData(void){ return m_DataMountain; }					// �R�f�[�^���擾 


private: // �v�f
	void LoadData(MOUNTAIN dataMountain);										// �R�f�[�^����&�ǂݍ���
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight, float fR);	// ���_�쐬

	// 3D�|���S���ɕK�v�ȗv�f
	typedef struct
	{
		D3DXVECTOR3 vtx;								// ���_
		D3DXVECTOR3 nor;								// �x�N�g���̌���(�����\)����
		D3DCOLOR	diffuse;							// ���_�F��ݒ�
		D3DXVECTOR2	tex;								// �e�N�X�`�����_
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;			// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;				// �Y���o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`��
	int						m_nVerTexMax;				// ���_�ő��
	int						m_nIndexMax;				// �Y���ő��
	USHORT					m_nTexNum;					// �e�N�X�`���ԍ��ۑ�
	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;						// �R�̈ʒu
	D3DXVECTOR3				m_rot;						// �R�̌���
	D3DXVECTOR3				m_scl;						// �R�̑傫��
	MOUNTAIN				m_DataMountain;				// �R�f�[�^
}; // class End  


#endif // _MOUNTAIN_H_