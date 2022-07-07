#pragma once
//=============================================================================
//  
// プレイヤー影の描画
//
//=============================================================================

#ifndef _PLAYERKAGE_H_
#define _PLAYERKAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定


class PlayerKage
{
public:
	PlayerKage();
	~PlayerKage();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw();//描画処理
	void Uninit(void);//終了処理
	//プレイヤーの座標を持ってくる
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
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

	CUSTOMVERTEX vertices[4];//構造体の構造体

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数

	D3DXVECTOR3 PlayerPos;//プレイヤーの座標

	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxworldT;


	D3DCOLOR m_color = D3DCOLOR_RGBA(100, 100, 100, 100);

};
#endif // _PLAYERKAGE_H_
