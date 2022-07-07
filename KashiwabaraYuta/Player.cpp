//=============================================================================
//
// プレイヤー [Player.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Player.h"
#include"input.h"
#include "Camera.h"
#include "Renderer.h"
#include "PlayerKage.h"
#include "Shot.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************



//==============
//コンストラクタ
//==============
Player::Player()
{
	//親のポインタ設定(親を入れる初期化処理)
	m_Part[0].Parent = NULL;//胴体
	m_Part[1].Parent = &m_Part[0];//頭
	m_Part[2].Parent = &m_Part[0];//右腕
	m_Part[3].Parent = &m_Part[2];//右手
	m_Part[4].Parent = &m_Part[3];//右手

	m_Part[5].Parent = &m_Part[0];//左腕
	m_Part[6].Parent = &m_Part[5];//左手
	m_Part[7].Parent = &m_Part[6];//左手

	m_Part[8].Parent = &m_Part[0];//右太もも
	m_Part[9].Parent = &m_Part[8];//右足
	m_Part[10].Parent = &m_Part[9];//右足

	m_Part[11].Parent = &m_Part[0];//左太もも
	m_Part[12].Parent = &m_Part[11];//左足
	m_Part[13].Parent = &m_Part[12];//左足

	m_Part[14].Parent = &m_Part[4];//銃
}

//==============
//デストラクタ
//==============
Player::~Player()
{
}

//==============
//  初期化関数
//==============
void Player::Init(void) 
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	HRESULT hr;

	//体
	hr = D3DXLoadMeshFromX("./data/xmodel/Karada.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[0].pD3DXMtrlBuffer,
		NULL,
		&m_Part[0].dwNumMaterials,
		&m_Part[0].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "体モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//頭
	hr = D3DXLoadMeshFromX("./data/xmodel/Atama.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[1].pD3DXMtrlBuffer,
		NULL,
		&m_Part[1].dwNumMaterials,
		&m_Part[1].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頭モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右腕
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[2].pD3DXMtrlBuffer,
		NULL,
		&m_Part[2].dwNumMaterials,
		&m_Part[2].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右腕モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右腕
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[3].pD3DXMtrlBuffer,
		NULL,
		&m_Part[3].dwNumMaterials,
		&m_Part[3].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右手モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右手
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiTe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[4].pD3DXMtrlBuffer,
		NULL,
		&m_Part[4].dwNumMaterials,
		&m_Part[4].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右手モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左腕
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[5].pD3DXMtrlBuffer,
		NULL,
		&m_Part[5].dwNumMaterials,
		&m_Part[5].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左腕モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左腕
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[6].pD3DXMtrlBuffer,
		NULL,
		&m_Part[6].dwNumMaterials,
		&m_Part[6].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左手モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左手
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariTe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[7].pD3DXMtrlBuffer,
		NULL,
		&m_Part[7].dwNumMaterials,
		&m_Part[7].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左手モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右太もも
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[8].pD3DXMtrlBuffer,
		NULL,
		&m_Part[8].dwNumMaterials,
		&m_Part[8].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右太ももモデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右太もも
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[9].pD3DXMtrlBuffer,
		NULL,
		&m_Part[9].dwNumMaterials,
		&m_Part[9].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右足モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//右足
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiAsi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[10].pD3DXMtrlBuffer,
		NULL,
		&m_Part[10].dwNumMaterials,
		&m_Part[10].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右足モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左太もも
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[11].pD3DXMtrlBuffer,
		NULL,
		&m_Part[11].dwNumMaterials,
		&m_Part[11].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左太ももモデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左太もも
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[12].pD3DXMtrlBuffer,
		NULL,
		&m_Part[12].dwNumMaterials,
		&m_Part[12].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左足モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//左足
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariAsi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[13].pD3DXMtrlBuffer,
		NULL,
		&m_Part[13].dwNumMaterials,
		&m_Part[13].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "左足モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	//銃
	hr = D3DXLoadMeshFromX("./data/xmodel/Gun.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[14].pD3DXMtrlBuffer,
		NULL,
		&m_Part[14].dwNumMaterials,
		&m_Part[14].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "右手モデルの読み込みに失敗しました", "失敗メッセージ", MB_YESNO | MB_DEFBUTTON2);
	}

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		m_Part[Loop].d3dxMaterials = (D3DXMATERIAL*)m_Part[Loop].pD3DXMtrlBuffer->GetBufferPointer();

		m_Part[Loop].pMeshMaterials = new D3DMATERIAL9[m_Part[Loop].dwNumMaterials];//マテリアルのメモリ領域をマテリアルの数だけ確保しpMeshMaterialsに入れる
		m_Part[Loop].pMeshTextures = new LPDIRECT3DTEXTURE9[m_Part[Loop].dwNumMaterials];//テクスチャに必要なメモリ領域を確保しpMeshTexturesに入れる

		//上で確保したメモリ領域に中身を入れていく
		for (DWORD i = 0; i < m_Part[Loop].dwNumMaterials; i++) //マテリアルの数だけループする
		{
			m_Part[Loop].pMeshMaterials[i] = m_Part[Loop].d3dxMaterials[i].MatD3D;//マテリアルデータを入れる
			m_Part[Loop].pMeshMaterials[i].Ambient = m_Part[Loop].pMeshMaterials[i].Diffuse;//AmbientをDiffuseと同じ値にする

																  //pTextureFilenameをもとにテクスチャオブジェクトの生成
			m_Part[Loop].pMeshTextures[i] = NULL;
			if (m_Part[Loop].d3dxMaterials[i].pTextureFilename != NULL && lstrlen(m_Part[Loop].d3dxMaterials[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					m_Part[Loop].d3dxMaterials[i].pTextureFilename/*"./data/texture/Ground.bmp"*/,//テクスチャを指定
					&m_Part[Loop].pMeshTextures[i])))
				{
					MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}
		m_Part[Loop].pD3DXMtrlBuffer->Release();//メモリの開放
	}
}

//==============
//  終了関数
//==============
void Player::Uninit(void)
{
	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		if (m_Part[Loop].pMesh != NULL)
		{
			m_Part[Loop].pMesh->Release();//これで開放される
			m_Part[Loop].pMesh = NULL;//アドレスが残っているのでNULLで上書き
		}
	}
}

//==============
// 　更新関数
//==============
void Player::Update(void) 
{

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		D3DXMatrixIdentity(&m_Part[Loop].World);//行列の初期化
	}


	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		float rate = (float)m_Frame / (float)m_KeyFrame[m_Key].Frame;//合成比率//rateは0～1の間を行き来する

		//現在のキーの移動座標と回転座標
		D3DXVECTOR3 GenzaiPos = m_KeyFrame[m_Key].Key[Loop].Position;
		D3DXVECTOR3 GenziaRot = m_KeyFrame[m_Key].Key[Loop].Rotation;

		//次のキーの移動座標と回転座標
		D3DXVECTOR3 nextPos = m_KeyFrame[m_Key + 1].Key[Loop].Position;
		D3DXVECTOR3	nextRot = m_KeyFrame[m_Key + 1].Key[Loop].Rotation;

		//線形補間
		m_Part[Loop].Position = GenzaiPos * (1.0f - rate) + nextPos * rate;
		m_Part[Loop].Rotate = GenziaRot * (1.0f - rate) + nextRot * rate;

	}


	if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_Q) || GetKeyboardPress(DIK_A))//キーフレームを進める
	{
		m_Frame++;
	}
	else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_E) || GetKeyboardPress(DIK_D))//キーフレームを戻す
	{
		m_Frame--;
	}

	//キーフレームを進めてフレームが31を越えた場合
	if (m_Frame >= 31/*m_KeyFrame[m_Key].Frame*/)//もしm_Frameがm_KeyFrame[m_Key番目]のFrameより大きい場合
	{
		m_Frame = 0;//フレームを0にする
		m_Key++;//次のキーにする

	}

	//キーが最大までいったら最小キーに戻す処理
	if (m_Key >= 4)//キーが4より大きくなった場合
	{
		m_Key = 0;//キーを0にする
	}

	//キーフレームを戻してフレームが-1を下回った場合
	if (-1 >= m_Frame)
	{
		m_Frame = 30;//フレームを30にする
		m_Key--;//前のキーに戻す
	}

	//キーが最小までいったら最大キーにする処理
	if (-1 >= m_Key)//mキーが-1より小さくなった場合
	{
		m_Key = 3;//キーを3にする
	}

	//SRT行列計算
	Scaling();//S拡縮処理
	Rotation();//R回転処理
	Translation();//T移動処理
	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		//各種行列の設定
		//親のマトリクスをかける
		if (m_Part[Loop].Parent != NULL)
		{
			D3DXMatrixMultiply(&m_Part[Loop].World, &m_Part[Loop].World, &m_Part[Loop].Parent->Matrix);
		}
		m_Part[Loop].Matrix = m_Part[Loop].World;
	}
}

//拡縮処理
void Player::Scaling()
{
	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixScaling(&m_Part[i].Scale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Scale);
	}
}

//回転処理
void Player::Rotation()
{
	/////////////////回転処理//////////////////////////////////////
	if (GetKeyboardPress(DIK_J) || GetKeyboardPress(DIK_Q) || GetKeyboardPress(DIK_LEFTARROW))//もしIキーが入力されたら
	{

		Ykaitenidou = Ykaitenidou - 0.016f;

	}
	else if (GetKeyboardPress(DIK_L) || GetKeyboardPress(DIK_E) || GetKeyboardPress(DIK_RIGHTARROW))//もしPキーが入力されたら
	{

		Ykaitenidou = Ykaitenidou + 0.016f;

	}

	m_Part[0].Rotate.y = Ykaitenidou;//親であるボディの回転座標に新しい回転座標を入れる
	/////////////////回転処理//////////////////////////////////////

	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixRotationYawPitchRoll(&m_Part[i].Rotation, m_Part[i].Rotate.y, m_Part[i].Rotate.x, m_Part[i].Rotate.z);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Rotation);
	}
}

//移動処理
void Player::Translation()
{
	// まずは軸ベクトルを用意する 今回は2軸のみ（Y軸は考慮しない）
	D3DXVECTOR3 vecAxisX(1.0f, 0.0f, 0.0f);//変換前のX軸ベクトル
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);//変換前のZ軸ベクトル
	//X、Z軸ベクトルそのものをを現在の回転状態により変換する
	D3DXVec3TransformCoord(&vecAxisX, &vecAxisX, &m_Part[0].Rotation);//ローテーションさせたものを変化前のX軸ベクトルにかける
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Part[0].Rotation);//ローテーションさせたものを変化前のZ軸ベクトルにかける


	///////////////////////////////左右移動///////////////////////
	if (GetKeyboardPress(DIK_A))//もしAキーが入力されたら
	{
		PlayerPos = PlayerPos - vecAxisX * 0.1f;//横移動スピード
	}
	else if (GetKeyboardPress(DIK_D))//もしDキーが入力されたら
	{
		PlayerPos = PlayerPos + vecAxisX * 0.1f;//横移動スピード
	}


	///////////////////////////////左右移動///////////////////////
	///////////////////////////////前後移動///////////////////////

	if (GetKeyboardPress(DIK_W))//もしWキーが入力されたら
	{
		PlayerPos = PlayerPos + vecAxisZ * 0.1f;//縦移動スピード
	}
	else if (GetKeyboardPress(DIK_S))//もしSキーが入力されたら
	{
		PlayerPos = PlayerPos - vecAxisZ * 0.1f;//縦移動スピード
	}

	///////////////////////////////前後移動///////////////////////

	


	////バウンディングボックス
	////プレイヤーの境界ボックス作成
	////プレイヤーの座標からx.y.zを+-0.5fし最小頂点と最大頂点を求めてそれを境界ボックスのあたり判定に送る
	D3DXVECTOR3 newpos = PlayerPos;//上で求めた新しい座標MovePosとPlayerPosを足したものをnewposに入れる
	D3DXVECTOR3 mina(newpos.x - 0.5f, newpos.y - 0.5f, newpos.z - 0.5f);//新しい座標のx.y.zに-0.5fしたものをminaに入れる
	D3DXVECTOR3 maxa(newpos.x + 0.5f, newpos.y + 0.5f, newpos.z + 0.5f);//新しい座標のx.y.zに+0.5fしたものをmaxaに入れる
	PlayerMin = mina;
	PlayerMax = maxa;
	if (PlayerIeBoxAtari == TRUE || PlayerIe2BoxAtari == TRUE)
	{
		//あたっていると判断
		if (PlayerSita == TRUE)
		{
			PlayerPos.z = PlayerPos.z - 0.2f;//ずれる
			m_Part[0].Position = PlayerPos;//親であるボディの移動座標に新しい移動座標を入れる
			PlayerSita = FALSE;
		}
		if (PlayerUe == TRUE)
		{
			PlayerPos.z = PlayerPos.z + 0.2f;//ずれる
			m_Part[0].Position = PlayerPos;//親であるボディの移動座標に新しい移動座標を入れる
			PlayerUe = FALSE;
		}
		if (PlayerMigi == TRUE)
		{
			PlayerPos.x = PlayerPos.x + 0.2f;//ずれる
			m_Part[0].Position = PlayerPos;//親であるボディの移動座標に新しい移動座標を入れる
			PlayerMigi = FALSE;
		}
		if (PlayerHidari == TRUE)
		{
			PlayerPos.x = PlayerPos.x - 0.2f;//ずれる
			m_Part[0].Position = PlayerPos;//親であるボディの移動座標に新しい移動座標を入れる
			PlayerHidari = FALSE;
		}
	}
	if (PlayerIeBoxAtari == FALSE && PlayerIe2BoxAtari == FALSE)//もしBoxAtariHanteiから返ってきた内容が==FALSEなら中身を実行
	{
		//あたってないと判断
		m_Part[0].Position = PlayerPos;//親であるボディの移動座標に新しい移動座標を入れる
	}
	//バウンディングボックス

	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixTranslation(&m_Part[i].Transform, m_Part[i].Position.x, m_Part[i].Position.y, m_Part[i].Position.z);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Transform);
	}
}

//==============
// 　描画関数
//==============
void Player::Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		pDevice->SetTransform(D3DTS_WORLD, &m_Part[Loop].World);

		//Direct3Dにおける「メッシュ」の「レンダリング」は「マテリアル」を基準にしています。
		//Direct3Dにおける「オブジェクトデータ」の「描画」は「表面的質感情報」を基準にしています。
		for (DWORD i = 0; i < m_Part[Loop].dwNumMaterials; i++) //マテリアルの数だけループする
		{
			pDevice->SetMaterial(&m_Part[Loop].pMeshMaterials[i]);//マテリアルを設定する
			pDevice->SetTexture(0, m_Part[Loop].pMeshTextures[i]);//テクスチャを設定する
			m_Part[Loop].pMesh->DrawSubset(i);//レンダリングする
		}
	}
}

void Player::ResetParameters(void)//パラメータのリセット
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 0.0f;

	Ykaitenidou = 0.0f;

	m_Key = 2;//キーフレームの各座標の変数
	m_Frame = 0;//フレーム間を動かすための変数
}
