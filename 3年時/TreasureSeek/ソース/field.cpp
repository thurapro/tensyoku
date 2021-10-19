//=============================================================================
// ���� [meshfield.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: ���V���̑����n�ʐ���
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "sceneline.h"
#include "data.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "field.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define TEX_XNUM			(30)		// �e�N�X�`��������t���b�v�����邩( X���W )
#define TEX_YNUM			(30)		// �e�N�X�`��������t���b�v�����邩( Y���W )

//=============================================================================
//	�֐���	: CField
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X����
//=============================================================================
CField::CField(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// �C���X�^���X����
	m_pVertexBuffer	= NULL;								// ���_�o�b�t�@������
	m_pIndexBuffer	= NULL;								// �C���f�b�N�X�o�b�t�@������
	m_pTexture		= NULL;								// �e�N�X�`���|�C���^������
	m_pNor			= NULL;								// �ʂ̖@���i�[�|�C���^������
	m_ppLine		= NULL;								// �@�����C��������
	m_nVerTexMax	= 0;								// ���_��������
	m_nIndexMax		= 0;								// �Y����������
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �n�ʂ̈ʒu������
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �n�ʂ̌���������
	m_scl			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �n�ʂ̑傫��������
	m_nPoint		= 0;								// ���_�|�C���g������
	m_nSpeed		= 1;								// �X�s�[�h������
	ZeroMemory(&m_DataField, sizeof(FIELD) );			// �n�ʃf�[�^������
	m_DataField.nTexNum		= -1;						// �摜�ԍ�������
}

//=============================================================================
//	�֐���	: ~CField
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CField::~CField(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �n�ʃ|�C���^
//	����	: �|���S���̑傫��(��, ����), ����(��, �c), �e�N�X�`���ԍ�
//	�@�\	: �n�ʂ̍쐬
//=============================================================================
CField *CField::Create( float fPolygonWidth , float fPolygonLength , 
						int nNumX , int nNumZ, USHORT nTexNum)
{
	// �ϐ��錾
	HRESULT hr;				// ����
	CField *pField = NULL;	// �n�ʃ|�C���^	

	// �n�ʐ���
	NEW_TYPE(pField, CField);			
	hr = pField->Init(fPolygonWidth, fPolygonLength, nNumX, nNumZ, nTexNum);	// �n�ʏ�����
	if( FAILED(hr) )
	{
		// �G���[�`�F�b�N
		return NULL;		// �G���[�R�[�h
	}
	return pField;			// ����R�[�h
}

//=============================================================================
//	�֐���	: CreateLoad
//	�߂�l	: �n�ʃ|�C���^
//	����	: �n�ʃf�[�^, �n�ʂ̍���, �e�N�X�`���ԍ�
//	�@�\	: �n�ʂ̍쐬
//=============================================================================
CField *CField::CreateLoad(FIELD dataField, USHORT nTexNum)
{
	// �ϐ��錾
	HRESULT hr;				// ����
	CField *pField = NULL;	// �n�ʃ|�C���^	
	bool	bLoad = true;	// �f�[�^���ǂݍ��߂���

	// �������m��
	NEW_TYPE(pField, CField);							// �n�ʐ���

	// �f�[�^�ǂݍ���
	bLoad = pField->LoadData(dataField);		// �n�ʃf�[�^�ǂݍ���
	if( !bLoad )
	{
		// �ǂݍ��ݎ��s
		return NULL;
	}

	hr = pField->MakeVerTex(dataField.fWidth, dataField.fLength);
	if( FAILED(hr) )
	{
		return NULL;
	}

	pField->SetPosition(dataField.pos);
	pField->SetRotition(dataField.rot);

	// �n�ʐ�������
	return pField;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: �|���S���̑傫��(��, ����), ����(��, �c), �e�N�X�`���ԍ�
//	�@�\	: �n�ʂ̏�����
//=============================================================================
HRESULT CField::Init(float fPolygonWidth, float fPolygonLength, 
					int nNumX, int nNumZ, USHORT nTexNum)
{
	///// �n�ʏ����������J�n /////
	// �ϐ��錾
	HRESULT hr; 
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫��������

	// �e�N�X�`���擾
	CTexture *pTex = NULL;

	SetTexNum(nTexNum);
	
	// �|���S���̑傫���ۑ�
	m_DataField.fWidth = fPolygonWidth;	// �|���S���̕��ۑ�
	m_DataField.fLength = fPolygonLength;	// �|���S���̍����ۑ�

	// �|���S�����ۑ�
	m_DataField.nNumX = nNumX;	// ���̃|���S�����ۑ�
	m_DataField.nNumZ = nNumZ;	// �c�̃|���S�����ۑ�

	// �ʒu�ۑ�
	m_DataField.pos = m_pos;	// �ʒu�ۑ�
	m_DataField.rot = m_rot;	// �����ۑ�
	m_DataField.scl = m_scl;	// �傫���ۑ�

	// ���_���v�Z
	m_nVerTexMax = ( (m_DataField.nNumX + 1) * (m_DataField.nNumZ + 1) );	// ���̃|���S���� + 1 * �c�̃|���S���� + 1

	m_DataField.nVerMax = m_nVerTexMax;

	NEW_TYPE_ARRAY(m_DataField.fY, float, m_nVerTexMax);

	for( int y = 0; y < m_nVerTexMax; y++ )
	{
		m_DataField.fY[y] = 0.0f;
	}

	// ���_�쐬
	hr = MakeVerTex(fPolygonWidth, fPolygonLength);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}


//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �n�ʂ̔j��
//=============================================================================
void CField::Uninit(void)
{
	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		SALF_RELEASE(m_ppLine[l]);
	}
	SALF_RELEASE(m_pVertexBuffer);		// ���_�o�b�t�@�j��
	SALF_RELEASE(m_pIndexBuffer);		// �Y���o�b�t�@�j��
	SALF_DELETE_ARRAY(m_pNor);			// �@���ۑ��o�b�t�@�j��
	SALF_DELETE_ARRAY(m_ppLine);		// �@�����C���j��
	SALF_DELETE_ARRAY(m_DataField.fY);	// ���_Y�j��
	Release();							// �n�ʔj��
}

//=============================================================================
//	�֐���	: Update
//	����	: �Ȃ�
//	�@�\	: �n�ʂ̍X�V
//=============================================================================
void CField::Update(void)
{
	VERTEX_3D *pVtx;	// ���_��
	CInputKeyboard *pKeyboard = CManager::GetInput();

	/*if( CManager::GetInput()->KeyPush(DIK_F1) )
	{
		m_DataField.nTexNum++;
	}
	else if( CManager::GetInput()->KeyPush(DIK_F2) )
	{
		m_DataField.nTexNum--;
	}
	if( m_DataField.nTexNum < CGame::GetData()->GetTexture()->GetTextureNum() )
	{
		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_DataField.nTexNum);
	}
	else
	{
		m_pTexture = NULL;
	}*/

	if( CManager::GetDebug()->GetDebugMode() == true )
	{
		// �f�o�b�O���[�h
		if( pKeyboard->KeyPush(DIK_9) )
		{
			GetNormalVec();
		}

		m_pVertexBuffer->Lock(0 , 0 , (void **)&pVtx , 0);

		if( !m_ppLine[0] )
		{
			NEW_TYPE_ARRAY(m_ppLine, CSceneLine*, m_nVerTexMax);
			for( int line = 0; line < m_nVerTexMax; line++ )
			{
				m_ppLine[line] = CSceneLine::Create( pVtx[line].vtx  , pVtx[line].nor , 255, 255, 255, 255);
			}
		}
		for( int y = 0; y < m_nVerTexMax; y++ )
		{
			m_DataField.fY[y] = pVtx[y].vtx.y;
		}

		m_pVertexBuffer->Unlock();
	}
	else
	{
		if( m_ppLine )
		{
			// ���C�������݂�����
			for( int line = 0; line < m_nVerTexMax; line++ )
			{
				SALF_RELEASE(m_ppLine[line]);
			}
		}
	}
}

//=============================================================================
//	�֐���	: Draw
//	����	: �Ȃ�
//	�@�\	: �n�ʂ̕`��
//			: �傫�����f
//			: �������f
//			: �ꏊ���f
//			: ���[���h�}�g���b�N�X�̐ݒ�
//			: ���_���ݒ�
//			: �e�N�X�`���Z�b�g
//=============================================================================
void CField::Draw(void)
{
	// �ϐ��錾
	D3DXMATRIX mtxScl;		// �X�P�[���}�g���b�N�X
	D3DXMATRIX mtxRot;		// ���b�g�}�g���b�N�X
	D3DXMATRIX mtxTrans;	// �g�����X�}�g���b�N�X
	
	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();		

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);					

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

	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// ���_���ݒ�
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_3D);

	// ���_�o�b�t�@�Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	pRenderer->GetDevice()->SetIndices(m_pIndexBuffer);

	// �v���~�e�B�u�\��
	pRenderer->GetDevice()->DrawIndexedPrimitive(
							CManager::GetDebug()->GetPolygonLine(),	// �v���~�e�B�u�̎��
							0,							// �ǂ����珑����
							0,
							m_nVerTexMax,				// ���_����
							0,
							m_nIndexMax - 2);			// �|���S����(3�p1��1��)
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CField::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu�ݒ�
	m_DataField.pos = m_pos;						// ���݈ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �ʒu�ݒ�
//=============================================================================
void CField::SetPosition(D3DXVECTOR3 pos)
{ 
	m_pos = pos;				// �ʒu�ݒ�
	m_DataField.pos = m_pos;		// �ʒu�ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CField::SetRotition(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// �����ݒ�
	m_DataField.rot = m_rot;						// ���݌����ۑ�
}

//=============================================================================
// �֐���	: SetRotition
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �p�x�ݒ�
//=============================================================================
void CField::SetRotition(D3DXVECTOR3 rot)
{
	m_rot = rot;				// �����ݒ�
	m_DataField.rot = m_rot;	// ���݌����ۑ�
}

//=============================================================================
// �֐���	: SetHeight
// �߂�l	: �Ȃ�
// �����l	: ����( X, Y, Z )
// �@�\		: �n�ʂ̍����ݒ�
//=============================================================================
void CField::SetHeight(float *fY)
{
	VERTEX_3D *pVtx = NULL;

	m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	for( int y = 0; y < m_DataField.nVerMax; y++ )
	{
		pVtx[y].vtx.y = fY[y];
	}

	GetNormalVec();					// �@���Z�o

	m_pVertexBuffer->Unlock();		// 
}

//=============================================================================
// �֐���	: SetTexNum
// �߂�l	: �Ȃ�
// �����l	: �摜�ԍ�
// �@�\		: �摜�ݒ�
//=============================================================================
void	CField::SetTexNum(USHORT nTexNum)
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
	case CManager::MODE_RANKING:
		pTex = CRanking::GetData()->GetTexture();
		break;
	default:
		break;
	}

	m_DataField.nTexNum = nTexNum;						// �e�N�X�`���ԍ��ۑ�
	
	if( pTex )
	{
		if( pTex->GetTextureNum() < m_DataField.nTexNum || 
		m_DataField.nTexNum < 0 )
		{
			m_pTexture = NULL;
		}
		else
		{
			m_pTexture = pTex->GetTexture(m_DataField.nTexNum);
		}
	}
	else
	{
		m_pTexture = NULL;
	}
}

//=============================================================================
// �֐���	: GetHeight
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y, Z )
// �@�\		: �����擾
//=============================================================================
float CField::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;	// ���_��
	float fCross = 0;
	int Num0 = 0;
	int Num1 = 0;
	int Num2 = 0;
	float fPolygonLength;

	D3DXVECTOR3 Vector0 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 Vector1 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 Vector2 = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 HitVector = D3DXVECTOR3( 0, 0, 0 ); 

	int nCntPrimitive = 0;
		
	// ���_���b�N
	 m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for(int nCntZ = 0; nCntZ < m_DataField.nNumZ; nCntZ++)
	{
		for(int nCntX = 0; nCntX < m_DataField.nNumX; nCntX++)
		{

				/////////////////
				//�_           //
				//  �_	--Vec1 //
	//	|-------//    �_       //
	//	Vec0	//      �_     //
	//			//        �_   //
				//          �_ //
				/////////////////
	//					|--Vec2
					
			Num0 = nCntZ * (m_DataField.nNumX + 1) + nCntX;
			Num1 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX;
			Num2 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX + 1;

			Vector0 = pVtx[ Num0 ].vtx - pVtx[ Num1 ].vtx;
			Vector1 = pVtx[ Num2 ].vtx - pVtx[ Num0 ].vtx;
			Vector2 = pVtx[ Num1 ].vtx - pVtx[ Num2 ].vtx;

			HitVector = pos - pVtx[ Num1 ].vtx;			// �v���C���[�̈ʒu - �����̒��_

			fCross = (HitVector.x * Vector0.z) - ( HitVector.z * Vector0.x);
			if(fCross >= 0.0f)
			{
				HitVector = pos - pVtx[ Num0 ].vtx;
				fCross = (HitVector.x * Vector1.z) - ( HitVector.z * Vector1.x);
				if(fCross >= 0.0f)
				{
					HitVector = pos - pVtx[ Num2 ].vtx;
					fCross = (HitVector.x * Vector2.z) - ( HitVector.z * Vector2.x);
					if(fCross >= 0.0f)
					{
						fPolygonLength = pVtx[Num1].vtx.y - ( (m_pNor[nCntPrimitive].x * (pos.x - pVtx[Num1].vtx.x) + m_pNor[nCntPrimitive].z *
								(pos.z - pVtx[Num1].vtx.z) ) / m_pNor[nCntPrimitive].y);

						return fPolygonLength;
					}
				}
			}
			nCntPrimitive++;

			// �x�N�g�����Z�o���邽�߂̓Y�����v�Z
			Num0 = nCntZ * (m_DataField.nNumX + 1) + nCntX;				// �x�N�g���Y���v�Z
			Num1 = nCntZ * (m_DataField.nNumX + 1) + nCntX + 1;			// �x�N�g���Y���v�Z
			Num2 = (nCntZ + 1) * (m_DataField.nNumX + 1) + nCntX + 1;		// �x�N�g���Y���v�Z
			
			Vector0 = pVtx[ Num0 ].vtx - pVtx[ Num1 ].vtx;				// �x�N�g���Z�o
			Vector1 = pVtx[ Num2 ].vtx - pVtx[ Num0 ].vtx;				// �x�N�g���Z�o
			Vector2 = pVtx[ Num1 ].vtx - pVtx[ Num2 ].vtx;				// �x�N�g���Z�o
			
			HitVector = pos - pVtx[ Num1 ].vtx;			// �����Ƃ��Ď����Ă������̂̈ʒu - �����̒��_

			// �O�όv�Z
			fCross = (HitVector.x * Vector0.z) - ( HitVector.z * Vector0.x);
			if(fCross <= 0.0f)
			{
				HitVector = pos - pVtx[ Num0 ].vtx;
				fCross = (HitVector.x * Vector1.z) - ( HitVector.z * Vector1.x);
				if(fCross <= 0.0f)
				{
					HitVector = pos - pVtx[ Num2 ].vtx;
					fCross = (HitVector.x * Vector2.z) - ( HitVector.z * Vector2.x);
					if(fCross <= 0.0f)
					{
						fPolygonLength = pVtx[Num1].vtx.y - ( (m_pNor[nCntPrimitive].x * (pos.x - pVtx[Num1].vtx.x) + m_pNor[nCntPrimitive].z *
								(pos.z - pVtx[Num1].vtx.z) ) / m_pNor[nCntPrimitive].y);
						
						return fPolygonLength;
					}
				}
			}
			nCntPrimitive++;
		}
	}

	m_pVertexBuffer->Unlock();

	return pos.y;
}

//=============================================================================
// �֐���	: LoadData
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�@�C���f�[�^���[�h
//=============================================================================
bool CField::LoadData(FIELD dataField)
{
	FILE *fp = NULL;			// �t�@�C���|�C���^
	int	nError = 0;				// �G���[�`�F�b�N

	m_DataField = dataField;	// �f�[�^����

	// �e�N�X�`���擾
	SetTexNum(m_DataField.nTexNum);

	return true;
}


//=============================================================================
//	�֐���	: MakeVerTex
//	�߂�l	: HRESULT
//	����	: �Ȃ�
//	�@�\	: �n�ʂ̒��_�����
//=============================================================================
HRESULT CField::MakeVerTex( float fPolygonWidth , float fPolygonLength)
{	
	// �ϐ��錾 
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_��
	WORD *pIdx;			// �Y������

	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_���v�Z
	m_nVerTexMax = ( (m_DataField.nNumX + 1) * (m_DataField.nNumZ + 1) );	// ���̃|���S���� + 1 * �c�̃|���S���� + 1

	// ���_�o�b�t�@�쐬����
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_3D) * m_nVerTexMax ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	m_ppLine = NULL;

	NEW_TYPE_ARRAY(m_ppLine, CSceneLine*, m_nVerTexMax);

	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		m_ppLine[l] = NULL;
	}

	// ���_�o�b�t�@�̃��b�N
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);
	
	// ���_�̕ϐ�
	float	fWidth	= (fPolygonWidth * m_DataField.nNumX) / 2;		// �|���S���̕�
	float	fHeight	= (fPolygonLength * m_DataField.nNumZ) / 2;		// �|���S���̉��s��
	float	fX		= -fWidth;								// ���_���W��X��
	float	fZ		= fHeight;								// ���_���W��Z��
	int		nP		= 0;									// �|���S���J�E���^�[ 

	// ���_���W�ݒ�
	for( int z = 0; z < m_DataField.nNumZ + 1; z++, fZ -= fPolygonLength)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataField.nNumX + 1; x++, nP++, fX += fPolygonWidth)
		{
			// ���̖�����
			pVtx[nP].vtx		= D3DXVECTOR3(fX, m_DataField.fY[nP], fZ);			// ���_���W�ݒ�
			pVtx[nP].diffuse	= D3DCOLOR_RGBA(255, 255, 255, 255);	// ���_�F�ݒ�
			pVtx[nP].nor		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �@���ݒ�
		}
		fX		= -fWidth;			// �|���S������������
	}

	nP = 0;		// �|���S���J�E���^�[������

	// �e�N�X�`���̕ϐ�
	float fTexX			= 0.0f;							// �e�N�X�`�����W��X��
	float fTexY			= 0.0f;							// �e�N�X�`�����W��Y��
	float fTexWidth		= 1.0f / m_DataField.nNumX * TEX_XNUM;	// �e�N�X�`���̕� * ����t���b�v�����邩
	float fTexHeight	= 1.0f / m_DataField.nNumZ * TEX_YNUM;	// �e�N�X�`���̍��� * ����t���b�v�����邩

	// �e�N�X�`�����W�ݒ�
	for( int z = 0; z < m_DataField.nNumZ + 1; z++, fTexY -= fTexHeight)
	{
		// �c�̖�����
		for( int x = 0; x < m_DataField.nNumX + 1; x++, nP++, fTexX += fTexWidth)
		{
			// ���̖�����
			pVtx[nP].tex		= D3DXVECTOR2(fTexX, fTexY);	// �e�N�X�`�����W�ݒ�
		}
		fTexX	= 0.0f;			// �e�N�X�`������������	
	}

	// ���_�o�b�t�@�̃��b�N��
	m_pVertexBuffer->Unlock();

	// �ʂ̐�
	int  PrimitiveNum = (m_DataField.nNumX * m_DataField.nNumZ) * 2;

	// �ʂ̖@�����i�[
	m_pNor = NULL;

	m_pNor = NEW D3DXVECTOR3[PrimitiveNum];


	// �@���Z�o
	GetNormalVec();		// �@�����擾

	//					(�� + 1) �̏c�̐�														
	m_nIndexMax = ( ( (m_DataField.nNumX + 1) * 2 ) * m_DataField.nNumZ ) + ( ( m_DataField.nNumZ - 1 ) * 2 );

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
		if( index ==  (( m_DataField.nNumX * 2 ) + 1)  + gyo )
		{
			// �k�ރ|���S���̐���
			for( int k = 0; k < 2; k++ )
			{
				if( index != m_nIndexMax )
				{ 
					pIdx[index] = m_DataField.nNumX + polygon;
					index++;
				}
			}

			if( index < m_nIndexMax )
			{ 
				for( int k = 0; k < 2; k++ )
				{
					pIdx[index] = ( m_DataField.nNumX + 1) + nNum_Gusu;
					index++;
				}
				nNum_Gusu ++;
				nNum_Kisu++;
				gyo +=  ( (m_DataField.nNumX + 1 )+ 1) * 2;
				polygon += (m_DataField.nNumX + 1);
			}
		}
		else if( index % 2 == 0 )
		{
			// �����������ꍇ
			pIdx[index] =  (m_DataField.nNumX + 1) + nNum_Gusu;
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
// �֐���	: GetNormalVec
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �@���Z�o
//=============================================================================
void CField::GetNormalVec(void)
{
	VERTEX_3D *pVtx;	// ���_��
	
	// ���_���b�N
	 m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	for( int l = 0; l < m_nVerTexMax; l++ )
	{
		if( m_ppLine[l] )
		{
			m_ppLine[l]->Release();
			m_ppLine[l] = NULL;
		}
	}

	D3DXVECTOR3 Vector0;				// �x�N�g��
	D3DXVECTOR3 Vector1;				// �x�N�g��
	D3DXVECTOR3 CrossProduct;			// �x�N�g��
	float fLength;						// �x�N�g���̐��K��

	int VectorNum0 = 0;
	int VectorNum1 = 0;
	int nCnt = 0;

	for(int i = 0; i < m_DataField.nNumZ ; i++)
	{
		for( int j = 0; j < m_DataField.nNumX; j++)
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
			VectorNum0 = i * (m_DataField.nNumX + 1) + j;

			// ������钸�_�̔ԍ��v�Z
			VectorNum1 = (i + 1) * (m_DataField.nNumX + 1) + j;

			// �x�N�g�������߂�
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// �������_�̔ԍ��v�Z
			VectorNum0 = (i + 1) * (m_DataField.nNumX + 1) + ( j + 1 );

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
			VectorNum0 = i * (m_DataField.nNumX + 1) + j;
			VectorNum1 = i * (m_DataField.nNumX + 1) + (j + 1);
			

			// �x�N�g�������߂�
			Vector0 = pVtx[ VectorNum0 ].vtx - pVtx[ VectorNum1 ].vtx;

			// �������_�̔ԍ��v�Z
			VectorNum0 = (i + 1) * (m_DataField.nNumX + 1) + (j + 1);

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
	for(int i = 0; i < m_DataField.nNumZ + 1 ; i++)
	{
		for( int j = 0; j < m_DataField.nNumZ + 1; j++)
		{	
			Num0 = i * (m_DataField.nNumX * 2 ) + (j * 2) ;
			Num1 = Num0 - ( m_DataField.nNumX * 2 );
			if( i == 0 )
			{
				// ��i�ڂ�
				if( j == 0 )
				{
					// ��ԍ��͂�
					wark = ( m_pNor[ Num0 ] + m_pNor[ Num0 + 1 ] ) / 2;
				}
				else if( j == m_DataField.nNumX )
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
			else if( i == m_DataField.nNumZ )
			{
				// �Ō�̒i��
				if( j == 0 )
				{
					// ��ԍ��[
					wark = m_pNor[ Num1 + 1 ]; 	
				}
				else if( j == m_DataField.nNumX )
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
				else if( j == m_DataField.nNumX )
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
			
			if( CManager::GetDebug()->GetDebugMode() )
			{
				m_ppLine[nCnt] = CSceneLine::Create( pVtx[nCnt].vtx  , pVtx[nCnt].nor , 255, 255, 255, 255);
			}
			nCnt++;
		}
	}
	m_pVertexBuffer->Unlock();
}