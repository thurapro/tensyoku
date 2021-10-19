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
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "data.h"
#include "fade.h"
#include "title.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE			("data/text/title.txt")
#define MAX_TIME		( 1000 )
#define CHAR_POSY		( 0 )
#define CHAR_HEIGHT		( 0 )
#define CHAR_SPEED		( 1 )
#define INIT_TEX_X		( 0.0f )
#define INIT_TEX_WIDTH	( 1.0f / 4.0f )
#define TEX_SPEED		( 1.0f / 4.0f )
#define CLEAN_TIME		( 0 )

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CData		*CTitle::m_pData;						// �摜�̎��̐���

//=============================================================================
// �֐���	: Game
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X����
//=============================================================================
CTitle::CTitle(void)
{
	m_pData			= NULL;								// �f�[�^������
	ZeroMemory(m_pTitleScene, sizeof(m_pTitleScene) );	// �^�C�g���摜������
	m_bFace			= false;							// ���̃��[�h�ړ��t���O
	m_fPosY			= CHAR_POSY;						// ��L�����N�^��Y���W�ʒu 
	m_fHeight		= CHAR_HEIGHT;						// ��L�����N�^�̍���
	m_fSpeed		= CHAR_SPEED;						// ��L�����N�^�̑��x
	m_fTexX			= INIT_TEX_X;						// PushEnter�̏����e�N�X�`��X���W
	m_fTexWidth		= INIT_TEX_WIDTH;					// PushEnter�̏����e�N�X�`���̕�
	m_fSpeedTex		= TEX_SPEED;						// PushEnter�̃A�j���[�V�������x
	m_nTimeCnt		= CLEAN_TIME;						// PushEnter�̃A�j���[�V�������x�}���J�E���g
}

//=============================================================================
// �֐���	: ~CTitle
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �Q�[���C���X�^���X�j��
//=============================================================================
CTitle::~CTitle(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �Ȃ�
// �@�\		: ������
//=============================================================================
HRESULT CTitle::Init(HWND hWnd)
{
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//----------------------------------------------------------------------------
	// �����_�����O�X�e�[�g�̏������ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//

	////-------------------------------------------------------------------------
	//// �T���v���[�X�e�[�g�̏������ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	if( m_pData == NULL )
	{
		// �f�[�^���Ȃ�����
		NEW_TYPE(m_pData, CData);				// �f�[�^���C���X�^���X����
		hr = m_pData->Init(hWnd, TITLE);	// �f�[�^��������
		ERROR_CHACK(hr);					// �G���[�`�F�b�N
	}

	m_pTitleScene[0] = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 5);
	if( m_pTitleScene[0] == NULL )
	{
		return NULL;
	}

	// �^�C�g���t�H���g�V�[��2D
	m_pTitleScene[1] = CScene2D::Create(40, 0, 500, 300, 2);
	if( m_pTitleScene[1] == NULL )
	{
		// �e�N�X�`��
		return E_FAIL;
	}
	
	// �󔠃V�[��2D
	m_pTitleScene[2] = CScene2D::Create(0, 150, WINDOW_WIDTH, 160, 1);
	if( m_pTitleScene[2] == NULL )
	{
		// �e�N�X�`��
		return E_FAIL;
	}

	// ��L�����p �ϐ�
	m_fPosY = 130;					// �ʒuY
	m_fHeight = 120;				// ����

	// ��L�����V�[��2D
	m_pTitleScene[3] = CScene2D::Create(120, m_fPosY, 300, m_fHeight, 3);
	if( m_pTitleScene[3] == NULL )
	{
		// �e�N�X�`��
		return E_FAIL;
	}

	// PushEnter�t�H���g2D
	m_pTitleScene[4] = CScene2D::Create(40, 300, 400, 100, 4);
	if( m_pTitleScene[4] == NULL )
	{
		// �e�N�X�`��
		return E_FAIL;
	}

	// PushEnter�t�H���g2D�̃e�N�X�`�����W�ݒ�
	m_pTitleScene[4]->SetTexure(m_fTexX, 0.0f, m_fTexWidth, 1.0f);

	return S_OK;
}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �I��
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();		// �V�[���j��
	CLASS_DELETE(m_pData);		// �^�C�g���Ŏg�����f�[�^�j��
}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �X�V
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();		// �L�[�{�[�h���擾
	int nColor = CManager::GetFade()->GetColor();						// ���݂̃t�F�[�h�̐F�擾
	
	// �t�F�[�h���̃{�^�������K�[�h
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE  )
	{
		// �t�F�[�h���Ă��Ȃ����			
		if( m_fPosY <= 80 )
		{
			// 20���l�������ɂȂ�����
			 m_fSpeed = 1;						// ��L��������Ɉړ�������
		}
		if( m_fPosY >= 140 )
		{
			// 
			m_fSpeed = -1;						// ��L���������Ɉړ�������
		}
		m_fPosY += m_fSpeed;					// ��L�����̏㉺�ړ�

		// ���x�̗}��
		if( m_nTimeCnt > MAX_TIME)
		{
			// �^�C���J�E���g���ō����Ԃ������Ă�����
			if( m_fTexWidth >= 1.0f)
			{
				// �e�N�X�`����X���W��1.0f�𒴂�����
				m_fTexX = INIT_TEX_X;			// �e�N�X�`�����W�ʒu��������
				m_fTexWidth = INIT_TEX_WIDTH;		// �e�N�X�`�����W�ʒu��������
			}
			else
			{
				m_fTexX += m_fSpeedTex;			// �e�N�X�`�����W�𓮂���
				m_fTexWidth += m_fSpeedTex;		// �e�N�X�`�����W�𓮂���
			}
			m_nTimeCnt = 0;						// �}���J�E���g��������
		}
		m_nTimeCnt += 16;						// �}���J�E���g���J�E���g�A�b�v

		// ��L�������ړ�������
		m_pTitleScene[3]->SetPosition(0, m_fPosY);
		
		// PushEnter�̃��S���A�j���[�V���������� 
		m_pTitleScene[4]->SetTexure(m_fTexX, 0.0f, m_fTexWidth, 1.0f); 
		CScene::UpdateAll();							// �V�[�����X�V
		if( pKeyboard->KeyPush(DIK_RETURN) )
		{
			// ENTER�L�[�������ꂽ��
			m_bFace = true;								// ���̃t�F�[�Y�t���O��ON��
			CManager::GetFade()->SetFadeMode(CFade::FADEMODE_OUT);	// �t�F�[�h�̃��[�h�ݒ�
		}
	}

	CManager::GetFade()->Update();

	// ��ʑJ�ڏ���
	if( nColor >= 255 && m_bFace == true )
	{
		// �t�F�[�h�̐F���O(��)�ł���莟�̃t�F�[�Y�t���O��ON�ł����
		CManager::SetMode(CManager::MODE_TUTORIAL);		// �Q�[����ʂɑJ��
	}

}

//=============================================================================
// �֐���	: 
// �߂�l	:
// ����		:
// �@�\		: �`��
//=============================================================================
void CTitle::Draw(void)
{
	CScene::DrawAll();
}
