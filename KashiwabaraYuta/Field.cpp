//=============================================================================
//
// フィールド [Field.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Field.h"
#include "Renderer.h"


//==============
//コンストラクタ
//==============
Field::Field()
{
}

//==============
//デストラクタ
//==============
Field::~Field()
{
}

//==============
//コンストラクタ
//==============
Zimen::Zimen()
{
	pos.x = 0.0f;
	pos.y = -1.0f;
	pos.z = 0.0f;
}

//==============
//デストラクタ
//==============
Zimen::~Zimen()
{
}

//==============
//コンストラクタ
//==============
SkyDome::SkyDome()
{
	pos.x = 0.0f;
	pos.y = -0.5f;
	pos.z = 0.0f;
}

//==============
//デストラクタ
//==============
SkyDome::~SkyDome()
{
}

//==============
//  初期化関数
//==============
void Zimen::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Ground.x", D3DXMESH_SYSTEMMEM,
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
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/Zimen3.bmp",
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//メモリの開放

}

//==============
//  初期化関数
//==============
void SkyDome::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Sky.x", D3DXMESH_SYSTEMMEM,
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
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/GraySky.bmp",
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
void Field::Uninit(void)
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
void Field::Update(void)
{

	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&mtxWorld);//数字を入れるための初期化

	//地面 01
	D3DXMatrixScaling(&mtxWorldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorldS);//合成

	D3DXMatrixTranslation(&mtxWorldT, pos.x, pos.y, pos.z);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorldT);//合成
}

//==============
// 　描画関数
//==============
void Field::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//ワールド行列
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//Direct3Dにおける「メッシュ」の「レンダリング」は「マテリアル」を基準にしています。
	//Direct3Dにおける「オブジェクトデータ」の「描画」は「表面的質感情報」を基準にしています。
	for (DWORD i = 0; i < dwNumMaterials; i++) //マテリアルの数だけループする
	{
		pDevice->SetMaterial(&pMeshMaterials[i]);//マテリアルを設定する
		pDevice->SetTexture(0, pMeshTextures[i]);//テクスチャを設定する
		pMesh->DrawSubset(i);//レンダリングする
	}

}