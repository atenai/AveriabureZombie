#pragma once
//=======================================================================================
//						バウンディングボックスあたり判定描画
//						2017.06.05
//=======================================================================================

#ifndef _BOXATARIHANTEI_H_
#define _BOXATARIHANTEI_H_
class BoxAtariHantei
{
public:
	BoxAtariHantei();
	~BoxAtariHantei();
	void Init(void);//初期化処理
	void Update(void);//更新処理
	void Uninit(void);//終了処理

	BOOL BoxAtari(float Box1MinPosX, float Box1MinPosY, float Box1MinPosZ, float Box1MaxPosX, float Box1MaxPosY, float Box1MaxPosZ, 
		float Box2MinPosX, float Box2MinPosY, float Box2MinPosZ, float Box2MaxPosX, float Box2MaxPosY, float Box2MaxPosZ);//境界ボックスのあたり判定

	//家の最小頂点を持ってくる
	void SetIeMin(D3DXVECTOR3 Min)
	{
		IeMinPos = Min;//家の最小頂点をIeMinPosに入れる
	}
	//家の最大頂点を持ってくる
	void SetIeMax(D3DXVECTOR3 Max)
	{
		IeMaxPos = Max;//家の最大頂点をIeMaxPosに入れる
	}
	//家2の最小頂点を持ってくる
	void SetIe2Min(D3DXVECTOR3 Min)
	{
		Ie2MinPos = Min;//家の最小頂点をIe2MinPosに入れる
	}
	//家2の最大頂点を持ってくる
	void SetIe2Max(D3DXVECTOR3 Max)
	{
		Ie2MaxPos = Max;//家の最大頂点をIe2MaxPosに入れる
	}
	//プレイヤーの最小頂点を持ってくる
	void SetPlayerMin(D3DXVECTOR3 Min)
	{
		PlayerMinPos = Min;
	}
	//プレイヤーの最大頂点を持ってくる
	void SetPlayerMax(D3DXVECTOR3 Max)
	{
		PlayerMaxPos = Max;
	}
	//プレイヤーと家のあたり判定の結果を送る
	bool GetPlayerIeBoxAtari()
	{
		return PlayerIeBoxAtari;
	}
	//プレイヤーと家2のあたり判定の結果を送る
	bool GetPlayerIe2BoxAtari()
	{
		return PlayerIe2BoxAtari;
	}

	bool GetPlayerSita()
	{
		return PlayerSita;
	}
	bool GetPlayerMigi()
	{
		return PlayerMigi;
	}
	bool GetPlayerUe()
	{
		return PlayerUe;
	}
	bool GetPlayerHidari()
	{
		return PlayerHidari;
	}
private:
//*****************************************************************************
// メンバ変数
//*****************************************************************************

//バウンディングボックス(ABB)
	//家
	D3DXVECTOR3 IeMinPos;//最小頂点
	D3DXVECTOR3 IeMaxPos;//最大頂点
	//家2
	D3DXVECTOR3 Ie2MinPos;//最小頂点
	D3DXVECTOR3 Ie2MaxPos;//最大頂点
	//プレイヤー
	D3DXVECTOR3 PlayerMinPos;//最小頂点
	D3DXVECTOR3 PlayerMaxPos;//最大頂点

	bool PlayerIeBoxAtari = false;
	bool PlayerIe2BoxAtari = false;

	bool PlayerSita = false;
	bool PlayerMigi = false;
	bool PlayerUe = false;
	bool PlayerHidari = false;

};
#endif //_BOXATARIHANTEI_H_
