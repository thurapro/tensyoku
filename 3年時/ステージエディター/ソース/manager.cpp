//=============================================================================
// �c�[���쐬�̑O�菇�@�@�@�@�@�@�t�B�[���h�쐬�c�[���p
//  
// ���C������ [maneger.cpp]
//
// �@�\ : �}�l�[�W���[����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "field.h"
#include "wall.h"
#include "mountain.h"
#include "sceneX.h"
#include "sky.h"
#include "data.h"
#include "stage.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CRenderer		*CManager::m_pRenderer;			// �����_���[�|�C���^�錾
CInputKeyboard	*CManager::m_pKeyboard;			// �L�[�{�[�h�|�C���^�錾
CDebug			*CManager::m_pDebug;			// �f�o�b�O�|�C���^�錾
CCamera			*CManager::m_pCamera;			// �J�����|�C���^�錾
CData			*CManager::m_pData;				// �f�[�^�|�C���^�錾
CStage			*CManager::m_pStage;			// �X�e�[�W�|�C���^�錾

//=============================================================================
//	�֐���	: CManager
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�C���X�^���X����
//=============================================================================
CManager::CManager(void)
{
	// �C���X�^���X����
	m_pRenderer	= NULL;			// �����_���[�|�C���^������
	m_pKeyboard	= NULL;			// �L�[�{�[�h�|�C���^������
	m_pDebug	= NULL;			// �f�o�b�O�|�C���^������
	m_pCamera	= NULL;			// �J�����|�C���^������
	m_pLight	= NULL;			// ���C�g�|�C���^������
	m_pData		= NULL;			// �f�[�^�|�C���^������
	m_pStage	= NULL;
}

//=============================================================================
//	�֐���	: CManager
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�C���X�^���X�j��
//=============================================================================
CManager::~CManager(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: HINSTANCE , HWND , BOOL
//	�@�\	: �}�l�[�W���[������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr;
	
	NEW_TYPE(m_pRenderer, CRenderer);			// �����_���[�C���X�^���X����
	hr = m_pRenderer->Init(hWnd, bWindow);		// �����_���[������
	ERROR_CHACK(hr);							// �G���[�`�F�b�N
	
	NEW_TYPE(m_pKeyboard, CInputKeyboard);		// �L�[�{�[�h�C���X�^���X����
	hr = m_pKeyboard->Init(hInstance, hWnd);	// �L�[�{�[�h������
	ERROR_CHACK(hr);							// �G���[�`�F�b�N

	NEW_TYPE(m_pDebug, CDebug);					// �f�o�b�O�C���X�^���X����
	hr = m_pDebug->Init();						// �f�o�b�O������
	ERROR_CHACK(hr);							// �G���[�`�F�b�N

	NEW_TYPE(m_pCamera, CCamera);				// �J�����C���X�^���X����
	m_pCamera->Init();							// �J����������

	NEW_TYPE(m_pLight, CLight);					// ���C�g�C���X�^���X����
	hr = m_pLight->Init();						// ���C�g������
	ERROR_CHACK(hr);							// �G���[�`�F�b�N

	NEW_TYPE(m_pData, CData);					// �f�[�^����
	hr = m_pData->Init(hWnd, "DATA/TEXT/GAME.txt");
	ERROR_CHACK(hr);

	NEW_TYPE(m_pStage, CStage);
	hr = m_pStage->Init();
	ERROR_CHACK(hr);

	return S_OK;								// �}�l�[�W������������
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�j��
//=============================================================================
void CManager::Uninit(void)
{
	CLASS_DELETE(m_pRenderer);		// �����_���[�C���X�^���X�j��
	CLASS_DELETE(m_pKeyboard);		// �L�[�{�[�h�C���X�^���X�j��
	CLASS_DELETE(m_pDebug);			// �f�o�b�O�C���X�^���X�j��
	CLASS_DELETE(m_pCamera);		// �J�����C���X�^���X�j��
	CLASS_DELETE(m_pLight);			// ���C�g�C���X�^���X�j��
	CLASS_DELETE(m_pData);			// �f�[�^�C���X�^���X�j��
	CLASS_DELETE(m_pStage);			// �X�e�[�W�C���X�^���X�j��
	CScene::ReleaseAll();			// �V�[���j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �}�l�[�W���[�X�V
//=============================================================================
void CManager::Update(void)
{
	m_pKeyboard->Update();			// �L�[�{�[�h�X�V
	m_pDebug->Update();				// �f�o�b�O�X�V
	m_pCamera->Update();			// �J�����X�V	
	m_pStage->Update();

	if( m_pKeyboard->KeyPush(DIK_F12) )
	{
		m_pStage->Save();
		m_pDebug->Print("�Z�[�u������");
	}
}

//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �f�o�C�X
//	�@�\	: �}�l�[�W���[�`��
//=============================================================================
void CManager::Draw(void)
{
	///// �`�揈�� /////
	m_pRenderer->Draw();			// �����_���[�`��
}

///// end of file /////




