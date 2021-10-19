//============================================================================= 
// 2D�I�u�W�F�N�g���� [ scene2D.cpp ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: 2D�I�u�W�F�N�g�쐬����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

#include "manager.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	POLYGON_NUM		(2)		// �|���S����
#define START_VERTEX	(0)		// �����n�߂钸�_
#define MAX_VERTEX		(4)		// �ő咸�_��
#define TEXTURE_NUM		(-1)	// �e�N�X�`���ԍ�������

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// �֐���	: CScene
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X����	( ������ )
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objType):CScene(nPriority, objType)
{
	m_pVertexBuffer = NULL;			// ���_�o�b�t�@������
	m_nTextureNum	= TEXTURE_NUM;	// �e�N�X�`��������
	m_pTexture		= NULL;			// �e�N�X�`���|�C���^������
}

//=============================================================================
// �֐���	: ~CScene
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: �C���X�^���X�j��	(�I������)
//=============================================================================
CScene2D::~CScene2D(void)
{
}

//=============================================================================
// �֐���	: Create
// �߂�l	: CScene2D
// �����l	: �����W( X��, Y�� ) �傫��( �� , ���� ), �ǂ̃e�N�X�`�����g����
// �@�\		: 2D�I�u�W�F�N�g�����
//=============================================================================
CScene2D *CScene2D::Create(float fPosX, float fPosY,
							float fWidth, float fHeight,
							unsigned short nTexturenNumber)
{		
	HRESULT hr;									// �G���[�`�F�b�N�ϐ�
	CScene2D *pScene2D = NULL;					// 2D�I�u�W�F�N�g�ϐ�

	// ����2D�I�u�W�F�N�g������Ă��Ȃ����
	NEW_TYPE(pScene2D, CScene2D);				// �C���X�^���X����
	hr = pScene2D->Init(fPosX, fPosY,		 
						fWidth, fHeight, 
						nTexturenNumber);		// 2D�I�u�W�F�N�g�̏�����
	if( FAILED(hr) )
	{
		// 2D�I�u�W�F�N�g�쐬���s
		return NULL;							// NULL��Ԃ�
	}

	// �쐬����
	return pScene2D;							// ���ꂽ2D��Ԃ�
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// �����l	: �Ȃ�
// �@�\		: �Ȃ�
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �����͓��ɂȂ�
	return S_OK;
}

//=============================================================================
// �֐���	: Init
// �߂�l	: HRESULT
// �����l	: �����W( X��, Y�� ) �傫��( �� , ���� ), �ǂ̃e�N�X�`�����g����
// �@�\		: 2D�I�u�W�F�N�g�����
//=============================================================================
HRESULT CScene2D::Init(float fPosX, float fPosY, 
						 float fWidth, float fHeight,
						 unsigned short nTextureNumber)
{
	HRESULT hr;						// �G���[�`�F�b�N�ϐ�

	m_nTextureNum = nTextureNumber;	// �e�N�X�`���ԍ��ۑ�

	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:
	//	if( m_nTextureNum > CLogo::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		m_pTexture = NULL;
	//	}
	//	else
	//	{
	//		m_pTexture = CLogo::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TITLE:
	//	if( m_nTextureNum > CTitle::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CTitle::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TUTORIAL:
	//	if( m_nTextureNum > CTutorial::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CTutorial::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_GAME:
	//	if( m_nTextureNum > CGame::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//case CManager::MODE_RESULT:
	//	if( m_nTextureNum > CResult::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CResult::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//case CManager::MODE_RANKING:
	//	if( m_nTextureNum > CRanking::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CRanking::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//default :
	//	return E_FAIL;
	//	break;
	//}

	// ���_�쐬
	hr = MakeVertex(fPosX, fPosY, fWidth, fHeight);
	ERROR_CHACK(hr);	// �G���[�`�F�b�N

	return S_OK;		// ����ɏ��������ꂽ
}

//=============================================================================
// �֐���	: Uninit
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: 2D�I�u�W�F�N�g�j��
//=============================================================================
void CScene2D::Uninit(void)
{
	SALF_RELEASE(m_pVertexBuffer);	// ���_�o�b�t�@�j��
	Release();						// �V�[�����X�g�\�����玩����j��
}

//=============================================================================
// �֐���	: Update
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: 2D�I�u�W�F�N�g�X�V
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// �֐���	: Draw
// �߂�l	: �Ȃ�
// �����l	: �Ȃ�
// �@�\		: 2D�I�u�W�F�N�g�`��
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	// ���_�t�H�[�}�b�g���Z�b�g
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D_TEX);
	
	// ���_�o�b�t�@�[�̃Z�b�g
	pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));
	
	// �e�N�X�`���[�Z�b�g
	pRenderer->GetDevice()->SetTexture(0, m_pTexture);

	// �v���~�e�B�u
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, START_VERTEX, POLYGON_NUM);

	// ����̃e�N�X�`�����c��Ȃ��悤��NULL����
	pRenderer->GetDevice()->SetTexture(0, NULL);
}

//=============================================================================
// �֐���	: MakeVertex
// �߂�l	: HRESULT
// �����l	: �����W( X��, Y�� ) �傫��( �� , ���� )
// �@�\		: 2D�I�u�W�F�N�g�̒��_�쐬
//=============================================================================
HRESULT CScene2D::MakeVertex(float fPosX, float fPosY, float fWidth, float fHeight)
{
	HRESULT		hr;					// �G���[�`�F�b�N�ϐ�
	VERTEX_2D	*pVtx;				// ���_�쐬�p�̊i�[�ϐ�
	CRenderer *pRenderer = NULL;	// �����_���[�|�C���^
	
	// �����_���[�擾
	pRenderer = CManager::GetRenderer();	
	
	// ���_�o�b�t�@�쐬
	hr = pRenderer->GetDevice()->CreateVertexBuffer( sizeof(VERTEX_2D) * MAX_VERTEX,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_2D_TEX,
													D3DPOOL_MANAGED,
													&m_pVertexBuffer,
													NULL );
	ERROR_CHACK(hr);	// �쐬�ł����̂��`�F�b�N
	
	// ���_�o�b�t�@�[���b�N
	hr = m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// �傫������
	fWidth += fPosX;	// ���𒲐�
	fHeight += fPosY;	// �����𒲐�

	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].Vertex = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].Vertex = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].Vertex = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].Vertex = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F���
	pVtx[0].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].Diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`���[���W�ݒ�
	pVtx[0].Texture = D3DXVECTOR2(0, 0);
	pVtx[1].Texture = D3DXVECTOR2(1, 0);
	pVtx[2].Texture = D3DXVECTOR2(0, 1);
	pVtx[3].Texture = D3DXVECTOR2(1, 1);

	// �ʒu�̕ۑ�
	m_pos.x = fPosX;	// X���̈ʒu�ۑ�	
	m_pos.y = fPosY;	// Y���̈ʒu�ۑ�

	// ���b�N����
	hr = m_pVertexBuffer->Unlock();

	return S_OK;		// ����ɒ��_�쐬�ł���
}

//=============================================================================
// �֐���	: SetPosition
// �߂�l	: �Ȃ�
// �����l	: �z�u������W( X��, Y�� ) �傫��( �� , ���� )
// �@�\		: ���W�ݒ�
//=============================================================================
void CScene2D::SetPosition(float fPosX, float fPosY,
							float fWidth, float fHeight)
{
	VERTEX_2D	*pVtx;		// ���_�쐬�p�̊i�[�ϐ�
	
	// �傫������
	fWidth += fPosX;		// ���̒���		
	fHeight += fPosY;		// �����̒���

	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�o�b�t�@�[�ʒu�Z�b�g
	pVtx[0].Vertex = D3DXVECTOR3(fPosX, fPosY, 0.0f);
	pVtx[1].Vertex = D3DXVECTOR3(fWidth, fPosY, 0.0f);
	pVtx[2].Vertex = D3DXVECTOR3(fPosX,  fHeight, 0.0f);
	pVtx[3].Vertex = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// �ʒu�̐ݒ�
	m_pos.x = fPosX;		// X�ʒu�ݒ�
	m_pos.y = fPosY;		// Y�ʒu�ݒ�

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}

//=============================================================================
// �֐���	: SetColor
// �߂�l	: �Ȃ�
// �����l	: �F�ݒ� ( ��, ��, ��, �����x )
// �@�\		: �F�ݒ�
//=============================================================================
void CScene2D::SetColor(int nR, int nG, int nB, int nA)
{
	VERTEX_2D	*pVtx;				// ���_�쐬�p�̊i�[�ϐ�
	
	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�̐F�ݒ�
	pVtx[0].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[1].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[2].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);
	pVtx[3].Diffuse = D3DCOLOR_RGBA(nR, nG, nB, nA);

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}

//=============================================================================
// �֐���	: SetTexture
// �߂�l	: �Ȃ�
// �����l	: �z�u������W( X��, Y�� ) �傫��( �� , ���� )
// �@�\		: �e�N�X�`�����W�ݒ�
//=============================================================================
void CScene2D::SetTexure(float fTexX, float fTexY, 
							float fTexWidth, float fTexHeight)
{
	VERTEX_2D	*pVtx;				// ���_�쐬�p�̊i�[�ϐ�
	
	// ���_�o�b�t�@�[���b�N
	m_pVertexBuffer->Lock(0, 0, (void **)&pVtx, 0);
	
	// �e�N�X�`���[���W�ݒ�
	pVtx[0].Texture = D3DXVECTOR2(fTexX, fTexY);
	pVtx[1].Texture = D3DXVECTOR2(fTexWidth, fTexY);
	pVtx[2].Texture = D3DXVECTOR2(fTexX, fTexHeight);
	pVtx[3].Texture = D3DXVECTOR2(fTexWidth, fTexHeight);

	m_pVertexBuffer->Unlock();		// ���_�A�����b�N
}

//=============================================================================
// �֐���	: SetTexNum
// �߂�l	: �Ȃ�
// �����l	: �e�N�X�`���ԍ�
// �@�\		: �e�N�X�`���ԍ��ݒ�
//=============================================================================
void CScene2D::SetTexNum(unsigned short nTexNum)
{
	m_nTextureNum = nTexNum;		// �e�N�X�`���ԍ��ۑ�
	
	//switch( CManager::GetMode() )
	//{
	//case CManager::MODE_LOGO:
	//	if( m_nTextureNum > CLogo::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		m_pTexture = NULL;
	//	}
	//	else
	//	{
	//		m_pTexture = CLogo::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_TITLE:
	//	if( m_nTextureNum > CTitle::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CTitle::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_GAME:
	//	if( m_nTextureNum > CGame::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CGame::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;

	//case CManager::MODE_RESULT:
	//	if( m_nTextureNum > CResult::GetData()->GetTexture()->GetTextureNum()
	//		|| m_nTextureNum < 0 )
	//	{
	//		// �e�N�X�`�������݂��Ȃ�
	//		m_pTexture = NULL;				// �G���[�R�[�h
	//	}
	//	else
	//	{
	//		m_pTexture = CResult::GetData()->GetTexture()->GetTexture(m_nTextureNum);
	//	}
	//	break;
	//}
}