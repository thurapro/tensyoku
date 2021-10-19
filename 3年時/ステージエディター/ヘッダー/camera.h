//=============================================================================
// �J�������� [camera.cpp]
//
// ���O	: ���� �Y��
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// �N���X��`
//=============================================================================
class CCamera
{
public:
	CCamera(void);												// �J�����C���X�^���X����
	~CCamera(void);												// �J�����C���X�^���X�j��
	void		Init(void);										// �J����������
	void		Uninit(void);									// �J�����̏I������
	void		Update(void);									// �J�����X�V
	void		Draw(void);										// �J�����`��
	D3DXMATRIX	GetView(void){return m_mtxView;}				// �J�����r���[�擾
	float		GetRot(void){return m_fRadian;}					// �J�����̊p�x

private:
	D3DXVECTOR3 m_posCameraP;								// �J�������_
	D3DXVECTOR3 m_posCameraR;								// �J���������_
	D3DXVECTOR3 m_vecCameraV;								// ������x�N�g��
	D3DXVECTOR3 m_rotCamera;								// �J�����̌���
	D3DXVECTOR3	m_rotSave;									// �J�����̌����̕ۑ�
	D3DXVECTOR3 m_Length;									// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX m_mtxView;									// �r���[�}�g���b�N�X
	float	m_fLengthInterval;								// �J�����̊Ԋu
	float	m_fRadian;										// ���W�A���p�x
	float	m_move;											// �J�����̈ړ�
};

#endif // _CAMERA_H_

///// end of file /////