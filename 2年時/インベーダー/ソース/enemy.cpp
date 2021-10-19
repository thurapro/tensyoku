//-----------------------------------------------------------------------------
//
// �G���� �N���X		[enemy.cpp]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define ENEMY_MOVE_LEFT_X	(-0.3f)
#define ENEMY_MOVE_RIGHT_X	(0.3f)
#define ENEMY_MOVE_Y		(1.0f)
#define ENEMY_SHOT_TIME		(20)
#define ENEMY_BULLET_SPEED	(1.0f)

//-----------------------------------------------------------------------------
// �G�̐ÓI�����o�[�ϐ�
//-----------------------------------------------------------------------------
int CEnemy::m_nNumCnt = 0;		// �G�̃J�E���g

//-----------------------------------------------------------------------------
// �G�̃R���X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::CEnemy(void)
{
	// �G�̐���
	CObject::SetObjType(OBJTYPE_ENEMY);
	
	// �G�̒ǉ�
	m_nNumCnt ++;

}

//-----------------------------------------------------------------------------
// �G�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::~CEnemy(void)
{
	// �G�����炷
	m_nNumCnt--;		// �G�̐������炷
#ifdef _DEBUG
	LOCATE(1, 20);
	printf("�G�̐�%d��", m_nNumCnt);
#endif
}

//-----------------------------------------------------------------------------
// �G�̏�����
//-----------------------------------------------------------------------------
void CEnemy::Init(float fPosX, float fPosY)
{
	m_fPosX = fPosX;							// �G�̏����ʒuX���W
 	m_fPosY = fPosY;							// �G�̏����ʒuY���W
	m_fMoveX = ENEMY_MOVE_RIGHT_X;				// �G�̈ړ���X���W
	m_fMoveY = ENEMY_MOVE_Y;					// �G�̈ړ���Y���W
	m_bAlive = true;							// �G��\��
	m_nShotTime = 0;							// �e�𔭎˂��鎞��
}

//-----------------------------------------------------------------------------
// �G�̏I��
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// �I��
}

//-----------------------------------------------------------------------------
// �G�̍X�V
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	// ���̍��W��ۑ�
	m_fPosXOld = m_fPosX;					// ���݂̈ʒu��ۑ�X���W
	m_fPosYOld = m_fPosY;					// ���݂̈ʒu��ۑ�Y���W
	m_fPosX += m_fMoveX;					// �G���ړ�X���W

	// �G�������E�[�𒴂��Ă��܂�����
	if(m_fPosX > SCREEN_WIDTH_MAX)
	{
		m_fPosX = SCREEN_WIDTH_MAX;			// �ʒu�𒲐�
		m_fPosY += m_fMoveY;				// �G��Y���W�����ɂ��炷
		m_fMoveX = ENEMY_MOVE_LEFT_X;		// �G�̈ړ�������������ֈړ�
	}
	else if(m_fPosX < SCREEN_WIDTH_MIN )	// �������[����������
	{
		m_fPosX = SCREEN_WIDTH_MIN;			// �ʒu�𒲐�
		m_fPosY += m_fMoveY;				// �G��Y���W�����ɂ��炷
		m_fMoveX = ENEMY_MOVE_RIGHT_X;		// �G�̈ړ�����������E�ֈړ�
	}

	// �G����������ʂ��z���Ă��܂�����
	if(m_fPosY > SCREEN_HEIGHT_MAX)
	{
		m_fPosY = SCREEN_HEIGHT_MAX;		// �ʒu�𒲐�
		LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// �ʒu���w��
		printf(" ");						// �G������
		CObject::Release();					// �G��j��
	}

	// �e�ƓG�̓����蔻��
	CObject *pObject = CObject::GetObj();	// �I�u�W�F�N�g�擾

	// �I�u�W�F�N�g
	for(int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		// OBJ������
		if(((int *)pObject)[nCntObj] != NULL)
		{
			// OBJ�̒�����ł͖������
			// �C���X�^���X�ւ̃|�C���^�擾
			CObject *pObjCur =  (CObject *)(((int *)pObject)[nCntObj]);
			
			// �^�C�v�擾
			CObject::OBJTYPE type = pObjCur->GetObjTyep();

			if(type ==	CObject::OBJTYPE_BULLET)
			{
#ifdef _DEBUG
				LOCATE(1,11);
				printf("�G��cpp�Ŏ擾�����^�C�v %d",  type);
#endif
				// �e�̃I�u�W�F�N�g��������
				float fPosX, fPosY, fPosXOld, fPosYOld;			// �ʒu�擾�p�ϐ�
				pObjCur->GetPos(&fPosX, &fPosY, &fPosXOld, &fPosYOld);	// �ʒu���擾
				
				// �����蔻��
				if( m_fPosX < fPosX + 1 &&
					m_fPosY < fPosY + 1 &&
					fPosX < m_fPosX + 1 &&
					fPosY < m_fPosY + 1)
				{
					// �����������Ă�����
#ifdef _DEBUG
					LOCATE(1, 12);
					printf("�����̐������� X:%.2f Y:%.2f",m_fPosX, m_fPosY);
#endif
					CExplosion::Create(m_fPosX, m_fPosY);
#ifdef _DEBUG
					LOCATE(1,13);
					printf("�e�̌��ʒu X:%.2f, Y:%.2f", fPosXOld, fPosYOld);
#endif
					LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// �G�̑O�̍��W�ʒu��
					printf(" ");								// �X�y�[�X�o��
#ifdef _DEBUG
					LOCATE(1,14);
					printf("�e�̌��ʒu X:%.2f, Y:%.2f", fPosXOld, fPosYOld);
#endif
					LOCATE(fPosX, fPosY);					// �e�̑O�̍��W�ʒu��
					printf(" ");							// �X�y�[�X�o��
					pObjCur->Release();						// OBJ�j��
					m_bAlive = false;						// ���S���Ȃ�ɂȂ���
					CObject::Release();						// ������j��
					//m_nNumCnt--;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// �G�̕`��
//-----------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// �ʒu���w��
	printf("  ");								// �O�̈ʒu������
	LOCATE((int)m_fPosX, (int)m_fPosY);			// �ʒu���w��
	COLOR(LIME, BLACK);
	printf("V");								// �G���o��
	COLOR(WHITE, BLACK);
}


//-----------------------------------------------------------------------------
// �G���쐬
//-----------------------------------------------------------------------------
CEnemy *CEnemy::Create(float fPosX, float fPosY)
{
	// �G�̃|�C���^�[�쐬
	CEnemy *pEnemy;							

	// �G�𐶐�
	pEnemy = new CEnemy;
		
	// �G��������
	pEnemy->Init(fPosX, fPosY);

	return pEnemy;
}




