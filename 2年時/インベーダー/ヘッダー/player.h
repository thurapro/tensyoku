//-----------------------------------------------------------------------------
//
// player���� �N���X		[player.h]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2�d�C���N���[�h�h�~
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "object.h"
#include "CScreen.h"
#include "common.h"
#include "main.h"

//-----------------------------------------------------------------------------
// �v���C���[�N���X �h���N���X�� : �A�N�Z�X�w��q ��{�N���X��
//-----------------------------------------------------------------------------
class CPlayer : public CObject
{
public:
	CPlayer();											// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^
	void Init(float fPosX, float fPosY);				// �v���C���[�̈ʒu������
	void Uninit(void);									// �I������
	void Update(void);									// �v���C���[�̍X�V
	void Draw(void);									// �v���C���[�̕`��
	void GetPos(float *pPosX, float *pPosY){*pPosX = m_fPosX; *pPosY = m_fPosY;}		// �v���C���[�̈ʒu
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// �����̈ʒu�擾
	static CPlayer *Create(float fPosX, float fPosY);	// �v���C���[�̐���
private:
	float m_fPosX;										// �v���C���[��X���W
	float m_fPosY;										// �v���C���[��Y���W
	float m_fPosXOld;									// �v���C���[�̑O�ɂ���X���W
	float m_fPosYOld;									// �v���C���[�̑O�ɂ���Y���W
	float m_fMoveX;										// �v���C���[��x�ړ���
	float m_fMoveY;										// �v���C���[��y�ړ���
	bool m_bMove;										// �v���C���[���ړ����������ĂȂ���
};

#endif //_PLAYER_H_
