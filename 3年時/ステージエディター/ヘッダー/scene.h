//============================================================================= 
// シーン処理 [ scene.h ]
// 
// 作成者	: 松尾 雄太
//
// 機能		: シーンリスト管理
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIST	(8)					// リストの数

//=============================================================================
// 構造体宣言
//=============================================================================

// 2Dポリゴンに必要な要素
typedef struct
{
	D3DXVECTOR3 Vertex;			// 頂点座標
	float		rhw;			// 同次座標の逆数
	D3DCOLOR	Diffuse;		// 頂点の色
	D3DXVECTOR2	Texture;		// テクスチャ座標
}VERTEX_2D;

// 3Dポリゴンに必要な要素
typedef struct
{
	D3DXVECTOR3 vtx;						// 頂点
	D3DXVECTOR3 nor;						// ベクトルの向き(裏か表)向き
	D3DCOLOR	diffuse;					// 頂点色を設定
	D3DXVECTOR2	tex;						// テクスチャ頂点
}VERTEX_3D;


//=============================================================================
// クラス宣言
//=============================================================================
class CScene
{
public:		// 操作
	typedef enum
	{
		OBJTYPE_NONE = 0,				// 特に関係なし
		OBJTYPE_2D,						// 2D
		OBJTYPE_3D,						// 3D
		OBJTYPE_MODEL,					// モデル
		OBJTYPE_BILLBOARD,				// ビルボード
		OBJTYPE_MESH,					// メッシュ
		OBJTYPE_PLAYER,					// プレイヤー
		OBJTYPE_PLAYER2,				// プレイヤー2
		OBJTYPE_ENEMY,					// 敵
		OBJTYPE_ITEM,					// アイテム
		OBJTYPE_TREE,					// 木
		OBJTYPE_GRASS,					// 草
		OBJTYPE_OCEAN,					// 海
		OBJTYPE_SHADOW,					// 影
		OBJTYPE_EXPLOSION,				// 爆発
		OBJTYPE_EFFECT,					// エフェクト
		OBJTYPE_GIMMICK,				// ギミック
		OBJTYPE_FIELD,					// 地面
		OBJTYPE_WALL,					// 壁
		OBJTYPE_MOUNTAIN,				// 山
		OBJTYPE_SKY						// 空
	}OBJTYPE;

	CScene(int nPriority = 0, OBJTYPE objType = OBJTYPE_NONE);	// インスタンス生成
	virtual ~CScene(){};							// インスタンス破棄
	virtual HRESULT	Init(void)=0;					// シーン初期化処理
	virtual void	Uninit(void)=0;					// シーン終了処理
	virtual void	Update(void)=0;					// シーン更新処理
	virtual void	Draw(void)=0;					// シーン描画処理
	static	void	UpdateAll(void);				// リスト内にあるシーン更新処理
	static	void	DrawAll(void);					// リスト内にあるシーン描画処理
	static  void	ReleaseAll(void);				// リスト内にあるシーン破棄処理
	void	LinkList(int nPriority, OBJTYPE objType);	// リストに入れる
	void	UnlinckList(void);						// リストから外す
	void	Release(void);							// フラグオン

	static CScene *GetScene(int i){return m_pTop[i];}	// シーン取得
	CScene *GetNext(void){ return m_pNext;}				// 次のシーン取得

	OBJTYPE GetObjType(void){return m_objType;}			// シーンの種類取得

private:
	static CScene *m_pTop[MAX_LIST];		// 前の場所
	static CScene *m_pCur[MAX_LIST];		// 現在の場所
	CScene *m_pPrev;						// 前のオブジェ
	CScene *m_pNext;						// 次のオブジェ
	bool	m_bDethFlag;					// 生きているのか
	int		m_nPriority;					// 優先順位保存
	CScene *m_pSceneLink;					// 誰に依存しているか
	OBJTYPE m_objType;						// オブジェクトの種類
};

#endif	// _SCENE_H_

// end of file