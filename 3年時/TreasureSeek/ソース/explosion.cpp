//=============================================================================
// �e���� [bullet.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: �e
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "explosion.h"

//=============================================================================
// �֐���	: CExplosion
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e�C���X�^���X����
//=============================================================================
CExplosion::CExplosion(int nPriority, OBJTYPE objType):CBillboard(nPriority, objType)
{
	// �C���X�^���X����
}

//=============================================================================
// �֐���	: ~CExplosion
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e�C���X�^���X�j��
//=============================================================================
CExplosion::~CExplosion(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e����
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,
								USHORT nTexNum)
{
	HRESULT hr;
	CExplosion *pExplosion = NULL;
	if( pExplosion == NULL )
	{
		pExplosion = NEW CExplosion;
		hr = pExplosion->Init(pos, fWidth, fHeight, nTexNum);
		if( FAILED(hr) )
		{
			return NULL;
		}
	}
	return pExplosion;
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e����
//=============================================================================
CExplosion *CExplosion::Create(float fPosX, float fPosY, float fPosZ, float fWidth, float fHeight,
								USHORT nTexNum)
{
	HRESULT hr;
	CExplosion *pExplosion = NULL;
	if( pExplosion == NULL )
	{
		pExplosion = NEW CExplosion;
		hr = pExplosion->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, nTexNum);
		if( FAILED(hr) )
		{
			return NULL;
		}
	}
	return pExplosion;
}


//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e����������
//=============================================================================
HRESULT CExplosion::Init(void)
{
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: float fWidth : �e�̕�
//			: float fHeight: �e�̍���	�e�N�X�`���ԍ�
// �@�\		: �e������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fWidth, float fHeight,
						USHORT nTexNum)
{
	HRESULT hr;
	pos.y = 10;
	hr = CBillboard::Init(fWidth, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: float fWidth : �e�̕�
//			: float fHeight: �e�̍���	�e�N�X�`���ԍ�
// �@�\		: �e������
//=============================================================================
HRESULT CExplosion::Init(float fPosX, float fPosY, float fPosZ, float fWidth, float fHeight,
						USHORT nTexNum)
{
	HRESULT hr;
	hr = CBillboard::Init(fWidth, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}


//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e�I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e�X�V����
//=============================================================================
void CExplosion::Update(void)
{
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �e�̕`��
//=============================================================================
void CExplosion::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState( D3DRS_LIGHTING , FALSE );
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
	pDevice->SetRenderState( D3DRS_ALPHAREF , 253 );
	pDevice->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
	CBillboard::Draw();
	pDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);
}
