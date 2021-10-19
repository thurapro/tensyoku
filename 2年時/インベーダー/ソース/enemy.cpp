//-----------------------------------------------------------------------------
//
// 敵処理 クラス		[enemy.cpp]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define ENEMY_MOVE_LEFT_X	(-0.3f)
#define ENEMY_MOVE_RIGHT_X	(0.3f)
#define ENEMY_MOVE_Y		(1.0f)
#define ENEMY_SHOT_TIME		(20)
#define ENEMY_BULLET_SPEED	(1.0f)

//-----------------------------------------------------------------------------
// 敵の静的メンバー変数
//-----------------------------------------------------------------------------
int CEnemy::m_nNumCnt = 0;		// 敵のカウント

//-----------------------------------------------------------------------------
// 敵のコンストラクタ
//-----------------------------------------------------------------------------
CEnemy::CEnemy(void)
{
	// 敵の生成
	CObject::SetObjType(OBJTYPE_ENEMY);
	
	// 敵の追加
	m_nNumCnt ++;

}

//-----------------------------------------------------------------------------
// 敵のデストラクタ
//-----------------------------------------------------------------------------
CEnemy::~CEnemy(void)
{
	// 敵を減らす
	m_nNumCnt--;		// 敵の数を減らす
#ifdef _DEBUG
	LOCATE(1, 20);
	printf("敵の数%d数", m_nNumCnt);
#endif
}

//-----------------------------------------------------------------------------
// 敵の初期化
//-----------------------------------------------------------------------------
void CEnemy::Init(float fPosX, float fPosY)
{
	m_fPosX = fPosX;							// 敵の初期位置X座標
 	m_fPosY = fPosY;							// 敵の初期位置Y座標
	m_fMoveX = ENEMY_MOVE_RIGHT_X;				// 敵の移動量X座標
	m_fMoveY = ENEMY_MOVE_Y;					// 敵の移動量Y座標
	m_bAlive = true;							// 敵を表示
	m_nShotTime = 0;							// 弾を発射する時間
}

//-----------------------------------------------------------------------------
// 敵の終了
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// 終了
}

//-----------------------------------------------------------------------------
// 敵の更新
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	// 今の座標を保存
	m_fPosXOld = m_fPosX;					// 現在の位置を保存X座標
	m_fPosYOld = m_fPosY;					// 現在の位置を保存Y座標
	m_fPosX += m_fMoveX;					// 敵を移動X座標

	// 敵がもし右端を超えてしまったら
	if(m_fPosX > SCREEN_WIDTH_MAX)
	{
		m_fPosX = SCREEN_WIDTH_MAX;			// 位置を調節
		m_fPosY += m_fMoveY;				// 敵のY座標を下にずらす
		m_fMoveX = ENEMY_MOVE_LEFT_X;		// 敵の移動する向きを左へ移動
	}
	else if(m_fPosX < SCREEN_WIDTH_MIN )	// もし左端をこえたら
	{
		m_fPosX = SCREEN_WIDTH_MIN;			// 位置を調節
		m_fPosY += m_fMoveY;				// 敵のY座標を下にずらす
		m_fMoveX = ENEMY_MOVE_RIGHT_X;		// 敵の移動する向きを右へ移動
	}

	// 敵がもし下画面を越えてしまったら
	if(m_fPosY > SCREEN_HEIGHT_MAX)
	{
		m_fPosY = SCREEN_HEIGHT_MAX;		// 位置を調節
		LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// 位置を指定
		printf(" ");						// 敵を消す
		CObject::Release();					// 敵を破棄
	}

	// 弾と敵の当たり判定
	CObject *pObject = CObject::GetObj();	// オブジェクト取得

	// オブジェクト
	for(int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		// OBJ数分回す
		if(((int *)pObject)[nCntObj] != NULL)
		{
			// OBJの中が空では無ければ
			// インスタンスへのポインタ取得
			CObject *pObjCur =  (CObject *)(((int *)pObject)[nCntObj]);
			
			// タイプ取得
			CObject::OBJTYPE type = pObjCur->GetObjTyep();

			if(type ==	CObject::OBJTYPE_BULLET)
			{
#ifdef _DEBUG
				LOCATE(1,11);
				printf("敵のcppで取得したタイプ %d",  type);
#endif
				// 弾のオブジェクトだったら
				float fPosX, fPosY, fPosXOld, fPosYOld;			// 位置取得用変数
				pObjCur->GetPos(&fPosX, &fPosY, &fPosXOld, &fPosYOld);	// 位置を取得
				
				// 当たり判定
				if( m_fPosX < fPosX + 1 &&
					m_fPosY < fPosY + 1 &&
					fPosX < m_fPosX + 1 &&
					fPosY < m_fPosY + 1)
				{
					// もし当たっていたら
#ifdef _DEBUG
					LOCATE(1, 12);
					printf("爆発の生成もと X:%.2f Y:%.2f",m_fPosX, m_fPosY);
#endif
					CExplosion::Create(m_fPosX, m_fPosY);
#ifdef _DEBUG
					LOCATE(1,13);
					printf("弾の元位置 X:%.2f, Y:%.2f", fPosXOld, fPosYOld);
#endif
					LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// 敵の前の座標位置に
					printf(" ");								// スペース出力
#ifdef _DEBUG
					LOCATE(1,14);
					printf("弾の現位置 X:%.2f, Y:%.2f", fPosXOld, fPosYOld);
#endif
					LOCATE(fPosX, fPosY);					// 弾の前の座標位置に
					printf(" ");							// スペース出力
					pObjCur->Release();						// OBJ破棄
					m_bAlive = false;						// お亡くなりになった
					CObject::Release();						// 自分を破棄
					//m_nNumCnt--;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// 敵の描画
//-----------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	LOCATE((int)m_fPosXOld, (int)m_fPosYOld);	// 位置を指定
	printf("  ");								// 前の位置を消す
	LOCATE((int)m_fPosX, (int)m_fPosY);			// 位置を指定
	COLOR(LIME, BLACK);
	printf("V");								// 敵を出力
	COLOR(WHITE, BLACK);
}


//-----------------------------------------------------------------------------
// 敵を作成
//-----------------------------------------------------------------------------
CEnemy *CEnemy::Create(float fPosX, float fPosY)
{
	// 敵のポインター作成
	CEnemy *pEnemy;							

	// 敵を生成
	pEnemy = new CEnemy;
		
	// 敵を初期化
	pEnemy->Init(fPosX, fPosY);

	return pEnemy;
}




