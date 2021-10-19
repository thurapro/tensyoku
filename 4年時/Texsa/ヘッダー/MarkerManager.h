/*-----------------------------------------------------------------------------
 another : Yuta Matsuo

 ���ʕ\���N���X
-----------------------------------------------------------------------------*/
#ifndef _MARKERMANAGER_H_
#define _MARKERMANAGER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Node.h"

//=============================================================================
// �}�N����`
//=============================================================================
#pragma warning(disable:4996)

struct MusicScore;
class MarkerButton;
class Score;

//=============================================================================
// �N���X�錾
//=============================================================================
class MarkerManager : public MeekH::Node{
public:
	MarkerManager();								// �C���X�^���X����
	~MarkerManager();								// �C���X�^���X�j��
	void Init(char *FilePath);						// �{�^���e�N�X�`��������
	void Update();									// �{�^���X�X�V
	void SetVisibleToken(int count);
	void SetStartToken(int count);
	float GetTokenSpeed();
	void SetMarkerSuccess(bool Success);			// �{�^�����肪���������̂�
	void SetComboNum(int i);
	void AddComboNum( int i );
	void AddGoodNum( int i );
	void AddBadNum( int i );

	int GetComboNum();

private:
	void Load(char *FilePath);			// �y���ǂݍ���
	int m_CountToken;					// �����̃J�E���^�[
	int m_VisibleToken;					// �o�����Ă��Ȃ��ƍs���Ȃ�������
	int m_StartToken;					// for�̍ŏ��̒l
	int m_MaxToken;						// �����̍ő吔
	MusicScore *m_MusicScore;			// 
	MarkerButton *m_pMarkerButton;		// �}�[�J�{�^��
	int m_ButtonID;
	int m_ButtonEndID;
	Score *m_pScore;					// �X�R�A�[
	float m_fTokenSpeed;				// �ꔏ�̃X�s�[�h
	int m_nMaxSpeed;					// �}�[�J�[BG�̓������x
	int m_nComboNum;					// �R���{��
	bool m_bMarkerSuccess;				// �{�^�����肪����������
};

#endif // _MARKERMANAGER_H_