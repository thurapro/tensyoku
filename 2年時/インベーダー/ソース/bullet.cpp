//-----------------------------------------------------------------------------
//
// 弾処理 クラス		[bullet.cpp]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "bullet.h"

//-----------------------------------------------------------------------------
// 弾のインスタント
//-----------------------------------------------------------------------------
CBullet::CBullet(void)
{
	m_fPosX = 0;					// 弾の現在X座標
	m_fPosY = 0;					// 弾の現在Y座標
	m_fPosXOld = 0;					// 弾の元いたX座標
	m_fPosYOld = 0;					// 弾の元いたY座標
	m_fMoveX = 0;					// 弾の移動量X
	m_fMoveY = 0;					// 弾の移動量Y
	CObject::SetObjType(OBJTYPE_BULLET);
}

//-----------------------------------------------------------------------------
// 弾のデストラクタ
//-----------------------------------------------------------------------------
CBullet::~CBullet(void)
{
	// 弾の破棄
	LOCATE(m_fPosX, m_fPosY);			// 現在位置に
	printf(" ");						// スペースを入れる
	LOCATE(m_fPosXOld, m_fPosYOld);		// 過去の位置に
	printf(" ");						// スペースを入れる
}

//-----------------------------------------------------------------------------
// 弾の初期化
//-----------------------------------------------------------------------------
void CBullet::Init(float fPosX, float fPosY, float fMoveX, float fMoveY)
{
	m_fPosX = fPosX;			// 弾の現在位置X
	m_fPosY = fPosY;			// 弾の現在位置Y
	m_fPosXOld = 0;				// 弾の元いた位置X
	m_fPosYOld = 0;				// 弾の元いた位置Y
	m_fMoveX = fMoveX;			// 弾の速度X
	m_fMoveY = fMoveY;			// 弾の速度Y
}

//-----------------------------------------------------------------------------
// 弾の終了
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	// 弾の破棄
}

//-----------------------------------------------------------------------------
// 弾の更新
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	m_fPosXOld = m_fPosX;								// 弾の元いた位置Xに現在の位置Xを代入
	m_fPosYOld = m_fPosY;								// 弾の元いた位置Yに現在の位置Yを代入
	m_fPosX += m_fMoveX;								// 弾の現在位置Xを速度X分移動
	m_fPosY += m_fMoveY;								// 弾の現在位置Yを速度Y分移動

	// 弾が上下画面外に出たら
	if(m_fPosY <  SCREEN_HEIGHT_MIN )
	{
		m_fPosY = SCREEN_HEIGHT_MIN;					// 位置を調節
   		CExplosion::Create(m_fPosX, m_fPosY);
		LOCATE((int)m_fPosXOld,(int)m_fPosYOld);		// 弾の元いた位置を指定
		printf(" ");									// 弾の元いた位置をスペース出力
#ifdef _DEBUG
		LOCATE( 1, 8);
		printf("弾の位置 X:%.3f, Y:%.3f", m_fPosX, m_fPosY);
#endif
		CObject::Release();								// 弾を破棄
	}
	else if( m_fPosY > SCREEN_HEIGHT_MAX )
	{
		m_fPosY = SCREEN_HEIGHT_MAX;					// 位置を調節
		LOCATE((int)m_fPosXOld,(int)m_fPosYOld);		// 弾の元いた位置を指定
		printf(" ");									// 弾の元いた位置をスペース出力
		CExplosion::Create(m_fPosX, m_fPosY);			// 爆発を作成
		CObject::Release();								// 弾を破棄
	}
	else
	{
		// 当たり判定
		// オブジェクトワーク先頭アドレスを取得
/*		CObject *pObject = CObject::GetObj();
		
		for(int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)	// オブジェクト分回す
		{
			if(((int *)pObject)[nCntObj] != NULL)
			{
				// オブジェクトが空で無ければ
				// インスタンスへのポインタを取得
				CObject *pObjCur = (CObject *)(((int *)pObject)[nCntObj]);

				// オブジェクトタイプを取得
				CObject::OBJTYPE type = pObjCur->GetObjTyep();
				
				if(type == CObject::OBJTYPE_ENEMY)
				{
					// 敵であれば
					// 敵の位置を取得
					float fPosX, fPosY, fPosXOld, fPosYOld;
					pObjCur->GetPos(&fPosX, &fPosY, &fPosXOld, &fPosYOld);
					
					if( m_fPosX > m_fPosX - 1)
					{
						// 当たり判定
						if( m_fPosX < fPosX + 1 && 
							m_fPosY < fPosY + 1 &&
							fPosX < m_fPosX + 1 &&
							fPosY < m_fPosY + 1)
						{
#ifdef _DEBUG
							LOCATE(1, 4);
							printf("爆発の生成もと X:%.2f Y:%.2f",m_fPosX, m_fPosY);
#endif
							CExplosion::Create(m_fPosX, m_fPosY);		// 爆発を作成
							LOCATE((int)m_fPosXOld,(int)m_fPosYOld);	// 弾の元いた位置を指定
							printf(" ");
							LOCATE((int)fPosXOld, (int)fPosYOld);		// 消去したい座標指定
							printf(" ");								// 敵を消去
							pObjCur->Release();							// 敵を破棄
							CObject::Release();							// 弾を破棄
						}
					}
				}
			}
		}*/
	}

}

//-----------------------------------------------------------------------------
// 弾の描画
//-----------------------------------------------------------------------------
void CBullet::Draw(void)
{
	LOCATE((int)m_fPosXOld , (int)m_fPosYOld);	// 弾の元いた位置をLOCATEで指定
	printf(" ");								// 弾の元いた位置にスペース出力
	LOCATE((int)m_fPosX , (int)m_fPosY);		// 弾の現在位置XをLOCATEで指定
	printf("o");								// 弾の現在位置に弾を出力
}

//-----------------------------------------------------------------------------
// 弾の生成
//-----------------------------------------------------------------------------
CBullet *CBullet::Create(float fPosX, float fPosY, float fMoveX, float fMoveY)
{
	// 弾のポインター
	CBullet *pBullet;									

	// 弾の生成
	pBullet = new CBullet;	

	// 弾の初期化
	pBullet->Init(fPosX, fPosY, fMoveX, fMoveY);	
	
	return pBullet;
}