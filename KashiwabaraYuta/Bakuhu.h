#pragma once
//=============================================================================
//  
// 爆風の描画
//
//=============================================================================

#ifndef _BAKUHU_H_
#define _BAKUHU_H_
#include "Zirai.h"
class Bakuhu
{
public:
	Bakuhu();
	~Bakuhu();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット

	//地雷の座標を持ってくる
	void SetZiraiPos(int num, float x, float y, float z)
	{
		m_Bakuhu[num].Pos.x = x;
		m_Bakuhu[num].Pos.y = y;
		m_Bakuhu[num].Pos.z = z;
	}

	//爆風の描画状態を持ってくる
	void SetBakuhuDraw(int num, bool draw)
	{
		m_Bakuhu[num].Draw = draw;
	}

private:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	typedef struct
	{
		D3DXVECTOR3 Pos;//座標
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		bool Draw = false;//表示・非表示
		float Timer = 0.0f;
	}BAKUHU_DATA;

	BAKUHU_DATA m_Bakuhu[ZIRAI_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;


};

#endif // _BAKUHU_H_