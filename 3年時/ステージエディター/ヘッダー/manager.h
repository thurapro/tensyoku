//=============================================================================
// �c�[���쐬�̑O�菇�@�@�@�@�@�@�@�@�t�B�[���h�쐬�c�[���p
//  
// ���C������ [maneger.h]
//
// �@�\ : �}�l�[�W���[����
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "renderer.h"
#include "inputkeyboard.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
class CData;
class CStage;

//=============================================================================
// �N���X�錾
//=============================================================================
class CManager
{
public:		// ����
	CManager(void);													// �C���X�^���X����
	~CManager(void);												// �C���X�^���X�j��
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// �}�l�[�W���[������
	void Uninit(void);												// �}�l�[�W���[�I��
	void Update(void);												// �}�l�[�W���[�X�V
	void Draw(void);												// �}�l�[�W���[�`��
	static CRenderer		*GetRenderer(void){return m_pRenderer;}	// �����_���[�擾
	static CInputKeyboard	*GetKeyboard(void){return m_pKeyboard;}	// �L�[�{�[�h�擾
	static CDebug			*GetDebug(void){return m_pDebug;}		// �f�o�b�O�擾
	static CCamera			*GetCamera(void){return m_pCamera;}		// �J�����擾
	static CData			*GetData(void){return m_pData;}
	static CStage			*GetStage(void){return m_pStage;}		

private:	// �v�f
	static CRenderer		*m_pRenderer;							// �����_���[�|�C���^
	static CInputKeyboard	*m_pKeyboard;							// �L�[�{�[�h�|�C���^
	static CDebug			*m_pDebug;								// �f�o�b�O�|�C���^
	static CCamera			*m_pCamera;								// �J�����|�C���^
	CLight					*m_pLight;								// ���C�g�|�C���^
	static CData			*m_pData;								// �f�[�^�|�C���^
	static CStage			*m_pStage;
};

#endif // _MANAGER_H_

// end of file