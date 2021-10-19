//*********************************************************************
// 																	 **
// Wall001の処理[ Wall001.cpp ]										 **
// 																	 **
//*********************************************************************
//-------------------------------
// ヘッダーファイル
//-------------------------------
#include "main.h"

/*-------------------------------------------------------------------
関数名:	CHouse
関数の説明:	Houseのコンストラクタ

戻り値:	void　
  引数: void
-------------------------------------------------------------------*/
CHouse::CHouse( void )
{
	m_pos = VECTOR3D( 0, 0, 0 );
	m_offset = VECTOR3D( 0, 0, 0 );
	m_move = VECTOR3D( 0, 0, 0 );
}

/*-------------------------------------------------------------------
関数名:	~CHouse
関数の説明:	CHouseのデストラクタ

戻り値:	void　
  引数: void
-------------------------------------------------------------------*/
CHouse::~CHouse( void )
{
}

/*-------------------------------------------------------------------
関数名:	Init
関数の説明:	CHouseの初期化

戻り値:	HRESULT　
  引数: LPDIRECT3DDEVICE9
-------------------------------------------------------------------*/
HRESULT CHouse::Init( void )
{
	// 当たり判定系の初期化
	m_pCollision = CCollision::SetCollision( this, 
											 CCollision::COL_BOX_AABB, 
											 CCollision::OBJ_PLAYER |
											 CCollision::OBJ_PLBULLET |
											 CCollision::OBJ_GIMMICK |
											 CCollision::OBJ_SHADOW |
											 CCollision::OBJ_ENEMY,
											 VECTOR3D( 14, 100, 14 ) );
	m_pCollision->SetPosPtr( &m_pos );

	// 衝突時ステータスの初期化
	m_colStatus.objType = CCollision::OBJ_GIMMICK;
	m_colStatus.damage = 0;
	m_colStatus.e = 1.05f;
	m_colStatus.mass = 1.0f;
	m_colStatus.velocity = m_move;
	m_colStatus.action = CCollision::ACTION_NONE;

	return S_OK;
}

/*-------------------------------------------------------------------
関数名:	Uninit
関数の説明:	CHouseの終了処理

戻り値:	void　
  引数: void
-------------------------------------------------------------------*/
void CHouse::Uninit( void )
{
	SAFE_RELEASE( m_pHouse )
	SAFE_RELEASE( m_pCollision )
}

/*-------------------------------------------------------------------
関数名:	Update
関数の説明:	Wall001の更新処理

戻り値:	void　
  引数: void
-------------------------------------------------------------------*/
void CHouse::Update( void )
{
	m_pos += m_move;

	m_move = VECTOR3D( 0, 0, 0 );
	//m_move.x *= 0.71f;
	//m_move.z *= 0.71f;

	m_pHouse->SetPosWorld( m_pos );
}

/*-------------------------------------------------------------------
関数名:	OnHit
関数の説明:	衝突時処理

戻り値:	void
  引数: VECTOR3D	colPos		: 衝突位置
		COLSTATUS	m_colStatus	: 衝突相手の衝突パラメータ 
-------------------------------------------------------------------*/
void CHouse::OnHit( VECTOR3D colPos, VECTOR3D objPos, VECTOR3D objOffset, COLSTATUS colStatus )
{
	int a;
	a= 0;
};
/*-------------------------------------------------------------------
関数名:	Create
関数の説明:	インスタンスの生成

戻り値:	CHouse*
  引数: RES_TEX		resTex		: テクスチャ番号
		VECTOR3D	vecPos		: 生成座標
		VECTOR3D	move		: 移動量
-------------------------------------------------------------------*/
CHouse* CHouse::Create( int nPriority, char *pFileName, VECTOR3D vecPos )
{
	CHouse *pHouse = new CHouse();
	pHouse->m_pos = vecPos;
	pHouse->m_pHouse = CDrawModel::Create( CDraw::PRI_MODELFIRST, pFileName, vecPos );

	pHouse->Init();

	return pHouse;
};
// EOF