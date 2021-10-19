//-----------------------------------------------------------------------------
//
// object����		[object.cpp]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "object.h"

//-----------------------------------------------------------------------------
// �ÓI�̃����o�[�ϐ���`
//-----------------------------------------------------------------------------
CObject *CObject::m_apObject[MAX_OBJECT] ={NULL};
int CObject::m_nNumObject = 0;

//-----------------------------------------------------------------------------
// OBJ�̃R���X�g���N�^
//-----------------------------------------------------------------------------
CObject::CObject(void)
{
	for(int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if(m_apObject[nCntObject] == NULL)
		{
			// ��������
			m_apObject[nCntObject] = this;
			
			// �I�u�W�F�N�gID�̓o�^
			m_nID = nCntObject;

			// �I�u�W�F�N�g���J�E���g
			m_nNumObject++;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// OBJ�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CObject::~CObject(void)
{
	m_nNumObject--;		// �I�u�W�F�̐�����
}

//-----------------------------------------------------------------------------
// OBJ�̔j��
//-----------------------------------------------------------------------------
void CObject::Release(void)
{
	// ������ID��ۑ�
	int nID = m_nID;

	// �����A�h���X��NULL����Ȃ����
	if( m_apObject[ nID ] != NULL )
	{
		delete m_apObject[ nID ];		// �j��
		m_apObject[ nID ] = NULL;		// NULL���
	}
}

//------------------------------------------------------------------------------
// �S�X�V
//------------------------------------------------------------------------------
void CObject::UpdateAll(void)
{
	for(int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���������̃N���X�������Ă�����
		if(m_apObject[nCntObject] != NULL)
		{
			// �X�V����
			m_apObject[nCntObject]->Update();
		}
	}
}

//------------------------------------------------------------------------------
// �S�`��
//------------------------------------------------------------------------------
void CObject::DrawAll(void)
{
	for(int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���������̃N���X�������Ă�����
		if(m_apObject[nCntObject] != NULL)
		{
			// �X�V����
			m_apObject[nCntObject]->Draw();
		}
	}
#ifdef _DEBUG
	LOCATE( 1,2 );
	printf("�I�u�W�F�N�g���F%03d", m_nNumObject);
#endif
}

//------------------------------------------------------------------------------
// �S�j��
//------------------------------------------------------------------------------
void CObject::ReleaseAll(void)
{
	for(int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���������̃N���X�������Ă�����
		if(m_apObject[nCntObject] != NULL)
		{
			delete m_apObject[nCntObject];
			m_apObject[nCntObject] = NULL;
		}
	}
}


