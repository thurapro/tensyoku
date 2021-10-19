//=============================================================================
//
// �t�B�[���h���� [Field.cpp]
//
// ���O	: ���� �Y��
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../hedder/Enemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIFE_MAX				(40)	// �G�̃��C�t�ő�l
#define RECUPERATING_CNT_MAX	(60)	// �񕜃J�E���g�ő�l
#define BULLET_ENEMY_SHOT		(40)	// �G���e�����Ԋu

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static	D3DXMATRIX g_mtxWorld;					// ���[���h
static	D3DXVECTOR3 g_posEnemy;					// ���f���̈ʒu
static	D3DXVECTOR3 g_rotEnemy;					// ���f���̌���
static	D3DXVECTOR3 g_sclEnemy;					// ���f���̑傫��
static	LPDIRECT3DTEXTURE9 g_pD3DTextureEnemy = NULL;
static	LPD3DXMESH g_pMeshEnemy = NULL;			// ���b�V���̏��ւ̃|�C���^
static LPD3DXBUFFER g_pD3DMatBuff = NULL;		// �}�e���A�����ւ̃|�C���^
static DWORD g_nNumMat;							// �}�e���A�����̑���
static float g_fEnemyRotX;						// �G�̌���X���W
static float g_fEnemyRotZ;						// �G�̌���Z���W
static int g_nEnemyShot;						// �G���e�������Ă���Ԋu
static float g_fAngleEnemy = D3DXToRadian(0); 
static int g_nEnemyLife;						// �G�̃��C�t
static bool g_bEnemyAlive;						// �����Ă��邩
static int g_nLifeUpCnt;						// ���C�t�񕜃J�E���g

//=============================================================================
//
//	�֐���	: EnemyInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: ���f��������
//
//=============================================================================
HRESULT EnemyInit( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// ���f��������
	g_posEnemy = D3DXVECTOR3(0.0f , 0.0f , 0.0f);		// ���f���̈ʒu
	g_rotEnemy = D3DXVECTOR3(0.0f , 0.0f , 0.0f);		// ���f���̌���
	g_sclEnemy = D3DXVECTOR3(5.0f , 5.0f , 5.0f);	// ���f���̑傫��
	g_nEnemyShot = 0;									// �e�̊Ԋu
	g_nEnemyLife = LIFE_MAX;									// �G�̃��C�t
	g_nLifeUpCnt = 0;
	g_fAngleEnemy = D3DXToRadian(0);
	g_bEnemyAlive = true;								// �G�͐����Ă��邩

	//-------------------------------------------------------------------------
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( "DATA/Model/choco.x" , 
									D3DXMESH_SYSTEMMEM,
									pD3DDevice,
									NULL,
									&g_pD3DMatBuff,
									NULL,
									&g_nNumMat,
									&g_pMeshEnemy) ) )
	{
		return E_FAIL;
	}

	FontInit(pD3DDevice, 30, 20, 0, "Terminal", ENEMY_TYPE);

	ShadowSet(g_posEnemy , ENEMY_TYPE , ENEMY_NUM);
	
	return S_OK;
}

//=============================================================================
//
//	�֐���	: EnemyUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: ���f���j��
//
//=============================================================================
void EnemyUninit( void )
{
	// �����e�N�X�`�����������Ă��Ȃ����
	if(g_pD3DTextureEnemy!= NULL)
	{
		// �e�N�X�`���̉��
		g_pD3DTextureEnemy->Release();

		// �e�N�X�`���̕�����NULL��
		g_pD3DTextureEnemy = NULL;
	}

	if( g_pMeshEnemy != NULL )
	{
		g_pMeshEnemy->Release();		// ���b�V���J��
		g_pMeshEnemy = NULL;
	}
	
	if( g_pD3DMatBuff != NULL )
	{
		g_pD3DMatBuff->Release();		// �}�e���A���o�b�t�@�[�J��
		g_pD3DMatBuff = NULL;
	}

	FontUninit(ENEMY_TYPE);
}

//=============================================================================
//
//	�֐���	: EnemyUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: ���f���X�V
//
//=============================================================================
void EnemyUpdate(void)
{
	D3DXVECTOR3 PlayerPos = PlayerPosGet();
	MESH_WALL *apMeshWall = MeshWallGet();
	BULLET *pBullet = BulletPosGet();
	
	float Vec_XZ = sqrt(((PlayerPos.x - g_posEnemy.x) * (PlayerPos.x - g_posEnemy.x)) + ((PlayerPos.z - g_posEnemy.z) * (PlayerPos.z - g_posEnemy.z)));	// �v���C���[�̋���
	float Vec_X = (PlayerPos.x - g_posEnemy.x) / Vec_XZ;
	float Vec_Z = (PlayerPos.z - g_posEnemy.z) / Vec_XZ;
	float Thita = 0;

	if( g_bEnemyAlive == true )
	{

		if( g_posEnemy.x == PlayerPos.x && g_posEnemy.z == PlayerPos.z )
		{
			GameSelectSet(OVER);
		}
		else
		{
			float Product = (Vec_X * -cosf(g_fAngleEnemy)) + (Vec_Z * -sinf(g_fAngleEnemy));
			Thita = acos(Product);
		}

		float Cross = (Vec_Z * -sinf(g_fAngleEnemy)) - (Vec_X * -cosf(g_fAngleEnemy));
		if(Cross > 0 )
		{
			if(Thita >= D3DXToRadian(2))
			{
				g_fAngleEnemy -= D3DXToRadian(2);
			}
			else
			{
				g_fAngleEnemy -= Thita;
			}
		}
		if( Cross < 0 )
		{
			if(Thita >= D3DXToRadian(2))
			{
				g_fAngleEnemy += D3DXToRadian(2);
			}
			else
			{
				g_fAngleEnemy += Thita;
			}
		}
		g_rotEnemy.y = g_fAngleEnemy;

		g_posEnemy.x -= sin(g_rotEnemy.y);
		g_posEnemy.z -= cos(g_rotEnemy.y);

		if( g_nEnemyShot > BULLET_ENEMY_SHOT )
		{
			BulletSet( g_posEnemy , g_rotEnemy.y , ENEMY_TYPE);
			g_nEnemyShot = 0;
		}
		else
		{
			g_nEnemyShot++;
		}
		if(g_nLifeUpCnt > RECUPERATING_CNT_MAX)
		{
			if(g_nEnemyLife < LIFE_MAX)
			{
				g_nEnemyLife++;
			}
			g_nLifeUpCnt = 0;
		}
		else
		{
			g_nLifeUpCnt++;
		}
		ShadowUpdate(g_posEnemy, 30, ENEMY_TYPE);

		for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
		{
			if( pBullet[nCntBullet].visible == true )
			{
				if( pBullet[nCntBullet].nType == PLAYER_TYPE )
				{
					if( pBullet[nCntBullet].posBullet.x < (g_posEnemy.x + 20)  &&
						g_posEnemy.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
						pBullet[nCntBullet].posBullet.z < ( g_posEnemy.z + 20 ) &&
						g_posEnemy.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight))
					{
						pBullet[nCntBullet].visible = false;
						pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
						pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
						ExplosionSet( pBullet[nCntBullet].MemoryPos);
						ShadowDelete( BULLET_TYPE , nCntBullet);
						ExplosionSet(g_posEnemy);
					}
				}
			}
		}
	}
	else
	{
		GameSelectSet(CLEAR);
	}

}

//=============================================================================
//
//	�֐���	: EnemyDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: ���f���`��
//
//=============================================================================
void EnemyDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxScl ;			// �傫���̐ݒ�
	D3DXMATRIX mtxRot ;			// �����̐ݒ�
	D3DXMATRIX mtxTrans;		
	D3DXMATERIAL *pD3DMat;		// �}�e���A���ݒ�
	char strLife[20];			// ���C�t�����^

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity( &g_mtxWorld );		// ���[���h�}�g���b�N�X������

	//*********************************
	// �X�P�[�����f
	D3DXMatrixScaling( &mtxScl , g_sclEnemy.x, g_sclEnemy.y , g_sclEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
	
	//*********************************
	// ��]���f
	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotEnemy.y , g_rotEnemy.x , g_rotEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

	//*********************************
	// �ړ����f
	D3DXMatrixTranslation( &mtxTrans , g_posEnemy.x , g_posEnemy.y , g_posEnemy.z );
	D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

	//-------------------------------------------------------------------------
	// ���[���h�}�g���b�N�X�ݒ�
	pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );	

	//-------------------------------------------------------------------------
	// ���f���ݒ�
	pD3DMat = ( D3DXMATERIAL * )g_pD3DMatBuff->GetBufferPointer();

	for( int nCntMat = 0; nCntMat < (int)g_nNumMat; nCntMat++ )
	{
		pD3DDevice->SetMaterial( &pD3DMat[nCntMat].MatD3D );
		pD3DDevice->SetTexture( 0 , g_pD3DTextureEnemy );
		g_pMeshEnemy->DrawSubset( nCntMat );
	}
	
	char g_strLifeBuffe[1024] = "�G�̃��C�t : ";		// �G�̃��C�t�̕�����
	itoa(g_nEnemyLife, strLife , 10);
	
	strcat( g_strLifeBuffe , strLife );
	FontDraw(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, 255, 255, 255, g_strLifeBuffe, ENEMY_TYPE);
	
}

//=============================================================================
//
//	�֐���	: EnemyPosGet
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: ���f���ʒu�擾
//
//=============================================================================
D3DXVECTOR3 EnemyPosGet( void )
{
	return g_posEnemy;
}

void EnemyLifeSet(int nLife)
{	
	g_nEnemyLife -= nLife;
	if( g_nEnemyLife < 1 )
	{
		GameSelectSet(CLEAR);
	}
}


int EnemyLifeGet(void)
{
	return g_nEnemyLife;
}