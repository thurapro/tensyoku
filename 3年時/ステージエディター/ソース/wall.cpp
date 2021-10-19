//=============================================================================
// �Ǐ��� [Meshwall.cpp]
//
// ���O	: ���� �Y��
//
// �@�\ : ���b�V���̑�����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene3D.h"
#include "wall.h"
#include "field.h"
#include "data.h"
#include "stage.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define TEX_XNUM			(1)		// �e�N�X�`��������t���b�v�����邩( X���W )
#define TEX_YNUM			(1)		// �e�N�X�`��������t���b�v�����邩( Y���W )

//=============================================================================
//	�֐���	: CWall
//	�߂�l	: �������ł���������
//	����	: �D�揇��, �I�u�W�F�̃^�C�v
//	�@�\	: �C���X�^���X����
//=============================================================================
CWall::CWall(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer	= NULL;								// ���_�o�b�t�@������
	m_pIndexBuffer	= NULL;								// �C���f�b�N�X�o�b�t�@������
	m_pTexture		= NULL;								// �e�N�X�`���|�C���^������
	m_nVerTexMax	= 0;								// ���_��������
	m_nIndexMax		= 0;								// �Y����������
	m_DataWall.nTexNum		= -1;								// �e�N�X�`���ԍ�������
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ǂ̈ʒu������
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ǂ̌���������
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �ǂ̑傫��������
	ZeroMemory(&m_DataWall, sizeof(WALL) );				// �ǃf�[�^������
}

//=============================================================================
//	�֐���	: MeshWallInit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CWall::~CWall(void)
{
}

//=============================================================================
//	�֐���	: Create
//	�߂�l	: �ǃ|�C���^
//	����	: �|���S���̑傫��( ��, ���� ) �|���S����( ��, �c )
//	�@�\	: �Ǐ�����
//=============================================================================
CWall *CWall::Create(float fPolygonWidth, float fPolygonHeight, int nNumX, int nNumY, 
					 USHORT nTexNum)
{
	// �ϐ��錾
	HRESULT hr;				// ����
	CWall *pWall = NULL;	// �ǃ|�C���^

	NEW_TYPE(pWall, CWall);	// �ǃC���X�^���X����
	hr = pWall->Init(fPolygonWidth, fPolygonHeight, nNumX, nNumY, nTexNum);		// �Ǐ�����
	if( FAILED(hr) )
	{
		// �G���[�`�F�b�N
		return NULL;		// �G���[
	}
	return pWall;			// ����R�[�h
}

//=============================================================================
//	�֐���	: CreateLoad
//	�߂�l	: �ǃ|�C���^
//	����	: �ǃf�[�^, �摜�ԍ�
//	�@�\	: �Ǐ�����
//=============================================================================
CWall* CWall::CreateLoad(WALL dataWall)
{
	// �ϐ��錾
	HRESULT	hr;					// ����
	CWall *pWall = NULL;		// �ǃ|�C���^
	
	// �������m��
	NEW_TYPE(pWall, CWall);		// �ǃN���X

	// ������
	pWall->LoadData(dataWall);	// �ǃf�[�^�ǂݍ���

	hr = pWall->Init(dataWall.fWidth, dataWall.fHeight,
					dataWall.nNumX, dataWall.nNumY, 
					dataWall.nTexNum);			// �Ǐ�����
	
	pWall->SetPosition(dataWall.pos);
	pWall->SetRotition(dataWall.rot);

	if( FAILED(hr) )
	{
		// ���������s
		return NULL;
	}
	return pWall;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: ������
//=============================================================================
HRESULT CWall::Init(void)
{
	return S_OK;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �������ł���������
//	����	: �f�o�C�X
//	�@�\	: �Ǐ�����
//=============================================================================
HRESULT CWall::Init(float fPolygonWidth, float fPolygonHeight, int nNumX, int nNumY, 
					USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;				// �f�[�^�擾�p
	CTexture	*pTex	= NULL;				// �e�N�X�`���擾�p

	// �Ǐ�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);		// �ǂ̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ǂ̌���
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f );		// �ǂ̑傫��


	pTex = CManager::GetData()->GetTexture();

	// �e�N�X�`���̃��[�h
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// �^�C�g��
	//	pData	= CTitle::GetData();		// �^�C�g������f�[�^�擾
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// �^�C�g������e�N�X�`���擾
	//	}
	//	break;
	//case CManager::MODE_GAME:				// �Q�[��
	//	pData	= CGame::GetData();			// �Q�[������f�[�^�擾
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// �Q�[������e�N�X�`���擾
	//	}
	//	break;
	//case CManager::MODE_RESULT:				// ���U���g
	//	pData	= CResult::GetData();		// ���U���g����f�[�^�擾
	//	if( pData )
	//	{	
	//		pTex = pData->GetTexture();		// ���U���g����e�N�X�`���擾
	//	}
	//	break;
	//}

	m_DataWall.nTexNum	= nTexNum;						// �e�N�X�`���ԍ��ۑ�

	if( pTex )
	{
		// �e�N�X�`�����擾�ł���
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			m_pTexture = NULL;							// �e�N�X�`����NULL��
		}
		else
		{
			m_pTexture	= pTex->GetTexture(m_DataWall.nTexNum);	// �e�N�X�`���擾
		}
	}
	else
	{
		// �e�N�X�`���擾�Ȃ炸
		m_pTexture = NULL;								// �e�N�X�`����NULL��
	}

	// �|���S���̑傫���ۑ�
	m_DataWall.fWidth	= fPolygonWidth;	// �|���S���̕��ۑ�
	m_DataWall.fHeight	= fPolygonHeight;	// �|���S���̍����ۑ�

	// �|���S�����ۑ�
	m_DataWall.nNumX = nNumX;				// ���̃|���S�����ۑ�
	m_DataWall.nNumY = nNumY;				// �c�̃|���S�����ۑ�
		
	m_DataWall.nTexNum = nTexNum;			// �摜�ԍ��ۑ�

	m_DataWall.pos = m_pos;					// �ʒu�ۑ�
	m_DataWall.rot = m_rot;					// �����ۑ�
	m_DataWall.scl = m_scl;					// �傫���ۑ�

	// ���_���쐬
	hr = MakeVerTex(fPolygonWidth , fPolygonHeight);		
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	return S_OK;		// ����R�[�h
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �ǔj��
//=============================================================================
void CWall::Uninit(void)
{	
	SALF_RELEASE(m_pVertexBuffer);		// ���_�o�b�t�@�̉��
	SALF_RELEASE(m_pIndexBuffer);		// �C���f�b�N�X�o�b�t�@�̉��					
	Release();							// �ǂ��V�[�����X�g�\������j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �ǍX�V
//=============================================================================
void CWall::Update(void)
{
	// �n�ʎ擾
	CStage *pStage  = CManager::GetStage();
	CField **pField = pStage->GetField();
	int		nFieldNum = 0;
	pStage->GetFieldNum(nFieldNum);

	if( pField )
	{
		for( int field = 0; field < nFieldNum; field++ )
		{
			// �n�ʂ̍����擾
			m_DataWall.pos.y = pField[field]->GetHeight(m_DataWall.pos);
		}
	}
	m_DataWall.pos.y += (m_DataWall.fHeight / 4);
	SetPosition(m_DataWall.pos);
}

//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �Ǖ`��
//=============================================================================
void CWall::Draw(void)
{
	// �ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &m_mtxWorld );		// ���[���h�}�g���b�N�X������

	// �X�P�[�����f
	D3DXMatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	D3DXMatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );
		
	// ��]���f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld , &mtxRot );

	// �ړ����f
	D3DXMatrixTranslation( &mtxTrans, m_pos.x, m_pos.y, m_pos.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans );

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );	

	// ���_���ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//  ���_�o�b�t�@�̃Z�b�g
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pIndexBuffer);

	// �e�N�X�`���̃Z�b�g
	pDevice->SetTexture(0, m_pTexture);

	// �v���~�e�B�u�\��
	pDevice->DrawIndexedPrimitive
				( CManager::GetDebug()->GetPolygonLine() ,	// �v���~�e�B�u�̎��
				0 ,											// �O�p�`�̐�
				0 ,
				m_nVerTexMax ,								// ���_�̌��i���_�o�b�t�@�j
				0 ,
				m_nIndexMax - 2 );							// �v���~�e�B�u�̐�

	//CManager::GetDebug()->Print("�ǉf���Ă��\n");
}

//=============================================================================
// �֐���	: SetTextureNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜��ύX
//=============================================================================
void CWall::SetTextureNum(USHORT nTexNum)
{
	CData		*pData	= NULL;					// �f�[�^�擾�p
	CTexture	*pTex	= NULL;					// �e�N�X�`���擾�p

	pTex = CManager::GetData()->GetTexture();	// �摜�擾

	// �e�N�X�`���̃��[�h
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// �^�C�g��
	//	pData	= CTitle::GetData();		// �^�C�g������f�[�^�擾
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// �^�C�g������e�N�X�`���擾
	//	}
	//	break;
	//case CManager::MODE_GAME:				// �Q�[��
	//	pData	= CGame::GetData();			// �Q�[������f�[�^�擾
	//	if( pData )
	//	{
	//		pTex = pData->GetTexture();		// �Q�[������e�N�X�`���擾
	//	}
	//	break;
	//case CManager::MODE_RESULT:				// ���U���g
	//	pData	= CResult::GetData();		// ���U���g����f�[�^�擾
	//	if( pData )
	//	{	
	//		pTex = pData->GetTexture();		// ���U���g����e�N�X�`���擾
	//	}
	//	break;
	//}

	if( pTex )
	{
		// �e�N�X�`�����擾�ł���
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			// �摜�ԍ��̍ő吔��菭�Ȃ����
			// �摜�ԍ���0���傫�����
			m_pTexture = NULL;							// �e�N�X�`����NULL��
		}
		else
		{
			// ����ȊO�ł���Ȃ�
			m_DataWall.nTexNum	= nTexNum;						// �摜�ԍ��ۑ�
			m_pTexture	= pTex->GetTexture(m_DataWall.nTexNum);	// �e�N�X�`���擾
		}
	}
	else
	{
		// �e�N�X�`���擾�Ȃ炸
		m_pTexture = NULL;								// �e�N�X�`����NULL��
	}
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CWall::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu�ݒ�
	m_DataWall.pos = m_pos;						// ���݂̈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CWall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;				// �ʒu�ݒ�
	m_DataWall.pos = m_pos;		// ���݂̈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CWall::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// �����ݒ�
	m_DataWall.rot = m_rot;						// ���݂̌����ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CWall::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// �����ݒ�
	m_DataWall.rot = m_rot;		// ���݂̌����ۑ�
}

//=============================================================================
// �֐���	: SetTexNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜�ݒ�
//=============================================================================
void CWall::SetTexNum(USHORT nTexNum)
{
	// �e�N�X�`���擾
	CTexture *pTex = NULL;

	pTex = CManager::GetData()->GetTexture();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:
	//	pTex = CTitle::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_GAME:
	//	pTex = CGame::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_RESULT:
	//	pTex = CResult::GetData()->GetTexture();
	//	break;
	//case CManager::MODE_RANKING:
	//	pTex = CRanking::GetData()->GetTexture();
	//	break;
	//default:
	//	break;
	//}

	m_DataWall.nTexNum = nTexNum;						// �e�N�X�`���ԍ��ۑ�
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataWall.nTexNum || 
		m_DataWall.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataWall.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}
}

//=============================================================================
// �֐���	: LoadData
// �߂�l	: �Ȃ�
// �����l	: �ǃf�[�^
// �@�\		: �ǃf�[�^�ǂݍ���
//=============================================================================
void CWall::LoadData(WALL dataWall)
{
	m_DataWall = dataWall;		// �f�[�^�ǂݍ���
}

//=============================================================================
// �֐��� : MakeVertex
// �߂�l : HRESULT
// ���� : �f�o�C�X 
// �@�\ : ���_�o�b�t�@�쐬
//=============================================================================
HRESULT CWall::MakeVerTex(float fPolygonWidth , float fPolygonHeight)
{
	// �ϐ��錾 
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������

	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_���v�Z
	m_nVerTexMax = ( (m_DataWall.nNumX + 1) * (m_DataWall.nNumY + 1) );	// ���̃|���S���� + 1 * �c�̃|���S���� + 1

	// ���_�o�b�t�@�쐬����
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_3D) * m_nVerTexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	// ���_�o�b�t�@�̃��b�N
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	// ���_�̕ϐ�
	float	fWidth	= (fPolygonWidth * m_DataWall.nNumX) / 2;		// �|���S���̕�
	float	fHeight	= (fPolygonHeight * m_DataWall.nNumY) / 2;		// �|���S���̍���
	float	fX		= -fWidth;										// ���_���W��X��
	float	fY		= fPolygonHeight * m_DataWall.nNumY;			// ���_���W��Y��
	int		nP		= 0;											// �|���S���J�E���^�[ 

	// ���_���W�ݒ�
	for( int y = 0; y < m_DataWall.nNumY + 1; y++, fY -= fPolygonHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataWall.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// ���̖�����
			pVtx[nP].vtx		= D3DXVECTOR3(fX, fY, 0);				// ���_���W�ݒ�
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// ���_�F�ݒ�
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// �@���ݒ�
		}
		fX		= -fWidth;			// �|���S������������
	}

	nP = 0;		// �|���S���J�E���^�[������

	// �e�N�X�`���̕ϐ�
	float fTexX			= 0.0f;									// �e�N�X�`�����W��X��
	float fTexY			= 0.0f;									// �e�N�X�`�����W��Y��
	float fTexWidth		= 1.0f / m_DataWall.nNumX * TEX_XNUM;	// �e�N�X�`���̕� * ����t���b�v�����邩
	float fTexHeight	= 1.0f / m_DataWall.nNumY * TEX_YNUM;	// �e�N�X�`���̍��� * ����t���b�v�����邩

	// �e�N�X�`�����W�ݒ�
	for( int y = 0; y < m_DataWall.nNumY + 1; y++, fTexY += fTexHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataWall.nNumX + 1; x++, nP++, fTexX -= fTexWidth)
		{
			// ���̖�����
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// �e�N�X�`�����W�ݒ�
		}
		fTexX	= 0.0f;			// �e�N�X�`������������	
	}

	// �C���f�b�N�X�̐�													
	m_nIndexMax = ( ( (m_DataWall.nNumX + 1) * 2 ) * m_DataWall.nNumY ) + ( ( m_DataWall.nNumY - 1 ) * 2 );

	// �C���f�b�N�X�o�b�t�@�쐬
	hr = pRenderer->GetDevice()->CreateIndexBuffer( sizeof(WORD) * m_nIndexMax, 
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&m_pIndexBuffer,
										NULL );
	ERROR_CHACK(hr);		// �G���[�`�F�b�N
	
	// �C���f�b�N�X�o�b�t�@�̃��b�N
	hr = m_pIndexBuffer->Lock( 0 , 0 , (void **)&pIdx , 0);

	int index = 0;			// �C���f�b�N�X�ԍ�
	int gyo = 0;			// �s��
	int polygon = 0;		// �|���S���ԍ�
	int nNum_Kisu = 0;		// �
	int nNum_Gusu = 0;		// ����

	while( index < m_nIndexMax )
	{
		// �܂�Ԃ��n�_�������ꍇ
		if( index ==  (( m_DataWall.nNumX * 2 ) + 1)  + gyo )
		{
			// �k�ރ|���S���̐���
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataWall.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataWall.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataWall.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataWall.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// �����������ꍇ
			pIdx[index] =  (m_DataWall.nNumX + 1) + nNum_Gusu;
			nNum_Gusu++;
			index++;
		}
		else if(  index % 2 == 1 )
		{
			// ��������ꍇ
			pIdx[index] = nNum_Kisu;
			nNum_Kisu++;
			index++;
		}
	}
			
	// �C���f�b�N�X�o�b�t�@�̃��b�N����
	m_pIndexBuffer->Unlock();
		
	// �쐬����
	return (S_OK);
}



