//=============================================================================
// デバッグコード出力処理[debugproc.cpp]
// 
// 製作者 : 松尾 雄太
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "debugproc.h"

//=============================================================================
//	関数名	: CDebug
//	戻り値	: なし
//	引数	: なし
//	機能	: デバッグインスタンス生成
//=============================================================================
CDebug::CDebug(void)				
{
	ZeroMemory(&m_strDebug, MAX_STRING);	// バッファ初期化
	m_pFont		= NULL;						// フォントポインタ初期化
	m_Polygon	= D3DPT_TRIANGLESTRIP;		// ポリゴン線の書き方
	m_strLineType = NULL;					// プリミティブラインの種類
#ifdef _DEBUG
	m_bDebug	= true;						// デバッグモードか(false 文字出力なし, true文字出力)
#else
	m_bDebug	= false;					// デバッグモードか(false 文字出力なし, true文字出力)
#endif
}

//=============================================================================
//	関数名	: ~CDebug
//	戻り値	: なし
//	引数	: なし
//	機能	: デバッグインスタンス破棄
//=============================================================================
CDebug::~CDebug(void)
{
}

//=============================================================================
//	関数名	: Init
//	戻り値	: HRESULT
//	引数	: なし
//	機能	: デバッグ初期化
//=============================================================================
HRESULT CDebug::Init(void)
{
	// デバッグ初期化
	HRESULT hr;
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラー取得
		
	// フォント作成
	hr = D3DXCreateFont( pRenderer->GetDevice(),			// デバイス
						12,									// フォントの高さ
						8,									// フォントの幅
						0,									// フォントの太さ
						1,									// ミップマップレベル
						FALSE,								// 斜体
						SHIFTJIS_CHARSET,					// キャラクタセット(シフトJISを指定)
						OUT_DEFAULT_PRECIS,					// 出力精度
						DEFAULT_QUALITY,					// 品質
						DEFAULT_PITCH,						// ピッチ
						"Terminal"	,						// フォント名保持
						&m_pFont);
	ERROR_CHACK(hr);										// エラーチェック
	

	return S_OK;											// 初期化終了
}

//=============================================================================
//	関数名	: Uninit
//	戻り値	: なし
//	引数	: なし
//	機能	: デバッグ終了
//=============================================================================
void CDebug::Uninit(void)
{
	SALF_RELEASE(m_pFont);				// デバッグ破棄
}

//=============================================================================
//	関数名	: Update
//	戻り値	: なし
//	引数	: なし
//	機能	: デバッグ更新
//=============================================================================
void CDebug::Update(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// デバッグモード切替処理
	if( pKeyboard->KeyPush(DIK_F1) )
	{
		// デバッグモード設定
		if( m_bDebug == false )
		{
			// デバッグモードでなければ
			m_bDebug = true;				// デバッグ出力をおこなう
		}
		else
		{
			// デバッグモードであれば
			m_bDebug = false;				// デバッグ出力を行わない
		}
	} // デバッグモード切替処理終了

	// デバッグモードのみ有効
	if( m_bDebug == true )
	{
		// ポリゴン線の書き方切り替え処理
		if( pKeyboard->KeyPush(DIK_F2) )
		{
			// 種類選択
			m_Polygon += 1;
			if( m_Polygon > D3DPT_TRIANGLEFAN )
			{
				m_Polygon = D3DPT_POINTLIST;
			}
		}
		else if( pKeyboard->KeyPush(DIK_F3) )
		{
			// 種類選択
			m_Polygon = D3DPT_TRIANGLESTRIP;
		}
	}
	else
	{
		// トライアングルストリップに変更
		m_Polygon = D3DPT_TRIANGLESTRIP;
	}

	// ライン種類の名前を設定
	switch( m_Polygon )
	{
	case D3DPT_POINTLIST:						// ポイントリスト
		m_strLineType = "D3DPT_POINTLIST";
		break;
	case D3DPT_LINELIST:						// ラインリスト
		m_strLineType = "D3DPT_LINELIST";
		break;
	case D3DPT_LINESTRIP:						// ラインストリップ
		m_strLineType = "D3DPT_LINESTRIP";
		break;
	case D3DPT_TRIANGLELIST:					// トライアングルリスト
		m_strLineType = "D3DPT_TRIANGLELIST";
		break;
	case D3DPT_TRIANGLESTRIP:					// トライアングルストリップ
		m_strLineType = "D3DPT_TRIANGLESTRIP";
		break;
	case D3DPT_TRIANGLEFAN:						// トライアングルファン
		m_strLineType = "D3DPT_TRIANGLEFAN";
		break;
	}
	Print("ライン種類: %s\n", m_strLineType);
}


//=============================================================================
//	関数名	: Draw
//	戻り値	: なし
//	引数	: なし
//	機能	: デバッグ描画
//=============================================================================
void CDebug::Draw(void)
{
	RECT rect = {0, 0, WINDOW_HEIGHT, WINDOW_WIDTH};	// 描画領域指定

	if( m_bDebug == true )
	{
		// デバッグ出力モードになっていれば
		m_pFont->DrawText(
					NULL,								// スプライト機能を使うか
					m_strDebug,							// 文字列
					-1,									// 文字数(NULL終端まで表示)
					&rect,								// 描画領域
					DT_NOCLIP,							// クリップしない
					D3DCOLOR_XRGB(255, 192, 0) );		// 文字色
	}
	
	// デバッグバッファクリア
	ZeroMemory(&m_strDebug, MAX_STRING);
}
	
//=============================================================================
//	関数名	: Print
//	戻り値	: なし
//	引数	: 出力したい文字列, 表示したい変数
//	機能	: デバッグバッファに書き込み
//=============================================================================
void CDebug::Print(char *pFmt , ...)
{
	va_list pArg;							// 変数宣言 (可変引数解析)
	char szBuffer[MAX_STRING];				// 変数宣言	(バッファ)
	ZeroMemory(szBuffer, MAX_STRING);		// バッファクリア
	va_start(pArg, pFmt);					// 文字識別開始
	vsprintf_s(szBuffer, pFmt, pArg);		// バッファに書き込み
	va_end(pArg);							// 文字識別終了
	strcat_s(m_strDebug, szBuffer);			// 文字列を結合
}

//=============================================================================
//	関数名	: GetPolygonLine
//	戻り値	: プリミティブ種類
//	引数	: なし
//	機能	: プリミティブ線の種類を取得
//=============================================================================
D3DPRIMITIVETYPE CDebug::GetPolygonLine(void)
{ 
	return (D3DPRIMITIVETYPE)m_Polygon; 
}

//=============================================================================
//	関数名	: GetDebugMode
//	戻り値	: デバッグモードなのかのフラグ
//	引数	: なし
//	機能	: プリミティブ線の種類を取得
//=============================================================================
bool CDebug::GetDebugMode(void)
{
	// デバッグモード取得
	return m_bDebug;
}