//=============================================================================
// ステージ処理 [ stage.h ]
//
// 製作者	: 松尾 雄太
//
// 機能		: ステージ設定
//=============================================================================

//=============================================================================
// 2重インクルード防止
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "sky.h"			// 空
#include "mountain.h"		// 山
#include "field.h"			// 地面
#include "wall.h"			// 壁
#include "tree.h"			// 木
#include "grass.h"			// 草
#include "ocean.h"			// 海
#include "item.h"			// アイテム

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_OBJECT ( 300 )			// 各ステージオブジェクトの最大個数

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	int			nWallMax;			// 壁の数
	int			nFieldMax;			// 地面の数			
	int			nTreeMax;			// 木の数
	int			nGrassMax;			// 草の数
	int			nOceanMax;			// 海の数
	int			nItemMax;			// アイテム数
}OBJ_NUM;

//=============================================================================
// クラス宣言
//=============================================================================
class CStage
{
public:		// 操作
	typedef enum
	{
		FIELD_OBJ = 0,		// 地面を設定中
		WALL_OBJ,			// 壁を設定中
		TREE_OBJ,			// 木を設定中
		GRASS_OBJ,			// 草を設定中
		OCEAN_OBJ,			// 海を生成中
		MAX_OBJ				// 最大
	}SET_OBJ;				// 何を設定しているか

	typedef enum
	{
		EDITMODE_CREATE = 0,	// オブジェクト作成
		EDITMODE_DELETE,		// オブジェクト破棄
		EDITMODE_MOVE,			// オブジェクト移動
		EDITMODE_CHENGE,		// オブジェクトの画像などを変える
		EDITMODE_MAX			// オブジェクト操作
	}EDIT_MODE;


	typedef struct
	{
		float	fWidth;		// ポリゴンの幅			
		float	fHeight;	// ポリゴンの高さ
		float	fLength;	// ポリゴンの奥行き
		int		nNumX;		// ポリゴン数(横)
		int		nNumY;		// ポリゴン数(縦)
		int		nNumZ;		// ポリゴン数(奥)
	}POLYGON;


	CStage(void);			// インスタンス生成
	~CStage(void);			// インスタンス破棄
	HRESULT Init(void);		// ステージ初期化
	void	Uninit(void);	// ステージ破棄
	void	Update(void);	// ステージ更新
	void	Draw(void);		// ステージ描画
		
	CSky			*GetSky(void){return m_pSky;}				// 空取得
	CMountain		*GetMountain(void){return m_pMountain;}		// 山取得
	CField			**GetField(void){return m_pField;}			// 地面取得
	CWall			**GetWall(void){return m_pWall;}			// 壁取得
	void			GetFieldNum(int &nFieldNum);				// 地面の数取得
	void			GetWallNum(int &nWallNum);					// 壁の数取得

	HRESULT	Save(void);		// ステージ書き込み
	bool	Load(void);		// ステージ読み込み

private:	// 要素
	void EditCreate(CInputKeyboard *pKeyboard);	// オブジェクトの作成
	void EditDelete(CInputKeyboard *pKeyboard);	// オブジェクトの破棄
	void EditMove(CInputKeyboard *pKeyboard);	// オブジェクトの移動
	void EditChange(CInputKeyboard *pKeyboard);	// オブジェクトの画像などを変える

	bool		m_bLoad;					// 読み込みフラグ
	CSky		*m_pSky;					// 空ポインタ
	CMountain	*m_pMountain;				// 山ポインタ
	CField		*m_pField[MAX_OBJECT];		// 地面ポインタ
	CWall		*m_pWall[MAX_OBJECT];		// 壁のポインタ
	CTree		*m_pTree[MAX_OBJECT];		// 木のポインタ
	CGrass		*m_pGrass[MAX_OBJECT];		// 草のポインタ
	COcean		*m_pOcean[MAX_OBJECT];		// 海のポインタ
	OBJ_NUM		m_ObjNum;					// オブジェクト数
	SKY			m_DataSky;					// 空データ
	MOUNTAIN	m_DataMountain;				// 山データ
	FIELD		m_DataField[MAX_OBJECT];	// 地面データ
	WALL		m_DataWall[MAX_OBJECT];		// 壁データ
	BILLBOARD	m_DataTree[MAX_OBJECT];		// 木データ
	BILLBOARD	m_DataGrass[MAX_OBJECT];	// 草データ
	OCEAN		m_DataOcean[MAX_OBJECT];	// 海データ
	int			m_Point;					// 何を指しているのかの位置
	int			m_nFiledVerPoint;			// 地面の頂点の位置  
	int			m_nSpeed;					// 移動速度
	int			m_nSetObj;					// 何を設定しているのか
	USHORT		m_nTexNum;					// 画像番号
	EDIT_MODE	m_nEditMode;				// エディットモード
	POLYGON		m_Polygon;					// ポリゴンの設定
};
	
#endif // _STAGE_H_

// end of file