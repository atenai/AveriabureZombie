#pragma once
//=============================================================================
//  
// UAVの描画
//
//=============================================================================

#ifndef _UAV_H_
#define _UAV_H_
class UAV
{
public:
	UAV();
	~UAV();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
private:
//*****************************************************************************
// メンバ変数
//*****************************************************************************

	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	//xモデル
	D3DXMATRIX m_mtxWorld;

	//スケール
	D3DXMATRIX m_mtxWorldS;//拡大用変数

	//トランスレーション
	D3DXMATRIX m_mtxWorldT;//移動用変数
	float m_okuidou = 0.0f;//奥移動用数値//XモデルのZ座標
	float m_zmovespeed = 0.0f;//Xモデルのzスピード
};
#endif // _UAV_H_
