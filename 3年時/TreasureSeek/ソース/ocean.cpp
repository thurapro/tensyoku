//=============================================================================
// ���� [meshfield.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: ���V���̑���3D�I�u�W�F�N�g����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "sceneline.h"
#include "data.h"
#include "renderer.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ocean.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define ANGLE_INIT			(180)															// �����p�x

//=============================================================================
//	�֐���	: COcean
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X����
//=============================================================================
COcean::COcean(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// �C���X�^���X����
	m_pTexture	= NULL;							// �e�N�X�`��NULL������
	m_nTexNum	= -1;							// �e�N�X�`���ԍ�������
	m_fAngle	= D3DX_PI / 2;					// �C�̊p�x
	m_nTimeCnt	= 0;							// �g���オ�鎞��
	m_pVertex	= NULL;							// ���_�쐬
	m_pNor		= NULL;							// �ʂ̖@��
	ZeroMemory(&m_DataOcean, sizeof(OCEAN));	// �\���̏�����
}

//=============================================================================
//	�֐���	: ~COcean
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
COcean::~COcean(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �C�|�C���^
// �����l	: �|���S���̑傫��(��, ���s), �|���S���̐�(�c, ��), �摜�ԍ�
// �@�\		: �C���쐬
//=============================================================================
COcean *COcean::Create(float fPolygonWidth, float fPolygonLength, 
					   int nNumX , int nNumZ, USHORT nTexNum)
{
	HRESULT hr;
	COcean *pOcean = NULL;
	NEW_TYPE(pOcean, COcean);
	hr = pOcean->Init(fPolygonWidth, fPolygonLength, nNumX, nNumZ, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pOcean;
}

//=============================================================================
// �֐���	: CreateLoad
// �߂�l	: �C�|�C���^
// �����l	: �C�f�[�^
// �@�\		: �C���쐬 & �ǂݍ���
//=============================================================================
COcean *COcean::CreateLoad(OCEAN dataOcean)
{
	// �ϐ��錾
	COcean	*pOcean = NULL;
	bool	bLoad = false;
	
	// �C�C���X�^���X����
	NEW_TYPE(pOcean, COcean);

	// �C�f�[�^�ǂݍ���
	bLoad = pOcean->LoadData(dataOcean);

	if( bLoad == false )
	{
		// �ǂݍ��ݎ��s
		return NULL;		// �G���[�R�[�h
	}

	return pOcean;			// ����R�[�h
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT COcean::Init(float fPolygonWidth, float fPolygonLength, 
					int nNumX, int nNumZ, 
					USHORT nTexNum)
{
	///// 3D�I�u�W�F�N�g�����������J�n /////
	// �ϐ��錾
	HRESULT hr; 
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫��������

	SetTexNum(nTexNum);

	// �f�[�^�ۑ�
	m_DataOcean.fWidth = fPolygonWidth;			// �|���S���̕�
	m_DataOcean.fLength = fPolygonLength;		// �|���S���̉��s

	m_DataOcean.nNumX = nNumX;					// �|���S����(��)
	m_DataOcean.nNumZ = nNumZ;					// �|���S����(�c)

	m_nTexNum = nTexNum;						// �e�N�X�`���ԍ��ۑ�

	m_nVerTexMax = ( (m_DataOcean.nNumX + 1) * (m_DataOcean.nNumZ + 1) );

	hr = MakeVerTex(fPolygonWidth, fPolygonLength);
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	SetPosition(m_DataOcean.pos);
	SetRotition(m_DataOcean.rot);

	return S_OK;
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̔j��
//=============================================================================
void COcean::Uninit(void)
{
	SALF_RELEASE(m_pIndexBuffer);			// �Y���j��
	SALF_RELEASE(m_pVertexBuffer);			// ���_�o�b�t�@�j��
	SALF_DELETE_ARRAY(m_pVertex);			// ���_�ۑ��p�ϐ��j��
	SALF_DELETE_ARRAY(m_pNor);				// �@���ۑ��p�ϐ��j��
	Release();								// �C�j��
}

//=============================================================================
//	�֐���	: Update
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̍X�V
//=============================================================================
void COcean::Update(void)
{
	VERTEX_3D *pVtx;										// ���_��
	int		nCnt = 0;
	int i = 0;

	if( m_nTimeCnt > 30 )
	{
		m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
		while( i < m_nVerTexMax )
		{
			pVtx[i].vtx = D3DXVECTOR3( m_pVertex[i].x,
								sinf(m_fAngle) * cosf(m_fAngle) * 100,
									 m_pVertex[i].z);
						
			if( m_fAngle <= D3DX_PI / 6 )
			{
				m_fAngle = D3DX_PI / 2;
			}
			else
			{
				m_fAngle -= D3DX_PI / 10;
			}
			i++;
		}
		m_nTimeCnt = 0;
		NorVertex();
	}
	else
	{
		m_nTimeCnt++;
	}
}

//=============================================================================
//	�֐���	: Draw
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̕`��
//			: �傫�����f
//			: �������f
//			: �ꏊ���f
//			: ���[���h�}�g���b�N�X�̐ݒ�
//			: ���_���ݒ�
//			: �e�N�X�`���Z�b�g
//=============================================================================
void COcean::Draw(void)
{
	///// 3D�I�u�W�F�N�g�̕`�揈���J�n /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//--- �ϐ��錾 ---//
	D3DXMATRIX mtxScl;		// �X�P�[���}�g���b�N�X
	D3DXMATRIX mtxRot;		// ���b�g�}�g���b�N�X
	D3DXMATRIX mtxTrans;	// �g�����X�}�g���b�N�X
	
	D3DXMatrixIdentity(&m_mtxWorld);					// ���[���h�}�g���b�N�X������

	//*********************************
	// �X�P�[�����f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
		
	//*********************************
	// ��]���f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//*********************************
	// �ړ����f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld );

	pDevice->SetTexture(0, m_pTexture);

	///// ���_���ݒ� /////
	pDevice->SetFVF(FVF_VERTEX_3D);

	///// ���_�o�b�t�@�Z�b�g /////
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pIndexBuffer);

	// �v���~�e�B�u�\��
	pDevice->DrawIndexedPrimitive(
							CManager::GetDebug()->GetPolygonLine(),	// �v���~�e�B�u�̎��
							0,										// �ǂ����珑����
							0,
							m_nVerTexMax,
							0,
							m_nIndexMax - 2);						// �|���S����(3�p1��1��)
							
}

//=============================================================================
//	�֐���	: MakeVerTexCylinder
//	�߂�l	: HRESULT
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̒��_�����
//=============================================================================
HRESULT COcean::MakeVerTex(float fPolygonWidth , float fPolygonLength)
{
	///// ���ʕϐ��錾 /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	///// ���_�p�ϐ��錾 /////
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;		// ���_��
	WORD *pIdx;			// �Y������


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
	float	fWidth	= (fPolygonWidth * m_DataOcean.nNumX) / 2;		// �|���S���̕�
	float	fHeight	= (fPolygonLength * m_DataOcean.nNumZ) / 2;		// �|���S���̉��s��
	float	fX		= -fWidth;										// ���_���W��X��
	float	fZ		= fHeight;										// ���_���W��Z��
	int		nP		= 0;											// �|���S���J�E���^�[ 

	NEW_TYPE_ARRAY(m_pVertex, D3DXVECTOR3, m_nVerTexMax);

	// ���_���W�ݒ�
	for( int z = 0; z < m_DataOcean.nNumZ + 1; z++, fZ -= fPolygonLength)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataOcean.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// ���̖�����
			pVtx[nP].vtx		= D3DXVECTOR3(fX, 0, fZ);				// ���_���W�ݒ�
			m_pVertex[nP]		= pVtx[nP].vtx;							// ���_�i�[
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// ���_�F�ݒ�
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �@���ݒ�
		}
		fX		= -fWidth;			// �|���S������������
	}

	nP = 0;		// �|���S���J�E���^�[������

	// �e�N�X�`���̕ϐ�
	float fTexX			= 0.0f;									// �e�N�X�`�����W��X��
	float fTexY			= 0.0f;									// �e�N�X�`�����W��Y��
	float fTexWidth		= 1.0f / m_DataOcean.nNumX * 1;			// �e�N�X�`���̕� * ����t���b�v�����邩
	float fTexHeight	= 1.0f / m_DataOcean.nNumZ * 1;			// �e�N�X�`���̍��� * ����t���b�v�����邩

	// �e�N�X�`�����W�ݒ�
	for( int z = 0; z < m_DataOcean.nNumZ + 1; z++, fTexY -= fTexHeight )
	{
		// �c�̖�����
		for( int x = 0; x < m_DataOcean.nNumX + 1; x++, nP++, fTexX += fTexWidth )
		{
			// ���̖�����
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// �e�N�X�`�����W�ݒ�
		}
		fTexX	= 0.0f;			// �e�N�X�`������������	
	}

	// ���_�o�b�t�@�̃��b�N��
	m_pVertexBuffer->Unlock();

	// �ʂ̐�
	int  PrimitiveNum = (m_DataOcean.nNumX * m_DataOcean.nNumZ) * 2;

	// �ʂ̖@�����i�[
	m_pNor = NULL;

	m_pNor = NEW D3DXVECTOR3[PrimitiveNum];

	// �@���Z�o
	NorVertex();		// �@�����擾

	// �C���f�b�N�X��														
	m_nIndexMax = ( ( (m_DataOcean.nNumX + 1) * 2 ) * m_DataOcean.nNumZ ) + ( ( m_DataOcean.nNumZ - 1 ) * 2 );

	// �C���f�b�N�X�o�b�t�@�쐬
	hr = pRenderer->GetDevice()->CreateIndexBuffer( sizeof(WORD) * m_nIndexMax , 
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
		if( index ==  (( m_DataOcean.nNumX * 2 ) + 1)  + gyo )
		{
			// �k�ރ|���S���̐���
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataOcean.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataOcean.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataOcean.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataOcean.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// �����������ꍇ
			pIdx[index] =  (m_DataOcean.nNumX + 1) + nNum_Gusu;
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

//=============================================================================
// �ʒu�ݒ�
//=============================================================================
void COcean::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos.x = fPosX;
	m_pos.y = fPosY;
	m_pos.z = fPosZ;
	m_DataOcean.pos = m_pos;
}

//=============================================================================
// �ʒu�ݒ�
//=============================================================================
void COcean::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_DataOcean.pos = m_pos;
}

//=============================================================================
// �p�x�ݒ�
//=============================================================================
void COcean::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot.x = fRotX;
	m_rot.y = fRotY;
	m_rot.z = fRotZ;
	m_DataOcean.rot = m_rot;
}

//=============================================================================
// �p�x�ݒ�
//=============================================================================
void COcean::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;
	m_DataOcean.rot = m_rot;
}

//=============================================================================
// �֐���	: SetTexNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜�ԍ��ύX
//=============================================================================
void COcean::SetTexNum(USHORT nTexNum)
{
	// �e�N�X�`���擾
	CTexture *pTex = NULL;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pTex = CTitle::GetData()->GetTexture();
		break;
	case CManager::MODE_GAME:
		pTex = CGame::GetData()->GetTexture();
		break;
	case CManager::MODE_RESULT:
		pTex = CResult::GetData()->GetTexture();
		break;
	default:
		break;
	}

	if( pTex->GetTextureNum() < nTexNum || 
	m_nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = pTex->GetTexture(nTexNum);
	}

	m_DataOcean.nTexNum = nTexNum;
}


void COcean::NorVertex(void)
{
	VERTEX_3D *pVtx;					// ���_��
	D3DXVECTOR3 Vector0;				// �x�N�g��
	D3DXVECTOR3 Vector1;				// �x�N�g��
	D3DXVECTOR3 CrossProduct;			// �x�N�g��
	float fLength;						// �x�N�g���̐��K��

	int VectorNum0 = 0;
	int VectorNum1 = 0;
	int nCnt = 0;

	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for(int i = 0; i < m_DataOcean.nNumZ; i++)
	{
		for( int j = 0; j < m_DataOcean.nNumX; j++)
		{	
			////////////////////
			// �_			  //
			// �@�_           //
		//--//�@�@ �_         //
		//V	//       �_       //
		//e	//  ����   �_     //
		//c	//           �_   //
		//0	//             �_ //
			////////////////////
						// |--Vec1
			// �v�Z��

			// �������_�̔ԍ��v�Z
			VectorNum0 = i * (m_DataOcean.nNumX + 1) + j;

			// ������钸�_�̔ԍ��v�Z
			VectorNum1 = (i + 1) * (m_DataOcean.nNumX + 1) + j;

			// �x�N�g�������߂�
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// �������_�̔ԍ��v�Z
			VectorNum0 = (i + 1) * (m_DataOcean.nNumX + 1) + ( j + 1 );

			// �x�N�g�������߂�
			Vector1 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;
				
			// �@���x�N�g�������߂�
			CrossProduct.x = (Vector0.y * Vector1.z) - (Vector0.z * Vector1.y);
			CrossProduct.y = (Vector0.z * Vector1.x) - (Vector0.x * Vector1.z);
			CrossProduct.z = (Vector0.x * Vector1.y) - (Vector0.y * Vector1.x);

			// �@���x�N�g���̐��K��
			fLength = sqrtf( (CrossProduct.x * CrossProduct.x) + (CrossProduct.y * CrossProduct.y) + (CrossProduct.z * CrossProduct.z));

			// �@���x�N�g�����i�[
			m_pNor[nCnt].x = CrossProduct.x / fLength;
			m_pNor[nCnt].y = CrossProduct.y / fLength;
			m_pNor[nCnt].z = CrossProduct.z / fLength;
			nCnt++;

			
				// |---Vec0
			////////////////////
			// �_			  //
			// �@�_ �@����    //
			//�@�@ �_         //---Vec1
			//       �_       //
			//  �@�@   �_     //
			//           �_   //
			//             �_ //
			////////////////////

			// �v�Z��

			// �������_�̔ԍ��v�Z
			VectorNum0 = i * (m_DataOcean.nNumX + 1) + j;
			VectorNum1 = i * (m_DataOcean.nNumX + 1) + (j + 1);
			
			// �x�N�g�������߂�
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// �������_�̔ԍ��v�Z
			VectorNum0 = (i + 1) * (m_DataOcean.nNumX + 1) + (j + 1);

			// �x�N�g�������߂�
			Vector1 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// �@���x�N�g�������߂�
			CrossProduct.x = (Vector0.z * Vector1.y) - (Vector0.y * Vector1.z);
			CrossProduct.y = (Vector0.x * Vector1.z) - (Vector0.z * Vector1.x);
			CrossProduct.z = (Vector0.y * Vector1.x) - (Vector0.x * Vector1.y);

			// �@���x�N�g���̐��K��
			fLength = sqrtf( (CrossProduct.x * CrossProduct.x) + (CrossProduct.y * CrossProduct.y) + (CrossProduct.z * CrossProduct.z));

			// �@���x�N�g�����i�[
			m_pNor[nCnt].x = CrossProduct.x / fLength;
			m_pNor[nCnt].y = CrossProduct.y / fLength;
			m_pNor[nCnt].z = CrossProduct.z / fLength;
			nCnt++;
		}
	}

	nCnt = 0;
	D3DXVECTOR3 wark;
	int Num0 = 0;
	int Num1 = 0;

	// �e���_�̖@�������߂�
	for(int i = 0; i < m_DataOcean.nNumZ + 1 ; i++)
	{
		for( int j = 0; j < m_DataOcean.nNumX + 1; j++)
		{	
			Num0 = i * (m_DataOcean.nNumX * 2 ) + (j * 2) ;
			Num1 = Num0 - ( m_DataOcean.nNumX * 2 );
			if( i == 0 )
			{
				// ��i�ڂ�
				if( j == 0 )
				{
					// ��ԍ��͂�
					wark = ( m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 2;
				}
				else if( j == m_DataOcean.nNumX )
				{
					// ��ԉE�͂�
					wark = m_pNor[ Num0 + 1]; 
				}
				else
				{
					// ����ȊO
					wark = ( m_pNor[ Num0 - 1 ] + m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 3;
				}
			}
			else if( i == m_DataOcean.nNumZ )
			{
				// �Ō�̒i��
				if( j == 0 )
				{
					// ��ԍ��[
					wark = m_pNor[ Num1 + 1 ]; 	
				}
				else if( j == m_DataOcean.nNumX )
				{
					// ��ԉE�[
					wark = ( m_pNor[ Num1 - 2 ] + m_pNor[ Num1 -1 ] ) / 2; 
				}
				else
				{
					// ����ȊO
					wark = ( m_pNor[ Num1 ] + m_pNor[ Num1 - 1 ] + m_pNor[ Num1 - 2 ] ) / 3;
				}
			}
			else
			{
				// ��Ԃł��Ō�̒i�ł��Ȃ��i��
				if( j == 0 )
				{
					// ��ԍ��[	
					wark = ( m_pNor[ Num1 ] + m_pNor[ Num0 + 1 ] + m_pNor[ Num0 ] ) / 3; 	
				}
				else if( j == m_DataOcean.nNumX )
				{
					// ��ԉE�[
					wark = ( m_pNor[ Num1 - 1 ] + m_pNor[ Num1 - 2 ] + m_pNor[ Num0 - 1 ]  ) / 3; 
				}
				else
				{
					// ����ȊO
					wark = ( m_pNor[ Num1 ] + m_pNor[Num1 ] + m_pNor[ Num1 - 2 ] + m_pNor[ Num0 - 1 ] + m_pNor[ Num0 ] + m_pNor[ Num0 + 1] ) / 6;
				}
			}
			pVtx[nCnt].nor.x = wark.x;	// �@������
			pVtx[nCnt].nor.y = wark.y;	// �@������
			pVtx[nCnt].nor.z = wark.z;	// �@������
			nCnt++;
		}
	} 

	// ���_�o�b�t�@�̃��b�N��
	m_pVertexBuffer->Unlock();
}

//=============================================================================
// �֐���	: LoadData 
// �߂�l	: �ǂݍ��݂ł�����
// �����l	: �C�f�[�^
// �@�\		: �f�[�^�ǂݍ���
//=============================================================================
bool COcean::LoadData(OCEAN dataOcean)
{
	HRESULT hr;

	// �f�[�^����
	m_DataOcean = dataOcean;
	
	// ����������
	hr = Init(m_DataOcean.fWidth, m_DataOcean.fLength,
		 m_DataOcean.nNumX, m_DataOcean.nNumZ, m_DataOcean.nTexNum);

	if( FAILED(hr) )
	{
		return false;		// �G���[�R�[�h
	}
	return true;			// ����R�[�h
}