#pragma once
//=============================================================================
//  
// ゾンビの影の描画
//
//=============================================================================

#ifndef _ZOMBIEKAGE_H_
#define _ZOMBIEKAGE_H_
#include "Zombie.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

class ZombieKage
{
public:
	ZombieKage();
	~ZombieKage();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	//ゾンビ影の座標を持ってくる
	void SetPos(int su, float x, float y, float z)
	{
		m_ZombieKage[su].ZombiePos.x = x;//xの値をEnemyPos.xに入れる
		m_ZombieKage[su].ZombiePos.y = y;//yの値をEnemyPos.yに入れる
		m_ZombieKage[su].ZombiePos.z = z;//zの値をEnemyPos.zに入れる
	}
	//ゾンビ影の描画状態を持ってくる
	void SetZombieKageDraw(int su, bool draw)
	{
		m_ZombieKage[su].Draw = draw;
	}

private:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	typedef struct  //構造体の定義
	{
		FLOAT x, y, z;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;//テクスチャ貼り付け座標
	}CUSTOMVERTEX;

	typedef struct  //構造体の定義
	{
		CUSTOMVERTEX vertices[4];//構造体の構造体
		D3DXVECTOR3 ZombiePos;
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		bool Draw;//ボンベの表示・非表示
	}ZOMBIEKAGE;

	ZOMBIEKAGE m_ZombieKage[ZOMBIE_NUM];
	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数



};
#endif // _ENEMYKAGE_H_
