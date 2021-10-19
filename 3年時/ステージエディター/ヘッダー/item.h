//=============================================================================
// �A�C�e������[item.h]
//
// ����� : ���� �Y��
//
// �@�\ :  �A�C�e��
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sceneX.h"

class CShadow;

//=============================================================================
// �N���X��`
//=============================================================================
class CItem : public CSceneX
{
public:		// ����
	CItem(int nPriority = 0, OBJTYPE objType = OBJTYPE_ITEM);			// �A�C�e���C���X�^���X����
	~CItem(void);			// �A�C�e���C���X�^���X�j��
	static CItem *Create(float fPosX, float fPosY, float fPosZ, 
						unsigned int nModeNum, unsigned int nTexNum);		// �A�C�e������
	HRESULT Init(void);		// �A�C�e������������
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
						unsigned int nModeNum, unsigned int nTexNum);		// �A�C�e������������
	void Uninit(void);		// �A�C�e���I������
	void Update(void);		// �A�C�e���X�V����
	void Draw(void);		// �A�C�e���`�揈��

private:
	CShadow		*m_pShadow;		// �e�|�C���^
};

#endif // _ITEM_H_

// end of file //
