#pragma once
//=============================================================================
//  
// �}�l�[�W���[�N���X
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "Enemy.h"
#include "Zombie.h"
#include "Shot.h"
#include "Zirai.h"
#include "RecoveryItem.h"
//*****************************************************************************
// ���N���X
//*****************************************************************************
class Manager
{
public:
	Manager();//�R���X�g���N�^
	~Manager();//�f�X�g���N�^
	void Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	void ResetParameters();//�p�����[�^�̃��Z�b�g
	//�����蔻�肩��̃t���O�������Ă��鏈��
	void Setnflag(int num)
	{
		nflag = num;
	}
	//�J�������猨�z�����ǂ����������Ă��鏈��
	void SetTPS_UI(bool draw)
	{
		TPS_UI = draw;
	}
	//Shot����e��̎c���������Ă��鏈��
	void SetShot_UI(int num)
	{
		Shot_UI = num;
	}
	//Zirai����n���̎c���������Ă��鏈��
	void SetZirai_UI(int num)
	{
		Zirai_UI = num;
	}
	//�����蔻�肩��c��HP�������Ă��鏈��
	void SetHP_UI(int num)
	{
		HP_UI = num;
	}

	void SetZombieNokori(int num)
	{
		ZombieNokori = num;
	}

	void SetEnemyNokori(int num)
	{
		EnemyNokori = num;
	}
private:
	int nflag = 0;//�^�C�g���˃Q�[���v���C�˃Q�[���I�[�o�[�˃^�C�g��
	int nflagTime = 0;//�V�[���J�ڗp�^�C��

	bool g_bPress = true;//�^�C�g���e�N�X�`����ON/OFF�̕ύX������
	int g_nCnt = 0;//�^�C�g����ON/OFF�̎��Ԃ��J�E���g������
	bool TPS_UI = false;//���z���J������ON/OFF�𒲂ׂ�
	int HP_UI = HP_NUM;//�c��HP
	int Shot_UI = SHOT_NUM;//�c��e��
	int Zirai_UI = ZIRAI_NUM;//�c��̒n����
	int ZombieNokori = ZOMBIE_NUM;//�c��]���r��
	int EnemyNokori = ENEMY_NUM;//�c��̓G��
	bool test = false;

	//�T�E���h
	int count0 = 0;//���y�p�ϐ�
	int count1 = 0;//���y�p�ϐ�
	int count2 = 0;//���y�p�ϐ�
	int count3 = 0;//���y�p�ϐ�
	int count4 = 0;//���y�p�ϐ�
	//�T�E���h
};
#endif // _MANAGER_H_