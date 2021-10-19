//*********************************************************************
// 													
// Houseの処理[ house.h ]									 
// Houseの処理を行うクラス
// 																	 
// Date:2013/11/18 NAME:YUTA MATSUO									 
// 																		
//*********************************************************************
//---------------------------
// インクルードガード
//---------------------------
#ifndef _HOUSE_H_
#define _HOUSE_H_

//--------------------------
// ヘッダーファイル
//--------------------------
#include "vector3D.h"
#include "object.h"
#include "drawModel.h"

//-------------------------------
// クラス宣言
//-------------------------------
class CHouse : public CObject
{
public:
	CHouse( void );			// コンストラクタ
	~CHouse( void );		// デストラクタ
	HRESULT Init( void );	// 初期化処理
	void Uninit( void );	// 終了処理
	void Update( void );	// 更新処理
	void OnHit( VECTOR3D colPos, VECTOR3D objPos, VECTOR3D objOffset, COLSTATUS colStatus );	// 衝突処理
	static CHouse* Create( int nPriority, char *pFileName, VECTOR3D vecPos );					// 家作成
	/*void SaveFile( FILE *fp )
	{
		fprintf( fp, "\n// wall001\n" );
		CObject::SaveFile( fp );
	};*/

private:
	CDrawModel		*m_pHouse;		// 描画用の家インスタンス
	CCollision		*m_pCollision;	// 当たり判定のインスタンス
	VECTOR3D		m_offset;		// オフセット
};

#endif
// EOF