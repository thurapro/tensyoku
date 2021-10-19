//*********************************************************************
// 																	 
// プレイヤーの処理[ player.h ]											 
// プレイヤーの処理を行う(シングルトン)
// カメラクラスがプレイヤーにフォーカスする為、
// 基本的にモード遷移以外で解放はしないこと！
// 																	 
// Date:2013/06/20 NAME:YUKI SATO									 
// 																		
//*********************************************************************
//---------------------------
// インクルードガード
//---------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//--------------------------
// ヘッダーファイル
//--------------------------
#include "drawModel.h"

//-------------------------------
// マクロ
//-------------------------------
#define PLAYER_MOVE			( 0.02f )				// プレイヤー移動量
#define PLAYER_ROT			( 0.02f )				// プレイヤー回転量
#define PLAYER_OFFSET_X		( 15.0f )				// プレイヤーオフセット
#define COL_VALUE			( 10.0f )				// 当たり判定補正値
#define STRAW_ROT			( 0.06f )				// ストロー回転量
#define STRAW_ROT_MAX		( D3DX_PI * 0.3f )		// ストロー回転最大値
#define STRAW_ROT_DEFAULT	( VECTOR3D( D3DX_PI * 0.5f, 0, 0 ) )	// ストローデフォルト角度
#define STRAW_ROT_LOOKDOWN	( D3DX_PI * 0.5f - 0.2f )				// 下を向いた時のストロー最大角度
#define MAX_COLOR			( 6 )

//-------------------------------
// クラス宣言
//-------------------------------
class CPlayer : public CObject
{
public:
	HRESULT Init( void );	// 初期化処理
	void Uninit( void );	// 終了処理
	void Update( void );	// 更新処理
	void Reflect( void );	// 反映処理

	// 衝突処理
	void OnHit( int tag, COLDETAIL detail, COLSTATUS colStatus )
	{
		//****************
		// 反射処理
		//****************
		float norValue;
		VECTOR3D vecMove;

		// 当たったオブジェクト毎の処理
		switch( colStatus.objType )
		{
		// 静的メッシュの場合
		case CCollision::OBJ_STATICMESH:

			// 衝突位置から残りの移動後の速度を割り出す
			vecMove = m_move * detail.colTime;
		
			vecMove = m_pos + m_move - detail.colPos;

			// 正規化した法線ベクトルとオブジェクトの進行方向ベクトルから法線ベクトルの長さを得る
			norValue = Vec3DDotProduct( detail.colNor, vecMove );

			if( abs( norValue ) >= 5.0f )
			{
				// 法線ベクトルを反射ベクトルとして移動ベクトルに補正する
				m_move -= ( detail.colNor * norValue ) * 2;
				m_move *= 0.76f;
			}
			else
			{
				// 壁づり計算
				m_move -= ( detail.colNor * norValue );
			}
			break;
		default:
			
			// 座標を衝突位置に戻す
			if( detail.colTime <= 1.0f && detail.colTime >= -10.0f )
				m_pos = m_pos + ( m_move * detail.colTime );

			// 壁吊り処理
			m_move = Vec3DWallHanging( detail.colNor, m_move );
			break;
		}
	};

	static CPlayer *Create( void )
	{
		m_pInstance = new CPlayer();
		m_pInstance->Init();
		m_pInstance->m_scl = VECTOR3D( 2.0f, 2.0f, 2.0f );
	
		return m_pInstance;
	};

	static CPlayer *GetInstance( void )
	{
		return m_pInstance;
	};

private:
	CPlayer( void );				// コンストラクタ(シングルトン)
	~CPlayer( void );				// デストラクタ
	static CPlayer	 *m_pInstance;	// 自身のインスタンスポインタ
	CAnimeModel		 *m_pPlayerBody;// プレイヤのモデル
	class CShadow	 *m_pShadow;	// 影
	CCollision		 *m_pCollision;	// あたり判定
	
	VECTOR3D		 m_direction;			// 向き情報
	float			 m_moveStrow;			// ストロー回転速度
	VECTOR3D		 m_rotStraw;			// ストロー回転角度保存用
	QUATERNION		 m_quatStraw;			// 回転クォータタニオン
	bool			 m_bFlagJunp;			// ジャンプフラグ
	float			 m_fJumpPower;			// ジャンプ力
	float			 m_fGravity;			// 重力
	D3DXCOLOR		 m_color[MAX_COLOR];	// 色
	int				 m_colorPoint;			// 指定している色
};

#endif
// EOF