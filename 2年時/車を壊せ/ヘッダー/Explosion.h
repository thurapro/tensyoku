//=============================================================================
//
// FAILE NAME [Explosion.h]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: 爆発エフェクトのマクロ,構造体,プロトタイプ宣言
//
//=============================================================================

//=============================================================================
// 二重インクルード防止
//=============================================================================
#ifndef _EXPLOSION_H_
#define	_EXPLOSION_H_

//=============================================================================
// インクルード
//=============================================================================
#include <d3dx9.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_NUM			( 7 )			// 爆発テクスチャ番号 9～14
#define EXPLOSION_WIDTHINIT		( 30 )			// 爆発の初期幅
#define EXPLOSION_HEIGHTINIT	( 30 )			// 爆発の初期高さ
#define EXPLOSION_TEXVTEXX0		( 0.025f )		// 爆発画像のX座標0
#define EXPLOSION_TEXVTEXY0		( 0.3f )		// 爆発画像のY座標0
#define EXPLOSION_TEXVTEXX1		( 0.1f )		// 爆発画像のX座標1
#define EXPLOSION_TEXVTEXY1		( 0.70f )		// 爆発画像のY座標1
#define EXPLOSION_TEXVTEXXADD	( 0.1f )		// 爆発画像のX座標を移動
#define EXPLOSION_TEXVTEXX0MAX	( 0.9f )		// 爆発画像のX座標0最大位置	
#define EXPLOSION_TEXVTEXX1MAX	( 1.f )			// 爆発画像のX座標1最大位置
#define EXPLOSION_WIDTHSUB		( 3 )			// 幅の引き算
#define EXPLOSION_HEIGHTSUB		( 3 )			// 高さの引き算
#define EXPLOSION_TEXTUREMOVEX	( 0.1f )		// テクスチャの座標X移動
#define EXPLOSION_TEXTUREMOVE	( 0 )			// テクスチャの座標Y移動
#define EXPLOSION_SOUNDNUM		( 3 )			// 爆発音
#define EXPLOSION_STRUCTMAX		( 4 )
#define EXPLOSION_MAX			( 3 )			// 爆発の最大数
#define EXPLOSION_WATE			( 20 )			// 爆発待ち時間
#define OUTPLAYER				( 3 )
#define OUTPLAYER_NUM			( 10 )			// プレイヤーのやれられモーション
#define OUTPLAYER_MOTIONX0		( 0.f )	
#define OUTPLAYER_MOTIONY0		( 0.f )
#define OUTPLAYER_MOTIONX1		( 1.f * 0.25 )
#define OUTPLAYER_MOTIONY1		( 1.f )
#define OUTPLAYER_MOTIONXMAX0	( 0.75f )
#define OUTPLAYER_MOTIONXMAX1	( 1.f )



//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	float	fExplosionPosX	;					// 爆発の位置X座標
	float	fExplosionPosY	;					// 爆発の位置Y座標
	float	fExplosionWidth	;					// 爆発の幅
	float	fExplosionHeight;					// 爆発の高さ
	float	fExplosionTexX0	;					// 爆発の画像X座標0
	float	fExplosionTexY0	;					// 爆発の画像Y座標0
	float	fExplosionTexX1	;					// 爆発の画像X座標1
	float	fExplosionTexY1	;					// 爆発の画像Y座標1
	int		iExplosionWate	;					// 爆発の待ち時間
	BOOL	bExplosionAppear;					// 爆発が表示されているか

}EXPLOSION;


//=============================================================================
// プロトタイプ宣言
//=============================================================================
void ExplosionInit( void )	;					// 爆発の初期化

void ExplosionPosSet( float fPosX	,			// 爆発のポジションセットX座標
					  float fPosY	,			// 爆発のポジションセットY座標
					  float fWidth	,			// 爆発のポジションセット最大X座標
					  float fHeight);			// 爆発のポジションセット最大Y座標

void ExplosionUpdate( void );					// 爆発の更新

void ExplosionDraw( void )	;					// 爆発の描画
void ExplosionUninit( void );					// 爆発解放
EXPLOSION *ExplosionGet( void );				// 爆発ゲッター

#endif // EXPLOSION_H_