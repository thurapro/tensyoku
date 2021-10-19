//=============================================================================
// �f�o�b�O�R�[�h�o�͏���[debugproc.cpp]
// 
// ����� : ���� �Y��
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "debugproc.h"

//=============================================================================
//	�֐���	: CDebug
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O�C���X�^���X����
//=============================================================================
CDebug::CDebug(void)				
{
	ZeroMemory(&m_strDebug, MAX_STRING);	// �o�b�t�@������
	m_pFont		= NULL;						// �t�H���g�|�C���^������
	m_Polygon	= D3DPT_TRIANGLESTRIP;		// �|���S�����̏�����
	m_strLineType = NULL;					// �v���~�e�B�u���C���̎��
#ifdef _DEBUG
	m_bDebug	= true;						// �f�o�b�O���[�h��(false �����o�͂Ȃ�, true�����o��)
#else
	m_bDebug	= false;					// �f�o�b�O���[�h��(false �����o�͂Ȃ�, true�����o��)
#endif
}

//=============================================================================
//	�֐���	: ~CDebug
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O�C���X�^���X�j��
//=============================================================================
CDebug::~CDebug(void)
{
}

//=============================================================================
//	�֐���	: Init
//	�߂�l	: HRESULT
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O������
//=============================================================================
HRESULT CDebug::Init(void)
{
	// �f�o�b�O������
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�擾
		
	// �t�H���g�쐬
	hr = D3DXCreateFont( pRenderer->GetDevice(),			// �f�o�C�X
						12,									// �t�H���g�̍���
						8,									// �t�H���g�̕�
						0,									// �t�H���g�̑���
						1,									// �~�b�v�}�b�v���x��
						FALSE,								// �Α�
						SHIFTJIS_CHARSET,					// �L�����N�^�Z�b�g(�V�t�gJIS���w��)
						OUT_DEFAULT_PRECIS,					// �o�͐��x
						DEFAULT_QUALITY,					// �i��
						DEFAULT_PITCH,						// �s�b�`
						"Terminal"	,						// �t�H���g���ێ�
						&m_pFont);
	ERROR_CHACK(hr);										// �G���[�`�F�b�N
	

	return S_OK;											// �������I��
}

//=============================================================================
//	�֐���	: Uninit
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O�I��
//=============================================================================
void CDebug::Uninit(void)
{
	SALF_RELEASE(m_pFont);				// �f�o�b�O�j��
}

//=============================================================================
//	�֐���	: Update
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O�X�V
//=============================================================================
void CDebug::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetInput();
	
	// �f�o�b�O���[�h�ؑ֏���
	if( pKeyboard->KeyPush(DIK_F1) )
	{
		// �f�o�b�O���[�h�ݒ�
		if( m_bDebug == false )
		{
			// �f�o�b�O���[�h�łȂ����
			m_bDebug = true;				// �f�o�b�O�o�͂������Ȃ�
		}
		else
		{
			// �f�o�b�O���[�h�ł����
			m_bDebug = false;				// �f�o�b�O�o�͂��s��Ȃ�
		}
	} // �f�o�b�O���[�h�ؑ֏����I��

	// �f�o�b�O���[�h�̂ݗL��
	if( m_bDebug == true )
	{
		// �|���S�����̏������؂�ւ�����
		if( pKeyboard->KeyPush(DIK_F2) )
		{
			// ��ޑI��
			m_Polygon += 1;
			if( m_Polygon > D3DPT_TRIANGLEFAN )
			{
				m_Polygon = D3DPT_POINTLIST;
			}
		}
		else if( pKeyboard->KeyPush(DIK_F3) )
		{
			// ��ޑI��
			m_Polygon = D3DPT_TRIANGLESTRIP;
		}
	}
	else
	{
		// �g���C�A���O���X�g���b�v�ɕύX
		m_Polygon = D3DPT_TRIANGLESTRIP;
	}

	// ���C����ނ̖��O��ݒ�
	switch( m_Polygon )
	{
	case D3DPT_POINTLIST:						// �|�C���g���X�g
		m_strLineType = "D3DPT_POINTLIST";
		break;
	case D3DPT_LINELIST:						// ���C�����X�g
		m_strLineType = "D3DPT_LINELIST";
		break;
	case D3DPT_LINESTRIP:						// ���C���X�g���b�v
		m_strLineType = "D3DPT_LINESTRIP";
		break;
	case D3DPT_TRIANGLELIST:					// �g���C�A���O�����X�g
		m_strLineType = "D3DPT_TRIANGLELIST";
		break;
	case D3DPT_TRIANGLESTRIP:					// �g���C�A���O���X�g���b�v
		m_strLineType = "D3DPT_TRIANGLESTRIP";
		break;
	case D3DPT_TRIANGLEFAN:						// �g���C�A���O���t�@��
		m_strLineType = "D3DPT_TRIANGLEFAN";
		break;
	}
	Print("���C�����: %s\n", m_strLineType);
}


//=============================================================================
//	�֐���	: Draw
//	�߂�l	: �Ȃ�
//	����	: �Ȃ�
//	�@�\	: �f�o�b�O�`��
//=============================================================================
void CDebug::Draw(void)
{
	RECT rect = {0, 0, WINDOW_HEIGHT, WINDOW_WIDTH};	// �`��̈�w��

	if( m_bDebug == true )
	{
		// �f�o�b�O�o�̓��[�h�ɂȂ��Ă����
		m_pFont->DrawText(
					NULL,								// �X�v���C�g�@�\���g����
					m_strDebug,							// ������
					-1,									// ������(NULL�I�[�܂ŕ\��)
					&rect,								// �`��̈�
					DT_NOCLIP,							// �N���b�v���Ȃ�
					D3DCOLOR_XRGB(255, 192, 0) );		// �����F
	}
	
	// �f�o�b�O�o�b�t�@�N���A
	ZeroMemory(&m_strDebug, MAX_STRING);
}
	
//=============================================================================
//	�֐���	: Print
//	�߂�l	: �Ȃ�
//	����	: �o�͂�����������, �\���������ϐ�
//	�@�\	: �f�o�b�O�o�b�t�@�ɏ�������
//=============================================================================
void CDebug::Print(char *pFmt , ...)
{
	va_list pArg;							// �ϐ��錾 (�ψ������)
	char szBuffer[MAX_STRING];				// �ϐ��錾	(�o�b�t�@)
	ZeroMemory(szBuffer, MAX_STRING);		// �o�b�t�@�N���A
	va_start(pArg, pFmt);					// �������ʊJ�n
	vsprintf_s(szBuffer, pFmt, pArg);		// �o�b�t�@�ɏ�������
	va_end(pArg);							// �������ʏI��
	strcat(m_strDebug, szBuffer);			// �����������
}

//=============================================================================
//	�֐���	: GetPolygonLine
//	�߂�l	: �v���~�e�B�u���
//	����	: �Ȃ�
//	�@�\	: �v���~�e�B�u���̎�ނ��擾
//=============================================================================
D3DPRIMITIVETYPE CDebug::GetPolygonLine(void)
{ 
	return (D3DPRIMITIVETYPE)m_Polygon; 
}

//=============================================================================
//	�֐���	: GetDebugMode
//	�߂�l	: �f�o�b�O���[�h�Ȃ̂��̃t���O
//	����	: �Ȃ�
//	�@�\	: �v���~�e�B�u���̎�ނ��擾
//=============================================================================
bool CDebug::GetDebugMode(void)
{
	// �f�o�b�O���[�h�擾
	return m_bDebug;
}