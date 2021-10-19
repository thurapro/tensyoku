//=============================================================================
// ���b�V���̑����󏈗� [ sky.cpp ]
//
// �����	: ���� �Y��
//
// �@�\		: ��쐬
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "data.h"
#include "renderer.h"
#include "debugproc.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "sky.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define POLYGON_ANGLE_XZ	(0.0f)	// X��Z�̏����p�x
#define POLYGON_ANGLE_XYZ	(0.0f)	// X��Y��Z�̏����p�x
#define CHANGE_SKY			(1)		// �ォ�����̔��]
#define TEX_XNUM			(3)		// �e�N�X�`��������t���b�v�����邩( X���W )
#define TEX_YNUM			(2)		// �e�N�X�`��������t���b�v�����邩( Y���W )

//=============================================================================
//	�֐���	: CSky
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X����
//=============================================================================
CSky::CSky(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer	= NULL;								// ���_�o�b�t�@������
	m_pIndexBuffer	= NULL;								// �C���f�b�N�X�o�b�t�@������
	m_pTexture		= NULL;								// �e�N�X�`���|�C���^������
	m_nVerTexMax	= 0;								// ���_��������
	m_nIndexMax		= 0;								// �Y����������
	m_nTexNum		= -1;								// �e�N�X�`���ԍ�������
	m_pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��̈ʒu������
	m_rot	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��̌���������
	m_scl	= D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// ��̑傫��������
	ZeroMemory(&m_DataSky, sizeof(m_DataSky) );			// ��f�[�^������
}

//=============================================================================
//	�֐���	: CSky
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CSky::~CSky(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Create
//	�߂�l	: ��̃|�C���^
//	����	: �|���S��(���A����), �|���S���̐�(���A�c), �|���S���̔��a, �e�N�X�`���ԍ� 
//	�@�\	: ��̏�����
//=============================================================================
CSky* CSky::Create(float fPolygonWidth, float fPolygonHeight,		
					int nNumX, int nNumY, float fR, 
					USHORT nTexNum)
{
	HRESULT hr;			// ����			
	CSky *pSky = NULL;	// ��|�C���^�錾
	
	// ��C���X�^���X����
	NEW_TYPE(pSky, CSky);								// �������m��
	hr = pSky->Init(fPolygonWidth, fPolygonHeight, 
					 nNumX, nNumY, fR, nTexNum);		// �󏉊��� 
	if( FAILED(hr) )									// �G���[�`�F�b�N
	{
		return NULL;									// �G���[�R�[�h
	}
	return pSky;										// ����R�[�h
}

//=============================================================================
//	�֐���	: CreateLoad
//	�߂�l	: ��̃|�C���^
//	����	: ��f�[�^, �摜�ԍ� 
//	�@�\	: ��̍쐬 & �f�[�^�ǂݍ���, �摜�ԍ��ݒ�
//=============================================================================
CSky* CSky::CreateLoad(SKY dataSky, USHORT nTexNum)
{
	HRESULT hr;						// ����			
	CSky *pSky = NULL;	// ��|�C���^�錾
	
	// �������m��
	NEW_TYPE(pSky, CSky);	

	// �f�[�^�ǂݍ���
	pSky->LoadData(dataSky);	// ��f�[�^�ǂݍ���
	
	// ������
	hr = pSky->Init(dataSky.fWidth, dataSky.fHeight,
					dataSky.nNumX,  dataSky.nNumY, 
					dataSky.fR, nTexNum);	// �󏉊���
	
	pSky->SetPosition(dataSky.pos);			// �ʒu�ݒ�
	pSky->SetRotition(dataSky.rot);			// �����ݒ�

	if( FAILED(hr) )
	{
		// ���������s
		return NULL;
	}
	return pSky;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: �|���S��(���A����), �|���S���̐�(���A�c), �|���S���̔��a, ��ɍ��̂�,�e�N�X�`���ԍ�
//	�@�\	: ��̏�����
//=============================================================================
HRESULT CSky::Init(float fPolygonWidth, float fPolygonHeight,		
					int nNumX, int nNumY, float fR, 
					USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;					// �f�[�^�擾�p
	CTexture	*pTex	= NULL;					// �e�N�X�`���擾�p

	// �󏉊���
	m_pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);		// ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��̌���
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// ��̑傫��


	// �摜�ݒ�
	SetTextureNum(nTexNum);

	// �|���S���̑傫���ۑ�
	m_DataSky.fWidth = fPolygonWidth;	// �|���S���̕��ۑ�
	m_DataSky.fHeight = fPolygonHeight;	// �|���S���̍����ۑ�

	// �|���S�����ۑ�
	m_DataSky.nNumX = nNumX;			// ���̃|���S�����ۑ�
	m_DataSky.nNumY = nNumY;			// �c�̃|���S�����ۑ�

	// �|���S���̔��a�ۑ�
	m_DataSky.fR = fR;					// ���a�ۑ�
	
	// ���_���쐬
	hr = MakeVerTex(fPolygonWidth , fPolygonHeight, fR);		
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	return S_OK;		// ����R�[�h
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: ��̔j��
//=============================================================================
void CSky::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// ���_�o�b�t�@�j��
	SALF_RELEASE(m_pIndexBuffer);		// �C���f�b�N�X�o�b�t�@�j��
	Release();							// ������X�g�\������j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: ��̍X�V
//=============================================================================
void CSky::Update(void)
{

}

//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: ��̕`��
//=============================================================================
void CSky::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

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
	pRenderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_mtxWorld );	

	// �����_�[�X�e�[�g�Ɛݒ�
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		// ���C�g������

	// ���_���ݒ�
	pRenderer->GetDevice()->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//  ���_�o�b�t�@�̃Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pRenderer->GetDevice()->SetIndices(m_pIndexBuffer);

	// �e�N�X�`���̃Z�b�g
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// �v���~�e�B�u�\��
	pRenderer->GetDevice()->DrawIndexedPrimitive
				( CManager::GetDebug()->GetPolygonLine() ,	// �v���~�e�B�u�̎��
				0 ,								// �O�p�`�̐�
				0 ,
				m_nVerTexMax ,					// ���_�̌��i���_�o�b�t�@�j
				0 ,
				m_nIndexMax - 2 );				// �v���~�e�B�u�̐�

	// �����_�[�X�e�[�g���������ݒ�ɖ߂�
	pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);	// ���C�g�L����

	CManager::GetDebug()->Print("��f���Ă��\n");
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CSky::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu�ݒ�
	m_DataSky.pos = m_pos;						// ���݈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CSky::SetPosition(D3DXVECTOR3 pos)
{ 
	m_pos = pos;				// �ʒu�ݒ�
	m_DataSky.pos = m_pos;		// �ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CSky::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// �����ݒ�
	m_DataSky.rot = m_rot;						// ���݌����ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CSky::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// �����ݒ�
	m_DataSky.rot = m_rot;		// ���݌����ۑ�
}

//=============================================================================
// �֐���	: LoadData
// �߂�l	: HRESULT
// �����l	: ��f�[�^
// �@�\		: ��f�[�^�ǂݍ���
//=============================================================================
void CSky::LoadData(SKY dataSky)
{
	m_DataSky = dataSky;	// ��f�[�^���
}

//=============================================================================
// �֐��� : MakeVerTex
// �߂�l : HRESULT
// ���� : �|���S��(��, ����), ���a 
// �@�\ : ���_�o�b�t�@�쐬
//=============================================================================
HRESULT CSky::MakeVerTex(float fPolygonWidth , float fPolygonHeight, float fR)
{
	// �ϐ��錾 
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������

	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_���v�Z
	m_nVerTexMax = ( (m_DataSky.nNumX + 1) * (m_DataSky.nNumY + 1) );	// ���̃|���S���� + 1 * �c�̃|���S���� + 1

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
	float	fAngleXZ		= POLYGON_ANGLE_XZ;			// X��Z�̊p�x		�~���ɂ���
	float	fAngleXYZ		= POLYGON_ANGLE_XYZ;		// X��Y��Z�̊p�x	���̂ɂ���
	float	fAngleXZSum		= (D3DX_PI * 2) / m_DataSky.nNumX;	// X��Y�̊p�x���Z
	float	fAngleXYZSum	= D3DX_PI / m_DataSky.nNumY;		// X��Y��Z�̊p�x���Z
	int		nP				= 0;						// �|���S���J�E���^�[ 

	// ���_���W�ݒ�
	for( int y = 0; y < m_DataSky.nNumY + 1; y++, fAngleXYZ += fAngleXYZSum )
	{
		// �c�̖�����
		for( int x = 0; x < m_DataSky.nNumX + 1; x++, nP++, fAngleXZ += fAngleXZSum )
		{
			// ���̖�����
			pVtx[nP].vtx		= D3DXVECTOR3( -cosf(fAngleXYZ) * cosf(fAngleXZ) * fR, 
												sin(fAngleXYZ)  * fR, 
												cosf(fAngleXYZ) * sinf(fAngleXZ) * fR);	// ���_���W�ݒ�

			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);							// ���_�F�ݒ�
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);								// �@���ݒ�
		}
		fAngleXZ	= POLYGON_ANGLE_XZ;		// �p�x��������
	}

	nP = 0;		// �|���S���J�E���^�[������

	// �e�N�X�`���̕ϐ�
	float fTexX			= 0.0f;							// �e�N�X�`�����W��X��
	float fTexY			= 0.0f;							// �e�N�X�`�����W��Y��
	float fTexWidth		= 1.0f / m_DataSky.nNumX * TEX_XNUM;	// �e�N�X�`���̕� * ����t���b�v�����邩
	float fTexHeight	= 1.0f / m_DataSky.nNumY * TEX_YNUM;	// �e�N�X�`���̍��� * ����t���b�v�����邩

	// �e�N�X�`�����W�ݒ�
	for( int y = 0; y < m_DataSky.nNumY + 1; y++, fTexY += fTexHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataSky.nNumX + 1; x++, nP++, fTexX += fTexWidth)
		{
			// ���̖�����
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// �e�N�X�`�����W�ݒ�
		}
		fTexX	= 0.0f;			// �e�N�X�`������������	
	}

	// �C���f�b�N�X�̐�													
	m_nIndexMax = ( ( (m_DataSky.nNumX + 1) * 2 ) * m_DataSky.nNumY ) + ( ( m_DataSky.nNumY - 1 ) * 2 );

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
		if( index ==  (( m_DataSky.nNumX * 2 ) + 1)  + gyo )
		{
			// �k�ރ|���S���̐���
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataSky.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataSky.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataSky.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataSky.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// �����������ꍇ
			pIdx[index] =  (m_DataSky.nNumX + 1) + nNum_Gusu;
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


void CSky::SetTextureNum(USHORT nTexNum)
{
	CData *pData = NULL;
	CTexture *pTex = NULL;

		// �e�N�X�`���̃��[�h
	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:				// �^�C�g��
		pData	= CTitle::GetData();		// �^�C�g������f�[�^�擾
		if( pData )
		{
			
		}
		break;
	case CManager::MODE_GAME:				// �Q�[��
		pData	= CGame::GetData();			// �Q�[������f�[�^�擾
		if( pData )
		{
			pTex = pData->GetTexture();		// �Q�[������e�N�X�`���擾
		}
		break;
	case CManager::MODE_RESULT:				// ���U���g
		pData	= CResult::GetData();		// ���U���g����f�[�^�擾
		if( pData )
		{	
			pTex = pData->GetTexture();		// ���U���g����e�N�X�`���擾
		}
		break;
	}

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
		// �e�N�X�`���擾�Ȃ炸
		m_pTexture = NULL;								// �e�N�X�`����NULL��
	}
}