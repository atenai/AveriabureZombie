//=============================================================================
//
// HPゲージ [HPgage.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "EnemyHPgage.h"
#include "Renderer.h"



EnemyHPgage::EnemyHPgage()
{
}


EnemyHPgage::~EnemyHPgage()
{
}

//==============
//  初期化関数
//==============
void EnemyHPgage::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//テクスチャ
	HRESULT hr;
	//テクスチャを生成する関数//いじらない
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/Red.png", &m_pTexture);
	//エラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "boyテクスチャが読み込めません", "エラー", MB_OK);
	}


}

//==============
//  終了関数
//==============
void EnemyHPgage::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//テクスチャの解放
}

//==============
// 　更新関数
//==============
void EnemyHPgage::Update(void)
{

	//頂点の初期値を設定
	//左上
	vertices[0].x = 0.0f - 1.0f;
	vertices[0].y = 0.1f;
	vertices[0].z = 0.0f;
	vertices[0].color = 0xff00ff00;
	vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
	//右上
	vertices[1].x = 1.0f * Scale - 1.0f;
	vertices[1].y = 0.1f;
	vertices[1].z = 0.0f;
	vertices[1].color = 0xff0000ff;
	vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
	//左下
	vertices[2].x = 0.0f - 1.0f;
	vertices[2].y = -0.1f;
	vertices[2].z = 0.0f;
	vertices[2].color = 0xffff0000;
	vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
	//右下
	vertices[3].x = 1.0f * Scale - 1.0f;
	vertices[3].y = -0.1f;
	vertices[3].z = 0.0f;
	vertices[3].color = 0xffff0000;
	vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);




	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&mtxworld);//数字を入れるための初期化

	D3DXMatrixTranslation(&mtxworldT, EnemyPos.x, EnemyPos.y + 1.0f, EnemyPos.z);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxworldT);//合成


	///////////////////////ビルボード処理///////////////////////////////////////////
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	D3DXMATRIXA16 matCurrentView;//ビュー行列をとり入れる用変数
	//現在のビュー行列を得て、、
	pDevice->GetTransform(D3DTS_VIEW, &matCurrentView);
	// それを逆行列にして、、
	D3DXMatrixTranspose(&matCurrentView, &matCurrentView);
	//逆行列にした際のトランスレーション部分には反映させない処理(これをしないとカメラにビルボードがついてくる)
	matCurrentView._14 = 0.0f;
	matCurrentView._24 = 0.0f;
	matCurrentView._34 = 0.0f;
	// ワールド行列に掛け合わせると、ビュー変換を打ち消すことになる
	D3DXMatrixMultiply(&mtxworld, &matCurrentView, &mtxworld);
	///////////////////////ビルボード処理///////////////////////////////////////////
}

//==============
// 　描画関数
//==============
void EnemyHPgage::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return;
	}



	pDevice->SetTransform(D3DTS_WORLD, &mtxworld);

	//　FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//上で設定したFVFを使用
	//テクスチャの貼り付け
	pDevice->SetTexture(0, m_pTexture);


	//プリミティブ
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(CUSTOMVERTEX));


}

