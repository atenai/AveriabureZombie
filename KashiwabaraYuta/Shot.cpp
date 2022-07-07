//=============================================================================
//
// 弾 [Shot.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Shot.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************


Shot::Shot()
{
}


Shot::~Shot()
{
}

//==============
//  初期化関数
//==============
void Shot::Init(void)
{
	//サウンド
	oto0 = 0;//音楽用変数初期化
	oto1 = 0;//音楽用変数初期化

	num = 0;//弾の弾数目

	Shot_UI = SHOT_NUM;//弾数表示の初期化

	//弾全てを非表示にする
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		m_Shot[Loop].Draw = false;
		m_Shot[Loop].AtariHantei = false;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Tama.x", D3DXMESH_SYSTEMMEM,
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
void Shot::Uninit(void)
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
void Shot::Update(void)
{

	//スペースキーを押す描画
	if (GetKeyboardPress(DIK_SPACE) && num < SHOT_NUM)
	{

		//サウンド
		oto0++;
		if (oto0 > 0)
		{
			PlaySound(SOUND_LABEL_BGM002);//音楽をならすok
		}
		oto0 = 0;
		//サウンド
		//サウンド
		oto1++;
		if (oto1 > 0)
		{
			PlaySound(SOUND_LABEL_BGM010);//音楽をならすok
		}
		oto1 = 0;
		//サウンド

		//プレイヤーの正面ベクトルを持ってくる処理
		m_Shot[num].muki.x = PlayerFront.x;
		m_Shot[num].muki.y = PlayerFront.y;
		m_Shot[num].muki.z = PlayerFront.z;
		//プレイヤーの正面ベクトルを持ってくる処理

		m_Shot[num].ShotPos.x = PlayerPos.x;//num番目の弾の座標にプレイヤーの座標を入れる
		m_Shot[num].ShotPos.y = PlayerPos.y;//num番目の弾の座標にプレイヤーの座標を入れる
		m_Shot[num].ShotPos.z = PlayerPos.z;//num番目の弾の座標にプレイヤーの座標を入れる
		m_Shot[num].Draw = true;//num番目の弾を描画する
		m_Shot[num].AtariHantei = true;//num番目の弾のあたり判定をON
		num++;//numを+1する
		Shot_UI--;//TamaUIを-1する
	}

	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		//表示したら描画する
		if (m_Shot[Loop].Draw == true)
		{
			//弾のz軸ベクトルを*1.0fしたものを弾の座標にたす
			m_Shot[Loop].ShotPos = m_Shot[Loop].ShotPos + m_Shot[Loop].muki * 1.0f;


			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_Shot[Loop].mtxworld);//数字を入れるための初期化

			//xモデル 05
			D3DXMatrixScaling(&m_Shot[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//Xモデルの拡大関数
			D3DXMatrixMultiply(&m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworldS);//合成


			D3DXMatrixTranslation(&m_Shot[Loop].mtxworldT, m_Shot[Loop].ShotPos.x, m_Shot[Loop].ShotPos.y , m_Shot[Loop].ShotPos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworldT);//合成
		}
	}

}

//==============
// 　描画関数
//==============
void Shot::Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		//表示したら描画する
		if (m_Shot[Loop].Draw == true)
		{
			//
			pDevice->SetTransform(D3DTS_WORLD, &m_Shot[Loop].mtxworld);

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

void Shot::ResetParameters(void)//パラメータのリセット
{
	//サウンド
	oto0 = 0;//音楽用変数初期化
	oto1 = 0;//音楽用変数初期化

	num = 0;//弾の弾数目

	Shot_UI = SHOT_NUM;//弾数表示の初期化

	//弾全てを非表示にする
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		m_Shot[Loop].Draw = false;
		m_Shot[Loop].AtariHantei = false;
	}
}
