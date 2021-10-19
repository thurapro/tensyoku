//-----------------------------------------------------------------------------
//
// ゲーム処理		[game.h]	松尾雄太
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "game.h"			// ゲームヘッダーファイル
#include "object.h"			// OBJヘッダーファイル
#include "player.h"			// プレイヤーヘッダーファイル
#include "enemy.h"			// 敵ヘッダーファイル
#include "explosion.h"		// 爆発ヘッダーファイル

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_X_INIT	(20.0f)			// プレイヤーの初期位置X
#define PLAYER_Y_INIT	(20.0f)			// プレイヤーの初期位置Y
#define MAX_ENEMY		(20)			// 敵の最大数
#define ENEMY_X_INIT	(10.0f + (i*2)) // 敵の位置X
#define ENEMY_Y_INIT	(4.0f)			// 敵の位置Y

//-----------------------------------------------------------------------------
// ゲーム	コンストラクタ
// 戻り値	なし
// 引数		なし
// 機能		生成
//-----------------------------------------------------------------------------
CGame::CGame(void)
{
	// 生成
}

//-----------------------------------------------------------------------------
// ゲーム	デストラクタ
// 戻り値	なし
// 引数		なし
// 機能		破棄
//-----------------------------------------------------------------------------
CGame::~CGame()
{
	// 破棄
}

//-----------------------------------------------------------------------------
// ゲーム	初期化
// 戻り値	なし
// 引数		なし
// 機能		プレイヤーの生成, 初期化
//			敵の生成, 初期化
//-----------------------------------------------------------------------------
void CGame::Init(void)
{
	// プレイヤー生成
	if( CPlayer::Create(PLAYER_X_INIT, PLAYER_Y_INIT) == NULL)
	{
		return;
	}
	for(int i = 0; i < MAX_ENEMY; i++)
	{
		// 敵の生成
		if(CEnemy::Create(ENEMY_X_INIT, ENEMY_Y_INIT) == NULL)
		{
				return;
		}
	}
}

//-----------------------------------------------------------------------------
// ゲーム	終了
// 戻り値	なし
// 引数		なし
// 機能		ゲームに使われたOBJなど破棄
//-----------------------------------------------------------------------------
void CGame::Uninit(void)
{
	// 全破棄
  	CObject::ReleaseAll();

	// 画面をまっさらに
	CLS();
}

//-----------------------------------------------------------------------------
// ゲーム	更新
// 戻り値	なし
// 引数		なし
//機能		ゲームに使われているOBJなどを更新
//-----------------------------------------------------------------------------
void CGame::Update(void)
{
	// 全OBJ更新
	CObject::UpdateAll();
}

//-----------------------------------------------------------------------------
// ゲーム	描画
// 戻り値	なし
// 引数		なし
// 機能		ゲームに使われているOBJなどを描画
//-----------------------------------------------------------------------------
void CGame::Draw(void)
{
	// 全OBJ描画
	CObject::DrawAll();
}