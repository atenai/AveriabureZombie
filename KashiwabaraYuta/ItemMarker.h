#pragma once
//=============================================================================
//  
// アイテムマーカー
//
//=============================================================================

#ifndef _ITEMMARKER_H_
#define _ITEMMARKER_H_
#include "Item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定


class ItemMarker
{
public:
	ItemMarker();
	~ItemMarker();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	//アイテムマーカー座標持ってくる
	void SetPos(int num, float x, float y, float z) 
	{
		m_ItemMarker[num].Pos.x = x;
		m_ItemMarker[num].Pos.y = y;
		m_ItemMarker[num].Pos.z = z;
	}
	//アイテムマーカーの描画状態を持ってくる
	void SetItemMarkerDraw(int num, bool draw)
	{
		m_ItemMarker[num].Draw = draw;
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

	typedef struct  //構造体の定義
	{
		CUSTOMVERTEX vertices[4];//構造体の構造体
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		float Scale;//左上の大きさ
		D3DXVECTOR3 Pos;
		bool Draw;//描画状態
	}ITEMMARKER;

	ITEMMARKER m_ItemMarker[ITEM_NUM];

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数

};



#endif // _ITEMMARKER_H_