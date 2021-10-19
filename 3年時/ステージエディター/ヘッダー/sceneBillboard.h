//=============================================================================
// ���� [sceneBillboard.h]
//
// �����	: ���� �Y��
//
// �@�\		: �r���{�[�h�쐬
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

typedef struct
{
	float		fWidth;		// �|���S���̕�
	float		fHeight;	// �|���S���̍���	
	USHORT		nTexNum;	// �|���S���̑傫��
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3 scl;		// �傫��
}BILLBOARD;

//=============================================================================
// �N���X�錾
//=============================================================================
class CBillboard : public CScene 
{
public:
	CBillboard(int nPriority = 4, OBJTYPE objType = OBJTYPE_BILLBOARD);		// �r���{�[�h�C���X�^���X����
	~CBillboard(void);														// �r���{�[�h�C���X�^���X�j��
	static CBillboard *Create(float fWidth, float fHeight, 
								USHORT nTexNum);							// �r���{�[�h�쐬
	static CBillboard *CreateLoad(BILLBOARD dataBillboard);					// �r���{�[�h�쐬	
	HRESULT Init(void);														// �r���{�[�h������
	HRESULT Init(float fWidth, float fHeight, 
						USHORT nTexNum);									// �r���{�[�h������
	HRESULT Init(BILLBOARD dataBillboard);									// �r���{�[�h������
	void Uninit(void);														// �r���{�[�h�I��
	void Update(void);														// �r���{�[�h�X�V
	void Draw(void);														// �r���{�[�h�`��

	void		SetPosition(float fPosX, float fPosY, float fPosZ);			// �r���{�[�h�̈ʒu�ݒ�
	void		SetPosition(D3DXVECTOR3 pos);								// �r���{�[�h�̈ʒu�ݒ�
	void		SetScale(float fSclX, float fSclY, float fSclZ);			// �r���{�[�h�̑傫���ݒ�
	void		SetScale(D3DXVECTOR3 scl);									// �r���{�[�h�̑傫���ݒ�
	void		SetTexturePos(float fTexX, float fTexY,				
								float fTexWidth, float fTexHeight);			// �e�N�X�`�����W�ݒ�
	void		SetTextureNum(USHORT nTexNum);								// �摜�ԍ��ݒ�

	D3DXVECTOR3 GetPosition(void){return m_pos;}							// �ʒu�擾
	BILLBOARD	GetData(void){return m_DataBillboard;}						// �r���{�[�h�f�[�^�擾

protected:
	bool LoadData(BILLBOARD dataBillboard);									// �r���{�[�h�f�[�^�ǂݍ���
	D3DXVECTOR3				m_pos;											// �ʒu
	D3DXVECTOR3				m_rot;											// ����
	D3DXVECTOR3				m_scl;											// �傫��
	BILLBOARD				m_DataBillboard;								// �r���{�[�h�f�[�^

private:
	HRESULT MakeVertex(float fWidth, float fHeight);						// ���_�o�b�t�@�쐬 
	
	D3DXMATRIX				m_mtxWorld;										// ���[���h
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9		m_pTexture;										// �e�N�X�`��
	USHORT					m_nTexNum;										// �e�N�X�`���ԍ�
};

#endif // _BILLBOARD_H_