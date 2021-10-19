//=============================================================================
// �t�F�[�h���� [ fade.h ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: �t�F�[�h����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//=============================================================================
// �֐���	: CFade
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X����		( ������ )
//=============================================================================
CFade::CFade(void)
{
	m_pVertexBuffer = NULL;				// ���_�o�b�t�@������
	m_fadeMode		= FADEMODE_IN;		// �t�F�[�h���[�h������
	m_nTime			= 0;				// �t�F�[�h�̎���
	m_nTimeCnt		= 0;				// ���ԃJ�E���g
	m_nRed			= 0;				// �Ԓl������
	m_nGreen		= 0;				// �Βl������
	m_nBlue			= 0;				// �l������
	m_nAlpha		= 255;				// �A���t�@�[�l������
}

//=============================================================================
// �֐���	: ~CFade
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j��		( �I�� )
//=============================================================================
CFade::~CFade(void)
{
	// �C���X�^���X�j��
}

//=============================================================================
// �֐���	: Create
// �߂�l	: CFade		( ���s�@NULL )
// �����l	: ���b�Ńt�F�[�h���邩
// �@�\		: �t�F�[�h�쐬
//=============================================================================
CFade *CFade::Create(unsigned int nTime)
{
	HRESULT hr;					// �G���[�`�F�b�N
	CFade	*pFade = NULL;		// �t�F�[�h�|�C���^
	if( pFade == NULL )
	{
		// �t�F�[�h���쐬����Ă��Ȃ����
		pFade = NEW CFade;			// �t�F�[�h�C���X�^���X����
		hr = pFade->Init(nTime);	// �t�F�[�h������
		if( FAILED(hr) )
		{
			// �t�F�[�h�������ɖ�肠��
			return NULL;			// �G���[�R�[�h
		}
	}
	return pFade;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// �����l	: ���b�Ńt�F�[�h���邩
// �@�\		: �t�F�[�h������
//=============================================================================
HRESULT CFade::Init(unsigned int nTime)
{
	HRESULT hr;			// �G���[�`�F�b�N�ϐ�
	m_nTime = nTime;	// ���Ԃ�ۑ�
	
	m_fadeMode = FADEMODE_IN;	// �t�F�[�h���[�h�ݒ� 
	
	// ���_�쐬
	hr = MakeVerTex();	// ���_�쐬
	ERROR_CHACK(hr);	// �G���[�`�F�b�N
	return S_OK;		// ����R�[�h
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�F�[�h�I��
//=============================================================================
void CFade::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);		// ���_�o�b�t�@�j��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�F�[�h�C�� , �t�F�[�h�A�E�g �X�V
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	switch( m_fadeMode )
	{
	case FADEMODE_IN:			// �t�F�[�h�C��
		m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);							// ���_���b�N
		pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		m_pVertexBuffer->Unlock();												// ���_�A�����b�N
		if( m_nAlpha <= 0 )
		{
			// �A���t�@�[�l��0�ȉ��ɂȂ�����
			m_nAlpha		= 0;
			m_fadeMode = FADEMODE_NONE;			// �t�F�[�h���[�h��NONE�ɕύX
		}
		else
		{
			// �A���t�@�[�l��0���傫�����
			if( m_nTimeCnt >= m_nTime )
			{
				// �ݒ肳�ꂽ���Ԃ𒴂��Ă����
				m_nAlpha	-= 5;
				m_nTimeCnt	= 0;					// �^�C�}�[�J�E���g���O��
			}
			else
			{
				// �ݒ肳�ꂽ���Ԃ𒴂��Ă��Ȃ����
				m_nTimeCnt++;					// �^�C�}�[�J�E���g���グ��
			}
		}
		break;

	case FADEMODE_OUT:		// �t�F�[�h�A�E�g
		m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);							// ���_���b�N
		pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);	// ���_�F�ύX
		m_pVertexBuffer->Unlock();
		if( m_nAlpha >= 255 )
		{
			// �A���t�@�[�l��0�ȉ��ɂȂ�����
			m_nAlpha		= 255;
			m_fadeMode = FADEMODE_NONE;			// �t�F�[�h���[�h��NONE�ɕύX
		}
		else
		{
			// �A���t�@�[�l��0���傫�����
			if( m_nTimeCnt > m_nTime )
			{
				// �ݒ肳�ꂽ���Ԃ𒴂��Ă����
				m_nAlpha	+= 5;
				m_nTimeCnt = 0;					// �^�C�}�[�J�E���g���O��
			}
			else
			{
				// �ݒ肳�ꂽ���Ԃ𒴂��Ă��Ȃ����
				m_nTimeCnt++;					// �^�C�}�[�J�E���g���グ��
			}
		}
		break;
	case FADEMODE_NONE:							// �t�F�[�h���[�hNONE
		break;									// �����Ȃ�
	default:									// ����ȊO
		break;									// �����Ȃ�
	}
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�F�[�h�`��
//=============================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�t�H�[�}�b�g���Z�b�g
	pDevice->SetFVF(FVF_VERTEX_2D_FADE);
	
	// ���_�o�b�t�@�[�̃Z�b�g
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
		
	// �e�N�X�`���[�Z�b�g
	pDevice->SetTexture(0, NULL);

	// �v���~�e�B�u
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �֐���	: MakeVerTex
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�F�[�h���_�쐬
//=============================================================================
void CFade::SetFadeMode(FADEMODE fadeMode)
{
	m_fadeMode = fadeMode;
}

//=============================================================================
// �֐���	: MakeVerTex
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �t�F�[�h���_�쐬
//=============================================================================
HRESULT CFade::MakeVerTex(void)
{
	HRESULT hr;
	VERTEX_2D *pVtx;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�[�쐬
	hr = pDevice->CreateVertexBuffer( sizeof(VERTEX_2D) * 4 ,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D_FADE,
									D3DPOOL_MANAGED,
									&m_pVertexBuffer,
									NULL);
	//-----------------------
	// �쐬�ł��Ȃ�������
	if(FAILED(hr))
	{
		return hr;
	}

	// ���_�o�b�t�@�[���b�N
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	if(FAILED(hr))
	{
		return hr;
	}
	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].vtx = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pVtx[1].vtx = D3DXVECTOR3( (float)WINDOW_WIDTH, 0.0f, 0.0f );
	pVtx[2].vtx = D3DXVECTOR3( 0.0f, (float)WINDOW_HEIGHT, 0.0f );
	pVtx[3].vtx = D3DXVECTOR3( (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
	
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F���
	pVtx[0].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	// ���b�N����
	hr = m_pVertexBuffer->Unlock();	
	ERROR_CHACK(hr);	// �G���[�`�F�b�N
	return S_OK;
}


// end of file //