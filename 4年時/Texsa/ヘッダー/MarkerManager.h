/*-----------------------------------------------------------------------------
 another : Yuta Matsuo

 譜面表示クラス
-----------------------------------------------------------------------------*/
#ifndef _MARKERMANAGER_H_
#define _MARKERMANAGER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "Node.h"

//=============================================================================
// マクロ定義
//=============================================================================
#pragma warning(disable:4996)

struct MusicScore;
class MarkerButton;
class Score;

//=============================================================================
// クラス宣言
//=============================================================================
class MarkerManager : public MeekH::Node{
public:
	MarkerManager();								// インスタンス生成
	~MarkerManager();								// インスタンス破棄
	void Init(char *FilePath);						// ボタンテクスチャ初期化
	void Update();									// ボタンス更新
	void SetVisibleToken(int count);
	void SetStartToken(int count);
	float GetTokenSpeed();
	void SetMarkerSuccess(bool Success);			// ボタン判定が成功したのか
	void SetComboNum(int i);
	void AddComboNum( int i );
	void AddGoodNum( int i );
	void AddBadNum( int i );

	int GetComboNum();

private:
	void Load(char *FilePath);			// 楽譜読み込み
	int m_CountToken;					// 音符のカウンター
	int m_VisibleToken;					// 出現していないと行けない音符数
	int m_StartToken;					// forの最初の値
	int m_MaxToken;						// 音符の最大数
	MusicScore *m_MusicScore;			// 
	MarkerButton *m_pMarkerButton;		// マーカボタン
	int m_ButtonID;
	int m_ButtonEndID;
	Score *m_pScore;					// スコアー
	float m_fTokenSpeed;				// 一拍のスピード
	int m_nMaxSpeed;					// マーカーBGの動き速度
	int m_nComboNum;					// コンボ数
	bool m_bMarkerSuccess;				// ボタン判定が成功したか
};

#endif // _MARKERMANAGER_H_