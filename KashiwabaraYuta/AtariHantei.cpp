//=======================================================================================
//						�����蔻��`��
//						2017.06.05
//=======================================================================================
#include <math.h>
#include "AtariHantei.h"
#include "Main.h"
#include "sound.h"


AtariHantei::AtariHantei()
{
}


AtariHantei::~AtariHantei()
{
}

bool AtariHantei::atari(float PlayerX, float PlayerY, float PlayerZ, float PlayerHankei, float ItemX, float ItemY, float ItemZ, float ItemHankei)
{

	float x = PlayerX - ItemX; //������x���W - �G��x���W = x�̎����ƓG�̋������o��
	float y = PlayerY - ItemY; //������y���W - �G��y���W = y�̎����ƓG�̋������o��
	float z = PlayerZ - ItemZ; //������z���W - �G��z���W = z�̎����ƓG�̋������o��

	float PlayerItemKixyori = x * x + y * y + z * z; //��ӂ�2�� + �Εӂ�2�� = �Εӂ�2�悪�ł�(�����ƓG�̋������o��)

	float PlayerItemHankei = PlayerHankei + ItemHankei; //�����ƓG�̔��a�𑫂����������o��

	return PlayerItemKixyori < (PlayerItemHankei * PlayerItemHankei); //�����ƓG�̋��� < �����ƓG�̔��a�𑫂������� ��2��(�������r���G�Ǝ����̔��a�𑫂������������������ꍇTrue��Ԃ�)
}

void AtariHantei::Init(void)
{
	//�T�E���h
	oto0 = 0;//���y�p�ϐ�������
	oto1 = 0;//���y�p�ϐ�������

	ZombieNokori = ZOMBIE_NUM;//�]���r�̎c�萔
	EnemyNokori = ENEMY_NUM;//�G�̎c�萔

	HP = HP_NUM;//�c��HP

	//�A�C�e��
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		Itematari[Loop].bHit = false;
		Itematari[Loop].posx = 0;
		Itematari[Loop].posy = 0;
		Itematari[Loop].posz = 0;
		Itematari[Loop].ItemDraw = true;//�A�C�e���̕`����
		Itematari[Loop].ItemMarkerDraw = true;//�A�C�e���}�[�J�[�̕`����
		Itematari[Loop].ItemAtariHantei = true;//�����蔻���ON!
	}

	//�񕜃A�C�e��
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		RecoveryItematari[Loop].bHit = false;
		RecoveryItematari[Loop].posx = 0;
		RecoveryItematari[Loop].posy = 0;
		RecoveryItematari[Loop].posz = 0;
		RecoveryItematari[Loop].ItemDraw = true;//�A�C�e���̕`����
		RecoveryItematari[Loop].ItemMarkerDraw = true;//�A�C�e���}�[�J�[�̕`����
		RecoveryItematari[Loop].ItemAtariHantei = true;//�����蔻���ON!
	}

	//�]���r
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		Zombieatari[Loop].bHit = false;
		Zombieatari[Loop].posx = 0;
		Zombieatari[Loop].posy = 0;
		Zombieatari[Loop].posz = 0;
		Zombieatari[Loop].ZombieDraw = true;//�]���r�̕`����
		Zombieatari[Loop].ZombieKageDraw = true;//�]���r�e�̕`����
		Zombieatari[Loop].ZombieAtariHantei = true;//�����蔻���ON!
		Zombieatari[Loop].ZombieHP = 100.0f;//�]���r��HP���
	}
	ZombieNokori = ZOMBIE_NUM;//�c��̃]���r��������

	//�G
	EnemyDraw = true;//�G�l�~�[�̕`�揉����
	EnemyKageDraw = true;//�G�l�~�[�e�̕`�揉����
	EnemyAtariHantei = true;//�����蔻���ON!
	EnemyNokori = ENEMY_NUM;//�G�̎c�萔������
	EnemyHP = 200.0f;//�G�l�~�[��HP������

	//�n��
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		Ziraiatari[Loop].bHit = false;
		Ziraiatari[Loop].posx = 0;
		Ziraiatari[Loop].posy = 50;
		Ziraiatari[Loop].posz = 0;
		Ziraiatari[Loop].Draw = false;//�`����
		Ziraiatari[Loop].AtariHantei = false;//�����蔻���OFF
		Ziraiatari[Loop].BakuhuDraw = false;//�����̕`���true�ɂ���
	}

	//�e(Shot)
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//�\���̂̐������� 
	{
		Shotatari[Loop].bHit = false;
		Shotatari[Loop].posx = 0;
		Shotatari[Loop].posy = 50;
		Shotatari[Loop].posz = 0;
		Shotatari[Loop].Draw = false;//�`����
		Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
	}
}

void AtariHantei::Update(void)
{
	//�v���C���[ & �A�C�e��//////////////////////////////////////////

	ammunition = 0;//�񕜂�����e�򐔂�������

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (Itematari[Loop].ItemAtariHantei == true)
		{
			Itematari[Loop].bHit = atari(//atarihantei.h//�����蔻��
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//�v���C���[�̈ʒu
				Itematari[Loop].posx, Itematari[Loop].posy, Itematari[Loop].posz, 0.5//�{���x�̈ʒu
			);
			if (Itematari[Loop].bHit == true)
			{
				//���������ꍇ�̏���

				//�T�E���h
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM005);//���y���Ȃ炷ok
				}
				oto1 = 0;
				//�T�E���h

				//�A�C�e��
				Itematari[Loop].ItemDraw = false;//�A�C�e���̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
				Itematari[Loop].ItemAtariHantei = false;//�����蔻���OFF
				Itematari[Loop].ItemMarkerDraw = false;//�A�C�e���}�[�J�[���\���ɂ�����e�𑗂�
				
				//�e(Shot)				
				ammunition = 10;//�񕜂�����e��

				for (Loop = 0; Loop < SHOT_NUM; Loop++)//�\���̂̐������� 
				{
					Shotatari[Loop].bHit = false;
					Shotatari[Loop].posx = 0;
					Shotatari[Loop].posy = 50;
					Shotatari[Loop].posz = 0;
					Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
				}
				//�e(Shot)

			}
		}
	}
	//�v���C���[ & �A�C�e��//////////////////////////////////////////

	//�v���C���[ & �񕜃A�C�e��//////////////////////////////////////////

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (RecoveryItematari[Loop].ItemAtariHantei == true)
		{
			RecoveryItematari[Loop].bHit = atari(//atarihantei.h//�����蔻��
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//�v���C���[�̈ʒu
				RecoveryItematari[Loop].posx, RecoveryItematari[Loop].posy, RecoveryItematari[Loop].posz, 0.5//�{���x�̈ʒu
			);
			if (RecoveryItematari[Loop].bHit == true)
			{
				//���������ꍇ�̏���

				//�T�E���h
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM015);//���y���Ȃ炷ok
				}
				oto1 = 0;
				//�T�E���h

				//�A�C�e��
				RecoveryItematari[Loop].ItemDraw = false;//�A�C�e���̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
				RecoveryItematari[Loop].ItemAtariHantei = false;//�����蔻���OFF
				RecoveryItematari[Loop].ItemMarkerDraw = false;//�A�C�e���}�[�J�[���\���ɂ�����e�𑗂�

				HP = HP - HP_NUM;//HP��
				if (HP <= HP_NUM)//HP��64�ȉ��̏ꍇ
				{
					HP = HP_NUM;//HP��64�ɂ���
				}

			}
		}
	}
	//�v���C���[ & �񕜃A�C�e��//////////////////////////////////////////

	//�v���C���[ & �]���r//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		if (Zombieatari[Loop].ZombieAtariHantei == true) //�����蔻�肪ON��������
		{
			Zombieatari[Loop].bHit = atari(//atarihantei.h//�����蔻��
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//�v���C���[�̈ʒu
				Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//�]���r�̈ʒu
			);
			if (Zombieatari[Loop].bHit == true)
			{
				//���������ꍇ�̏���

				//�T�E���h
				oto0++;
				if (oto0 > 0)
				{
					PlaySound(SOUND_LABEL_BGM013);//���y���Ȃ炷ok
				}
				oto0 = 0;
				//�T�E���h

				Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 100;
				if (Zombieatari[Loop].ZombieHP <= 0)
				{
					//�]���r
					Zombieatari[Loop].ZombieDraw = false;//�]���r�̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
					Zombieatari[Loop].ZombieAtariHantei = false;//�����蔻���OFF
					ZombieNokori = ZombieNokori - 1;//�]���r�̎c�萔��-1����
					Zombieatari[Loop].ZombieKageDraw = false;//�]���r�̉e�`����\���ɂ��ē��e�𑗂�
				}

				HP = HP + HP_NUM;//HP�Ƀ_���[�W
				if (HP >= 256)//HP��256�ȏ�̏ꍇ
				{
					HP = 256;//HP��256�ɂ���
				}
			}
		}
	}
	//�v���C���[ & �]���r//////////////////////////////////////////

	//�v���C���[ & �G//////////////////////////////////////////
	if (EnemyAtariHantei == true)//�G�̂����蔻�肪ON��������
	{
		bool bHit1 = atari(//atarihantei.h//�����蔻��
			EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5,//�G�̈ʒu
			PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5//�v���C���[�̈ʒu
		);
		if (bHit1 == true)
		{
			//���������ꍇ�̏���

			//�T�E���h
			oto0++;
			if (oto0 > 0)
			{
				PlaySound(SOUND_LABEL_BGM013);//���y���Ȃ炷ok
			}
			oto0 = 0;
			//�T�E���h

			EnemyHP = EnemyHP - 200.0f;
			if (EnemyHP <= 0)
			{
				//�G
				EnemyDraw = false;//�G�̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
				EnemyAtariHantei = false;//�����蔻���OFF
				EnemyNokori = EnemyNokori - 1;//�G�̎c�萔��-1����
				EnemyKageDraw = false;//�G�l�~�[�̉A��OFF�ɂ���
			}

			HP = HP + HP_NUM;//HP�Ƀ_���[�W
			if (HP >= 256)//HP��256�ȏ�̏ꍇ
			{
				HP = 256;//HP��256�ɂ���
			}
		}
	}
	//�v���C���[ & �G//////////////////////////////////////////

	//�n�� & �G//////////////////////////////////////////
	for (int Loop2 = 0; Loop2 < ZIRAI_NUM; Loop2++)//�n���\���̂̐������� 
	{
		if (EnemyAtariHantei == true)//�G�̂����蔻�肪ON��������
		{
			if (Ziraiatari[Loop2].AtariHantei == true) //�n���̂����蔻�肪ON��������
			{
				bool bHit1 = atari(//atarihantei.h//�����蔻��
					Ziraiatari[Loop2].posx, Ziraiatari[Loop2].posy, Ziraiatari[Loop2].posz, 1.0,//�n���̈ʒu
					EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5//�G�̈ʒu
				);
				if (bHit1 == true)
				{
					//���������ꍇ�̏���

					//�T�E���h
					oto0++;
					if (oto0 > 0)
					{
						PlaySound(SOUND_LABEL_BGM012);//���y���Ȃ炷ok
					}
					oto0 = 0;
					oto1++;
					if (oto1 > 0)
					{
						PlaySound(SOUND_LABEL_BGM007);//���y���Ȃ炷ok
					}
					oto1 = 0;
					//�T�E���h

					//�n��
					Ziraiatari[Loop2].AtariHantei = false;//�����蔻���OFF
					Ziraiatari[Loop2].Draw = false;//�n���̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
					Ziraiatari[Loop2].BakuhuDraw = true;//�����̕`���true�ɂ���

					EnemyHP = EnemyHP - 200;
					if (EnemyHP <= 0)
					{
						//�G
						EnemyDraw = false;//�G�̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
						EnemyAtariHantei = false;//�����蔻���OFF
						EnemyNokori = EnemyNokori - 1;//�G�̎c�萔��-1����
						EnemyKageDraw = false;//�G�l�~�[�̉A��OFF�ɂ���
					}
				}
			}
		}
	}
	//�n�� & �G//////////////////////////////////////////

	//�G & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//�e�\���̂̐������� 
	{
		if (EnemyAtariHantei == true)//�G�̂����蔻�肪ON��������
		{
			if (Shotatari[Loop].AtariHantei == true) //�e�̂����蔻�肪ON��������
			{
				bool bHit1 = atari(//atarihantei.h//�����蔻��
					EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5,//�G�̈ʒu
					Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shot�̈ʒu
				);
				if (bHit1)
				{
					//���������ꍇ�̏���

					//�T�E���h
					oto1++;
					if (oto1 > 0)
					{
						PlaySound(SOUND_LABEL_BGM003);//���y���Ȃ炷ok
					}
					oto1 = 0;
					//�T�E���h

					EnemyHP = EnemyHP - 10;
					if (EnemyHP <= 0)
					{
						//�G
						EnemyDraw = false;//�G�̕`����\���ɂ��ē��e��Enemy.cpp�ɑ���
						EnemyAtariHantei = false;//�����蔻���OFF
						EnemyNokori = EnemyNokori - 1;//�G�̎c�萔��-1����
						EnemyKageDraw = false;//�G�l�~�[�̉A��OFF�ɂ���
					}

					//�e(Shot)
					Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
					Shotatari[Loop].Draw = false;//�e�̕`����\���ɂ��ē��e��Shot.cpp�ɑ���
				}
			}
		}
	}
	//�G & Shot//////////////////////////////////////////

	//�n�� & �]���r//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�]���r�\���̂̐������� 
	{
		for (int Loop2 = 0; Loop2 < ZIRAI_NUM; Loop2++)//�n���\���̂̐������� 
		{
			if (Zombieatari[Loop].ZombieAtariHantei == true) //�]���r�̂����蔻�肪ON��������
			{
				if (Ziraiatari[Loop2].AtariHantei == true) //�n���̂����蔻�肪ON��������
				{
					Zombieatari[Loop].bHit = atari(//atarihantei.h//�����蔻��
						Ziraiatari[Loop2].posx, Ziraiatari[Loop2].posy, Ziraiatari[Loop2].posz, 1.0,//�n���̈ʒu
						Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//�]���r�̈ʒu
					);
					if (Zombieatari[Loop].bHit == true)
					{
						//���������ꍇ�̏���

						//�T�E���h
						oto0++;
						if (oto0 > 0)
						{
							PlaySound(SOUND_LABEL_BGM012);//���y���Ȃ炷ok
						}
						oto0 = 0;
						oto1++;
						if (oto1 > 0)
						{
							PlaySound(SOUND_LABEL_BGM007);//���y���Ȃ炷ok
						}
						oto1 = 0;
						//�T�E���h

						Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 100;
						if (Zombieatari[Loop].ZombieHP <= 0)
						{
							//�]���r
							Zombieatari[Loop].ZombieDraw = false;//�]���r�̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
							Zombieatari[Loop].ZombieAtariHantei = false;//�����蔻���OFF
							ZombieNokori = ZombieNokori - 1;//�]���r�̎c�萔��-1����
							Zombieatari[Loop].ZombieKageDraw = false;//�]���r�̉e�`����\���ɂ��ē��e�𑗂�
						}
						//�n��
						Ziraiatari[Loop2].AtariHantei = false;//�����蔻���OFF
						Ziraiatari[Loop2].Draw = false;//�n���̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
						Ziraiatari[Loop2].BakuhuDraw = true;//�����̕`���true�ɂ���
					}
				}
			}
		}
	}
	//�n�� & �]���r//////////////////////////////////////////

	//Shot & �]���r//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�]���r�\���̂̐������� 
	{
		for (int Loop2 = 0; Loop2 < SHOT_NUM; Loop2++)//�e�\���̂̐������� 
		{
			if (Zombieatari[Loop].ZombieAtariHantei == true) //�]���r�̂����蔻�肪ON��������
			{
				if (Shotatari[Loop2].AtariHantei == true) //�e�̂����蔻�肪ON��������
				{
					Zombieatari[Loop].bHit = atari(//atarihantei.h//�����蔻��
						Shotatari[Loop2].posx, Shotatari[Loop2].posy, Shotatari[Loop2].posz, 0.1,//�e�̈ʒu
						Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//�]���r�̈ʒu
					);
					if (Zombieatari[Loop].bHit == true)
					{
						//���������ꍇ�̏���

						//�T�E���h
						oto1++;
						if (oto1 > 0)
						{
							PlaySound(SOUND_LABEL_BGM003);//���y���Ȃ炷ok
						}
						oto1 = 0;
						//�T�E���h

						Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 10;
						if (Zombieatari[Loop].ZombieHP <= 0)
						{
							//�]���r
							Zombieatari[Loop].ZombieDraw = false;//�]���r�̕`����\���ɂ��ē��e��Manager.cpp�ɑ���
							Zombieatari[Loop].ZombieAtariHantei = false;//�����蔻���OFF
							ZombieNokori = ZombieNokori - 1;//�]���r�̎c�萔��-1����
							Zombieatari[Loop].ZombieKageDraw = false;//�]���r�̉e�`����\���ɂ��ē��e�𑗂�
						}
						//�e(Shot)
						Shotatari[Loop2].AtariHantei = false;//�����蔻���OFF
						Shotatari[Loop2].Draw = false;//�e�̕`����\���ɂ��ē��e��Shot.cpp�ɑ���

					}
				}
			}
		}
	}
	//Shot & �]���r//////////////////////////////////////////

	//�� & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//�e�\���̂̐������� 
	{
		if (Shotatari[Loop].AtariHantei == true) //�e�̂����蔻�肪ON��������
		{
			bool bHit1 = atari(//atarihantei.h//�����蔻��
				IePos.x, IePos.y, IePos.z, 2.5,//�G�̈ʒu
				Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shot�̈ʒu
			);
			if (bHit1)
			{
				//���������ꍇ�̏���

				//�T�E���h
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM014);//���y���Ȃ炷ok
				}
				oto1 = 0;
				//�T�E���h

				//�e(Shot)
				Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
				Shotatari[Loop].Draw = false;//�e�̕`����\���ɂ��ē��e��Shot.cpp�ɑ���
			}
		}
	}
	//�� & Shot//////////////////////////////////////////

	//��2 & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//�e�\���̂̐������� 
	{
		if (Shotatari[Loop].AtariHantei == true) //�e�̂����蔻�肪ON��������
		{
			bool bHit1 = atari(//atarihantei.h//�����蔻��
				Ie2Pos.x, Ie2Pos.y, Ie2Pos.z, 2.5,//�G�̈ʒu
				Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shot�̈ʒu
			);
			if (bHit1)
			{
				//���������ꍇ�̏���

				//�T�E���h
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM014);//���y���Ȃ炷ok
				}
				oto1 = 0;
				//�T�E���h

				//�e(Shot)
				Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
				Shotatari[Loop].Draw = false;//�e�̕`����\���ɂ��ē��e��Shot.cpp�ɑ���
			}
		}
	}
	//��2 & Shot//////////////////////////////////////////

}


void AtariHantei::Uninit(void) 
{

}

void AtariHantei::ResetParameters(void)
{
	//�T�E���h
	oto0 = 0;//���y�p�ϐ�������
	oto1 = 0;//���y�p�ϐ�������

	ZombieNokori = ZOMBIE_NUM;//�]���r�̎c�萔
	EnemyNokori = ENEMY_NUM;//�G�̎c�萔

	HP = HP_NUM;//�c��HP

	//�A�C�e��
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		Itematari[Loop].bHit = false;
		Itematari[Loop].posx = 0;
		Itematari[Loop].posy = 0;
		Itematari[Loop].posz = 0;
		Itematari[Loop].ItemDraw = true;//�A�C�e���̕`����
		Itematari[Loop].ItemMarkerDraw = true;//�A�C�e���}�[�J�[�̕`����
		Itematari[Loop].ItemAtariHantei = true;//�����蔻���ON!
	}

	//�񕜃A�C�e��
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		RecoveryItematari[Loop].bHit = false;
		RecoveryItematari[Loop].posx = 0;
		RecoveryItematari[Loop].posy = 0;
		RecoveryItematari[Loop].posz = 0;
		RecoveryItematari[Loop].ItemDraw = true;//�A�C�e���̕`����
		RecoveryItematari[Loop].ItemMarkerDraw = true;//�A�C�e���}�[�J�[�̕`����
		RecoveryItematari[Loop].ItemAtariHantei = true;//�����蔻���ON!
	}

	//�]���r
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		Zombieatari[Loop].bHit = false;
		Zombieatari[Loop].posx = 0;
		Zombieatari[Loop].posy = 0;
		Zombieatari[Loop].posz = 0;
		Zombieatari[Loop].ZombieDraw = true;//�]���r�̕`����
		Zombieatari[Loop].ZombieKageDraw = true;//�]���r�e�̕`����
		Zombieatari[Loop].ZombieAtariHantei = true;//�����蔻���ON!
		Zombieatari[Loop].ZombieHP = 100.0f;//�]���r��HP���
	}
	ZombieNokori = ZOMBIE_NUM;//�c��̃]���r��������

	//�G
	EnemyDraw = true;//�G�l�~�[�̕`�揉����
	EnemyKageDraw = true;//�G�l�~�[�e�̕`�揉����
	EnemyAtariHantei = true;//�����蔻���ON!
	EnemyNokori = ENEMY_NUM;//�G�̎c�萔������
	EnemyHP = 200.0f;//�G�l�~�[��HP������

	//�n��
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		Ziraiatari[Loop].bHit = false;
		Ziraiatari[Loop].posx = 0;
		Ziraiatari[Loop].posy = 50;
		Ziraiatari[Loop].posz = 0;
		Ziraiatari[Loop].Draw = false;//�`����
		Ziraiatari[Loop].AtariHantei = false;//�����蔻���OFF
		Ziraiatari[Loop].BakuhuDraw = false;//�����̕`���true�ɂ���
	}

	//�e(Shot)
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//�\���̂̐������� 
	{
		Shotatari[Loop].bHit = false;
		Shotatari[Loop].posx = 0;
		Shotatari[Loop].posy = 50;
		Shotatari[Loop].posz = 0;
		Shotatari[Loop].Draw = false;//�`����
		Shotatari[Loop].AtariHantei = false;//�����蔻���OFF
	}
}