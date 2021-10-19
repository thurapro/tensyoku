//=============================================================================
//
// FAILE NAME [Player.cpp]
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
#include "../hedder/Player.h"
#include "../hedder/Texture.h"
#include "../hedder/game.h"
#include "../hedder/common.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/BG.h"
#include "../hedder/Judgment.h"
#include "../hedder/Sound.h"
#include "../hedder/Enemy.h"
#include "../hedder/Explosion.h"
#include <dsound.h>


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static PLAYER g_Player;					// �v���C���[�\���̒�`
static int g_Attack_Wate = 0;			// �U���҂�����
static BOOL g_bAttack = FALSE;			// �U�������Đ����ꂽ��
static LPDIRECTSOUNDBUFFER g_SAttack;	// �U�����o�b�t�@�쐬
static int g_PlayerTimer = 0;			// �v���C���[�̘A���U�����ł���^�C�}�[
static BOOL g_bPlayerTex = FALSE;
static BOOL g_bAttackSou = FALSE;
static PLAYERREMAINING g_Remain;


//=============================================================================
//
// �֐���	: PlayerInit�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ������
//
//=============================================================================
void PlayerInit( void )
{

	// �e�N�X�`���[�����[�h
	TextureLoad("photo/Player.png", PLAYER_NUM );

	// 1���_�ݒ�
	g_Player.fPlayerPosX = PLAYER_POSX_INIT;
	g_Player.fPlayerPosY = PLAYER_POSY_INIT;

	// 2���_�ݒ�
	g_Player.fPlayerfWidth = PLAYER_WIDTHINIT;
	g_Player.fPlayerfHeight = PLAYER_HEIGHTINIT;

	// �e�N�X�`���̒��_0�ݒ�
	g_Player.fPlayerTexX0 = PLAYER_TEXVTEXX0;
	g_Player.fPlayerTexY0 = PLAYER_TEXVTEXY0;

	// �e�N�X�`���̒��_1�ݒ�
	g_Player.fPlayerTexX1 = PLAYER_TEXVTEXX1;
	g_Player.fPlayerTexY1 = PLAYER_TEXVTEXY1;
	
	// �v���C���[�̊p�x��ݒ�(���W�A���l)
	g_Player.fPlayerAngle = 0.f;

	// �v���C���[���C�t�̐ݒ�
	g_Player.nPlayerHP = 1;

	// �v���C���[�������Ă��邩
	g_Player.bPlayerAlive = TRUE;

	// �v���C���[�͍U����������
	g_Player.bPlayerAttack = FALSE;

	// �v���C���[�͖h�䂵����
	g_Player.bPlayerDefense = FALSE;

	// �v���C���[�̘A���U��������������
	g_Player.bContinuousAttack = FALSE;

	if( !SoundFileLoad( "sound/Attack.wav" , PLAYER_SOUND ) )
	{
		return ;
	}

	if( !CreateSoundBuffer( &g_SAttack , PLAYER_SOUND ) )
	{
		return ;
	}

	TextureLoad( "photo/5.png" , 20 );

	g_Remain.fPlayerRemainingX0 = 0.f;
	g_Remain.fPlayerRemainingX1 = 1.f;
	g_Remain.fPlayerRemainingY0 = 0.f;
	g_Remain.fPlayerRemainingY1 = 1.f;


}

//=============================================================================
//
// �֐���	: PlayerLeft�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ���Ɉړ�
//
//=============================================================================
void PlayerLeft( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		if( g_Player.fPlayerPosX > 0   )
		{
			// ���Ɉړ�
			BGLeftMove();
		}
	}
}

//=============================================================================
//
// �֐���	: PlayerRight�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �E�Ɉړ�
//
//=============================================================================
void PlayerRight( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		// �E�Ɉړ�
		if( g_Player.fPlayerPosX + g_Player.fPlayerfWidth <  SCREEN_WIDTH )
		{
		//	g_Player.fPlayerPosX += 5.f;
		//	g_Player.fPlayerAngle = 165.f; 
			BGRightMove();
		}
	}
	
}

//=============================================================================
//
// �֐���	: PlayerUp�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ��Ɉړ�
//
//=============================================================================
void PlayerUp( void )
{
	// �v���C���[�������Ă���
	if( g_Player.bPlayerAlive == TRUE )
	{
		// ��ʊO�ɂłĂ��Ȃ����
		if( ScreenOutJudg( g_Player.fPlayerPosX , g_Player.fPlayerPosY ,
					g_Player.fPlayerfWidth , g_Player.fPlayerfHeight ) == UP_OUT )
		{
			// ��Ɉړ�
			g_Player.fPlayerPosY -= 5.f;
		}
		
	}

}

//=============================================================================
//
// �֐���	: PlayerDOWN�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: ���Ɉړ�
//
//=============================================================================
void PlayerDown( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		// ���Ɉړ�
		if( g_Player.fPlayerPosY +  g_Player.fPlayerfHeight / 1.25 < SCREEN_HEIGHT )
		{
			g_Player.fPlayerPosY += 5;
		}
	}
}

//=============================================================================
//
// �֐���	: PlayerAngle�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̍X�V
//
//=============================================================================
void PlayerAngle( void )
{
	if( g_Player.bPlayerAlive == TRUE )
	{
		if( g_Player.fPlayerAngle > 3.1415926534f )
		{
			g_Player.fPlayerAngle -= 3.1415926534f * 2.f;
		}
		else
		{
			g_Player.fPlayerAngle += 2.f;
		}
	}
}

//=============================================================================
//
// �֐���	: PlayerAttack�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̍U��
//
//=============================================================================
void PlayerAttack( void )
{
	// �v���C���[���U�����Ă��Ȃ����
	if( g_Player.bPlayerAlive == TRUE && g_Player.bPlayerAttack == FALSE )
	{
		// ���[�V���������ׂĊ������Ă��Ȃ����
		if( g_Player.fPlayerTexX1 < 1.f  )
		{
			// ���[�V�����ύX
			g_Player.fPlayerTexX0 += PLAYER_TEXVTEXX1;

			// ���[�V�����ύX
			g_Player.fPlayerTexX1 += PLAYER_TEXVTEXX1;

			// �R���{������
			g_Player.bContinuousAttack = TRUE;

			// ���[�V������ύX������
			g_Player.bAttackMotion = TRUE;

		}

		// ���[�V�������ׂĂ������������ꍇ
		else
		{
			// �R���{�����ׂďI������̂ōU���������ƂȂ�
			g_Player.bPlayerAttack = TRUE;
		}
	}


}

//=============================================================================
//
// �֐���	: PlayerDefense�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̖h��
//
//=============================================================================
void PlayerDefense( void )
{
}

//=============================================================================
//
// �֐���	: PlayerUpdate�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �U����̍X�V
//
//=============================================================================
void PlayerUpdate( void )
{
	ENEMY *pEnemy;
	pEnemy = EnemyGet();

	// �����v���C���[�̃R���{���������� ���� �v���C���[���U�������Ă��Ȃ����
	if( g_Player.bContinuousAttack == TRUE )
	{
		// ����2�b�����Ă�����
		if( g_PlayerTimer > ATTACK_CONTINUOUS )
		{
			// �v���C���[�^�C�}�[�����Z�b�g
			g_PlayerTimer = 0;
		}

		// �v���C���[�^�C�}�[��
		g_PlayerTimer++;

		// �Q�[�����Ԃ�2�b��������R���{�������ɖ߂�
		if( g_PlayerTimer == ATTACK_CONTINUOUS )
		{	
			//// �R���{�I��
			g_Player.bContinuousAttack = FALSE;

			// �U��������
			g_Player.bPlayerAttack = TRUE;

			g_PlayerTimer = 0;
		}
	}

	if( g_Player.bPlayerAttack == TRUE )
	{
		// �v���C���[���[�V�������W�������l��
		g_Player.fPlayerTexX0 = PLAYER_TEXVTEXX0;

		// �v���C���[���[�V�������W�������l��
		g_Player.fPlayerTexX1 = PLAYER_TEXVTEXX1;
	}

	/*for( int i = 0; i < ENEMY_MAX; i++ )
	{
		if( HitJudg( g_Player.fPlayerPosX - 20 , g_Player.fPlayerPosY - 20,
			g_Player.fPlayerfWidth - 20, g_Player.fPlayerfHeight ,
			pEnemy[i].fEnemyPosX - 20 , pEnemy[i].fEnemyPosY ,
			pEnemy[i].fEnemyfWidth + 20 , pEnemy[i].fEnemyfHeight - 50) )
		{
			if( g_Player.fPlayerTexX0 == PLAYER_TEXVTEXX0 && g_Player.fPlayerTexX1 == PLAYER_TEXVTEXX1 )
			{
				if( g_Player.bPlayerAlive == TRUE )
				{
					g_Player.bPlayerAlive = FALSE;

					ExplosionPosSet( g_Player.fPlayerPosX , g_Player.fPlayerPosY ,
								g_Player.fPlayerfWidth , g_Player.fPlayerfHeight );
				}
			}
			
		}

	}*/
}

//=============================================================================
//
// �֐���	: PlayerDraw�֐�
//
// �߂�l	: �Ȃ�
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̕`��
//
//=============================================================================
void PlayerDraw( void )
{
	// �����v���C���[���R���{(�U��)���Ă�����
	if( g_Player.bAttackMotion == TRUE )
	{
		g_SAttack->Play( 0 , 0 , 0 );
		g_Player.bAttackMotion = FALSE;
	}

	if( g_Player.bPlayerAlive == TRUE )
	{
		PrimitiveCreate(	PLAYERID					,
							ROTATION					,
							PLAYER_NUM					,
							g_Player.fPlayerAngle		,
							g_Player.fPlayerPosX		, 
							g_Player.fPlayerPosY		,
							g_Player.fPlayerfWidth		,
							g_Player.fPlayerfHeight		,
							g_Player.fPlayerTexX0		,
							g_Player.fPlayerTexY0		,
							g_Player.fPlayerTexX1		,
							g_Player.fPlayerTexY1		);
	}

			PrimitiveCreate(	REMAINID				,
							2							,
							20							,
							0							,
							0							,
							40							,
							60							,
							70							,
							g_Remain.fPlayerRemainingX0		,
							g_Remain.fPlayerRemainingY0		,
							g_Remain.fPlayerRemainingX1		,
							g_Remain.fPlayerRemainingY1		);


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
void PlayerUninit( void )
{
	// �v���C���[�̃e�N�X�`�����
	TextureUninit( PLAYER_NUM );

	TextureUninit( 20 );

	// �T�E���h���
	if( g_SAttack != NULL )
	{
		g_SAttack->Release();
		g_SAttack = NULL;
	}
}

//=============================================================================
//
// �֐���	: PlayerGet�֐�
//
// �߂�l	: PLAYER�\����
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̃Q�b�^�[
//
//=============================================================================
PLAYER* PlayerGet( void )
{
	return &g_Player;
}

//=============================================================================
//
// �֐���	: PlayerSet�֐�
//
// �߂�l	: PLAYER�\����
//
// ����		: �Ȃ�
//
// �@�\		: �v���C���[�̃Q�b�^�[
//
//=============================================================================
void PlayerSet( PLAYER *pPlayer )
{
	// �v���C���[������
	g_Player.bPlayerAlive = pPlayer->bPlayerAlive;

	// �v���C���[�U���\
	g_Player.bPlayerAttack = pPlayer->bPlayerAttack;

	g_Player.bContinuousAttack = pPlayer->bContinuousAttack;
}

PLAYERREMAINING *RemainGet(void)
{
	return &g_Remain;
}

void RemainSet( PLAYERREMAINING *pRemainSet )
{
	g_Remain.fPlayerRemainingX0 = pRemainSet->fPlayerRemainingX0;

	g_Remain.fPlayerRemainingX1 = pRemainSet->fPlayerRemainingX1;
}