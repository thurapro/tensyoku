//=============================================================================
// �X�R�A����[score.h]
//
// ����� : ���� �Y��
//
// �@�\ :  �X�R�A�[
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "number.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�
#define MAX_SCORE			(3)

//=============================================================================
// �N���X�錾
//=============================================================================
class CScore : public CScene2D
{
public:
	CScore(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);								// �X�R�A�C���X�^���X����
	~CScore(void);								// �X�R�A�C���X�^���X�j��

	static CScore *CScore::Create(float fPosX, float fWidth, float fPosY, 
									float fHeight, unsigned int nTexNum);	// �X�R�A�[�쐬
	HRESULT CScore::Init(void);					// ������
	HRESULT Init(float fPosX, float fWidth, float fPosY, 
					float fHeight, unsigned int nTexNum);	// ������
	void Uninit(void);										// �X�R�A�I������
	void Update(void);										// �X�R�A�X�V����
	void Draw(void);										// �X�R�A�`�揈��
	
	// �e�N�X�`�����W�ʒu�Z�b�g 
	void SetScore(unsigned nNumber);
	unsigned int GetScore(void){return m_nScore;}	// �X�R�A����
private:
	unsigned int m_nScore;						// �X�R�A
	CNumber	*m_pNumber[MAX_SCORE];				// �X�R�A�̔ԍ�
	unsigned int m_nTexNum;						// �e�N�X�`���ԍ�
};

#endif // _SCORE_H_