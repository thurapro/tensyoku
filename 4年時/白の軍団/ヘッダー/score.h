/**************************************************************************************

	�t�@�C�����e	:	�`��I�u�W�F�N�g�t�@�C��[scene2DGL.h]
	�N���X��		:	AT-13C-243
	�����			:	�H���@��

**************************************************************************************/
#ifndef _SCORE_H_
#define _SCORE_H_
#include "sceneGL.h"
#include "vector3D.h"
#include "2DpolygonGL.h"

class CScore : public CSceneGL
{
public:
	CScore();
	~CScore();

	static CScore* Create(int width, int height, float posx, float posy,const char* tex);

	void Init(int width, int height, float posx, float posy,const char* tex);							//	������
	virtual void UnInit(void);							//	��n��
	virtual void UpDate(void);							//	�X�V
	virtual void Draw(void);							//	�`��

	int GetScore(void){return m_nScore;}
	void SetScore(int score){m_nScore = score;}
private:
	unsigned int m_nTexture;
	//VECTOR3D m_rot;
	int m_nWidth;
	int m_nHeight;
	VERTEX3D* m_pVertex;
	C2DpolygonGL* m_pScore[8];

	int m_nScore;
protected:
};

#endif
