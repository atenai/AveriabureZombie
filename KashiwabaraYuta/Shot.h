#pragma once
//=============================================================================
//  
// 弾の描画
//
//=============================================================================

#ifndef _SHOT_H_
#define _SHOT_H_

#define SHOT_NUM 200//弾の数

class Shot
{
public:
	Shot();
	~Shot();
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
	//弾の位置座標数値Xを送る
	float GetPosX(int Loop)
	{
		return m_Shot[Loop].ShotPos.x;
	}
	//弾の位置座標数値Yを送る
	float GetPosY(int Loop)
	{
		return m_Shot[Loop].ShotPos.y;
	}
	//弾の位置座標数値Zを送る
	float GetPosZ(int Loop)
	{
		return m_Shot[Loop].ShotPos.z;
	}
	//弾の描画状態を持ってくる
	void SetShotDraw(int kazu, bool draw)
	{
		m_Shot[kazu].Draw = draw;
	}
	//弾のあたり判定状態を持ってくる
	void SetShotAtariHantei(int kazu, bool draw)
	{
		m_Shot[kazu].AtariHantei = draw;
	}
	//弾の描画状態を送る
	bool GetShotDraw(int kazu)
	{
		return m_Shot[kazu].Draw;
	}
	//弾のあたり判定状態を送る
	bool GetShotAtariHantei(int Loop)
	{
		return m_Shot[Loop].AtariHantei;
	}

	void SetTamaHuyasu(int su)
	{
		num = num - su;//弾数を減らす
		if (num < 0)//numが0以下の場合
		{
			num = 0;//numを0にする
		}
		Shot_UI = Shot_UI + su;//弾数UI表示用変数を増やす
		if (Shot_UI > SHOT_NUM)//弾数UI表示がSHOT_NUMを越えたら
		{
			Shot_UI = SHOT_NUM;//弾数UI表示をSHOT_NUMと同じにする
		}
	}

	//プレイヤーの前ベクトルを持ってくる
	void SetPlayerFront(D3DXVECTOR3 ret)
	{
		PlayerFront = ret;
	}

	//弾の残り弾数のUIを送る処理
	int GetShot_UI()
	{
		return Shot_UI;
	}

private:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	typedef struct
	{
		D3DXVECTOR3 ShotPos;//弾の座標
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		bool Draw = false;//弾の表示・非表示
		bool AtariHantei = false;//弾のあたり判定
		D3DXVECTOR3 muki;//プレイヤーの正面ベクトルを各弾に入れる変数
	}SHOT_DATA;

	SHOT_DATA m_Shot[SHOT_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	int num = 0;//弾の弾数目
	int Shot_UI = SHOT_NUM;//弾数UI表示用変数

	D3DXVECTOR3 PlayerPos;//プレイヤーの座標
	D3DXVECTOR3 PlayerFront;//プレイヤーの前ベクトル

	//サウンド
	int oto0;//音楽用変数
	int oto1;//音楽用変数
};


#endif // _SHOT_H_

