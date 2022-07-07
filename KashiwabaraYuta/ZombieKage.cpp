//=============================================================================
//
// ゾンビの影 [HPgage.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "ZombieKage.h"
#include "Renderer.h"


ZombieKage::ZombieKage()
{
}


ZombieKage::~ZombieKage()
{
}

//==============
//  初期化関数
//==============
void ZombieKage::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		m_ZombieKage[Loop].Draw = true;//ボンベがプレイヤーに当たった時の表示・非表示を管理
	}

	//テクスチャ
	HRESULT hr;
	//テクスチャを生成する関数//いじらない
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kage.bmp", &m_pTexture);
	//エラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "kageテクスチャが読み込めません", "エラー", MB_OK);
	}


}

//==============
//  終了関数
//==============
void ZombieKage::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//テクスチャの解放
}

//==============
// 　更新関数
//==============
void ZombieKage::Update(void)
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_ZombieKage[Loop].Draw == true)//表示・非表示を管理する
		{
			//頂点の初期値を設定
			//左上
			m_ZombieKage[Loop].vertices[0].x = -0.5f;
			m_ZombieKage[Loop].vertices[0].y = 0.0f;
			m_ZombieKage[Loop].vertices[0].z = 0.5f;
			m_ZombieKage[Loop].vertices[0].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
			//右上
			m_ZombieKage[Loop].vertices[1].x = 0.5f;
			m_ZombieKage[Loop].vertices[1].y = 0.0f;
			m_ZombieKage[Loop].vertices[1].z = 0.5f;
			m_ZombieKage[Loop].vertices[1].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
			//左下
			m_ZombieKage[Loop].vertices[2].x = -0.5f;
			m_ZombieKage[Loop].vertices[2].y = 0.0f;
			m_ZombieKage[Loop].vertices[2].z = -0.5f;
			m_ZombieKage[Loop].vertices[2].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
			//右下
			m_ZombieKage[Loop].vertices[3].x = 0.5f;
			m_ZombieKage[Loop].vertices[3].y = 0.0f;
			m_ZombieKage[Loop].vertices[3].z = -0.5f;
			m_ZombieKage[Loop].vertices[3].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);




			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_ZombieKage[Loop].mtxworld);//数字を入れるための初期化

			D3DXMatrixTranslation(&m_ZombieKage[Loop].mtxworldT, m_ZombieKage[Loop].ZombiePos.x, -0.99f, m_ZombieKage[Loop].ZombiePos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_ZombieKage[Loop].mtxworld, &m_ZombieKage[Loop].mtxworld, &m_ZombieKage[Loop].mtxworldT);//合成
		}
	}

}

//==============
// 　描画関数
//==============
void ZombieKage::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return;
	}

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_ZombieKage[Loop].Draw == true)//表示・非表示を管理する
		{

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

			pDevice->SetTransform(D3DTS_WORLD, &m_ZombieKage[Loop].mtxworld);

			//　FVF（今から使用する頂点情報）の設定
			pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//上で設定したFVFを使用
			//テクスチャの貼り付け
			pDevice->SetTexture(0, m_pTexture);


			//プリミティブ
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_ZombieKage[Loop].vertices, sizeof(CUSTOMVERTEX));

			//もとに戻す
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

}


void ZombieKage::ResetParameters(void)//パラメータのリセット
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//構造体の数だけ回す 
	{
		m_ZombieKage[Loop].Draw = true;//ボンベがプレイヤーに当たった時の表示・非表示を管理
	}
}
