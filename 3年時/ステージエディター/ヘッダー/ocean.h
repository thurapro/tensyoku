//=============================================================================
// ���� [Ocean.h]
//
// �����	: ���� �Y��
//
// �@�\		: ���V���̑����C����
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _OCEAN_H_
#define _OCEAN_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �\���̐ݒ�
//=============================================================================
typedef struct
{
	float			fWidth;			// ��
	float			fLength;		// �傫��
	int				nNumX;			// ���̐�
	int				nNumZ;			// �c�̐�
	int				nSpeed;			// �g�̂��X�s�[�h
	USHORT			nTexNum;		// �摜�ԍ�
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ����
}OCEAN;
	
//=============================================================================
// �N���X�錾
//=============================================================================
class COcean : public CScene
{
public: 
	COcean(int nPriority = 4, OBJTYPE objType = OBJTYPE_OCEAN);						// �C�C���X�^���X����
	~COcean(void);																	// �C�C���X�^���X�j��
	static COcean *Create(float fPolygonWidth, float fPolygonLength, 
							int nNumX, int nNumZ, 
							USHORT nTexNum);										// �C�̍쐬
	static COcean *CreateLoad(OCEAN dataOcean);										// �C�f�[�^�쐬�A�ǂݍ���
	HRESULT	Init(void){return S_OK;}												// �C������
	HRESULT Init(float fPolygonWidth, float fPolygonLength, 
				int nNumX, int nNumZ, 
				USHORT nTexNum);													// ����������
	void	Uninit(void);															// �C�j��
	void	Update(void);															// �C�̍X�V
	void	Draw(void);																// �C�̕`��
	void	SetPosition(float fPosX, float fPosY, float fPosZ);						// �C�̈ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);											// �C�̈ʒu�ݒ�
	void	SetRotition(float fRotX, float fRotY, float fRotZ);						// �C�̌����ݒ�
	void	SetRotition(D3DXVECTOR3 rot);											// �C�̌����ݒ�
	void	SetTexNum(USHORT nTexNum);												// �C�̉摜���ւ�

	D3DXVECTOR3 GetPosition(void){return m_pos;}									// �C�̈ʒu�擾
	D3DXVECTOR3 GetRotition(void){return m_rot;}									// �C�̌����擾
	OCEAN	GetData(void){return m_DataOcean;}										// �C�f�[�^�擾

private:
	HRESULT MakeVerTex( float fPolygonWidth , float fPolygonLength);				// ���_�쐬�֐�
	void	NorVertex(void);														// �@���쐬
	bool	LoadData(OCEAN dataOcean);												// �C�f�[�^�ǂݍ���

	// 3D�|���S���ɕK�v�ȗv�f
	typedef struct
	{
		D3DXVECTOR3 vtx;						// ���_
		D3DXVECTOR3 nor;						// �x�N�g���̌���(�����\)����
		D3DCOLOR	diffuse;					// ���_�F��ݒ�
		D3DXVECTOR2	tex;						// �e�N�X�`�����_
	}VERTEX_3D;

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// �Y���o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��
	
	D3DXVECTOR3 *m_pVertex;						// ���_�i�[
	D3DXVECTOR3 *m_pNor;						// �@���x�N�g���i�[
	
	int		m_nVerTexMax;						// ���_�ő��
	int		m_nIndexMax;						// �Y���ő��
	USHORT	m_nTexNum;							// �e�N�X�`���ԍ��ۑ�
	
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// �C�̈ʒu
	D3DXVECTOR3 m_rot;							// �C�̌���
	D3DXVECTOR3 m_scl;							// �C�̑傫��
	int			m_nTimeCnt;
	float		m_fAngle;						// �p�x
	OCEAN		m_DataOcean;					// �C�f�[�^
};

#endif //_OCEAN_H_