//=============================================================================
// ���b�V���̑����󏈗� [ sky.h ]
//
// �����	: ���� �Y��
//
// �@�\		: ��쐬
//=============================================================================


//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

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
	D3DXVECTOR3		pos;		// ��̈ʒu
	D3DXVECTOR3		rot;		// ��̌���
	D3DXVECTOR3		scl;		// ��̑傫��
}SKY;

//=============================================================================
// �N���X�錾
//=============================================================================
class CSky : public CScene
{
public:	// ����
	CSky(int nPriority = 2, OBJTYPE objType = OBJTYPE_SKY);				// �C���X�^���X����
	~CSky(void);														// �C���X�^���X�j��
	static CSky* Create(float fPolygonWidth, float fPolygonHeight,		
						int nNumX, int nNumY, float fR, 
						USHORT nTexNum);								// ��̐���
	static CSky* CreateLoad(SKY dataSky, USHORT nTexNum);				// ��̐����A�ǂݍ��� 

	HRESULT Init(void){return S_OK;}									// ��̏�����
	HRESULT Init(float fPolygonWidth, float fPolygonHeight,		
				int nNumX, int nNumY, float fR, 
				USHORT nTexNum);										// ��̏�����
	void	Uninit(void);												// ��̔j��
	void	Update(void);												// ��̍X�V
	void	Draw(void);													// ��̕`��

	void	SetTextureNum(USHORT nTexNum);								// �摜�ԍ��ݒ�
	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// ��̈ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);								// ��̈ʒu�ݒ�
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// ��̌����ݒ�
	void	SetRotition(D3DXVECTOR3 rot);								// ��̌����ݒ�

	D3DXVECTOR3	GetPosition(void){ return m_DataSky.pos; }				// ��̈ʒu�擾
	D3DXVECTOR3	GerRotition(void){ return m_DataSky.rot; }				// ��̊p�x�擾
	SKY			GetData(void){ return m_DataSky; }						// ��f�[�^���擾 

private: // �v�f
	void LoadData(SKY dataSKy);													// ��f�[�^����&�ǂݍ���
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight, float fR);	// ���_�쐬

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;							// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;								// �Y���o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`��
	D3DXVECTOR3				*m_pVtx;									// ���_�ʒu�i�[
	int						m_nVerTexMax;								// ���_�ő��
	int						m_nIndexMax;								// �Y���ő��
	USHORT					m_nTexNum;									// �e�N�X�`���ԍ��ۑ�
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;										// ��̈ʒu
	D3DXVECTOR3				m_rot;										// ��̌���
	D3DXVECTOR3				m_scl;										// ��̑傫��
	SKY						m_DataSky;									// ��̃f�[�^
}; // class End  

#endif // _SKY_H_

// end of file
