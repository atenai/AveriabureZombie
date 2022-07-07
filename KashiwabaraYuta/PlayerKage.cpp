//=============================================================================
//
// プレイヤー影の描画 [PlayerKage.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "PlayerKage.h"
#include "Renderer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//==============
//コンストラクタ
//==============
PlayerKage::PlayerKage()
{
}

//==============
//デストラクタ
//==============
PlayerKage::~PlayerKage()
{
}

//==============
//  初期化関数
//==============
void PlayerKage::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//テクスチャ
	HRESULT hr;
	//テクスチャを生成する関数//いじらない
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kage.bmp", &m_pTexture);
	//エラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "boyテクスチャが読み込めません", "エラー", MB_OK);
	}


}

//==============
//  終了関数
//==============
void PlayerKage::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//テクスチャの解放
}

//==============
// 　更新関数
//==============
void PlayerKage::Update(void)
{

	//頂点の初期値を設定
	//左上
	vertices[0].x = -0.5f;
	vertices[0].y = 0.0f;
	vertices[0].z = 0.5f;
	vertices[0].color = m_color;
	vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
	//右上
	vertices[1].x = 0.5f;
	vertices[1].y = 0.0f;
	vertices[1].z = 0.5f;
	vertices[1].color = m_color;
	vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
	//左下
	vertices[2].x = -0.5f;
	vertices[2].y = 0.0f;
	vertices[2].z = -0.5f;
	vertices[2].color = m_color;
	vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
	//右下
	vertices[3].x = 0.5f;
	vertices[3].y = 0.0f;
	vertices[3].z = -0.5f;
	vertices[3].color = m_color;
	vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);




	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&mtxworld);//数字を入れるための初期化

	D3DXMatrixTranslation(&mtxworldT, PlayerPos.x, -0.99f, PlayerPos.z);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxworldT);//合成

}

//==============
// 　描画関数
//==============
void PlayerKage::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return;
	}

	//アルファブレンディング
	//アルファ合成の設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//アルファブレンディング

	//テクスチャと頂点色の両方を反映させる
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pDevice->SetTransform(D3DTS_WORLD, &mtxworld);

	//　FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//上で設定したFVFを使用
	//テクスチャの貼り付け
	pDevice->SetTexture(0, m_pTexture);


	//プリミティブ
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(CUSTOMVERTEX));

	//もとに戻す
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}