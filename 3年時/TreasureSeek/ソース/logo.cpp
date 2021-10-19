//=============================================================================
// ���� [game.cpp]
//
// �����	: ���� �Y��
//
// �@�\		: 
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "data.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "renderer.h"
#include "logo.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LOGO ("data/text/logo.txt")

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CData		*CLogo::m_pData;						// �f�[�^�̎��̐���
CScene2D	*CLogo::m_pTitleScene;					// �^�C�g���摜

//=============================================================================
// �֐���	: CLogo
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X����
//=============================================================================
CLogo::CLogo(void)
{
	m_pFade			= NULL;		// �t�F�[�h������
	m_pData			= NULL;		// �f�[�^������
	m_pTitleScene	= NULL;		// �^�C�g���摜
	m_bFace			= false;	// ���̃��[�h�ړ��t���O
	m_nTimeCnt		= 0;		// ���ԃJ�E���^
}

//=============================================================================
// �֐���	: ~CLogo
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X�j��
//=============================================================================
CLogo::~CLogo(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �E�B���h�E�n���h��
// �@�\		: ������
//=============================================================================
HRESULT CLogo::Init(HWND hWnd)
{
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//----------------------------------------------------------------------------
	// �����_�����O�X�e�[�g�̏������ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//

	//-------------------------------------------------------------------------
	// �T���v���[�X�e�[�g�̏������ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if( m_pData == NULL )
	{
		// �f�[�^���쐬����Ă��Ȃ����
		m_pData = NEW CData;				// �f�[�^�C���X�^���X����
		hr = m_pData->Init(hWnd, LOGO);		// �f�[�^������
		ERROR_CHACK(hr);					// �f�[�^���쐬����Ă��邩
	}

	m_pTitleScene = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if( m_pTitleScene == NULL )
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �I��
//=============================================================================
void CLogo::Uninit(void)
{
	// �������̊J��
	CScene::ReleaseAll();		// �V�[���j��
	CLASS_DELETE(m_pData);		// �f�[�^�j��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �X�V
//=============================================================================
void CLogo::Update(void)
{
	int nColor = CManager::GetFade()->GetColor();					// �t�F�[�h�̐F�擾

	// �t�F�[�h���s���Ă��Ȃ����
	if( CManager::GetInput()->KeyPush(DIK_RETURN) )
	{
		m_bFace = true;									// �ړ��t���OON
		CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// �t�F�[�h�ݒ�
	}
	else if( m_nTimeCnt > 120 )
	{
		m_bFace = true;												// �ړ��t���OON
		CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// �t�F�[�h�ݒ�
		m_nTimeCnt = 0;
	}

	if( m_bFace == false )
	{
		m_nTimeCnt++;
	}
	
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE && 
		m_bFace == true )
	{
		CManager::SetMode(CManager::MODE_TITLE);			// �^�C�g���w�ڍs
	}
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �`��
//=============================================================================
void CLogo::Draw(void)
{
	CScene::DrawAll();
}
