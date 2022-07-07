#pragma once
//=============================================================================
//  
// 雨の描画
//
//=============================================================================

#ifndef _AME_H_
#define _AME_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

#define AME_NUM 100

//*****************************************************************************
// 基底クラス
//*****************************************************************************
//雨クラス
class Ame
{
public:
	Ame();//コンストラクタ
	~Ame();//デストラクタ
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理

	void AmesetTimer(DWORD time);
	BOOL AmeisTimerGoal();
private:
//*****************************************************************************
// 構造体
//*****************************************************************************
//設計図を作る
	struct CUSTOMVERTEX //構造体の定義
	{
		FLOAT x, y, z;
		DWORD color;
		D3DXVECTOR2 texcoord;//テクスチャ貼り付け座標
	};

	typedef struct {
		D3DXVECTOR3 pos;//座標
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		BOOL used;//使用中を示すフラグ
	}AME_DATA;

	AME_DATA m_Ame[AME_NUM];//構造体でアイテムをいくつ作るかを宣言

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//ポリゴン表示用変数
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数

	//雨用
	DWORD Ameg_goaltimes;

};
#endif // _AME_H_
