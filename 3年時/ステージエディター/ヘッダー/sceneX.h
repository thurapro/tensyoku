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
#ifndef _SCENEX_H_
#define _SCENEX_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "model.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 0, OBJTYPE objType = OBJTYPE_MODEL);		// �C���X�^���X����
	~CSceneX(void);														// �C���X�^���X�j��
	static CSceneX *Create(float fPosX, float fPosY, float fPosZ, 
							USHORT m_nModelNum,
							USHORT m_nTextureNum);						// X�I�u�W�F�N�g�쐬	
	HRESULT	Init(void);													// X�I�u�W�F�N�g������
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				 USHORT m_nModelNum,
				 USHORT m_nTexturenNum);								// X�I�u�W�F�N�g������
	void	Uninit(void);												// X�I�u�W�F�N�g�j��
	void	Update(void);												// X�I�u�W�F�N�g�X�V
	void	Draw(void);													// X�I�u�W�F�N�g�`��

	void	SetPosition(float fPosX, float fPosY, float fPosZ);			// X�I�u�W�F�N�g�̈ʒu�ݒ�
	void	SetRotition(float fPosX, float fPosY, float fPosZ);			// X�I�u�W�F�N�g�̌����ݒ�
	void	SetScale(float fPosX, float fPosY, float fPosZ);			// X�I�u�W�F�N�g�̑傫���ݒ�

	D3DXVECTOR3 GetPosition(void){return m_pos;}						// X�I�u�W�F�N�g�̈ʒu�擾
	D3DXVECTOR3	GetRotition(void){return m_rot;}						// X�I�u�W�F�N�g�̌����擾
	D3DXVECTOR3	GetScale(void){return m_scl;}							// X�I�u�W�F�N�g�̑傫���擾
	float		GetRadius(void){return m_fRadius;}						// X�I�u�W�F�N�g�̔��a�擾

protected:
	D3DXVECTOR3			m_pos;			// X�I�u�W�F�N�g�̌��݈ʒu
	D3DXVECTOR3			m_oldpos;		// X�I�u�W�F�N�g�̑O��ʒu
	D3DXVECTOR3			m_rot;			// X�I�u�W�F�N�g�̌��݌���
	D3DXVECTOR3			m_oldrot;		// X�I�u�W�F�N�g�̑O�����
	D3DXVECTOR3			m_scl;			// X�I�u�W�F�N�g�̌��݂̑傫��
	D3DXVECTOR3			m_oldscl;		// X�I�u�W�F�N�g�̑O��̑傫��
	D3DXMATRIX			m_mtxWorld;		// ���[���h�}�g���b�N�X
	float				m_fRadius;		// X�I�u�W�F�N�g�̔��a 
	USHORT				m_nModelNum;	// ���f���ԍ�
	USHORT				m_nTextureNum;	// �e�N�X�`���ԍ�
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���f�[�^

private:
	DWORD				m_nNumMat;		// ���}�e���A����
	LPD3DXMESH			m_pMesh;		// ���b�V���|�C���^
	LPD3DXBUFFER		m_pMatBuff;		// �}�e���A���o�b�t�@
	CModel::X_FILE		m_pXmodel;		// ���f���f�[�^
};

#endif // _SCENEX_H_
