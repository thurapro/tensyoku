//============================================================================= 
// �I�u�W�F�N�g���X�g���� [ scene.cpp ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: �I�u�W�F�N�g���X�g�Ǘ�
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene *CScene::m_pTop[MAX_LIST] = {NULL};		// �擪�ʒuNULL ������
CScene *CScene::m_pCur[MAX_LIST] = {NULL};		// ���݈ʒuNULL ������ 

//=============================================================================
// �֐���	: CScene
// �߂�l	: �Ȃ� 
// �����l	: int �D�揇��  OBJTYPE �I�u�W�F�N�g�̎��
// �@�\		: �C���X�^���X����
//=============================================================================
CScene::CScene(int nPriority, CScene::OBJTYPE objType)
{
	LinkList(nPriority, objType);
}

//=============================================================================
// �֐���	: UpdateAll
// �߂�l	: �Ȃ� 
// �����l	: �Ȃ�
// �@�\		: ���X�g���̃I�u�W�F�N�g�����ׂčX�V
//=============================================================================
void CScene::UpdateAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// ���X�g����
		CScene *pScene = m_pTop[nList];			// ��Ԑ擪�ɂ���I�u�W�F�N�g��ۑ�
		while(pScene)							// �I�u�W�F�N�g�����݂��Ȃ��Ȃ�܂Ń��[�v
		{
			CScene *pNext = pScene->m_pNext;	// ���̃I�u�W�F�N�g��ۑ�
			pScene->Update();					// ���݂̃I�u�W�F�N�g���X�V
			pScene = pNext;						// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// ���X�g����
		CScene *pScene = m_pTop[nList];			// �擪�ʒu��ۑ�
		while( pScene )							// �I�u�W�F�N�g�����݂��Ȃ��Ȃ�܂Ń��[�v
		{
			// ���̃I�u�W�F�N�g�����݂�����
			CScene *pNext = pScene->m_pNext;	// ���̃I�u�W�F�N�g�ۑ�
			if(pScene->m_bDethFlag == true)
			{
				// �t���O�������Ă�����
				pScene->Uninit();
				pScene->UnlinckList();			// ���X�g����O��		
			}
			pScene = pNext;						// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}
}


//=============================================================================
// �֐���	: DrawAll
// �߂�l	: �Ȃ� 
// �����l	: �Ȃ�
// �@�\		: ���X�g���̃I�u�W�F�N�g�����ׂĕ`��
//=============================================================================
void CScene::DrawAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// ���X�g����
		CScene *pScene = m_pTop[nList];			// ��Ԑ擪�ɂ���I�u�W�F�N�g��ۑ�
		while( pScene )							// �I�u�W�F�N�g�����݂��Ȃ��Ȃ�܂Ń��[�v
		{
			CScene *pNext = pScene->m_pNext;	// ���̃I�u�W�F�N�g��ۑ�
			pScene->Draw();						// ���݂̃I�u�W�F�N�g��`��
			pScene = pNext;						// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}
}

//=============================================================================
// �֐���	: ReleaseAll
// �߂�l	: �Ȃ� 
// �����l	: �Ȃ�
// �@�\		: ���X�g���̃I�u�W�F�N�g�����ׂĔj��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// ���X�g����
		CScene *pScene = m_pTop[nList];			// ��Ԑ擪�ɂ���I�u�W�F�N�g��ۑ�
		while( pScene )							// �I�u�W�F�N�g�����݂��Ȃ��Ȃ�܂Ń��[�v
		{
			CScene *pNext = pScene->m_pNext;	// ���̃I�u�W�F�N�g��ۑ�
			pScene->Uninit();					// ���݂̃I�u�W�F�N�g�̏I������
			pScene->Release();					// �I�u�W�F�N�g��j��
			pScene = pNext;						// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	for( int nList = 0; nList < MAX_LIST; nList++ )
	{
		// ���X�g����
		CScene *pScene = m_pTop[nList];			// �擪�ʒu��ۑ�
		while( pScene )							// �I�u�W�F�N�g�����݂��Ȃ��Ȃ�܂Ń��[�v
		{
			// ���̃I�u�W�F�N�g�����݂�����
			CScene *pNext = pScene->m_pNext;	// ���̃I�u�W�F�N�g�ۑ�
			if(pScene->m_bDethFlag == true)
			{
				// �t���O�������Ă�����
				pScene->UnlinckList();			// ���X�g����O��
			}
			pScene = pNext;						// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

}

//=============================================================================
// �֐���	: LinkList
// �߂�l	: �Ȃ� 
// �����l	: int �D�揇��  OBJTYPE �I�u�W�F�N�g�̎��
// �@�\		: ���X�g�ɓo�^
//=============================================================================
void CScene::LinkList(int nPriority, CScene::OBJTYPE objType)
{
	if( m_pTop[nPriority] == NULL )
	{
		// �����擪�ɂȂ�̃��X�g���o�^����Ă��Ȃ����
		m_pTop[nPriority] = this;		// �擪�͎����ł���
	}
	if( m_pCur[nPriority] == NULL )
	{
		// �����Ō�ɂȂ�̃��X�g���o�^����Ă��Ȃ����
		m_pCur[nPriority] = this;		// �Ō�͎����ł���
	}

	m_pCur[nPriority]->m_pNext = this;	// �Ō�̃��X�g�̌�Ɏ�����o�^

	if( m_pCur[nPriority] == this )
	{
		// �����Ōオ�����ł���̂Ȃ���ɒN�����Ȃ��̂�����
		this->m_pPrev = NULL;			// �����̌���NULL�ɂ���
	}
	else
	{
		m_pPrev = m_pCur[nPriority];
	}

	m_pCur[nPriority] = this;			// �Ō�������ɂ���
	
	this->m_pNext = NULL;				// �����̎��͋��Ȃ�
	
	m_nPriority = nPriority;			// �����̗D��ԍ���ۑ�
	m_objType	= objType;				// �������ǂ̃I�u�W�F�Ȃ̂��ۑ�
	m_bDethFlag = false;				// �����͐����Ă���Ƃ��� 
}

//=============================================================================
// �֐���	: UnlinkList
// �߂�l	: �Ȃ� 
// �����l	: �Ȃ�
// �@�\		: ���X�g����O��
//=============================================================================
void CScene::UnlinckList(void)
{
	CScene *pScene;		// ���݂̃I�u�W�F�N�g�����p
	CScene *pNext;		// �����̎��̃I�u�W�F�N�g��ۑ��p
	CScene *pPrev;		// �����̑O�̃I�u�W�F�N�g��ۑ��p
	pScene = m_pTop[m_nPriority];	// �����D��x�̈�ԍŏ��̃I�u�W�F�N�g����
	while( pScene )
	{
		pNext = pScene->m_pNext;		// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۑ�
		if( pScene == this )
		{
			// �����擪�������������ꍇ
			if(pScene->m_pPrev)
			{
				// ���݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g��NULL�ȏꍇ
				pScene->m_pPrev->m_pNext = pScene->m_pNext;		// ���݂̑O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�Ɍ��݂̃I�u�W�F�̎��̃I�u�W�F�N�g����
			}
			if( pScene->m_pNext )
			{
				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��NULL�ȏꍇ
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;		// ���݂̎��̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�Ɍ��݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g����
			}
			if(pScene == m_pTop[m_nPriority])
			{
				// ���݂̃I�u�W�F�N�g���擪�̃I�u�W�F�N�g�ł���̂Ȃ�
				m_pTop[m_nPriority] = pNext;					// �擪�̃I�u�W�F�N�g�Ɏ��̃I�u�W�F�N�g����
			}
			pScene = pNext;
		}
		pScene = m_pCur[m_nPriority];	// �����D��x�̃I�u�W�F�N�g�̈�Ԍ��̃I�u�W�F�N�g����
		while( pScene )
		{
			pPrev = pScene->m_pPrev;	// ���݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g��ۑ�
			if( pScene == this)
			{
				// �������݂̃I�u�W�F�N�g�������Ȃ�
				if(pScene->m_pPrev)
				{
					// ���݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g��NULL�ȏꍇ
					pScene->m_pPrev->m_pNext = pScene->m_pNext;		// ���݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�Ɍ��݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g����
				}
				if(pScene->m_pNext)
				{
					// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��NULL�ȏꍇ
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;		// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�Ɍ��݂̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g����
				}
				if(pScene == m_pCur[m_nPriority])
				{
					// ���݂̃I�u�W�F�N�g���Ō�̃I�u�W�F�N�g�ł���Ȃ�
					m_pCur[m_nPriority] = pPrev;					// �Ō�̃I�u�W�F�N�g�ɑO�̃I�u�W�F�N�g����
				}
		}
		pScene = pPrev;
		}
	}
	delete this;
}

//=============================================================================
// �֐���	: Release
// �߂�l	: �Ȃ� 
// �����l	: �Ȃ�
// �@�\		: ���X�g����j��
//=============================================================================
void CScene::Release(void)
{
	m_bDethFlag = true;
}
