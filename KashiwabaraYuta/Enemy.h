#pragma once
//=============================================================================
//  
// エネミーの描画
//
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ENEMY_NUM (1)
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	BOOL JikiProbe(float *pfoundangley);//敵キャラに自キャラを探させる
	//エネミーの座標を持ってくる
	void SetPos(D3DXVECTOR3 Pos)
	{
		EnemyPos = Pos;
	}
	//エネミーの座標を送る
	D3DXVECTOR3 GetEnemyPos()
	{
		return EnemyPos;//リターンは型名を書く
	}
	//プレイヤー座標を持ってくる
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}
	//敵の描画状態を持ってくる
	void SetEnemyDraw(bool draw)
	{
		EnemyDraw = draw;

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
// メンバ変数
//*****************************************************************************
//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//ワールド行列
	D3DXMATRIX m_mtxWorld;

	//スケール
	D3DXMATRIX m_mtxWorldS;//拡大用変数

	//ローテーション
	float Ykaitenidou = 0.0f;//Y回転移動用数値
	D3DXMATRIX m_mtxWorldR;//回転用変数

	//トランスレーション
	D3DXMATRIX m_mtxWorldT;//移動用変数
	D3DXVECTOR3 EnemyPos;

	D3DXVECTOR3 PlayerPos;

	bool EnemyDraw = true;//敵の表示・非表示


	//敵キャラの思考ルーチンを作る
	float anglesp = D3DX_PI / 2;//90度/s
	float searchpivot = 0.0f;//探索軸
	int searchturn = -1;//探索回転方向(-1:反時計回り、1時計回り)

	enum
	{
		TK_CHASE,//追跡モード(自キャラを見つけている)
		TK_SEARCH//探索モード(自キャラを見つけていない)
	};
	int tekimode = TK_SEARCH;//敵キャラ行動モード

	//バウンディングボックス(ABB)
	D3DXVECTOR3 IePos;//家の座標
	D3DXVECTOR3 IeMin;//家の最小頂点
	D3DXVECTOR3 IeMax;//家の最大頂点
	D3DXVECTOR3 Ie2Pos;//家2の座標
	D3DXVECTOR3 Ie2Min;//家2の最小頂点
	D3DXVECTOR3 Ie2Max;//家2の最大頂点
};



#endif // _ENEMY_H_

