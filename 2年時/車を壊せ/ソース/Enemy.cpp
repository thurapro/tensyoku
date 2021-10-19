//=============================================================================
//
// FAILE NAME [Enemy.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �v���C���[�̐ݒ�
//
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Enemy.h"
#include "../hedder/Texture.h"
#include "../hedder/game.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Judgment.h"
#include "../hedder/Player.h"
#include "../hedder/Explosion.h"


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static ENEMY g_Enemy[ENEMY_MAX];
static int g_EnemyWate = 0;
static int g_bEnemyTex[ENEMY_MAX] = {FALSE};

//=============================================================================
//
// �֐���	: EnemyInit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̏�����
//
//=============================================================================
void EnemyInit( void )
{
	for( int i = 0; i < ENEMY_MAX; i++ )
	{

		// �e�N�X�`���[�����[�h
		TextureLoad("photo/sample002.png", ENEMY_NUM + i  );
		g_bEnemyTex[i] = TRUE;
		
		
		// 1���_�ݒ�
		g_Enemy[i].fEnemyPosX = SCREEN_WIDTH;
		if( g_Enemy[0].fEnemyfWidth )
		{
			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * 0.5;
		}
		g_Enemy[i].fEnemyPosY = ENEMY_POSY;

		// 2���_�ݒ�
		g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
		g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;

		// �e�N�X�`���̒��_1�ݒ�
		g_Enemy[i].fEnemyTexX0 = ENEMY_TEXVTEXX0;
		g_Enemy[i].fEnemyTexY0 = ENEMY_TEXVTEXY0;

		// �e�N�X�`���̒��_2�ݒ�
		g_Enemy[i].fEnemyTexX1 = ENEMY_TEXVTEXX1;
		g_Enemy[i].fEnemyTexY1 = ENEMY_TEXVTEXY1;

		// �G�̏o���҂�
		g_Enemy[i].nEnemyWate = 0;
		
		// �v���C���[�̊p�x��ݒ�(���W�A���l)
		g_Enemy[i]. fEnemyAngle = ENEMY_ANGLE; 

		// �G�������Ă��邩
		g_Enemy[i].bEnemyAlive = TRUE;

		// �G�̌��̍��WX
		g_Enemy[i].fEnemyOldX = 0;

		// �G�̌��̍��WY
		g_Enemy[i].fEnemyOldY = 0;

		// �G�͍U��������
		g_Enemy[i].bEnemyAttack = FALSE;

		// �G�͖h�䂵����
		g_Enemy[i].bEnemyDefense = FALSE;
	}
}

//=============================================================================
//
// �֐���	: EnemyUpdate�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̍X�V
//
//=============================================================================
void EnemyUpdate( void )
{	
	PLAYER *Player;
	Player =  PlayerGet();

	EnemyLeft();

	//for( int i = 0; i < ENEMY_MAX; i++ )
	//{
	//	if( g_Enemy[i].bEnemyAlive == TRUE )
	//	{
	//		// �����������Ă�����
	//		if( HitJudg(	Player->fPlayerPosX , Player->fPlayerPosY , 
	//						Player->fPlayerfWidth - 20 , Player->fPlayerfHeight ,
	//						g_Enemy[i].fEnemyPosX , g_Enemy[i].fEnemyPosY ,
	//						g_Enemy[i].fEnemyfWidth + 20 , g_Enemy[i].fEnemyfHeight) )
	//		{
	//			if( Player->fPlayerTexX0 != PLAYER_TEXVTEXX0 && Player->fPlayerTexX1 != PLAYER_TEXVTEXX1 )
	//			{
	//				
	//					// �G���������SX���L�^(X���W)
	//					g_Enemy[i].fEnemyOldX =  g_Enemy[i].fEnemyPosX;

	//					// �G���������SY���L�^(Y���W)
	//					g_Enemy[i].fEnemyOldY =  g_Enemy[i].fEnemyPosY;
	//					
	//					// �G�̌��̕�
	//					g_Enemy[i].fEnemyOldWidth = g_Enemy[i].fEnemyfWidth;

	//					// �G�̌��̍���
	//					g_Enemy[i].fEnemuOldHeight = g_Enemy[i].fEnemyfHeight;

	//					// �G���X�e�[�W�ォ�����
	//					g_Enemy[i].fEnemyfHeight	= 0;
	//					g_Enemy[i].fEnemyfWidth		= 0;
	//					g_Enemy[i].fEnemyPosX		= 0;
	//					g_Enemy[i].fEnemyPosY		= 0;
	//					g_Enemy[i].bEnemyAlive		= FALSE;

	//					ExplosionPosSet( g_Enemy[i].fEnemyOldX  , g_Enemy[i].fEnemyOldY , 
	//					g_Enemy[i].fEnemyOldWidth , g_Enemy[i].fEnemuOldHeight);
	//			}
	//		}
	//	
	//		if( ScreenOutJudg( g_Enemy[i].fEnemyPosX , g_Enemy[i].fEnemyPosY ,
	//					g_Enemy[i].fEnemyfWidth , g_Enemy[i].fEnemyfHeight)  == LEFT_OUT )
	//		{
	//			// 1���_�ݒ�
	//			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
	//			g_Enemy[i].fEnemyPosY = ENEMY_POSY;

	//			// 2���_�ݒ�
	//			g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
	//			g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;
	//		}

	//	}
	//}
}

//=============================================================================
//
// �֐���	: EnemyDraw�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̕`��
//
//=============================================================================
void EnemyDraw( void )
{
	// ���ׂĂ̓G��`��
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			PrimitiveCreate(	ENEMYID					,	
								ROTATION						,
								ENEMY_NUM				,
								g_Enemy[i].fEnemyAngle		,
								g_Enemy[i].fEnemyPosX		, 
								g_Enemy[i].fEnemyPosY		,
								g_Enemy[i].fEnemyfWidth	,
								g_Enemy[i].fEnemyfHeight	,
								g_Enemy[i].fEnemyTexX0		,
								g_Enemy[i].fEnemyTexY0		,
								g_Enemy[i].fEnemyTexX1		,
								g_Enemy[i].fEnemyTexY1		);
		}
	}
}

//=============================================================================
//
// �֐���	: EnemyLeft�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̍��ړ�
//
//=============================================================================
void EnemyLeft( void )
{
	for( int i= 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			g_Enemy[i].fEnemyPosX -= 2.f;
		}
	}
}

//=============================================================================
//
// �֐���	: EnemyRight�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̉E�ړ�
//
//=============================================================================
void EnemyRight( void )
{
	// ���ׂĂ̓G���E�ֈړ�
	for( int i= 0; i < ENEMY_MAX; i++ )
	{
		// �����G�������Ă�����
		if( g_Enemy[i].bEnemyAlive == TRUE )
		{
			g_Enemy[i].fEnemyPosX += 2.f;
		}
	}
}


//=============================================================================
//
// �֐���	: PlayerUninit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̉��
//
//=============================================================================
void EnemyUninit( void )
{
	// �v���C���[�̃e�N�X�`�����
	TextureUninit( ENEMY_NUM );
}

//=============================================================================
//
// �֐���	: EnemyGet�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �G�̃Q�b�^�[
//
//=============================================================================
ENEMY* EnemyGet( void )
{
	return &g_Enemy[0];
}

//=============================================================================
//
// �֐���	: EnemySet�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: EnemyAlive
//
// �@�\		: �G�̃Z�b�^�[
//
//=============================================================================
void EnemySet( ENEMY *pEnemy )
{
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( g_Enemy[i].bEnemyAlive == FALSE )
		{
			// 1���_�ݒ�
			g_Enemy[i].fEnemyPosX = SCREEN_WIDTH * ( (float)i + 1.f ) + 2.f ;
			g_Enemy[i].fEnemyPosY = ENEMY_POSY;

			// 2���_�ݒ�
			g_Enemy[i].fEnemyfWidth = ENEMY_WIDHTINIT;
			g_Enemy[i].fEnemyfHeight = ENEMY_HEIGHTINIT;


			// �e�N�X�`���̒��_1�ݒ�
			g_Enemy[i].fEnemyTexX0 = ENEMY_TEXVTEXX0;
			g_Enemy[i].fEnemyTexY0 = ENEMY_TEXVTEXY0;

			// �e�N�X�`���̒��_2�ݒ�
			g_Enemy[i].fEnemyTexX1 = ENEMY_TEXVTEXX1;
			g_Enemy[i].fEnemyTexY1 = ENEMY_TEXVTEXY1;


			// �G������
			g_Enemy[i].bEnemyAlive = TRUE;

			// �G���U���\�ƂȂ�
			g_Enemy[i].bEnemyAttack = pEnemy[i].bEnemyAttack;
		}
	}
}

