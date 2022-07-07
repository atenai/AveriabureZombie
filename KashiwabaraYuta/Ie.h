#pragma once
//=============================================================================
//  
// 家の描画
//
//=============================================================================

#ifndef _IE_H_
#define _IE_H_
class Ie
{
public:
	Ie();
	~Ie();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void Uninit(void);//終了処理
	//家の座標を持ってくる
	void SetPos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	//家の座標を送る
	D3DXVECTOR3 GetPos()
	{
		return IePos;
	}
	//家の最小頂点を送る
	D3DXVECTOR3 GetIeMin() 
	{
		return Min;
	}
	//家の最大頂点を送る
	D3DXVECTOR3 GetIeMax()
	{
		return Max;
	}

private:
//*****************************************************************************
// メンバ変数
//*****************************************************************************

	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//ワールド行列
	D3DXMATRIX m_mtxWorld;

	//スケール
	D3DXMATRIX m_mtxWorldS;//拡大用変数

	//トランスレーション
	D3DXMATRIX m_mtxWorldT;//移動用変数
	D3DXVECTOR3 IePos;//家の座標

	//バウンディングボックス(ABB)
	D3DXVECTOR3 Min;//最小頂点
	D3DXVECTOR3 Max;//最大頂点
};
#endif // _IE_H_
