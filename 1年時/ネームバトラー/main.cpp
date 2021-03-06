//===============================
// ファイル名 : main.cpp
// 作成者 : 松尾　雄太
// クラス :　GP12BB02
// 出席番号 : 15番
// 機能 : ネームバトラー
//		　ストーリー構成
//		　名前入力
//		　名前からステータスを作成
//		　敵とバトル
//		　どちらかのライフがなくなり
//		　しだいゲーム終了
//===============================

//===============================
// ヘッダーファイル読み込み
#include <stdio.h>						//　スタンダードヘッダーファイル
#include "Cscreen.h"					//	装飾を可能にするヘッダーファイル
#include <windows.h>					//	windowsの機能を使えるヘッダーファイル
#include <string.h>						//	文字列ヘッダーファイル
#include <stdlib.h>						//	乱数ヘッダーファイル
#include <time.h>						//	時間読み込みヘッダーファイル

//================================
// 定数定義
#define	STRING_MAX (1024)				// 文字列の最大値
#define DAMAGE_MAX (10)					// ダメージ文字列の最大値
#define	RANDM_DAMAGE (10)				// 乱数選択で割る値
#define INT_NUM_TEN (10)				// itoaで使う。10進数を表す

//=================================
// 構造体定義

// 自分のステータス構造体
typedef struct
{
	char szNAME[9];
	int nHP;
	int nATP;
	int nDFP;
} STATUS;

// 敵のステータス構造体
typedef struct
{
	char szNAME[9];
	int nHP;
	int nATP;
	int nDFP;
} ENEMY;

//=====================================================================
// プロトタイプ宣言

// ファイルの開閉作業用
int openfile(int nFile, STATUS *aPlayer, int nStorycnt, int nStoryEnd);

// バトル時の計算、何のダメージを与えたかの出力
bool battle(STATUS *pOffence,				//	バトルを成立させるため
		   ENEMY *pDffence);

//===================================
// 関数名 : main
// 戻り値 : 正常に起動か、動作の失敗
// 引数 : なし
// 機能 : 音楽を流す、開く
//		　自分・敵の名前入力
//		　名前の文字数判定
//		　決定でいいのかの質問,判定
//		　入力ミスはもう一度入力
//		　音楽を停止、閉じる
//===================================
int main()
{
	//===============================
	// ローカル変数定義
	STATUS aPlayer[1];					// マイキャラクターのステータス配列
	ENEMY aEnemy[1];					// 相手キャラクターのステータス配列
	int nFilecnt = 0;					// ファイルの個数のカウント
	int nAnswer = 0;
	bool bFinalAnswer = false;
	int nStrCnt = 0;
	int nStoryLine = 0;
	int nMIDIHandle;
	int nMP3Handle;
	int nStoryEnd = 0;
	bool bBackNum;
	nMIDIHandle = OPENMIDI("START.mid");
	if(nMIDIHandle == NULL)
	{
		printf("音楽再生に失敗しました\n");
		exit(0);
	}
	nMP3Handle = OPENMP3("storyBGM.mp3");
	if(nMP3Handle == NULL)
	{
		printf("音楽再生に失敗しました\n");
		exit(0);
	}
	CUROFF();
	CLS(PINK,BLACK);
	PLAYMIDI(nMIDIHandle,1);
	LOCATE(10,2);
	printf("■＿＿＿＿■＿＿＿＿■■＿＿＿＿■＿＿＿＿＿■＿＿■■■■■\n");
	LOCATE(10,3);
	printf("■■＿＿＿■＿＿＿＿■■＿＿＿＿■■＿＿＿■■＿＿■＿＿＿＿\n");
	LOCATE(10,4);
	printf("■■＿＿＿■＿＿＿■＿＿■＿＿＿■■＿＿＿■■＿＿■＿＿＿＿\n");
	LOCATE(10,5);
	printf("■＿■＿＿■＿＿＿■＿＿■＿＿＿■＿■＿■＿■＿＿■＿＿＿＿\n");
	LOCATE(10,6);
	printf("■＿■＿＿■＿＿＿■＿＿■＿＿＿■＿■＿■＿■＿＿■■■■＿\n");
	LOCATE(10,7);
	printf("■＿＿■＿■＿＿■■■■■■＿＿■＿■＿■＿■＿＿■＿＿＿＿\n");
	LOCATE(10,8);
	printf("■＿＿＿■■＿＿■＿＿＿＿■＿＿■＿＿■＿＿■＿＿■＿＿＿＿\n");
	LOCATE(10,9);
	printf("■＿＿＿■■＿＿■＿＿＿＿■＿＿■＿＿■＿＿■＿＿■＿＿＿＿\n");
	LOCATE(10,10);
	printf("■＿＿＿＿■＿＿■＿＿＿＿■＿＿■＿＿＿＿＿■＿＿■■■■■\n");
	LOCATE(10,11);
	printf("＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿\n");
	LOCATE(4,12);
	printf("■■■■＿＿■＿＿＿＿■＿■■■■■＿■＿＿＿＿■■■■＿＿■■■■＿＿\n");
	LOCATE(4,13);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿＿■＿\n");
	LOCATE(4,14);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿＿■＿\n");
	LOCATE(4,15);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿＿■＿\n");
	LOCATE(4,16);
	printf("■■■■＿＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■■■■＿＿＿■■■■＿\n");
	LOCATE(4,17);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿■＿＿\n");
	LOCATE(4,18);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿＿■＿\n");
	LOCATE(4,19);
	printf("■＿＿＿■＿■＿＿＿＿■＿＿＿■＿＿＿■＿＿＿＿■＿＿＿＿＿■＿＿＿■＿\n");
	LOCATE(4,20);
	printf("■■■■＿＿＿■■■■＿＿＿＿■＿＿＿■■■■＿■■■■＿＿■＿＿＿＿■\n");
	LOCATE(28,24);
	printf("ENTERを押してね!!");
	getchar();
	CLS();
	CLOSEMIDI(nMIDIHandle);
	PLAYMP3(nMP3Handle,3);
	while(1)
	{
		LOCATE(28, 10);
		printf("ストーリをとばしたい！\n");
		LOCATE(28, 11);
		printf("1 = はい, 0 = いいえ\n");
		LOCATE(28, 12);
		CURON();
		scanf("%d", &nStoryEnd);
		if(nStoryEnd < 0 || nStoryEnd >= 2)
		{
			printf("もう一度入力してください\n");
		}
		else
		{
			LOCATE(28, 13);
			printf("ENTERを押してね!");
			rewind(stdin);
			getchar();
			break;
		}
	}
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	if(nStoryEnd == 1)
	{
		nStoryEnd = 2;
	}
	nStoryLine = 1;
	while(bFinalAnswer == false)
	{
		CLS(GREEN,SKYBLUE);
		while(1)
		{
			LOCATE(16,5);
			printf("名前を決めてね!![半角8文字　全角は入力しないで!!]");
			LOCATE(16,6);
			CURON();
			scanf("%s",aPlayer[0].szNAME);
			CUROFF();
			for (nStrCnt = 0; aPlayer[0].szNAME[nStrCnt] != '\0'; nStrCnt++);
			nStrCnt = nStrCnt - 1;
			if(nStrCnt > 7)
			{
				LOCATE(28,6);
				printf("もう一度入力しなおしてください");
				Sleep(0);
			}
			else
			{
				break;
			}
		}
		LOCATE(16,7);
		printf("これでよろしいでしょうか？");
		LOCATE(16,8);
		printf("1:はい,2:いいえ");
		while(1)
		{
			LOCATE(16,9);
			CURON();
			scanf("%d", &nAnswer);
			CUROFF();
			if(nAnswer < 0 || nAnswer >= 3)
			{
				LOCATE(28,7);
				printf("もう一度入力し直してね!\n");
				Sleep(0);
			}
			else
			{
				break;
			}
		}

		nAnswer = nAnswer - 1;
		switch(nAnswer)
		{
		case 0:
			bFinalAnswer = true;
			break;
		case 1:
			bFinalAnswer = false;
			break;
		}
	}
	system("cls");
	printf("ステータスを作成します\n");
	printf("\n何か押してね!");
	rewind(stdin);
	getchar();
	system("cls");
	
	aPlayer[0].nHP = aPlayer[0].szNAME[0 + nStrCnt];
	aPlayer[0].nHP = aPlayer[0].nHP * 4;
	if(aPlayer[1].nHP < 0)
	{
		aPlayer[1].nHP = aPlayer[0].nHP + 200;
	}
	aPlayer[0].nATP = aPlayer[0].nHP / 2 + 2 * 3;
	aPlayer[0].nDFP = aPlayer[0].nHP / 2 + (3 * 4);
	nFilecnt = 1;
	openfile(nFilecnt, &aPlayer[0] ,nStoryLine, nStoryEnd);
	LOCATE(2,2);
	printf("名前 = %s\n", aPlayer[0].szNAME);
	LOCATE(2,3);
	printf("体力値 = %d\n", aPlayer[0].nHP);
	LOCATE(2,4);
	printf("攻撃力 = %d\n", aPlayer[0].nATP);
	LOCATE(2,5);
	printf("防御力 = %d\n", aPlayer[0].nDFP);
	rewind(stdin);
	getchar();
	system("cls");
	nFilecnt = 2;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	nFilecnt = 0;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	STOPMP3(nMP3Handle);
	nFilecnt = 3;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	CLOSEMP3(nMP3Handle);
	nStoryEnd = 0;
	nFilecnt = 4;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	while(1)
	{
		LOCATE(16,5);
		printf("名前を決めてね!![半角8文字　全角は入力しないで!!]※1回だけ※");
		LOCATE(16,6);
		CURON();
		scanf("%s",aEnemy[0].szNAME);
		CUROFF();
		for (nStrCnt = 0; aEnemy[0].szNAME[nStrCnt] != '\0'; nStrCnt++);
		nStrCnt = nStrCnt - 1;
		if(nStrCnt > 7)
		{
			LOCATE(28,6);
			printf("もう一度入力しなおしてください");
			Sleep(0);
		}
		else
		{
			break;
		}
	}
	aEnemy[0].nHP = aEnemy[0].szNAME[0 + nStrCnt];
	aEnemy[0].nHP = aEnemy[0].nHP * 4 + 3;
	if(aPlayer[1].nHP < 0)
	{
		aPlayer[1].nHP = 200;
	}
	aEnemy[0].nATP = aEnemy[0].nHP / 2 + 2 * 3 + 9;
	aEnemy[0].nDFP = aEnemy[0].nHP / 2 + (3 * 4) + 5;
	if(aPlayer[0].nATP <= aEnemy[0].nDFP)
	{
		aEnemy[0].nDFP = aEnemy[0].nDFP - 50;
	}
	nFilecnt = 1;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	LOCATE(2,2);
	printf("名前 = %s\n", aEnemy[0].szNAME);
	LOCATE(2,3);
	printf("体力値 = %d\n", aEnemy[0].nHP);
	LOCATE(2,4);
	printf("攻撃力 = %d\n", aEnemy[0].nATP);
	LOCATE(2,5);
	printf("防御力 = %d\n", aEnemy[0].nDFP);
	rewind(stdin);
	getchar();
	nStoryLine = 2;
	nFilecnt = 4;
	openfile(nFilecnt, aPlayer, nStoryLine, nStoryEnd);
	
	//　バトル勝敗判定
	bBackNum = battle(aPlayer, aEnemy);	
	if(bBackNum == true)												//	falseが返った場合
	{
		int LOSE();
		int nLose;
		system("cls");
		nLose = LOSE();
	}
	if(bBackNum == false)
	{
		int WIN();
		int nWin;
		system("cls");
		nWin = WIN();
	}
	rewind(stdin);
	getchar();
	return 0;
}
//==================================================
// 関数 : battle関数
// 引数 : STATUS *pOffence 攻撃側の指定
//		  STATUS *pDffence 守り側の指定
// 戻り値 : ture or false  攻守交代
// 機能 : ダメージをランダムで選択
//				攻守交代
//				名前と残りの体力とダメージ結合
//				結合後の文字列を出力
//---------------------------------------------------
bool battle(STATUS	*pOffence,
			ENEMY	*pDffence)
{
	char szDffence[STRING_MAX];										//	Dffenceダメージを表示させるための文字列
	int	nDamage;													//	ランダムで出たダメージの格納場所
	char szDamage[DAMAGE_MAX];										//	Offenceダメージを表示させるための文字列
	int nCritical;

	srand((int) time(NULL));										//	時間を整数型にしてランダムの種にしている

	nDamage = rand() % RANDM_DAMAGE;								//	ダメージをランダムで設定


	//================================
	//	自分と敵の攻防変更
	while(1)
	{
		if(pOffence->nHP != 0)
		{
			nCritical = rand() % 10;
			strcpy_s(szDffence,pOffence->szNAME);
			strcat_s(szDffence,"は、");
			strcat_s(szDffence,pDffence->szNAME);
			strcat_s(szDffence,"に");
			strcat_s(szDffence,"攻撃");
			int	nLen = strlen(szDffence);
			if(nCritical == 10)
			{
				nDamage = pOffence->nATP;
				itoa(nDamage,szDamage,INT_NUM_TEN);
				strcat_s(szDffence,"クリティカルヒット!!");
				strcat_s(szDffence,szDamage);
				pDffence->nHP -= nDamage;
			}
			else
			{
				nDamage = rand() % pOffence->nATP;
				nDamage = rand() % pDffence->nDFP - nDamage;
				if(nDamage < 0)
				{
					nDamage = nDamage + (nDamage * -2);
				}
				else
				{
					nDamage = nDamage;
				}
				itoa(nDamage,szDamage,INT_NUM_TEN);
				strcat_s(szDffence,szDamage);
				if(nDamage < 0)
				{
					pDffence->nHP += nDamage;
				}
				else
				{
					pDffence->nHP -= nDamage;
				}
				itoa(pOffence->nHP,szDamage,INT_NUM_TEN);
			}
			strcat_s(szDffence,"のダメージ!\n");
			LOCATE(23,26);
			printf("%s",szDffence);
			//=====================================
			// 自分のステータス表示
			LOCATE(2,25);
			printf("名前 = %s\n", pOffence->szNAME);
			LOCATE(2,26);
			printf("体力値 = %d\n", pOffence->nHP);
			LOCATE(2,27);
			printf("攻撃力 = %d\n", pOffence->nATP);
			LOCATE(2,28);
			printf("防御力 = %d\n", pOffence->nDFP);
			//======================================
			// 相手のステータス表示
			LOCATE(65,25);
			printf("名前 = %s\n", pDffence->szNAME);
			LOCATE(65,26);
			printf("体力値 = %d\n", pDffence->nHP);
			LOCATE(65,27);
			printf("攻撃力 = %d\n", pDffence->nATP);
			LOCATE(65,28);
			printf("防御力 = %d\n", pDffence->nDFP);
			getchar();
		}
		if(pDffence->nHP != 0)
		{
			nCritical = rand() % 25;
			strcpy_s(szDffence,pDffence->szNAME);
			strcat_s(szDffence,"は、");
			strcat_s(szDffence,pOffence->szNAME);
			strcat_s(szDffence,"に");
			strcat_s(szDffence,"攻撃");
			int	nLen = strlen(szDffence);
			if(nCritical == 4)
			{
				nDamage = pOffence->nATP;
				itoa(nDamage,szDamage,INT_NUM_TEN);
				strcat_s(szDffence,"クリティカルヒット!!");
				strcat_s(szDffence,szDamage);
				strcat_s(szDffence,"のダメージ!\n");
				pOffence->nHP -= nDamage;
			}
			else
			{
				nDamage = rand() % pDffence->nATP;
				nDamage = rand() % pOffence->nDFP - nDamage;
				if(nDamage < 0)
				{
					nDamage = nDamage + (nDamage * -2);
				}
				else
				{
					nDamage = nDamage;
				}
				itoa(nDamage,szDamage,INT_NUM_TEN);
				strcat_s(szDffence,szDamage);
				strcat_s(szDffence,"のダメージ!\n");
				if(nDamage < 0)
				{
					pOffence->nHP += nDamage;
				}
				else
				{
					pOffence->nHP -= nDamage;
				}
				itoa(pOffence->nHP,szDamage,INT_NUM_TEN);
			}
			LOCATE(23,26);
			printf("%s",szDffence);
			//======================================
			// 自分のステータス表示
			LOCATE(2,25);
			printf("名前 = %s\n", pOffence->szNAME);
			LOCATE(2,26);
			printf("体力値 = %d\n", pOffence->nHP);
			LOCATE(2,27);
			printf("攻撃力 = %d\n", pOffence->nATP);
			LOCATE(2,28);
			printf("防御力 = %d\n", pOffence->nDFP);
			//======================================
			// 相手のステータス表示
			LOCATE(65,25);
			printf("名前 = %s\n", pDffence->szNAME);
			LOCATE(65,26);
			printf("体力値 = %d\n", pDffence->nHP);
			LOCATE(65,27);
			printf("攻撃力 = %d\n", pDffence->nATP);
			LOCATE(65,28);
			printf("防御力 = %d\n", pDffence->nDFP);
			getchar();
		}
		//===============================
		//	HP判定
		if(pOffence->nHP <= 0)								//	自分のHP判定
		{
			return true;
		}
		if(pDffence->nHP <= 0)
		{
			return false;
		}
	}
}
int openfile(int nFile, STATUS *aPlayer, int nStorycnt, int nStoryEnd)
{
	FILE *fpStory[5];
	char *fpFile_serect[5] = {"story.txt", "fram.txt","name.txt","HOME.txt", "BATTLE.txt"};
	char szStoryText[1024];
	int i = 0;
	i = i + nFile;
	int nCnt = 0;	
	int nBackcolor = 0;
	int nMP3Handle;
	int nXos = 15;
	int nYos = 10;
	CLS(WHITE,GREEN);
	switch(nFile)
	{
	case 0:	
			fpStory[i] = fopen(fpFile_serect[nFile],"r");
			while(fpStory[i] == NULL)
			{
				printf("ファイルが開けません\n");
				return EOF;
			}
			while(fgets(szStoryText, 1024, fpStory[i]) != NULL)
			{
				if(nStoryEnd == 1)
				{
					return 0;
				}
				if(nStorycnt == 0)
				{
					if(nStorycnt == 0)
					{
						LOCATE(8,10);
						printf("%s", szStoryText);
						Sleep(1200);
						system("cls");
					}
					if(nStoryEnd == 1)
					{
						nCnt = 11;
					}
					if(nCnt == 11)
					{
						if(nStorycnt == 0)
						{
							fclose(fpStory[i]);
							return 0;
						}
					}
				}
				if(nStorycnt == 1)
				{
					if(nCnt == 14)
					{
						i = 2;
						nFile = 2;
						fpStory[i] = fopen(fpFile_serect[nFile],"r");
						while(fpStory[i] == NULL)
						{	
							printf("ファイルが開けません\n");
							return EOF;
						}
						while(fgets(szStoryText, 1024, fpStory[i]) != NULL)
						{
							LOCATE(4,10);
							printf("%s", szStoryText);
							Sleep(1200);
							system("cls");
						}
						if(nStoryEnd == 2)
						{
							break;
						}
						fclose(fpStory[i]);
						i = 0;
						nFile = 0;
						fpStory[i] = fopen(fpFile_serect[nFile],"r");
						nCnt = 0;
						nStorycnt = 2;
					}
				}
				if(nStorycnt == 2)
				{
					if(nCnt >= 15)
					{
						LOCATE(4,10);
						printf("%s", szStoryText);
						Sleep(1200);
						system("cls");
					}
					nCnt++;
				}
				else
				{
					nCnt++;
				}
			}
			break;

	case 1:
		fpStory[i] = fopen(fpFile_serect[nFile],"r");
		while(fpStory[i] == NULL)
		{
			printf("ファイルが開けません\n");
			return EOF;
		}
		while(fgets(szStoryText, 1024, fpStory[i]) != NULL)
		{
			printf("%s", szStoryText);
		}
		break;
	case 2:
		fpStory[i] = fopen(fpFile_serect[nFile],"w");
		fprintf(fpStory[i],"ファントム「%sって名前なんだ。いい名前だね!!」", aPlayer[0].szNAME);
		break;
	case 3:
		fpStory[i] = fopen(fpFile_serect[nFile],"r");
		if(nStoryEnd == 2)
		{
			break;
		}
		while(fpStory[i] == NULL)
		{
			printf("ファイルが開けません\n");
			return EOF;
		}
		while(fgets(szStoryText, 1024, fpStory[i]) != NULL)
		{
			if(nStoryEnd == 2)
			{
				break;
			}
			if(nCnt <= 9)
			printf("%s", szStoryText);
			if(nCnt == 10)
			{
				nMP3Handle = OPENMP3("end.mp3");   // オープン＆初期化
				if (nMP3Handle == 0)
				{
					 printf("MP3ファイルの再生準備に失敗しました。\n");
					 exit(0);
				}
				PLAYMP3(nMP3Handle, 1);
				CLS(WHITE,RED);
				Sleep(350);
				CLS(RED,BLACK);
				Sleep(350);
				CLS(GREEN,PINK);
				Sleep(350);
				CLS(RED,BLACK);
				Sleep(350);
				CLS(WHITE,RED);
			}
			if(nCnt >= 11 && nCnt < 24)
			{
				LOCATE(0,10);
				printf("%s", szStoryText);
			}
			nCnt++;
		}
		CLOSEMP3(nMP3Handle);
		break;
	case 4:
		fpStory[i] = fopen(fpFile_serect[nFile],"r");
		if(fpStory[i] == NULL)
		{
			printf("ファイルが開けません\n");
			return 0;
		}
		while(fgets(szStoryText, 1024, fpStory[i]) != NULL)
		{
			if(nStorycnt == 1)
			{
				if(nCnt <= 10)
				{
					printf("%s", szStoryText);
				}
				if(nCnt == 10)
				{
					Sleep(1000);
					system("cls");
					return 0;
				}
			}
			else if(nStorycnt == 2)
			{
				if(nCnt == 11)
				{
					BACKCOLOR(BLACK);
					Sleep(350);
					BACKCOLOR(YELLOW);
					Sleep(350);
					BACKCOLOR(BLACK);
					Sleep(350);
					BACKCOLOR(YELLOW);
					CLS(WHITE,L_BLUE);
				}
				if(nCnt >= 12)
				{
					printf("%s", szStoryText);
				}
				if(nCnt == 33)
				{
					return 0;
				}
			}
			nCnt++;
		}
	}
	fclose(fpStory[i]);	

	return 0;
}
