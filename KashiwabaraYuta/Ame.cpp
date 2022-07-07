//=============================================================================
//
// 雨 [Ame.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Ame.h"
#include "Renderer.h"


//==============
//コンストラクタ
//==============
Ame::Ame()
{
}

//==============
//デストラクタ
//==============
Ame::~Ame()
{
}


//==============
//  初期化関数
//==============
void Ame::Init(void)
{

	for (int i = 0; i < AME_NUM; i++)//構造体の数だけ回す 
	{
		m_Ame[i].used = FALSE;
		m_Ame[i].pos.x = -50 + rand() % 100;
		m_Ame[i].pos.y = 30;
		m_Ame[i].pos.z = -50 + rand() % 100;
	}

	//初期タイマー設定
	AmesetTimer(0.00000001);//ここで最初の雪を表示するまでの時間をカウントする(0.1秒から出てくる)

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	//頂点の初期値を設定
	CUSTOMVERTEX vertices[] =
	{

	{ -0.05f,1.0f,0.0f,0xff00ff00, D3DXVECTOR2(0.0f,0.0f) },
	{ 0.05f, 1.0f,0.0f,0xff0000ff,D3DXVECTOR2(1.0f,0.0f) },
	{ 0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(1.0f,1.0f) },

	{ 0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(1.0f,1.0f) },
	{ -0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(0.0f,1.0f) },
	{ -0.05f,1.0f,0.0f,0xff00ff00, D3DXVECTOR2(0.0f,0.0f) },

	};

	//頂点バッファーを作成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(vertices),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &pVB, NULL)))
	{
		MessageBox(0, "頂点バッファーの作成に失敗しました", "", MB_OK);
	}
	//頂点バッファーに頂点を設定（コピー）する
	VOID* pVertices;
	if (FAILED(pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		MessageBox(0, "頂点バッファーのロックに失敗しました", "", MB_OK);
	}
	memcpy(pVertices, vertices, sizeof(vertices));
	pVB->Unlock();

	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		/*d3dxMaterials[i].pTextureFilename*/"./data/texture/Ame2.png",
		&m_pTexture)))
	{
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
	}




}

//==============
//  終了関数
//==============
void Ame::Uninit(void)
{

	SAFE_RELEASE(pVB);
	SAFE_RELEASE(m_pTexture);//テクスチャの解放

}

//==============
// 　更新関数
//==============
void Ame::Update(void)
{
	//雨の出現
	if (AmeisTimerGoal() == TRUE)//isTimeGoalがTRUEなら下の内容を実行
	{

		//雨を出現させる
		for (int i = 0; i < AME_NUM; i = i + 1)
		{
			if (m_Ame[i].used == FALSE)
			{

				m_Ame[i].pos.x = -50 + rand() % 100;
				m_Ame[i].pos.y = 30;
				m_Ame[i].pos.z = -50 + rand() % 100;

				m_Ame[i].used = TRUE;
				break;//ここで処理終了
			}
		}

		AmesetTimer(0.00000001);//0.1秒おきに雪をTRUE//また0.1秒チャージ時間

	}

	//雨の表示・移動
	for (int i = 0; i < AME_NUM; i = i + 1)
	{
		if (m_Ame[i].used == TRUE)
		{
			m_Ame[i].pos.y = m_Ame[i].pos.y - 0.4f;//移動
			if (m_Ame[i].pos.y <= -2.0f) //画面外に出たら消滅
			{
				m_Ame[i].used = FALSE;
			}

			//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
			D3DXMatrixIdentity(&m_Ame[i].mtxworld);//数字を入れるための初期化

			D3DXMatrixTranslation(&m_Ame[i].mtxworldT, m_Ame[i].pos.x, m_Ame[i].pos.y, m_Ame[i].pos.z);//Xモデルの平行移動関数
			D3DXMatrixMultiply(&m_Ame[i].mtxworld, &m_Ame[i].mtxworld, &m_Ame[i].mtxworldT);//合成


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
			D3DXMatrixMultiply(&m_Ame[i].mtxworld, &matCurrentView, &m_Ame[i].mtxworld);
			///////////////////////ビルボード処理///////////////////////////////////////////

		}
	}

}

//==============
// 　描画関数
//==============
void Ame::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int i = 0; i < AME_NUM; i++)//構造体の数だけ回す 
	{
		//アルファブレンディング
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//アルファブレンド開始
		pDevice->SetRenderState(D3DRS_ALPHAREF, 96);//テクスチャの背景を透明に
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//テクスチャの背景を透明に
		//アルファブレンディング

		pDevice->SetTransform(D3DTS_WORLD, &m_Ame[i].mtxworld);

		pDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
		pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//上で設定したFVFを使用

		pDevice->SetTexture(0, m_pTexture);//テクスチャをセット

		//マテリアル設定
		D3DMATERIAL9 mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.Diffuse.r = 1.0f;
		mat.Diffuse.g = 1.0f;
		mat.Diffuse.b = 1.0f;
		mat.Diffuse.a = 1.0f;
		//マテリアルの色を変える
		mat.Ambient.r = 1.0f;
		mat.Ambient.g = 1.0f;
		mat.Ambient.b = 1.0f;
		mat.Ambient.a = 1.0f;
		pDevice->SetMaterial(&mat);

		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//テクスチャをセット
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);//テクスチャをセット
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);//テクスチャをセット

		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//アルファブレンド終了//2018/12/12/add
	}
}

//ここから下は雪用の関数
//目標時間をセットする
void Ame::AmesetTimer(DWORD time)
{

	Ameg_goaltimes = timeGetTime() + time;//セットした2秒に+timeGetTime(0から+1ずつなる関数)=g_goaltime//こいつがカウントの最大値
	//（例）3000 = 0 + 3000
}

//タイマーをチェックする
BOOL Ame::AmeisTimerGoal()//こいつがカウントする
{
	//ここでtimeGetTimeがまた0ミリ秒から数えるそしてg_goaltimesを越えたらTRUEになる
	//（例）3000 > 0 = false
	if (Ameg_goaltimes > timeGetTime())//g_goaltimeがtimeGetTimeより大きい場合
	{

		return FALSE;//FALSEにする

	}
	//（例）timeGetTimeが3001になったら
	return TRUE;//TRUEにする

}