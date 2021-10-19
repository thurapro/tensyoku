//=============================================================================
// �e�N�X�`���ۑ� [ texture.cpp ]
//
// ����� : ���� �Y��
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "renderer.h"
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_STR		(1024)				// �ő啶����
#define DIRECTORY	("DATA/MODEL/");	// �f�B���N�g��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel(void)
{
	m_pModel = NULL;		// ���f���f�[�^�|�C���^������
	m_nModelNum = 0;		// ���f���ԍ�������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// ������
//=============================================================================
HRESULT CModel::Init(char *FileName)
{
	HRESULT hr;

	// ���f���f�[�^��ǂݍ���
	hr = LoardModelData(FileName);
	ERROR_CHACK(hr);					// �G���[�`�F�b�N

	return S_OK;	// ����I��
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	for(unsigned int i = 0; i < m_nModelNum; i++)
	{
		SALF_RELEASE(m_pModel[i].pMesh);
		SALF_RELEASE(m_pModel[i].pMatBuff);
	}
	SALF_DELETE_ARRAY(m_pModel);
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CModel::LoardModelData(char *FileName)
{
	// �ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();
	
	// �f�o�C�X������
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	// ����
	HRESULT hr;

	// �t�@�C����
	char strFile[MAX_STR] = { NULL };

	// �t�@�C���|�C���^ ������
	FILE *fp = NULL;							

	// �t�@�C���ǂݍ���
	fp = fopen(FileName, "r");
	if( fp == NULL)
	{
		// �t�@�C�����Ȃ��ꍇ
		return E_FAIL;
	}

	// �t�@�C���s���擾
	while(true)
	{
		// �t�@�C���̍s���擾
		if(fscanf(fp, "%s", &strFile) != EOF)
		{
			// �s�� = �e�N�X�`���̖���
			m_nModelNum++;	// �s���J�E���g
		}
		else
		{
			// �t�@�C���̒��g�������Ȃ���
			break;
		}
	}

	// �e�N�X�`���ϐ��@���I�m��
	m_pModel = NEW X_FILE[m_nModelNum];

	// �t�@�C����ǂݍ���
	fseek(fp, 0, SEEK_SET);

	// �e�N�X�`���ǂݍ���
	for( unsigned int i = 0; i < m_nModelNum; i++)
	{
		// �e�N�X�`���̖��O���擾
		if(fscanf(fp, "%s", strFile) != EOF)
		{
			// �f�B���N�g��
			char Directory[MAX_STR]  = DIRECTORY;

			// �t�@�C�����ƃf�B���N�g����z�񂷂�
			strcat(Directory, strFile);
			

			// �e�N�X�`���ǂݍ���
			hr = D3DXLoadMeshFromX( Directory ,				// �t�@�C����
									D3DXMESH_SYSTEMMEM,		// ���b�V���̏�����
									pDevice,				// �f�o�C�X
									NULL,					// �אڐ������󂯎��
									&m_pModel[i].pMatBuff,	// �}�e���A���o�b�t�@�̏����󂯎��
									NULL,					// �s��
									&m_pModel[i].nNumMat,	// ���}�e���A����
									&m_pModel[i].pMesh );	// ���b�V��
			if( FAILED(hr) )
			{
				// �w�肵���e�N�X�`�������݂��Ȃ����
				fclose(fp);			// �t�@�C�������
				return E_FAIL;		// ����
			}
		}
	}

	// �t�@�C�������
	fclose(fp);
	return S_OK;					// ����
}
