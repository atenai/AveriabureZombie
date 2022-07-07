//=============================================================================
//
// UAV [UAV.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "UAV.h"
#include "Renderer.h"



UAV::UAV()
{
}


UAV::~UAV()
{
}

//==============
//  初期化関数
//==============
void UAV::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/UAV8.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", NULL, MB_OK);
		return;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];//マテリアルのメモリ領域をマテリアルの数だけ確保しpMeshMaterialsに入れる
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];//テクスチャに必要なメモリ領域を確保しpMeshTexturesに入れる

														   //上で確保したメモリ領域に中身を入れていく
	for (DWORD i = 0; i < dwNumMaterials; i++) //マテリアルの数だけループする
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;//マテリアルデータを入れる
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;//AmbientをDiffuseと同じ値にする

		//pTextureFilenameをもとにテクスチャオブジェクトの生成
		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//メモリの開放

}

//==============
//  終了関数
//==============
void UAV::Uninit(void)
{

	if (pMesh != NULL)
	{
		pMesh->Release();//これで開放される
		pMesh = NULL;//アドレスが残っているのでNULLで上書き
	}

}

//==============
// 　更新関数
//==============
void UAV::Update(void)
{

	////////////////////////////奥自動移動///////////////////////////////////
	//ここをいじる場合はカメラもいじらないといけない！
	m_zmovespeed += 0.5f;//Xモデルの奥に進むスピード

	if (m_okuidou >= 330) {//奥移動の範囲制限
		m_zmovespeed = 0;
	}

	m_okuidou = m_okuidou + m_zmovespeed;//奥移動計算
	m_zmovespeed = 0;//奥移動のスピードを初期化
	////////////////////////////奥自動移動///////////////////////////////////



	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&m_mtxWorld);//数字を入れるための初期化

	//xモデル 05
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//合成

	D3DXMatrixTranslation(&m_mtxWorld, 0.0f, 7.0f, m_okuidou);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorld);//合成


}

//==============
// 　描画関数
//==============
void UAV::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//xモデル 05
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//Direct3Dにおける「メッシュ」の「レンダリング」は「マテリアル」を基準にしています。
	//Direct3Dにおける「オブジェクトデータ」の「描画」は「表面的質感情報」を基準にしています。
	for (DWORD i = 0; i < dwNumMaterials; i++) //マテリアルの数だけループする
	{
		pDevice->SetMaterial(&pMeshMaterials[i]);//マテリアルを設定する
		pDevice->SetTexture(0, pMeshTextures[i]);//テクスチャを設定する
		pMesh->DrawSubset(i);//レンダリングする
	}

}
