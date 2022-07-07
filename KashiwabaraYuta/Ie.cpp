//=============================================================================
//
// 家 [Ie.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Ie.h"
#include "Renderer.h"



Ie::Ie()
{
}


Ie::~Ie()
{
}

//==============
//  初期化関数
//==============
void Ie::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/house.x", D3DXMESH_SYSTEMMEM,
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
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/house.bmp",
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//メモリの開放

	//バウンディングボックス(ABB)
	//家の境界ボックスの作成
	//.xモデルのメッシュ情報をもとに自動的にバウンディングボックスを作成してくれる
	DWORD numv, stride;
	LPDIRECT3DVERTEXBUFFER9 pvb;
	BYTE *pvertices;
	HRESULT hr;
	D3DXVECTOR3 lminv(0.0f,0.0f,0.0f), lmaxv(0.0f, 0.0f, 0.0f);

	numv = pMesh->GetNumVertices();//頂点数を求める
	stride = D3DXGetFVFVertexSize(pMesh->GetFVF());
	hr = pMesh->GetVertexBuffer(&pvb);//頂点バッファ取得

	hr = pvb->Lock(0, 0, (VOID**)&pvertices, 0);//頂点バッファロック

	hr = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv, stride, &lminv, &lmaxv);

	Min = IePos + lminv;//描画対象の座標+lminvしたものをビルディングボックスのminvに入れる
	Max = IePos + lmaxv;//描画対象の座標+lmaxvしたものをビルディングボックスのmaxvに入れる
	pvb->Unlock();//頂点バッファアンロック
	//バウンディングボックス(ABB)


	//IeEnemyPos(IePos);//家の座標を送る
	//IeEnemyMin(minv);//家のマイナスのx・y・zの3頂点座標をエネミーに送る
	//IeEnemyMax(maxv);//家のプラスのx・y・zの3頂点座標をエネミーに送る

	//IeZombiePos(IePos);//家の座標を送る
	//IeZombieMin(minv);//家のマイナスのx・y・zの3頂点座標をエネミーに送る
	//IeZombieMax(maxv);//家のプラスのx・y・zの3頂点座標をエネミーに送る

}

//==============
//  終了関数
//==============
void Ie::Uninit(void)
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
void Ie::Update(void)
{

	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&m_mtxWorld);//数字を入れるための初期化

	//地面 01
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//合成

	D3DXMatrixTranslation(&m_mtxWorldT, IePos.x, IePos.y, IePos.z);//Xモデルの平行移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);//合成
}

//==============
// 　描画関数
//==============
void Ie::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

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
