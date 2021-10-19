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
#include "scene.h"
#include "scene2D.h"
#include "number.h"
#include "data.h"
#include "timer.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "game.h"

#include "ranking.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RANKING ("data/text/ranking.txt")

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CData		*CRanking::m_pData;							// �f�[�^�̎��̐���

//=============================================================================
// �֐���	: CRanking
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �����L���O�C���X�^���X����
//=============================================================================
CRanking::CRanking(void)
{
	m_pData			= NULL;							// �f�[�^������
	m_pRankBack		= NULL;							// �����L���O�w�i
	ZeroMemory(m_pRanking, sizeof(m_pRanking) );	// �����L���O������
	for( int i = 0; i < MAX_RANKING; i++ )
	{
		m_nNumber[i] = 100;
	}
	m_bFace			= false;						// ���̃��[�h�ړ��t���O
}

//=============================================================================
// �֐���	: ~CRanking
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �����L���O�C���X�^���X�j��
//=============================================================================
CRanking::~CRanking(void)
{
	// �Ȃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// ����		: �E�B���h�E�n���h��
// �@�\		: ������
//=============================================================================
HRESULT CRanking::Init(HWND hWnd)
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
		hr = m_pData->Init(hWnd, RANKING);	// �f�[�^������
		ERROR_CHACK(hr);					// �f�[�^���쐬����Ă��邩
	}

	m_pRankBack = CScene2D::Create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if( m_pRankBack == NULL )
	{
		return E_FAIL;
	}

	m_pRanking[0] = CTimer::Create(WINDOW_WIDTH / 2, 30, 10, 60, 1);
	m_pRanking[1] = CTimer::Create(WINDOW_WIDTH / 2, 30, 100, 60, 1);
	m_pRanking[2] = CTimer::Create(WINDOW_WIDTH / 2, 30, 190, 60, 1);
	m_pRanking[3] = CTimer::Create(WINDOW_WIDTH / 2, 30, 280, 60, 1);
	m_pRanking[4] = CTimer::Create(WINDOW_WIDTH / 2, 30, 370, 60, 1);

	int nCurRankData = CManager::GetRankScore();

	for(int i = 0; i < MAX_RANKING; i++ )
	{
		// �召�m�F
		if( nCurRankData < m_nNumber[i] )
		{
			// �������ꍇ�̓X�R�A�����炷
			for( int n = (MAX_RANKING - 1); n > i; n-- )
			{
				m_nNumber[n] = m_nNumber[n - 1]; 
			}
			m_nNumber[i] = nCurRankData;
			break;
		}
	}

	FILE *fp;
	fopen_s(&fp, "data/text/ranking/rankdata.txt", "w+");
	
	for( int i = 0; i < MAX_RANKING; i++ )
	{
		m_pRanking[i]->SetTimer(m_nNumber[i]);
		fprintf(fp, "%d\n", m_nNumber[i]);
	}

	fclose(fp);

	return S_OK;
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �I��
//=============================================================================
void CRanking::Uninit(void)
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
void CRanking::Update(void)
{
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
	if( CManager::GetFade()->GetFadeMode() == CFade::FADEMODE_NONE && m_bFace == true )
	{
		// �t�F�[�h�̐F��0(��)�Ŏ��̃t�F�[�Y�ړ��t���O��ON�ł����
		CManager::SetMode(CManager::MODE_LOGO);			// ���U���g�w�ڍs
	}
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// ����		: �Ȃ�
// �@�\		: �`��
//=============================================================================
void CRanking::Draw(void)
{
	CScene::DrawAll();
}
