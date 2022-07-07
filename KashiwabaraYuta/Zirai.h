#pragma once
//=============================================================================
//  
// 地雷の描画
//
//=============================================================================

#ifndef _ZIRAI_H_
#define _ZIRAI_H_

#define ZIRAI_NUM 6//地雷の数

class Zirai
{
public:
	Zirai();
	~Zirai();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	//プレイヤーの位置座標数値を持ってくる
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}

	int GetLoop(int Loop)
	{
		return Loop;
	}
	//地雷の位置座標数値Xを送る
	float GetPosX(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.x;
	}
	//地雷の位置座標数値Yを送る
	float GetPosY(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.y;
	}
	//地雷の位置座標数値Zを送る
	float GetPosZ(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.z;
	}
	//地雷の描画状態を持ってくる
	void SetZiraiDraw(int kazu, bool draw)
	{
		m_Zirai[kazu].Draw = draw;
	}
	//地雷のあたり判定状態を持ってくる
	void SetZiraiAtariHantei(int kazu, bool draw)
	{
		m_Zirai[kazu].AtariHantei = draw;
	}
	//地雷の描画状態をManager.cppに送る
	bool GetZiraiDraw(int kazu)
	{
		return m_Zirai[kazu].Draw;
	}
	//地雷のあたり判定状態をManager.cppに送る
	bool GetZiraiAtariHantei(int Loop)
	{
		return m_Zirai[Loop].AtariHantei;
	}
	//地雷数を送る
	int GetZirai_UI() 
	{
		return m_Zirai_UI;
	}

public:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	typedef struct
	{
		D3DXVECTOR3 ZiraiPos;//座標
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		bool Draw = false;//地雷の表示・非表示
		bool AtariHantei = false;//地雷のあたり判定
	}ZIRAI_DATA;

	ZIRAI_DATA m_Zirai[ZIRAI_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	int m_num = 0;//地雷の地雷数目
	int m_ZiraiTime = 0;//地雷のチャージ時間
	int m_Zirai_UI = ZIRAI_NUM;//地雷数表示用変数

	D3DXVECTOR3 PlayerPos;//プレイヤーの座標

	//サウンド
	int m_count;//音楽用変数
};
#endif // _ZIRAI_H_

