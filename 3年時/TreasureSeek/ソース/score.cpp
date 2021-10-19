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
#include "data.h"
#include "game.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority, OBJTYPE objType):CScene2D(nPriority, objType)
{
	// �e�����o�ϐ�������

	ZeroMemory(m_pNumber, sizeof(m_pNumber) );		// �ԍ�����������NULL������
	m_pVertexBuffer = NULL;							// ���_�o�b�t�@��NULL������
	m_nScore = 0;									// �X�R�A������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore(void)
{
	// �Ȃ�
}

//=============================================================================
// �X�R�A�[���쐬
//=============================================================================
CScore *CScore::Create(float fPosX, float fWidth, float fPosY, 
						float fHeight, unsigned int nTexNum)
{
	HRESULT hr;
	CScore *pScore;
	pScore = NEW CScore;
	hr = pScore->Init(fPosX, fWidth, fPosY, fHeight, nTexNum);
	if(FAILED(hr))
	{
		return NULL;
	}
	else
	{
		return pScore;
	}
}

//=============================================================================
// ������
//=============================================================================
HRESULT CScore::Init(void)
{	
	return S_OK;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CScore::Init(float fPosX, float fWidth, float fPosY, 
						float fHeight, unsigned int nTexNum)
{
	CTexture *pTex = CGame::GetData()->GetTexture();		// �Q�[���Ŏg����摜�擾

	// �摜��ǂݍ���
	m_pTexture = NULL;										// �e�N�X�`��NULL������

	D3DXVECTOR3 Pos[4];
	float PosX = fPosX;
	float Width = fWidth;
	float PosY = fPosY;
	float Height = fHeight;
	float fMinPosX[MAX_SCORE];
	float fMin = fPosX;
	float fMaxPosX[MAX_SCORE];
	float fMax = fPosX + fWidth;

	for( int i = 0; i < MAX_SCORE; i++ )
	{
		fMinPosX[i] = fMin;
		fMaxPosX[i] = fMax;
		fMin = fMaxPosX[i];
		fMax += Width;
	}

	for( int nScore = 0; nScore < MAX_SCORE; nScore++ )
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
				PosY = fHeight;
			}
			else
			{
				PosY = fPosY;
			}
		}
		PosX = fMaxPosX[nScore];
		PosY = fPosY;

		m_pNumber[nScore] = CNumber::Create(Pos[0], Pos[1], Pos[2], Pos[3], nTexNum);
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
void CScore::Uninit(void)
{
	// 2D�I�u�W�F�N�g�j��
	CScene2D::Uninit();
	
	for( int i = 0; i < MAX_SCORE; i++ )
	{
		if(m_pNumber[i] != NULL )
		{	
			// �X�R�A�[�Ɏg�����ԍ��j��
			m_pNumber[i]->Uninit();			// �ԍ��j��
			m_pNumber[i] = NULL;			// �ԍ��̕ϐ���NULL��
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for( int i = 0; i < MAX_SCORE; i++ )
	{
		// ���������`��
		m_pNumber[i]->Draw();		// �ԍ���`��
	}
}

//=============================================================================
// �X�R�A�[�Z�b�g
//=============================================================================
void CScore::SetScore( unsigned int nNumber )
{
	m_nScore += nNumber;						// �X�R�A�����_ 
	int Num = 0;								// �������o������
	int Ket = m_nScore;							// ���w�肵�Ă��鐔
	for( int i = MAX_SCORE - 1; i >= 0; i-- )
	{	
   		Num = Ket % 10;							// 0�`9�܂ł̔ԍ������o��
		Ket = Ket / 10;							// ���������o��
		m_pNumber[i]->SetNumberTexture( Num );	// �ԍ����Z�b�g
	}
}


