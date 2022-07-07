//=======================================================================================
//						あたり判定描画
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

	float x = PlayerX - ItemX; //自分のx座標 - 敵のx座標 = xの自分と敵の距離を出す
	float y = PlayerY - ItemY; //自分のy座標 - 敵のy座標 = yの自分と敵の距離を出す
	float z = PlayerZ - ItemZ; //自分のz座標 - 敵のz座標 = zの自分と敵の距離を出す

	float PlayerItemKixyori = x * x + y * y + z * z; //底辺の2乗 + 対辺の2乗 = 斜辺の2乗がでる(自分と敵の距離を出す)

	float PlayerItemHankei = PlayerHankei + ItemHankei; //自分と敵の半径を足した長さを出す

	return PlayerItemKixyori < (PlayerItemHankei * PlayerItemHankei); //自分と敵の距離 < 自分と敵の半径を足した長さ の2乗(長さを比較し敵と自分の半径を足した長さよりも小さい場合Trueを返す)
}

void AtariHantei::Init(void)
{
	//サウンド
	oto0 = 0;//音楽用変数初期化
	oto1 = 0;//音楽用変数初期化

	ZombieNokori = ZOMBIE_NUM;//ゾンビの残り数
	EnemyNokori = ENEMY_NUM;//敵の残り数

	HP = HP_NUM;//残りHP

	//アイテム
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		Itematari[Loop].bHit = false;
		Itematari[Loop].posx = 0;
		Itematari[Loop].posy = 0;
		Itematari[Loop].posz = 0;
		Itematari[Loop].ItemDraw = true;//アイテムの描画状態
		Itematari[Loop].ItemMarkerDraw = true;//アイテムマーカーの描画状態
		Itematari[Loop].ItemAtariHantei = true;//あたり判定をON!
	}

	//回復アイテム
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		RecoveryItematari[Loop].bHit = false;
		RecoveryItematari[Loop].posx = 0;
		RecoveryItematari[Loop].posy = 0;
		RecoveryItematari[Loop].posz = 0;
		RecoveryItematari[Loop].ItemDraw = true;//アイテムの描画状態
		RecoveryItematari[Loop].ItemMarkerDraw = true;//アイテムマーカーの描画状態
		RecoveryItematari[Loop].ItemAtariHantei = true;//あたり判定をON!
	}

	//ゾンビ
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		Zombieatari[Loop].bHit = false;
		Zombieatari[Loop].posx = 0;
		Zombieatari[Loop].posy = 0;
		Zombieatari[Loop].posz = 0;
		Zombieatari[Loop].ZombieDraw = true;//ゾンビの描画状態
		Zombieatari[Loop].ZombieKageDraw = true;//ゾンビ影の描画状態
		Zombieatari[Loop].ZombieAtariHantei = true;//あたり判定をON!
		Zombieatari[Loop].ZombieHP = 100.0f;//ゾンビのHP状態
	}
	ZombieNokori = ZOMBIE_NUM;//残りのゾンビ数初期化

	//敵
	EnemyDraw = true;//エネミーの描画初期化
	EnemyKageDraw = true;//エネミー影の描画初期化
	EnemyAtariHantei = true;//あたり判定をON!
	EnemyNokori = ENEMY_NUM;//敵の残り数初期化
	EnemyHP = 200.0f;//エネミーのHP初期化

	//地雷
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		Ziraiatari[Loop].bHit = false;
		Ziraiatari[Loop].posx = 0;
		Ziraiatari[Loop].posy = 50;
		Ziraiatari[Loop].posz = 0;
		Ziraiatari[Loop].Draw = false;//描画状態
		Ziraiatari[Loop].AtariHantei = false;//あたり判定をOFF
		Ziraiatari[Loop].BakuhuDraw = false;//爆風の描画をtrueにする
	}

	//弾(Shot)
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//構造体の数だけ回す 
	{
		Shotatari[Loop].bHit = false;
		Shotatari[Loop].posx = 0;
		Shotatari[Loop].posy = 50;
		Shotatari[Loop].posz = 0;
		Shotatari[Loop].Draw = false;//描画状態
		Shotatari[Loop].AtariHantei = false;//あたり判定をOFF
	}
}

void AtariHantei::Update(void)
{
	//プレイヤー & アイテム//////////////////////////////////////////

	ammunition = 0;//回復させる弾薬数を初期化

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (Itematari[Loop].ItemAtariHantei == true)
		{
			Itematari[Loop].bHit = atari(//atarihantei.h//あたり判定
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//プレイヤーの位置
				Itematari[Loop].posx, Itematari[Loop].posy, Itematari[Loop].posz, 0.5//ボンベの位置
			);
			if (Itematari[Loop].bHit == true)
			{
				//当たった場合の処理

				//サウンド
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM005);//音楽をならすok
				}
				oto1 = 0;
				//サウンド

				//アイテム
				Itematari[Loop].ItemDraw = false;//アイテムの描画を非表示にして内容をManager.cppに送る
				Itematari[Loop].ItemAtariHantei = false;//あたり判定のOFF
				Itematari[Loop].ItemMarkerDraw = false;//アイテムマーカーを非表示にする内容を送る
				
				//弾(Shot)				
				ammunition = 10;//回復させる弾薬数

				for (Loop = 0; Loop < SHOT_NUM; Loop++)//構造体の数だけ回す 
				{
					Shotatari[Loop].bHit = false;
					Shotatari[Loop].posx = 0;
					Shotatari[Loop].posy = 50;
					Shotatari[Loop].posz = 0;
					Shotatari[Loop].AtariHantei = false;//あたり判定をOFF
				}
				//弾(Shot)

			}
		}
	}
	//プレイヤー & アイテム//////////////////////////////////////////

	//プレイヤー & 回復アイテム//////////////////////////////////////////

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (RecoveryItematari[Loop].ItemAtariHantei == true)
		{
			RecoveryItematari[Loop].bHit = atari(//atarihantei.h//あたり判定
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//プレイヤーの位置
				RecoveryItematari[Loop].posx, RecoveryItematari[Loop].posy, RecoveryItematari[Loop].posz, 0.5//ボンベの位置
			);
			if (RecoveryItematari[Loop].bHit == true)
			{
				//当たった場合の処理

				//サウンド
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM015);//音楽をならすok
				}
				oto1 = 0;
				//サウンド

				//アイテム
				RecoveryItematari[Loop].ItemDraw = false;//アイテムの描画を非表示にして内容をManager.cppに送る
				RecoveryItematari[Loop].ItemAtariHantei = false;//あたり判定のOFF
				RecoveryItematari[Loop].ItemMarkerDraw = false;//アイテムマーカーを非表示にする内容を送る

				HP = HP - HP_NUM;//HP回復
				if (HP <= HP_NUM)//HPが64以下の場合
				{
					HP = HP_NUM;//HPを64にする
				}

			}
		}
	}
	//プレイヤー & 回復アイテム//////////////////////////////////////////

	//プレイヤー & ゾンビ//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		if (Zombieatari[Loop].ZombieAtariHantei == true) //あたり判定がONだったら
		{
			Zombieatari[Loop].bHit = atari(//atarihantei.h//あたり判定
				PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5,//プレイヤーの位置
				Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//ゾンビの位置
			);
			if (Zombieatari[Loop].bHit == true)
			{
				//当たった場合の処理

				//サウンド
				oto0++;
				if (oto0 > 0)
				{
					PlaySound(SOUND_LABEL_BGM013);//音楽をならすok
				}
				oto0 = 0;
				//サウンド

				Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 100;
				if (Zombieatari[Loop].ZombieHP <= 0)
				{
					//ゾンビ
					Zombieatari[Loop].ZombieDraw = false;//ゾンビの描画を非表示にして内容をManager.cppに送る
					Zombieatari[Loop].ZombieAtariHantei = false;//あたり判定のOFF
					ZombieNokori = ZombieNokori - 1;//ゾンビの残り数を-1する
					Zombieatari[Loop].ZombieKageDraw = false;//ゾンビの影描画を非表示にして内容を送る
				}

				HP = HP + HP_NUM;//HPにダメージ
				if (HP >= 256)//HPが256以上の場合
				{
					HP = 256;//HPを256にする
				}
			}
		}
	}
	//プレイヤー & ゾンビ//////////////////////////////////////////

	//プレイヤー & 敵//////////////////////////////////////////
	if (EnemyAtariHantei == true)//敵のあたり判定がONだったら
	{
		bool bHit1 = atari(//atarihantei.h//あたり判定
			EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5,//敵の位置
			PlayerPos.x, PlayerPos.y, PlayerPos.z, 0.5//プレイヤーの位置
		);
		if (bHit1 == true)
		{
			//当たった場合の処理

			//サウンド
			oto0++;
			if (oto0 > 0)
			{
				PlaySound(SOUND_LABEL_BGM013);//音楽をならすok
			}
			oto0 = 0;
			//サウンド

			EnemyHP = EnemyHP - 200.0f;
			if (EnemyHP <= 0)
			{
				//敵
				EnemyDraw = false;//敵の描画を非表示にして内容をManager.cppに送る
				EnemyAtariHantei = false;//あたり判定のOFF
				EnemyNokori = EnemyNokori - 1;//敵の残り数を-1する
				EnemyKageDraw = false;//エネミーの陰をOFFにする
			}

			HP = HP + HP_NUM;//HPにダメージ
			if (HP >= 256)//HPが256以上の場合
			{
				HP = 256;//HPを256にする
			}
		}
	}
	//プレイヤー & 敵//////////////////////////////////////////

	//地雷 & 敵//////////////////////////////////////////
	for (int Loop2 = 0; Loop2 < ZIRAI_NUM; Loop2++)//地雷構造体の数だけ回す 
	{
		if (EnemyAtariHantei == true)//敵のあたり判定がONだったら
		{
			if (Ziraiatari[Loop2].AtariHantei == true) //地雷のあたり判定がONだったら
			{
				bool bHit1 = atari(//atarihantei.h//あたり判定
					Ziraiatari[Loop2].posx, Ziraiatari[Loop2].posy, Ziraiatari[Loop2].posz, 1.0,//地雷の位置
					EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5//敵の位置
				);
				if (bHit1 == true)
				{
					//当たった場合の処理

					//サウンド
					oto0++;
					if (oto0 > 0)
					{
						PlaySound(SOUND_LABEL_BGM012);//音楽をならすok
					}
					oto0 = 0;
					oto1++;
					if (oto1 > 0)
					{
						PlaySound(SOUND_LABEL_BGM007);//音楽をならすok
					}
					oto1 = 0;
					//サウンド

					//地雷
					Ziraiatari[Loop2].AtariHantei = false;//あたり判定のOFF
					Ziraiatari[Loop2].Draw = false;//地雷の描画を非表示にして内容をManager.cppに送る
					Ziraiatari[Loop2].BakuhuDraw = true;//爆風の描画をtrueにする

					EnemyHP = EnemyHP - 200;
					if (EnemyHP <= 0)
					{
						//敵
						EnemyDraw = false;//敵の描画を非表示にして内容をManager.cppに送る
						EnemyAtariHantei = false;//あたり判定のOFF
						EnemyNokori = EnemyNokori - 1;//敵の残り数を-1する
						EnemyKageDraw = false;//エネミーの陰をOFFにする
					}
				}
			}
		}
	}
	//地雷 & 敵//////////////////////////////////////////

	//敵 & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//弾構造体の数だけ回す 
	{
		if (EnemyAtariHantei == true)//敵のあたり判定がONだったら
		{
			if (Shotatari[Loop].AtariHantei == true) //弾のあたり判定がONだったら
			{
				bool bHit1 = atari(//atarihantei.h//あたり判定
					EnemyPos.x, EnemyPos.y, EnemyPos.z, 0.5,//敵の位置
					Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shotの位置
				);
				if (bHit1)
				{
					//当たった場合の処理

					//サウンド
					oto1++;
					if (oto1 > 0)
					{
						PlaySound(SOUND_LABEL_BGM003);//音楽をならすok
					}
					oto1 = 0;
					//サウンド

					EnemyHP = EnemyHP - 10;
					if (EnemyHP <= 0)
					{
						//敵
						EnemyDraw = false;//敵の描画を非表示にして内容をEnemy.cppに送る
						EnemyAtariHantei = false;//あたり判定のOFF
						EnemyNokori = EnemyNokori - 1;//敵の残り数を-1する
						EnemyKageDraw = false;//エネミーの陰をOFFにする
					}

					//弾(Shot)
					Shotatari[Loop].AtariHantei = false;//あたり判定のOFF
					Shotatari[Loop].Draw = false;//弾の描画を非表示にして内容をShot.cppに送る
				}
			}
		}
	}
	//敵 & Shot//////////////////////////////////////////

	//地雷 & ゾンビ//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//ゾンビ構造体の数だけ回す 
	{
		for (int Loop2 = 0; Loop2 < ZIRAI_NUM; Loop2++)//地雷構造体の数だけ回す 
		{
			if (Zombieatari[Loop].ZombieAtariHantei == true) //ゾンビのあたり判定がONだったら
			{
				if (Ziraiatari[Loop2].AtariHantei == true) //地雷のあたり判定がONだったら
				{
					Zombieatari[Loop].bHit = atari(//atarihantei.h//あたり判定
						Ziraiatari[Loop2].posx, Ziraiatari[Loop2].posy, Ziraiatari[Loop2].posz, 1.0,//地雷の位置
						Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//ゾンビの位置
					);
					if (Zombieatari[Loop].bHit == true)
					{
						//当たった場合の処理

						//サウンド
						oto0++;
						if (oto0 > 0)
						{
							PlaySound(SOUND_LABEL_BGM012);//音楽をならすok
						}
						oto0 = 0;
						oto1++;
						if (oto1 > 0)
						{
							PlaySound(SOUND_LABEL_BGM007);//音楽をならすok
						}
						oto1 = 0;
						//サウンド

						Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 100;
						if (Zombieatari[Loop].ZombieHP <= 0)
						{
							//ゾンビ
							Zombieatari[Loop].ZombieDraw = false;//ゾンビの描画を非表示にして内容をManager.cppに送る
							Zombieatari[Loop].ZombieAtariHantei = false;//あたり判定のOFF
							ZombieNokori = ZombieNokori - 1;//ゾンビの残り数を-1する
							Zombieatari[Loop].ZombieKageDraw = false;//ゾンビの影描画を非表示にして内容を送る
						}
						//地雷
						Ziraiatari[Loop2].AtariHantei = false;//あたり判定のOFF
						Ziraiatari[Loop2].Draw = false;//地雷の描画を非表示にして内容をManager.cppに送る
						Ziraiatari[Loop2].BakuhuDraw = true;//爆風の描画をtrueにする
					}
				}
			}
		}
	}
	//地雷 & ゾンビ//////////////////////////////////////////

	//Shot & ゾンビ//////////////////////////////////////////
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//ゾンビ構造体の数だけ回す 
	{
		for (int Loop2 = 0; Loop2 < SHOT_NUM; Loop2++)//弾構造体の数だけ回す 
		{
			if (Zombieatari[Loop].ZombieAtariHantei == true) //ゾンビのあたり判定がONだったら
			{
				if (Shotatari[Loop2].AtariHantei == true) //弾のあたり判定がONだったら
				{
					Zombieatari[Loop].bHit = atari(//atarihantei.h//あたり判定
						Shotatari[Loop2].posx, Shotatari[Loop2].posy, Shotatari[Loop2].posz, 0.1,//弾の位置
						Zombieatari[Loop].posx, Zombieatari[Loop].posy, Zombieatari[Loop].posz, 0.5//ゾンビの位置
					);
					if (Zombieatari[Loop].bHit == true)
					{
						//当たった場合の処理

						//サウンド
						oto1++;
						if (oto1 > 0)
						{
							PlaySound(SOUND_LABEL_BGM003);//音楽をならすok
						}
						oto1 = 0;
						//サウンド

						Zombieatari[Loop].ZombieHP = Zombieatari[Loop].ZombieHP - 10;
						if (Zombieatari[Loop].ZombieHP <= 0)
						{
							//ゾンビ
							Zombieatari[Loop].ZombieDraw = false;//ゾンビの描画を非表示にして内容をManager.cppに送る
							Zombieatari[Loop].ZombieAtariHantei = false;//あたり判定のOFF
							ZombieNokori = ZombieNokori - 1;//ゾンビの残り数を-1する
							Zombieatari[Loop].ZombieKageDraw = false;//ゾンビの影描画を非表示にして内容を送る
						}
						//弾(Shot)
						Shotatari[Loop2].AtariHantei = false;//あたり判定のOFF
						Shotatari[Loop2].Draw = false;//弾の描画を非表示にして内容をShot.cppに送る

					}
				}
			}
		}
	}
	//Shot & ゾンビ//////////////////////////////////////////

	//家 & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//弾構造体の数だけ回す 
	{
		if (Shotatari[Loop].AtariHantei == true) //弾のあたり判定がONだったら
		{
			bool bHit1 = atari(//atarihantei.h//あたり判定
				IePos.x, IePos.y, IePos.z, 2.5,//敵の位置
				Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shotの位置
			);
			if (bHit1)
			{
				//当たった場合の処理

				//サウンド
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM014);//音楽をならすok
				}
				oto1 = 0;
				//サウンド

				//弾(Shot)
				Shotatari[Loop].AtariHantei = false;//あたり判定のOFF
				Shotatari[Loop].Draw = false;//弾の描画を非表示にして内容をShot.cppに送る
			}
		}
	}
	//家 & Shot//////////////////////////////////////////

	//家2 & Shot//////////////////////////////////////////
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//弾構造体の数だけ回す 
	{
		if (Shotatari[Loop].AtariHantei == true) //弾のあたり判定がONだったら
		{
			bool bHit1 = atari(//atarihantei.h//あたり判定
				Ie2Pos.x, Ie2Pos.y, Ie2Pos.z, 2.5,//敵の位置
				Shotatari[Loop].posx, Shotatari[Loop].posy, Shotatari[Loop].posz, 0.5//Shotの位置
			);
			if (bHit1)
			{
				//当たった場合の処理

				//サウンド
				oto1++;
				if (oto1 > 0)
				{
					PlaySound(SOUND_LABEL_BGM014);//音楽をならすok
				}
				oto1 = 0;
				//サウンド

				//弾(Shot)
				Shotatari[Loop].AtariHantei = false;//あたり判定のOFF
				Shotatari[Loop].Draw = false;//弾の描画を非表示にして内容をShot.cppに送る
			}
		}
	}
	//家2 & Shot//////////////////////////////////////////

}


void AtariHantei::Uninit(void) 
{

}

void AtariHantei::ResetParameters(void)
{
	//サウンド
	oto0 = 0;//音楽用変数初期化
	oto1 = 0;//音楽用変数初期化

	ZombieNokori = ZOMBIE_NUM;//ゾンビの残り数
	EnemyNokori = ENEMY_NUM;//敵の残り数

	HP = HP_NUM;//残りHP

	//アイテム
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		Itematari[Loop].bHit = false;
		Itematari[Loop].posx = 0;
		Itematari[Loop].posy = 0;
		Itematari[Loop].posz = 0;
		Itematari[Loop].ItemDraw = true;//アイテムの描画状態
		Itematari[Loop].ItemMarkerDraw = true;//アイテムマーカーの描画状態
		Itematari[Loop].ItemAtariHantei = true;//あたり判定をON!
	}

	//回復アイテム
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		RecoveryItematari[Loop].bHit = false;
		RecoveryItematari[Loop].posx = 0;
		RecoveryItematari[Loop].posy = 0;
		RecoveryItematari[Loop].posz = 0;
		RecoveryItematari[Loop].ItemDraw = true;//アイテムの描画状態
		RecoveryItematari[Loop].ItemMarkerDraw = true;//アイテムマーカーの描画状態
		RecoveryItematari[Loop].ItemAtariHantei = true;//あたり判定をON!
	}

	//ゾンビ
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		Zombieatari[Loop].bHit = false;
		Zombieatari[Loop].posx = 0;
		Zombieatari[Loop].posy = 0;
		Zombieatari[Loop].posz = 0;
		Zombieatari[Loop].ZombieDraw = true;//ゾンビの描画状態
		Zombieatari[Loop].ZombieKageDraw = true;//ゾンビ影の描画状態
		Zombieatari[Loop].ZombieAtariHantei = true;//あたり判定をON!
		Zombieatari[Loop].ZombieHP = 100.0f;//ゾンビのHP状態
	}
	ZombieNokori = ZOMBIE_NUM;//残りのゾンビ数初期化

	//敵
	EnemyDraw = true;//エネミーの描画初期化
	EnemyKageDraw = true;//エネミー影の描画初期化
	EnemyAtariHantei = true;//あたり判定をON!
	EnemyNokori = ENEMY_NUM;//敵の残り数初期化
	EnemyHP = 200.0f;//エネミーのHP初期化

	//地雷
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		Ziraiatari[Loop].bHit = false;
		Ziraiatari[Loop].posx = 0;
		Ziraiatari[Loop].posy = 50;
		Ziraiatari[Loop].posz = 0;
		Ziraiatari[Loop].Draw = false;//描画状態
		Ziraiatari[Loop].AtariHantei = false;//あたり判定をOFF
		Ziraiatari[Loop].BakuhuDraw = false;//爆風の描画をtrueにする
	}

	//弾(Shot)
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)//構造体の数だけ回す 
	{
		Shotatari[Loop].bHit = false;
		Shotatari[Loop].posx = 0;
		Shotatari[Loop].posy = 50;
		Shotatari[Loop].posz = 0;
		Shotatari[Loop].Draw = false;//描画状態
		Shotatari[Loop].AtariHantei = false;//あたり判定をOFF
	}
}