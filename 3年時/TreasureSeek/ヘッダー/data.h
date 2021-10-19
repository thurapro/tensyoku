//=============================================================================
// �f�[�^�ꊇ�Ǘ� [ data.h ]
//
// �����	: ���� �Y��
//
// �@�\		: �f�[�^�ꊇ�Ǘ�
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _DATA_H_
#define _DATA_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "model.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_TEXT	("data/text/title.txt")
#define GAME_TEXT	("data/text/game.txt")
#define RESULT_TEXT	("data/text/result.txt")

//=============================================================================
// �N���X��`
//=============================================================================
class CData
{
public:		// ����
	CData(void);							// �C���X�^���X����
	~CData(void);							// �C���X�^���X�j��
	HRESULT Init(HWND hWnd, const char *FileName);// �f�[�^�̏���������
	void Uninit(void);						// �f�[�^�̏I������
	void Save(void);						// �܂Ƃ߂Ă���f�[�^��ۑ�

	CTexture	*GetTexture(void){return m_pTexture;}		// �e�N�X�`���擾
	CModel		*GetModel(void){return m_pModel;}			// ���f���擾
	CSound		*GetSound(void){return m_pSound;}			// �T�E���h�擾

private:	// �v�f
	HRESULT LoardData(HWND hWnd, const char *FileName);		// �܂Ƃ߂Ă���f�[�^��ǂݍ���
	
	CTexture	*m_pTexture;		// �e�N�X�`���|�C���^
	CModel		*m_pModel;			// ���f���|�C���^
	CSound		*m_pSound;			// �T�E���h�|�C���^
};

#endif	// _DATA_H_

// end of file //