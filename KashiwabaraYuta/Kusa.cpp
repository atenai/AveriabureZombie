//=============================================================================
//
// 草 [Kusa.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Kusa.h"
#include "Renderer.h"

//==============
//コンストラクタ
//==============
Kusa::Kusa()
{
}

//==============
//デストラクタ
//==============
Kusa::~Kusa()
{
}

//==============
//コンストラクタ
//==============
Kusa1::Kusa1()
{
}

//==============
//デストラクタ
//==============
Kusa1::~Kusa1()
{
}

//==============
//コンストラクタ
//==============
Kusa2::Kusa2()
{
}

//==============
//デストラクタ
//==============
Kusa2::~Kusa2()
{
}

//==============
//コンストラクタ
//==============
Kusa3::Kusa3() 
{
}

//==============
//デストラクタ
//==============
Kusa3::~Kusa3() 
{
}

//==============
//コンストラクタ
//==============
Tree::Tree()
{
}

//==============
//デストラクタ
//==============
Tree::~Tree()
{
}

//==============
//  初期化関数
//==============
void Kusa1::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//フィールド外に出ないようにする
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{

		//頂点の初期値を設定
		//左上
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//右上
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//右下
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//右下
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//左下
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//左上
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//頂点バッファーを作成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "頂点バッファーの作成に失敗しました", "", MB_OK);
		}
		//頂点バッファーに頂点を設定（コピー）する

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "頂点バッファーのロックに失敗しました", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed001.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
		}

	}

}

void Kusa2::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//フィールド外に出ないようにする
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{

		//頂点の初期値を設定
		//左上
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//右上
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//右下
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//右下
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//左下
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//左上
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//頂点バッファーを作成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "頂点バッファーの作成に失敗しました", "", MB_OK);
		}
		//頂点バッファーに頂点を設定（コピー）する

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "頂点バッファーのロックに失敗しました", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed002.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
		}

	}

}

void Kusa3::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//フィールド外に出ないようにする
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{

		//頂点の初期値を設定
		//左上
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//右上
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//右下
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//右下
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//左下
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//左上
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//頂点バッファーを作成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "頂点バッファーの作成に失敗しました", "", MB_OK);
		}
		//頂点バッファーに頂点を設定（コピー）する

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "頂点バッファーのロックに失敗しました", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed003.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
		}

	}

}

//==============
//  初期化関数
//==============
void Tree::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = 0;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//プレイヤーの初期座標に被らないようにする
		if (m_Kusa[Loop].pos.x == 0 && m_Kusa[Loop].pos.z == 0)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家1用(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//家2用(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = 3 + rand() % 7;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{

		//頂点の初期値を設定
		//左上
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//右上
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//右下
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//右下
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//左下
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//左上
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);





	//頂点バッファーを作成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "頂点バッファーの作成に失敗しました", "", MB_OK);
		}
		//頂点バッファーに頂点を設定（コピー）する

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "頂点バッファーのロックに失敗しました", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/tree_b.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
		}



	}
}



//==============
//  終了関数
//==============
void Kusa::Uninit(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		SAFE_RELEASE(m_Kusa[Loop].pVB);

	}
	SAFE_RELEASE(m_pTexture);//テクスチャの解放

}

//==============
// 　更新関数
//==============
void Kusa::Update(void)
{
	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{

		//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
		D3DXMatrixIdentity(&m_Kusa[Loop].mtxworld);//数字を入れるための初期化

		D3DXMatrixTranslation(&m_Kusa[Loop].mtxworldT, m_Kusa[Loop].pos.x, m_Kusa[Loop].pos.y, m_Kusa[Loop].pos.z);//Xモデルの平行移動関数
		D3DXMatrixMultiply(&m_Kusa[Loop].mtxworld, &m_Kusa[Loop].mtxworld, &m_Kusa[Loop].mtxworldT);//合成


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
		D3DXMatrixMultiply(&m_Kusa[Loop].mtxworld, &matCurrentView, &m_Kusa[Loop].mtxworld);
		///////////////////////ビルボード処理///////////////////////////////////////////
	}
}

//==============
// 　描画関数
//==============
void Kusa::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//構造体の数だけ回す 
	{
		//アルファブレンディング
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//アルファブレンド開始
		pDevice->SetRenderState(D3DRS_ALPHAREF, 96);//テクスチャの背景を透明に
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//テクスチャの背景を透明に
		//アルファブレンディング

		pDevice->SetTransform(D3DTS_WORLD, &m_Kusa[Loop].mtxworld);

		pDevice->SetStreamSource(0, m_Kusa[Loop].pVB, 0, sizeof(CUSTOMVERTEX));
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

