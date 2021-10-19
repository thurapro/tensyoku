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
#include "sceneline.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
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
CSceneLine::CSceneLine(int nPriority):CScene(nPriority)
{

}

//=============================================================================
//	�֐���	: ~CScene3D
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �C���X�^���X�j��
//=============================================================================
CSceneLine::~CSceneLine(void)
{
	// �C���X�^���X�j��
}

HRESULT CSceneLine::Init(void)
{
	return S_OK;
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CSceneLine::Init(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	///// 3D�I�u�W�F�N�g�����������J�n /////
	//--- �ϐ��錾 ---//
	HRESULT hr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����������
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫��������

	hr = MakeVerTex(startPoint,  endPoint, nRed, nGreen,  nBlue,  nAlpha);
	if(FAILED(hr))
	{
		return hr;
	}
	return hr;
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̔j��
//=============================================================================
void CSceneLine::Uninit(void)
{
	if(m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	Release();
}

//=============================================================================
//	�֐���	: Update
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̍X�V
//=============================================================================
void CSceneLine::Update(void)
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
void CSceneLine::Draw(void)
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

	pDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	///// ���_���ݒ� /////
	pDevice->SetFVF(FVF_VERTEX_3D);

	///// ���_�o�b�t�@�Z�b�g /////
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	// �v���~�e�B�u�\��
	pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 1);

	pDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
}

//=============================================================================
//	�֐���	: MakeVerTexCylinder
//	�߂�l	: HRESULT
//	����	: �Ȃ�
//	�@�\	: 3D�I�u�W�F�N�g�̒��_�����
//=============================================================================
HRESULT CSceneLine::MakeVerTex(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	///// ���ʕϐ��錾 /////
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	///// ���_�p�ϐ��錾 /////
	HRESULT hr;			// ���ʕϐ�
	VERTEX_3D *pVtx;	// ���_

	//---------------------------------------------------------------------
	// ���_�o�b�t�@�쐬����
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_3D) * 2 ,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pVertexBuffer,
										NULL );
	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̃��b�N
	hr = m_pVertexBuffer->Lock( 0 , 0 , (void **)&pVtx , 0);

	pVtx[0].vtx = startPoint;
	pVtx[1].vtx = D3DXVECTOR3( (endPoint.x * 10) + startPoint.x, (endPoint.y * 10) + startPoint.y, (endPoint.z * 10) + startPoint.z);

	for(int i = 0; i < 2; i++)
	{
		//-------------------------------------------------------------------------
		// �����̐ݒ�if( FAILED(hr) )
		pVtx[i].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		//---------------------------------------------------------------------
		// �F���̐ݒ�	( �� , �� , �� , �����x)
		pVtx[i].diffuse = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	}

	//-------------------------------------------------------------------------
	// ���_�o�b�t�@�̃��b�N��
	m_pVertexBuffer->Unlock();

	
	// �쐬����
	return (S_OK);
}

//=============================================================================
// 3D�쐬
//=============================================================================
CSceneLine *CSceneLine::Create(D3DXVECTOR3 startPoint, D3DXVECTOR3 endPoint, int nRed, int nGreen, int nBlue, int nAlpha)
{
	CSceneLine *pSceneLine;
	pSceneLine = NEW CSceneLine;
	pSceneLine->Init(startPoint,  endPoint, nRed, nGreen,  nBlue,  nAlpha);
	return pSceneLine;
}

