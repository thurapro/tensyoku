//=============================================================================
//
// �}�l�[�W���[�N���X����[manager.h]		���� �Y��
//
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// �}�N����`
//=============================================================================
class CTitle;			// �^�C�g���N���X
class CGame;			// �Q�[���N���X
class CResult;			// ���U���g�N���X
class CInput;			// ���̓N���X 

//=============================================================================
// �}�l�[�W���[�N���X��`
//=============================================================================
class CManager
{
public:
	typedef enum 
	{
		MODE_TITLE = 0,									// ���[�h�^�C�g��
		MODE_GAME,										// ���[�h�Q�[��
		MODE_RESULT,									// ���[�h���U���g
		MODE_MAX										// ���[�h�ő�
	}MODE;												// �Q�[���X�e�[�g�p
	CManager();											// �}�l�[�W���R���X�g���N�^
	~CManager();										// �}�l�[�W���[�f�X�g���N�^
	void Init(void);									// �������֐�
	void Uninit(void);									// �I���֐�
	void Update(void);									// �X�V�֐�
	void Draw(void);									// �`��֐�
	static CInput *GetInput(void){return m_pInput;}		// ���̓|�C���^�[�擾
	static void SetMode(MODE m_mode);					// ���[�h�Z�b�g
	MODE GetMode(void);									// ���[�h�擾
private:
	static CTitle *m_pTitle;							// �^�C�g���|�C���^
	static CGame *m_pGame;								// �Q�[���|�C���^
	static CResult *m_pResult;							// ���U���g�|�C���^
	static CInput *m_pInput;							// ���̓|�C���^
	static MODE m_mode;									// ���[�h
};	

#endif //_MANAGER_H_

// end files