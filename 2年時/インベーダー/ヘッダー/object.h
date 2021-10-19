//-----------------------------------------------------------------------------
//
// object����		[object.h]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2�d�C���N���[�h�h�~
//-----------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "CScreen.h"
//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_OBJECT (100)						// �I�u�W�F�N�g�̍ő吔

//-----------------------------------------------------------------------------
// �I�u�W�F�N���X��`
//-----------------------------------------------------------------------------
class CObject
{
public:
	typedef enum
	{
		OBJTYPE_PLAYER = 0,												// �v���C���[�������Ă���
		OBJTYPE_ENEMY,													// �G�������Ă���
		OBJTYPE_BULLET,													// �e�������Ă���
		OBJTYPE_EXPLOSION,												// �����������Ă���
		OBJTYPE_MAX														// �ō��l
	}OBJTYPE;
	CObject();															// �R���X�g���N�^
	virtual ~CObject() = 0;												// �f�X�g���N�^
	virtual void Init(void){};											// ������
	virtual void Uninit(void)=0;										// �I������
	virtual void Update(void)=0;										// �X�V����
	virtual void Draw(void)=0;											// �`�揈��
	virtual void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld)=0;			// �����̈ʒu�擾
	// �|�W�V�������擾
	void Release(void);													// �I�u�W�F�N�g�j��
	static void UpdateAll(void);										// ���ׂĂ̍X�V
	static void DrawAll(void);											// ���ׂĂ̕`��
	static void ReleaseAll(void);										// ���ׂĂ̔j��
	void SetObjType(OBJTYPE type){m_objType = type;}					// �I�u�W�F�N�g�^�C�v���Z�b�g
	OBJTYPE GetObjTyep(void){ return m_objType;}						// �I�u�W�F�N�g�^�C�v���擾
	static CObject *GetObj(void){return (CObject *)&m_apObject[0];}
private:
	static CObject *m_apObject[MAX_OBJECT];				// �I�u�W�F�N�g���[�N
	static int m_nNumObject;							// �I�u�W�F�N�g����
	OBJTYPE m_objType;									// �I�u�W�F�N�g�̃^�C�v
	int m_nID;											// �I�u�W�F�N�gID
};

#endif //_OBJECT_H_