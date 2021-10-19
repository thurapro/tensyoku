//=============================================================================
//
// FAILE NAME [Judgment.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: �Q�[�����̔���
//
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Judgment.h"
#include "../hedder/InputKey.h"
#include "../hedder/Texture.h"
#include "../hedder/Player.h"
#include "../hedder/Enemy.h"
#include "../hedder/common.h"
#include "../hedder/BG.h"
#include "../hedder/WinMain.h"
#include "../hedder/Title.h"
#include "../hedder/Game.h"
#include "../hedder/Clear.h"
#include "../hedder/Over.h"
#include <d3d9.h>
#include <windows.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static int g_AliveTimer	= 0;				// �����̃^�C�}�[
static int g_PlayerTurnTimer = 0;			// �v���C���[�d���^�C�}�[�I��
static int g_EnemyTurnTimer	= 0;			// �G�̍d���^�C�}�[�I��	


//=============================================================================
// �����蔻��
//=============================================================================
BOOL HitJudg(	float fax , float fay , float faw , float fah , 
				float fbx , float fby , float fbw , float fbh )
{
	if( fax < ( fbx + fbw ) &&
		fbx < ( fax + faw ) &&
		fay < ( fby + fbh ) && 
		fby < ( fay + fah ) )
	{
		return TRUE;
	}
	return FALSE;
}


//=============================================================================
// ���c����
//=============================================================================
void PlayerControlJudg( void )
{
	int Select = GameSelectGet();

	switch( Select )
	{
	case TITLE :
		if( KeyPush( DIK_G ) )
		{
			GameSelectSet( GAME );
			TitleUninit();
		}
		break;

	case GAME :

		// �����E����������
		if( KeyState( DIK_RIGHT ) )
		{
			// �E�Ɉړ��֐�
			EnemyLeft();
			BGLeftMove();
		}

		// ����������������
		//if( KeyState( DIK_LEFT ) )
		//{
		//	// ���Ɉړ��֐�
		//	EnemyRight();
		//	BGRightMove();
		//}

		// ���������������
		if( KeyState( DIK_UP ) )
		{
			// ��Ɉړ��֐�
			PlayerUp();
		}

		// ����������������
		if( KeyState( DIK_DOWN ) )
		{
			// ���Ɉړ��֐�
			PlayerDown();
		}

		// ����A����������
		if( KeyPush( DIK_F ) )
		{
			// �U���֐�
			PlayerAttack();
		}

		// ����S����������
		if( KeyState( DIK_S ) )
		{
			// �h��֐�
			PlayerDefense();
		}

		// ����H����������
		if( KeyState( DIK_H ) )
		{
			// ��]�֐�
			PlayerAngle();
		}
		break;

	case CLEAR :
		if( KeyPush( DIK_D ) )
		{
			GameSelectSet( INIT );
			ClearUninit();
		}
		break;

	case OVER :
		if( KeyPush( DIK_D) )
		{
			GameSelectSet( INIT );
			OverUninit();
		}
 
	default :
		break;
	}
}

//=============================================================================
// ��������
//=============================================================================
void RebornJudg( void )
{
	// �|�C���^�[�錾
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	// �v���C���[���\���̂������Ă���
	pPlayer = PlayerGet();

	// �G�̍\���̂������Ă���
	pEnemy = EnemyGet();
	
	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// �����ǂ��炩���퓬�s�\��
		if( pPlayer->bPlayerAlive == FALSE 
			|| pEnemy[i].bEnemyAlive == FALSE ) 
		{
			// �^�C�}�[�N��
			g_AliveTimer++;

			// �^�C�}�[��3�b�o�߂����Ƃ��ɕ���
			if( g_AliveTimer == ALIVE_TIMEWATE )
			{
				// �����v���C���[���퓬�s�\�ȏꍇ
				if( pPlayer->bPlayerAlive == FALSE )
				{
					pPlayer->bPlayerAlive = TRUE;
					PlayerSet( pPlayer );
				}
				
				// �^�C�}�[�̃��Z�b�g
				g_AliveTimer = 0;
			}

			if( pEnemy[i].nEnemyWate == ALIVE_TIMEWATE )
			{
				// �����G���퓬�s�\�Ȃ�
				if( pEnemy[i].bEnemyAlive == FALSE )
				{
					EnemySet( pEnemy );
				}
				pEnemy[i].nEnemyWate = 0;
			}
			
			// �G�̕����J�E���g
			pEnemy[i].nEnemyWate++;
		}
	}
}

//=============================================================================
// �^�[���֐�
//=============================================================================
void TurnJudg( void )
{
	// �|�C���^�[�ϐ�
	PLAYER	*pPlayer;
	ENEMY	*pEnemy;

	// �v���C���[���\���̂������Ă���
	pPlayer = PlayerGet();

	// �G�̍\���̂������Ă���
	pEnemy = EnemyGet();

	// �����ǂ��炩������U��������
	if( pPlayer->bPlayerAttack == TRUE )
	{
		// 2�b�ԍU���ł��Ȃ�
		if( g_PlayerTurnTimer == TURN_TIMEWATE )
		{
			// �����v���C���[���U�����s������
			if( pPlayer->bPlayerAttack == TRUE )
			{
				// �v���C���[�͍U���\�ɂȂ�
				pPlayer->bPlayerAttack = FALSE;
				PlayerSet( pPlayer );		
			}
			g_PlayerTurnTimer = 0;
		}
		g_PlayerTurnTimer++;
	}

	for( int i = 0; i < ENEMY_MAX; i++ )
	{
		// �����G���U�����s������
		if( pEnemy[i].bEnemyAttack == TRUE )
		{
			if( g_EnemyTurnTimer == TURN_TIMEWATE )
			{
				// �G�͍U���\�ƂȂ�
				pEnemy[i].bEnemyAttack = FALSE;
				EnemySet( pEnemy );

				g_EnemyTurnTimer = 0;
			}
			g_EnemyTurnTimer++;
		}
	}
		
}

//=============================================================================
// ��ʊO�ɂł�������
//=============================================================================
int ScreenOutJudg( float fX , float fY , float fWidth , float  fHeight)
{
	// �������ɏo����
	if( fX < 0 )
	{
		return LEFT_OUT;
	}

	// �����E�ɏo����
	if( fX + fWidth > SCREEN_WIDTH )
	{
		return RIGHT_OUT;
	}
	
	// ������ɏo����
	if( fY > PLAYER_POSY_INIT )
	{
		return UP_OUT;
	}

	// �������ɏo����
	if( fY + fHeight / 1.25 < SCREEN_HEIGHT )
	{
		return DOWN_OUT;
	}

	return NO_OUT;
}
