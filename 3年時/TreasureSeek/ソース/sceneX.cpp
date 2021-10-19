//=============================================================================
// ���b�V��3D�I�u�W�F�N�g���� [scene3D.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: ���b�V���̑���3D�I�u�W�F�N�g���쐬
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "manager.h"
#include "data.h"
#include "logo.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "sceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//	�֐���	: CSceneX
//	�߂�l	: �Ȃ�
//	����	: nPriority �D�揇��  objType �I�u�W�F�N�g�̎��
//	�@�\	: �C���X�^���X���� ( ������ )
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̈ʒu
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̌���
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// X�I�u�W�F�N�g�̑傫��
	m_oldpos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̑O��ʒu
	m_oldrot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// X�I�u�W�F�N�g�̑O�����
	m_oldscl		= D3DXVECTOR3(1.0f, 1.0f, 0.0f);		// X�I�u�W�F�N�g�̑O��̑傫��
	m_nModelNum		= MODEL_NUM_INIT;						// ���f���ԍ�
	m_nTextureNum	= TEXTURE_NUM_INIT;						// �e�N�X�`���ԍ�
}

//=============================================================================
//	�֐���	: ~CSceneX
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CSceneX::~CSceneX(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: X�I�u�W�F�N�g ( ���s�����ꍇNULL )
// �����l	: fPosX�@�\���ʒuX��  fPosY �\���ʒuY�� fPosZ �\���ʒuZ��
//				nModelNum ���f���ԍ� nTextureNum �e�N�X�`���ԍ� 
// �@�\		: X�I�u�W�F�N�g�쐬
//=============================================================================
CSceneX *CSceneX::Create(float fPosX, float fPosY, float fPosZ, 
							unsigned int nModelNum,
							unsigned int nTextureNum)
{
	HRESULT hr;					// �G���[�`�F�b�N�ϐ�
	CSceneX *pSceneX = NULL;	// X�I�u�W�F�N�g�N���X�ϐ�
	if( pSceneX == NULL )
	{
		// X�I�u�W�F�N�g���ł��Ă��Ȃ����
		pSceneX = NEW CSceneX;							// X�I�u�W�F�N�g�C���X�^���X����
		hr = pSceneX->Init(fPosX, fPosY, fPosZ,	
							nModelNum, nTextureNum);	// X�I�u�W�F�N�g������
		if( FAILED(hr) )
		{
			// X�I�u�W�F�N�g�̏��������s
			return NULL;								// �����Ԃ��Ȃ�
		}
		return pSceneX;									// X�I�u�W�F�N�g��Ԃ�
	}
	return NULL;	// �����Ԃ��Ȃ�
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: X�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �G���[�܂��͐���
//	����	: fPosX�@�\���ʒuX���@fPosY �\���ʒuY�� fPosZ �\���ʒuZ��
//				nModelNum ���f���ԍ��@nTextrueNum �e�N�X�`���ԍ�
//	�@�\	: X�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CSceneX::Init(float fPosX, float fPosY, float fPosZ, 
							unsigned int nModelNum,
							unsigned int nTextureNum)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// X�I�u�W�F�N�g�̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// X�I�u�W�F�N�g�̌���
	m_scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);			// X�I�u�W�F�N�g�̑傫��
	
	CData			*pData		= NULL;					// �f�[�^�擾�p

	switch( CManager::GetMode() )
	{
	case CManager::MODE_LOGO:				// ���S�̏ꍇ
		pData	= CLogo::GetData();			// ���S����f�[�^�擾
		break;

	case CManager::MODE_TITLE:				// �^�C�g���̏ꍇ
		pData = CTitle::GetData();			// �^�C�g������f�[�^�擾
		break;

	case CManager::MODE_TUTORIAL:			// �`���[�g���A���̏ꍇ
		pData	= CTutorial::GetData();		// �`���[�g���A������f�[�^�擾
		break;

	case CManager::MODE_GAME:				// �Q�[���̏ꍇ
		pData = CGame::GetData();			// �Q�[������f�[�^�擾
		break;

	case CManager::MODE_RESULT:				// ���U���g�̏ꍇ
		pData = CResult::GetData();			// ���U���g����f�[�^�擾
		break;

	case CManager::MODE_RANKING:			// �����L���O�̏ꍇ
		pData = CRanking::GetData();		// �����L���O����f�[�^�擾
		break;

	default:
		break;
	}

	CModel			*pModel		= pData->GetModel();	// ���f���擾
	CTexture		*pTexture	= pData->GetTexture();	// �e�N�X�`���擾

	// ���f���ԍ����Z�b�g
	m_nModelNum = nModelNum;	// ���f���ԍ�
	if( m_nModelNum >pData->GetModel()->GetNumber() 
		|| m_nModelNum < 0 )
	{
		// ���f���ԍ������݂��Ȃ����
		m_pTexture = NULL;			// �G���[�R�[�h
	}
	else
	{
		// ���f���f�[�^�擾
		m_pXmodel = pModel->GetObj(m_nModelNum);
	}

	// �e�N�X�`���ԍ����Z�b�g
	m_nTextureNum = nTextureNum;	// �e�N�X�`���ԍ�
	if( m_nTextureNum > pTexture->GetTextureNum() 
		|| m_nTextureNum < 0 )
	{
		// �e�N�X�`�������݂��Ȃ�
		m_pTexture = NULL;				// �G���[�R�[�h
	}
	else
	{
		// �e�N�X�`���f�[�^�擾
		m_pTexture = pTexture->GetTexture(m_nTextureNum);
	}

	return S_OK;
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: X�I�u�W�F�N�g�̔j��
//=============================================================================
void CSceneX::Uninit(void)
{
	Release();
}

//=============================================================================
//	�֐���	: Update
//	����	: �Ȃ�
//	�@�\	: X�I�u�W�F�N�g�̍X�V
//=============================================================================
void CSceneX::Update(void)
{
	CData	*pData		= NULL;					// �f�[�^�擾�p
	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData = CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData = CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData = CResult::GetData();
		break;
	default:
		break;
	}
	if( CManager::GetInput()->KeyPush(DIK_F1) )
	{
		m_nModelNum += 1;
		if( pData->GetModel()->GetNumber() < m_nModelNum )
		{
			m_nModelNum = 0;
		}
		m_pXmodel = pData->GetModel()->GetObj(m_nModelNum);
	}

	if( CManager::GetInput()->KeyPush(DIK_F3) )
	{
		m_nTextureNum++;
		if( m_nTextureNum >pData->GetTexture()->GetTextureNum() )
		{
			m_nTextureNum = 0;
		}
		m_pXmodel = pData->GetModel()->GetObj(m_nModelNum);
	}
}

//=============================================================================
//	�֐���	: Draw
//	����	: �Ȃ�
//	�@�\	: X�I�u�W�F�N�g�̕`��
//			: �傫�����f
//			: �������f
//			: �ꏊ���f
//			: ���[���h�}�g���b�N�X�̐ݒ�
//			: ���_���ݒ�
//			: �e�N�X�`���Z�b�g
//=============================================================================
void CSceneX::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	// �ϐ��錾
	D3DXMATRIX mtxScl ;			// �傫���̐ݒ�
	D3DXMATRIX mtxRot ;			// �����̐ݒ�
	D3DXMATRIX mtxTrans;		// �ʒu�̐ݒ�
	D3DXMATERIAL *pD3DMat;		// �}�e���A���ݒ�

	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);					// ���[���h�}�g���b�N�X������

	// �X�P�[�����f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
		
	// ��]���f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ����f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�ݒ�
	pRenderer->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld );	

	// X�I�u�W�F�N�g�ݒ�
	pD3DMat = (D3DXMATERIAL *)m_pXmodel.pMatBuff->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_pXmodel.nNumMat; nCntMat++)
	{
		pRenderer->GetDevice()->SetMaterial(&pD3DMat[nCntMat].MatD3D );
		pRenderer->GetDevice()->SetTexture(0, m_pTexture);
		m_pXmodel.pMesh->DrawSubset(nCntMat);
	}
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �ʒu�Z�b�g
//=============================================================================
void CSceneX::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �����Z�b�g
//=============================================================================
void CSceneX::SetRotition(float fPosX, float fPosY, float fPosZ)
{
	m_rot = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}

//=============================================================================
// �֐���	: SetScale
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �傫���Z�b�g
//=============================================================================
void CSceneX::SetScale(float fPosX, float fPosY, float fPosZ)
{
	m_scl = D3DXVECTOR3(fPosX, fPosY, fPosZ);
}