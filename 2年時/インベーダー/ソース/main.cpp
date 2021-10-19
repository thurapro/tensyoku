//-----------------------------------------------------------------------------
//
// main���� 		[main.cpp]	�����Y��
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "CScreen.h"
#include "main.h"
#include "manager.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
static int		g_nCountFPS = 0;			// FPS�̃J�E���^�[

//-----------------------------------------------------------------------------
// ���C������
//-----------------------------------------------------------------------------
void main(void)
{
	int nExecLastTime;
	int nFPSLastTime;
	int nCurrentTime;
	int nFrameCount;
	CManager *pManager = NULL;

	// ����\��ݒ�
	timeBeginPeriod(1);

	nExecLastTime = 
	nFPSLastTime = timeGetTime();
	nCurrentTime = 
	nFrameCount = 0;

	if(pManager == NULL)
	{
		pManager = new CManager();
		pManager->Init();
	}

	// �J�[�\��OFF
	CUROFF();

	// �Q�[�����C������
	do{
		nCurrentTime = timeGetTime();
		if( ( nCurrentTime - nFPSLastTime ) >= 500 )
		{
			g_nCountFPS = nFrameCount * 1000 / (nCurrentTime - nFPSLastTime );
			nFPSLastTime = nCurrentTime;
			nFrameCount = 0;
		}
		if( ( nCurrentTime - nExecLastTime ) >= ( 1000 / 60 ) )
		{
			nExecLastTime = nCurrentTime;

			// �X�V����
			pManager->Update();

			// �`�揈��
			pManager->Draw();

#ifdef _DEBUG		
			// FPS�\��
			DispFPS();
#endif
			// FPS�\��
			nFrameCount++;
		}
	}while(!INP( KEY_ESC ));

	// �J�[�\��ON
	CURON();

	// �I������
	pManager->Uninit();

	if(pManager != NULL)
	{
		delete pManager;
		pManager = NULL;
	}
	// ����\��߂�
	timeEndPeriod(1);
}

//-------------------------------------------------------------------------------
// FPS��ʕ\��
//-------------------------------------------------------------------------------
void DispFPS(void)
{
	LOCATE(1 , 1);
	printf("FPS = %d", g_nCountFPS );	// FPS�`��
}




