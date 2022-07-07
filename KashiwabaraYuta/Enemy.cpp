//=============================================================================
//
// エネミー [Enemy.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Enemy.h"
#include "Renderer.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

//==============
//  初期化関数
//==============
void Enemy::Init(void)
{


	EnemyDraw = true;//敵の表示・非表示
	EnemyPos.x = -50 + rand() % 100;
	EnemyPos.y = 0;
	EnemyPos.z = -50 + rand() % 100;
	//プレイヤーの初期座標に被らないようにする
	if (EnemyPos.x == 0 && EnemyPos.z == 0)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//フィールド外に出ないようにする
	if (EnemyPos.z <= -51 || 51 <= EnemyPos.z || EnemyPos.x <= -51 || 51 <= EnemyPos.x)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//家1用(0.0f,0.0f,10.0f)
	if (-6 < EnemyPos.x && EnemyPos.x < 6 && 4 < EnemyPos.z && EnemyPos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//家2用(-10.0f,0.0f,0.0f)
	if (-16 < EnemyPos.x && EnemyPos.x < -4 && -6 < EnemyPos.z && EnemyPos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() & 100;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

											//Xファイルからメッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/OneMeshTank.x", D3DXMESH_SYSTEMMEM,
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
				d3dxMaterials[i].pTextureFilename/*"./data/texture/kusa.png"*/,
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
void Enemy::Uninit(void)
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
void Enemy::Update(void)
{
	if (EnemyDraw == true)
	{

		////追尾
		//D3DXVECTOR3 vDir = PlayerPos - EnemyPos;//向きベクトルを出す(ゴール - スタート)
		//D3DXVec3Normalize(&vDir, &vDir);//出した向きベクトルを正規化する(正の数なら1・負の数なら-1・0なら0にする)
		//vDir *= 0.05f;//向きベクトルに移動量をかけてあげる
		//EnemyPos += vDir;//移動量を現在の敵ポジションにかけてあげる


		float looptime = 0.01;//1ループにかかる時間(秒)
		float fangley;

		switch (tekimode)
		{
		case TK_SEARCH://探索モード
		{
			//looptimeが動いてない
			Ykaitenidou = Ykaitenidou + searchturn * anglesp * looptime;
			if (fabs(searchpivot - Ykaitenidou) > D3DX_PI / 1.5f)//fabs関数は絶対値を返す関数[searchpivot - Ykaitenidouの差が120度( D3DX_PI / 1.5f)を越えたら中身を実行]
			{
				searchturn = searchturn * -1;
			}
			if (JikiProbe(&fangley) == TRUE)
			{
				//敵キャラに自キャラを探させる
				tekimode = TK_CHASE;//追跡モードに変更
			}
			break;
		}
		case TK_CHASE://追跡モード
		{

			if (JikiProbe(&fangley) == TRUE)
			{
				if (fangley < Ykaitenidou)
				{
					searchturn = -1;
				}
				else
				{
					searchturn = 1;
				}
				Ykaitenidou = Ykaitenidou + searchturn * anglesp * looptime;
				if (fabs(fangley - Ykaitenidou) < D3DX_PI / 12)
				{
					//前進処理
					D3DXVECTOR3 vec1(0.0f, 0.0f, 0.05f);
					D3DXVECTOR3 vec2;
					D3DXMatrixRotationY(&m_mtxWorldR, Ykaitenidou);
					D3DXVec3TransformCoord(&vec2, &vec1, &m_mtxWorldR);
					EnemyPos = EnemyPos + vec2;
				}
			}
			else
			{
				//見失った
				searchpivot = Ykaitenidou;
				searchturn = -1;
				tekimode = TK_SEARCH;
			}

			break;
		}
		}



		//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
		D3DXMatrixIdentity(&m_mtxWorld);//数字を入れるための初期化


		D3DXMatrixScaling(&m_mtxWorldS, 0.5f, 0.5f, 0.5f);//Xモデルの拡大関数
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//合成

		D3DXMatrixRotationY(&m_mtxWorldR, Ykaitenidou);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldR);//合成

		D3DXMatrixTranslation(&m_mtxWorldT, EnemyPos.x, EnemyPos.y - 0.2f, EnemyPos.z);//Xモデルの平行移動関数
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);//合成

	}

}

//==============
// 　描画関数
//==============
void Enemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	if (EnemyDraw == true)
	{

		//地面 01
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
}

void Enemy::ResetParameters(void)//パラメータのリセット
{
	EnemyDraw = true;//敵の表示・非表示
	EnemyPos.x = -50 + rand() % 100;
	EnemyPos.y = 0;
	EnemyPos.z = -50 + rand() % 100;
	//プレイヤーの初期座標に被らないようにする
	if (EnemyPos.x == 0 && EnemyPos.z == 0)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//フィールド外に出ないようにする
	if (EnemyPos.z <= -51 || 51 <= EnemyPos.z || EnemyPos.x <= -51 || 51 <= EnemyPos.x)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//家1用(0.0f,0.0f,10.0f)
	if (-6 < EnemyPos.x && EnemyPos.x < 6 && 4 < EnemyPos.z && EnemyPos.z < 16)//草のz座標が4より大きいかつ16より小さい場合もう一度z座標のやり直し
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//家2用(-10.0f,0.0f,0.0f)
	if (-16 < EnemyPos.x && EnemyPos.x < -4 && -6 < EnemyPos.z && EnemyPos.z < 6)//草のx座標が-16より大きいかつ-4より小さい場合もう一度x座標のやり直し
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() & 100;
	}

}

//敵キャラに自キャラを探させる
BOOL Enemy::JikiProbe(float *pfoundangley)
{
	//自キャラの境界ボックス作成
	D3DXVECTOR3 PlayerMin(PlayerPos.x - 0.5f, PlayerPos.y - 0.5f, PlayerPos.z - 0.5f);//プレイヤーの最小頂点を計算する
	D3DXVECTOR3 PlayerMax(PlayerPos.x + 0.5f, PlayerPos.y + 0.5f, PlayerPos.z + 0.5f);//プレイヤーの最大頂点を計算する

	D3DXVECTOR3 probevec1(0.0f, 0.0f, 1.0f);//初期ベクトル
	D3DXVECTOR3 probevec2;
	D3DXMATRIXA16 matWorld;
	//45度の視野を4.5度単位で探索
	for (int i = -5; i < 6; i = i + 1)
	{
		D3DXMatrixRotationY(&matWorld, Ykaitenidou + D3DX_PI / 40 * i);
		D3DXVec3TransformCoord(&probevec2, &probevec1, &matWorld);
		if (D3DXBoxBoundProbe(&PlayerMin, &PlayerMax, &EnemyPos, &probevec2) == TRUE)//もしエネミーの視界にプレイヤーが入ったなら下の内容を実行
		{
			//地形との当たり判定
			D3DXVECTOR3 temp1 = PlayerPos - EnemyPos;//自キャラとの距離を調べる
			float l1 = D3DXVec3Length(&temp1);//プレイヤーとエネミーの距離をl1に入れる

			if (D3DXBoxBoundProbe(&IeMin, &IeMax, &EnemyPos, &probevec2) == TRUE)//もしエネミーの視界に家が入ったなら下の内容を実行
			{

				temp1 = IePos - EnemyPos;//家との距離を調べる
				float l2 = D3DXVec3Length(&temp1);//家とエネミーの距離をl2に入れる

				if (l2 < l1)//家 - エネミーの距離 < プレイヤー - エネミーの距離
				{
					//自キャラとの間にある 
					break;//ループを出てこの関数を終了する
				}

			}

			if (D3DXBoxBoundProbe(&Ie2Min, &Ie2Max, &EnemyPos, &probevec2) == TRUE)//もしエネミーの視界に家2が入ったなら下の内容を実行
			{

				temp1 = Ie2Pos - EnemyPos;//家との距離を調べる
				float l3 = D3DXVec3Length(&temp1);//家とエネミーの距離をl2に入れる

				if (l3 < l1)//家 - エネミーの距離 < プレイヤー - エネミーの距離
				{
					//自キャラとの間にある 
					break;//ループを出てこの関数を終了する
				}

			}

			//発見
			*pfoundangley = Ykaitenidou + D3DX_PI / 40 * i;
			return TRUE;
		}
	}
	return FALSE;
}


