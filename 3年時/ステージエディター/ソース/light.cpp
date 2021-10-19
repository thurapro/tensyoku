//=============================================================================
// �Ɩ�(���C�g)����	[light.cpp]
// 
// �����	: ���� �Y��
//
// �@�\		: ���C�g������
//			: �X�V
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "light.h"

//=============================================================================
// �֐���	: CLight
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: ���C�g�̃C���X�^���X����
//=============================================================================
CLight::CLight(void)
{
	// �C���X�^���X����
}

//=============================================================================
// �֐���	: ~CLight
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: ���C�g�̃C���X�^���X�j��
//=============================================================================
CLight::~CLight(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Init
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: ���C�g�̏�����
//			: ���C�g�̖��邳������
//			: ���C�g�̌���������
//=============================================================================
HRESULT CLight::Init(void)
{
	///// ���C�g�̏����������J�n /////

	// �ϐ��錾 
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�擾

	/////// 1�ڂ̃��C�g�̖��邳������ /////
	ZeroMemory(&m_aLight[FIRST_LIGHT], sizeof(D3DLIGHT9) );							// ���C�g�̃�������S������
	m_aLight[FIRST_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ���C�g�̎��
	m_aLight[FIRST_LIGHT].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);				// �g�U�F�ݒ�

	///// ���C�g�̌��������� /////
	m_vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);										// ���C�g�̕��� ���d�v��
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[FIRST_LIGHT].Direction, &m_vecDir);	// ���C�g�̕����C��
	hr = pDevice->SetLight(FIRST_LIGHT, &m_aLight[FIRST_LIGHT]);					// ���C�g�̐ݒ�
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(FIRST_LIGHT, TRUE);									// ���C�g��L���ɂ���
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// 2�ڂ̃��C�g�̖��邳������ /////
	ZeroMemory(&m_aLight[SECOND_LIGHT], sizeof(D3DLIGHT9) );						// ���C�g�̃�������S������
	m_aLight[SECOND_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ���C�g�̎��
	m_aLight[SECOND_LIGHT].Diffuse = D3DXCOLOR(0.55f, 0.55f, 0.55f, 0.35f);				// �g�U�F�ݒ�

	///// ���C�g�̌��������� /////
	m_vecDir = D3DXVECTOR3(1.0f, 0.0f, 1.0f);										// ���C�g�̕��� ���d�v��
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[SECOND_LIGHT].Direction, &m_vecDir);	// ���C�g�̕����C��
	hr = pDevice->SetLight(SECOND_LIGHT, &m_aLight[SECOND_LIGHT]);					// ���C�g�̐ݒ�
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(SECOND_LIGHT, TRUE);									// ���C�g��L���ɂ���
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// 3�ڂ̃��C�g�̖��邳������ /////
	ZeroMemory(&m_aLight[THIRD_LIGHT], sizeof(D3DLIGHT9) );							// ���C�g�̃�������S������
	m_aLight[THIRD_LIGHT].Type = D3DLIGHT_DIRECTIONAL;								// ���C�g�̎��
	m_aLight[THIRD_LIGHT].Diffuse = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);			// �g�U�F�ݒ�

	///// ���C�g�̌��������� /////
	m_vecDir = D3DXVECTOR3(-4.0f, 0.3f, 1.0f);										// ���C�g�̕��� ���d�v��
	D3DXVec3Normalize( (D3DXVECTOR3 *)&m_aLight[THIRD_LIGHT].Direction, &m_vecDir);	// ���C�g�̕����C��
	hr = pDevice->SetLight(THIRD_LIGHT, &m_aLight[THIRD_LIGHT]);					// ���C�g�̐ݒ�
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	hr = pDevice->LightEnable(THIRD_LIGHT, TRUE);									// ���C�g��L���ɂ���
	if(FAILED(hr))
	{
		return E_FAIL;
	}

	///// �����_�[�X�e�[�g�ݒ� /////
	hr = pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);								// ���C�g��ݒ肷��
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
// �@�\		: ���C�g�̔j��
//=============================================================================
void CLight::Uninit(void)
{
	// �I������
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: ���C�g�̍X�V
//=============================================================================
void CLight::Update(void)
{
}

///// end of file /////