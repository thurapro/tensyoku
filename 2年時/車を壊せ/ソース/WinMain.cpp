//=============================================================================
//
// FAILE NAME[WinMain.cpp]
//
// ���O		: ���� �Y��
//
// �N���X	: AT12C283
//
// �@�\		: ���C��
//
//
//=============================================================================
#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "../hedder/Font.h"
#include "../hedder/Direct3DCreater.h"
#include "../hedder/WndProc.h"
#include "../hedder/Texture.h"
#include "../hedder/PrimitiveCreater.h"
#include "../hedder/Judgment.h"
#include "../hedder/common.h"
#include "../hedder/InputKey.h"
#include "../hedder/game.h"
#include "../hedder/System.h"
#include "../hedder/FPS.h"
#include "../hedder/Sound.h"
#include "../hedder/WinMain.h"
#include "../hedder/Title.h"
#include "../hedder/Clear.h"
#include "../hedder/Over.h"

static int g_GameSelect = INIT;

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
// ���C���֐�
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
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

	HWND hWnd;
	MSG msg;
	HRESULT hr = NULL;


	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

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

	int nFrameCount = 0;
	
	// �V�X�e��������
	SystemInit(hInstance , hWnd);

	if( !SoundInit( hWnd ) )
	{
		return -1;
	}
	if( !CreatePrimaryBuff() ) 
	{
		return -1;
	}

	// �ϐ���`
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3ddeviceGetDevice();

	// �E�B���h�E�\��
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	BOOL bFPSFixing = FALSE;


	// ���C�����[�v
	while(1)
	{
		bFPSFixing = FPSFixing();

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
			if( bFPSFixing == TRUE )
			{
				UpdateInput();

				switch( g_GameSelect )
				{
				case INIT :
					TitleInit();
					GameInit();
					ClearInit();
					OverInit();
					g_GameSelect = TITLE;
					break;

				case TITLE :
					TitleUpdate();
					break;

				//=========================
				// �Q�[���X�V����
				//=========================
				case GAME :
					GameUpdate();
					break;

				case CLEAR :
					ClearUpdate();
					break;

				case OVER :
					OverUpdate();
				}
				
#if 0
				for(int i=0;i<�G�̐�;++i)
				{
					�v���[���[�ƓG��x�̍��� = �v���[���[��x���W - �G��x���W
					�v���[���[�ƓG��y�̍��� = �v���[���[��y���W - �G��y���W
					�v���[���[�ƓG�̋��� = sqrtf( (�v���[���[�ƓG��x�̍��� * �v���[���[�ƓG��x�̍���) + (�v���[���[�ƓG��y�̍��� * �v���[���[�ƓG��y�̍���) );
					if( �������Ă�����(�v���[���[�ƓG�̋���<�v���[���[�̔��a�{�G�̔��a) )
					{
						�������Ă������̏���
					}
				}
#endif

				//=========================
				// �Q�[���`�揈��
				//=========================
				// �o�b�N�o�b�t�@�̃N���A
				pD3DDevice->Clear
					( 0 , NULL ,
					 (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER) ,
					 D3DCOLOR_RGBA( 0 , 0 , 0 , 0) ,
					 1.0f, 0);			


				// �`��J�n
				hr = pD3DDevice->BeginScene();
				if( SUCCEEDED(hr) )
				{
					//==============================
					// �����ɕ`�揈��
					//==============================
					
					//*******************************
					// �`��֐�
					//*******************************
					switch( g_GameSelect )
					{
						if( g_GameSelect != INIT )
						{
							case TITLE :
								TitleDraw();
								break;

							case GAME :
								GameDraw();
								break;

							case CLEAR :
								ClearDraw();
								break;

							case OVER :
								OverDraw();

							default :
								break;
						}
					}
						
					// �`��I��
					pD3DDevice->EndScene();
				}

				// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@����ւ�
				pD3DDevice->Present( 
							NULL ,
							NULL ,
							NULL , 
							NULL );

				nFrameCount++;
				SetFrameTime( nFrameCount );
			}
		}

	}

	// �S�V�X�e���̉��
	SystemUninit();

	// �E�B���h�E�N���X�o�^������
	UnregisterClass(
		CLASS_NAME ,
		wcex.hInstance);

	return (int)msg.wParam;
}

int GameSelectGet( void )
{
	return g_GameSelect;
}

void GameSelectSet( int Select )
{
	g_GameSelect = Select;
}


