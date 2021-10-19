//=============================================================================
// ���� [meshfield.h]
//
// �����	: ���� �Y��
//
// �@�\		: ���V���̑����n�ʐ���
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================

// �O���Q��
#include "sceneline.h"

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	float			fWidth;		// �|���S���̕�
	float			fLength;	// �|���S���̉��s
	int				nNumX;		// �|���S����(��)
	int				nNumZ;		// �|���S����(�c)
	float			*fY;		// ����
	int				nVerMax;	// ���_��
	USHORT			nTexNum;	// �摜�ԍ�
	D3DXVECTOR3		pos;		// �n�ʂ̈ʒu
	D3DXVECTOR3		rot;		// �n�ʂ̌���
	D3DXVECTOR3		scl;		// �n�ʂ̑傫��
}FIELD;

//=============================================================================
// �N���X�錾
//=============================================================================
class CField : public CScene
{
public: 
	CField(int nPriority = 4, OBJTYPE objType = OBJTYPE_FIELD);						// �n�ʃC���X�^���X����
	~CField(void);																	// �n�ʃC���X�^���X�j��
	static CField *Create(float fPolygonWidth, float fPolygonHeight, 
							int nNumX, int nNumZ,	USHORT nTexNum);				// �n�ʂ̍쐬
	static CField *CreateLoad(FIELD dataField, USHORT nTexNum);						// �n�ʐ����Ɠǂݍ���
	HRESULT	Init(void){ return S_OK; }												// �n�ʏ�����
	HRESULT Init(float fPolygonWidth, float fPolygonHeight, 
				int nNumX, int nNumZ,	USHORT nTexNum);							// ����������(�ʏ�)

	void	Uninit(void);															// �n�ʔj��
	void	Update(void);															// �n�ʂ̍X�V
	void	Draw(void);																// �n�ʂ̕`��

	void	SetPosition(float fPosX, float fPosY, float fPosZ);						// �n�ʂ̈ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);											// �n�ʂ̈ʒu�ݒ�
	void	SetRotition(float fRotX, float fRotY, float fRotZ);						// �n�ʂ̌����ݒ�
	void	SetRotition(D3DXVECTOR3 rot);											// �n�ʂ̌����ݒ�
	void	SetHeight(float *fY);													// �n�ʂ̍����ݒ�
	void	SetTexNum(USHORT nTexNum);

	D3DXVECTOR3 GetPosition(void){ return m_pos; }									// �n�ʂ̈ʒu�擾
	D3DXVECTOR3 GetRotition(void){ return m_rot; }									// �n�ʂ̌����擾
	D3DXVECTOR3 *GetVector(void){ return &m_pNor[0]; }								// �n�ʂ̖@���x�N�g���擾
	float		GetHeight(D3DXVECTOR3 pos);											// �n�ʂ̍����擾
	FIELD		GetData(void){ return m_DataField; }								// �n�ʃf�[�^�擾
	float		*GetFieldHeight(void){ return &m_DataField.fY[0]; }					// �n�ʂ̍�����ۑ�
	LPDIRECT3DVERTEXBUFFER9	 GetVertex(void){ return m_pVertexBuffer;}				// ���_�o�b�t�@�擾

private:
	bool	LoadData(FIELD dataField);												// �n�ʂ̃}�b�v�ǂݍ���
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight);					// ���_�쐬�֐�	
	void	GetNormalVec(void);														// �@���Z�o

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// �Y���o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��
	D3DXVECTOR3				*m_pNor;			// �@���x�N�g���i�[
	CSceneLine				**m_ppLine;			// �@�����C��
	int						m_nVerTexMax;		// ���_�ő��
	int						m_nIndexMax;		// �Y���ő��
	USHORT					m_nTexNum;			// �e�N�X�`���ԍ��ۑ�
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;				// �n�ʂ̈ʒu
	D3DXVECTOR3				m_rot;				// �n�ʂ̌���
	D3DXVECTOR3				m_scl;				// �n�ʂ̑傫��
	FIELD					m_DataField;		// �n�ʃf�[�^
	int						m_nPoint;			// �ݒ肷�钸�_�̓Y��
	int						m_nSpeed;			// �n�ʂ������鑬�x
};	// class End

#endif //_MESHFIELD_H_