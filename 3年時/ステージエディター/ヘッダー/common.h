//============================================================================= 
// �ꊇ�Ǘ����� [ common.h ]
// 
// �쐬��	: ���� �Y��
//
// �@�\		: �w�b�_�[�Ȃǂ��ꊇ�Ǘ�
//=============================================================================

//=============================================================================
// 2�d�C���N���[�h�h�~
//=============================================================================
#ifndef _COMMON_H_
#define _COMMON_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <d3dx9.h>
#include <Windows.h>
#include <crtdbg.h>

//=============================================================================
// �}�N����`
//=============================================================================
#pragma warning (disable : 4996)

#define NEW											new(	_NORMAL_BLOCK,	__FILE__,	__LINE__	)	// new�}�N��
#define NEW_TYPE( p , Class )						{ if(!p){ (p) = NEW Class; } }						// �������m��
#define NEW_TYPE_ARRAY( p, Class, num )				{ if(!p){ (p) = NEW Class[num]; } }					// �������m��(�z��)
#define NEW_PRIOBJTYPE( p, Class, pri, objType )	{ if(!p){ (p) = NEW Class(pri, objType) }			// �������m��(�D��x, ���)
#define SALF_RELEASE( p )							{ if(p){ (p)->Release(); (p) = NULL; } } 			// Relese�}�N��
#define SALF_DELETE( p )							{ if(p){ delete (p); (p) = NULL; } }				// delete�}�N��
#define SALF_DELETE_ARRAY( p )						{ if(p){ delete[] (p); (p) = NULL; } }				// �z��delete�}�N��
#define CLASS_DELETE( c )							{ if(c){ (c)->Uninit(); delete (c); (c) = NULL; } }	// �N���X��delete�}�N��
#define ERROR_CHACK( hr )							{ if(FAILED(hr)){return E_FAIL;} }					// �G���[�`�F�b�N

#endif // _COMMON_H_

// end of file
