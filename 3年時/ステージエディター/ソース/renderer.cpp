//=============================================================================
// �c�[���쐬�̑O�菇�@�@�@�@�@�@�@�@�t�B�[���h�쐬�c�[���p
//  
// �`�揈�� [renderer.cpp]
//
// �@�\ : �����_�����O (DirectX)
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

#include "main.h"
#include "manager.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BUFFER_DOUBLE_MODE (1)		// �o�b�t�@�[�J�E���g

//=============================================================================
// �֐���	: CRenderer
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X���� (��{�͏�����)
//=============================================================================
CRenderer::CRenderer(void)
{
	m_pD3D		= NULL;		// IDirect9�C���^�[�t�F�[�X������
	m_pDevice	= NULL;		// Direct�f�o�C�X�C���^�[�t�F�[�X������
}

//=============================================================================
// �֐���	: ~CRenderer
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j�� ( �I������ )
//=============================================================================
CRenderer::~CRenderer(void)
{
	Uninit();	// �I������
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT	����I��������
// �����l	: HWnd		�E�B���h�E�n���h��
// �@�\		: �Ȃ�
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindowMode)
{
	HRESULT hr;	// �G���[�`�F�b�N����

	// IDirect9�C���^�[�t�F�[�X�쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	// DirectX�o�[�W�����쐬
	if( m_pD3D == NULL )
	{
		//  IDirect9�C���^�[�t�F�[�X�쐬���s
		return E_FAIL;	// �G���[�R�[�h
	}

	// �f�B�X�v���C���[�h�ݒ�
	D3DDISPLAYMODE	d3ddm;	// �f�B�X�v���C���[�h�\���̕ϐ�
	hr = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	ERROR_CHACK(hr);		// �G���[�`�F�b�N

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;								// �v���[���e�[�V�����\���̕ϐ�
	ZeroMemory(&d3dpp , sizeof(d3dpp) );						// �\���̂̒��g���O������
	d3dpp.Windowed					= bWindowMode;				// �E�B���h�E���[�h�ݒ�
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �X���b�v�G�t�F�N�g�ݒ�
	d3dpp.BackBufferCount			= BUFFER_DOUBLE_MODE;		// �o�b�t�@�� ����(�_�u���o�b�t�@)
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �[�x/�X�e���V���o�b�t�@�ݒ� (�L��)						
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �[�x/�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	if(d3dpp.Windowed == TRUE)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@�t�H�[�}�b�g�ݒ�
		d3dpp.FullScreen_RefreshRateInHz = 0;						// �E�B���h�E���[�h�ݒ� (�E�B���h�E���[�h) 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// ���t���b�V�����[�g (�����ɍX�V)
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;						// �o�b�N�o�b�t�@�[�t�H�[�}�b�g�ݒ�
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // �E�B���h�E���[�h�ݒ� (�t���X�N���[�����[�h)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// ���t���b�V�����[�g (�����҂��čX�V)
	}


	// �f�o�C�X����
	struct
	{
		D3DDEVTYPE	DevType;
		DWORD		BehaviorFlags;
	} 
	DevTypes[] = {
		{ D3DDEVTYPE_HAL , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_HAL , D3DCREATE_SOFTWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_SOFTWARE_VERTEXPROCESSING }
	};

	D3DDEVTYPE	DevType;				// �f�o�C�X�̃^�C�v
	DWORD		BehaviorFlags;			// �t���O
	BOOL		bCreateDevice;			// �f�o�C�X���ł������ǂ���
	int			i;						// �J�E���^�[
	bCreateDevice = FALSE;				// �f�o�C�X�͂ł��ĂȂ�

	for( i = 0; i < _countof(DevTypes); i++ )
	{
		DevType	= DevTypes[i].DevType;
		BehaviorFlags = DevTypes[i].BehaviorFlags;
		hr = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT ,
		DevType ,
		hWnd ,
		BehaviorFlags ,
		&d3dpp,
		&m_pDevice);
		if( SUCCEEDED(hr) )
		{
			// �f�o�C�X�̐�������
			bCreateDevice = TRUE;		// �f�o�C�X���ł���
			break;
		}
	}
	if( bCreateDevice == FALSE )
	{
		// �f�o�C�X�����Ȃ����
		return E_FAIL;					// �G���[�R�[�h
	}
	return S_OK;						// �����R�[�h

}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �����o�ϐ��j��
//=============================================================================
void CRenderer::Uninit(void)
{
	SALF_RELEASE(m_pD3D);		// �������̊J��
	SALF_RELEASE(m_pDevice);	// �������̊J��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �X�V�����Ǔ��ɋ@�\�Ȃ�
//=============================================================================
void CRenderer::Update(void)
{
	// �E�B���h�E��ς���ꍇ�ɍX�V

}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �`��
//=============================================================================
void CRenderer::Draw(void)
{
	HRESULT hr;

	// �o�b�N�o�b�t�@�̃N���A
	m_pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	// �`�揈��
	hr = m_pDevice->BeginScene();			// �`��J�n
	if( SUCCEEDED(hr) )
	{
		CManager::GetCamera()->Draw();		// �J�����`��
		CScene::DrawAll();
		CManager::GetDebug()->Draw();		// �f�o�b�O�`��
		m_pDevice->EndScene();				// �`��I��
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@����ւ�
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

// end of file
