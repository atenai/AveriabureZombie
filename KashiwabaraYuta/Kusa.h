#pragma once
//=============================================================================
//  
// 草の描画
//
//=============================================================================

#ifndef _KUSA_H_
#define _KUSA_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

#define KUSA_NUM 100//草の数を指定

//*****************************************************************************
// 基底クラス
//*****************************************************************************
//草クラス
class Kusa
{
public:
	Kusa();//コンストラクタ
	~Kusa();//デストラクタ
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理

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


	typedef struct {
		D3DXVECTOR3 pos;//座標
		float Scale;//左上の大きさ
		CUSTOMVERTEX vertices[6];//構造体の構造体
		VOID* pVertices;
		LPDIRECT3DVERTEXBUFFER9 pVB;
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
	}KUSA_DATA;

	KUSA_DATA m_Kusa[KUSA_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数
};

//*****************************************************************************
// 派生クラス
//*****************************************************************************
//草1クラス
class Kusa1:public Kusa
{
public:
	Kusa1();//コンストラクタ
	~Kusa1();//デストラクタ
	void Init(void);//初期化処理
private:

};
//草2クラス
class Kusa2 :public Kusa
{
public:
	Kusa2();//コンストラクタ
	~Kusa2();//デストラクタ
	void Init(void);//初期化処理
private:

};
//草3クラス
class Kusa3 :public Kusa
{
public:
	Kusa3();//コンストラクタ
	~Kusa3();//デストラクタ
	void Init(void);//初期化処理
private:

};
//木クラス
class Tree :public Kusa
{
public:
	Tree();//コンストラクタ
	~Tree();//デストラクタ
	void Init(void);//初期化処理
private:

};


#endif // _KUSA_H_

