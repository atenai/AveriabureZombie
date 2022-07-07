//=============================================================================
//
// 地雷 [Zirai.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Zirai.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include"sound.h"

Zirai::Zirai()
{
}


Zirai::~Zirai()
{
}

//==============
//  初期化関数
//==============
void Zirai::Init(void)
{
	//サウンド
	m_count = 0;//音楽用変数初期化

	m_num = 0;//地雷数の初期化
	m_Zirai_UI = ZIRAI_NUM;//地雷数表示の初期化

	//スペースキーが押されたら時の表示・非表示を管理
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Zirai[Loop].Draw = false;//地雷非表示
		m_Zirai[Loop].AtariHantei = false;//地雷のあたり判定をOFF
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Zirai4.x", D3DXMESH_SYSTEMMEM,
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
void Zirai::Uninit(void)
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
void Zirai::Update(void)
{


	//スペースキーを押すかつfirenumが120秒以上の時弾の描画
	if (GetKeyboardRelease(DIK_M) && m_ZiraiTime >= 10 && m_num < ZIRAI_NUM)
	{
		//サウンド
		m_count++;
		if (m_count > 0)
		{
			PlaySound(SOUND_LABEL_BGM011);//音楽をならすok
		}
		m_count = 0;
		//サウンド

		//プレイヤーの座標を地雷の座標におくる
		m_Zirai[m_num].ZiraiPos.x = PlayerPos.x;
		m_Zirai[m_num].ZiraiPos.y = PlayerPos.y;
		m_Zirai[m_num].ZiraiPos.z = PlayerPos.z;

		m_Zirai[m_num].Draw = true;//地雷を描画
		m_Zirai[m_num].AtariHantei = true;//地雷のあたり判定をON
		m_ZiraiTime = 0;//ZiraiTimeを0に初期化
		m_num++;//kazuを+1する
		m_Zirai_UI--;//HixyouziZiraiを-1する
	}


	m_ZiraiTime++;//ZiraiTimeを+1する


	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_Zirai[Loop].Draw == true)//地雷の表示・非表示を管理する
		{

			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_Zirai[Loop].mtxworld);//数字を入れるための初期化

													 //xモデル 05
			D3DXMatrixScaling(&m_Zirai[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
			D3DXMatrixMultiply(&m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworldS);//合成

			D3DXMatrixTranslation(&m_Zirai[Loop].mtxworldT, m_Zirai[Loop].ZiraiPos.x, m_Zirai[Loop].ZiraiPos.y, m_Zirai[Loop].ZiraiPos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworldT);//合成
		}
	}


}

//==============
// 　描画関数
//==============
void Zirai::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_Zirai[Loop].Draw == true)//地雷の表示・非表示を管理する
		{
			//
			pDevice->SetTransform(D3DTS_WORLD, &m_Zirai[Loop].mtxworld);

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

void Zirai::ResetParameters(void)//パラメータのリセット
{
	//サウンド
	m_count = 0;//音楽用変数初期化

	m_num = 0;//地雷数の初期化
	m_Zirai_UI = ZIRAI_NUM;//地雷数表示の初期化

	//スペースキーが押されたら時の表示・非表示を管理
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Zirai[Loop].Draw = false;//地雷非表示
		m_Zirai[Loop].AtariHantei = false;//地雷のあたり判定をOFF
	}

}