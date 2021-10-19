//=============================================================================
// �e�̏��� [shadow.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: �e�̍쐬 
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "data.h"
#include "shadow.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �֐���	: CShadow
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X����( ������ )
//=============================================================================
CShadow::CShadow(int nPriority, OBJTYPE objType):CScene3D(nPriority, objType)
{
	// �C���X�^���X����
}

//=============================================================================
// �֐���	: ~CShadow
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j��( �I�� )
//=============================================================================
CShadow::~CShadow(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: �e ( ���s NULL )
// �����l	: �ʒu ( X, Y, Z ), �傫��( �� , ����, ���s), �e�N�X�`���ԍ�
// �@�\		: �e�̐���
//=============================================================================
CShadow *CShadow::Create(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						unsigned int nTexNum)
{
	HRESULT hr;						// �G���[�`�F�b�N�ϐ�
	CShadow *pShadow = NULL;		// �e�|�C���^
	if( pShadow == NULL )
	{
		// ����Ă��Ȃ����
		pShadow = NEW CShadow;		// �e�C���X�^���X����
		hr = pShadow->Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength, nTexNum);	// ������
		if( FAILED(hr) )	
		{
			// �G���[�`�F�b�N
			return NULL;		// �G���[�R�[�h
		}
	}
	return pShadow;				// �e��Ԃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// �����l	: �ʒu ( X, Y, Z ), �傫��( �� , ����, ���s), �e�N�X�`���ԍ�
// �@�\		: �e�̏���������
//=============================================================================
HRESULT CShadow::Init(float fPosX, float fPosY, float fPosZ,
						float fWidth, float fHeight, float fLength,
						unsigned int nTexNum)
{
	HRESULT hr;			// �G���[�`�F�b�N�ϐ�
	hr = CScene3D::Init(fPosX, fPosY, fPosZ, fWidth, fHeight, fLength, nTexNum);
	ERROR_CHACK(hr);	// �G���[�`�F�b�N
	return S_OK;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �e�̏I������
//=============================================================================
void CShadow::Uninit(void)
{
	CScene3D::Uninit();		// �e�̏I������
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �e�̍X�V����
//=============================================================================
void CShadow::Update(void)
{
	// �e�̍X�V
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �e�̕`�揈��
//=============================================================================
void CShadow::Draw(void)
{
	// �e�̕`��
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�擾
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE );
	CScene3D::Draw();
	pDevice->SetRenderState(D3DRS_BLENDOP , D3DBLENDOP_ADD);				// ���Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);			// ���Z����
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);		
}


