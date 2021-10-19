//=============================================================================
// ���b�V���̑����R���� [ mountain.cpp ]
//
// �����	: ���� �Y��
//
// �@�\		: �R���쐬
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "manager.h"
#include "data.h"
#include "debugproc.h"
#include "renderer.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "mountain.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define POLYGON_ANGLEXZ	(0.0f)	// X��Z�̏����p�x
#define TEX_XNUM		(2)		// �e�N�X�`��������t���b�v�����邩( X���W )
#define TEX_YNUM		(1)		// �e�N�X�`��������t���b�v�����邩( Y���W )

//=============================================================================
//	�֐���	: CMountain
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X����
//=============================================================================
CMountain::CMountain(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer		= NULL;								// ���_�o�b�t�@������
	m_pIndexBuffer		= NULL;								// �C���f�b�N�X�o�b�t�@������
	m_pTexture			= NULL;								// �e�N�X�`���|�C���^������
	m_nVerTexMax		= 0;								// ���_��������
	m_nIndexMax			= 0;								// �Y����������
	m_nTexNum			= -1;								// �摜�ԍ�������
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �R�̈ʒu������
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �R�̌���������
	m_scl				= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �R�̑傫��������
	ZeroMemory(&m_DataMountain, sizeof(m_DataMountain) );	// �R�f�[�^������
}

//=============================================================================
//	�֐���	: CMountain
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CMountain::~CMountain(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Create
//	�߂�l	: �R�̃|�C���^
//	����	: �|���S��(���A����), �|���S���̐�(���A�c), �|���S���̔��a, �摜�ԍ� 
//	�@�\	: �R�̍쐬
//=============================================================================
CMountain* CMountain::Create(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum)
{
	HRESULT hr;						// ����			
	CMountain *pMountain = NULL;	// �R�|�C���^�錾
	
	// �������m��
	NEW_TYPE(pMountain, CMountain);						// �R�C���X�^���X����	
	hr = pMountain->Init(fPolygonWidth, fPolygonHeight, 
						nNumX, nNumY, fR, nTexNum);		// �R������ 
	if( FAILED(hr) )									// �G���[�`�F�b�N
	{
		return NULL;									// �G���[�R�[�h
	}
	return pMountain;									// ����R�[�h
}

//=============================================================================
//	�֐���	: CreateLoad
//	�߂�l	: �R�̃|�C���^
//	����	: �R�f�[�^, �摜�ԍ� 
//	�@�\	: �R�̍쐬 & �f�[�^�ǂݍ���, �摜�ԍ��ݒ�
//=============================================================================
CMountain* CMountain::CreateLoad(MOUNTAIN dataMountain, USHORT nTexNum)
{
	HRESULT hr;						// ����			
	CMountain *pMountain = NULL;	// �R�|�C���^�錾
	
	// �������m��
	NEW_TYPE(pMountain, CMountain);	

	// �f�[�^�ǂݍ���
	pMountain->LoadData(dataMountain);	// �R�f�[�^�ǂݍ���
	
	// ������
	hr = pMountain->Init(dataMountain.fWidth, dataMountain.fHeight,
					dataMountain.nNumX,  dataMountain.nNumY, 
					dataMountain.fR, nTexNum);	// �R������
	
	pMountain->SetPosition(dataMountain.pos);
	pMountain->SetRotition(dataMountain.rot);

	if( FAILED(hr) )
	{
		// ���������s
		return NULL;
	}
	return pMountain;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: �|���S��(���A����), �|���S���̐�(���A�c), �|���S���̔��a, �摜�ԍ�
//	�@�\	: �R�̏�����
//=============================================================================
HRESULT CMountain::Init(float fPolygonWidth, float fPolygonHeight,		
							int nNumX, int nNumY, float fR, 
							USHORT nTexNum)
{
	HRESULT hr;
	CData		*pData	= NULL;				// �f�[�^�擾�p
	CTexture	*pTex	= NULL;				// �e�N�X�`���擾�p

	// �R������
	m_pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);	// �R�̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �R�̌���
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f );	// �R�̑傫��

	// �摜�ݒ�
	SetTextureNum(nTexNum);

	// �|���S���̑傫���ۑ�
	m_DataMountain.fWidth = fPolygonWidth;		// �|���S���̕��ۑ�
	m_DataMountain.fHeight = fPolygonHeight;	// �|���S���̍����ۑ�

	// �|���S�����ۑ�
	m_DataMountain.nNumX = nNumX;	// ���̃|���S�����ۑ�
	m_DataMountain.nNumY = nNumY;	// �c�̃|���S�����ۑ�

	// �|���S���̔��a�ۑ�
	m_DataMountain.fR = fR;			// ���a�ۑ�

	// ���_���쐬
	hr = MakeVerTex(fPolygonWidth , fPolygonHeight, fR);		
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	return S_OK;		// ����R�[�h
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �R�̔j��
//=============================================================================
void CMountain::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);			// ���_�o�b�t�@�j��
	SALF_RELEASE(m_pIndexBuffer);			// �C���f�b�N�X�o�b�t�@�j��
	Release();								// �R�����X�g�\������j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �R�̍X�V
//=============================================================================
void CMountain::Update(void)
{

}

//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �R�̕`��
//=============================================================================
void CMountain::Draw(void)
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

	// �����_�[�X�e�[�g�ݒ�
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 150);
	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);		// 150����ł���̂Ȃ�`�悵�Ȃ�

	// ���_���ݒ�
	pRenderer->GetDevice()->SetFVF( FVF_VERTEX_3D );	// ���_�t�H�[�}�b�g��3D���W�ƐF�ɐݒ�

	//  ���_�o�b�t�@�̃Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pRenderer->GetDevice()->SetIndices(m_pIndexBuffer);

	// �e�N�X�`���̃Z�b�g
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// �v���~�e�B�u�\��
	pRenderer->GetDevice()->DrawIndexedPrimitive
				( CManager::GetDebug()->GetPolygonLine() ,			// �v���~�e�B�u�̎��
				0 ,								// �O�p�`�̐�
				0 ,
				m_nVerTexMax ,					// ���_�̌��i���_�o�b�t�@�j
				0 ,
				m_nIndexMax - 2 );				// �v���~�e�B�u�̐�

	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	CManager::GetDebug()->Print("�w�i�f���Ă��\n");
}

//=============================================================================
// �֐���	: SetTextureNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜��ύX
//=============================================================================
void CMountain::SetTextureNum(USHORT nTexNum)
{
	CData		*pData	= NULL;					// �f�[�^�擾�p
	CTexture	*pTex	= NULL;					// �e�N�X�`���擾�p

	// �e�N�X�`���̃��[�h
	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:				// �^�C�g��
		pData	= CTitle::GetData();		// �^�C�g������f�[�^�擾
		if( pData )
		{
			pTex = pData->GetTexture();		// �^�C�g������e�N�X�`���擾
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
			m_nTexNum	= nTexNum;						// �摜�ԍ��ۑ�
			m_pTexture	= pTex->GetTexture(m_nTexNum);	// �e�N�X�`���擾
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
void CMountain::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu�ݒ�
	m_DataMountain.pos = m_pos;					// ���݂̈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CMountain::SetPosition(D3DXVECTOR3 pos)
{ 
	m_pos = pos;					// �ʒu�ݒ�
	m_DataMountain.pos = m_pos;		// ���݂̈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CMountain::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// �����ݒ�
	m_DataMountain.rot = m_rot;					// ���݂̌����ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CMountain::SetRotition(D3DXVECTOR3 rot)
{ 
	m_rot = rot;					// �����ݒ�
	m_DataMountain.rot = m_rot;		// ���݂̌����ۑ�
}

//=============================================================================
// �֐���	: LoadData
// �߂�l	: HRESULT
// �����l	: �R�f�[�^
// �@�\		: �R�f�[�^�ǂݍ���
//=============================================================================
void CMountain::LoadData(MOUNTAIN dataMountain)
{
	m_DataMountain = dataMountain;	// �R�f�[�^���
}

//=============================================================================
// �֐��� : MakeVerTex
// �߂�l : HRESULT
// ���� : �|���S��(��, ����), ���a 
// �@�\ : ���_�o�b�t�@�쐬
//=============================================================================
HRESULT CMountain::MakeVerTex(float fPolygonWidth , float fPolygonHeight, float fR)
{
	// �ϐ��錾 
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������

	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_���v�Z
	m_nVerTexMax = ( (m_DataMountain.nNumX + 1) * (m_DataMountain.nNumY + 1) );	// ���̃|���S���� + 1 * �c�̃|���S���� + 1
	
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
	float	fY			= fPolygonHeight * m_DataMountain.nNumY;				// ���_���W��Y��
	float	fAngleXZ	= POLYGON_ANGLEXZ;						// �p�x
	int		nP			= 0;									// �|���S���J�E���^�[ 

	// ���_���W�ݒ�
	for( int y = 0; y < m_DataMountain.nNumY + 1; y++, fY -= fPolygonHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataMountain.nNumX + 1; x++, nP++, fAngleXZ += (D3DX_PI * 2) / m_DataMountain.nNumX )
		{
			// ���̖�����
			pVtx[nP].vtx		= D3DXVECTOR3( -cosf(fAngleXZ) * fR, 
												fY, 
												sinf(fAngleXZ) * fR);	// ���_���W�ݒ�
			
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// ���_�F�ݒ�
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// �@���ݒ�
		}
		fAngleXZ = POLYGON_ANGLEXZ;		// �p�x������
	}

	nP = 0;		// �|���S���J�E���^�[������

	// �e�N�X�`���̕ϐ�
	float fTexX			= 0.0f;							// �e�N�X�`�����W��X��
	float fTexY			= 0.0f;							// �e�N�X�`�����W��Y��
	float fTexWidth		= 1.0f / m_DataMountain.nNumX * TEX_XNUM;	// �e�N�X�`���̕�
	float fTexHeight	= 1.0f / m_DataMountain.nNumY * TEX_YNUM;	// �e�N�X�`���̍���

	// �e�N�X�`�����W�ݒ�
	for( int y = 0; y < m_DataMountain.nNumY + 1; y++, fTexY += fTexHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataMountain.nNumX + 1; x++, nP++, fTexX += fTexWidth)
		{
			// ���̖�����
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// �e�N�X�`�����W�ݒ�
		}
		fTexX	= 0.0f;			// �e�N�X�`������������	
	}

	// �C���f�b�N�X�̐�													
	m_nIndexMax = ( ( (m_DataMountain.nNumX + 1) * 2 ) * m_DataMountain.nNumY ) + ( ( m_DataMountain.nNumY - 1 ) * 2 );

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
		if( index ==  (( m_DataMountain.nNumX * 2 ) + 1)  + gyo )
		{
			// �k�ރ|���S���̐���
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataMountain.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataMountain.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataMountain.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataMountain.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// �����������ꍇ
			pIdx[index] =  (m_DataMountain.nNumX + 1) + nNum_Gusu;
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
