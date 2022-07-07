//=============================================================================
//
// カメラ [Camera.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include"Camera.h"
#include"Main.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//==============
//コンストラクタ
//==============
Camera::Camera()
{
}

//==============
//デストラクタ
//==============
Camera::~Camera()
{
}

//==============
//  初期化関数
//==============
void Camera::Init(void)
{
	m_up_pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//==============
//  終了関数
//==============
void Camera::Uninit(void)
{

}

//==============
// 　更新関数
//==============
void Camera::Update(void)
{
	//カメラ
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//SRT(スケール→ローテーション→トランスレーション)の順番で合成しないといけない
	D3DXMatrixIdentity(&m_mtxWorld);//数字を入れるための初期化

	if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT))
	{

		//サウンド
		if (oto1 == 0)
		{
			PlaySound(SOUND_LABEL_BGM006);//音楽をならすok
		}
		oto1++;//2度目の音楽を鳴らさない
		//サウンド

		TPS = true;//肩越しカメラ
	}
	else
	{
		oto1 = 0;//音楽を初期化

		TPS = false;//通常カメラ
	}

	//通常カメラ
	if (TPS == false)
	{

		//カメラを人間の後ろに配置。方向は人間の方を向くようにする
		D3DXVECTOR3 eyemove(0.0f, 3.0f, -6.0f);//カメラの移動先座標を設定(プレイヤーの少し後ろ)
		//CameraMove = プレイヤーの移動や回転などをしたまとまった行列(D3DMATRIX)が入っている
		D3DXVec3TransformCoord(&eyemove, &eyemove, &PlayerMatrix);//プレイヤーの行列を正面として、eyemove(カメラの移動先座標)をかける(回転座標と平行移動座標を掛け合わせる)
		//v = v + PlayerPos;//プレイヤーの移動座標がすでに入っているのでこれはいらない
		m_eye_pos = eyemove;//プレイヤーからカメラの移動先座標をかけた座標をカメラ座標に入れる
		D3DXVECTOR3 atmove(0.0f, 0.0f, 0.0f);//視点の移動先座標を設定
		D3DXVec3TransformCoord(&atmove, &atmove, &PlayerMatrix);//プレイヤーの行列を正面として、atmove(視点の移動先座標)をかける(回転座標と平行移動座標を掛け合わせる)
		//g_at_pos = PlayerPos;//カメラの視点座標(at)をプレイヤーの座標と同じにする
		m_at_pos = atmove;//カメラの視点座標(at)をプレイヤーの座標と同じにする
	}
	//肩越しカメラ
	if (TPS == true)
	{
		//カメラを人間の後ろに配置。方向は人間の方を向くようにする
		D3DXVECTOR3 eyemove(0.5, 0.25, -1);//カメラの移動先座標を設定(プレイヤーの少し後ろ)
		//CameraMove = プレイヤーの移動や回転などをしたまとまった行列(D3DMATRIX)が入っている
		D3DXVec3TransformCoord(&eyemove, &eyemove, &PlayerMatrix);//プレイヤーの行列を正面として、eyemove(カメラの移動先座標)をかける(回転座標と平行移動座標を掛け合わせる)
		//v = v + PlayerPos;//プレイヤーの移動座標がすでに入っているのでこれはいらない
		m_eye_pos = eyemove;//プレイヤーからカメラの移動先座標をかけた座標をカメラ座標に入れる
		D3DXVECTOR3 atmove(0.5, 0.25, 0);//視点の移動先座標を設定
		D3DXVec3TransformCoord(&atmove, &atmove, &PlayerMatrix);//プレイヤーの行列を正面として、atmove(視点の移動先座標)をかける(回転座標と平行移動座標を掛け合わせる)
		//g_at_pos = PlayerPos;//カメラの視点座標(at)をプレイヤーの座標と同じにする
		m_at_pos = atmove;//カメラの視点座標(at)をプレイヤーの座標と同じにする
	}


	//カメラ
	// ビュートランスフォーム（視点座標変換）
	D3DXMatrixLookAtLH(&m_mtxView, &m_eye_pos, &m_at_pos, &m_up_pos);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxView);//合成

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxWorld);
	
	//レンズ
	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&m_mtxProj, D3DX_PI / 3, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}