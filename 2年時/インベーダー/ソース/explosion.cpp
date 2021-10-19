//-----------------------------------------------------------------------------
//
// 爆発処理 クラス		[bullet.cpp]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "explosion.h"
#include "CScreen.h"
#include "common.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define EXPLOSION_TIME	(20)		// 爆発表示時間

//-----------------------------------------------------------------------------
// 爆発のインスタント
//-----------------------------------------------------------------------------
CExplosion::CExplosion(void)
{
	m_fPosX = 0;					// 爆発の現在X座標
	m_fPosY = 0;					// 爆発の現在Y座標
	m_fPosXOld = 0;					// 爆発の元いたX座標
	m_fPosYOld = 0;					// 爆発の元いたY座標
	m_fMoveX = 0;					// 爆発の移動量X
	m_fMoveY = 0;					// 爆発の移動量Y
	CObject::SetObjType(OBJTYPE_EXPLOSION);
}

//-----------------------------------------------------------------------------
// 爆発のデストラクタ
//-----------------------------------------------------------------------------
CExplosion::~CExplosion(void)
{
	// 爆発の破棄
}

//-----------------------------------------------------------------------------
// 爆発の初期化
//-----------------------------------------------------------------------------
void CExplosion::Init(float fPosX, float fPosY)
{
	m_fPosX = fPosX;			// 弾の現在の位置X
	m_fPosY = fPosY;			// 弾の現在の位置Y
	m_fPosXOld = 0;				// 爆発の元いた位置X
	m_fPosYOld = 0;				// 爆発の元いた位置Y
	m_fMoveX = 0;				// 爆発の速度X
	m_fMoveY = 0;				// 爆発の速度Y
	m_nTime = 0;				// 爆発表示時間
	m_nSelect = 0;				// 爆発の文字処理
#ifdef _DEBUG	
	LOCATE(1, 6);
	printf("爆発の初期位置 X:%.2f, Y:%.2f", fPosX, fPosY);
#endif
}

//-----------------------------------------------------------------------------
// 爆発の終了
//-----------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	// 爆発の破棄
}

//-----------------------------------------------------------------------------
// 爆発の更新
//-----------------------------------------------------------------------------
void CExplosion::Update(void)
{
#ifdef _DEBUG
	LOCATE(1,3);	
	printf("m_nTime : %d" , m_nTime);					// タイマーの時間表示	
#endif

	m_fPosXOld = m_fPosX;
	m_fPosYOld = m_fPosY;
	if(m_nTime == EXPLOSION_TIME)
	{
		LOCATE((int)m_fPosXOld , (int)m_fPosYOld);		// 爆発の現在位置XをLOCATEで指定
		printf("　");									// 爆発の元いた位置にスペース出力
#ifdef _DEBUG
		LOCATE(1,7);									
		// 爆発位置を表示
		printf("爆発の位置 X:%.2f Y:%.2f",m_fPosXOld,m_fPosYOld);
#endif
		CObject::Release();								// 爆発を破棄
	}
	else
	{
		m_nSelect = rand() % 3;							// 爆発模様
		m_nTime++;										// カウントアップ
	}
}

//-----------------------------------------------------------------------------
// 爆発の描画
//-----------------------------------------------------------------------------
void CExplosion::Draw(void)
{
	LOCATE((int)m_fPosXOld , (int)m_fPosYOld);			// 爆発の元いた位置をLOCATEで指定
	printf(" ");										// 爆発の元いた位置にスペース出力
	LOCATE((int)m_fPosX , (int)m_fPosY);				// 爆発の現在位置XをLOCATEで指定
	switch(m_nSelect)
	{
	case STAR:
		printf("☆");									// 爆発の現在位置に爆発を出力
		break;
	case SQUARE:
		printf("□");									// 爆発の現在位置に爆発を出力
		break;
	case CIRCLE:
		printf("◎");									// 爆発の現在位置に爆発を出力
		break;
	}
}

//-----------------------------------------------------------------------------
// 爆発の生成
//-----------------------------------------------------------------------------
CExplosion *CExplosion::Create(float fPosX, float fPosY)
{
	// 爆発のポインター
	CExplosion *pExplosion;									

	// 爆発の生成
	pExplosion = new CExplosion;

#ifdef _DEBUG
	LOCATE(1, 5);
	// 弾の生成位置を表示
	printf("爆発の生成位置 X:%.2f, Y:%.2f", fPosX, fPosY);
#endif

	// 爆発の初期化
	pExplosion->Init(fPosX, fPosY);	
	
	return pExplosion;
}