//=============================================================================
// �v���C���[���� [player.h]
//
// �����	: ���� �Y��
//
// �@�\		: �v���C���[����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================
class CShadow;				// �}�N����`

//=============================================================================
// �N���X�錾
//=============================================================================
class CPlayer: public CSceneX
{
public:
	enum
	{
		LEFT = 0,
		RIGHT,
		TOP,
		BOTTOM,
		MAX_DIRECTION
	};
	CPlayer(int nPriority, OBJTYPE objType = OBJTYPE_PLAYER);					// �v���C���[�C���X�^���X����
	~CPlayer(void);																// �v���C���[�C���X�^���X�j��
	static CPlayer *Create(float fPosX, float fPosY, float fPosZ, 
								unsigned int nModelNum, unsigned int nTexNum);	// �v���C���[����
	HRESULT Init(void);															// �v���C���[������
	HRESULT Init(float fPosX, float fPosY, float fPosZ, 
				unsigned int nModelNum, unsigned int nTexNum);					// �v���C���[������
	void Uninit(void);															// �v���C���[�I��
	void Update(void);															// �v���C���[�X�V
	void Draw(void);															// �v���C���[�`��
	void SetPosition(D3DXVECTOR3 pos);											// �v���C���[�̈ʒu�ݒ�
	D3DXVECTOR3		GetRotVector(void){return m_rotVector;}						// �v���C���[�̕����x�N�g��
	unsigned int	GetStopCnt(void){return m_nStopCnt;}						// �v���C���[�������Ȃ���������
	float PlayerRotition(D3DXVECTOR3 rot, D3DXVECTOR3 Next);					// �v���C���[�̉��p�x

private:
	D3DXVECTOR3		m_rotVector;				// �v���C���[�̕����x�N�g��
	float			m_fAngle;					// �v���C���[�̊p�x
	float			m_fMoveX;					// �i�ޗʁ@X���W
	float			m_fMoveY;					// �i�ޗʁ@Y���W
	float			m_fMoveZ;					// �i�ޗʁ@Z���W
	bool			m_bJump;					// �W�����v���Ă��邩�̃t���O
	bool			m_bMove;					// �v���C���[���i�񂾂�
	bool			m_bOutMove[4];					// �i�߂邩�ǂ���
	unsigned int	m_nStopCnt;					// �v���C���[�������Ȃ���������	
	CShadow			*m_pShadow;					// �e�|�C���^
};

///// end of file /////