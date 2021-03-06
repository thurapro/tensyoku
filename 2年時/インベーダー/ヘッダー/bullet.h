//-----------------------------------------------------------------------------
//
// e NX		[bullet.h]	¼öY¾
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2dCN[hh~
//-----------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "CScreen.h"
#include "common.h"
#include "object.h"
#include "explosion.h"

//-----------------------------------------------------------------------------
// eÌNX
//-----------------------------------------------------------------------------
class CBullet  : public CObject
{
public:
	CBullet(void);																	// eÌ¶¬
	~CBullet(void);																	// eÌjü
	void Init(float fPosX, float fPosY, float fMoveX, float fMoveY);				// eÌú»
	void Uninit(void);																// eÌjü
	void Update(void);																// eÌXV
	void Draw(void);																// eÌ`æ
	void GetPos(float *pPosX, float *pPosY){*pPosX = m_fPosX; *pPosY = m_fPosY;}	// eÌ»ÝÊuðæ¾
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// ­ÌÊuæ¾
	static CBullet *Create(float fPosX, float fPosY, float fMoveX, float fMoveY);	// eÌ¶¬
private:
	float m_fPosX;																	// eÌ»ÝÊuX
	float m_fPosY;																	// eÌ»ÝÊuY
	float m_fPosXOld;																// eÌ³¢½ÊuX
	float m_fPosYOld;																// eÌ³¢½ÊuY
	float m_fMoveX;																	// eÌ¬xX
	float m_fMoveY;																	// eÌ¬xY
	int m_nType;																	// eªNÌ©
};

#endif // BULLET
