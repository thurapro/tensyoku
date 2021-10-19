//=============================================================================
// �`�揈�� [scene.cpp]
//
// �����	: ���� �Y��
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "number.h"
#include "Timer.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer::CTimer(void)
{
	// �e�����o�ϐ�������
	ZeroMemory(m_pNumber, sizeof(m_pNumber) );		// �ԍ�����������NULL������
	m_pVertexBuffer = NULL;							// ���_�o�b�t�@��NULL������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimer::~CTimer(void)
{
	// �Ȃ�
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTimer::Init(void)
{	
	return S_OK;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTimer::Init(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum)
{
	// �摜��ǂݍ���
	m_pTexture = NULL;							// �e�N�X�`��NULL������
	m_nTimerCnt = 0;							// ���Ԃ�1�b�ɕϊ�	
	m_nTime = 0;								// ���݂̎���

	m_nTexNum = nTexNum;						//�@�e�N�X�`���ԍ�

	
	//CTexture *pTex = CGame::GetData()->GetTexture();		// �Q�[���Ŏg����摜�擾

	//int  i	=  pTex->GetTextureNum();
	//if( pTex->GetTextureNum() < m_nTexNum ||
	//	m_nTexNum < 0 )
	//{
	//	return E_FAIL;
	//}

	D3DXVECTOR3 Pos[4];
	float PosX = fPosX;
	float Width = fWidth;
	float PosY = fPosY;
	float Height = fPosY + fHeight;
	float fMinPosX[MAX_TIMER];
	float fMin = fPosX;
	float fMaxPosX[MAX_TIMER];
	float fMax = fPosX + fWidth;

	for( int i = 0; i < MAX_TIMER; i++ )
	{
		fMinPosX[i] = fMin;
		fMaxPosX[i] = fMax;
		fMin = fMaxPosX[i];
		fMax += Width;
	}

	for( int nScore = 0; nScore < MAX_TIMER; nScore++ )
	{
		for( int pos = 0; pos < 4; pos++)
		{
		
			Pos[pos] = D3DXVECTOR3(PosX, PosY, 0.0f);
			if( PosX >= fMaxPosX[nScore] )
			{
				PosX = fMinPosX[nScore];
			}
			else
			{
				PosX += Width;
			}
			if( pos > 0)
			{
				PosY = Height;
			}
			else
			{
				PosY = fPosY;
			}
		}
		PosX = fMaxPosX[nScore];
		PosY = fPosY;

		m_pNumber[nScore] = CNumber::Create(Pos[0], Pos[1], Pos[2], Pos[3], m_nTexNum);
		if( m_pNumber == NULL )
		{
			return E_FAIL;
		}
	}

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CTimer::Uninit(void)
{
	// 2D�I�u�W�F�N�g�j��
	CScene2D::Uninit();
	
	for( int i = 0; i < MAX_TIMER; i++ )
	{
		if(m_pNumber[i] != NULL )
		{	
			// �^�C�}�[�Ɏg�����ԍ��j��
			m_pNumber[i]->Uninit();			// �ԍ��j��
			m_pNumber[i] = NULL;			// �ԍ��̕ϐ���NULL��
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CTimer::Update(void)
{
	m_nTimerCnt++;
	if( m_nTimerCnt % 60 == 0 )
	{
		m_nTime++;
		m_nTimerCnt = 0;
	}
	
	SetTimer(m_nTime);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	for( int i = 0; i < MAX_TIMER; i++ )
	{
		// ���������`��
		m_pNumber[i]->Draw();		// �ԍ���`��
	}
}

//=============================================================================
// �^�C�}�[�Z�b�g
//=============================================================================
void CTimer::SetTimer( unsigned int nNumber )
{
	int Num = 0;								// �������o������
	int Ket = nNumber;							// ���w�肵�Ă��鐔
	for( int i = MAX_TIMER - 1; i >= 0; i-- )
	{	
   		Num = Ket % 10;							// 0�`9�܂ł̔ԍ������o��
		Ket = Ket / 10;							// ���������o��
		m_pNumber[i]->SetNumberTexture( Num );	// �ԍ����Z�b�g
	}
}

//=============================================================================
// �^�C�}�[���쐬
//=============================================================================
CTimer *CTimer::Create(float fPosX, float fWidth, float fPosY, float fHeight, unsigned int nTexNum)
{
	HRESULT hr;
	CTimer *pTimer;
	pTimer = NEW CTimer;
	hr = pTimer->Init(fPosX, fWidth, fPosY, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return NULL;
	}
	else
	{
		return pTimer;
	}
}

