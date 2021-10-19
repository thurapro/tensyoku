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
#include "../hedder/Player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_LIFE_MAX (10)
#define VISIBLECNT_MAX	(20)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
static	D3DXMATRIX g_mtxWorld;						// ���[���h
static	D3DXVECTOR3 g_posPlayer;					// �v���C���[�̈ʒu
static	D3DXVECTOR3 g_rotPlayer;					// �v���C���[�̌���
static	D3DXVECTOR3 g_sclPlayer;					// �v���C���[�̑傫��
static	D3DXVECTOR3 g_rotArrow;						// �����Ă��Ȃ���΂Ȃ�Ȃ��ʒu
static	D3DXVECTOR3 g_movePlayer;					// �v���C���[�̓������x
static	LPDIRECT3DTEXTURE9 g_pD3DTexturePlayer = NULL; 
static	LPD3DXMESH g_pMeshPlayer = NULL;			// ���b�V���̏��ւ̃|�C���^
static	LPD3DXBUFFER g_pD3DMatBuff = NULL;			// �}�e���A�����ւ̃|�C���^
static	DWORD g_nNumMat;							// �}�e���A�����̑���
static	float g_rotMove = D3DX_PI / 180;			// ������ς��鑬�x
static	float g_fPlayerX = 0;						// �v���C���[�̌��݂̌���X
static	float g_fPlayerZ = 0;						// �v���C���[�̌��݂̌���Z
static bool g_bVisible = true;						// �v���C���[��\�����邩�H 
static int g_nPlayerLife;							// �v���C���[�̗̑�
static int g_nVisibleCount = 0;						// �v���C���[����������ɂ܂��\�����邽�߂̎���
static LPDIRECTSOUNDBUFFER g_soundStart;			// �T�E���h

//=============================================================================
//
//	�֐���	: PlayerInit
//	
//	�߂�l	: �������ł���������
//
//	����	: �f�o�C�X
//
//	�@�\	: �v���C���[������
//
//=============================================================================
HRESULT PlayerInit( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//-------------------------------------------------------------------------
	// �v���C���[������
	g_posPlayer = D3DXVECTOR3(0.0f, 0.0f, -300.0f);			// �v���C���[�̈ʒu
	g_rotPlayer = D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f);	// �v���C���[�̌���
	g_sclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// �v���C���[�̑傫��
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �v���C���[�̑��x
	g_rotMove = D3DX_PI / 180;								// �v���C���[�̌�������
	g_rotArrow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���Ɍ����x�N�g��	
	g_fPlayerX = 0;											// �v���C���[�̌��݂̌�������
	g_fPlayerZ = 0;											// �v���C���[�̌��݂̌���
	g_nPlayerLife = PLAYER_LIFE_MAX;						// �v���C���[�̗̑�
	g_soundStart;											// �T�E���h
	g_nVisibleCount = 0;									// �v���C���[��\�����邽�߂̎���
	g_bVisible = true;										// �v���C���[��\�����邩�����߂� true/�\��, false/��\�� 

	//-------------------------------------------------------------------------
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( "DATA/Model/tank.x" , 
									D3DXMESH_SYSTEMMEM,
									pD3DDevice,
									NULL,
									&g_pD3DMatBuff,
									NULL,
									&g_nNumMat,
									&g_pMeshPlayer) ) )
	{
		return E_FAIL;
	}
	
	//--------------------------------------------------
	// ���y�t�@�C�����[�h�@& ����
	SoundFileLoad("DATA/Sound/Start.wav", PLAYER_STOP);
	CreateSoundBuffer( &g_soundStart, PLAYER_STOP);

	FontInit(pD3DDevice, 20, 20, 0, "Terminal", PLAYER_TYPE);


	//---------------------------------------------------
	// �e���Z�b�g
	ShadowSet(g_posPlayer, PLAYER_TYPE , 0);

	return S_OK;
}

//=============================================================================
//
//	�֐���	: PlayerUninit
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C���[�j��
//
//=============================================================================
void PlayerUninit( void )
{
	
	if(g_pD3DTexturePlayer!= NULL)
	{
		// �����e�N�X�`�����������Ă��Ȃ����
		g_pD3DTexturePlayer->Release();		// �e�N�X�`���̉��
		g_pD3DTexturePlayer = NULL;			// �J�����ꂽ��������NULL������
	}

	if( g_pMeshPlayer != NULL )
	{
		// ���b�V�����J������Ă��Ȃ����
		g_pMeshPlayer->Release();			// ���b�V���J��
		g_pMeshPlayer = NULL;				// �J�����ꂽ��������NULL������
	}
	
	if( g_pD3DMatBuff != NULL )
	{
		// �}�e���A���o�b�t�@�[���J������Ă��Ȃ����
		g_pD3DMatBuff->Release();			// �}�e���A���o�b�t�@�[�J��
		g_pD3DMatBuff = NULL;				// �J�����ꂽ��������NULL������
	}
	if(g_soundStart != NULL)
	{
		// �T�E���h���J������Ă��Ȃ����
		g_soundStart->Release();			// �T�E���h���J��
		g_soundStart = NULL;				// �J�����ꂽ��������NULL������
	}

	FontUninit(PLAYER_TYPE);
}

//=============================================================================
//
//	�֐���	: PlayerUpdate
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C���[�X�V
//
//=============================================================================
void PlayerUpdate(void)
{
	
	MESH_WALL *aMeshWall = MeshWallGet();				// �ǂ̈ʒu���擾
	BULLET *pBullet = BulletPosGet();					// �e���擾
	bool bStop = GameStop();							// �|�[�Y�{�^���������ꂽ���擾
	PlayerStop(bStop);									// �|�[�Y��������Ă̂����Z�b�g

	if(g_nPlayerLife >= 0)
	{
		// �v���C���[�̗̑͂��Ȃ��Ȃ��Ă��ȏ��
		if(g_bVisible == false)
		{
			// �v���C���[���\������Ă��Ȃ����
			if(g_nVisibleCount > VISIBLECNT_MAX)
			{
				// �\�����邽�߂̎��Ԃ𒴂��Ă�����
				g_bVisible = true;						// �v���C���[��\��
				g_nVisibleCount = 0;					// �^�C�}�[�����Z�b�g
			}
			else
			{
				// �\�����邽�߂̎��ԂɒB���Ă��Ȃ����
				g_nVisibleCount++;						// �\�����邽�߂ɃJ�E���g���グ��
			}
		}
		else
		{
			// �v���C���[���\������Ă�����
			g_fPlayerX = -sin( g_rotPlayer.y );			// �v���C���[�̌����Ă���������Z�b�g
			g_fPlayerZ = -cos( g_rotPlayer.y );			// �v���C���[�̌����Ă���������Z�b�g

			g_movePlayer.x = 4 * sin( g_rotPlayer.y );	// �v���C���[�̈ړ����x
			g_movePlayer.z = 4 * cos( g_rotPlayer.y );	// �v���C���[�̈ړ����x

			//---------------------------------
			// �E�ړ�
			if( KeyState( DIK_D ) )
			{
				g_rotArrow.x = D3DX_PI * 0.5f;
				g_rotArrow.x = sinf(g_rotArrow.x);
				g_rotArrow.z = 0.0f;

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				if( Cross > 0 )
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.x + 13 < aMeshWall[1].pos.x)
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}
			//---------------------------------
			// ���ړ�
			else if( KeyState( DIK_A ) )
			{
				g_rotArrow.x = -D3DX_PI * 0.5f;
				g_rotArrow.x = sinf(g_rotArrow.x);
				g_rotArrow.z = 0.0f;
				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}
				float Cross = (g_rotArrow.z * g_fPlayerX) - ( g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				if( Cross > 0 )
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.x - 13 > aMeshWall[2].pos.x )
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z += g_movePlayer.z;
				}
			}
			//---------------------------------
			// ���ړ�
			else if( KeyState( DIK_W ) )
			{
				g_rotArrow.x = 0.0f;
				g_rotArrow.z = 0.0f;
				g_rotArrow.z = cosf(g_rotArrow.z);

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				else if( Cross > 0)
				{
					g_rotPlayer.y -= Thita;
				}

				if(g_posPlayer.z + 13 < aMeshWall[0].pos.z)
				{
					g_posPlayer.x -= g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}

			//---------------------------------
			// ��O�ړ�
			else if( KeyState( DIK_S ) )
			{	
				g_rotArrow.x = 0;
				g_rotArrow.z = D3DX_PI * 1.0f;
				g_rotArrow.z = cosf(g_rotArrow.z);

				float Product = (g_fPlayerX * g_rotArrow.x) + (g_fPlayerZ * g_rotArrow.z);
				float Thita = acos(Product);
				if(Thita > 1.0f )
				{
					Thita = 1.0f;
				}
				else if(Thita < -1.0f)
				{
					Thita = -1.0f;
				}

				float Cross = (g_rotArrow.z * g_fPlayerX) - (g_rotArrow.x * g_fPlayerZ);
				if( Cross < 0 )
				{
					g_rotPlayer.y += Thita;
				}
				else if( Cross > 0)
				{
					g_rotPlayer.y -= Thita;
				}
				
				if( g_posPlayer.z - 13 > aMeshWall[3].pos.z )
				{
					g_posPlayer.x += g_movePlayer.x;
					g_posPlayer.z -= g_movePlayer.z;
				}
			}

			//---------------------------------
			// �e����
			if( KeyPush( DIK_SPACE ) )
			{
				BulletSet( g_posPlayer, g_rotPlayer.y , PLAYER_TYPE);
			}

			ShadowUpdate(g_posPlayer, 0 , PLAYER_TYPE);
			
			for( int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
			{
				if(pBullet[nCntBullet].visible == true )
				{
					if( pBullet[nCntBullet].nType != PLAYER_TYPE )
					{
						if( pBullet[nCntBullet].posBullet.x < (g_posPlayer.x + 20)&&
							g_posPlayer.x < (pBullet[nCntBullet].posBullet.x + pBullet[nCntBullet].fWidth) &&
							pBullet[nCntBullet].posBullet.z < (g_posPlayer.z + 20)&&
							g_posPlayer.z < (pBullet[nCntBullet].posBullet.z + pBullet[nCntBullet].fHeight))
						{
							pBullet[nCntBullet].visible = false;
							pBullet[nCntBullet].MemoryPos = pBullet[nCntBullet].posBullet;
							pBullet[nCntBullet].posBullet = D3DXVECTOR3( 0, 0, 0 );
							ExplosionSet( pBullet[nCntBullet].MemoryPos);
							ShadowDelete( BULLET_TYPE , nCntBullet);
							g_bVisible = false;			// �v���C���[���\���ɂ���
							//g_nPlayerLife--;			// �̗͂��ւ炷
						}// �e���������Ă��邩��if�𔲂��� 
					}// �e�������̒e����if�𔲂���
				}// �e���\������Ă��邩��if�𔲂���
			}// �e�̔����for�𔲂���
		}// �v���C���[���\������Ă��邩��if�𔲂���
	}
	else
	{
		// �����̗͂��Ȃ����
		GameSelectSet(OVER);		// �Q�[���I�[�o�[�Ɉړ�
	}
}

//=============================================================================
//
//	�֐���	: PlayerDraw
//	
//	�߂�l	: �Ȃ�
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C���[�`��
//
//=============================================================================
void PlayerDraw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	//---------------------------------
	// �ϐ��錾
	D3DXMATRIX mtxScl ;			// �傫���̐ݒ�
	D3DXMATRIX mtxRot ;			// �����̐ݒ�
	D3DXMATRIX mtxTrans;		
	D3DXMATERIAL *pD3DMat;		// �}�e���A���ݒ�
	char strPlayer[1024] = "�v���C���[�̃��C�t : ";
	char strLife[10];
	char srtStopMsg[50] = "STOP";
	bool bStop = GameStop();

	if(g_bVisible == true)
	{
		//-------------------------------------------------------------------------
		// ���[���h�}�g���b�N�X
		D3DXMatrixIdentity( &g_mtxWorld );		// ���[���h�}�g���b�N�X������

		//*********************************
		// �X�P�[�����f
		D3DXMatrixScaling( &mtxScl , g_sclPlayer.x, g_sclPlayer.y , g_sclPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxScl );
		
		//*********************************
		// ��]���f
		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_rotPlayer.y , g_rotPlayer.x , g_rotPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxRot );

		//*********************************
		// �ړ����f
		D3DXMatrixTranslation( &mtxTrans , g_posPlayer.x , g_posPlayer.y , g_posPlayer.z );
		D3DXMatrixMultiply( &g_mtxWorld , &g_mtxWorld , &mtxTrans );

		//-------------------------------------------------------------------------
		// ���[���h�}�g���b�N�X�ݒ�
		pD3DDevice->SetTransform( D3DTS_WORLD , &g_mtxWorld );	

		//-------------------------------------------------------------------------
		// �v���C���[�ݒ�
		pD3DMat = ( D3DXMATERIAL * )g_pD3DMatBuff->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < (int)g_nNumMat; nCntMat++ )
		{
			pD3DDevice->SetMaterial( &pD3DMat[nCntMat].MatD3D );
			pD3DDevice->SetTexture( 0 , g_pD3DTexturePlayer );
			g_pMeshPlayer->DrawSubset( nCntMat );
		}
	}
		
	itoa( g_nPlayerLife, strLife, 10);
	strcat(strPlayer , strLife);
	FontDraw(20 , 300, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 255, 255, 255, strPlayer, PLAYER_TYPE);
	
	/*if( bStop == true )
	{
		FontDraw(280 , 190, SCREEN_WIDTH, SCREEN_HEIGHT, srtStopMsg);
	}*/
}

//=============================================================================
//
//	�֐���	: PlayerPosGet
//	
//	�߂�l	: �v���C���[�̈ʒu
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C���[�ʒu�擾
//
//=============================================================================
D3DXVECTOR3 PlayerPosGet( void )
{
	return g_posPlayer;
}

//=============================================================================
//
//	�֐���	: PlayerRosGet
//	
//	�߂�l	: �v���C���[�̌���
//
//	����	: �Ȃ�
//
//	�@�\	: �v���C���[�����擾
//
//=============================================================================
D3DXVECTOR3 PlayerRotGet(void)
{
	return g_rotPlayer;
}

bool PlayerStop(bool bStop)
{
	if( KeyPush(DIK_RETURN))
	{
		g_soundStart->Play(0,0,0);
		if( bStop == false )
		{
			bStop = true;
		}
		else
		{
			bStop = false;
		}
	}
	return bStop;
}

