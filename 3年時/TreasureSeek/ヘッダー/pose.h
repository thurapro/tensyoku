//=============================================================================
// �|�[�Y���� [pose.h]
//
// �����	: ���� �Y��
//
// �@�\		: �|�[�Y�@�\
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�̖h�~
//=============================================================================
#ifndef _POSE_H_
#define _POSE_H_

//=============================================================================
// �}�N����`
//=============================================================================
class CScene2D;				// 2D�|���S��
#define MAX_POSE	( 7 )		// 2D�摜�̐�

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CPose
{
public:	
	CPose(void);												// �|�[�Y�C���X�^���X����
	~CPose(void);												// �|�[�Y�C���X�^���X�j��
	HRESULT Init(void);											// �|�[�Y����������
	void	Uninit(void);										// �|�[�Y�I������
	void	Update(void);										// �|�[�Y�X�V����
	void	Draw(void);											// �|�[�Y�`��
	void	SetPoseNum(unsigned short nNum){m_nNumber = nNum;}
	bool	GetTutorialFlag(void){return m_bTutorial;}
	CScene2D **GetPose(void){return &m_apPose[0];}
	unsigned short GetPoseNum(void){return  m_nNumber;}
private:	
	CScene2D			*m_apPose[MAX_POSE];	// �|�[�Y���
	CScene2D			*m_pTutorial[2];		// �`���[�g���A�����
	float				m_fPosY;				// �ʒuY
	float				m_fHeight;				// ����
	float				m_fTexY;				// �e�N�X�`�����WX
	float				m_fTexHeight;			// �e�N�X�`���̕�
	unsigned short		m_nNumber;				// �ǂ����w���Ă��邩
	bool				m_bTutorial;			// �`���[�g���A���t���O
};

#endif	// _POSE_H_
