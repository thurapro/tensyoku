//=============================================================================
//
// FAILE NAME [Explosion.cpp]
//
// 名前		: 松尾 雄太
//
// クラス	: AT12C283
//
// 機能		: 爆発エフェクト
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "../hedder/Explosion.h"
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/common.h"
#include "../hedder/Sound.h"
#include "../hedder/Player.h"
#include <dsound.h>

//=============================================================================
// グローバル変数
//=============================================================================
static EXPLOSION		g_Explosion[EXPLOSION_STRUCTMAX] = { NULL };// 爆発変数
static LPDIRECTSOUNDBUFFER	g_SoundEx = NULL;							// 爆発音
static BOOL g_bPlayerTex = FALSE;
static BOOL g_bExplosionTex[EXPLOSION_MAX] = {FALSE};
static BOOL g_bExplosionSou = FALSE;

//=============================================================================
//
// 関数名	: ExplosionInit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 爆発の初期化
//
//=============================================================================
void ExplosionInit( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{

		// 爆発テクスチャーの読み込み
		TextureLoad("photo/Explosion.png" , EXPLOSION_NUM + i );

		// 爆発の場所X座標
		g_Explosion[i].fExplosionPosX = 0;

		// 爆発の場所Y座標
		g_Explosion[i].fExplosionPosY = 0;

		// 爆発の幅
		g_Explosion[i].fExplosionWidth = EXPLOSION_WIDTHINIT;

		// 爆発の高さ
		g_Explosion[i].fExplosionHeight = EXPLOSION_HEIGHTINIT;
		
		// 爆発のテクスチャX座標0
		g_Explosion[i].fExplosionTexX0 = EXPLOSION_TEXVTEXX0;

		// 爆発のテクスチャY座標0
		g_Explosion[i].fExplosionTexY0 = EXPLOSION_TEXVTEXY0;

		// 爆発のテクスチャX座標1
		g_Explosion[i].fExplosionTexX1 = EXPLOSION_TEXVTEXX1;

		// 爆発のテクスチャY座標1
		g_Explosion[i].fExplosionTexY1 = EXPLOSION_TEXVTEXY1;

		// 爆発の待ち時間
		g_Explosion[i].iExplosionWate	= 0;

		// 爆発が使われているか
		g_Explosion[i].bExplosionAppear = FALSE;
	}

	TextureLoad( "photo/out.png" , OUTPLAYER_NUM ); 
	g_Explosion[OUTPLAYER].fExplosionTexX0 = OUTPLAYER_MOTIONX0;
	g_Explosion[OUTPLAYER].fExplosionTexY0 = OUTPLAYER_MOTIONY0;
	g_Explosion[OUTPLAYER].fExplosionTexX1 = OUTPLAYER_MOTIONX1;
	g_Explosion[OUTPLAYER].fExplosionTexY1 = OUTPLAYER_MOTIONY1;
	g_Explosion[OUTPLAYER].iExplosionWate = 0;
	g_Explosion[OUTPLAYER].bExplosionAppear = FALSE;

	// サウンドファイルロード
	if( !SoundFileLoad( "sound/Explosion.wav" , EXPLOSION_SOUNDNUM ) )
	{
		return;
	}

	// サウンドバッファ作成
	if( !CreateSoundBuffer( &g_SoundEx , EXPLOSION_SOUNDNUM ) )
	{
		return;
	}
}

void ExplosionPosSet( float fPosX , float fPosY , float fWidth , float fHeight )
{
	PLAYER *pPlayer;
	pPlayer = PlayerGet();

	if( pPlayer->bPlayerAlive == FALSE )
	{
		// 爆発のX座標を設定
		g_Explosion[OUTPLAYER].fExplosionPosX = fPosX;

		// 爆発のY座標を設定
		g_Explosion[OUTPLAYER].fExplosionPosY = fPosY;

		// 爆発の最大X座標
		g_Explosion[OUTPLAYER].fExplosionWidth = fWidth;

		// 爆発の最大Y座標
		g_Explosion[OUTPLAYER].fExplosionHeight = fHeight;

		g_Explosion[OUTPLAYER].bExplosionAppear = TRUE;
	}

	else
	{
		for( int i = 0; i < EXPLOSION_MAX; i++ )
		{
			if( g_Explosion[i].bExplosionAppear == FALSE )
			{
				// 爆発のX座標を設定
				g_Explosion[i].fExplosionPosX = fPosX;

				// 爆発のY座標を設定
				g_Explosion[i].fExplosionPosY = fPosY;

				// 爆発の最大X座標
				g_Explosion[i].fExplosionWidth = fWidth;

				// 爆発の最大Y座標
				g_Explosion[i].fExplosionHeight = fHeight;

				// 爆発が使われた
				g_Explosion[i].bExplosionAppear = TRUE;
				break;
			}
		}
	}
}


//=============================================================================
//
// 関数名	: ExplosionUpdate関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 爆発の更新
//
//=============================================================================
void ExplosionUpdate( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_Explosion[i].bExplosionAppear == TRUE )
		{
			if( g_Explosion[i].iExplosionWate ==  EXPLOSION_WATE )
			{
				// 爆発の画像X座標0変更
				g_Explosion[i].fExplosionTexX0 += EXPLOSION_TEXVTEXXADD;

				if( g_Explosion[i].fExplosionTexX0 > EXPLOSION_TEXVTEXX0MAX )
				{
					// 爆発の画像X座標0を初期位置に
					g_Explosion[i].fExplosionTexX0 = EXPLOSION_TEXVTEXX0;
				}

				// 爆発の画像X座標1変更
				g_Explosion[i].fExplosionTexX1 += EXPLOSION_TEXVTEXXADD;

				if( g_Explosion[i].fExplosionTexX1 > EXPLOSION_TEXVTEXX1MAX )
				{
					// 爆発の画像X座標1を初期位置に
					g_Explosion[i].fExplosionTexX1 = EXPLOSION_TEXVTEXX1;

					g_Explosion[i].bExplosionAppear = FALSE;
				}

				// 爆発の待ちタイマーリセット
				g_Explosion[i].iExplosionWate = 0;
			}
			// 爆発の待ちタイマーカウント
			g_Explosion[i].iExplosionWate++;
		}
		g_Explosion[i].fExplosionPosX -= 0.40f;
	}

	if( g_Explosion[OUTPLAYER].bExplosionAppear == TRUE )
	{
		if( g_Explosion[OUTPLAYER].iExplosionWate ==  EXPLOSION_WATE )
		{
			// 爆発の画像X座標0変更
			g_Explosion[OUTPLAYER].fExplosionTexX0 += OUTPLAYER_MOTIONX1;
			
			g_Explosion[OUTPLAYER].fExplosionTexX1 += OUTPLAYER_MOTIONX1;
			if( g_Explosion[OUTPLAYER].fExplosionTexX1 > OUTPLAYER_MOTIONXMAX1 )
			{
				g_Explosion[OUTPLAYER].fExplosionTexX0 = OUTPLAYER_MOTIONX0;
				g_Explosion[OUTPLAYER].fExplosionTexX1 = OUTPLAYER_MOTIONX1;
				g_Explosion[OUTPLAYER].bExplosionAppear = FALSE;
			}
			// 爆発の待ちタイマーリセット
			g_Explosion[OUTPLAYER].iExplosionWate = 0;
		}
		g_Explosion[OUTPLAYER].iExplosionWate++;
		g_Explosion[OUTPLAYER].fExplosionPosX += 0.40f;
	}
	
}

//=============================================================================
//
// 関数名	: ExplosionDraw関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 爆発の描画 , 音声
//
//=============================================================================
void ExplosionDraw( void )
{
	for( int i = 0; i < EXPLOSION_MAX; i++ )
	{
		if( g_Explosion[i].bExplosionAppear == TRUE )
		{
			// 爆発の描画
			PrimitiveCreate(	EXPLOSIONID						,	//どのプリミティブを作成するか
								ROTATION						,	// 回転する頂点か , 回転しない頂点か
								EXPLOSION_NUM					,	// テクスチャ番号
								0								,	// 角度 ※回転しない場合は0
								g_Explosion[i].fExplosionPosX	,	// 爆発のX座標設定
								g_Explosion[i].fExplosionPosY	,	// 爆発のY座標設定
								g_Explosion[i].fExplosionWidth	,	// 爆発の幅設定
								g_Explosion[i].fExplosionHeight	,	// 爆発の高さ設定
								g_Explosion[i].fExplosionTexX0	,	// 爆発の画像X座標0設定
								g_Explosion[i].fExplosionTexY0	,	// 爆発の画像Y座標0設定
								g_Explosion[i].fExplosionTexX1	,	// 爆発の画像X座標1設定
								g_Explosion[i].fExplosionTexY1	);	// 爆発の画像Y座標1設定

			// 爆発音の再生
			g_SoundEx->Play( 0 , 0 , 0 );
		}

	}

	if( g_Explosion[OUTPLAYER].bExplosionAppear == TRUE )
	{
		// 爆発の描画
		PrimitiveCreate(	EXPLOSIONID						,	//どのプリミティブを作成するか
							ROTATION						,	// 回転する頂点か , 回転しない頂点か
							OUTPLAYER_NUM					,	// テクスチャ番号
							0								,	// 角度 ※回転しない場合は0
							g_Explosion[OUTPLAYER].fExplosionPosX	,	// 爆発のX座標設定
							g_Explosion[OUTPLAYER].fExplosionPosY	,	// 爆発のY座標設定
							g_Explosion[OUTPLAYER].fExplosionWidth	,	// 爆発の幅設定
							g_Explosion[OUTPLAYER].fExplosionHeight	,	// 爆発の高さ設定
							g_Explosion[OUTPLAYER].fExplosionTexX0	,	// 爆発の画像X座標0設定
							g_Explosion[OUTPLAYER].fExplosionTexY0	,	// 爆発の画像Y座標0設定
							g_Explosion[OUTPLAYER].fExplosionTexX1	,	// 爆発の画像X座標1設定
							g_Explosion[OUTPLAYER].fExplosionTexY1	);	// 爆発の画像Y座標1設定
	
	}
}


//=============================================================================
//
// 関数名	: ExplosionUninit関数
//
// 戻り値	: なし
//
// 引数		: なし
//
// 機能		: 爆発の解放
//
//=============================================================================
void ExplosionUninit( void )
{
	g_bPlayerTex = FALSE;

	g_bExplosionSou = FALSE;

	// テクスチャの解放
	TextureUninit( EXPLOSION_NUM );
	TextureUninit( OUTPLAYER_NUM );

	// サウンドバッファの解放
	if( g_SoundEx != NULL )
	{
		g_SoundEx->Release();
		g_SoundEx = NULL;
	}
}

//=============================================================================
//
// 関数名	: ExplosionGet関数
//
// 戻り値	: EXPLOSION
//
// 引数		: なし
//
// 機能		: 爆発のゲッター
//
//=============================================================================
EXPLOSION *ExplosionGet( void )
{
	return &g_Explosion[0];
}