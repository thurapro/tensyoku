//-----------------------------------------------------------------------------
//
// ’eˆ— ƒNƒ‰ƒX		[bullet.h]	¼”ö—Y‘¾
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 2dƒCƒ“ƒNƒ‹[ƒh–h~
//-----------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "CScreen.h"
#include "common.h"
#include "object.h"
#include "explosion.h"

//-----------------------------------------------------------------------------
// ’e‚ÌƒNƒ‰ƒX
//-----------------------------------------------------------------------------
class CBullet  : public CObject
{
public:
	CBullet(void);																	// ’e‚Ì¶¬
	~CBullet(void);																	// ’e‚Ì”jŠü
	void Init(float fPosX, float fPosY, float fMoveX, float fMoveY);				// ’e‚Ì‰Šú‰»
	void Uninit(void);																// ’e‚Ì”jŠü
	void Update(void);																// ’e‚ÌXV
	void Draw(void);																// ’e‚Ì•`‰æ
	void GetPos(float *pPosX, float *pPosY){*pPosX = m_fPosX; *pPosY = m_fPosY;}	// ’e‚ÌŒ»İˆÊ’u‚ğæ“¾
	void GetPos(float *pPosX, float *pPosY, float *pPosXOld, float *pPosYOld){*pPosX = m_fPosX; *pPosY = m_fPosY; *pPosXOld = m_fPosXOld; *pPosYOld = m_fPosYOld;}			// ”š”­‚ÌˆÊ’uæ“¾
	static CBullet *Create(float fPosX, float fPosY, float fMoveX, float fMoveY);	// ’e‚Ì¶¬
private:
	float m_fPosX;																	// ’e‚ÌŒ»İˆÊ’uX
	float m_fPosY;																	// ’e‚ÌŒ»İˆÊ’uY
	float m_fPosXOld;																// ’e‚ÌŒ³‚¢‚½ˆÊ’uX
	float m_fPosYOld;																// ’e‚ÌŒ³‚¢‚½ˆÊ’uY
	float m_fMoveX;																	// ’e‚Ì‘¬“xX
	float m_fMoveY;																	// ’e‚Ì‘¬“xY
	int m_nType;																	// ’e‚ª’N‚Ì‚©
};

#endif // BULLET
