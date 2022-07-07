#pragma once
//=======================================================================================
//						あたり判定描画
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
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Uninit(void);//終了処理
	void ResetParameters();//パラメータのリセット

	//プレイヤーの位置座標数値を持ってくる
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}

	//敵///////////////////////////////////////////////////////
	//敵の位置座標数値を持ってくる
	void SetEnemyPos(D3DXVECTOR3 pos)
	{
		EnemyPos = pos;
	}
	//敵の描画状態をManager.cppに送る
	bool GetEnemyDraw()
	{
		return EnemyDraw;
	}
	//敵の影描画状態をManager.cppに送る
	bool GetEnemyKageDraw()
	{
		return EnemyKageDraw;
	}
	//敵HPゲージの残り残量を持ってくる処理
	float GetEnemyHPgage()
	{
		return EnemyHP;
	}
	//敵の残り数を送る処理
	int GetEnemyNokori() 
	{
		return EnemyNokori;
	}
	//敵///////////////////////////////////////////////////////

	//アイテム///////////////////////////////////////////////////////
	//アイテムの位置座標数値を持ってくる
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
	//アイテムの描画状態をManager.cppに送る
	bool GetItemDraw(int Loop)
	{
		return Itematari[Loop].ItemDraw;
	}
	//アイテムマーカー描画状態をManager.cppに送る
	bool GetItemMarkerDraw(int Loop)
	{
		return Itematari[Loop].ItemMarkerDraw;
	}
	//アイテム///////////////////////////////////////////////////////

	//回復アイテム///////////////////////////////////////////////////////
	//回復アイテムの位置座標数値を持ってくる
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
	//回復アイテムの描画状態をManager.cppに送る
	bool GetRecoveryItemDraw(int Loop)
	{
		return RecoveryItematari[Loop].ItemDraw;
	}
	//回復アイテムマーカー描画状態をManager.cppに送る
	bool GetRecoveryItemMarkerDraw(int Loop)
	{
		return RecoveryItematari[Loop].ItemMarkerDraw;
	}
	//回復アイテム///////////////////////////////////////////////////////

	//ゾンビ///////////////////////////////////////////////////////
	//ゾンビの位置座標数値を持ってくる
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
	//ゾンビの描画状態をManager.cppに送る
	bool GetZombieDraw(int Loop)
	{
		return Zombieatari[Loop].ZombieDraw;
	}
	//敵の影描画状態をManager.cppに送る
	bool GetZombieKageDraw(int Loop)
	{
		return Zombieatari[Loop].ZombieKageDraw;
	}
	//ゾンビHPゲージの残り残量を持ってくる処理
	float GetZombieHPgage(int Loop)
	{
		return Zombieatari[Loop].ZombieHP;
	}
	//ゾンビの残り数を送る処理
	int GetZombieNokori()
	{
		return ZombieNokori;
	}
	//ゾンビ///////////////////////////////////////////////////////

	//地雷///////////////////////////////////////////////////////
	//地雷の位置座標数値を持ってくる
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
	//地雷の描画状態をManager.cppに送る
	bool GetZiraiDraw(int Loop)
	{
		return Ziraiatari[Loop].Draw;
	}
	//地雷のあたり判定状態をManager.cppに送る
	bool GetZiraiAtariHantei(int Loop)
	{
		return Ziraiatari[Loop].AtariHantei;
	}
	//地雷の描画状態を持ってくる
	void SetZiraiDraw(int Loop, bool draw)
	{
		Ziraiatari[Loop].Draw = draw;
	}
	//地雷のあたり判定状態を持ってくる
	void SetZiraiAtariHantei(int Loop, bool hit)
	{
		Ziraiatari[Loop].AtariHantei = hit;
	}
	//爆風の描画状態をManager.cppに送る
	bool GetBakuhuDraw(int Loop)
	{
		return Ziraiatari[Loop].BakuhuDraw;
	}
	//地雷///////////////////////////////////////////////////////

	//弾///////////////////////////////////////////////////////
	//弾の位置座標数値を持ってくる
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
	//弾の描画状態をManager.cppに送る
	bool GetShotDraw(int Loop)
	{
		return Shotatari[Loop].Draw;
	}
	//弾のあたり判定状態をManager.cppに送る
	bool GetShotAtariHantei(int Loop)
	{
		return Shotatari[Loop].AtariHantei;
	}
	//弾の描画状態を持ってくる
	void SetShotDraw(int Loop, bool draw)
	{
		Shotatari[Loop].Draw = draw;
	}
	//弾のあたり判定状態を持ってくる
	void SetShotAtariHantei(int Loop, bool hit)
	{
		Shotatari[Loop].AtariHantei = hit;
	}

	//回復させる弾薬数を送る
	int Getammunition()
	{
		return ammunition;
	}
	//弾///////////////////////////////////////////////////////

	//家///////////////////////////////////////////////////////
	//家の位置座標数値を持ってくる
	void SetIePos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	//家2の位置座標数値を持ってくる
	void SetIe2Pos(D3DXVECTOR3 pos)
	{
		Ie2Pos = pos;
	}
	//家///////////////////////////////////////////////////////

	//HPの数値を送る
	int GetHP()
	{
		return HP;
	}

private:
//*****************************************************************************
// 構造体
//*****************************************************************************

	//アイテム///////////////////////////////////////
	typedef struct//設計図を作る
	{
		float posx;//座標x
		float posy;//座標y
		float posz;//座標z
		bool bHit;//あたり判定
		bool ItemDraw = true;//アイテムの描画状態
		bool ItemMarkerDraw = true;//アイテムマーカーの描画状態
		bool ItemAtariHantei = true;//あたり判定の状態
	}ITEM_ATARI;

	ITEM_ATARI Itematari[ITEM_NUM];//構造体でアイテムをいくつ作るかを宣言
	//アイテム///////////////////////////////////////

	//回復アイテム///////////////////////////////////////

	ITEM_ATARI RecoveryItematari[RECOVERYITEM_NUM];//構造体でアイテムをいくつ作るかを宣言

	//回復アイテム///////////////////////////////////////

	//ゾンビ///////////////////////////////////////
	typedef struct//設計図を作る
	{
		float posx;//ゾンビの座標x
		float posy;//ゾンビの座標y
		float posz;//ゾンビの座標z
		bool bHit;//あたり判定
		bool ZombieDraw = true;//ゾンビの描画状態
		bool ZombieKageDraw = true;//ゾンビ影の描画状態
		bool ZombieAtariHantei = true;//あたり判定の状態
		float ZombieHP = 100.0f;//ゾンビのHP状態
	}ZOMBIE_ATARI;

	ZOMBIE_ATARI Zombieatari[ZOMBIE_NUM];//構造体でアイテムをいくつ作るかを宣言
	//ゾンビ///////////////////////////////////////

	//地雷///////////////////////////////////////
	typedef struct//設計図を作る
	{
		float posx;//座標x
		float posy;//座標y
		float posz;//座標z
		bool bHit;//あたり判定
		bool Draw = false;//描画状態
		bool AtariHantei = false;//あたり判定の状態
		bool BakuhuDraw = false;//爆風の描画状態
	}DATA_ATARI;

	DATA_ATARI Ziraiatari[ZIRAI_NUM];//構造体でアイテムをいくつ作るかを宣言
	//地雷///////////////////////////////////////

	//弾/////////////////////////////////////////
	DATA_ATARI Shotatari[SHOT_NUM];//構造体でアイテムをいくつ作るかを宣言

	int ammunition = 0;//弾薬を回復する数
	//弾/////////////////////////////////////////

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Player
	D3DXVECTOR3 PlayerPos;

	//Enemy
	D3DXVECTOR3 EnemyPos;//エネミーの座標
	bool EnemyDraw = true;//エネミーの描画状態
	bool EnemyKageDraw = true;//エネミー影の描画状態
	bool EnemyAtariHantei = true;//エネミーのあたり判定の状態
	float EnemyHP = 200.0f;//エネミーのHP状態

	//家1
	D3DXVECTOR3 IePos;
	//家2
	D3DXVECTOR3 Ie2Pos;

	int ZombieNokori = ZOMBIE_NUM;//ゾンビの残り数
	int EnemyNokori = ENEMY_NUM;//敵の残り数

	int HP = HP_NUM;//残りHP

	//サウンド
	int oto0;//音楽用変数
	int oto1;//音楽用変数

	
};

#endif //_ATARIHANTEI_H_