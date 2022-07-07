#pragma once
//=============================================================================
//  
// UIの描画
//
//　      
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

#define NUMBER_WIDTH (64)
#define NUMBER_HEIGHT (70)

#define DIG_SCORE (2)

class UI
{
public:
	UI();
	~UI();
	bool Init(void);//ポリゴンの初期化処理
	void Uninit(void);//ポリゴンの終了処理
	void Update(void);//ポリゴンの更新処理
	void Draw(//画像を表示
		int texNum,//使うテクスチャ,
		float dx, //描画位置X軸
		float dy, //描画位置Y軸
		int dw, //テクスチャの表示する横の長さ
		int dh, //テクスチャの表示する縦の長さ
		int tcx, //元の画像の切り取り開始場所（横）（画像の左から数える）
		int tcy, //元の画像の切り取り開始場所（縦）（画像の上から数える）
		int tcw, //元の画像の切り取りたい幅
		int tch //元の画像の切り取りたい高さ
	);//ポリゴンの描画処理

	//ポリゴンカラーの設定
	void SetPolygonColor(D3DCOLOR color)
	{
		m_color = color;
	}

	void DrawNumber(int n, float x, float y);	//intは0から9の数字のみ入力する
	
	//void DrawScore(int 表したいスコアー(数字), int スコアーの右枠, float 表示したいX座標, float 表示したいY座標, bool スコアーの右枠を0で埋めるかどうか)
	void DrawScore(int nScore, int nDig, float x, float y, bool bZero = false);	//nDigは桁数

private:
//===============
//構造体定義
//===============
	typedef struct
	{
		D3DXVECTOR4 pos;//座標
		D3DCOLOR color;//カラー
		D3DXVECTOR2 texcoord;//テクスチャ
	}VERTEX_2D;

	typedef struct
	{
		char fileName[256];
		float width;
		float height;
	}TEXTURE;

	//テクスチャ列挙型
	typedef enum
	{
		TEX_1 = 0,
		TEX_2,
		TEX_3,
		TEX_4,
		TEX_5,
		TEX_6,
		TEX_7,
		TEX_8,
		TEX_9,
		TEX_10,
		TEX_11,
		TEX_12,
		TEX_13,
		TEX_MAX
	}TEXTURE_NUM;

	D3DCOLOR m_color = D3DCOLOR_RGBA(255, 255, 255, 255);//プリミティブポリゴンの色//ポリゴンカラーの設定
	LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX] = { NULL };//ここで使うテクスチャの数だけNULLを追加しないといけない(2)

	TEXTURE m_Texture[TEX_MAX] = //ここで使うテクスチャとその画像のサイズを入力する(3)
	{
		{ "data/texture/hurea2.png", 3500, 2333 },//1
		{ "data/texture/hurea4.png", 3500, 2333 },//2
		{ "data/texture/hurea5.png", 3500, 2333 },//3
		{ "data/texture/sousa4.png",1000,500 },//4
		{ "data/texture/Number.png",145,64 },//5
		{ "data/texture/Press_Enter.png", 800, 600 },//6
		{ "data/texture/rekuriteru.png", 500, 500 },//7
		{ "data/texture/Title4.png",800,600 },//8
		{ "data/texture/CLEAR.png", 1280, 720 },//9
		{ "data/texture/FAILED.png", 1280, 720 },//10
		{ "data/texture/title.png", 1280, 720 },//11
		{ "data/texture/hadairo.png", 128, 128 },//12
		{ "data/texture/kuro.png", 300, 300 },//13
	};
};

#endif // _UI_H_