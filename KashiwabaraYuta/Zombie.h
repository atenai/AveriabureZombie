#pragma once
//=============================================================================
//  
// ゾンビの描画
//
//=============================================================================

#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#define ZOMBIE_NUM (7)//ゾンビの数

class Zombie
{
public:
	Zombie();
	~Zombie();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	BOOL ZombieProbe(float *pfoundangley, int i2);//敵キャラに自キャラを探させる
	int GetLoop(int Loop)
	{
		return Loop;
	}
	//ゾンビの位置座標数値Xを送る
	float GetPosX(int Loop)
	{
		return m_Zombie[Loop].pos.x;
	}
	//ゾンビの位置座標数値Yを送る
	float GetPosY(int Loop)
	{
		return m_Zombie[Loop].pos.y;
	}
	//ゾンビの位置座標数値Zを送る
	float GetPosZ(int Loop)
	{
		return m_Zombie[Loop].pos.z;
	}
	//プレイヤーの位置座標数値を持ってくる
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}
	//ゾンビの描画状態を持ってくる
	void SetZombieDraw(int num, bool draw)
	{
		m_Zombie[num].Draw = draw;
	}


	void SetIePos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	void SetIeMin(D3DXVECTOR3 min)
	{
		IeMin = min;
	}
	void SetIeMax(D3DXVECTOR3 max)
	{
		IeMax = max;
	}

	void SetIe2Pos(D3DXVECTOR3 pos)
	{
		Ie2Pos = pos;
	}
	void SetIe2Min(D3DXVECTOR3 min)
	{
		Ie2Min = min;
	}
	void SetIe2Max(D3DXVECTOR3 max)
	{
		Ie2Max = max;
	}
private:
//*****************************************************************************
// 構造体
//*****************************************************************************
	//しっかり初期化しないとデバッグモードでバグる
	enum
	{
		TK_CHASE,//追跡モード(自キャラを見つけている)
		TK_SEARCH//探索モード(自キャラを見つけていない)
	};

	//設計図を作る
	typedef struct
	{
		D3DXVECTOR3 pos;//座標
		float Ykaitenidou = 0.0f;//Y回転移動用数値
		//敵キャラの思考ルーチンを作る
		float anglesp = D3DX_PI / 2;//90度/s
		float searchpivot = 0.0f;//探索軸
		int searchturn = -1;//探索回転方向(-1:反時計回り、1時計回り)
		float looptime = 0.01f;//1ループにかかる時間(秒)
		float fangley = 0.0f;
		int tekimode = TK_SEARCH;//敵キャラ行動モード
		D3DXVECTOR3 vec1;
		D3DXVECTOR3 vec2;

		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		bool Draw = true;//表示・非表示
	}ZOMBIE_DATA;

	ZOMBIE_DATA m_Zombie[ZOMBIE_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;


	D3DXVECTOR3 PlayerPos;
	//バウンディングボックス(ABB)
	D3DXVECTOR3 IePos;//家の座標
	D3DXVECTOR3 IeMin;//家の最小頂点
	D3DXVECTOR3 IeMax;//家の最大頂点
	D3DXVECTOR3 Ie2Pos;//家2の座標
	D3DXVECTOR3 Ie2Min;//家2の最小頂点
	D3DXVECTOR3 Ie2Max;//家2の最大頂点

};
#endif // _ZOMBIE_H_
