#pragma once
//=============================================================================
//  
// レンダラー(DirectX)の描画
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
//*****************************************************************************
// 基底クラス
//*****************************************************************************
//レンダラー(DirectX)クラス
//staticをつけないとエラーが出る
class Renderer
{
public:
	Renderer();//コンストラクタ
	~Renderer();//デストラクタ

	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);//初期化処理
	static void Uninit(void);//終了処理

	static void DrawBegin();//レンダラー(DirectX)の描画処理開始
	static void DrawEnd();//レンダラー(DirectX)の描画処理終了

	static LPDIRECT3DDEVICE9 GetDevice();//Direct3Dデヴァイスを送る関数
private:
	static LPDIRECT3D9			pD3d;//Direct3Dインターフェイス
	static LPDIRECT3DDEVICE9	pDevice;	//Direct3Dデヴァイス

};
#endif // _RENDERER_H_
