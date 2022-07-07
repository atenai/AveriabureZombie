//=============================================================================
//
// レンダラー(DirectX) [Renderer.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Renderer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9			Renderer::pD3d = NULL;		//Direct3Dインターフェイス
LPDIRECT3DDEVICE9	Renderer::pDevice = NULL;	//Direct3Dデヴァイス

//==============
//コンストラクタ
//==============
Renderer::Renderer()
{
}

//==============
//デストラクタ
//==============
Renderer::~Renderer()
{
}

//==============
//  初期化関数
//==============
HRESULT Renderer::Init(HINSTANCE hInstance, HWND hWnd)
{

	// 「Direct3D」オブジェクトの作成
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	if (FAILED(pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//3
		return E_FAIL;
	}//3

	 // デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));//零に初期化する
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//裏のスクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//裏のスクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;//色数の指定
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//これしか選ばない　同期信号をどう扱うか
	d3dpp.EnableAutoDepthStencil = TRUE;//絶対true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//絶対コレにする
	d3dpp.Windowed = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//デバイスオブジェクトの作成
	//[デバイス作成制御]<描画>と<頂点処理>
	if (FAILED(pD3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&pDevice)))
	{//4
		MessageBox(NULL, "pDeviceの取得に失敗しました", "失敗", MB_OK);
		return E_FAIL;
	}//4

	//ここにセットレンダーステートの設定
	//アンビエントライト(環境光)の設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));


	return S_OK;
}

//==============
//  終了関数
//==============
void Renderer::Uninit(void)
{
	if (pDevice != NULL)
	{//デバイスの開放//2
		pDevice->Release();//これで開放される
		pDevice = NULL;//アドレスが残っているのでNULLで上書き
	}//2

	if (pD3d != NULL)
	{//Direct3Dオブジェクトの開放//3
		pD3d->Release();
		pD3d = NULL;
	}//3
}

//================
//  描画開始関数
//================
void Renderer::DrawBegin(void)
{
	////////////////////ライトとマテリアルの設定////////////////
	//マテリアル設定
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	//マテリアルの色を変える
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 1.0f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);

	//ライトの設定
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(-1.0f, 0.0f, 0.0f);//(X,Y,Z)の光の当たる方向を指定する
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	pDevice->SetLight(0, &light);//ライト番号0～3
	pDevice->LightEnable(0, TRUE);//0番ライトオン！
	////////////////////ライトとマテリアルの設定////////////////

	pDevice->Clear(
		0, NULL, //指定した先頭アドレスの矩形などのものをNULLのとろこに下記何個あるのかをNULLの
		(D3DCLEAR_TARGET | //色をClear
			D3DCLEAR_ZBUFFER),//ゼットバッファをClear
		D3DCOLOR_RGBA(169, 169, 169, 255),//背景色の変更
		1.0f, 0);//1.0fがゼットバッファのClear数値、ステンシルを何の値でClearするのか

	 //Direct3Dによる描画の開始
	pDevice->BeginScene();
}

//================
//  描画終了関数
//================
void Renderer::DrawEnd(void)
{
	pDevice->EndScene();//Direct3Dによる描画の終了
	pDevice->Present(NULL, NULL, NULL, NULL);//描画が終わってデバイスにプレゼントする

}

LPDIRECT3DDEVICE9 Renderer::GetDevice() 
{
	return pDevice; 
}