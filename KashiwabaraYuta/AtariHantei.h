#pragma once
//=======================================================================================
//						�����蔻��`��
//						2017.06.05
//=======================================================================================

#ifndef _ATARIHANTEI_H_
#define _ATARIHANTEI_H_

#include<d3d9.h>
#include<d3dx9.h>
#include "Player.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Zirai.h"
#include "Shot.h"
#include "EnemyHPgage.h"
#include "ZombieHPgage.h"
#include "ItemMarker.h"
#include "EnemyKage.h"
#include "ZombieKage.h"
#include "RecoveryItem.h"



class AtariHantei
{
public:
	AtariHantei();
	~AtariHantei();
	bool atari(float PlayerX, float PlayerY, float PlayerZ, float PlayerHankei, float ItemX, float ItemY, float ItemZ, float ItemHankei);
	void Init(void);//����������
	void Update(void);//�X�V����
	void Uninit(void);//�I������
	void ResetParameters();//�p�����[�^�̃��Z�b�g

	//�v���C���[�̈ʒu���W���l�������Ă���
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}

	//�G///////////////////////////////////////////////////////
	//�G�̈ʒu���W���l�������Ă���
	void SetEnemyPos(D3DXVECTOR3 pos)
	{
		EnemyPos = pos;
	}
	//�G�̕`���Ԃ�Manager.cpp�ɑ���
	bool GetEnemyDraw()
	{
		return EnemyDraw;
	}
	//�G�̉e�`���Ԃ�Manager.cpp�ɑ���
	bool GetEnemyKageDraw()
	{
		return EnemyKageDraw;
	}
	//�GHP�Q�[�W�̎c��c�ʂ������Ă��鏈��
	float GetEnemyHPgage()
	{
		return EnemyHP;
	}
	//�G�̎c�萔�𑗂鏈��
	int GetEnemyNokori() 
	{
		return EnemyNokori;
	}
	//�G///////////////////////////////////////////////////////

	//�A�C�e��///////////////////////////////////////////////////////
	//�A�C�e���̈ʒu���W���l�������Ă���
	void SetItemPos(int num, float x, float y, float z)
	{
		Itematari[num].posx = x;
		Itematari[num].posy = y;
		Itematari[num].posz = z;
	}
	int GetItemLoop(int Loop)
	{
		return Loop;
	}
	//�A�C�e���̕`���Ԃ�Manager.cpp�ɑ���
	bool GetItemDraw(int Loop)
	{
		return Itematari[Loop].ItemDraw;
	}
	//�A�C�e���}�[�J�[�`���Ԃ�Manager.cpp�ɑ���
	bool GetItemMarkerDraw(int Loop)
	{
		return Itematari[Loop].ItemMarkerDraw;
	}
	//�A�C�e��///////////////////////////////////////////////////////

	//�񕜃A�C�e��///////////////////////////////////////////////////////
	//�񕜃A�C�e���̈ʒu���W���l�������Ă���
	void SetRecoveryItemPos(int num, float x, float y, float z)
	{
		RecoveryItematari[num].posx = x;
		RecoveryItematari[num].posy = y;
		RecoveryItematari[num].posz = z;
	}
	int GetRecoveryItemLoop(int Loop)
	{
		return Loop;
	}
	//�񕜃A�C�e���̕`���Ԃ�Manager.cpp�ɑ���
	bool GetRecoveryItemDraw(int Loop)
	{
		return RecoveryItematari[Loop].ItemDraw;
	}
	//�񕜃A�C�e���}�[�J�[�`���Ԃ�Manager.cpp�ɑ���
	bool GetRecoveryItemMarkerDraw(int Loop)
	{
		return RecoveryItematari[Loop].ItemMarkerDraw;
	}
	//�񕜃A�C�e��///////////////////////////////////////////////////////

	//�]���r///////////////////////////////////////////////////////
	//�]���r�̈ʒu���W���l�������Ă���
	void SetZombiePos(int num, float x, float y, float z)
	{
		Zombieatari[num].posx = x;
		Zombieatari[num].posy = y;
		Zombieatari[num].posz = z;
	}
	int GetZombieLoop(int Loop)
	{
		return Loop;
	}
	//�]���r�̕`���Ԃ�Manager.cpp�ɑ���
	bool GetZombieDraw(int Loop)
	{
		return Zombieatari[Loop].ZombieDraw;
	}
	//�G�̉e�`���Ԃ�Manager.cpp�ɑ���
	bool GetZombieKageDraw(int Loop)
	{
		return Zombieatari[Loop].ZombieKageDraw;
	}
	//�]���rHP�Q�[�W�̎c��c�ʂ������Ă��鏈��
	float GetZombieHPgage(int Loop)
	{
		return Zombieatari[Loop].ZombieHP;
	}
	//�]���r�̎c�萔�𑗂鏈��
	int GetZombieNokori()
	{
		return ZombieNokori;
	}
	//�]���r///////////////////////////////////////////////////////

	//�n��///////////////////////////////////////////////////////
	//�n���̈ʒu���W���l�������Ă���
	void SetZiraiPos(int num, float x, float y, float z)
	{
		Ziraiatari[num].posx = x;
		Ziraiatari[num].posy = y;
		Ziraiatari[num].posz = z;
	}
	int GetZiraiLoop(int Loop)
	{
		return Loop;
	}
	//�n���̕`���Ԃ�Manager.cpp�ɑ���
	bool GetZiraiDraw(int Loop)
	{
		return Ziraiatari[Loop].Draw;
	}
	//�n���̂����蔻���Ԃ�Manager.cpp�ɑ���
	bool GetZiraiAtariHantei(int Loop)
	{
		return Ziraiatari[Loop].AtariHantei;
	}
	//�n���̕`���Ԃ������Ă���
	void SetZiraiDraw(int Loop, bool draw)
	{
		Ziraiatari[Loop].Draw = draw;
	}
	//�n���̂����蔻���Ԃ������Ă���
	void SetZiraiAtariHantei(int Loop, bool hit)
	{
		Ziraiatari[Loop].AtariHantei = hit;
	}
	//�����̕`���Ԃ�Manager.cpp�ɑ���
	bool GetBakuhuDraw(int Loop)
	{
		return Ziraiatari[Loop].BakuhuDraw;
	}
	//�n��///////////////////////////////////////////////////////

	//�e///////////////////////////////////////////////////////
	//�e�̈ʒu���W���l�������Ă���
	void SetShotPos(int num, float x, float y, float z)
	{
		Shotatari[num].posx = x;
		Shotatari[num].posy = y;
		Shotatari[num].posz = z;
	}
	int GetShotLoop(int Loop)
	{
		return Loop;
	}
	//�e�̕`���Ԃ�Manager.cpp�ɑ���
	bool GetShotDraw(int Loop)
	{
		return Shotatari[Loop].Draw;
	}
	//�e�̂����蔻���Ԃ�Manager.cpp�ɑ���
	bool GetShotAtariHantei(int Loop)
	{
		return Shotatari[Loop].AtariHantei;
	}
	//�e�̕`���Ԃ������Ă���
	void SetShotDraw(int Loop, bool draw)
	{
		Shotatari[Loop].Draw = draw;
	}
	//�e�̂����蔻���Ԃ������Ă���
	void SetShotAtariHantei(int Loop, bool hit)
	{
		Shotatari[Loop].AtariHantei = hit;
	}

	//�񕜂�����e�򐔂𑗂�
	int Getammunition()
	{
		return ammunition;
	}
	//�e///////////////////////////////////////////////////////

	//��///////////////////////////////////////////////////////
	//�Ƃ̈ʒu���W���l�������Ă���
	void SetIePos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	//��2�̈ʒu���W���l�������Ă���
	void SetIe2Pos(D3DXVECTOR3 pos)
	{
		Ie2Pos = pos;
	}
	//��///////////////////////////////////////////////////////

	//HP�̐��l�𑗂�
	int GetHP()
	{
		return HP;
	}

private:
//*****************************************************************************
// �\����
//*****************************************************************************

	//�A�C�e��///////////////////////////////////////
	typedef struct//�݌v�}�����
	{
		float posx;//���Wx
		float posy;//���Wy
		float posz;//���Wz
		bool bHit;//�����蔻��
		bool ItemDraw = true;//�A�C�e���̕`����
		bool ItemMarkerDraw = true;//�A�C�e���}�[�J�[�̕`����
		bool ItemAtariHantei = true;//�����蔻��̏��
	}ITEM_ATARI;

	ITEM_ATARI Itematari[ITEM_NUM];//�\���̂ŃA�C�e����������邩��錾
	//�A�C�e��///////////////////////////////////////

	//�񕜃A�C�e��///////////////////////////////////////

	ITEM_ATARI RecoveryItematari[RECOVERYITEM_NUM];//�\���̂ŃA�C�e����������邩��錾

	//�񕜃A�C�e��///////////////////////////////////////

	//�]���r///////////////////////////////////////
	typedef struct//�݌v�}�����
	{
		float posx;//�]���r�̍��Wx
		float posy;//�]���r�̍��Wy
		float posz;//�]���r�̍��Wz
		bool bHit;//�����蔻��
		bool ZombieDraw = true;//�]���r�̕`����
		bool ZombieKageDraw = true;//�]���r�e�̕`����
		bool ZombieAtariHantei = true;//�����蔻��̏��
		float ZombieHP = 100.0f;//�]���r��HP���
	}ZOMBIE_ATARI;

	ZOMBIE_ATARI Zombieatari[ZOMBIE_NUM];//�\���̂ŃA�C�e����������邩��錾
	//�]���r///////////////////////////////////////

	//�n��///////////////////////////////////////
	typedef struct//�݌v�}�����
	{
		float posx;//���Wx
		float posy;//���Wy
		float posz;//���Wz
		bool bHit;//�����蔻��
		bool Draw = false;//�`����
		bool AtariHantei = false;//�����蔻��̏��
		bool BakuhuDraw = false;//�����̕`����
	}DATA_ATARI;

	DATA_ATARI Ziraiatari[ZIRAI_NUM];//�\���̂ŃA�C�e����������邩��錾
	//�n��///////////////////////////////////////

	//�e/////////////////////////////////////////
	DATA_ATARI Shotatari[SHOT_NUM];//�\���̂ŃA�C�e����������邩��錾

	int ammunition = 0;//�e����񕜂��鐔
	//�e/////////////////////////////////////////

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//Player
	D3DXVECTOR3 PlayerPos;

	//Enemy
	D3DXVECTOR3 EnemyPos;//�G�l�~�[�̍��W
	bool EnemyDraw = true;//�G�l�~�[�̕`����
	bool EnemyKageDraw = true;//�G�l�~�[�e�̕`����
	bool EnemyAtariHantei = true;//�G�l�~�[�̂����蔻��̏��
	float EnemyHP = 200.0f;//�G�l�~�[��HP���

	//��1
	D3DXVECTOR3 IePos;
	//��2
	D3DXVECTOR3 Ie2Pos;

	int ZombieNokori = ZOMBIE_NUM;//�]���r�̎c�萔
	int EnemyNokori = ENEMY_NUM;//�G�̎c�萔

	int HP = HP_NUM;//�c��HP

	//�T�E���h
	int oto0;//���y�p�ϐ�
	int oto1;//���y�p�ϐ�

	
};

#endif //_ATARIHANTEI_H_