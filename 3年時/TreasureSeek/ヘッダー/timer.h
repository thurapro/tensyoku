//=============================================================================
// ���ԏ���[timer.h]
//
// ����� : ���� �Y��
//
// �@�\ :  �^�C�}�[
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "number.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�
#define MAX_TIMER			(3)											// ����(�S�b)
#define MAX_TIME_COUNT		(16)										// 1�b�ɕϊ�

//=============================================================================
// �N���X�錾
//=============================================================================
class CTimer : public CScene2D
{
public:
	CTimer(void);								// �X�R�A�C���X�^���X����
	~CTimer(void);								// �X�R�A�C���X�^���X�j��

	HRESULT CTimer::Init(void);					// ������

	// �X�R�A���������� �I�[�o�[���[�h
	HRESULT Init(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum);
	void Uninit(void);							// �X�R�A�I������
	void Update(void);							// �X�R�A�X�V����
	void Draw(void);							// �X�R�A�`�揈��
	static CTimer *CTimer::Create(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum);
	unsigned int GetTime(void){return m_nTime;}
	CNumber  **GetNumber(void){return &m_pNumber[0];}
	
	// �e�N�X�`�����W�ʒu�Z�b�g 
	void SetTimer(unsigned nNumber);
private:
	CNumber				*m_pNumber[MAX_TIMER];			// �X�R�A�̔ԍ�
	unsigned int		m_nTimerCnt;					// 1�b�ԂɕύX
	unsigned int		m_nTime;						// ����
	unsigned int		m_nTexNum;						// �e�N�X�`���ԍ�	
};

#endif // _TIMER_H