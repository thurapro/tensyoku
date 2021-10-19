/**************************************************************************//**
 * @file		NetworkMessage.h
 * @brief
 * @author 		Watanabe Yositaka
 *****************************************************************************/
#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H

/*
���M���b�Z�[�W
�T�u�Q�[���̌���
id:0xFF
data:null

��ʑJ��
id:1
data:�J�ڐ�
data[0] = 0:�^�C�g��
data[0] = 1:�ȑI��
data[0] = 2:�Q�[��
data[0] = 3:���U���g
data[0] = 4:�����L���O
data[0] = 0xFF:���̃V�[�P���X


�ȑI��
id:2
data:�Ȕԍ�,��Փx
data[0] = 0:bgm1
data[0] = 0:bgm2
data[0] = 0:bgm3
data[1] = 0:easy
data[1] = 1:normal
data[1] = 2:hard

Score
id:3
data:Score
data[0] = x:�X�R�A�l
*/

/*
��M���b�Z�[�W

�T�u�Q�[���̌����̉���
id:-0xFF
data:null

*/

#pragma warning(disable:4351)
struct NetworkMessage{
	NetworkMessage() :messageID(-1), data(){
	}
	int messageID;
	unsigned char data[64];
};
#pragma warning(default:4351)

const int SUBGAME_PORT = 60001;
const int MAINGAME_PORT = 60000;

#endif //NETWORKMESSAGE_H