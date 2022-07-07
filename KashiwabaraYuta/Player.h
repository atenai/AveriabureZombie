#pragma once
//=============================================================================
//  
// プレイヤーの描画
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PARTS_NUM 15 //パーツの数

//*****************************************************************************
// 基底クラス
//*****************************************************************************
//プレイヤークラス
class Player
{
public:
	Player();//コンストラクタ
	~Player();//デストラクタ
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット

	D3DXVECTOR3 GetFront(void)//プレイヤーの前ベクトルを送る
	{
		D3DXVECTOR3 ret = D3DXVECTOR3(m_Part[0].World._31, m_Part[0].World._32, m_Part[0].World._33);

		D3DXVec3Normalize(&ret, &ret);

		return ret;
	}


	//プレイヤーの座標を持ってくる
	void SetPlayerPos(D3DXVECTOR3 Pos)
	{
		PlayerPos = Pos;
	}
	//プレイヤーの座標を送る
	D3DXVECTOR3 GetPlayerPos()
	{
		return PlayerPos;//リターンは型名を書く
	}
	//プレイヤーと家のバウンディングボックスあたり判定の結果を持ってくる
	void SetPlayerIeBoxAtari(bool hit)
	{
		PlayerIeBoxAtari = hit;
	}
	//プレイヤーと家2のバウンディングボックスあたり判定の結果を持ってくる
	void SetPlayerIe2BoxAtari(bool hit)
	{
		PlayerIe2BoxAtari = hit;
	}
	//プレイヤーの最小頂点を送る
	D3DXVECTOR3 GetPlayerMin()
	{
		return PlayerMin;
	}
	//プレイヤーの最大頂点を送る
	D3DXVECTOR3 GetPlayerMax()
	{
		return PlayerMax;
	}

	void SetPlayerSita(bool hit)
	{
		PlayerSita = hit;
	}
	void SetPlayerUe(bool hit)
	{
		PlayerUe = hit;
	}
	void SetPlayerMigi(bool hit)
	{
		PlayerMigi = hit;
	}
	void SetPlayerHidari(bool hit)
	{
		PlayerHidari = hit;
	}

	////プレイヤーの回転座標と移動座標をカメラに送る関数
	D3DXMATRIX GetMtxWorld() 
	{
		return m_Part[0].World;
	}

private:
//*****************************************************************************
// メンバ変数
//*****************************************************************************

	//バウンディングボックスのあたり判定
	D3DXVECTOR3 PlayerMin;
	D3DXVECTOR3 PlayerMax;
	bool PlayerIeBoxAtari = false;
	bool PlayerIe2BoxAtari = false;

	bool PlayerSita = false;
	bool PlayerMigi = false;
	bool PlayerUe = false;
	bool PlayerHidari = false;

	//スケール
	void Scaling();//拡縮処理

	//ローテーション
	void Rotation();//回転処理
	float Ykaitenidou = 0.0f;//Y回転移動用数値

	//トランスレーション
	void Translation();//移動処理
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動先数値

	//キーフレームアニメーション
	int m_Key = 2;//キーフレームの各座標の変数
	int m_Frame = 0;//フレーム間を動かすための変数

	struct PARTS
	{
		//Xモデル表示用変数
		LPD3DXMESH pMesh = NULL;      //メッシュを受けとる変数
		DWORD dwNumMaterials = 0;	 //マテリアル数
		D3DMATERIAL9* pMeshMaterials = NULL;
		LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;//マテリアルを受け取る
		D3DXMATERIAL* d3dxMaterials;
		//Xモデル表示用変数

		D3DXVECTOR3 Position;//座標変数
		D3DXVECTOR3 Rotate;//回転変数
		D3DXMATRIX World;//ワールド行列
		D3DXMATRIX Matrix;//行列
		D3DXMATRIX Transform;//移動行列
		D3DXMATRIX Rotation;//回転行列
		D3DXMATRIX Scale;//拡縮行列
		PARTS *Parent;//親を入れる
	};
	PARTS m_Part[PARTS_NUM];//パーツ構造体を10個つくる


	//1パーツの座標と回転
	typedef struct
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Rotation;
	}KEY;

	//キーフレーム
	typedef struct
	{
		int Frame;//補間フレーム数
		KEY Key[PARTS_NUM];//上の移動座標と回転座標が入っている
	}KEY_FRAME;

	KEY_FRAME m_KeyFrameWalk[PARTS_NUM] = //構造体でアイテムをいくつ作るかを宣言
	{
		//m_Key0
			{
			//Frame = 30 m_Frame = 0 を比較して Frame >= m_Frameの間だけパーツを動かす
			30,
			{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//胴体
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//頭
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.7f,-0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右手
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左手
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右足
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左足
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//銃
	}
},

//m_Key1
{
	//Frame = 30 m_Frame = 0 を比較して Frame >= m_Frameの間だけパーツを動かす
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//胴体
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//頭
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.65f,-0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右手
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左手
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右足
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(-1.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左足
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//銃
	}
},

//m_Key2//始まり
{
	//Frame = 30 m_Frame = 0 を比較して Frame >= m_Frameの間だけパーツを動かす
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//胴体
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//頭
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.6f,-0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右手
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左手
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右足
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左足
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//銃
	}
},

//m_Key3
{
	//Frame = 30 m_Frame = 0 を比較して Frame >= m_Frameの間だけパーツを動かす
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//胴体
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//頭
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.65f,-0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右手
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左手
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(-1.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右足
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左足
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//銃
	}
},

//m_Key4
{
	//Frame = 30 m_Frame = 0 を比較して Frame >= m_Frameの間だけパーツを動かす
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//胴体
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//頭
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.7f,-0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//右腕
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右手
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//左腕
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左手
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//右足
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左太もも
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//左足
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//銃
	}
}
	};

	KEY_FRAME *m_KeyFrame = m_KeyFrameWalk;

	float test = 0.0f;
};

#endif // _PLAYER_H_
