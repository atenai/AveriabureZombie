#pragma once
//=============================================================================
//  
// HPゲージの描画
//
//=============================================================================
#ifndef _HPGAGE_H_
#define _HPGAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

class EnemyHPgage
{
public:
	EnemyHPgage();
	~EnemyHPgage();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	//エネミーの座標を持ってくる
	void SetEnemyPos(D3DXVECTOR3 pos)
	{
		EnemyPos = pos;
	}
	//エネミーHPゲージの残量を持ってくる
	void SetNokoriEnemyHP(float x)
	{
		Scale = x / 100.0f;
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

	CUSTOMVERTEX vertices[4];//構造体の構造体

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数

	D3DXVECTOR3 EnemyPos;

	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxworldT;

	float Scale = 0.0f;//左上の大きさ
};
#endif // _HPGAGE_H_
