//=============================================================================
// �ԍ�����[number.h]
//
// ����� : ���� �Y��
//
// �@�\ :  �X�R�A�[�E�^�C�}�[�Ȃ� 
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "manager.h"
#include "main.h"
#include "debugproc.h"
#include "renderer.h"
#include "data.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "number.h"

//=============================================================================
// �֐���	: CNumber
// ����		: �Ȃ�
// �߂�l	: �Ȃ�
// �@�\		: �C���X�^���X����
//=============================================================================
CNumber::CNumber(void)
{
	// �C���X�^���X����
	m_pVertexBuffer = NULL;
	m_nNumber		= -1;
}

//=============================================================================
// �֐���	: ~CNumber
// ����		: �Ȃ�
// �߂�l	: �Ȃ�
// �@�\		: �C���X�^���X�j��
//=============================================================================
CNumber::~CNumber(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: HREUSLT	����,�G���[����
// ����		: �ʒu�̍���A�E��A�����A�E��, �e�N�X�`���ԍ�
// �@�\		: �ԍ��쐬
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, 
						D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom,
						unsigned int nTexNum)
{
	HRESULT hr;
	CNumber *pNumber = NULL;
	pNumber = NEW CNumber;
	hr = pNumber->Init(fPosLeftTop, fPosRightTop, fPosLeftBottom, fPosRightBottom, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pNumber;
}

//=============================================================================
// �֐���	: Create
// �߂�l	: HREUSLT	����,�G���[����
// ����		: �ʒu�̍���A�E��A��, ����, �e�N�X�`���ԍ�
// �@�\		: �ԍ��쐬
//=============================================================================
CNumber *CNumber::Create(float fPosX, float fPosY, float fWidth, float fHeight,
						unsigned int nTexNum)
{
	HRESULT hr;
	CNumber *pNumber = NULL;
	pNumber = NEW CNumber;
	hr = pNumber->Init(fPosX, fPosY, fWidth, fHeight, nTexNum);
	if( FAILED(hr) )
	{
		return NULL;
	}
	return pNumber;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HREUSLT	����,�G���[����
// ����		: �e�N�X�`�����W�̍���A�E��A�����A�E��
// �@�\		: ������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop,
					D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom,
					unsigned int nTexNum )
{
	HRESULT hr;
	CData	*pData = NULL;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData	= CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData	= CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData	= CResult::GetData();
		break;
	case CManager::MODE_RANKING:
		pData	= CRanking::GetData();
		break;
	}
	
	if( nTexNum > pData->GetTexture()->GetTextureNum() ||
		nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = pData->GetTexture()->GetTexture(nTexNum);
	}

	if( m_pTexture == NULL )
	{
		return E_FAIL;
	}

	// ���_�쐬
	hr = MakeVerTex(fPosLeftTop, fPosRightTop, fPosLeftBottom, fPosRightBottom);
	
	//-----------------------
	// ���_���쐬�o���Ȃ����
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HREUSLT	����,�G���[����
// ����		: �ʒu (X, Y) �傫��( ��, ���� ) 
// �@�\		: ������
//=============================================================================
HRESULT CNumber::Init(float fPosX, float fPosY, float fWidth, float fHeight,
					unsigned int nTexNum)
{
	HRESULT hr;
	CData	*pData = NULL;

	switch( CManager::GetMode() )
	{
	case CManager::MODE_TITLE:
		pData	= CTitle::GetData();
		break;
	case CManager::MODE_GAME:
		pData	= CGame::GetData();
		break;
	case CManager::MODE_RESULT:
		pData	= CResult::GetData();
		break;
	case CManager::MODE_RANKING:
		pData	= CRanking::GetData();
		break;
	}
	
	if( nTexNum > pData->GetTexture()->GetTextureNum() ||
		nTexNum < 0 )
	{
		m_pTexture = NULL;
	}
	else
	{
		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(nTexNum);
	}

	if( m_pTexture == NULL )
	{
		return E_FAIL;
	}

	// ���_�쐬
	hr = MakeVerTex(fPosX, fPosY, fWidth, fHeight);
	
	//-----------------------
	// ���_���쐬�o���Ȃ����
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}
				

//=============================================================================
// �I������
//=============================================================================
void CNumber::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);
}

//=============================================================================
// �X�V����
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�t�H�[�}�b�g���Z�b�g
	pDevice->SetFVF(FVF_VERTEX_2D_TEX);
	
	// ���_�o�b�t�@�[�̃Z�b�g
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
	
	// �e�N�X�`���[�Z�b�g
	pDevice->SetTexture(0, m_pTexture);

	// �v���~�e�B�u
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_�쐬
//=============================================================================
HRESULT CNumber::MakeVerTex(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, 
							D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�[�쐬
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// �쐬�ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}

	// ���_�o�b�t�@�[���b�N
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx = fPosLeftTop;
	pVtx[1].vtx = fPosRightTop;
	pVtx[2].vtx = fPosLeftBottom;
	pVtx[3].vtx = fPosRightBottom;
	
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F���
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���[���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f, 1.0f);

	// ���b�N����
	hr = m_pVertexBuffer->Unlock();
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// ���_�쐬
//=============================================================================
HRESULT CNumber::MakeVerTex(float fPosX, float fPosY, float fWidth, float fHeight)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�[�쐬
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_TEX,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// �쐬�ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}

	// ���_�o�b�t�@�[���b�N
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(fPosX, fHeight, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F���
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���[���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f, 1.0f);

	// ���b�N����
	hr = m_pVertexBuffer->Unlock();
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �֐���	: SetNumber
// �߂�l	: �ԍ�
// �����l	: �Ȃ�
// �@�\		: �ԍ��ݒ�
//=============================================================================
void CNumber::SetNumberTexture(unsigned int nNumber)
{
	VERTEX_2D *pVtx;
	
	float fNumber	= nNumber * 0.1f;
	float fLeftTex	= fNumber;
	m_nNumber		= nNumber;

	// ���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);


	// �e�N�X�`���[���W�ݒ�
	pVtx[0].tex.x = fNumber;
	pVtx[1].tex.x = fNumber + 0.1f;
	pVtx[2].tex.x = fNumber;
	pVtx[3].tex.x = fNumber + 0.1f;

	if( pVtx[0].tex.x > 0.9f && pVtx[1].tex.x > 1.0f)
	{
		pVtx[0].tex.x = 0.0f;
		pVtx[1].tex.x = 1.0f / 10.0f;
		pVtx[2].tex.x = 0.0f;
		pVtx[3].tex.x = 1.0f / 10.0f;
	}


	// ���b�N����
	m_pVertexBuffer->Unlock();
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �ʒu( X, Y ) �傫��( ��, ���� )
// �@�\		: �ʒu��ݒ�
//=============================================================================
void CNumber::SetPosition(float fPosX, float fPosY,
						float fWidth, float fHeight)
{
	VERTEX_2D	*pVtx;					// ���_�쐬�p�̊i�[�ϐ�
	
	fWidth += fPosX;
	fHeight += fPosY;

	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}

//=============================================================================
// �֐���	: SetPosHeight
// �߂�l	: �Ȃ�
// �����l	: �����ݒ� ( ��, ��, ��, �����x )
// �@�\		: �����ݒ�
//=============================================================================
void CNumber::SetPosHeight(float fPosY, float fHeight)
{
	VERTEX_2D	*pVtx;					// ���_�쐬�p�̊i�[�ϐ�
	
	fHeight += fPosY;

	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx.y = fPosY;
	pVtx[1].vtx.y = fPosY;
	pVtx[2].vtx.y = fHeight;
	pVtx[3].vtx.y = fHeight;

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}

//=============================================================================
// �֐���	: SetNumColor
// �߂�l	: �Ȃ�
// �����l	: �F�ݒ� ( ��, ��, ��, �����x )
// �@�\		: �ԍ��̐F�ݒ�
//=============================================================================
void CNumber::SetNumColor(int nR, int nG, int nB, int nA)
{
	VERTEX_2D	*pVtx;				// ���_�쐬�p�̊i�[�ϐ�
	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[1].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[2].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[3].diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}