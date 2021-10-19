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
#include "data.h"
#include "manager.h"
#include "scene2D.h"
#include "timer.h"
#include "renderer.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "result.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT ("./DATA/TEXT/result.txt")

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CData		*CResult::m_pData;							// �f�[�^�̎��̐���
CScene2D	*CResult::m_pTitleScene;					// �^�C�g���摜

//=============================================================================
// �֐���	: CResult
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X����
//=============================================================================
CResult::CResult(void)
{
	m_pData			= NULL;		// �f�[�^������
	m_pTitleScene	= NULL;		// �^�C�g���摜
	m_pTimer		= NULL;		// �^�C�}�[
	m_bFace			= false;	// ���̃��[�h�ړ��t���O
}

//=============================================================================
// �֐���	: ~CResult
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X�j��
//=============================================================================
CResult::~CResult(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �E�B���h�E�n���h��
// �@�\		: ������
//=============================================================================
HRESULT CResult::Init(HWND hWnd)
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
		hr = m_pData->Init(hWnd, RESULT);	// �f�[�^������
		ERROR_CHACK(hr);					// �f�[�^���쐬����Ă��邩
	}

	m_pTitleScene = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if( m_pTitleScene == NULL )
	{
		return E_FAIL;
	}

	m_pTimer = CTimer::Create(100, 100, 100, 100, 1);
	if( m_pTimer == NULL )
	{
		return E_FAIL;
	}

	CNumber **pNumber = m_pTimer->GetNumber();
	for(int i = 0; i < MAX_TIMER; i++ )
	{
		pNumber[i]->SetNumColor(0, 0, 0, 255);
	}

	m_pTimer->SetTimer( CManager::GetRankScore() );

	return S_OK;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �I��
//=============================================================================
void CResult::Uninit(void)
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
void CResult::Update(void)
{
	int nColor = CManager::GetFade()->GetColor();					// �t�F�[�h�̐F�擾

	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE )
	{
		// �t�F�[�h���s���Ă��Ȃ����
		if( CManager::GetInput()->KeyPush(DIK_RETURN) )
		{
			m_bFace = true;									// �ړ��t���OON
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);		// �t�F�[�h�ݒ�
		}
	}

	// ��ʑJ�ڏ���
	if( nColor >= 255 && m_bFace == true )
	{
		// �t�F�[�h�̐F��0(��)�Ŏ��̃t�F�[�Y�ړ��t���O��ON�ł����
		CManager::SetMode(CManager::MODE_RANKING);			// ���U���g�w�ڍs
	}
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �`��
//=============================================================================
void CResult::Draw(void)
{
	CScene::DrawAll();
}
