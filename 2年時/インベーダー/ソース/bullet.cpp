//-----------------------------------------------------------------------------
//
// �e���� �N���X		[bullet.cpp]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "bullet.h"

//-----------------------------------------------------------------------------
// �e�̃C���X�^���g
//-----------------------------------------------------------------------------
CBullet::CBullet(void)
{
	m_fPosX = 0;					// �e�̌���X���W
	m_fPosY = 0;					// �e�̌���Y���W
	m_fPosXOld = 0;					// �e�̌�����X���W
	m_fPosYOld = 0;					// �e�̌�����Y���W
	m_fMoveX = 0;					// �e�̈ړ���X
	m_fMoveY = 0;					// �e�̈ړ���Y
	CObject::SetObjType(OBJTYPE_BULLET);
}

//-----------------------------------------------------------------------------
// �e�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CBullet::~CBullet(void)
{
	// �e�̔j��
	LOCATE(m_fPosX, m_fPosY);			// ���݈ʒu��
	printf(" ");						// �X�y�[�X������
	LOCATE(m_fPosXOld, m_fPosYOld);		// �ߋ��̈ʒu��
	printf(" ");						// �X�y�[�X������
}

//-----------------------------------------------------------------------------
// �e�̏�����
//-----------------------------------------------------------------------------
void CBullet::Init(float fPosX, float fPosY, float fMoveX, float fMoveY)
{
	m_fPosX = fPosX;			// �e�̌��݈ʒuX
	m_fPosY = fPosY;			// �e�̌��݈ʒuY
	m_fPosXOld = 0;				// �e�̌������ʒuX
	m_fPosYOld = 0;				// �e�̌������ʒuY
	m_fMoveX = fMoveX;			// �e�̑��xX
	m_fMoveY = fMoveY;			// �e�̑��xY
}

//-----------------------------------------------------------------------------
// �e�̏I��
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	// �e�̔j��
}

//-----------------------------------------------------------------------------
// �e�̍X�V
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	m_fPosXOld = m_fPosX;								// �e�̌������ʒuX�Ɍ��݂̈ʒuX����
	m_fPosYOld = m_fPosY;								// �e�̌������ʒuY�Ɍ��݂̈ʒuY����
	m_fPosX += m_fMoveX;								// �e�̌��݈ʒuX�𑬓xX���ړ�
	m_fPosY += m_fMoveY;								// �e�̌��݈ʒuY�𑬓xY���ړ�

	// �e���㉺��ʊO�ɏo����
	if(m_fPosY <  SCREEN_HEIGHT_MIN )
	{
		m_fPosY = SCREEN_HEIGHT_MIN;					// �ʒu�𒲐�
   		CExplosion::Create(m_fPosX, m_fPosY);
		LOCATE((int)m_fPosXOld,(int)m_fPosYOld);		// �e�̌������ʒu���w��
		printf(" ");									// �e�̌������ʒu���X�y�[�X�o��
#ifdef _DEBUG
		LOCATE( 1, 8);
		printf("�e�̈ʒu X:%.3f, Y:%.3f", m_fPosX, m_fPosY);
#endif
		CObject::Release();								// �e��j��
	}
	else if( m_fPosY > SCREEN_HEIGHT_MAX )
	{
		m_fPosY = SCREEN_HEIGHT_MAX;					// �ʒu�𒲐�
		LOCATE((int)m_fPosXOld,(int)m_fPosYOld);		// �e�̌������ʒu���w��
		printf(" ");									// �e�̌������ʒu���X�y�[�X�o��
		CExplosion::Create(m_fPosX, m_fPosY);			// �������쐬
		CObject::Release();								// �e��j��
	}
	else
	{
		// �����蔻��
		// �I�u�W�F�N�g���[�N�擪�A�h���X���擾
/*		CObject *pObject = CObject::GetObj();
		
		for(int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)	// �I�u�W�F�N�g����
		{
			if(((int *)pObject)[nCntObj] != NULL)
			{
				// �I�u�W�F�N�g����Ŗ������
				// �C���X�^���X�ւ̃|�C���^���擾
				CObject *pObjCur = (CObject *)(((int *)pObject)[nCntObj]);

				// �I�u�W�F�N�g�^�C�v���擾
				CObject::OBJTYPE type = pObjCur->GetObjTyep();
				
				if(type == CObject::OBJTYPE_ENEMY)
				{
					// �G�ł����
					// �G�̈ʒu���擾
					float fPosX, fPosY, fPosXOld, fPosYOld;
					pObjCur->GetPos(&fPosX, &fPosY, &fPosXOld, &fPosYOld);
					
					if( m_fPosX > m_fPosX - 1)
					{
						// �����蔻��
						if( m_fPosX < fPosX + 1 && 
							m_fPosY < fPosY + 1 &&
							fPosX < m_fPosX + 1 &&
							fPosY < m_fPosY + 1)
						{
#ifdef _DEBUG
							LOCATE(1, 4);
							printf("�����̐������� X:%.2f Y:%.2f",m_fPosX, m_fPosY);
#endif
							CExplosion::Create(m_fPosX, m_fPosY);		// �������쐬
							LOCATE((int)m_fPosXOld,(int)m_fPosYOld);	// �e�̌������ʒu���w��
							printf(" ");
							LOCATE((int)fPosXOld, (int)fPosYOld);		// �������������W�w��
							printf(" ");								// �G������
							pObjCur->Release();							// �G��j��
							CObject::Release();							// �e��j��
						}
					}
				}
			}
		}*/
	}

}

//-----------------------------------------------------------------------------
// �e�̕`��
//-----------------------------------------------------------------------------
void CBullet::Draw(void)
{
	LOCATE((int)m_fPosXOld , (int)m_fPosYOld);	// �e�̌������ʒu��LOCATE�Ŏw��
	printf(" ");								// �e�̌������ʒu�ɃX�y�[�X�o��
	LOCATE((int)m_fPosX , (int)m_fPosY);		// �e�̌��݈ʒuX��LOCATE�Ŏw��
	printf("o");								// �e�̌��݈ʒu�ɒe���o��
}

//-----------------------------------------------------------------------------
// �e�̐���
//-----------------------------------------------------------------------------
CBullet *CBullet::Create(float fPosX, float fPosY, float fMoveX, float fMoveY)
{
	// �e�̃|�C���^�[
	CBullet *pBullet;									

	// �e�̐���
	pBullet = new CBullet;	

	// �e�̏�����
	pBullet->Init(fPosX, fPosY, fMoveX, fMoveY);	
	
	return pBullet;
}