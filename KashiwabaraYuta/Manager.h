#pragma once
//=============================================================================
//  
// マネージャークラス
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
// 基底クラス
//*****************************************************************************
class Manager
{
public:
	Manager();//コンストラクタ
	~Manager();//デストラクタ
	void Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	void ResetParameters();//パラメータのリセット
	//あたり判定からのフラグを持ってくる処理
	void Setnflag(int num)
	{
		nflag = num;
	}
	//カメラから肩越しかどうかを持ってくる処理
	void SetTPS_UI(bool draw)
	{
		TPS_UI = draw;
	}
	//Shotから弾薬の残数を持ってくる処理
	void SetShot_UI(int num)
	{
		Shot_UI = num;
	}
	//Ziraiから地雷の残数を持ってくる処理
	void SetZirai_UI(int num)
	{
		Zirai_UI = num;
	}
	//あたり判定から残りHPを持ってくる処理
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
	int nflag = 0;//タイトル⇒ゲームプレイ⇒ゲームオーバー⇒タイトル
	int nflagTime = 0;//シーン遷移用タイム

	bool g_bPress = true;//タイトルテクスチャのON/OFFの変更をする
	int g_nCnt = 0;//タイトルのON/OFFの時間をカウントをする
	bool TPS_UI = false;//肩越しカメラのON/OFFを調べる
	int HP_UI = HP_NUM;//残りHP
	int Shot_UI = SHOT_NUM;//残り弾数
	int Zirai_UI = ZIRAI_NUM;//残りの地雷数
	int ZombieNokori = ZOMBIE_NUM;//残りゾンビ数
	int EnemyNokori = ENEMY_NUM;//残りの敵数
	bool test = false;

	//サウンド
	int count0 = 0;//音楽用変数
	int count1 = 0;//音楽用変数
	int count2 = 0;//音楽用変数
	int count3 = 0;//音楽用変数
	int count4 = 0;//音楽用変数
	//サウンド
};
#endif // _MANAGER_H_