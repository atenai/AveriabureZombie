//=============================================================================
//
// �}�l�[�W���[ [Manager.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Manager.h"
#include "Player.h"
#include "Field.h"
#include "Kusa.h"
#include "Bonbe.h"
#include "Camera.h"
#include "Ame.h"
#include "PlayerKage.h"
#include "Item.h"
#include "ItemMarker.h"
#include "UAV.h"
#include "Ie.h"
#include "EnemyKage.h"
#include "EnemyHPgage.h"
#include "ZombieKage.h"
#include "ZombieHPgage.h"
#include "AtariHantei.h"
#include "Bakuhu.h"
#include "BoxAtariHantei.h"
#include "input.h"
#include "sound.h"
#include "UI.h"
#include "RecoveryItemMarker.h"

//===========================
//�N���X��(�݌v�})�̖��O�t��
//===========================
Player *p_Player;//�v���C���[�N���X(�݌v�})�̃|�C���^��p��
PlayerKage *p_PlayerKage;//�v���C���[�e�N���X(�݌v�})�̃|�C���^��p��
Camera *p_Camera;//�J�����N���X(�݌v�})�̃|�C���^��p��
SkyDome *p_SkyDome;//�X�J�C�h�[���N���X(�݌v�})�̃|�C���^��p��
Zimen *p_Zimen;//�n�ʃN���X(�݌v�})�̃|�C���^��p��
Kusa1 *p_Kusa1;//��1�N���X(�݌v�})�̃|�C���^��p��
Kusa2 *p_Kusa2;//��2�N���X(�݌v�})�̃|�C���^��p��
Kusa3 *p_Kusa3;//��3�N���X(�݌v�})�̃|�C���^��p��
Tree *p_Tree;//�؃N���X(�݌v�})�̃|�C���^��p��
Bonbe *p_Bonbe;//�{���x�N���X(�݌v�})�̃|�C���^��p��
Bonbe *p_Bonbe2;//�{���x2�N���X(�݌v�})�̃|�C���^��p��
Ame *p_Ame;//�J�N���X(�݌v�})�̃|�C���^��p��
Shot *p_Shot;//�e�N���X(�݌v�})�̃|�C���^��p��
Zirai *p_Zirai;//�n���N���X(�݌v�})�̃|�C���^��p��
Item *p_Item;//�A�C�e���N���X(�݌v�})�̃|�C���^��p��
ItemMarker *p_ItemMarker;//�A�C�e���}�[�J�[�N���X(�݌v�})�̃|�C���^��p��
UAV *p_UAV;//UAV�N���X(�݌v�})�̃|�C���^��p��
Ie *p_Ie;//�ƃN���X(�݌v�})�̃|�C���^��p��
Ie *p_Ie2;//��2�N���X(�݌v�})�̃|�C���^��p��
Enemy *p_Enemy;//�G�l�~�[�N���X(�݌v�})�̃|�C���^��p��
EnemyKage *p_EnemyKage;//�G�l�~�[�e�N���X(�݌v�})�̃|�C���^��p��
EnemyHPgage *p_EnemyHPgage;//�G�l�~�[HP�Q�[�W�N���X(�݌v�})�̃|�C���^��p��
Zombie *p_Zombie;//�]���r�N���X(�݌v�})�̃|�C���^��p��
ZombieKage *p_ZombieKage;//�]���r�e�N���X(�݌v�})�̃|�C���^��p��
ZombieHPgage *p_ZombieHPgage;//�]���rHP�Q�[�W�N���X(�݌v�})�̃|�C���^��p��
AtariHantei *p_AtariHantei;//�����蔻��N���X(�݌v�})�̃|�C���^��p��
Bakuhu *p_Bakuhu;//�����N���X(�݌v�})�̃|�C���^��p��
BoxAtariHantei *p_BoxAtariHantei;//�{�b�N�X�����蔻��(�݌v�})�̃|�C���^��p��
UI *p_UI;//UI(�݌v�})�̃|�C���^��p��
RecoveryItem *p_RecoveryItem;//�񕜃A�C�e���N���X(�݌v�})�̃|�C���^��p��
RecoveryItemMarker *p_RecoveryItemMarker;//�񕜃A�C�e���}�[�J�[�N���X(�݌v�})�̃|�C���^��p��

//===============
//�O���[�o���ϐ�
//===============

//==============
//�R���X�g���N�^
//==============
Manager::Manager()
{
}

//==============
//�f�X�g���N�^
//==============
Manager::~Manager()
{
}


//==============
//  �������֐�
//==============
void Manager::Init()
{
	p_Camera = new Camera;//�J�����N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Camera->Init();//�J�����̏���������

	p_UAV = new UAV;//UAV�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_UAV->Init();//UAV�̏���������

	p_Player = new Player;//�v���C���[�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Player->Init();//�v���C���[�̏���������
	p_Player->SetPlayerPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�ړ��p���l������

	p_Ie = new Ie;//�ƃN���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Ie->SetPos(D3DXVECTOR3(0.0f, 0.0f, 10.0f));//�����Ƃ̍��W���Z�b�g
	p_Ie->Init();//�Ƃ̏���������
	

	p_Ie2 = new Ie;//��2�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Ie2->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));//������2�̍��W���Z�b�g
	p_Ie2->Init();//��2�̏���������
	

	p_Enemy = new Enemy;//�G�l�~�[�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Enemy->Init();//�G�l�~�[�̏���������
	p_Enemy->SetIePos(p_Ie->GetPos());
	p_Enemy->SetIeMin(p_Ie->GetIeMin());
	p_Enemy->SetIeMax(p_Ie->GetIeMax());
	p_Enemy->SetIe2Pos(p_Ie2->GetPos());
	p_Enemy->SetIe2Min(p_Ie2->GetIeMin());
	p_Enemy->SetIe2Max(p_Ie2->GetIeMax());

	p_Zombie = new Zombie;//�]���r�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Zombie->Init();//�]���r�̏���������
	p_Zombie->SetIePos(p_Ie->GetPos());
	p_Zombie->SetIeMin(p_Ie->GetIeMin());
	p_Zombie->SetIeMax(p_Ie->GetIeMax());
	p_Zombie->SetIe2Pos(p_Ie2->GetPos());
	p_Zombie->SetIe2Min(p_Ie2->GetIeMin());
	p_Zombie->SetIe2Max(p_Ie2->GetIeMax());

	p_Zimen = new Zimen;//�n�ʃN���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Zimen->Init();//�n�ʂ̏���������

	p_SkyDome = new SkyDome;//�X�J�C�h�[���N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_SkyDome->Init();//�X�J�C�h�[���̏���������

	p_Item = new Item;//�A�C�e���N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Item->Init();//�A�C�e���̏���������

	p_RecoveryItem = new RecoveryItem;//�񕜃A�C�e���N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_RecoveryItem->Init();//�񕜃A�C�e���̏���������

	p_Tree = new Tree;//�؃N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Tree->Init();//�؂̏���������

	p_Kusa1 = new Kusa1;//��1�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Kusa1->Init();//��1�̏���������

	p_Kusa2 = new Kusa2;//��2�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Kusa2->Init();//��2�̏���������

	p_Kusa3 = new Kusa3;//��3�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Kusa3->Init();//��3�̏���������

	p_Ame = new Ame;//�J�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Ame->Init();//�J�̏���������

	p_ItemMarker = new ItemMarker;//�A�C�e���}�[�J�[�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_ItemMarker->Init();//�A�C�e���}�[�J�[�̏���������
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_ItemMarker->SetPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//�A�C�e���}�[�J�[�̍��W���Z�b�g
	}

	p_RecoveryItemMarker = new RecoveryItemMarker;//�񕜃A�C�e���}�[�J�[�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_RecoveryItemMarker->Init();//�񕜃A�C�e���}�[�J�[�̏���������
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_RecoveryItemMarker->SetPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//�񕜃A�C�e���}�[�J�[�̍��W���Z�b�g
	}

	p_EnemyHPgage = new EnemyHPgage;//�G�l�~�[HP�Q�[�W�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_EnemyHPgage->Init();//�G�l�~�[HP�Q�[�W�̏���������
	p_EnemyHPgage->SetEnemyPos(p_Enemy->GetEnemyPos());//�G�l�~�[HP�Q�[�W�̏������W���Z�b�g

	p_ZombieHPgage = new ZombieHPgage;//�]���rHP�Q�[�W�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_ZombieHPgage->Init();//�]���rHP�Q�[�W�̏���������
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_ZombieHPgage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�]���rHP�Q�[�W�̏������W���Z�b�g
	}

	p_PlayerKage = new PlayerKage;//�v���C���[�e�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_PlayerKage->Init();//�v���C���[�e�̏���������
	p_PlayerKage->SetPlayerPos(p_Player->GetPlayerPos());//�v���C���[�e�̏������W���Z�b�g

	p_EnemyKage = new EnemyKage;//�G�l�~�[�e�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_EnemyKage->Init();//�G�l�~�[�e�̏���������
	p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//�G�l�~�[�e�̏������W���Z�b�g

	p_ZombieKage = new ZombieKage;//�]���r�e�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_ZombieKage->Init();//�]���r�e�̏���������
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�]���r�e�̏������W���Z�b�g
	}

	p_Shot = new Shot;//�e�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Shot->Init();//�e�̏���������
	p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//�e�̏������W���Z�b�g
	p_Shot->SetPlayerFront(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�e�̑O�x�N�g����������

	p_Zirai = new Zirai;//�n���N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Zirai->Init();//�n���̏���������
	p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//�n���̏������W���Z�b�g

	p_Bakuhu = new Bakuhu;//�����N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Bakuhu->Init();//�����̏���������
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����̏������W���Z�b�g
	}

	p_AtariHantei = new AtariHantei;//�����蔻��N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_AtariHantei->Init();//�����蔻��̏���������
	p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//�����蔻��v���C���[�̏������W���Z�b�g
	p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//�����蔻��G�l�~�[�̏������W���Z�b�g
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�����蔻��]���r�̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_AtariHantei->SetItemPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//�����蔻��A�C�e���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_AtariHantei->SetRecoveryItemPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//�����蔻��񕜃A�C�e���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����蔻��n���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//�����蔻��e�̏������W���Z�b�g
	}
	p_AtariHantei->SetIePos(p_Ie->GetPos());//�����蔻��Ƃ̏������W���Z�b�g
	p_AtariHantei->SetIe2Pos(p_Ie2->GetPos());//�����蔻���2�̏������W���Z�b�g

	p_BoxAtariHantei = new BoxAtariHantei;//�o�E���f�B���O�{�b�N�X�����蔻��N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_BoxAtariHantei->Init();//�o�E���f�B���O�{�b�N�X�����蔻��̏���������

	p_UI = new UI;//UI�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_UI->Init();//UI�̏���������

	//p_Bonbe = new Bonbe;//�{���x�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	//p_Bonbe->Init();//�{���x�̏���������
	//p_Bonbe->SetBonbePos(0.0f, 0.0f, 5.0f);//�{���x�̍��W���Z�b�g

	//p_Bonbe2 = new Bonbe;//�{���x2�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	//p_Bonbe2->Init();//�{���x2�̏���������
	//p_Bonbe2->SetBonbePos(0.0f, 3.0f, 5.0f);//�{���x2�̍��W���Z�b�g


}

//==============
//  �I���֐�
//==============
void Manager::Uninit() 
{
	p_Camera->Uninit();//�J�����̏I������
	delete p_Camera;//�J�����N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_UAV->Uninit();//UAV�̏I������
	delete p_UAV;//UAV�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Player->Uninit();//�v���C���[�̏I������
	delete p_Player;//�v���C���[�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Ie->Uninit();//�Ƃ̏I������
	delete p_Ie;//�ƃN���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Ie2->Uninit();//��2�̏I������
	delete p_Ie2;//��2�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Enemy->Uninit();//�G�l�~�[�̏I������
	delete p_Enemy;//�G�l�~�[�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Zombie->Uninit();//�]���r�̏I������
	delete p_Zombie;//�]���r�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Zimen->Uninit();//�n�ʂ̏I������
	delete p_Zimen;//�n�ʃN���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_SkyDome->Uninit();//�X�J�C�h�[���̏I������
	delete p_SkyDome;//�X�J�C�h�[���N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Item->Uninit();//�A�C�e���̏I������
	delete p_Item;//�A�C�e���N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_RecoveryItem->Uninit();//�񕜃A�C�e���̏I������
	delete p_RecoveryItem;//�񕜃A�C�e���N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Tree->Uninit();//�؂̏I������
	delete p_Tree;//�؃N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Kusa1->Uninit();//��1�̏I������
	delete p_Kusa1;//��1�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Kusa2->Uninit();//��2�̏I������
	delete p_Kusa2;//��2�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Kusa3->Uninit();//��3�̏I������
	delete p_Kusa3;//��3�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Ame->Uninit();//�J�̏I������
	delete p_Ame;//�J�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_ItemMarker->Uninit();//�A�C�e���}�[�J�[�̏I������
	delete p_ItemMarker;//�A�C�e���}�[�J�[�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_RecoveryItemMarker->Uninit();//�񕜃A�C�e���}�[�J�[�̏I������
	delete p_RecoveryItemMarker;//�񕜃A�C�e���}�[�J�[�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_EnemyHPgage->Uninit();//�G�l�~�[HP�Q�[�W�̏I������
	delete p_EnemyHPgage;//�G�l�~�[HP�Q�[�W�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_ZombieHPgage->Uninit();//�]���rHP�Q�[�W�̏I������
	delete p_ZombieHPgage;//�]���rHP�Q�[�W�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_PlayerKage->Uninit();//�v���C���[�e�̏I������
	delete p_PlayerKage;//�v���C���[�e�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_EnemyKage->Uninit();//�G�l�~�[�e�̏I������
	delete p_EnemyKage;//�G�l�~�[�e�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_ZombieKage->Uninit();//�]���r�e�̏I������
	delete p_ZombieKage;//�]���r�e�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Shot->Uninit();//�e�̏I������
	delete p_Shot;//�e�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_Zirai->Uninit();//�n���̏I������
	delete p_Zirai;//�n���N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s
	
	p_Bakuhu->Uninit();//�����̏I������
	delete p_Bakuhu;//�����N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_AtariHantei->Uninit();//�����蔻��̏I������
	delete p_AtariHantei;//�����蔻��N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_BoxAtariHantei->Uninit();//�{�b�N�X�����蔻��̏I������
	delete p_BoxAtariHantei;//�{�b�N�X�����蔻��N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	p_UI->Uninit();//UI�̏I������
	delete p_UI;//UI�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s
	
	//p_Bonbe->Uninit();//�{���x�̏I������
	//delete p_Bonbe;//�{���x�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	//p_Bonbe2->Uninit();//�{���x2�̏I������
	//delete p_Bonbe2;//�{���x2�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	
}

//==============
//  �X�V�֐�
//==============
void Manager::Update()
{
	nflagTime++;

		if (nflag == 0 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10)//�����^�C�g����ʂ�������
		{

			//�T�E���h
			count0++;
			if (count0 > 0)
			{
				PlaySound(SOUND_LABEL_BGM004);//���y���Ȃ炷ok
			}
			count0 = 0;
			//�T�E���h


				nflag = 1;//�Q�[���v���C��ʂֈړ�
				nflagTime = 0;
		}

		if (nflag == 2 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10 || nflag == 3 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10)//�Q�[���N���A�[��ʂ܂��̓Q�[���I�[�o�[��ʂ�������
		{
				nflag = 0;//�^�C�g����ʂֈړ�
				nflagTime = 0;
		}

	//�^�C�g��
	if (nflag == 0)
	{

		ResetParameters();

		count3 = 0;//���y�p�ϐ��̏�����
		count4 = 0;//���y�p�ϐ��̏�����
		//�T�E���h
		StopSound(SOUND_LABEL_BGM008);//�T�E���h�̒�~
		StopSound(SOUND_LABEL_BGM009);//�T�E���h�̒�~
		if (count1 == 0)
		{
			PlaySound(SOUND_LABEL_BGM000);//���y���Ȃ炷
		}
		count1++;
		//�T�E���h
	}

	//�Q�[���v���C
	if (nflag == 1)
	{
		count1 = 0;//���y�p�ϐ��̏�����
		//�T�E���h
		StopSound(SOUND_LABEL_BGM000);//�T�E���h�̒�~
		if (count2 == 0)
		{
			PlaySound(SOUND_LABEL_BGM001);//���y���Ȃ炷
		}
		count2++;
		//�T�E���h

		p_UAV->Update();//UAV�̍X�V����

		p_Player->Update();//�v���C���[�̍X�V����
		p_Shot->SetPlayerFront(p_Player->GetFront());//�e�̑O�x�N�g���Ƀv���C���[�̑O�x�N�g�������鏈��
		p_Camera->SetPlayerMatrix(p_Player->GetMtxWorld());//�J�����̍s��Ƀv���C���[�̈ړ��Ɖ�]�̓��������[���h�s������鏈��

		p_Ie->Update();//�Ƃ̍X�V����

		p_Ie2->Update();//��2�̍X�V����

		p_Enemy->Update();//�G�l�~�[�̍X�V����
		p_Enemy->SetEnemyDraw(p_AtariHantei->GetEnemyDraw());//�G�l�~�[�̕`���Ԃ��X�V
		p_Enemy->SetPlayerPos(p_Player->GetPlayerPos());//�G�l�~�[�̒T�����W�Ƀv���C���[�̍��W�����鏈��

		p_Zombie->Update();//�]���r�̍X�V����
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_Zombie->SetZombieDraw(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieDraw(Loop));//�]���r�̕`���Ԃ��X�V
		}
		p_Zombie->SetPlayerPos(p_Player->GetPlayerPos());//�]���r�̒T�����W�Ƀv���C���[�̍��W�����鏈��

		p_Zimen->Update();//�n�ʂ̍X�V����

		p_SkyDome->Update();//�X�J�C�h�[���̍X�V����

		p_Item->Update();//�A�C�e���̍X�V����
		for (int Loop = 0; Loop < ITEM_NUM; Loop++)
		{
			p_Item->SetItemDraw(p_AtariHantei->GetItemLoop(Loop), p_AtariHantei->GetItemDraw(Loop));//�A�C�e���̕`���Ԃ��X�V
		}

		p_RecoveryItem->Update();//�񕜃A�C�e���̍X�V����
		for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
		{
			p_RecoveryItem->SetRecoveryItemDraw(p_AtariHantei->GetRecoveryItemLoop(Loop), p_AtariHantei->GetRecoveryItemDraw(Loop));//�񕜃A�C�e���̕`���Ԃ��X�V
		}

		p_Camera->Update();//�J�����̍X�V����

		p_Tree->Update();//�؂̍X�V����

		p_Kusa1->Update();//��1�̍X�V����

		p_Kusa2->Update();//��2�̍X�V����

		p_Kusa3->Update();//��3�̍X�V����

		p_Ame->Update();//�J�̍X�V����

		p_ItemMarker->Update();//�A�C�e���}�[�J�[�̍X�V����
		for (int Loop = 0; Loop < ITEM_NUM; Loop++)
		{
			p_ItemMarker->SetItemMarkerDraw(p_AtariHantei->GetItemLoop(Loop), p_AtariHantei->GetItemMarkerDraw(Loop));//�A�C�e���}�[�J�[�̕`���Ԃ��X�V
		}

		p_RecoveryItemMarker->Update();//�񕜃A�C�e���}�[�J�[�̍X�V����
		for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
		{
			p_RecoveryItemMarker->SetRecoveryItemMarkerDraw(p_AtariHantei->GetRecoveryItemLoop(Loop), p_AtariHantei->GetRecoveryItemMarkerDraw(Loop));//�A�C�e���}�[�J�[�̕`���Ԃ��X�V
		}

		p_EnemyHPgage->Update();//�G�l�~�[HP�Q�[�W�̍X�V����
		p_EnemyHPgage->SetEnemyPos(p_Enemy->GetEnemyPos());//�G�l�~�[HP�Q�[�W�̍��W�ɃG�l�~�[�̍��W������X�V����
		p_EnemyHPgage->SetNokoriEnemyHP(p_AtariHantei->GetEnemyHPgage());//�G�l�~�[HP�Q�[�W�̎c��c�ʂ�����X�V����

		p_ZombieHPgage->Update();//�]���rHP�Q�[�W�̍X�V����
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_ZombieHPgage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�]���rHP�Q�[�W�̍��W���X�V
			p_ZombieHPgage->SetNokoriZombieHP(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieHPgage(Loop));//�]���rHP�Q�[�W�̎c��c�ʂ�����X�V����
		}

		p_PlayerKage->SetPlayerPos(p_Player->GetPlayerPos());//�v���C���[�e�̍��W�Ƀv���C���[�̍��W������X�V����
		p_PlayerKage->Update();//�v���C���[�e�̍X�V����

		p_EnemyKage->Update();//�G�l�~�[�e�̍X�V����
		p_EnemyKage->SetEnemyKageDraw(p_AtariHantei->GetEnemyKageDraw());//�G�l�~�[�e�̕`���Ԃ��X�V
		p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//�G�l�~�[�e�̍��W�ɃG�l�~�[�̍��W������X�V����

		p_ZombieKage->Update();//�]���r�e�̍X�V����
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�]���r�e�̍��W���X�V
			p_ZombieKage->SetZombieKageDraw(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieKageDraw(Loop));//�]���r�e�̕`���Ԃ��X�V
		}

		p_Shot->Update();//�e�̍X�V����(1)[Shot.cpp �� true �� Shot.h]
		for (int Loop = 0; Loop < SHOT_NUM; Loop++)
		{
			p_AtariHantei->SetShotDraw(p_Shot->GetLoop(Loop), p_Shot->GetShotDraw(Loop));//�e�̕`���Ԃ��X�V(2)[Shot.h �� true �� AtariHantei.h]
			p_AtariHantei->SetShotAtariHantei(p_Shot->GetLoop(Loop), p_Shot->GetShotAtariHantei(Loop));//�e�̂����蔻��̏�Ԃ��X�V(2)[Shot.h �� true �� AtariHantei.h]

		}
		p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//�e�̍��W�Ƀv���C���[�̍��W������X�V����

		p_Zirai->Update();//�n���̍X�V����(1)[Zirai.cpp �� true �� Zirai.h]
		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_AtariHantei->SetZiraiDraw(p_Zirai->GetLoop(Loop), p_Zirai->GetZiraiDraw(Loop));//�n���̕`���Ԃ��X�V(2)[Zirai.h �� true �� AtariHantei.h]
			p_AtariHantei->SetZiraiAtariHantei(p_Zirai->GetLoop(Loop), p_Zirai->GetZiraiAtariHantei(Loop));//�n���̂����蔻��̏�Ԃ��X�V(2)[Zirai.h �� true �� AtariHantei.h]
		}
		p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//�n���̍��W�Ƀv���C���[�̍��W������X�V����

		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����̍��W���Z�b�g
			p_Bakuhu->SetBakuhuDraw(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetBakuhuDraw(Loop));
		}
		p_Bakuhu->Update();//�����̍X�V����

		p_AtariHantei->Update();//�����蔻��̍X�V����(3)[AtariHantei.cpp �� false �� AtariHantei.h]
		p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//�����蔻��v���C���[�̍��W�Ƀv���C���[�̍��W������X�V����
		p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//�����蔻��G�l�~�[�̍��W�ɃG�l�~�[�̍��W������X�V����
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�����蔻��]���r�̍��W�Ƀ]���r�̍��W������X�V����
		}
		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����蔻��n���̍��W�ɒn���̍��W������X�V����

			p_Zirai->SetZiraiDraw(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetZiraiDraw(Loop));//�n���̕`���Ԃ��X�V(4)[AtariHantei.h �� false �� Zirai.h]
			p_Zirai->SetZiraiAtariHantei(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetZiraiAtariHantei(Loop));//�n���̂����蔻��̏�Ԃ��X�V(4)[AtariHantei.h �� false �� Zirai.h]

		}
		for (int Loop = 0; Loop < SHOT_NUM; Loop++)
		{
			p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//�����蔻��e�̍��W�ɒe�̍��W������X�V����

			p_Shot->SetShotDraw(p_AtariHantei->GetShotLoop(Loop), p_AtariHantei->GetShotDraw(Loop));//�e�̕`���Ԃ��X�V(4)[AtariHantei.h �� false �� Shot.h]
			p_Shot->SetShotAtariHantei(p_AtariHantei->GetShotLoop(Loop), p_AtariHantei->GetShotAtariHantei(Loop));//�e�̂����蔻��̏�Ԃ��X�V(4)[AtariHantei.h �� false �� Shot.h]
		}
		p_Shot->SetTamaHuyasu(p_AtariHantei->Getammunition());//����������e�𑝂₷����


		p_BoxAtariHantei->SetPlayerMin(p_Player->GetPlayerMin());//�{�b�N�X�����蔻��Ƀv���C���[�̍ŏ����_�𑗂�
		p_BoxAtariHantei->SetPlayerMax(p_Player->GetPlayerMax());//�{�b�N�X�����蔻��Ƀv���C���[�̍ő咸�_�𑗂�
		p_BoxAtariHantei->SetIeMin(p_Ie->GetIeMin());//�{�b�N�X�����蔻��ɉƂ̍ŏ����_�𑗂�
		p_BoxAtariHantei->SetIeMax(p_Ie->GetIeMax());//�{�b�N�X�����蔻��ɉƂ̍ő咸�_�𑗂�
		p_BoxAtariHantei->SetIe2Min(p_Ie2->GetIeMin());//�{�b�N�X�����蔻��ɉ�2�̍ŏ����_�𑗂�
		p_BoxAtariHantei->SetIe2Max(p_Ie2->GetIeMax());//�{�b�N�X�����蔻��ɉ�2�̍ő咸�_�𑗂�
		p_BoxAtariHantei->Update();//�o�E���f�B���O�{�b�N�X�����蔻��̍X�V����
		p_Player->SetPlayerIeBoxAtari(p_BoxAtariHantei->GetPlayerIeBoxAtari());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�
		p_Player->SetPlayerIe2BoxAtari(p_BoxAtariHantei->GetPlayerIe2BoxAtari());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�
		p_Player->SetPlayerSita(p_BoxAtariHantei->GetPlayerSita());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�
		p_Player->SetPlayerUe(p_BoxAtariHantei->GetPlayerUe());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�
		p_Player->SetPlayerMigi(p_BoxAtariHantei->GetPlayerMigi());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�
		p_Player->SetPlayerHidari(p_BoxAtariHantei->GetPlayerHidari());//�v���C���[�Ƀ{�b�N�X�����蔻��̌��ʂ𑗂�

		//p_Bonbe->Update();//�{���x�̍X�V����

		//p_Bonbe2->Update();//�{���x�̍X�V����

		SetZombieNokori(p_AtariHantei->GetZombieNokori());
		SetEnemyNokori(p_AtariHantei->GetEnemyNokori());
		//�c��̃]���r����0���G�l�~�[����0�Ȃ�
		if (ZombieNokori == 0 && EnemyNokori == 0 && test == false) 
		{
			nflag = 2;//�Q�[���N���A�[�Ɉړ�
		}
		SetHP_UI(p_AtariHantei->GetHP());//HP�c��
		//HP�_���[�W��256���z������
		if (HP_UI >= 256 && test == false)
		{
			nflag = 3;//�Q�[���I�[�o�[�Ɉړ�
		}
	}

	//�Q�[���N���A�[
	if (nflag == 2)
	{
		count2 = 0;//���y�p�ϐ��̏�����
		//�T�E���h
		StopSound(SOUND_LABEL_BGM001);//�T�E���h�̒�~
		if (count3 == 0)
		{
			PlaySound(SOUND_LABEL_BGM008);//���y���Ȃ炷
		}
		count3++;
		//�T�E���h

		//test = true;
	}

	//�Q�[���I�[�o�[
	if (nflag == 3)
	{
		count2 = 0;//���y�p�ϐ��̏�����
		//�T�E���h
		StopSound(SOUND_LABEL_BGM001);//�T�E���h�̒�~
		if (count4 == 0)
		{
			PlaySound(SOUND_LABEL_BGM009);//���y���Ȃ炷
		}
		count4++;
		//�T�E���h

		//test = true;
	}

}

//==============
//  �`��֐�
//==============
void Manager::Draw() 
{
	//�^�C�g��
	if (nflag == 0)
	{

		//�^�C�g�����
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			10,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			1280,//���̉摜�̐؂��肽����
			720 //���̉摜�̐؂��肽������
		);

		//�^�C�g�����
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			7,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			800,//���̉摜�̐؂��肽����
			600 //���̉摜�̐؂��肽������
		);

		//�e�N�X�`���s�R�s�R
		g_nCnt++;
		if (g_nCnt % 60 == 0)
		{
			switch (g_bPress)
			{
			case false:
				g_bPress = true;
				break;
			case true:
				g_bPress = false;
				break;
			}
		}

		if (g_bPress == true)
		{
			p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
			p_UI->Draw(
				5,//�g���e�N�X�`��,
				15.0f,//x���W,
				0.0f,//y���W,
				1500,//�e�N�X�`���̕\�����鉡�̒���,//���̉摜�̉��̒�����32
				1000,//�e�N�X�`���̕\������c�̒���,//���̉摜�̏c�̒�����32
				0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
				0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
				800,//���̉摜�̐؂��肽����
				600 //���̉摜�̐؂��肽������
			);
		}
		//�e�N�X�`���s�R�s�R
	}

	//�Q�[���v���C
	if (nflag == 1)
	{
		p_UAV->Draw();//UAV�̕`�揈��

		p_Player->Draw();//Player�̕`�揈��

		p_Ie->Draw();//�Ƃ̕`�揈��

		p_Ie2->Draw();//��2�̕`�揈��

		p_Enemy->Draw();//�G�l�~�[�̕`�揈��

		p_Zombie->Draw();//�]���r�̕`�揈��

		p_Zimen->Draw();//�n�ʂ̕`�揈��

		p_SkyDome->Draw();//�X�J�C�h�[���̕`�揈��

		p_Item->Draw();//�A�C�e���̕`�揈��

		p_RecoveryItem->Draw();//�񕜃A�C�e���̕`�揈��

		p_Tree->Draw();//�؂̕`�揈��

		p_Kusa1->Draw();//��1�̕`�揈��

		p_Kusa2->Draw();//��2�̕`�揈��

		p_Kusa3->Draw();//��3�̕`�揈��

		p_Ame->Draw();//�J�̕`�揈��

		p_ItemMarker->Draw();//�A�C�e���}�[�J�[�̕`�揈��

		p_RecoveryItemMarker->Draw();//�񕜃A�C�e���}�[�J�[�̕`�揈��

		p_EnemyHPgage->Draw();//�G�l�~�[HP�Q�[�W�̕`�揈��

		p_ZombieHPgage->Draw();//�]���rHP�Q�[�W�̕`�揈��

		p_PlayerKage->Draw();//Player�e�̕`�揈��

		p_EnemyKage->Draw();//�G�l�~�[�e�̕`�揈��

		p_ZombieKage->Draw();//�]���r�e�̕`�揈��

		p_Shot->Draw();//�e�̕`�揈��

		p_Zirai->Draw();//�n���̕`�揈��

		p_Bakuhu->Draw();//�����̕`�揈��

		//p_Bonbe->Draw();//�{���x�̕`�揈��

		//p_Bonbe2->Draw();//�{���x�̕`�揈��


		//�����Y�t���A
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			0,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			3500,//���̉摜�̐؂��肽����
			2333 //���̉摜�̐؂��肽������
		);

		//�����Y�t���A
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			1,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			3500,//���̉摜�̐؂��肽����
			2333 //���̉摜�̐؂��肽������
		);

		//�����Y�t���A
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			2,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			3500,//���̉摜�̐؂��肽����
			2333 //���̉摜�̐؂��肽������
		);

		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 100));//�|���S���J���[�̐ݒ�
		p_UI->Draw(11, 0, 700, 400, 260, 0, 0, 128, 128);//2D�摜(UI)��\��//UI�͈�ԉ��ɂ��Ȃ��Ɖ摜�������Ă��܂��B
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(3, 15, 700, 500, 250, 0, 0, 1000, 500);//2D�摜(UI)��\��//UI�͈�ԉ��ɂ��Ȃ��Ɖ摜�������Ă��܂��B
		SetTPS_UI(p_Camera->GetTPS());//�J�������猨�z�����ǂ����������Ă��鏈��
		if (TPS_UI == true)
		{
			p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
			p_UI->Draw(6, 480, 300, 500, 500, 0, 0, 500, 500);//2D�摜(UI)��\��//UI�͈�ԉ��ɂ��Ȃ��Ɖ摜�������Ă��܂��B

		}
		#ifdef _DEBUG
		p_UI->DrawScore(ZombieNokori, 3, 30.0f, 30.0f, true);//�c��̃]���r����\��
		p_UI->DrawScore(EnemyNokori, 3, 30.0f, 100.0f, true);//�c��̓G����\��
		p_UI->DrawScore(HP_UI, 3, 30.0f, 170.0f, true);//�c���HP��\��
		#endif // DEBUG
		SetShot_UI(p_Shot->GetShot_UI());
		p_UI->DrawScore(Shot_UI, 3, 1285.0f, 870.0f, true);//�e����\��
		SetZirai_UI(p_Zirai->GetZirai_UI());
		p_UI->DrawScore(Zirai_UI, 1, 1410.0f, 790.0f, true);//�n������\��
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(12, 1200, 860, 300, 5, 0, 0, 300, 300);//2D�摜(UI)��\��//UI�͈�ԉ��ɂ��Ȃ��Ɖ摜�������Ă��܂��B

	}

	//�Q�[���N���A�[
	if (nflag == 2)
	{
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			8,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			1280,//���̉摜�̐؂��肽����
			720 //���̉摜�̐؂��肽������
		);
	}

	//�Q�[���I�[�o�[
	if (nflag == 3)
	{
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//�|���S���J���[�̐ݒ�
		p_UI->Draw(
			9,//�g���e�N�X�`��,
			0.0f, //x���W,
			0.0f,//y���W,
			1500,//�e�N�X�`���̕\�����鉡�̒���
			1000,//�e�N�X�`���̕\������c�̒���
			0,//���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
			0,//���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
			1280,//���̉摜�̐؂��肽����
			720 //���̉摜�̐؂��肽������
		);
	}
}

void Manager::ResetParameters()
{
	SetZombieNokori(p_AtariHantei->GetZombieNokori());
	SetEnemyNokori(p_AtariHantei->GetEnemyNokori());

	p_Zombie->ResetParameters();

	p_ZombieKage->ResetParameters();
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�]���r�e�̏������W���Z�b�g
	}

	p_Enemy->ResetParameters();

	p_EnemyKage->ResetParameters();
	p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//�G�l�~�[�e�̏������W���Z�b�g

	p_Item->ResetParameters();

	p_ItemMarker->ResetParameters();
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_ItemMarker->SetPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//�A�C�e���}�[�J�[�̍��W���Z�b�g
	}

	p_RecoveryItem->ResetParameters();

	p_RecoveryItemMarker->ResetParameters();
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_RecoveryItemMarker->SetPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//�񕜃A�C�e���}�[�J�[�̍��W���Z�b�g
	}

	p_Player->ResetParameters();
	p_Player->SetPlayerPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�ړ��p���l������

	p_Shot->ResetParameters();
	p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//�e�̏������W���Z�b�g
	p_Shot->SetPlayerFront(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�e�̑O�x�N�g����������

	p_Zirai->ResetParameters();
	p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//�n���̏������W���Z�b�g

	p_Bakuhu->ResetParameters();
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����̏������W���Z�b�g
	}

	p_AtariHantei->ResetParameters();
	p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//�����蔻��v���C���[�̏������W���Z�b�g
	p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//�����蔻��G�l�~�[�̏������W���Z�b�g
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//�����蔻��]���r�̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_AtariHantei->SetItemPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//�����蔻��A�C�e���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_AtariHantei->SetRecoveryItemPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//�����蔻��񕜃A�C�e���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//�����蔻��n���̏������W���Z�b�g
	}
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//�����蔻��e�̏������W���Z�b�g
	}


}