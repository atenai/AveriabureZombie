//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,//�^�C�g��
	SOUND_LABEL_BGM001,//�Q�[���v���C
	SOUND_LABEL_BGM002,//�e���ˉ�
	SOUND_LABEL_BGM003, // �]���r�ƒe�̓���������
	SOUND_LABEL_BGM004,//����I��
	SOUND_LABEL_BGM005,//�e�A�C�e����
	SOUND_LABEL_BGM006, // �e���\���鉹
	SOUND_LABEL_BGM007,//�n��������
	SOUND_LABEL_BGM008,//�Q�[���N���A�[
	SOUND_LABEL_BGM009,//�Q�[���I�[�o�[
	SOUND_LABEL_BGM010,//��䰉�
	SOUND_LABEL_BGM011,//�n���̐ݒu��
	SOUND_LABEL_BGM012,//�n���̋N����
	SOUND_LABEL_BGM013,//�v���C���[�_���[�W��
	SOUND_LABEL_BGM014,//�ǂɒe�������������̉�
	SOUND_LABEL_BGM015,//�񕜃A�C�e����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);//����̉��y�������~�߂�
void StopSound(void);//�S�Ẳ��y���~�߂�

#endif
