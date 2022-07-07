#pragma once
//=============================================================================
//  
// 回復アイテムマーカー
//
//=============================================================================
#ifndef _RECOVERYITEMMARKER_H_
#define _RECOVERYITEMMARKER_H_
#include "RecoveryItem.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//メモリ開放した際クラッシュしないようにチェックする処理
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBufferなど用の頂点の性質設定

class RecoveryItemMarker
{
public:
	RecoveryItemMarker();
	~RecoveryItemMarker();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット
	//アイテムマーカー座標持ってくる
	void SetPos(int num, float x, float y, float z)
	{
		m_RecoveryItemMarker[num].Pos.x = x;
		m_RecoveryItemMarker[num].Pos.y = y;
		m_RecoveryItemMarker[num].Pos.z = z;
	}
	//アイテムマーカーの描画状態を持ってくる
	void SetRecoveryItemMarkerDraw(int num, bool draw)
	{
		m_RecoveryItemMarker[num].Draw = draw;
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

	ITEMMARKER m_RecoveryItemMarker[RECOVERYITEM_NUM];

	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャを入れる変数
};

#endif // _RECOVERYITEMMARKER_H_