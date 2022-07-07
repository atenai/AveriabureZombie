//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,//タイトル
	SOUND_LABEL_BGM001,//ゲームプレイ
	SOUND_LABEL_BGM002,//弾発射音
	SOUND_LABEL_BGM003, // ゾンビと弾の当たった音
	SOUND_LABEL_BGM004,//決定オン
	SOUND_LABEL_BGM005,//弾アイテム音
	SOUND_LABEL_BGM006, // 銃を構える音
	SOUND_LABEL_BGM007,//地雷爆発音
	SOUND_LABEL_BGM008,//ゲームクリアー
	SOUND_LABEL_BGM009,//ゲームオーバー
	SOUND_LABEL_BGM010,//薬莢音
	SOUND_LABEL_BGM011,//地雷の設置音
	SOUND_LABEL_BGM012,//地雷の起動音
	SOUND_LABEL_BGM013,//プレイヤーダメージ音
	SOUND_LABEL_BGM014,//壁に弾が当たった時の音
	SOUND_LABEL_BGM015,//回復アイテム音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);//特定の音楽だけを止める
void StopSound(void);//全ての音楽を止める

#endif
