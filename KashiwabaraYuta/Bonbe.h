#pragma once
//=============================================================================
//  
// ボンベの描画
//
//=============================================================================

#ifndef _BONBE_H_
#define _BONBE_H_
//*****************************************************************************
// 基底クラス
//*****************************************************************************
//ボンベクラス
class Bonbe
{
public:
	Bonbe();//コンストラクタ
	~Bonbe();//デストラクタ
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理

	//void SetPos(float setpos)//座標を入れる
	//{
	//	pos = setpos;
	//}

	//float GetPos()//座標を取ってくる
	//{
	//	return pos;
	//}

	D3DXVECTOR3 SetBonbePos(float x, float y, float z)//座標を入れる
	{
		BonbePos.x = x;
		BonbePos.y = y;
		BonbePos.z = z;

		return BonbePos;
	}
private:
	
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//ワールド行列
	D3DXMATRIX mtxWorld;
	//スケール
	D3DXMATRIX mtxWorldS;//拡大用変数
	//トランスレーション
	D3DXMATRIX mtxWorldT;//移動用変数

//*****************************************************************************
// メンバ変数
//*****************************************************************************
	//float pos = 0.0f;//座標
	D3DXVECTOR3 BonbePos;
};
#endif // _BONBE_H_
