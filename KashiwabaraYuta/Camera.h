#pragma once
//=============================================================================
//  
// カメラ
//    
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
//*****************************************************************************
// 基底クラス
//*****************************************************************************
//カメラクラス
class Camera 
{
public:
	Camera();//コンストラクタ
	~Camera();//デストラクタ
	void Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理

	//プレイヤーのワールド行列を持ってくる
	void SetPlayerMatrix(D3DXMATRIX Mat) 
	{
		PlayerMatrix = Mat;
	}

	bool GetTPS()
	{
		return TPS;
	}

private:

	//レンズ
	D3DXMATRIX m_mtxProj;//プロジェクション行列

	//カメラ
	D3DXMATRIX m_mtxView;//ビュー行列
	D3DXMATRIX m_mtxWorld;

	D3DXVECTOR3 m_eye_pos;//カメラ座標//eye
	D3DXVECTOR3 m_at_pos;//視点座標//at
	D3DXVECTOR3 m_up_pos;//上方向座標//up

	bool TPS = false;

	D3DXMATRIX PlayerMatrix;//プレイヤーのワールド行列

	//サウンド
	//int oto0;//音楽用変数
	int oto1;//音楽用変数
};


#endif // _CAMERA_H_


