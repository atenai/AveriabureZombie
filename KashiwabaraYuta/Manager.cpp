//=============================================================================
//
// マネージャー [Manager.cpp]
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
//クラスの(設計図)の名前付け
//===========================
Player *p_Player;//プレイヤークラス(設計図)のポインタを用意
PlayerKage *p_PlayerKage;//プレイヤー影クラス(設計図)のポインタを用意
Camera *p_Camera;//カメラクラス(設計図)のポインタを用意
SkyDome *p_SkyDome;//スカイドームクラス(設計図)のポインタを用意
Zimen *p_Zimen;//地面クラス(設計図)のポインタを用意
Kusa1 *p_Kusa1;//草1クラス(設計図)のポインタを用意
Kusa2 *p_Kusa2;//草2クラス(設計図)のポインタを用意
Kusa3 *p_Kusa3;//草3クラス(設計図)のポインタを用意
Tree *p_Tree;//木クラス(設計図)のポインタを用意
Bonbe *p_Bonbe;//ボンベクラス(設計図)のポインタを用意
Bonbe *p_Bonbe2;//ボンベ2クラス(設計図)のポインタを用意
Ame *p_Ame;//雨クラス(設計図)のポインタを用意
Shot *p_Shot;//弾クラス(設計図)のポインタを用意
Zirai *p_Zirai;//地雷クラス(設計図)のポインタを用意
Item *p_Item;//アイテムクラス(設計図)のポインタを用意
ItemMarker *p_ItemMarker;//アイテムマーカークラス(設計図)のポインタを用意
UAV *p_UAV;//UAVクラス(設計図)のポインタを用意
Ie *p_Ie;//家クラス(設計図)のポインタを用意
Ie *p_Ie2;//家2クラス(設計図)のポインタを用意
Enemy *p_Enemy;//エネミークラス(設計図)のポインタを用意
EnemyKage *p_EnemyKage;//エネミー影クラス(設計図)のポインタを用意
EnemyHPgage *p_EnemyHPgage;//エネミーHPゲージクラス(設計図)のポインタを用意
Zombie *p_Zombie;//ゾンビクラス(設計図)のポインタを用意
ZombieKage *p_ZombieKage;//ゾンビ影クラス(設計図)のポインタを用意
ZombieHPgage *p_ZombieHPgage;//ゾンビHPゲージクラス(設計図)のポインタを用意
AtariHantei *p_AtariHantei;//あたり判定クラス(設計図)のポインタを用意
Bakuhu *p_Bakuhu;//爆風クラス(設計図)のポインタを用意
BoxAtariHantei *p_BoxAtariHantei;//ボックスあたり判定(設計図)のポインタを用意
UI *p_UI;//UI(設計図)のポインタを用意
RecoveryItem *p_RecoveryItem;//回復アイテムクラス(設計図)のポインタを用意
RecoveryItemMarker *p_RecoveryItemMarker;//回復アイテムマーカークラス(設計図)のポインタを用意

//===============
//グローバル変数
//===============

//==============
//コンストラクタ
//==============
Manager::Manager()
{
}

//==============
//デストラクタ
//==============
Manager::~Manager()
{
}


//==============
//  初期化関数
//==============
void Manager::Init()
{
	p_Camera = new Camera;//カメラクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Camera->Init();//カメラの初期化処理

	p_UAV = new UAV;//UAVクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_UAV->Init();//UAVの初期化処理

	p_Player = new Player;//プレイヤークラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Player->Init();//プレイヤーの初期化処理
	p_Player->SetPlayerPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//移動用数値初期化

	p_Ie = new Ie;//家クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Ie->SetPos(D3DXVECTOR3(0.0f, 0.0f, 10.0f));//初期家の座標をセット
	p_Ie->Init();//家の初期化処理
	

	p_Ie2 = new Ie;//家2クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Ie2->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));//初期家2の座標をセット
	p_Ie2->Init();//家2の初期化処理
	

	p_Enemy = new Enemy;//エネミークラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Enemy->Init();//エネミーの初期化処理
	p_Enemy->SetIePos(p_Ie->GetPos());
	p_Enemy->SetIeMin(p_Ie->GetIeMin());
	p_Enemy->SetIeMax(p_Ie->GetIeMax());
	p_Enemy->SetIe2Pos(p_Ie2->GetPos());
	p_Enemy->SetIe2Min(p_Ie2->GetIeMin());
	p_Enemy->SetIe2Max(p_Ie2->GetIeMax());

	p_Zombie = new Zombie;//ゾンビクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Zombie->Init();//ゾンビの初期化処理
	p_Zombie->SetIePos(p_Ie->GetPos());
	p_Zombie->SetIeMin(p_Ie->GetIeMin());
	p_Zombie->SetIeMax(p_Ie->GetIeMax());
	p_Zombie->SetIe2Pos(p_Ie2->GetPos());
	p_Zombie->SetIe2Min(p_Ie2->GetIeMin());
	p_Zombie->SetIe2Max(p_Ie2->GetIeMax());

	p_Zimen = new Zimen;//地面クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Zimen->Init();//地面の初期化処理

	p_SkyDome = new SkyDome;//スカイドームクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_SkyDome->Init();//スカイドームの初期化処理

	p_Item = new Item;//アイテムクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Item->Init();//アイテムの初期化処理

	p_RecoveryItem = new RecoveryItem;//回復アイテムクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_RecoveryItem->Init();//回復アイテムの初期化処理

	p_Tree = new Tree;//木クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Tree->Init();//木の初期化処理

	p_Kusa1 = new Kusa1;//草1クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Kusa1->Init();//草1の初期化処理

	p_Kusa2 = new Kusa2;//草2クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Kusa2->Init();//草2の初期化処理

	p_Kusa3 = new Kusa3;//草3クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Kusa3->Init();//草3の初期化処理

	p_Ame = new Ame;//雨クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Ame->Init();//雨の初期化処理

	p_ItemMarker = new ItemMarker;//アイテムマーカークラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_ItemMarker->Init();//アイテムマーカーの初期化処理
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_ItemMarker->SetPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//アイテムマーカーの座標をセット
	}

	p_RecoveryItemMarker = new RecoveryItemMarker;//回復アイテムマーカークラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_RecoveryItemMarker->Init();//回復アイテムマーカーの初期化処理
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_RecoveryItemMarker->SetPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//回復アイテムマーカーの座標をセット
	}

	p_EnemyHPgage = new EnemyHPgage;//エネミーHPゲージクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_EnemyHPgage->Init();//エネミーHPゲージの初期化処理
	p_EnemyHPgage->SetEnemyPos(p_Enemy->GetEnemyPos());//エネミーHPゲージの初期座標をセット

	p_ZombieHPgage = new ZombieHPgage;//ゾンビHPゲージクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_ZombieHPgage->Init();//ゾンビHPゲージの初期化処理
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_ZombieHPgage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//ゾンビHPゲージの初期座標をセット
	}

	p_PlayerKage = new PlayerKage;//プレイヤー影クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_PlayerKage->Init();//プレイヤー影の初期化処理
	p_PlayerKage->SetPlayerPos(p_Player->GetPlayerPos());//プレイヤー影の初期座標をセット

	p_EnemyKage = new EnemyKage;//エネミー影クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_EnemyKage->Init();//エネミー影の初期化処理
	p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//エネミー影の初期座標をセット

	p_ZombieKage = new ZombieKage;//ゾンビ影クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_ZombieKage->Init();//ゾンビ影の初期化処理
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//ゾンビ影の初期座標をセット
	}

	p_Shot = new Shot;//弾クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Shot->Init();//弾の初期化処理
	p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//弾の初期座標をセット
	p_Shot->SetPlayerFront(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//弾の前ベクトルを初期化

	p_Zirai = new Zirai;//地雷クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Zirai->Init();//地雷の初期化処理
	p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//地雷の初期座標をセット

	p_Bakuhu = new Bakuhu;//爆風クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Bakuhu->Init();//爆風の初期化処理
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//爆風の初期座標をセット
	}

	p_AtariHantei = new AtariHantei;//あたり判定クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_AtariHantei->Init();//あたり判定の初期化処理
	p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//あたり判定プレイヤーの初期座標をセット
	p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//あたり判定エネミーの初期座標をセット
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//あたり判定ゾンビの初期座標をセット
	}
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_AtariHantei->SetItemPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//あたり判定アイテムの初期座標をセット
	}
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_AtariHantei->SetRecoveryItemPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//あたり判定回復アイテムの初期座標をセット
	}
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//あたり判定地雷の初期座標をセット
	}
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//あたり判定弾の初期座標をセット
	}
	p_AtariHantei->SetIePos(p_Ie->GetPos());//あたり判定家の初期座標をセット
	p_AtariHantei->SetIe2Pos(p_Ie2->GetPos());//あたり判定家2の初期座標をセット

	p_BoxAtariHantei = new BoxAtariHantei;//バウンディングボックスあたり判定クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_BoxAtariHantei->Init();//バウンディングボックスあたり判定の初期化処理

	p_UI = new UI;//UIクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_UI->Init();//UIの初期化処理

	//p_Bonbe = new Bonbe;//ボンベクラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	//p_Bonbe->Init();//ボンベの初期化処理
	//p_Bonbe->SetBonbePos(0.0f, 0.0f, 5.0f);//ボンベの座標をセット

	//p_Bonbe2 = new Bonbe;//ボンベ2クラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	//p_Bonbe2->Init();//ボンベ2の初期化処理
	//p_Bonbe2->SetBonbePos(0.0f, 3.0f, 5.0f);//ボンベ2の座標をセット


}

//==============
//  終了関数
//==============
void Manager::Uninit() 
{
	p_Camera->Uninit();//カメラの終了処理
	delete p_Camera;//カメラクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_UAV->Uninit();//UAVの終了処理
	delete p_UAV;//UAVクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Player->Uninit();//プレイヤーの終了処理
	delete p_Player;//プレイヤークラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Ie->Uninit();//家の終了処理
	delete p_Ie;//家クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Ie2->Uninit();//家2の終了処理
	delete p_Ie2;//家2クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Enemy->Uninit();//エネミーの終了処理
	delete p_Enemy;//エネミークラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Zombie->Uninit();//ゾンビの終了処理
	delete p_Zombie;//ゾンビクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Zimen->Uninit();//地面の終了処理
	delete p_Zimen;//地面クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_SkyDome->Uninit();//スカイドームの終了処理
	delete p_SkyDome;//スカイドームクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Item->Uninit();//アイテムの終了処理
	delete p_Item;//アイテムクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_RecoveryItem->Uninit();//回復アイテムの終了処理
	delete p_RecoveryItem;//回復アイテムクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Tree->Uninit();//木の終了処理
	delete p_Tree;//木クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Kusa1->Uninit();//草1の終了処理
	delete p_Kusa1;//草1クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Kusa2->Uninit();//草2の終了処理
	delete p_Kusa2;//草2クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Kusa3->Uninit();//草3の終了処理
	delete p_Kusa3;//草3クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Ame->Uninit();//雨の終了処理
	delete p_Ame;//雨クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_ItemMarker->Uninit();//アイテムマーカーの終了処理
	delete p_ItemMarker;//アイテムマーカークラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_RecoveryItemMarker->Uninit();//回復アイテムマーカーの終了処理
	delete p_RecoveryItemMarker;//回復アイテムマーカークラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_EnemyHPgage->Uninit();//エネミーHPゲージの終了処理
	delete p_EnemyHPgage;//エネミーHPゲージクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_ZombieHPgage->Uninit();//ゾンビHPゲージの終了処理
	delete p_ZombieHPgage;//ゾンビHPゲージクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_PlayerKage->Uninit();//プレイヤー影の終了処理
	delete p_PlayerKage;//プレイヤー影クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_EnemyKage->Uninit();//エネミー影の終了処理
	delete p_EnemyKage;//エネミー影クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_ZombieKage->Uninit();//ゾンビ影の終了処理
	delete p_ZombieKage;//ゾンビ影クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Shot->Uninit();//弾の終了処理
	delete p_Shot;//弾クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_Zirai->Uninit();//地雷の終了処理
	delete p_Zirai;//地雷クラスオブジェクトの破棄とメモリの解放とデストラクタの実行
	
	p_Bakuhu->Uninit();//爆風の終了処理
	delete p_Bakuhu;//爆風クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_AtariHantei->Uninit();//あたり判定の終了処理
	delete p_AtariHantei;//あたり判定クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_BoxAtariHantei->Uninit();//ボックスあたり判定の終了処理
	delete p_BoxAtariHantei;//ボックスあたり判定クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	p_UI->Uninit();//UIの終了処理
	delete p_UI;//UIクラスオブジェクトの破棄とメモリの解放とデストラクタの実行
	
	//p_Bonbe->Uninit();//ボンベの終了処理
	//delete p_Bonbe;//ボンベクラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	//p_Bonbe2->Uninit();//ボンベ2の終了処理
	//delete p_Bonbe2;//ボンベ2クラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	
}

//==============
//  更新関数
//==============
void Manager::Update()
{
	nflagTime++;

		if (nflag == 0 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10)//もしタイトル画面だったら
		{

			//サウンド
			count0++;
			if (count0 > 0)
			{
				PlaySound(SOUND_LABEL_BGM004);//音楽をならすok
			}
			count0 = 0;
			//サウンド


				nflag = 1;//ゲームプレイ画面へ移動
				nflagTime = 0;
		}

		if (nflag == 2 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10 || nflag == 3 && GetKeyboardPress(DIK_RETURN) && nflagTime >= 10)//ゲームクリアー画面またはゲームオーバー画面だったら
		{
				nflag = 0;//タイトル画面へ移動
				nflagTime = 0;
		}

	//タイトル
	if (nflag == 0)
	{

		ResetParameters();

		count3 = 0;//音楽用変数の初期化
		count4 = 0;//音楽用変数の初期化
		//サウンド
		StopSound(SOUND_LABEL_BGM008);//サウンドの停止
		StopSound(SOUND_LABEL_BGM009);//サウンドの停止
		if (count1 == 0)
		{
			PlaySound(SOUND_LABEL_BGM000);//音楽をならす
		}
		count1++;
		//サウンド
	}

	//ゲームプレイ
	if (nflag == 1)
	{
		count1 = 0;//音楽用変数の初期化
		//サウンド
		StopSound(SOUND_LABEL_BGM000);//サウンドの停止
		if (count2 == 0)
		{
			PlaySound(SOUND_LABEL_BGM001);//音楽をならす
		}
		count2++;
		//サウンド

		p_UAV->Update();//UAVの更新処理

		p_Player->Update();//プレイヤーの更新処理
		p_Shot->SetPlayerFront(p_Player->GetFront());//弾の前ベクトルにプレイヤーの前ベクトルを入れる処理
		p_Camera->SetPlayerMatrix(p_Player->GetMtxWorld());//カメラの行列にプレイヤーの移動と回転の入ったワールド行列を入れる処理

		p_Ie->Update();//家の更新処理

		p_Ie2->Update();//家2の更新処理

		p_Enemy->Update();//エネミーの更新処理
		p_Enemy->SetEnemyDraw(p_AtariHantei->GetEnemyDraw());//エネミーの描画状態を更新
		p_Enemy->SetPlayerPos(p_Player->GetPlayerPos());//エネミーの探索座標にプレイヤーの座標を入れる処理

		p_Zombie->Update();//ゾンビの更新処理
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_Zombie->SetZombieDraw(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieDraw(Loop));//ゾンビの描画状態を更新
		}
		p_Zombie->SetPlayerPos(p_Player->GetPlayerPos());//ゾンビの探索座標にプレイヤーの座標を入れる処理

		p_Zimen->Update();//地面の更新処理

		p_SkyDome->Update();//スカイドームの更新処理

		p_Item->Update();//アイテムの更新処理
		for (int Loop = 0; Loop < ITEM_NUM; Loop++)
		{
			p_Item->SetItemDraw(p_AtariHantei->GetItemLoop(Loop), p_AtariHantei->GetItemDraw(Loop));//アイテムの描画状態を更新
		}

		p_RecoveryItem->Update();//回復アイテムの更新処理
		for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
		{
			p_RecoveryItem->SetRecoveryItemDraw(p_AtariHantei->GetRecoveryItemLoop(Loop), p_AtariHantei->GetRecoveryItemDraw(Loop));//回復アイテムの描画状態を更新
		}

		p_Camera->Update();//カメラの更新処理

		p_Tree->Update();//木の更新処理

		p_Kusa1->Update();//草1の更新処理

		p_Kusa2->Update();//草2の更新処理

		p_Kusa3->Update();//草3の更新処理

		p_Ame->Update();//雨の更新処理

		p_ItemMarker->Update();//アイテムマーカーの更新処理
		for (int Loop = 0; Loop < ITEM_NUM; Loop++)
		{
			p_ItemMarker->SetItemMarkerDraw(p_AtariHantei->GetItemLoop(Loop), p_AtariHantei->GetItemMarkerDraw(Loop));//アイテムマーカーの描画状態を更新
		}

		p_RecoveryItemMarker->Update();//回復アイテムマーカーの更新処理
		for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
		{
			p_RecoveryItemMarker->SetRecoveryItemMarkerDraw(p_AtariHantei->GetRecoveryItemLoop(Loop), p_AtariHantei->GetRecoveryItemMarkerDraw(Loop));//アイテムマーカーの描画状態を更新
		}

		p_EnemyHPgage->Update();//エネミーHPゲージの更新処理
		p_EnemyHPgage->SetEnemyPos(p_Enemy->GetEnemyPos());//エネミーHPゲージの座標にエネミーの座標を入れる更新処理
		p_EnemyHPgage->SetNokoriEnemyHP(p_AtariHantei->GetEnemyHPgage());//エネミーHPゲージの残り残量を入れる更新処理

		p_ZombieHPgage->Update();//ゾンビHPゲージの更新処理
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_ZombieHPgage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//ゾンビHPゲージの座標を更新
			p_ZombieHPgage->SetNokoriZombieHP(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieHPgage(Loop));//ゾンビHPゲージの残り残量を入れる更新処理
		}

		p_PlayerKage->SetPlayerPos(p_Player->GetPlayerPos());//プレイヤー影の座標にプレイヤーの座標を入れる更新処理
		p_PlayerKage->Update();//プレイヤー影の更新処理

		p_EnemyKage->Update();//エネミー影の更新処理
		p_EnemyKage->SetEnemyKageDraw(p_AtariHantei->GetEnemyKageDraw());//エネミー影の描画状態を更新
		p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//エネミー影の座標にエネミーの座標を入れる更新処理

		p_ZombieKage->Update();//ゾンビ影の更新処理
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//ゾンビ影の座標を更新
			p_ZombieKage->SetZombieKageDraw(p_AtariHantei->GetZombieLoop(Loop), p_AtariHantei->GetZombieKageDraw(Loop));//ゾンビ影の描画状態を更新
		}

		p_Shot->Update();//弾の更新処理(1)[Shot.cpp ⇒ true ⇒ Shot.h]
		for (int Loop = 0; Loop < SHOT_NUM; Loop++)
		{
			p_AtariHantei->SetShotDraw(p_Shot->GetLoop(Loop), p_Shot->GetShotDraw(Loop));//弾の描画状態を更新(2)[Shot.h ⇒ true ⇒ AtariHantei.h]
			p_AtariHantei->SetShotAtariHantei(p_Shot->GetLoop(Loop), p_Shot->GetShotAtariHantei(Loop));//弾のあたり判定の状態を更新(2)[Shot.h ⇒ true ⇒ AtariHantei.h]

		}
		p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//弾の座標にプレイヤーの座標を入れる更新処理

		p_Zirai->Update();//地雷の更新処理(1)[Zirai.cpp ⇒ true ⇒ Zirai.h]
		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_AtariHantei->SetZiraiDraw(p_Zirai->GetLoop(Loop), p_Zirai->GetZiraiDraw(Loop));//地雷の描画状態を更新(2)[Zirai.h ⇒ true ⇒ AtariHantei.h]
			p_AtariHantei->SetZiraiAtariHantei(p_Zirai->GetLoop(Loop), p_Zirai->GetZiraiAtariHantei(Loop));//地雷のあたり判定の状態を更新(2)[Zirai.h ⇒ true ⇒ AtariHantei.h]
		}
		p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//地雷の座標にプレイヤーの座標を入れる更新処理

		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//爆風の座標をセット
			p_Bakuhu->SetBakuhuDraw(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetBakuhuDraw(Loop));
		}
		p_Bakuhu->Update();//爆風の更新処理

		p_AtariHantei->Update();//あたり判定の更新処理(3)[AtariHantei.cpp ⇒ false ⇒ AtariHantei.h]
		p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//あたり判定プレイヤーの座標にプレイヤーの座標を入れる更新処理
		p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//あたり判定エネミーの座標にエネミーの座標を入れる更新処理
		for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
		{
			p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//あたり判定ゾンビの座標にゾンビの座標を入れる更新処理
		}
		for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
		{
			p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//あたり判定地雷の座標に地雷の座標を入れる更新処理

			p_Zirai->SetZiraiDraw(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetZiraiDraw(Loop));//地雷の描画状態を更新(4)[AtariHantei.h ⇒ false ⇒ Zirai.h]
			p_Zirai->SetZiraiAtariHantei(p_AtariHantei->GetZiraiLoop(Loop), p_AtariHantei->GetZiraiAtariHantei(Loop));//地雷のあたり判定の状態を更新(4)[AtariHantei.h ⇒ false ⇒ Zirai.h]

		}
		for (int Loop = 0; Loop < SHOT_NUM; Loop++)
		{
			p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//あたり判定弾の座標に弾の座標を入れる更新処理

			p_Shot->SetShotDraw(p_AtariHantei->GetShotLoop(Loop), p_AtariHantei->GetShotDraw(Loop));//弾の描画状態を更新(4)[AtariHantei.h ⇒ false ⇒ Shot.h]
			p_Shot->SetShotAtariHantei(p_AtariHantei->GetShotLoop(Loop), p_AtariHantei->GetShotAtariHantei(Loop));//弾のあたり判定の状態を更新(4)[AtariHantei.h ⇒ false ⇒ Shot.h]
		}
		p_Shot->SetTamaHuyasu(p_AtariHantei->Getammunition());//当たったら弾を増やす処理


		p_BoxAtariHantei->SetPlayerMin(p_Player->GetPlayerMin());//ボックスあたり判定にプレイヤーの最小頂点を送る
		p_BoxAtariHantei->SetPlayerMax(p_Player->GetPlayerMax());//ボックスあたり判定にプレイヤーの最大頂点を送る
		p_BoxAtariHantei->SetIeMin(p_Ie->GetIeMin());//ボックスあたり判定に家の最小頂点を送る
		p_BoxAtariHantei->SetIeMax(p_Ie->GetIeMax());//ボックスあたり判定に家の最大頂点を送る
		p_BoxAtariHantei->SetIe2Min(p_Ie2->GetIeMin());//ボックスあたり判定に家2の最小頂点を送る
		p_BoxAtariHantei->SetIe2Max(p_Ie2->GetIeMax());//ボックスあたり判定に家2の最大頂点を送る
		p_BoxAtariHantei->Update();//バウンディングボックスあたり判定の更新処理
		p_Player->SetPlayerIeBoxAtari(p_BoxAtariHantei->GetPlayerIeBoxAtari());//プレイヤーにボックスあたり判定の結果を送る
		p_Player->SetPlayerIe2BoxAtari(p_BoxAtariHantei->GetPlayerIe2BoxAtari());//プレイヤーにボックスあたり判定の結果を送る
		p_Player->SetPlayerSita(p_BoxAtariHantei->GetPlayerSita());//プレイヤーにボックスあたり判定の結果を送る
		p_Player->SetPlayerUe(p_BoxAtariHantei->GetPlayerUe());//プレイヤーにボックスあたり判定の結果を送る
		p_Player->SetPlayerMigi(p_BoxAtariHantei->GetPlayerMigi());//プレイヤーにボックスあたり判定の結果を送る
		p_Player->SetPlayerHidari(p_BoxAtariHantei->GetPlayerHidari());//プレイヤーにボックスあたり判定の結果を送る

		//p_Bonbe->Update();//ボンベの更新処理

		//p_Bonbe2->Update();//ボンベの更新処理

		SetZombieNokori(p_AtariHantei->GetZombieNokori());
		SetEnemyNokori(p_AtariHantei->GetEnemyNokori());
		//残りのゾンビ数が0かつエネミー数も0なら
		if (ZombieNokori == 0 && EnemyNokori == 0 && test == false) 
		{
			nflag = 2;//ゲームクリアーに移動
		}
		SetHP_UI(p_AtariHantei->GetHP());//HP残量
		//HPダメージが256を越えたら
		if (HP_UI >= 256 && test == false)
		{
			nflag = 3;//ゲームオーバーに移動
		}
	}

	//ゲームクリアー
	if (nflag == 2)
	{
		count2 = 0;//音楽用変数の初期化
		//サウンド
		StopSound(SOUND_LABEL_BGM001);//サウンドの停止
		if (count3 == 0)
		{
			PlaySound(SOUND_LABEL_BGM008);//音楽をならす
		}
		count3++;
		//サウンド

		//test = true;
	}

	//ゲームオーバー
	if (nflag == 3)
	{
		count2 = 0;//音楽用変数の初期化
		//サウンド
		StopSound(SOUND_LABEL_BGM001);//サウンドの停止
		if (count4 == 0)
		{
			PlaySound(SOUND_LABEL_BGM009);//音楽をならす
		}
		count4++;
		//サウンド

		//test = true;
	}

}

//==============
//  描画関数
//==============
void Manager::Draw() 
{
	//タイトル
	if (nflag == 0)
	{

		//タイトル画面
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(
			10,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			1280,//元の画像の切り取りたい幅
			720 //元の画像の切り取りたい高さ
		);

		//タイトル画面
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(
			7,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			800,//元の画像の切り取りたい幅
			600 //元の画像の切り取りたい高さ
		);

		//テクスチャピコピコ
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
			p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
			p_UI->Draw(
				5,//使うテクスチャ,
				15.0f,//x座標,
				0.0f,//y座標,
				1500,//テクスチャの表示する横の長さ,//元の画像の横の長さは32
				1000,//テクスチャの表示する縦の長さ,//元の画像の縦の長さは32
				0,//元の画像の切り取り開始場所（横）（画像の左から数える）
				0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
				800,//元の画像の切り取りたい幅
				600 //元の画像の切り取りたい高さ
			);
		}
		//テクスチャピコピコ
	}

	//ゲームプレイ
	if (nflag == 1)
	{
		p_UAV->Draw();//UAVの描画処理

		p_Player->Draw();//Playerの描画処理

		p_Ie->Draw();//家の描画処理

		p_Ie2->Draw();//家2の描画処理

		p_Enemy->Draw();//エネミーの描画処理

		p_Zombie->Draw();//ゾンビの描画処理

		p_Zimen->Draw();//地面の描画処理

		p_SkyDome->Draw();//スカイドームの描画処理

		p_Item->Draw();//アイテムの描画処理

		p_RecoveryItem->Draw();//回復アイテムの描画処理

		p_Tree->Draw();//木の描画処理

		p_Kusa1->Draw();//草1の描画処理

		p_Kusa2->Draw();//草2の描画処理

		p_Kusa3->Draw();//草3の描画処理

		p_Ame->Draw();//雨の描画処理

		p_ItemMarker->Draw();//アイテムマーカーの描画処理

		p_RecoveryItemMarker->Draw();//回復アイテムマーカーの描画処理

		p_EnemyHPgage->Draw();//エネミーHPゲージの描画処理

		p_ZombieHPgage->Draw();//ゾンビHPゲージの描画処理

		p_PlayerKage->Draw();//Player影の描画処理

		p_EnemyKage->Draw();//エネミー影の描画処理

		p_ZombieKage->Draw();//ゾンビ影の描画処理

		p_Shot->Draw();//弾の描画処理

		p_Zirai->Draw();//地雷の描画処理

		p_Bakuhu->Draw();//爆風の描画処理

		//p_Bonbe->Draw();//ボンベの描画処理

		//p_Bonbe2->Draw();//ボンベの描画処理


		//レンズフレア
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//ポリゴンカラーの設定
		p_UI->Draw(
			0,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			3500,//元の画像の切り取りたい幅
			2333 //元の画像の切り取りたい高さ
		);

		//レンズフレア
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//ポリゴンカラーの設定
		p_UI->Draw(
			1,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			3500,//元の画像の切り取りたい幅
			2333 //元の画像の切り取りたい高さ
		);

		//レンズフレア
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(235, 122, 119, HP_UI));//ポリゴンカラーの設定
		p_UI->Draw(
			2,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			3500,//元の画像の切り取りたい幅
			2333 //元の画像の切り取りたい高さ
		);

		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 100));//ポリゴンカラーの設定
		p_UI->Draw(11, 0, 700, 400, 260, 0, 0, 128, 128);//2D画像(UI)を表示//UIは一番下にしないと画像が透けてしまう。
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(3, 15, 700, 500, 250, 0, 0, 1000, 500);//2D画像(UI)を表示//UIは一番下にしないと画像が透けてしまう。
		SetTPS_UI(p_Camera->GetTPS());//カメラから肩越しかどうかを持ってくる処理
		if (TPS_UI == true)
		{
			p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
			p_UI->Draw(6, 480, 300, 500, 500, 0, 0, 500, 500);//2D画像(UI)を表示//UIは一番下にしないと画像が透けてしまう。

		}
		#ifdef _DEBUG
		p_UI->DrawScore(ZombieNokori, 3, 30.0f, 30.0f, true);//残りのゾンビ数を表示
		p_UI->DrawScore(EnemyNokori, 3, 30.0f, 100.0f, true);//残りの敵数を表示
		p_UI->DrawScore(HP_UI, 3, 30.0f, 170.0f, true);//残りのHPを表示
		#endif // DEBUG
		SetShot_UI(p_Shot->GetShot_UI());
		p_UI->DrawScore(Shot_UI, 3, 1285.0f, 870.0f, true);//弾数を表示
		SetZirai_UI(p_Zirai->GetZirai_UI());
		p_UI->DrawScore(Zirai_UI, 1, 1410.0f, 790.0f, true);//地雷数を表示
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(12, 1200, 860, 300, 5, 0, 0, 300, 300);//2D画像(UI)を表示//UIは一番下にしないと画像が透けてしまう。

	}

	//ゲームクリアー
	if (nflag == 2)
	{
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(
			8,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			1280,//元の画像の切り取りたい幅
			720 //元の画像の切り取りたい高さ
		);
	}

	//ゲームオーバー
	if (nflag == 3)
	{
		p_UI->SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));//ポリゴンカラーの設定
		p_UI->Draw(
			9,//使うテクスチャ,
			0.0f, //x座標,
			0.0f,//y座標,
			1500,//テクスチャの表示する横の長さ
			1000,//テクスチャの表示する縦の長さ
			0,//元の画像の切り取り開始場所（横）（画像の左から数える）
			0,//元の画像の切り取り開始場所（縦）（画像の上から数える）
			1280,//元の画像の切り取りたい幅
			720 //元の画像の切り取りたい高さ
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
		p_ZombieKage->SetPos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//ゾンビ影の初期座標をセット
	}

	p_Enemy->ResetParameters();

	p_EnemyKage->ResetParameters();
	p_EnemyKage->SetEnemyPos(p_Enemy->GetEnemyPos());//エネミー影の初期座標をセット

	p_Item->ResetParameters();

	p_ItemMarker->ResetParameters();
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_ItemMarker->SetPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//アイテムマーカーの座標をセット
	}

	p_RecoveryItem->ResetParameters();

	p_RecoveryItemMarker->ResetParameters();
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_RecoveryItemMarker->SetPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//回復アイテムマーカーの座標をセット
	}

	p_Player->ResetParameters();
	p_Player->SetPlayerPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//移動用数値初期化

	p_Shot->ResetParameters();
	p_Shot->SetPlayerPos(p_Player->GetPlayerPos());//弾の初期座標をセット
	p_Shot->SetPlayerFront(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//弾の前ベクトルを初期化

	p_Zirai->ResetParameters();
	p_Zirai->SetPlayerPos(p_Player->GetPlayerPos());//地雷の初期座標をセット

	p_Bakuhu->ResetParameters();
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_Bakuhu->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//爆風の初期座標をセット
	}

	p_AtariHantei->ResetParameters();
	p_AtariHantei->SetPlayerPos(p_Player->GetPlayerPos());//あたり判定プレイヤーの初期座標をセット
	p_AtariHantei->SetEnemyPos(p_Enemy->GetEnemyPos());//あたり判定エネミーの初期座標をセット
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)
	{
		p_AtariHantei->SetZombiePos(p_Zombie->GetLoop(Loop), p_Zombie->GetPosX(Loop), p_Zombie->GetPosY(Loop), p_Zombie->GetPosZ(Loop));//あたり判定ゾンビの初期座標をセット
	}
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)
	{
		p_AtariHantei->SetItemPos(p_Item->GetLoop(Loop), p_Item->GetPosX(Loop), p_Item->GetPosY(Loop), p_Item->GetPosZ(Loop));//あたり判定アイテムの初期座標をセット
	}
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)
	{
		p_AtariHantei->SetRecoveryItemPos(p_RecoveryItem->GetLoop(Loop), p_RecoveryItem->GetPosX(Loop), p_RecoveryItem->GetPosY(Loop), p_RecoveryItem->GetPosZ(Loop));//あたり判定回復アイテムの初期座標をセット
	}
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)
	{
		p_AtariHantei->SetZiraiPos(p_Zirai->GetLoop(Loop), p_Zirai->GetPosX(Loop), p_Zirai->GetPosY(Loop), p_Zirai->GetPosZ(Loop));//あたり判定地雷の初期座標をセット
	}
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		p_AtariHantei->SetShotPos(p_Shot->GetLoop(Loop), p_Shot->GetPosX(Loop), p_Shot->GetPosY(Loop), p_Shot->GetPosZ(Loop));//あたり判定弾の初期座標をセット
	}


}