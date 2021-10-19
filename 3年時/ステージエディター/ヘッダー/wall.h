//=============================================================================
// ���� [meshwall.h]
//
// �����	: ���� �Y��
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "sceneline.h"

class CSceneLine;

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	float					fWidth;			// �|���S���̕�
	float					fHeight;		// �|���S���̍���
	int						nNumX;			// �u���b�N�̐� X
	int						nNumY;			// �u���b�N�̐�	Z
	USHORT					nTexNum;		// �摜�ԍ�
	D3DXVECTOR3				pos;			// �ǃI�u�W�F�N�g�̈ʒu
	D3DXVECTOR3				rot;			// �ǃI�u�W�F�N�g�̌���
	D3DXVECTOR3				scl;			// �ǃI�u�W�F�N�g�̑傫��
}WALL;
	
//=============================================================================
// �N���X�錾
//=============================================================================
class CWall : public CScene
{
public:
	CWall(int nPriority = 3, OBJTYPE objType = OBJTYPE_WALL);		// �ǃI�u�W�F�N�g�C���X�^���X����
	~CWall(void);													// �ǃI�u�W�F�N�g�C���X�^���X�j��
	static CWall *Create(float fPolygonWidth, float fPolygonHeight,
						int nNumX, int nNumY, USHORT nTexNum);		// �ǃI�u�W�F�N�g�̍쐬
	static CWall *CreateLoad(WALL dataWall);						// �ǃI�u�W�F�N�g�̍쐬�Ɠǂݍ���
	HRESULT	Init(void);												// �ǃI�u�W�F�N�g������
	HRESULT Init(float fPolygonWidth, float fPolygonHeight, 
				int nNumX, int nNumY, USHORT nTexNum);				// �ǃI�u�W�F�N�g������
	void	Uninit(void);											// �ǃI�u�W�F�N�g�j��
	void	Update(void);											// �ǃI�u�W�F�N�g�̍X�V
	void	Draw(void);												// �ǃI�u�W�F�N�g�̕`��

	WALL	GetData(void){ return m_DataWall; }						// �ǃf�[�^�擾 

	void	SetTextureNum(USHORT nTexNum);							// �摜�ԍ��ݒ�
	void	SetPosition(float fPosX, float fPosY, float fPosZ);		// �ǂ̈ʒu�ݒ�
	void	SetPosition(D3DXVECTOR3 pos);							// �ǂ̈ʒu�ݒ�
	void	SetRotition(float fPosX, float fPosY, float fPosZ);		// �ǂ̌����ݒ�
	void	SetRotition(D3DXVECTOR3 rot);							// �ǂ̌����ݒ�
	void	SetTexNum(USHORT nTexNum);								// �摜�ԍ��ݒ�

	D3DXVECTOR3 GetPosition(void){return m_pos;}					// �ǂ̈ʒu�擾
	D3DXVECTOR3 GerRotition(void){return m_rot;}					// �ǂ̊p�x�擾

private:
	void	LoadData(WALL dataWall);								// �ǃf�[�^�ǂݍ���
	HRESULT MakeVerTex(float fPolygonWidth, float fPolygonHeight);	// ���_�쐬�֐�	

	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	// ���_�o�b�t�@�p�ϐ�
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;		// �Y���o�b�t�@�p�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��	
	int						m_nVerTexMax;		// ���_�ő��
	int						m_nIndexMax;		// �Y���ő��
	USHORT					m_nTexNum;			// �e�N�X�`���ԍ��ۑ�
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;				// �ǃI�u�W�F�N�g�̈ʒu
	D3DXVECTOR3				m_rot;				// �ǃI�u�W�F�N�g�̌���
	D3DXVECTOR3				m_scl;				// �ǃI�u�W�F�N�g�̑傫��
	WALL					m_DataWall;			// �ǃf�[�^
};

#endif // _WALL_H_