//=============================================================================
// �X�e�[�W���� [ stage.h ]
//
// �����	: ���� �Y��
//
// �@�\		: �X�e�[�W�ݒ�
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sky.h"			// ��
#include "mountain.h"		// �R
#include "field.h"			// �n��
#include "wall.h"			// ��
#include "tree.h"			// ��
#include "grass.h"			// ��
#include "ocean.h"			// �C
#include "item.h"			// �A�C�e��

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_OBJECT ( 300 )			// �e�X�e�[�W�I�u�W�F�N�g�̍ő��

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	int			nWallMax;			// �ǂ̐�
	int			nFieldMax;			// �n�ʂ̐�			
	int			nTreeMax;			// �؂̐�
	int			nGrassMax;			// ���̐�
	int			nOceanMax;			// �C�̐�
	int			nItemMax;			// �A�C�e����
}OBJ_NUM;

//=============================================================================
// �N���X�錾
//=============================================================================
class CStage
{
public:		// ����
	typedef enum
	{
		FIELD_OBJ = 0,		// �n�ʂ�ݒ蒆
		WALL_OBJ,			// �ǂ�ݒ蒆
		TREE_OBJ,			// �؂�ݒ蒆
		GRASS_OBJ,			// ����ݒ蒆
		OCEAN_OBJ,			// �C�𐶐���
		MAX_OBJ				// �ő�
	}SET_OBJ;				// ����ݒ肵�Ă��邩

	typedef enum
	{
		EDITMODE_CREATE = 0,	// �I�u�W�F�N�g�쐬
		EDITMODE_DELETE,		// �I�u�W�F�N�g�j��
		EDITMODE_MOVE,			// �I�u�W�F�N�g�ړ�
		EDITMODE_CHENGE,		// �I�u�W�F�N�g�̉摜�Ȃǂ�ς���
		EDITMODE_MAX			// �I�u�W�F�N�g����
	}EDIT_MODE;


	typedef struct
	{
		float	fWidth;		// �|���S���̕�			
		float	fHeight;	// �|���S���̍���
		float	fLength;	// �|���S���̉��s��
		int		nNumX;		// �|���S����(��)
		int		nNumY;		// �|���S����(�c)
		int		nNumZ;		// �|���S����(��)
	}POLYGON;


	CStage(void);			// �C���X�^���X����
	~CStage(void);			// �C���X�^���X�j��
	HRESULT Init(void);		// �X�e�[�W������
	void	Uninit(void);	// �X�e�[�W�j��
	void	Update(void);	// �X�e�[�W�X�V
	void	Draw(void);		// �X�e�[�W�`��
		
	CSky			*GetSky(void){return m_pSky;}				// ��擾
	CMountain		*GetMountain(void){return m_pMountain;}		// �R�擾
	CField			**GetField(void){return m_pField;}			// �n�ʎ擾
	CWall			**GetWall(void){return m_pWall;}			// �ǎ擾
	void			GetFieldNum(int &nFieldNum);				// �n�ʂ̐��擾
	void			GetWallNum(int &nWallNum);					// �ǂ̐��擾

	HRESULT	Save(void);		// �X�e�[�W��������
	bool	Load(void);		// �X�e�[�W�ǂݍ���

private:	// �v�f
	void EditCreate(CInputKeyboard *pKeyboard);	// �I�u�W�F�N�g�̍쐬
	void EditDelete(CInputKeyboard *pKeyboard);	// �I�u�W�F�N�g�̔j��
	void EditMove(CInputKeyboard *pKeyboard);	// �I�u�W�F�N�g�̈ړ�
	void EditChange(CInputKeyboard *pKeyboard);	// �I�u�W�F�N�g�̉摜�Ȃǂ�ς���

	bool		m_bLoad;					// �ǂݍ��݃t���O
	CSky		*m_pSky;					// ��|�C���^
	CMountain	*m_pMountain;				// �R�|�C���^
	CField		*m_pField[MAX_OBJECT];		// �n�ʃ|�C���^
	CWall		*m_pWall[MAX_OBJECT];		// �ǂ̃|�C���^
	CTree		*m_pTree[MAX_OBJECT];		// �؂̃|�C���^
	CGrass		*m_pGrass[MAX_OBJECT];		// ���̃|�C���^
	COcean		*m_pOcean[MAX_OBJECT];		// �C�̃|�C���^
	OBJ_NUM		m_ObjNum;					// �I�u�W�F�N�g��
	SKY			m_DataSky;					// ��f�[�^
	MOUNTAIN	m_DataMountain;				// �R�f�[�^
	FIELD		m_DataField[MAX_OBJECT];	// �n�ʃf�[�^
	WALL		m_DataWall[MAX_OBJECT];		// �ǃf�[�^
	BILLBOARD	m_DataTree[MAX_OBJECT];		// �؃f�[�^
	BILLBOARD	m_DataGrass[MAX_OBJECT];	// ���f�[�^
	OCEAN		m_DataOcean[MAX_OBJECT];	// �C�f�[�^
	int			m_Point;					// �����w���Ă���̂��̈ʒu
	int			m_nFiledVerPoint;			// �n�ʂ̒��_�̈ʒu  
	int			m_nSpeed;					// �ړ����x
	int			m_nSetObj;					// ����ݒ肵�Ă���̂�
	USHORT		m_nTexNum;					// �摜�ԍ�
	EDIT_MODE	m_nEditMode;				// �G�f�B�b�g���[�h
	POLYGON		m_Polygon;					// �|���S���̐ݒ�
};
	
#endif // _STAGE_H_

// end of file