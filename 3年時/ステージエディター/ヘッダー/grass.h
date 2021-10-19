//=============================================================================
// ������ [grass.h]
//
// �����	: ���� �Y��
//
// �@�\		: ���쐬
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _GRASS_H_
#define _GRASS_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sceneBillboard.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CGrass : public CBillboard 
{
public:		// ����
	CGrass(int nPriority = 4, OBJTYPE objType = OBJTYPE_BILLBOARD);		// ���C���X�^���X����
	~CGrass(void);														// ���C���X�^���X�j��
	static CGrass *Create(float fWidth, float fHeight, 
							USHORT nTexNum);							// ���쐬
	static CGrass *CreateLoad(BILLBOARD dataGrass);						// ���쐬&�ǂݍ���
	
	HRESULT Init(void){return S_OK;	}									// ��������
	HRESULT Init(float fWidth, float fHeight, 
					USHORT nTexNum);									// ��������
	void Uninit(void);													// ���I��
	void Update(void);													// ���X�V
	void Draw(void);													// ���`��

private:	// �v�f
	BILLBOARD	m_DataGrass;											// ���̃f�[�^
};

#endif	// _GRASS_H_