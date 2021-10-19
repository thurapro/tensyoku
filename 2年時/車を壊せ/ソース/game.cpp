//=============================================================================
//
// FAILE NAME [game.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �Q�[����������
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/game.h"
#include "../hedder/Texture.h"
#include "../hedder/Font.h"
#include "../hedder/InputKey.h"
#include "../hedder/Judgment.h"
#include "../hedder/BG.h"
#include "../hedder/Enemy.h"
#include "../hedder/Player.h"
#include "../hedder/Explosion.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/common.h"
#include <dsound.h>


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static LPDIRECTSOUNDBUFFER	g_BGM					= NULL;			// BGM�p
static BOOL					g_bSound				= FALSE;		// BGM���Ȃ��Ă��邩
static int					g_nGameTimer			= 180;			// �Q�[�����E�̎���
static int					g_nOneSecondSetting		= 0;			// 1�b�ݒ�
static DRAWFONT				g_Font					= { NULL };

//=============================================================================
//
// �֐���	: GameInit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �Q�[���̏�����
//
//=============================================================================
void GameInit( void )
{
	BGInit();
	PlayerInit();
	EnemyInit();
	ExplosionInit();
	if( !SoundFileLoad( "sound/BGM.wav" , 0) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_BGM , 0 ) )
	{
		return ;
	}

	g_nGameTimer = 180;

}

//=============================================================================
//
// �֐���	: GameUpdate�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �Q�[���̍X�V
//
//=============================================================================
void GameUpdate( void )
{
	// �v���C���[�|�C���^�錾
	PLAYER	*pPlayer;

	// �G�|�C���^�錾
	ENEMY	*pEnemy;

	PLAYERREMAINING *pRemain;

	pRemain = RemainGet();

	if( g_nOneSecondSetting == 60 )
	{
		// �Q�[���^�C�}�[�X�V
		g_nGameTimer--;

		g_nOneSecondSetting = 0;
	}

	// �v���C���[�̃L�[���͔���
	PlayerControlJudg();

	// �v���C���[�̍X�V
	PlayerUpdate();

	// �G�̓����X�V
	EnemyUpdate();

	// �����̓����X�V
	ExplosionUpdate( );

	pPlayer = PlayerGet();

	pEnemy = EnemyGet();

	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// �����蔻��
		if( HitJudg( pPlayer->fPlayerPosX , pPlayer->fPlayerPosY  ,
				pPlayer->fPlayerfWidth - 40 , pPlayer->fPlayerfHeight ,
				pEnemy[i].fEnemyPosX  , pEnemy[i].fEnemyPosY ,
				pEnemy[i].fEnemyfWidth , pEnemy[i].fEnemyfHeight - 70) )
		{
			// �v���C���[���ŏ��̃��[�V������������
			if( pPlayer->fPlayerTexX0 == PLAYER_TEXVTEXX0 && pPlayer->fPlayerTexX1 == PLAYER_TEXVTEXX1 )
			{
				if( pEnemy[i].bEnemyAttack != TRUE )
				{

					// �����v���C���[�������Ă�����
					if( pPlayer->bPlayerAlive == TRUE )
					{
						// �v���C���[�����S
						pPlayer->bPlayerAlive = FALSE;

						// ���񂾂Ƃ��ɏo��G�t�F�N�g���������v���C���[�̏ꏊ�ɃZ�b�g
						ExplosionPosSet( pPlayer->fPlayerPosX , pPlayer->fPlayerPosY ,
									pPlayer->fPlayerfWidth , pPlayer->fPlayerfHeight );
						
						pRemain->fPlayerRemainingX0 = 0.f;
						pRemain->fPlayerRemainingX1 -= 0.5f;
					}					

					pEnemy[i].bEnemyAttack = TRUE;
				}

			}
			else if( pPlayer->fPlayerTexX0 != PLAYER_TEXVTEXX0 && pPlayer->fPlayerTexX1 != PLAYER_TEXVTEXX1 )
			{			
				// �G���������SX���L�^(X���W)
				pEnemy[i].fEnemyOldX =  pEnemy[i].fEnemyPosX;

				// �G���������SY���L�^(Y���W)
				pEnemy[i].fEnemyOldY =  pEnemy[i].fEnemyPosY;
				
				// �G�̌��̕�
				pEnemy[i].fEnemyOldWidth = pEnemy[i].fEnemyfWidth;

				// �G�̌��̍���
				pEnemy[i].fEnemuOldHeight = pEnemy[i].fEnemyfHeight;

				// �G���X�e�[�W�ォ�����
				pEnemy[i].fEnemyfHeight		= 0;
				pEnemy[i].fEnemyfWidth		= 0;
				pEnemy[i].fEnemyPosX		= 0;
				pEnemy[i].fEnemyPosY		= 0;
				pEnemy[i].bEnemyAlive		= FALSE;

				ExplosionPosSet( pEnemy[i].fEnemyOldX  , pEnemy[i].fEnemyOldY , 
				pEnemy[i].fEnemyOldWidth , pEnemy[i].fEnemuOldHeight);
			}
		}
		if( ScreenOutJudg(pEnemy[i].fEnemyPosX ,pEnemy[i].fEnemyPosY ,
						pEnemy[i].fEnemyfWidth ,pEnemy[i].fEnemyfHeight)  == LEFT_OUT )
		{
			// 1���_�ݒ�
			pEnemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
			pEnemy[i].fEnemyPosY = ENEMY_POSY;

			// 2���_�ݒ�
			pEnemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
			pEnemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;
		}

	}
	

	// ��������
	RebornJudg();

	// �U���\������
	TurnJudg();

	g_nOneSecondSetting++;

	if( g_nGameTimer == 0 )
	{
		GameSelectSet( CLEAR );
		GameUninit();
	}

	if(pRemain->fPlayerRemainingX1 == 0.f)
	{
		GameSelectSet( OVER );
		GameUninit();
	}
}


//=============================================================================
//
// �֐���	: GameDraw�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �Q�[���̕`��
//
//=============================================================================
void GameDraw( void )
{
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	pPlayer		= PlayerGet();
	pEnemy		= EnemyGet();

	// �w�i�̕`��
	BGDraw();

	// �v���C���[�̕`��
	PlayerDraw();

	// �G�̕`��
	EnemyDraw();

	// �����̕`��
	ExplosionDraw();

	itoa( g_nGameTimer , g_Font.nGameTimer , 10 );
	itoa( pPlayer->nPlayerHP , g_Font.nPlayerHP , 10 );

	// �t�H���g
	FontDraw( 300 , 150 , 360 , 220 , g_Font.nGameTimer );

	FontDraw( 200 , 100 , 400 , 220 , g_Font.nPlayerHP );/*pPlayer->fPlayerPosX , pPlayer->fPlayerPosY - 20 ,
		pPlayer->fPlayerfWidth , pPlayer->fPlayerfHeight ,  g_Font.nPlayerH );*/

		// bgm���Đ�
	g_BGM->Play( 0 , 0 , 0 );
}

//=============================================================================
//
// �֐���	: GameUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �Q�[���̉��
//
//=============================================================================
void GameUninit( void )
{
	BGUninit();
	PlayerUninit();
	EnemyUninit();
	ExplosionUninit();
	if( g_BGM != NULL )
	{
		g_BGM->Release();
		g_BGM = NULL;
	}
}