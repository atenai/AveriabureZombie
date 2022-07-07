#pragma once
//=============================================================================
//  
// 回復アイテムの描画
//
//=============================================================================

#ifndef _RECOVERYITEM_H_
#define _RECOVERYITEM_H_

#define RECOVERYITEM_NUM (3)//回復アイテムの数
#define HP_NUM 64//HP変動数

class RecoveryItem
{
public:
	RecoveryItem();
	~RecoveryItem();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Draw(void);//画像を表示
	void Uninit(void);//終了処理
	void ResetParameters(void);//パラメータのリセット

	int GetLoop(int Loop)
	{
		return Loop;
	}
	//アイテムの位置座標数値Xを送る
	float GetPosX(int Loop)
	{
		return m_RecoveryItem[Loop].pos.x;
	}
	//アイテムの位置座標数値Yを送る
	float GetPosY(int Loop)
	{
		return m_RecoveryItem[Loop].pos.y;
	}
	//アイテムの位置座標数値Zを送る
	float GetPosZ(int Loop)
	{
		return m_RecoveryItem[Loop].pos.z;
	}

	//アイテムの描画状態を持ってくる
	void SetRecoveryItemDraw(int kazu, bool draw)
	{
		m_RecoveryItem[kazu].Draw = draw;
	}
private:
	//*****************************************************************************
	// 構造体
	//*****************************************************************************
	//設計図を作る
	typedef struct
	{
		D3DXVECTOR3 pos;//座標
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//拡縮用変数
		D3DXMATRIX mtxworldR;//拡縮用変数
		D3DXMATRIX mtxworldT;//移動用関数
		bool Draw;//ボンベの表示・非表示

	}ITEM_DATA;

	ITEM_DATA m_RecoveryItem[RECOVERYITEM_NUM];//構造体でアイテムをいくつ作るかを宣言


	//*****************************************************************************
	// メンバ変数
	//*****************************************************************************
	//Xモデル表示用変数
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	float Ykaitenidou = 0.0f;
};

#endif // _RECOVERYITEM_H_