//=============================================================================
//
// 爆風 [Bakuhu.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Bakuhu.h"
#include "Renderer.h"


Bakuhu::Bakuhu()
{
}


Bakuhu::~Bakuhu()
{
}

//==============
//  初期化関数
//==============
void Bakuhu::Init(void)
{

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//地雷の数だけ回す 
	{
		m_Bakuhu[Loop].Draw = false;//爆風非表示
		m_Bakuhu[Loop].Timer = 0.0f;
	}

	

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/bakuha.x", D3DXMESH_SYSTEMMEM,
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
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/bakuha.bmp",
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
void Bakuhu::Uninit(void)
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
void Bakuhu::Update(void)
{
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//地雷の数だけ回す 
	{
		
		if (m_Bakuhu[Loop].Draw == true)
		{
			m_Bakuhu[Loop].Timer = m_Bakuhu[Loop].Timer + 23.0f;
			
			if (m_Bakuhu[Loop].Timer < 2000)//Loop番目2秒のみ
			{
				float pt = m_Bakuhu[Loop].Timer;//0秒から2秒までを入れる

				//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
				D3DXMatrixIdentity(&m_Bakuhu[Loop].mtxworld);//数字を入れるための初期化

				//地面 01
				D3DXMatrixScaling(&m_Bakuhu[Loop].mtxworldS, 1.0f + pt / 100.0f, 1.0f + pt / 100.0f, 1.0f + pt / 100.0f);//Xモデルの拡大関数
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldS);//合成

				D3DXMatrixRotationY(&m_Bakuhu[Loop].mtxworldR, (float)timeGetTime() / 1000);//Y回転関数
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldR);//合成

				D3DXMatrixTranslation(&m_Bakuhu[Loop].mtxworldT, m_Bakuhu[Loop].Pos.x, m_Bakuhu[Loop].Pos.y - 1.0f, m_Bakuhu[Loop].Pos.z);//Xモデルの平行移動関数
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldT);//合成


			}

			if (2000 < m_Bakuhu[Loop].Timer)//Loop番目2秒後
			{
				m_Bakuhu[Loop].Draw = false;
			}

		}
	}
}

//==============
// 　描画関数
//==============
void Bakuhu::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//地雷の数だけ回す 
	{
		if (m_Bakuhu[Loop].Draw == true)
		{
			if (m_Bakuhu[Loop].Timer < 2000)//Loop番目2秒のみ
			{
				//アルファブレンディング
				//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンド開始
				//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
				//pDevice->SetRenderState(D3DRS_BLENDFACTOR, 0x88888888);

				//地面 01
				pDevice->SetTransform(D3DTS_WORLD, &m_Bakuhu[Loop].mtxworld);

				//Direct3Dにおける「メッシュ」の「レンダリング」は「マテリアル」を基準にしています。
				//Direct3Dにおける「オブジェクトデータ」の「描画」は「表面的質感情報」を基準にしています。
				for (DWORD i = 0; i < dwNumMaterials; i++) //マテリアルの数だけループする
				{
					pDevice->SetMaterial(&pMeshMaterials[i]);//マテリアルを設定する
					pDevice->SetTexture(0, pMeshTextures[i]);//テクスチャを設定する
					pMesh->DrawSubset(i);//レンダリングする
				}

				//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//アルファブレンド終了
			}

			if (2000 < m_Bakuhu[Loop].Timer)//Loop番目2秒後
			{
				m_Bakuhu[Loop].Draw = false;
			}
		}
	}
}



void Bakuhu::ResetParameters(void)
{
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Bakuhu[Loop].Draw = false;//地雷の非表示
		m_Bakuhu[Loop].Timer = 0.0f;
	}
}

