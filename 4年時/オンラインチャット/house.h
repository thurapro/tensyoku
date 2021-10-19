//*********************************************************************
// 													
// House�̏���[ house.h ]									 
// House�̏������s���N���X
// 																	 
// Date:2013/11/18 NAME:YUTA MATSUO									 
// 																		
//*********************************************************************
//---------------------------
// �C���N���[�h�K�[�h
//---------------------------
#ifndef _HOUSE_H_
#define _HOUSE_H_

//--------------------------
// �w�b�_�[�t�@�C��
//--------------------------
#include "vector3D.h"
#include "object.h"
#include "drawModel.h"

//-------------------------------
// �N���X�錾
//-------------------------------
class CHouse : public CObject
{
public:
	CHouse( void );			// �R���X�g���N�^
	~CHouse( void );		// �f�X�g���N�^
	HRESULT Init( void );	// ����������
	void Uninit( void );	// �I������
	void Update( void );	// �X�V����
	void OnHit( VECTOR3D colPos, VECTOR3D objPos, VECTOR3D objOffset, COLSTATUS colStatus );	// �Փˏ���
	static CHouse* Create( int nPriority, char *pFileName, VECTOR3D vecPos );					// �ƍ쐬
	/*void SaveFile( FILE *fp )
	{
		fprintf( fp, "\n// wall001\n" );
		CObject::SaveFile( fp );
	};*/

private:
	CDrawModel		*m_pHouse;		// �`��p�̉ƃC���X�^���X
	CCollision		*m_pCollision;	// �����蔻��̃C���X�^���X
	VECTOR3D		m_offset;		// �I�t�Z�b�g
};

#endif
// EOF