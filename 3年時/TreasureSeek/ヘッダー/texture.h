//=============================================================================
// �e�N�X�`���ۑ�����	[ texture.h ]
//
// �쐬�� : ���� �Y��
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// �N���X��`
//=============================================================================
class CTexture
{
public:
	CTexture();						// �C���X�^���X����
	~CTexture();					// �C���X�^���X�j��
	HRESULT Init(char *FileName);	// �e�N�X�`��������
	void Uninit(void);				// �e�N�X�`���I��
	HRESULT LoardTexture(char *FileName); // �e�N�X�`���ǂݍ���

	unsigned int GetTextureNum(void){return m_nTextureNum - 1;}					// �e�N�X�`����
	LPDIRECT3DTEXTURE9 GetTexture(int nNumber){return m_ppTexture[nNumber];}	// �e�N�X�`���擾
private:
	int	m_nTextureNum;					// �e�N�X�`����
	LPDIRECT3DTEXTURE9 *m_ppTexture;	// �e�N�X�`���ۑ�
};

#endif  // _TEXTURE_H_