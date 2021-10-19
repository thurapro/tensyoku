#include "score.h"
#include "texture.h"

CScore::CScore()
{
	m_nScore = 0;
}

CScore::~CScore()
{
}

CScore* CScore::Create(int width, int height, float posx, float posy,const char* tex)
{
	CScore* ps = new CScore;
	ps->Init(width,height,posx,posy,tex);
	return ps;
}

void CScore::Init(int width, int height, float posx, float posy,const char* tex)
{
	for(int nLoop = 0; nLoop < 8; nLoop++)
	{
		m_pScore[nLoop] = C2DpolygonGL::Create(width/8,height,posx + width/8*nLoop,posy);
		m_pScore[nLoop]->SetAnimeSize(10,1);
		m_pScore[nLoop]->SetAnimePos(nLoop,0);
	}
	m_pos = VECTOR3D(posx,posy,0);
	m_nTexture = LoadTexture(tex);

}

void CScore::UnInit(void)
{
	for(int nLoop = 0; nLoop < 8; nLoop++)
	{
		if(m_pScore[nLoop] != NULL)
		{
			delete m_pScore[nLoop];
			m_pScore[nLoop] = NULL;
		}
	}
}

void CScore::UpDate(void)
{
	int nScore = m_nScore;
	for(int nLoop = 0; nLoop < 8; nLoop++)
	{
		if(m_pScore[7 - nLoop] != NULL)
		{
			m_pScore[7 - nLoop]->SetAnimePos(nScore%10,0);
			m_pScore[7 - nLoop]->UpDate();
			nScore /= 10;
		}
	}
}

void CScore::Draw(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,m_nTexture);

	//+++++++++++++++++++++++++
	//2/17
	//Koukyoku_Ou
	//+++++++++++++++++++++++++
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	for(int nLoop = 0;nLoop < 8; nLoop++)
	{
		m_pScore[nLoop]->Draw();
	}
	glDisable(GL_TEXTURE_2D);

	//+++++++++++++++++++++++++
	//2/17
	//Koukyoku_Ou
	//+++++++++++++++++++++++++
	glDisable(GL_BLEND);
}
