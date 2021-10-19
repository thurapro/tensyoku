/**************************************************************************//**
 * @file		NetworkMessage.h
 * @brief
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H

/*
送信メッセージ
サブゲームの検索
id:0xFF
data:null

画面遷移
id:1
data:遷移先
data[0] = 0:タイトル
data[0] = 1:曲選択
data[0] = 2:ゲーム
data[0] = 3:リザルト
data[0] = 4:ランキング
data[0] = 0xFF:次のシーケンス


曲選択
id:2
data:曲番号,難易度
data[0] = 0:bgm1
data[0] = 0:bgm2
data[0] = 0:bgm3
data[1] = 0:easy
data[1] = 1:normal
data[1] = 2:hard

Score
id:3
data:Score
data[0] = x:スコア値
*/

/*
受信メッセージ

サブゲームの検索の応答
id:-0xFF
data:null

*/

#pragma warning(disable:4351)
struct NetworkMessage{
	NetworkMessage() :messageID(-1), data(){
	}
	int messageID;
	unsigned char data[64];
};
#pragma warning(default:4351)

const int SUBGAME_PORT = 60001;
const int MAINGAME_PORT = 60000;

#endif //NETWORKMESSAGE_H