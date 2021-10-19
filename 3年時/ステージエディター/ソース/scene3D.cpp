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
#include <d3dx9.h>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene3D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define UPSTARTINm_POINT	(0)																// ��̌��_
#define DOWNSTARTINm_POINT	(25)															// ���̌��_
#define ANGLE_INIT			(180)															// �����p�x
#define INDEX_MAX			(20)

//=============================================================================
//	�֐���	: CScene3D
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X����
//=============================================================================
CScene3D::CScene3D(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	// �C���X�^���X����
	m_pTexture = NULL;							// �e�N�X�`��������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫��������
	m_nTexNum = -1;
}

//=============================================================================
//	�֐���	: ~CScene3D
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CScene3D::~CScene3D(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Create
//	�߂�l	: �Ȃ�
//	����	: �ʒu (X, Y, Z) �傫��( ��, ����, ���s ), �e�N�X�`���ԍ�
//	�@�\	: 3D�I�u�W�F�N�g�̍쐬
//=============================================================================
CScene3D *CScene3D::Create(float fPosX, float fPosY, float fPosZ, 
							float fWidth, float fHeight, float fLength,
							USHORT nTexNum)
{
	HRESULT hr;						// �G���[�`�F�b�N
	CScene3D *pScene3D;				// 3D�I�u�W�F�N�g
	pScene3D = NEW CScene3D;		// 3D�I�u�W�F�N�g�C���X�^���X����

	hr = pScene3D->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength ,nTexNum);	// 3D�I�u�W�F�N�g������
	if( FAILED(hr) )
	{
		// 3D�I�u�W�F�N�g�쐬�Ɏ��s
		return NULL;				// �G���[�R�[�h
	}
	return pScene3D;				// ����R�[�h
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �Ȃ�
//	����	: �ʒu (X, Y, Z) �傫��( ��, ����, ���s ), �e�N�X�`���ԍ�
//	�@�\	: 3D�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CScene3D::Init(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						USHORT nTexNum)
{
	///// 3D�I�u�W�F�N�g�����������J�n /////

	//--- �ϐ��錾 ---//
	HRESULT hr;
	//CData	 *pData = NULL;			// �f�[�^
	//CTexture *pTex	= NULL;			// �e�N�X�`��

	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫��������

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:				// ���S�̏ꍇ
	//	pData	= CLogo::GetData();			// ���S����f�[�^�擾
	//	pTex	= pData->GetTexture();		// �e�N�X�`���擾
	//	break;

	//case CManager::MODE_TITLE:				// �^�C�g���̏ꍇ
	//	pData = CTitle::GetData();			// �^�C�g������f�[�^�擾
	//	pTex = pData->GetTexture();			// �e�N�X�`���擾
	//	break;

	//case CManager::MODE_TUTORIAL:			// �`���[�g���A���̏ꍇ
	//	pData	= CTutorial::GetData();		// �`���[�g���A������f�[�^�擾
	//	pTex	= pData->GetTexture();		// �e�N�X�`���擾
	//	break;

	//case CManager::MODE_GAME:				// �Q�[���̏ꍇ
	//	pData = CGame::GetData();			// �Q�[������f�[�^�擾
	//	pTex = pData->GetTexture();			// �e�N�X�`���擾
	//	break;

	//case CManager::MODE_RESULT:				// ���U���g�̏ꍇ
	//	pData = CResult::GetData();			// ���U���g����f�[�^�擾
	//	pTex = pData->GetTexture();			// �e�N�X�`���擾
	//	break;

	//case CManager::MODE_RANKING:			// �����L���O�̏ꍇ
	//	pData = CRanking::GetData();		// �����L���O����f�[�^�擾
	//	pTex = pData->GetTexture();			// �e�N�X�`���擾
	//	break;

	//default:
	//	break;
	//}
	
	//unsigned int nMaxTex = pTex->GetTextureNum();
	m_nTexNum = nTexNum;

	//if( m_nTexNum > nMaxTex
	//	|| m_nTexNum < 0 )
	//{
	//	m_pTexture = NULL;
	//}
	//else
	//{
	//	m_pTexture = pTex->GetTexture(m_nTexNum);
	//}

	// ���_�쐬
	hr = MakeVerTex(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength);

	return S_OK;
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̔j��
//=============================================================================
void CScene3D::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);	// ���_�j��
	Release();						// �V�[�����X�g�\�����玩����j��
}

//=============================================================================
//	�֐���	: Update
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̍X�V
//=============================================================================
void CScene3D::Update(void)
{
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
void CScene3D::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈���J�n
	CRenderer *pRenderer = CManager::GetRenderer();

	// �ϐ��錾
	D3DXMATRIX mtxScl;		// �X�P�[���}�g���b�N�X
	D3DXMATRIX mtxRot;		// ���b�g�}�g���b�N�X
	D3DXMATRIX mtxTrans;	// �g�����X�}�g���b�N�X
	
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

	// �e�N�X�`���Z�b�g
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);
	
	// ���_���ݒ�
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_3D);

	// ���_�o�b�t�@�Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	// �v���~�e�B�u�\��
	pRenderer->GetDevice()->DrawPrimitive(
						D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
							0,							// �ǂ����珑����
							2);							// �|���S����(3�p1��1��)
}

//=============================================================================
//	�֐���	: MakeVerTex
//	�߂�l	: HRESULT
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̒��_�����
//=============================================================================
HRESULT CScene3D::MakeVerTex(float fPosX, float fPosY, float fPosZ, 
							float fWidth , float fHeight, float fLength)
{
	// �ϐ��錾
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();				// �����_���[�擾

	// ���_�p�ϐ��錾
	VERTEX_3D	*pVertex;										// ���_�f�[�^�����\����

	// ���_�o�b�t�@�쐬
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_3D) * 4,	// ���_�����ݒ肷��̂�
									D3DUSAGE_WRITEONLY,						// �o�b�t�@�̎g�p�� (���݂̐ݒ菑�����ݐ�p)
									FVF_VERTEX_3D,							// D3DFVF�t���O�̑g�ݍ��킹
									D3DPOOL_MANAGED,						// ���_�o�b�t�@���z�u�����L���ȃ������N���X
									&m_pVertexBuffer,						// ���_�o�b�t�@���󂯎��|�C���^
									NULL);									// ���NULL
	ERROR_CHACK(hr);	// �G���[�`�F�b�N
	
	// ���_�Ƀf�[�^����������
	hr = m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);					// ���_�S�̂����b�N

	pVertex[0].vtx = D3DXVECTOR3(-fWidth, fPosY, -fLength);
	pVertex[1].vtx = D3DXVECTOR3(-fWidth, fHeight, fLength);
	pVertex[2].vtx = D3DXVECTOR3(fWidth, fHeight, -fLength);
	pVertex[3].vtx = D3DXVECTOR3(fWidth, fPosY, fLength);
	
	D3DXVECTOR3 Vector0 = pVertex[1].vtx - pVertex[0].vtx;
	D3DXVECTOR3 Vector1 = pVertex[2].vtx - pVertex[0].vtx;
	D3DXVECTOR3 Vector2 = pVertex[1].vtx - pVertex[3].vtx;
	D3DXVECTOR3 Vector3 = pVertex[2].vtx - pVertex[3].vtx;

	D3DXVECTOR3 VectorA;
	VectorA.x = (Vector0.y * Vector1.z) - (Vector0.z * Vector1.y);
	VectorA.y = (Vector0.z * Vector1.x) - (Vector0.x * Vector1.z);
	VectorA.z = (Vector0.x * Vector1.y) - (Vector0.y * Vector1.x);

	D3DXVECTOR3 VectorB;
	VectorB.x = (Vector2.y * Vector3.z) - (Vector2.z * Vector3.y);
	VectorB.y = (Vector2.z * Vector3.x) - (Vector2.x * Vector3.z);
	VectorB.z = (Vector2.x * Vector3.y) - (Vector2.y * Vector3.x);

	float fLengthA = sqrt( (VectorA.x * VectorA.x) + (VectorA.y * VectorA.y) + (VectorA.z * VectorA.z) );
	float fLengthB = sqrt( (VectorB.x * VectorB.x) + (VectorB.y * VectorB.y) + (VectorB.z * VectorB.z) );

	D3DXVECTOR3 VectorC;
	VectorC.x = (VectorA.x + VectorB.x) / 2;
	VectorC.y = (VectorA.y + VectorB.y) / 2;
	VectorC.z = (VectorA.z + VectorB.z) / 2;
	VectorC = (VectorA + VectorB) / 2;

	float fLengthC = sqrt( (VectorC.x * VectorC.x) + (VectorC.y * VectorC.y) + (VectorC.z * VectorC.z) );

	pVertex[0].nor = D3DXVECTOR3( (VectorA.x / fLengthA), (VectorA.y / fLengthA), (VectorA.z / fLengthA) );
	pVertex[1].nor = D3DXVECTOR3( (VectorC.x / fLengthC), (VectorC.y / fLengthC), (VectorC.z / fLengthC) );
	pVertex[2].nor = D3DXVECTOR3(( VectorC.x / fLengthC), (VectorC.y / fLengthC), (VectorC.z / fLengthC) );
	pVertex[3].nor = D3DXVECTOR3( (VectorB.x / fLengthB), (VectorB.y / fLengthB), (VectorB.z / fLengthB) );

	pVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	hr = m_pVertexBuffer->Unlock();	// ���_�S�̃��b�N������

	// �쐬����
	return (S_OK);
}

//=============================================================================
//	�֐���	: SetPotition
//	�߂�l	: �Ȃ�
//	����	: �ʒu ( X, Y, Z ) float�^
//	�@�\	: �ʒu�ݒ�
//=============================================================================
void CScene3D::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);	// �ʒu�ݒ�
}

//=============================================================================
//	�֐���	: SetPotition
//	�߂�l	: �Ȃ�
//	����	: �ʒu ( X, Y, Z ) D3DXVECTOR3�^
//	�@�\	: �ʒu�ݒ�
//=============================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;	// �ʒu�ݒ�
}

//=============================================================================
//	�֐���	: SetRotition
//	�߂�l	: �Ȃ�
//	����	: ����( X, Y, Z ) float�^
//	�@�\	: �����ݒ�
//=============================================================================
void CScene3D::SetRotiton(float fRotX, float fRotY, float fRotZ)
{
	m_rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);	// �����ݒ�
}

//=============================================================================
//	�֐���	: SetRotition
//	�߂�l	: �Ȃ�
//	����	: ����( X, Y, Z ) D3DXVECTOR3�^
//	�@�\	: �ʒu�ݒ�
//=============================================================================
void CScene3D::SetRotiton(D3DXVECTOR3 rot)
{
	m_rot = rot;		// �����ݒ�
}

//=============================================================================
//	�֐���	: SetScale
//	�߂�l	: �Ȃ�
//	����	: �傫��( X, Y, Z ) float�^ 
//	�@�\	: �傫���ݒ�
//=============================================================================
void CScene3D::SetScale(float fSclX, float fSclY, float fSclZ)
{
	m_scl = D3DXVECTOR3(fSclX, fSclY, fSclZ);	// �傫���ݒ�
}

//=============================================================================
//	�֐���	: SetScale
//	�߂�l	: �Ȃ�
//	����	: �傫��( X, Y, Z ) D3DXVECTOR3�^ 
//	�@�\	: �傫���ݒ�
//=============================================================================
void CScene3D::SetScale(D3DXVECTOR3 scl)
{
	m_scl = scl;		// �傫���ݒ�
}



