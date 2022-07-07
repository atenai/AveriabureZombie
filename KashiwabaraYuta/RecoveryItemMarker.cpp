//=============================================================================
//
// アイテムマーカー [ItemMarker.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "RecoveryItemMarker.h"
#include "Renderer.h"


RecoveryItemMarker::RecoveryItemMarker()
{
}


RecoveryItemMarker::~RecoveryItemMarker()
{
}

//==============
//  初期化関数
//==============
void RecoveryItemMarker::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		m_RecoveryItemMarker[Loop].Draw = true;
	}


	//テクスチャ
	HRESULT hr;
	//テクスチャを生成する関数//いじらない
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kiro.png", &m_pTexture);
	//エラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "kiroテクスチャが読み込めません", "エラー", MB_OK);
	}


}

//==============
//  終了関数
//==============
void RecoveryItemMarker::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//テクスチャの解放
}

//==============
// 　更新関数
//==============
void RecoveryItemMarker::Update(void)
{
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_RecoveryItemMarker[Loop].Draw == true)
		{
			//頂点の初期値を設定
			//左上
			m_RecoveryItemMarker[Loop].vertices[0].x = -0.2f;
			m_RecoveryItemMarker[Loop].vertices[0].y = 0.2f;
			m_RecoveryItemMarker[Loop].vertices[0].z = 0.0f;
			m_RecoveryItemMarker[Loop].vertices[0].color = 0xff00ff00;
			m_RecoveryItemMarker[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
			//右上
			m_RecoveryItemMarker[Loop].vertices[1].x = 0.2f;
			m_RecoveryItemMarker[Loop].vertices[1].y = 0.2f;
			m_RecoveryItemMarker[Loop].vertices[1].z = 0.0f;
			m_RecoveryItemMarker[Loop].vertices[1].color = 0xff0000ff;
			m_RecoveryItemMarker[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
			//左下
			m_RecoveryItemMarker[Loop].vertices[2].x = 0.0f;
			m_RecoveryItemMarker[Loop].vertices[2].y = -0.2f;
			m_RecoveryItemMarker[Loop].vertices[2].z = 0.0f;
			m_RecoveryItemMarker[Loop].vertices[2].color = 0xffff0000;
			m_RecoveryItemMarker[Loop].vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);




			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_RecoveryItemMarker[Loop].mtxworld);//数字を入れるための初期化

			D3DXMatrixTranslation(&m_RecoveryItemMarker[Loop].mtxworldT, m_RecoveryItemMarker[Loop].Pos.x, m_RecoveryItemMarker[Loop].Pos.y + 0.5f, m_RecoveryItemMarker[Loop].Pos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_RecoveryItemMarker[Loop].mtxworld, &m_RecoveryItemMarker[Loop].mtxworld, &m_RecoveryItemMarker[Loop].mtxworldT);//合成


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
			D3DXMatrixMultiply(&m_RecoveryItemMarker[Loop].mtxworld, &matCurrentView, &m_RecoveryItemMarker[Loop].mtxworld);
			///////////////////////ビルボード処理///////////////////////////////////////////
		}
	}
}

//==============
// 　描画関数
//==============
void RecoveryItemMarker::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return;
	}

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		if (m_RecoveryItemMarker[Loop].Draw == true)
		{

			pDevice->SetTransform(D3DTS_WORLD, &m_RecoveryItemMarker[Loop].mtxworld);

			//　FVF（今から使用する頂点情報）の設定
			pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//上で設定したFVFを使用
			//テクスチャの貼り付け
			pDevice->SetTexture(0, m_pTexture);


			//プリミティブ
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, m_RecoveryItemMarker[Loop].vertices, sizeof(CUSTOMVERTEX));
		}
	}

}

void RecoveryItemMarker::ResetParameters(void)//パラメータのリセット
{
	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//構造体の数だけ回す 
	{
		m_RecoveryItemMarker[Loop].Draw = true;//ボンベがプレイヤーに当たった時の表示・非表示を管理
	}
}