//=============================================================================
// ���� [sceneBillboard.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: �r���{�[�h�쐬
//=============================================================================
#include "manager.h"
#include "data.h"
#include "stage.h"
#include "sceneBillboard.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_BILLBOARD	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define VERTEX_MAX				( 2 )																// ���_�o�b�t�@�ݒ�e��

//=============================================================================
// �֐���	: CBillboard
// �߂�l	: �Ȃ�
// ����		: �v���C�I���e�B�ԍ�
// �@�\		: �C���X�^���X����
//=============================================================================
CBillboard::CBillboard(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// �C���X�^���X����
	m_pTexture = NULL;

	// �r���{�[�h�f�[�^������
	ZeroMemory(&m_DataBillboard, sizeof(BILLBOARD) );
}

//=============================================================================
// �֐���	: CBillboard
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CBillboard::~CBillboard(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: float fWidth : ��
//			: float fHeight: ����
// �@�\		: �r���{�[�h�쐬
//=============================================================================
CBillboard *CBillboard::Create(float fWidth, float fHeight, 
								USHORT nTexNum)
{
	HRESULT	hr;
	CBillboard *pBillboard;
	pBillboard = NEW CBillboard;
	hr = pBillboard->Init(fWidth, fHeight, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pBillboard;
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: float fWidth : ��
//			: float fHeight: ����
// �@�\		: �r���{�[�h�쐬
//=============================================================================
CBillboard *CBillboard::CreateLoad(BILLBOARD dataBillboard)
{
	// �ϐ��錾
	HRESULT	hr;
	bool		bLoad = true;
	CBillboard *pBillboard = NULL;
	
	// �������m��
	NEW_TYPE(pBillboard, CBillboard);	// �r���{�[�h�C���X�^���X����

	// �f�[�^�ǂݍ���
	bLoad = pBillboard->LoadData(dataBillboard);
	if( bLoad == false )
	{
		return NULL;		// �G���[�R�[�h
	}

	// ������
	hr = pBillboard->Init(dataBillboard.fWidth, dataBillboard.fHeight, 
							dataBillboard.nTexNum);
	if( FAILED(hr) )
	{
		return NULL;		// �G���[�R�[�h
	}

	return pBillboard;		// ����R�[�h
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �r���{�[�h������
//=============================================================================
HRESULT CBillboard::Init(void)
{
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: D3DXVECTOR3 �ʒu( X, Y, Z )
//			: float fWidth : ��
//			: float fHeight: ���� , �e�N�X�`���ԍ�
// �@�\		: �r���{�[�h������
//=============================================================================
HRESULT CBillboard::Init(float fWidth, float fHeight, USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;				// �f�[�^�擾�p
	CTexture	*pTex	= NULL;				// �e�N�X�`���擾�p

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ݒ�
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �傫���ݒ�

	pData = CManager::GetData();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// �^�C�g��
	//	pData	= CTitle::GetData();		// �^�C�g������f�[�^�擾
	//	break;
	//case CManager::MODE_GAME:				// �Q�[��
	//	pData	= CGame::GetData();			// �Q�[������f�[�^�擾
	//	break;
	//case CManager::MODE_RESULT:				// ���U���g
	//	pData	= CResult::GetData();		// ���U���g����f�[�^�擾
	//	break;
	//}

	if( pData )
	{
		pTex = pData->GetTexture();		// �e�N�X�`���擾
	}

	if( pTex )
	{
		// �e�N�X�`�����擾�ł���
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			m_pTexture = NULL;							// �e�N�X�`����NULL��
		}
		else
		{
			m_nTexNum	= nTexNum;						// �e�N�X�`���ԍ��ۑ�
			m_pTexture	= pTex->GetTexture(m_nTexNum);	// �e�N�X�`���擾
		}
	}
	else
	{
		// �e�N�X�`�����擾�ł��Ȃ�����
		m_pTexture = NULL;								// �e�N�X�`����NULL��
	}

	// �f�[�^�ۑ�
	m_DataBillboard.fWidth = fWidth;					// ��
	m_DataBillboard.fHeight = fHeight;					// ����
	m_DataBillboard.nTexNum = nTexNum;					// �摜�ԍ�

	m_pos = m_DataBillboard.pos;

	hr = MakeVertex(fWidth, fHeight);					// ���_�쐬
	ERROR_CHACK(hr);									// �G���[�`�F�b�N
	return S_OK;										// ����R�[�h
}


//=============================================================================
// �֐���	: Load
// �߂�l	: �f�[�^���ǂݍ��߂����ǂݍ��߂Ȃ�������
// ����		: �r���{�[�h�f�[�^
// �@�\		: �r���{�[�h�f�[�^�ǂݍ���
//=============================================================================
bool CBillboard::LoadData(BILLBOARD dataBillboard)
{
	m_DataBillboard = dataBillboard;	// �f�[�^���
	return true;						// ����R�[�h
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �r���{�[�h�I��
//=============================================================================
void CBillboard::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// ���_��j�� 
	Release();							// �����[�X
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �r���{�[�h�X�V
//=============================================================================
void CBillboard::Update(void)
{
	CStage *pStage = CManager::GetStage();
	
	CField **pField = pStage->GetField();
	int		nFieldNum = 0;
	pStage->GetFieldNum(nFieldNum);

	if( pField )
	{
		for( int field = 0; field < nFieldNum; field++ )
		{
			// �n�ʂ̍����擾
			m_DataBillboard.pos.y = pField[field]->GetHeight(m_DataBillboard.pos);
		}
	}
	SetPosition(m_DataBillboard.pos);
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �r���{�[�h�`��
//=============================================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X�擾
	CRenderer *pRenderer = CManager::GetRenderer();
	CCamera *pCamera = NULL;
	D3DXMATRIX mtxView; //= pCamera->GetView();
	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;

	pCamera = CManager::GetCamera();

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_TITLE:				// �^�C�g��
	//	//pCamera	= CTitle::GetCamera();		// �^�C�g������J�����擾
	//	break;
	//case CManager::MODE_GAME:				// �Q�[��
	//	pCamera	= CGame::GetCamera();		// �Q�[������J�����擾
	//	break;
	//case CManager::MODE_RESULT:				// ���U���g
	//	//pCamera	= CResult::GetCamera();		// ���U���g����J�����擾
	//	break;
	//}

	if( pCamera ) 
	{
		 mtxView = pCamera->GetView();
	}

	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &m_mtxWorld );		// ���[���h�}�g���b�N�X������

	D3DXMatrixInverse( &m_mtxWorld , NULL , &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �X�P�[�����f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);					// �傫����ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);					// �}�g���b�N�X����
			
	// ��]���f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		// ������ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);					// �}�g���b�N�X����

	// �ړ����f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);			// �ʒu��ݒ�
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans);				// �}�g���b�N�X����

	// �����_�[�X�e�[�g�ݒ�
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// �A���t�@�[�u�����h�g�p
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 250 );					// �A���t�@�[�l�ݒ�
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 250����ł���̂Ȃ�`�悵�Ȃ�
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�e�B���O����

	// ���[���h�}�g���b�N�X�ݒ�
	pRenderer->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);	

	// ���_���ݒ�
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_BILLBOARD);	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//  ���_�o�b�t�@�̃Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0,sizeof(VERTEX_3D) );

	// �e�N�X�`���̃Z�b�g
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// �v���~�e�B�u�\��
	pRenderer->GetDevice()->DrawPrimitive(
				CManager::GetDebug()->GetPolygonLine(),	// �v���~�e�B�u�̎��
				0 ,										// �ŏ��ɏ������_�͉����H
				2);										// �v���~�e�B�u�̐�

	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O�L��
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// �A���t�@�[�e�X�g����
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// ����		: float�^ �ʒu(X, Y, Z)
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CBillboard::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// �ʒu�ݒ�
	m_DataBillboard.pos = m_pos;					// �ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// ����		: D3DXVECTOR3�^ �ʒu(X, Y, Z)
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;					// �ʒu�ݒ�
	m_DataBillboard.pos = m_pos;	// �ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetScale
// �߂�l	: �Ȃ�
// ����		: float�^ �傫��(X, Y, Z)
// �@�\		: �傫���ݒ�
//=============================================================================
void CBillboard::SetScale(float fSclX, float fSclY, float fSclZ)
{
	m_scl = D3DXVECTOR3(fSclX, fSclY, fSclZ);	// �傫���ݒ�
	m_DataBillboard.scl	= m_scl;				// �傫���ۑ�
}

//=============================================================================
// �֐���	: SetScale
// �߂�l	: �Ȃ�
// ����		: D3DXVECTOR3�^ �傫��(X, Y, Z)
// �@�\		: �傫���ݒ�
//=============================================================================
void CBillboard::SetScale(D3DXVECTOR3 scl)
{
	m_scl = scl;					// �傫���ݒ�
	m_DataBillboard.scl	= m_scl;	// �傫���ۑ�
}

//=============================================================================
// �֐���	: SetTexture
// �߂�l	: �Ȃ�
// ����		: float�^ �e�N�X�`�����W �ʒu( X, Y ), �� ���� 
// �@�\		: �傫���ݒ�
//=============================================================================
void CBillboard::SetTexturePos(float fTexX, float fTexY, float fTexWidth, float fTexHeight)
{
	VERTEX_3D *pVtx;	// ���_��

	// ���_���b�N
	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	pVtx[0].tex = D3DXVECTOR2(fTexX, fTexHeight);
	pVtx[1].tex = D3DXVECTOR2(fTexX, fTexY);
	pVtx[2].tex = D3DXVECTOR2(fTexWidth, fTexHeight);
	pVtx[3].tex = D3DXVECTOR2(fTexWidth, fTexY);

	m_pVertexBuffer->Unlock();		// ���_���b�N����
}



//=============================================================================
// �֐���	: SetTextureNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜��ύX
//=============================================================================
void CBillboard::SetTextureNum(USHORT nTexNum)
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
	//		
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

	if( pData )
	{
		pTex = pData->GetTexture();		// �e�N�X�`���擾
	}

	if( pTex )
	{
		// �e�N�X�`�����擾�ł���
		if( pTex->GetTextureNum() < nTexNum || nTexNum < 0 )
		{
			// �摜�ԍ��̍ő吔��菭�Ȃ����
			// �摜�ԍ���0���傫�����
			m_pTexture = NULL;											// �e�N�X�`����NULL��
		}
		else
		{
			// ����ȊO�ł���Ȃ�
			m_DataBillboard.nTexNum	= nTexNum;							// �摜�ԍ��ۑ�
			m_pTexture	= pTex->GetTexture(m_DataBillboard.nTexNum);	// �e�N�X�`���擾
		}
	}
	else
	{
		// �e�N�X�`���擾�Ȃ炸
		m_pTexture = NULL;								// �e�N�X�`����NULL��
	}

	// �e�N�X�`���ԍ��ۑ�
	m_DataBillboard.nTexNum = nTexNum; 
}


//=============================================================================
// �֐���	: MakeVertex
// �߂�l	: HRESUL
// ����		: �傫�� ( ��, ���� )
// �@�\		: �r���{�[�h���_�쐬
//=============================================================================
HRESULT CBillboard::MakeVertex(float fWidth, float fHeight)
{
	// �ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();

	HRESULT hr;					// ���ʕϐ�
	VERTEX_3D *pVtx;			// ���_��

	// ���_�o�b�t�@�쐬����
	hr = pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_BILLBOARD,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL);
	ERROR_CHACK(hr);					

	fWidth /= 2;

	// ���_�o�b�t�@�̃��b�N
	hr = m_pVertexBuffer->Lock(0 , 0 , (void **)&pVtx , 0);
	
	// ���_�o�b�t�@��
	pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0);
	pVtx[2].vtx = D3DXVECTOR3(-fWidth, 0, 0);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, 0, 0);

	// nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// �F���̐ݒ�	( �� , �� , �� , �����x)
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			// ����̃e�N�X�`�����_�ݒ�
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			// �E��̃e�N�X�`�����_�ݒ�
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			// �E���̃e�N�X�`�����_�ݒ�
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			// �����̃e�N�X�`�����_�ݒ�

	hr = m_pVertexBuffer->Unlock();					// ���_�o�b�t�@�̃��b�N����

	// �쐬����
	return S_OK;
}