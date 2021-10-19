/**************************************************************************************

	ファイル内容	:	描画オブジェクトファイル[scene2DGL.h]
	クラス名		:	AT-13C-243
	製作者			:	工藤　治

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

	void Init(int width, int height, float posx, float posy,const char* tex);							//	初期化
	virtual void UnInit(void);							//	後始末
	virtual void UpDate(void);							//	更新
	virtual void Draw(void);							//	描画

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
