//=============================================================================
// �c�[���쐬�̑O�菇�@�@�@�@�@�@�@�@�t�B�[���h�쐬�c�[���p
//  
// ���C������ [main.cpp]
//
// �@�\ : DXUT�̊�b�𒲂ׂ����
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================

#include "manager.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CLASS_NAME	("���b�V���t�B�[���h")		// �N���X�̖��O
#define WINDOW_NAME	("���b�V���t�B�[���h")		// �E�B���h�E�̖��O

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//=============================================================================
// �֐���	: APIENTRY WinMain
// �߂�l	: DWORD
// �����l	: H�C���X�^���X, H�v���r���[�C���X�^���X, 
//				�R�}���h���C��, �R�}���h�f��
// �@�\		: ���C������
//=============================================================================
int APIENTRY WinMain(HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	// �E�B���h�E�Ɋւ���ϐ�
	HWND	hWnd;			// �E�B���h�E�n���h��
	MSG		msg;			// ���b�Z�[�W
	HRESULT	hr;				// �G���[����

	// FPS�Ɋւ���ϐ�
	DWORD dwExecLastTime;	// �Ō�̎���
	DWORD dwFPSLastTime;	// FPS�I������
	DWORD dwCurrentTime;	// ���݂̎���
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwCoudwtFPS;		// FPS�J�E���^�[

	// �E�B���h�E�N���X�쐬
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);


	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx( 0,			// �E�B���h�E�X�^�C���쐬
				CLASS_NAME,				// �N���X�̖��O�ݒ�
				WINDOW_NAME,			// �E�B���h�E�̖��O�ݒ�
				WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C���ݒ�
				CW_USEDEFAULT,			// �E�B���h�E��\������ʒu (X���W)
				CW_USEDEFAULT,			// �E�B���h�E��\������ʒu (Y���W)
				WINDOW_WIDTH,			// �E�B���h�E�̕�
				WINDOW_HEIGHT,			// �E�B���h�E�̍���
				NULL,					// �e�E�B���h�E�̃n���h��
				NULL,					// ���j���[�n���h��
				hInstance,				// �C���X�^���X�n���h��
				NULL);					// ���̑��̍쐬�f�[�^

	// FPS�ݒ�
	timeBeginPeriod(1);					// �f�o�C�X�h���C�u�̎��Ԃ��~���b�Ɏw��
	dwExecLastTime =					// FPS�Ō�̎��Ԃ���	
	dwFPSLastTime = timeGetTime();		// ���Ԃ��擾
	dwCurrentTime =						// �t���[���J�E���g�����݂̎��Ԃɑ��
	dwFrameCount = 0;					// �t���[���J�E���g��������
	dwCoudwtFPS	= 0;					// FPS�J�E���^�[������

	// �}�l�[�W���[���쐬
	CManager *pManager = NULL;						// �}�l�[�W���[�|�C���^������ 
	NEW_TYPE(pManager, CManager);					// �}�l�[�W���[����
	hr = pManager->Init(hInstance, hWnd, TRUE);		// �}�l�[�W��������
	ERROR_CHACK(hr);								// �G���[�`�F�b�N

	// �E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);						// �E�B���h�E�\��
	UpdateWindow(hWnd);								// �E�B���h�E�̍X�V

	// �X�V���`��
	while(true)
	{
		// ���b�Z�[�W�擾
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
			dwCurrentTime = timeGetTime();
			if( (dwCurrentTime - dwFPSLastTime) >= 500)
			{
				dwCoudwtFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			/////// FPS��1�b�������� //////
			if((dwCurrentTime - dwExecLastTime) >= 1000 / 60)
			{
				CManager::GetDebug()->Print("FPS:%d\n", dwCoudwtFPS);	// FPS�o��
				pManager->Update();										// �}�l�[�W���[�X�V
				pManager->Draw();										// �}�l�[�W���[�`��
				dwExecLastTime = dwCurrentTime;						
				dwFrameCount++;											// ���݂̎��Ԃ��J�E���g�A�b�v
			}
		}
	}

	// �I������
	CLASS_DELETE(pManager);		// �}�l�[�W���N���X�j��

	///// �V�X�e���I������ /////
	return NULL;
}


//=============================================================================
// �֐���	: WndProc
// �߂�l	: LRESULT
// �����l	: �E�B���h�E�n���h��, ���b�Z�[�W, W�p�����[�^, L�p�����[�^ 
// �@�\		: �E�B���h�E�ɒ��ڍs������
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{	
	case WM_DESTROY:
		PostQuitMessage(0);						// �E�B���h�E��j��
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE :						// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);				// �E�B���h�E��j������悤�Ɏw��
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd , message , wParam , lParam);
		break;
	}
	return 0;
}

