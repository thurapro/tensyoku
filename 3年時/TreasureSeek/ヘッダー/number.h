//=============================================================================
// �ԍ�����[number.h]
//
// ����� : ���� �Y��
//
// �@�\ :  �X�R�A�[�E�^�C�}�[�Ȃ� 
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D_TEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 2D�e�N�X�`���[�ݒ�

//=============================================================================
// �N���X�錾
//=============================================================================
class CNumber
{
public:
	CNumber(void);											// �ԍ��C���X�^���X����
	~CNumber(void);											// �ԍ��C���X�^���X�j��

	static CNumber	*Create(D3DXVECTOR3 fPosLeftTop, 
							D3DXVECTOR3 fPosRightTop, 
							D3DXVECTOR3 fPosLeftBottom, 
							D3DXVECTOR3 fPosRightBottom,
							unsigned int nTexNum);			// �ԍ��쐬

	static CNumber	*Create(float fPosX, float fPosY, 
							float fWidth, float fHeight, 
							unsigned int nTexNum);			// �ԍ��쐬

	HRESULT Init(D3DXVECTOR3 fTexPosLeftTop, 
				D3DXVECTOR3 fPosRightTop, 
				D3DXVECTOR3 fPosLeftBottom, 
				D3DXVECTOR3 fPosRightBottom,
				unsigned int nTexNum);						// �ԍ�����������

	HRESULT Init(float fPosX, float fPosY,
				float fWidth, float fHeight,
				unsigned int nTexNum);						// �ԍ�����������

	void Uninit(void);										// �ԍ��I������
	void Update(void);										// �ԍ��X�V����
	void Draw(void);										// �ԍ��`�揈��

	// �e�N�X�`�����W�ʒu�Z�b�g 
	void SetNumberTexture(unsigned int nNumber);
	
	void SetPosition(float fPosX, float fPosY,
					float fWidht, float fHeight);
	
	void SetPosHeight(float fPosY, float fHeight);
	void SetNumColor(int nR, int nG, int nB, int nA); 

	unsigned int GetNumber(void){return m_nNumber;}

private:
	// ���_�쐬
	HRESULT MakeVerTex(D3DXVECTOR3 fPosLeftTop, D3DXVECTOR3 fPosRightTop, D3DXVECTOR3 fPosLeftBottom, D3DXVECTOR3 fPosRightBottom);
	HRESULT	MakeVerTex(float fPosX, float fPosY, float fWidth, float fHeight);

	// 2D�\���̐錾
	typedef struct
	{
		D3DVECTOR	vtx;						// ���_���W
		float		rhw;						// �������W�̋t��
		D3DCOLOR	diffuse;					// �F���
		D3DXVECTOR2	tex;						// �e�N�X�`���[���W
	}VERTEX_2D;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	// ���_�o�b�t�@�[
	LPDIRECT3DTEXTURE9		m_pTexture;			// �^�C�g���摜
	unsigned int			m_nNumber;
};

#endif // _NUMBER_H_