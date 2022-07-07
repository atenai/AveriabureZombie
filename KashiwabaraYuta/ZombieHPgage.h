#pragma once
//=============================================================================
//  
// ゾンビHPゲージの描画
//
//=============================================================================

#ifndef _ZOMBIEHPGAGE_H_
#define _ZOMBIEHPGAGE_H_
#include "Zombie.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

class ZombieHPgage
{
public:
	ZombieHPgage();
	~ZombieHPgage();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	//ゾンビHPゲージの座標を持ってくる
	void SetPos(int su, float x, float y, float z)
	{
		m_ZombieHP[su].ZombiePos.x = x;//xの値をEnemyPos.xに入れる
		m_ZombieHP[su].ZombiePos.y = y;//yの値をEnemyPos.yに入れる
		m_ZombieHP[su].ZombiePos.z = z;//zの値をEnemyPos.zに入れる
	}//ゾンビHPゲージの残りを持ってくる
	void SetNokoriZombieHP(int su, float x)
	{
		m_ZombieHP[su].Scale = x / 100;
	}
private:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	typedef struct  //構造体の定義
	{
		FLOAT x, y, z;
		DWORD color;
		D3DXVECTOR2 texcoord;//テクスチャ貼り付け座標
	}CUSTOMVERTEX;

	typedef struct  //構造体の定義
	{
		CUSTOMVERTEX vertices[4];//構造体の構造体
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		float Scale;//左上の大きさ
		D3DXVECTOR3 ZombiePos;
	}ZOMBIEHP;

	ZOMBIEHP m_ZombieHP[ZOMBIE_NUM];

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数

};
#endif // _HPGAGE_H_

