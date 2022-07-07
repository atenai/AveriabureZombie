//=============================================================================
//
// アイテム [Item.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Item.h"
#include "Renderer.h"
#include "ItemMarker.h"



Item::Item()
{
}


Item::~Item()
{
}

//==============
//  初期化関数
//==============
void Item::Init(void)
{
	//構造体で作ったボンベの位置座標を指定

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Item[Loop].pos.x = -50 + rand() % 100;
		m_Item[Loop].pos.y = 0;
		m_Item[Loop].pos.z = -50 + rand() % 100;
		//プレイヤーの初期座標に被らないようにする
		if (m_Item[Loop].pos.x == 0 && m_Item[Loop].pos.z == 0)
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//フィールド外に出ないようにする
		if (m_Item[Loop].pos.z <= -51 || 51 <= m_Item[Loop].pos.z || m_Item[Loop].pos.x <= -51 || 51 <= m_Item[Loop].pos.x)
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (4 < m_Item[Loop].pos.z  && m_Item[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Item[Loop].pos.x && m_Item[Loop].pos.x < -4)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
		}

		m_Item[Loop].Draw = true;//ボンベがプレイヤーに当たった時の表示・非表示を管理
	}


	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/DanyakuBako2.x", D3DXMESH_SYSTEMMEM,
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
				d3dxMaterials[i].pTextureFilename/*"./data/texture/Ground.bmp"*/,//テクスチャを指定
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
void Item::Uninit(void)
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
void Item::Update(void)
{

	Ykaitenidou = Ykaitenidou + 0.05f;

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_Item[Loop].Draw == true)//ボンベの表示・非表示を管理する
		{

			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_Item[Loop].mtxworld);//数字を入れるための初期化

			D3DXMatrixScaling(&m_Item[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
			D3DXMatrixMultiply(&m_Item[Loop].mtxworld, &m_Item[Loop].mtxworld, &m_Item[Loop].mtxworldS);//合成

			D3DXMatrixRotationY(&m_Item[Loop].mtxworldR, Ykaitenidou);//XモデルのY回転関数
			D3DXMatrixMultiply(&m_Item[Loop].mtxworld, &m_Item[Loop].mtxworld, &m_Item[Loop].mtxworldR);//合成

			D3DXMatrixTranslation(&m_Item[Loop].mtxworldT, m_Item[Loop].pos.x, m_Item[Loop].pos.y, m_Item[Loop].pos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_Item[Loop].mtxworld, &m_Item[Loop].mtxworld, &m_Item[Loop].mtxworldT);//合成
		}
	}
}

//==============
// 　描画関数
//==============
void Item::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_Item[Loop].Draw == true)//ボンベの表示・非表示を管理する
		{
			//地面 01
			pDevice->SetTransform(D3DTS_WORLD, &m_Item[Loop].mtxworld);

			//Direct3Dにおける「メッシュ」の「レンダリング」は「マテリアル」を基準にしています。
			//Direct3Dにおける「オブジェクトデータ」の「描画」は「表面的質感情報」を基準にしています。
			for (DWORD i = 0; i < dwNumMaterials; i++) //マテリアルの数だけループする
			{
				pDevice->SetMaterial(&pMeshMaterials[i]);//マテリアルを設定する
				pDevice->SetTexture(0, pMeshTextures[i]);//テクスチャを設定する
				pMesh->DrawSubset(i);//レンダリングする
			}
		}
	}
}

void Item::ResetParameters(void)//パラメータのリセット
{

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Item[Loop].pos.x = -50 + rand() % 100;
		m_Item[Loop].pos.y = 0;
		m_Item[Loop].pos.z = -50 + rand() % 100;
		//プレイヤーの初期座標に被らないようにする
		if (m_Item[Loop].pos.x == 0 && m_Item[Loop].pos.z == 0)
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//フィールド外に出ないようにする
		if (m_Item[Loop].pos.z <= -51 || 51 <= m_Item[Loop].pos.z || m_Item[Loop].pos.x <= -51 || 51 <= m_Item[Loop].pos.x)
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (4 < m_Item[Loop].pos.z  && m_Item[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Item[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Item[Loop].pos.x && m_Item[Loop].pos.x < -4)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Item[Loop].pos.x = -50 + rand() % 100;
		}

		m_Item[Loop].Draw = true;//ボンベがプレイヤーに当たった時の表示・非表示を管理
	}


}