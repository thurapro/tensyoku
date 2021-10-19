//=============================================================================
// �X�e�[�W���� [ stage.cpp ]
//
// �����	: ���� �Y��
//
// �@�\		: �X�e�[�W�ݒ�
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "game.h"
#include "debugproc.h"
#include "stage.h"

//=============================================================================
// �֐���	: stage
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�	
// �@�\		: �C���X�^���X����
//=============================================================================
CStage::CStage(void)
{
	m_bLoad		= false;	// �X�e�[�W�f�[�^�ǂݍ��݃t���O������
	m_pSky		= NULL;		// ��|�C���^������
	m_pMountain	= NULL;		// �R�|�C���^������
	m_pField	= NULL;		// �n�ʃ|�C���^������
	m_pWall		= NULL;		// �ǃ|�C���^������
	m_pTree		= NULL;		// �؃|�C���^������
	m_pGrass	= NULL;		// ���|�C���^������
	m_pOcean	= NULL;		// �C�|�C���^������
	m_Point		= 0;		// ���ݎw���Ă���ʒu
	m_nFiledVerPoint = 0;	// �n�ʂ̒��_���w���Ă���ʒu
	m_nSpeed	= 1;		// �ړ����x
	ZeroMemory(&m_DataSky, sizeof(SKY) );					// ��f�[�^
	ZeroMemory(&m_DataMountain, sizeof(MOUNTAIN) );			// �R�f�[�^
	m_pDataWall  = NULL;	// �ǃf�[�^
	m_pDataField = NULL;	// �n�ʃf�[�^
	m_pDataTree = NULL;		// �؃f�[�^
	m_pDataGrass = NULL;	// ���f�[�^
	m_pDataOcean = NULL;	// �C�f�[�^
	m_nSetObj	= FIELD_OBJ; // ���݉��𒲐߂��Ă���̂�
	m_nTexNum	= 0;		 // �摜�ԍ�
}

//=============================================================================
// �֐���	: ~stage
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CStage::~CStage(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W������
//=============================================================================
HRESULT CStage::Init(void)
{		
		// ��쐬
		/*m_pSky = CSky::Create(100, 200, 20, 20, 90000.0f, 0);
		if( !m_pSky )
		{
			return E_FAIL;
		}

		m_pMountain = CMountain::Create(300, 100, 20, 10, 15000.0f, 1);
		if( !m_pMountain )
		{
			return E_FAIL;
		}
	
		NEW_TYPE_ARRAY(m_pOcean, COcean*, 1);

		m_pOcean[0] = COcean::Create(200, 200, 10, 10, 7);*/


	Load();

	
	// �n�ʍ쐬
	/*m_pField = CField::Create(50, 50, 6, 6, 2);
	if( !m_pField )
	{
		return E_FAIL;
	}*/

	// �ǂ̐��m��
	//NEW_TYPE_ARRAY(m_pDataWall, WALL, m_pDatanWallMax); 
	//NEW_TYPE_ARRAY(m_pWall, CWall*, MAX_WALL);

	//// �Ǎ쐬
	//for( int w = 0; w < m_pDatanWallMax; w++ )
	//{
	//	m_pWall[w] = CWall::Create(50, 50, 2, 2, 3);
	//	if( !m_pWall[w] )
	//	{
	//		return E_FAIL;
	//	}
	//}

	return S_OK;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�j��
//=============================================================================
void CStage::Uninit(void)
{
	CScene::ReleaseAll();					// �V�[���S�j��
	SALF_DELETE_ARRAY(m_pDataField);		// �n�ʂ̊m�ۂ������������j��(�n�ʃf�[�^)
	SALF_DELETE_ARRAY(m_pField);			// �n�ʂ̊m�ۂ������������j��
	SALF_DELETE_ARRAY(m_pDataWall);			// �ǂ̊m�ۂ������������j��(�ǃf�[�^)
	SALF_DELETE_ARRAY(m_pWall);				// �ǂ̊m�ۂ������������j��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�X�V
//=============================================================================
void CStage::Update(void)
{
	char			*strSetObj = NULL;			// ���𒲐߂��Ă���̂���m�点�镶����
	int				nMaxNum = 0;				// ���߂��Ă���I�u�W�F�̍ő吔

	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera			*pCamera = CGame::GetCamera();
	float			rotCamera = pCamera->GetRot();
	bool			bDebug = CManager::GetDebug()->GetDebugMode();

	CScene::UpdateAll();
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�`��
//=============================================================================
void CStage::Draw(void)
{
	CScene::DrawAll();	
}

//=============================================================================
// �֐���	: GetFieldNum
// �߂�l	: �Ȃ�
// �����l	: �����i�[���邽�߂̃|�C���^
// �@�\		: �n�ʂ̐��擾
//=============================================================================
void CStage::GetFieldNum(int &nFieldNum)
{
	nFieldNum = m_ObjNum.nFieldMax;
}

//=============================================================================
// �֐���	: GetWallNum
// �߂�l	: �Ȃ�
// �����l	: �����i�[���邽�߂̃|�C���^
// �@�\		: �ǂ̐��擾
//=============================================================================
void CStage::GetWallNum(int &nWallNum)
{
	nWallNum = m_ObjNum.nWallMax;
}

//=============================================================================
// �֐���	: Load
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�f�[�^�ǂݍ���
//=============================================================================
bool CStage::Load(void)
{
	FILE *fp = NULL;
	int	 nData = 0;

	// �t�@�C�����J��
	fp = fopen("DATA/TEXT/game/stage.dat", "rb");
	if( fp == NULL )
	{
		// �ǂݍ��ݎ��s
		return false;
	}

	// �I�u�W�F�N�g�̐��ǂݍ���
	nData = fread(&m_ObjNum, sizeof(OBJ_NUM), 1, fp); 

	// ��f�[�^�ǂݍ���
	nData = fread(&m_DataSky, sizeof(SKY), 1, fp);
	if( nData <= 0 )
	{
		// �f�[�^�ǂݍ��ݎ��s
		return false;
	}
	if( !m_pSky )
	{
		m_pSky = CSky::CreateLoad(m_DataSky, 0);
	}

	// �R�f�[�^�ǂݍ���
	nData = fread(&m_DataMountain, sizeof(MOUNTAIN), 1, fp);
	if( nData <= 0 )
	{
		// �f�[�^�ǂݍ��ݎ��s
		return false;
	}
	if( !m_pMountain )
	{
		m_pMountain = CMountain::CreateLoad(m_DataMountain, 1);
	}

	if( nData <= 0 )
	{
		// �f�[�^�ǂݍ��ݎ��s
		return false;
	}
	if( m_ObjNum.nFieldMax > 0 )
	{
		m_pDataField = NULL;
		NEW_TYPE_ARRAY(m_pDataField, FIELD, m_ObjNum.nFieldMax);
		
		// �ǂݍ���
		nData = fread(&m_pDataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		NEW_TYPE_ARRAY(m_pField, CField*, m_ObjNum.nFieldMax);

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = NULL;
			m_pDataField[field].fY = NULL;
			NEW_TYPE_ARRAY(fY, float, m_pDataField[field].nVerMax);
			NEW_TYPE_ARRAY(m_pDataField[field].fY, float, m_pDataField[field].nVerMax);
			for( int i = 0; i < m_pDataField[field].nVerMax; i++ )
			{
				m_pDataField[field].fY[i] = 0.0f;
			}
			m_pField[field] = CField::CreateLoad(m_pDataField[field], 2);
			fread(&fY[0], sizeof(float), m_pDataField[field].nVerMax, fp);
			m_pField[field]->SetHeight(&fY[0]);
		}
	}


	if( m_ObjNum.nWallMax > 0 )
	{
		NEW_TYPE_ARRAY(m_pDataWall, WALL, m_ObjNum.nWallMax);

		for( int i = 0; i < m_ObjNum.nWallMax; i++ )
		{
			nData = fread(&m_pDataWall[i], sizeof(WALL), 1, fp);
		}
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		NEW_TYPE_ARRAY(m_pWall, CWall*, m_ObjNum.nWallMax); 
		for(int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_pWall[w] = CWall::CreateLoad(m_pDataWall[w]);
		}
	}

	if( m_ObjNum.nOceanMax > 0 )
	{
		m_pDataOcean = NULL;
		NEW_TYPE_ARRAY(m_pDataOcean, OCEAN, m_ObjNum.nOceanMax);
		
		// �ǂݍ���
		nData = fread(&m_pDataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		NEW_TYPE_ARRAY(m_pOcean, COcean*, m_ObjNum.nOceanMax);
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_pOcean[ocean] = COcean::CreateLoad(m_pDataOcean[ocean]);
		}
	}


	if( m_ObjNum.nTreeMax > 0 )
	{
		m_pDataTree = NULL;
		NEW_TYPE_ARRAY(m_pDataTree, BILLBOARD, m_ObjNum.nTreeMax);
		nData = fread(&m_pDataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}
		NEW_TYPE_ARRAY(m_pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_pTree[tree] = CTree::CreateLoad(m_pDataTree[tree]);
		}
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		m_pDataGrass = NULL;
		NEW_TYPE_ARRAY(m_pDataGrass, BILLBOARD, m_ObjNum.nGrassMax);
		nData = fread(&m_pDataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}
		NEW_TYPE_ARRAY(m_pGrass, CGrass*, m_ObjNum.nGrassMax); 
		for(int grass = 0; grass < m_ObjNum.nGrassMax; grass++ )
		{
			m_pGrass[grass] = CGrass::CreateLoad(m_pDataGrass[grass]);
		}
	}

	// �t�@�C�������
	fclose(fp);

	// �ǂݍ��ݐ���
	return true;
}
	

	





