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
#include "data.h"
#include "stage.h"

//=============================================================================
// �֐���	: stage
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�	
// �@�\		: �C���X�^���X����
//=============================================================================
CStage::CStage(void)
{
	m_bLoad		= false;							// �X�e�[�W�f�[�^�ǂݍ��݃t���O������
	m_pSky		= NULL;								// ��|�C���^������
	m_pMountain	= NULL;								// �R�|�C���^������
	ZeroMemory(&m_pField, sizeof(MAX_OBJECT) );		// �n�ʃ|�C���^������
	ZeroMemory(&m_pWall, sizeof(MAX_OBJECT) );		// �ǃ|�C���^������
	ZeroMemory(&m_pTree	, sizeof(MAX_OBJECT) );		// �؃|�C���^������
	ZeroMemory(&m_pGrass, sizeof(MAX_OBJECT) );		// ���|�C���^������
	ZeroMemory(&m_pOcean, sizeof(MAX_OBJECT) );		// �C�|�C���^������
	m_Point		= 0;								// ���ݎw���Ă���ʒu
	m_nFiledVerPoint = 0;							// �n�ʂ̒��_���w���Ă���ʒu
	m_nSpeed	= 1;								// �ړ����x
	ZeroMemory(&m_ObjNum, sizeof(OBJ_NUM) );		// �I�u�W�F�N�g��
	ZeroMemory(&m_DataField[0], sizeof(FIELD) );		// �n�ʃf�[�^
	ZeroMemory(&m_DataWall[0], sizeof(WALL) );			// �ǃf�[�^
	ZeroMemory(&m_DataTree[0], sizeof(BILLBOARD) );		// �؃f�[�^
	ZeroMemory(&m_DataGrass[0], sizeof(BILLBOARD) );	// ���f�[�^
	ZeroMemory(&m_DataOcean[0], sizeof(OCEAN) );		// �C�f�[�^
	m_nSetObj	= FIELD_OBJ;						// ���݉��𒲐߂��Ă���̂�
	m_nTexNum	= 0;								// �摜�ԍ�
	m_nEditMode = EDITMODE_CREATE;					// �G�f�B�b�g���[�h�ݒ�
	memset(&m_Polygon, 0, sizeof(m_Polygon) );		// �I�u�W�F�N�g�ݒ�
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
	m_pSky = CSky::Create(100, 200, 20, 20, 30000.0f, 0);
	if( !m_pSky )
	{
		return E_FAIL;
	}

	m_pMountain = CMountain::Create(300, 100, 20, 15, 12000.0f, 1);
	if( !m_pMountain )
	{
		return E_FAIL;
	}

	m_pMountain->SetPosition( D3DXVECTOR3(0.0f, -200.0f, 0.0f) );

	for( int obj = 0; obj < MAX_OBJECT; obj++ )
	{
		m_pField[obj] = NULL;
		m_pWall[obj] = NULL;
		m_pTree[obj] = NULL;
		m_pGrass[obj] = NULL;
		m_pOcean[obj] = NULL;
	}

	// �|���S��
	m_Polygon.fWidth	= 10.0f;
	m_Polygon.fHeight	= 10.0f;
	m_Polygon.fLength	= 10.0f;
	m_Polygon.nNumX		= 1;
	m_Polygon.nNumY		= 1;
	m_Polygon.nNumZ		= 1;



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
	CScene::ReleaseAll();						// �V�[���S�j��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�X�V
//=============================================================================
void CStage::Update(void)
{
	char			*strEditMode = NULL;		// ���݃G�f�B�b�g���[�h�̎��
	char			*strSetObj = NULL;			// ���𒲐߂��Ă���̂���m�点�镶����
	int				nMaxNum = 0;				// ���߂��Ă���I�u�W�F�̍ő吔

	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	bool			bDebug = CManager::GetDebug()->GetDebugMode();

	// �f�o�b�O���[�h�ؑ֏���
	if( bDebug == true )
	{
		switch( m_nEditMode )
		{
		case EDITMODE_CREATE:
			EditCreate(pKeyboard);
			strEditMode = "�I�u�W�F�N�g�쐬";
			break;
		
		case EDITMODE_DELETE:
			EditDelete(pKeyboard);
			strEditMode = "�I�u�W�F�N�g�j��";
			break;

		case EDITMODE_MOVE:
			EditMove(pKeyboard);
			strEditMode = "�I�u�W�F�N�g�ړ�";
			break;

		case EDITMODE_CHENGE:
			EditChange(pKeyboard);
			strEditMode = "�I�u�W�F�N�g�摜�ؑ�";
			break;
		default:
			break;
		}


		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			strSetObj = "�n��";
			nMaxNum = m_ObjNum.nFieldMax;
			break;

		case WALL_OBJ:
			strSetObj = "��";
			nMaxNum = m_ObjNum.nWallMax;
			break;

		case TREE_OBJ:
			strSetObj = "��";
			nMaxNum = m_ObjNum.nTreeMax;
			break;

		case GRASS_OBJ:
			strSetObj = "��";
			nMaxNum = m_ObjNum.nGrassMax;
			break;
		
		case OCEAN_OBJ:
			strSetObj = "�C";
			nMaxNum = m_ObjNum.nOceanMax;
			break;

		case MAX_OBJ:
			break;

		default:
			break;
		}

		if( pKeyboard->KeyPush(DIK_7) )
		{
			m_nEditMode = EDITMODE_CREATE;
		}
		else if( pKeyboard->KeyPush(DIK_8) )
		{
			m_nEditMode = EDITMODE_DELETE;
		}
		else if( pKeyboard->KeyPush(DIK_9) )
		{
			m_nEditMode = EDITMODE_MOVE;
		}
		else if( pKeyboard->KeyPush(DIK_0) )
		{
			m_nEditMode = EDITMODE_CHENGE;
		}
		

		if( pKeyboard->KeyPush(DIK_F11) )
		{
			SALF_RELEASE(m_pSky);
			SALF_RELEASE(m_pSky);
			SALF_RELEASE(m_pMountain);

			for( int wall = 0; wall < m_ObjNum.nWallMax; wall++ )
			{
				SALF_RELEASE(m_pWall[wall]);
			}
			
			for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
			{
				SALF_RELEASE(m_pField[field]);
			}

			for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
			{
				SALF_RELEASE(m_pTree[tree]);
			}

			Load();
		}
	

		if( pKeyboard->KeyPush(DIK_UP) )
		{
			m_Point++;
		}
		else if( pKeyboard->KeyPush(DIK_DOWN) )
		{
			if( m_Point > 0 )
			{
				m_Point--;
			}
		}
	
		if( pKeyboard->KeyPush(DIK_F5) )
		{
			if( m_nSetObj < MAX_OBJ - 1 )
			{
				m_nSetObj++;
			}
			m_Point = 0;
		}
		else if( pKeyboard->KeyPush(DIK_F6) )
		{
			if( m_nSetObj > FIELD_OBJ )
			{
				m_nSetObj--;
			}
			m_Point = 0;
		}
	}
	

	CScene::UpdateAll();
	CManager::GetDebug()->Print("���݂̃G�f�B�b�g���[�h %s\n", strEditMode);	
	CManager::GetDebug()->Print("���� %s�𒲐ߒ�\n", strSetObj);
	CManager::GetDebug()->Print("�n�ʂ̐� : %d\n", m_ObjNum.nFieldMax);
	CManager::GetDebug()->Print("�ǂ̐� : %d\n", m_ObjNum.nWallMax);
	CManager::GetDebug()->Print("�؂̐� : %d\n", m_ObjNum.nTreeMax);
	CManager::GetDebug()->Print("���̐� : %d\n", m_ObjNum.nGrassMax);
	CManager::GetDebug()->Print("�C�̐� : %d\n", m_ObjNum.nOceanMax);
	CManager::GetDebug()->Print("�摜�ԍ� %d\n", m_nTexNum);
	CManager::GetDebug()->Print("�|�C���g: %d\n", m_Point);
	CManager::GetDebug()->Print("�ړ����x %d\n", m_nSpeed);
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
// �֐���	: Save
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �X�e�[�W�f�[�^��������
//=============================================================================
HRESULT CStage::Save(void)
{
	FILE *fp		= NULL;
	FILE *fpDebug	= NULL;
	int	 nVtxMax	= 0;
	float *fY		= 0;

	// �f�[�^�擾
	if( m_pSky )
	{
		
		m_DataMountain	= m_pMountain->GetData();	// �R�̃f�[�^�擾
	}

	// �t�@�C�����J��
	fp = fopen("DATA/TEXT/game/stage.dat", "wb");
	if( fp == NULL )
	{
		// �t�@�C���ǂݍ��ݎ��s
		return E_FAIL;
	}
	
	// �X�e�[�W�f�[�^�̏�������
	fwrite(&m_ObjNum, sizeof(OBJ_NUM), 1, fp);

	if( m_pSky )
	{
		m_DataSky		= m_pSky->GetData();		// ��̃f�[�^�擾
		fwrite(&m_DataSky, sizeof(SKY), 1, fp);
	}

	if( m_pMountain )
	{
		m_DataMountain = m_pMountain->GetData();
		fwrite(&m_DataMountain, sizeof(SKY), 1, fp);
	}

	if( m_ObjNum.nFieldMax > 0 )
	{
		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			m_DataField[field] = m_pField[field]->GetData();
		}

		fwrite(&m_DataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp); 

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = m_pField[field]->GetFieldHeight();										// 
			fwrite(&fY[0], sizeof(float), m_DataField[field].nVerMax, fp);				// �n�ʂ̏�������
		}
	}

	if( m_ObjNum.nWallMax > 0 )
	{
		// �ǂ̏�������
		for( int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_DataWall[w] = m_pWall[w]->GetData();
		}
		fwrite(&m_DataWall[0], sizeof(WALL), m_ObjNum.nWallMax, fp);
	}

	if( m_ObjNum.nOceanMax > 0 )
	{
		// �C�̏�������
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_DataOcean[ocean] = m_pOcean[ocean]->GetData();
		}
		fwrite(&m_DataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
	}

	if( m_ObjNum.nTreeMax > 0 )
	{
		// �؂̏�������
		for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_DataTree[tree] = m_pTree[tree]->GetData();
		}
		fwrite(&m_DataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		// ���̏�������
		for( int grass = 0; grass < m_ObjNum.nGrassMax; grass++ )
		{
			m_DataGrass[grass] = m_pGrass[grass]->GetData();
		}
		fwrite(&m_DataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
	}

	// �t�@�C�������
	fclose(fp);

	// �t�@�C���������ݐ���
	return S_OK;
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

	CField **pField = NULL;
	CWall **pWall = NULL;
	CTree **pTree = NULL;
	CGrass **pGrass = NULL;
	COcean **pOcean = NULL;


	// �t�@�C�����J��
	fp = fopen("DATA/TEXT/game/stage.dat", "rb");
	if( fp == NULL )
	{
		// �ǂݍ��ݎ��s
		return false;
	}

	// �X�e�[�W�f�[�^�ǂݍ���
	nData = fread(&m_ObjNum, sizeof(OBJ_NUM), 1, fp);
	if( nData <= 0 )
	{
		// �f�[�^�ǂݍ��ݎ��s
		return false;
	}

	if( !m_pSky )
	{
		fread(&m_DataSky, sizeof(SKY), 1, fp);
		m_pSky = CSky::CreateLoad(m_DataSky, 0);
	}
	if( !m_pMountain )
	{
		fread(&m_DataMountain, sizeof(MOUNTAIN), 1, fp);
		m_pMountain = CMountain::CreateLoad(m_DataMountain, 1);
	}

	if( m_ObjNum.nFieldMax > 0 )
	{
		if( !m_pField )
		{
			NEW_TYPE_ARRAY(pField, CField*, m_ObjNum.nFieldMax);
		}
	
		// �ǂݍ���
		nData = fread(&m_DataField[0], sizeof(FIELD), m_ObjNum.nFieldMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			float *fY = NULL;
			m_DataField[field].fY = NULL;
			NEW_TYPE_ARRAY(fY, float, m_DataField[field].nVerMax);
			NEW_TYPE_ARRAY(m_DataField[field].fY, float, m_DataField[field].nVerMax);
			for( int i = 0; i < m_DataField[field].nVerMax; i++ )
			{
				m_DataField[field].fY[i] = 0.0f;
			}
			m_pField[field] = CField::CreateLoad(m_DataField[field], 2);
			fread(&fY[0], sizeof(float), m_DataField[field].nVerMax, fp);
			m_pField[field]->SetHeight(&fY[0]);
		}
	}

	if( m_ObjNum.nWallMax > 0 )
	{
		for( int i = 0; i < m_ObjNum.nWallMax; i++ )
		{
			nData = fread(&m_DataWall[i], sizeof(WALL), 1, fp);
		}
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		NEW_TYPE_ARRAY(pWall, CWall*, m_ObjNum.nWallMax); 
		for(int w = 0; w < m_ObjNum.nWallMax; w++ )
		{
			m_pWall[w] = CWall::CreateLoad(m_DataWall[w]);
		}
	}

	if( m_ObjNum.nOceanMax > 0 )
	{		
		// �ǂݍ���
		nData = fread(&m_DataOcean[0], sizeof(OCEAN), m_ObjNum.nOceanMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}

		NEW_TYPE_ARRAY(pOcean, COcean*, m_ObjNum.nOceanMax);
		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			m_pOcean[ocean] = COcean::CreateLoad(m_DataOcean[ocean]);
		}
	}


	if( m_ObjNum.nTreeMax > 0 )
	{
		nData = fread(&m_DataTree[0], sizeof(BILLBOARD), m_ObjNum.nTreeMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}
		
		NEW_TYPE_ARRAY(pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			m_pTree[tree] = CTree::CreateLoad(m_DataTree[tree]);
		}
	}

	if( m_ObjNum.nGrassMax > 0 )
	{
		nData = fread(&m_DataGrass[0], sizeof(BILLBOARD), m_ObjNum.nGrassMax, fp);
		if( nData <= 0 )
		{
			// �f�[�^�ǂݍ��ݎ��s
			return false;
		}
		
		NEW_TYPE_ARRAY(pTree, CTree*, m_ObjNum.nTreeMax); 
		for(int grass = 0; grass < m_ObjNum.nTreeMax; grass++ )
		{
			m_pTree[grass] = CTree::CreateLoad(m_DataTree[grass]);
		}
	}


	// �t�@�C�������
	fclose(fp);

	// �ǂݍ��ݐ���
	return true;
}


//=============================================================================
// �֐���	: EditCreate
// �߂�l	: �Ȃ�
// �����l	: CInputKeyboard *pKeyboard
// �@�\		: �I�u�W�F�N�g�쐬
//=============================================================================
void CStage::EditCreate(CInputKeyboard *pKeyboard)
{
	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_ObjNum.nFieldMax < MAX_OBJECT )
			{
				for( int field = 0; field < MAX_OBJECT; field++ )
				{
					if( !m_pField[field] )
					{
						m_pField[field] = CField::Create(m_Polygon.fWidth, m_Polygon.fLength, m_Polygon.nNumX, m_Polygon.nNumZ, 2);
						m_DataField[field] = m_pField[field]->GetData();
						m_ObjNum.nFieldMax++;
						break;
					}
				}
			}
			break;

		case WALL_OBJ:
			if( m_ObjNum.nWallMax < MAX_OBJECT )
			{
				for(int wall = 0; wall < MAX_OBJECT; wall++ )
				{
					if( !m_pWall[wall] )
					{
						m_pWall[wall] = CWall::Create(m_Polygon.fWidth, m_Polygon.fHeight, m_Polygon.nNumX, m_Polygon.nNumY, 3);
						m_DataWall[wall] = m_pWall[wall]->GetData();
						m_ObjNum.nWallMax++;
						break;
					}
				}
			}
			break;

		case TREE_OBJ:
			if( m_ObjNum.nTreeMax < MAX_OBJECT )
			{
				for(int tree = 0; tree < MAX_OBJECT; tree++ )
				{
					if( !m_pTree[tree] )
					{
						m_pTree[tree] = CTree::Create(m_Polygon.fWidth, m_Polygon.fHeight, 3);
						m_DataTree[tree] = m_pTree[tree]->GetData();
						m_ObjNum.nTreeMax++;
						break;
					}
				}
			}
			break;

		case GRASS_OBJ:
			if( m_ObjNum.nGrassMax < MAX_OBJECT )
			{
				for(int grass = 0; grass < MAX_OBJECT; grass++ )
				{
					if( !m_pGrass[grass] )
					{
						m_pGrass[grass] = CGrass::Create(200, 200, 3);
						m_DataGrass[grass] = m_pGrass[grass]->GetData();
						m_ObjNum.nGrassMax++;
						break;
					}
				}
			}
			break;

		case OCEAN_OBJ:
			if( m_ObjNum.nOceanMax < MAX_OBJECT )
			{
				for( int ocean = 0; ocean < MAX_OBJECT; ocean++ )
				{
					if( !m_pOcean[ocean] )
					{
						m_pOcean[ocean] = COcean::Create(m_Polygon.fWidth, m_Polygon.fLength, m_Polygon.nNumX, m_Polygon.nNumZ, 0);
						m_DataOcean[ocean] = m_pOcean[ocean]->GetData();
						m_ObjNum.nOceanMax++;
						break;
					}
				}
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}


	// �|���S���̑傫���ݒ�
	if( pKeyboard->KeyPush(DIK_Y) )
	{
		m_Polygon.fWidth += 10.0f;
	}
	else if( pKeyboard->KeyPush(DIK_H) )
	{
		if( m_Polygon.fWidth > 10.0f )
		{
			m_Polygon.fWidth -= 10.0f;
		}
	}

	if( pKeyboard->KeyPush(DIK_U) )
	{
		m_Polygon.fHeight += 10.0f;
		m_Polygon.fLength += 10.0f;
	}
	else if( pKeyboard->KeyPush(DIK_J) )
	{
		if( m_Polygon.fHeight > 10.0f )
		{
			m_Polygon.fHeight -= 10.0f;
			m_Polygon.fLength -= 10.0f;
		}
	}

	// �|���S���̐��ݒ�
	if( pKeyboard->KeyPush(DIK_I) )
	{
		m_Polygon.nNumX++;
	}
	else if( pKeyboard->KeyPush(DIK_K) )
	{
		if(	m_Polygon.nNumX > 1 )
		{
			m_Polygon.nNumX--;
		}
	}
	if( pKeyboard->KeyPush(DIK_O) )
	{
		m_Polygon.nNumY++;
		m_Polygon.nNumZ++;
	}
	if( pKeyboard->KeyPush(DIK_L) )
	{
		if( m_Polygon.nNumY > 1 )
		{
			m_Polygon.nNumY--;
			m_Polygon.nNumZ--;
		}
	}
	CManager::GetDebug()->Print("�|���S���̕� : %.3f\n", m_Polygon.fWidth);
	CManager::GetDebug()->Print("�|���S���̍��� : %.3f\n", m_Polygon.fHeight);
	CManager::GetDebug()->Print("�|���S���̉��s�� : %.3f\n", m_Polygon.fLength);
	CManager::GetDebug()->Print("�|���S���̉��� : %d\n", m_Polygon.nNumX);
	CManager::GetDebug()->Print("�|���S���̏c�� : %d\n", m_Polygon.nNumY);
	CManager::GetDebug()->Print("�|���S���̉��� : %d\n", m_Polygon.nNumZ);
}

//=============================================================================
// �֐���	: EditDelete
// �߂�l	: �Ȃ�
// �����l	: CInputKeyboard *pKeyboard
// �@�\		: �I�u�W�F�N�g�j��
//=============================================================================
void CStage::EditDelete(CInputKeyboard *pKeyboard)
{
	// �S�I�u�W�F�N�g�폜
	if( pKeyboard->KeyPush(DIK_F10) )
	{
		SALF_RELEASE(m_pSky);
		SALF_RELEASE(m_pMountain);

		for( int field = 0; field < m_ObjNum.nFieldMax; field++ )
		{
			SALF_RELEASE(m_pField[field]);
		}
		m_ObjNum.nFieldMax = 0;

		for( int wall = 0; wall < m_ObjNum.nWallMax; wall++ )
		{
			SALF_RELEASE(m_pWall[wall]);
		}
		m_ObjNum.nWallMax = 0;
			
		for( int tree = 0; tree < m_ObjNum.nTreeMax; tree++ )
		{
			SALF_RELEASE(m_pTree[tree]);
		}
		m_ObjNum.nTreeMax = 0;

		for( int ocean = 0; ocean < m_ObjNum.nOceanMax; ocean++ )
		{
			SALF_RELEASE(m_pOcean[ocean]);
		}
		m_ObjNum.nOceanMax = 0;
	}

	if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				SALF_RELEASE(m_pField[m_Point]);
				m_ObjNum.nFieldMax--;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				SALF_RELEASE(m_pWall[m_Point]);
				m_ObjNum.nWallMax--;
			}
			break;
		
		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				SALF_RELEASE(m_pTree[m_Point]);
				m_ObjNum.nTreeMax--;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				SALF_RELEASE(m_pGrass[m_Point]);
				m_ObjNum.nGrassMax--;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				SALF_RELEASE(m_pOcean[m_Point]);
				m_ObjNum.nOceanMax--;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}
}

//=============================================================================
// �֐���	: EditMove
// �߂�l	: �Ȃ�
// �����l	: CInputKeyboard *pKeyboard
// �@�\		: �I�u�W�F�N�g�ړ�
//=============================================================================
void CStage::EditMove(CInputKeyboard *pKeyboard)
{
	VERTEX_3D		*pVtx;						// ���_��
	CCamera			*pCamera = CManager::GetCamera();
	float			rotCamera = pCamera->GetRot();

	if( pKeyboard->KeyState(DIK_U) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField )
			{
				if( m_pField[m_Point] )
				{
					m_DataField[m_Point].rot.y += D3DX_PI / 50;
				}
			}
			break;

		case WALL_OBJ:
			if( m_pWall )
			{
				if( m_pWall[m_Point] )
				{
					m_DataWall[m_Point].rot.y += D3DX_PI / 50;
				}
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}			
	}
	else if(  pKeyboard->KeyState(DIK_O) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			m_DataField[m_Point].rot.y -= D3DX_PI / 50;
			break;
				
		case WALL_OBJ:
			m_DataWall[m_Point].rot.y -= D3DX_PI / 50;
			break;

		case OCEAN_OBJ:
			m_DataOcean[m_Point].rot.y -= D3DX_PI / 50;
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;
				
		default:
			// �����Ȃ�
			break;
		}
	}

	if( pKeyboard->KeyState(DIK_I) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;
		

		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x += sinf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z += cosf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}
	else if(  pKeyboard->KeyState(DIK_K) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x -= sinf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z -= cosf(rotCamera) * m_nSpeed;
			}
			break;
				

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}
	if( pKeyboard->KeyState(DIK_J) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;


		case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x -= cosf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z += sinf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}	
	}
	else if( pKeyboard->KeyState(DIK_L) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataField[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataWall[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataTree[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataGrass[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.x += cosf(rotCamera) * m_nSpeed;
				m_DataOcean[m_Point].pos.z -= sinf(rotCamera) * m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}

	if( pKeyboard->KeyState(DIK_Y) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.y += m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.y += m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.y += m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.y += m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.y += m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}

	}
	else if( pKeyboard->KeyState(DIK_N) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField[m_Point] )
			{
				m_DataField[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case WALL_OBJ:
			if( m_pWall[m_Point] )
			{
				m_DataWall[m_Point].pos.y -= m_nSpeed;
			}
			break;

			case TREE_OBJ:
			if( m_pTree[m_Point] )
			{
				m_DataTree[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case GRASS_OBJ:
			if( m_pGrass[m_Point] )
			{
				m_DataGrass[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case OCEAN_OBJ:
			if( m_pOcean[m_Point] )
			{
				m_DataOcean[m_Point].pos.y -= m_nSpeed;
			}
			break;

		case MAX_OBJ:
			// �����Ȃ�
			break;

		default:
			// �����Ȃ�
			break;
		}
	}
	if( pKeyboard->KeyPush(DIK_1) )
	{
		m_nSpeed += 1;
	}
	else if( pKeyboard->KeyPush(DIK_2) )
	{
		if( m_nSpeed > 1 )
		{
			m_nSpeed -= 1;
		}
	}

	switch( (SET_OBJ)m_nSetObj )
	{
	case FIELD_OBJ:
		if( m_pField[m_Point] )
		{	
			m_pField[m_Point]->GetVertex()->Lock(0 , 0 , (void **)&pVtx , 0);
			if( pKeyboard->KeyState(DIK_P) )
			{
				pVtx[m_nFiledVerPoint].vtx.y += m_nSpeed;
			} 
			
			else if( pKeyboard->KeyState(DIK_M) )
			{
				if( m_pField[m_Point] )
				{
					pVtx[m_nFiledVerPoint].vtx.y -= m_nSpeed;
				}
			}

			if( pKeyboard->KeyPush(DIK_LEFT) )
			{
				if( m_nFiledVerPoint > 0 )
				{
					m_nFiledVerPoint--;
				}	
			}
			else if( pKeyboard->KeyPush(DIK_RIGHT) )
			{
				if( m_nFiledVerPoint < m_pField[m_Point]->GetData().nVerMax - 1 )
				{
					m_nFiledVerPoint++;
				}
			}
			m_pField[m_Point]->GetVertex()->Unlock();

			m_pField[m_Point]->SetRotition(m_DataField[m_Point].rot);
			m_pField[m_Point]->SetPosition(m_DataField[m_Point].pos);
			CManager::GetDebug()->Print("�n�ʂ̈ʒu : %f %f %f\n", 
										m_DataField[m_Point].pos.x, 
										m_DataField[m_Point].pos.y, 
										m_DataField[m_Point].pos.z );

			CManager::GetDebug()->Print("���_[%d] %f %f %f\n", m_nFiledVerPoint, 
											pVtx[m_nFiledVerPoint].vtx.x, 
											pVtx[m_nFiledVerPoint].vtx.y, 
											pVtx[m_nFiledVerPoint].vtx.z);

		}
		break;

	case WALL_OBJ:
		if( m_pWall[m_Point] )
		{
			m_pWall[m_Point]->SetRotition(m_DataWall[m_Point].rot);
			m_pWall[m_Point]->SetPosition(m_DataWall[m_Point].pos);
			CManager::GetDebug()->Print("�ǂ̈ʒu : %f %f %f\n", 
										m_DataWall[m_Point].pos.x, 
										m_DataWall[m_Point].pos.y, 
										m_DataWall[m_Point].pos.z );
		}
		break;
		
	case TREE_OBJ:
		if( m_pTree[m_Point] )
		{
			m_pTree[m_Point]->SetPosition(m_DataTree[m_Point].pos);
			CManager::GetDebug()->Print("�؂̈ʒu : %f %f %f\n", 
										m_DataTree[m_Point].pos.x, 
										m_DataTree[m_Point].pos.y, 
										m_DataTree[m_Point].pos.z );
		}
		break;

	case GRASS_OBJ:
		if( m_pGrass[m_Point] )
		{
			m_pGrass[m_Point]->SetPosition(m_DataGrass[m_Point].pos);
			CManager::GetDebug()->Print("���̈ʒu : %f %f %f\n", 
										m_DataGrass[m_Point].pos.x, 
										m_DataGrass[m_Point].pos.y, 
										m_DataGrass[m_Point].pos.z );
		}
		break;

	case OCEAN_OBJ:
		if( m_pOcean[m_Point] )
		{
			m_pOcean[m_Point]->SetPosition(m_DataOcean[m_Point].pos);
			CManager::GetDebug()->Print("�C�̈ʒu : %f %f %f\n", 
										m_DataOcean[m_Point].pos.x, 
										m_DataOcean[m_Point].pos.y, 
										m_DataOcean[m_Point].pos.z );
		}

	case MAX_OBJ:
		// �����Ȃ�
		break;

	default:
		// �����Ȃ�
		break;
	}
		

}

//=============================================================================
// �֐���	: EditChange
// �߂�l	: �Ȃ�
// �����l	: CInputKeyboard *pKeyboard
// �@�\		: �I�u�W�F�N�g�̉摜�Ȃǂ�ύX
//=============================================================================
void CStage::EditChange(CInputKeyboard *pKeyboard)
{
	if( pKeyboard->KeyPush(DIK_I) )
	{
		if( m_nTexNum < CManager::GetData()->GetTexture()->GetTextureNum() )
		m_nTexNum++;
	}
	else if( pKeyboard->KeyPush(DIK_K) )
	{
		if( m_nTexNum > 0 )
		{
			m_nTexNum--;
		}
	}
	else if( pKeyboard->KeyPush(DIK_RETURN) )
	{
		switch( (SET_OBJ)m_nSetObj )
		{
		case FIELD_OBJ:
			if( m_pField )
			{
				if( m_pField[m_Point] )
				{
					m_pField[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case WALL_OBJ:
			if( m_pWall )
			{
				if( m_pWall[m_Point] )
				{
					m_pWall[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case TREE_OBJ:
			if( m_pTree )
			{
				if( m_pTree[m_Point] )
				{
					m_pTree[m_Point]->SetTextureNum(m_nTexNum);
				}
			}
			break;
			
		case OCEAN_OBJ:
			if( m_pOcean )
			{
				if( m_pOcean[m_Point] )
				{
					m_pOcean[m_Point]->SetTexNum(m_nTexNum);
				}
			}
			break;

		case MAX_OBJ:
			break;
		}
	}
}

	





