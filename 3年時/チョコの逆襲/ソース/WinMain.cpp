//=============================================================================
//
// ���C������[WinMain.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: ���C��
//
//=============================================================================
#include <windows.h>

#include "../hedder/WinMain.h"

#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// ���R�ɐݒ�ł��钸�_�t�H�[�}�b�g
#define VERTEX_MAX		( 30 )				// ���_�o�b�t�@�ݒ�e��
#define VTEXMAX			( 6 )				// ���_�̍ő吔
#define RED_MAX			( 255 )				// �ԐF�̍ő�F
#define GREEN_MAX		( 255 )				// �ΐF�̍ő�F
#define BLUE_MAX		( 255 )				// �F�̍ő�F
#define ALPHA_MAX		( 255 )				// �����x�̍ő�

static int	g_nSelect = TITLE;				// �Q�[���J��
static bool g_bStop = false;				// �Q�[�����~�߂�
static int g_nGameTime;						// �Q�[���^�C��

//============================================================================
//
// �֐���	:	WinMain�֐�
//
// �߂�l	:	int
//
// ����		:	h�C���X�^���X , �v���u�C���X�^���X
//
// �@�\		:	
//			
//
//============================================================================
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	//---------------------------------
	// �ϐ��錾
	HWND hWnd;							// �E�B���h�Ɋւ���
	MSG msg;							// ���b�Z�[�W�Ɋւ���
	HRESULT hr = NULL;					// ���ʕϐ�
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�Ɋւ���
	LPDIRECT3D9 pD3D = NULL;			// Direct3D�I�u�W�F�N�g

	//-------------------------------------------------------------------------
	// �E�B���h�N���X
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//-------------------------------------------------------------------------
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//-------------------------------------------------------------------------
	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	//-------------------------------------------------------------------------
	// DirectX�̏�����
	pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	// �f�o�C�X�쐬���s
	if(NULL == pD3D)
	{
		return -1;
	}

	// ���݂̃f�B�X�v���C���[�h�擾
	D3DDISPLAYMODE d3ddm;	
	hr = pD3D->GetAdapterDisplayMode( 
	D3DADAPTER_DEFAULT,&d3ddm);
	if( FAILED( hr ) )
	{
		return -1;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp , sizeof(d3dpp) );

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(TRUE == d3dpp.Windowed)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// �f�o�C�X����
	struct
	{
		D3DDEVTYPE	DevType;
		DWORD		BehaviorFlags;
	} 
	DevTypes[] = {
		{ D3DDEVTYPE_HAL , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_HAL , D3DCREATE_SOFTWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_HARDWARE_VERTEXPROCESSING } ,
		{ D3DDEVTYPE_REF , D3DCREATE_SOFTWARE_VERTEXPROCESSING }
	};

	D3DDEVTYPE	DevType;
	DWORD		BehaviorFlags;
	BOOL		bCreateDevice;
	int			i;
	bCreateDevice = FALSE;

	for( i = 0; i < _countof(DevTypes); i++)
	{
		DevType	= DevTypes[i].DevType;
		BehaviorFlags = DevTypes[i].BehaviorFlags;
		hr = pD3D->CreateDevice(
		D3DADAPTER_DEFAULT ,
		DevType ,
		hWnd ,
		BehaviorFlags ,
		&d3dpp,
		&pDevice);

		if(SUCCEEDED( hr ) )
		{
			bCreateDevice = TRUE;
			break;
		}
	}
	if( FALSE == bCreateDevice )
	{
		return FALSE;
	}
	//----------------------------------------------------------------------------
	// �����_�����O�X�e�[�g�̏������ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE ,D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);				// 
	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);						// 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE , TRUE);				//
	pDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);		//
	pDevice->SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);	//
	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);				//
	//-------------------------------------------------------------------------
	// �T���v���[�X�e�[�g�̏������ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	 //------------------------------------------------------------------------
	 // �L�[������
	if( !InitInput( hInstance , hWnd ) )
	{
		// ���������s
		return -1;
	}

	if( !SoundInit(hWnd) )
	{
		return -1;
	}

	if( !CreatePrimaryBuff() ) 
	{
		return -1;
	}

	//-------------------------------------------------------------------------
	// �E�B���h�E�\��
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	//---------------------------------
	// �ϐ��錾
	BOOL bFPS = FALSE;		// FPS�Œ�
	int nFrameCount = 0;	// �v���C���J�E���g

	bool bTitleInit = false;	// �^�C�g�����������������H
	bool bGameInit = false;		// �Q�[�����������������H
	bool bClearInit = false;	// �N���A��������������?
	bool bOverInit= false;		// �I�[�o�[��������������?
	bool bExplainInit = false;
	bool bLankInit = false;
	g_bStop = false;
	int nTimeCnt = 0;

	//-------------------------------------------------------------------------
	// ���C�����[�v
	while(1)
	{
		//---------------------------------------------------------------------
		// �t���[���J�E���g
		bFPS = FPSFixing();

		//---------------------------------------------------------------------
		// ���b�Z�[�W��`���H
		if( PeekMessage(&msg , NULL , 0 , 0 ,PM_REMOVE) )
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{		
			if( bFPS == TRUE )
			{
				//-------------------------------------------------------------
				// ���͍X�V
				UpdateInput();
				switch(g_nSelect)
				{
				case TITLE:
					//---------------------------------
					// �^�C�g��������������Ă��Ȃ����
					if(bTitleInit == false)
					{
						InitTitle(pDevice);			// �^�C�g���̏�����
						bGameInit = false;			// �Q�[���t���O�̏�����
						bClearInit = false;			// �N���A�t���O�̏�����
						bOverInit = false;			// �I�[�o�[�t���O�̏�����
						bTitleInit = true;			// �^�C�g���������I��
					}
					else
					{
						UpdateTitle();				// �^�C�g���X�V
						//---------------------
						// �^�C�g������Ȃ�������
						if(g_nSelect != TITLE)
						{
							UninitTitle();
							g_nSelect = EXPLAIN;
							bTitleInit = false;
						}
					}
					break;

				case EXPLAIN:
					if( bExplainInit == false )
					{
						InitExplain(pDevice);
						bExplainInit = true;
					}
					else
					{
						UpdateExplain();
						if( g_nSelect != EXPLAIN)
						{
							UninitExplain();
							bExplainInit = false;
						}
					}
					break;

				case GAME:
					LPDIRECTSOUNDBUFFER soundGame;
					//-------------------------------
					// �Q�[������������Ă��Ȃ����
					if(bGameInit == false)
					{
						g_nGameTime = 0;
						SoundFileLoad("DATA/Sound/Game.wav", GAME);
						CreateSoundBuffer(&soundGame, GAME);
						CameraInit();								// �J�����̏�����
						LightInit(pDevice);							// ���C�g�̏�����
						FieldInit(pDevice, 100, 100, 10, 10);		// �n�ʂ̏�����
						MeshWallInit(pDevice, 100, 100, 10, 10);	// �ǂ̏�����
						BulletInit(pDevice, 50, 50);			// �e�̏�����
						ShadowInit(pDevice, 25, 25);				// �e�̏�����
						PlayerInit(pDevice);						// �v���C���[������
						EnemyInit(pDevice);							// �G�̏�����
						EnemyLifeInit(pDevice);
						ExplosionInit(pDevice, 25, 25);				// �����̏�����
						EffectInit(pDevice, 25, 25);				// �G�t�F�N�g�̏�����
						bTitleInit = false;							// �^�C�g���t���O������
						bClearInit = false;							// �N���A�t���O������
						bOverInit = false;							// �I�[�o�[�t���O������
						bGameInit = true;							// �Q�[���������I��
					}
					else
					{
						if( nTimeCnt > 60)
						{
							g_nGameTime++;
							nTimeCnt = 0;
						}
						else
						{
							nTimeCnt++;
						}
						soundGame->Play(0,0,0);
						g_bStop = PlayerStop(g_bStop);
						CameraUpdate();								// �J�����̍X�V
						if( g_bStop == false )
						{
							PlayerUpdate();							// �v���C���[�̍X�V
							EnemyUpdate();							// �G�̍X�V
							EnemyLifeUpdate();
							BulletUpdate();							// �e�̍X�V
				   			ExplosionUpdate();						// �����̍X�V
							EffectUpdate();							// �G�t�F�N�g�̍X�V
						}
						//--------------------------
						// �Q�[����ʂ���Ȃ�������
						if(g_nSelect != GAME)
						{
     						FieldUninit();							// �n�ʔj��			
							PlayerUninit();							// �v���C���[�j��
							EnemyUninit();							// �G�j��
							EnemyLifeUninit();
							MeshWallUninit();						// �ǔj��
							BulletUninit();							// �e�j��
							ShadowUninit();							// �e�j��
							ExplosionUninit();						// �����j��
							EffectUninit();							// �G�t�F�N�g�j��
							if(soundGame != NULL)
							{
								soundGame->Release();
								soundGame = NULL;
							}
							bGameInit = false;
						}
					}
					break;
				case CLEAR:
					//---------------------------------
					// �N���A������������Ă��Ȃ�������
					if(bClearInit == false)
					{
						InitClear(pDevice);
						bTitleInit = false;							// �^�C�g���t���O������
						bOverInit = false;							// �I�[�o�[�t���O������
						bGameInit = false;							// �Q�[���t���O������
						bClearInit = true;							// �N���A�������I��
					}
					else
					{
						UpdateClear();								// �N���A�X�V
						//------------------------
						// �N���A����Ȃ�������
						if(g_nSelect != CLEAR)
						{
							UninitClear();
							bClearInit = false;
						}
					}
					break;
				case OVER:
					if(bOverInit == false)
					{
						InitOver(pDevice);
						bOverInit = true;
					}
					else
					{
						UpdateOver();
						if(g_nSelect != OVER)
						{
							UninitOver();
							bOverInit = false;
						}
					}
					break;

				case LANK:
					if( bLankInit == false )
					{
						InitLank(pDevice);
						bLankInit = true;
					}
					else
					{
						UpdateLank();
						if(g_nSelect != LANK)
						{
							UninitLank();
							bLankInit = false;
						}
					}
					break;
				default:
					continue;										// ������x��蒼��
				}

				//-------------------------------------------------------------
				// �o�b�N�o�b�t�@�̃N���A
				pDevice->Clear
					( 0 , NULL ,
					 (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER) ,
					 D3DCOLOR_RGBA( 255 , 255 , 255 , 255) ,
					 1.0f, 0);			

				//-------------------------------------------------------------
				// �`��J�n
				hr = pDevice->BeginScene();

				//---------------------------------------------------------
				// �����ɕ`�揈��
				if( SUCCEEDED(hr) )
				{
					switch(g_nSelect)
					{
					case TITLE:
						//-----------------------------------
						// �^�C�g��������������Ă�����
						if(bTitleInit == true)
						{
							DrawTitle(pDevice);					// �^�C�g���`��
						}
						break;
					case EXPLAIN:
						if( bExplainInit == true )
						{
							DrawExplain(pDevice);
						}
						break;
					case GAME:
						DrawExplain(pDevice);
						//------------------------------------
						// �Q�[��������������Ă�����
						if(bGameInit == true)
						{
							CameraDraw(pDevice);			// �J�����`��
							FieldDraw(pDevice);				// �n�ʕ`��
							PlayerDraw(pDevice);			// �v���C���[�`��
							EnemyDraw(pDevice);				// �G�̕`��
							EnemyLifeDraw(pDevice);
							MeshWallDraw(pDevice);			// �ǂ̕`��
							BulletDraw(pDevice);			// �e�̕`��
							ShadowDraw(pDevice);			// �e�̕`��
							EffectDraw(pDevice);			// �G�t�F�N�g�`��
							ExplosionDraw(pDevice);			// �����`��
						}			
						break;
					case CLEAR:
						//-------------------------------------
						// �N���A������������Ă�����
						if(bClearInit == true)
						{
							DrawClear(pDevice);					// �N���A�`��
						}
						break;
					case OVER:
						if(bOverInit == true)
						{
							DrawOver(pDevice);
						}
						break;
					case LANK:
						if(bLankInit == true)
						{
							DrawLank(pDevice);
						}
						break;
					default:
						continue;
					}
						
					//---------------------------------------------------------
					// �`��I��
					pDevice->EndScene();
				}

				//-------------------------------------------------------------
				// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@����ւ�
				pDevice->Present( 
							NULL ,
							NULL ,
							NULL , 
							NULL );

				//-------------------------------------------------------------
				// FPS�Ɋւ��邱��
				nFrameCount++;						// �t���C���J�E���g
				SetFrameTime( nFrameCount );		// �t���C�����Z�b�g
			}
		}
	}
	//-------------------------------------------------------------------------
	// �S�J��
	UninitTitle();
	FieldUninit();
	PlayerUninit();
	EnemyUninit();
	MeshWallUninit();
	BulletUninit();
	ShadowUninit();
	ExplosionUninit();
	EffectUninit();
	FontAllUninit();
	EnemyLifeUninit();
	UninitClear();
	UninitTitle();
	UninitOver();

	//-------------------------------------------------------------------------
	// �L�[���͉��
	UninitInput();

	//-------------------------------------------------------------------------
	// �f�o�C�X�̉��
	if( pDevice != NULL)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pD3D != NULL)
	{
		pD3D->Release();
		pD3D = NULL;
	}

	//-------------------------------------------------------------------------
	// �E�B���h�E�N���X�o�^������
	UnregisterClass(
		CLASS_NAME ,
		wcex.hInstance);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	return (int)msg.wParam;
}

void GameSelectSet(int Select)
{
	g_nSelect = Select;
}

int GameTimerGet(void)
{
	return g_nGameTime;
}

bool GameStop(void)
{
	return g_bStop;
}

	

