//============================================================================= 
// �V�[������ [ scene.h ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: �V�[�����X�g�Ǘ�
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LIST	(8)					// ���X�g�̐�

//=============================================================================
// �\���̐錾
//=============================================================================

// 2D�|���S���ɕK�v�ȗv�f
typedef struct
{
	D3DXVECTOR3 Vertex;			// ���_���W
	float		rhw;			// �������W�̋t��
	D3DCOLOR	Diffuse;		// ���_�̐F
	D3DXVECTOR2	Texture;		// �e�N�X�`�����W
}VERTEX_2D;

// 3D�|���S���ɕK�v�ȗv�f
typedef struct
{
	D3DXVECTOR3 vtx;						// ���_
	D3DXVECTOR3 nor;						// �x�N�g���̌���(�����\)����
	D3DCOLOR	diffuse;					// ���_�F��ݒ�
	D3DXVECTOR2	tex;						// �e�N�X�`�����_
}VERTEX_3D;


//=============================================================================
// �N���X�錾
//=============================================================================
class CScene
{
public:		// ����
	typedef enum
	{
		OBJTYPE_NONE = 0,				// ���Ɋ֌W�Ȃ�
		OBJTYPE_2D,						// 2D
		OBJTYPE_3D,						// 3D
		OBJTYPE_MODEL,					// ���f��
		OBJTYPE_BILLBOARD,				// �r���{�[�h
		OBJTYPE_MESH,					// ���b�V��
		OBJTYPE_PLAYER,					// �v���C���[
		OBJTYPE_PLAYER2,				// �v���C���[2
		OBJTYPE_ENEMY,					// �G
		OBJTYPE_ITEM,					// �A�C�e��
		OBJTYPE_TREE,					// ��
		OBJTYPE_GRASS,					// ��
		OBJTYPE_OCEAN,					// �C
		OBJTYPE_SHADOW,					// �e
		OBJTYPE_EXPLOSION,				// ����
		OBJTYPE_EFFECT,					// �G�t�F�N�g
		OBJTYPE_GIMMICK,				// �M�~�b�N
		OBJTYPE_FIELD,					// �n��
		OBJTYPE_WALL,					// ��
		OBJTYPE_MOUNTAIN,				// �R
		OBJTYPE_SKY						// ��
	}OBJTYPE;

	CScene(int nPriority = 0, OBJTYPE objType = OBJTYPE_NONE);	// �C���X�^���X����
	virtual ~CScene(){};							// �C���X�^���X�j��
	virtual HRESULT	Init(void)=0;					// �V�[������������
	virtual void	Uninit(void)=0;					// �V�[���I������
	virtual void	Update(void)=0;					// �V�[���X�V����
	virtual void	Draw(void)=0;					// �V�[���`�揈��
	static	void	UpdateAll(void);				// ���X�g���ɂ���V�[���X�V����
	static	void	DrawAll(void);					// ���X�g���ɂ���V�[���`�揈��
	static  void	ReleaseAll(void);				// ���X�g���ɂ���V�[���j������
	void	LinkList(int nPriority, OBJTYPE objType);	// ���X�g�ɓ����
	void	UnlinckList(void);						// ���X�g����O��
	void	Release(void);							// �t���O�I��

	static CScene *GetScene(int i){return m_pTop[i];}	// �V�[���擾
	CScene *GetNext(void){ return m_pNext;}				// ���̃V�[���擾

	OBJTYPE GetObjType(void){return m_objType;}			// �V�[���̎�ގ擾

private:
	static CScene *m_pTop[MAX_LIST];		// �O�̏ꏊ
	static CScene *m_pCur[MAX_LIST];		// ���݂̏ꏊ
	CScene *m_pPrev;						// �O�̃I�u�W�F
	CScene *m_pNext;						// ���̃I�u�W�F
	bool	m_bDethFlag;					// �����Ă���̂�
	int		m_nPriority;					// �D�揇�ʕۑ�
	CScene *m_pSceneLink;					// �N�Ɉˑ����Ă��邩
	OBJTYPE m_objType;						// �I�u�W�F�N�g�̎��
};

#endif	// _SCENE_H_

// end of file