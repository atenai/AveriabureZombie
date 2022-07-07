//=============================================================================
//  
// UIの描画
//2D画像を表示する為の
//SetPolygonColor();//ポリゴンカラーの設定
//DrawPolygon();//ポリゴンの設定
//の2つを使う為必要
//
//=============================================================================
#include "UI.h"
#include "Renderer.h"

//FVFの宣言(定数)
//座標			//カラー		//テクスチャ
#define FVF_VERTEX_2D  (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//設定


UI::UI()
{
}


UI::~UI()
{
}

//UIの初期化処理
bool UI::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return false;
	}

	//テクスチャ
	HRESULT hr;

	for (int Loop = 0; Loop < TEX_MAX; Loop++)
	{
		//テクスチャを生成する関数//いじらない
		hr = D3DXCreateTextureFromFile(pDevice, m_Texture[Loop].fileName, &m_pTexture[Loop]);
		//エラーチェック
		if (FAILED(hr))
		{
			MessageBox(NULL, "UIテクスチャが読み込めません", "エラー", MB_OK);
			return false;
		}

	}

	////アルファブレンディング
	////レンダーステートの設定
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンド開始
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////テクスチヤステージステートの設定
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	////
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////フィルタリング
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//アルファブレンド終了//2018/12/12/add

	return true;
}

//UIの終了処理
void UI::Uninit(void)//いじらない
{

	for (int Loop = TEX_1; Loop < TEX_MAX; Loop++)
	{
		if (m_pTexture[Loop] != NULL)
		{
			m_pTexture[Loop]->Release();
			m_pTexture[Loop] = NULL;
		}
	}


}

//UIの更新処理
void UI::Update(void)
{

}

//UIの描画処理
void UI::Draw(int texNum, float dx, float dy, int dw, int dh, int tcx, int tcy, int tcw, int tch)//画像を表示
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要
	if (pDevice == NULL)
	{
		return;
	}

	//////////////////ここから↓の中身をいじる/////////////////////////////////

	float tw = m_Texture[texNum].width;
	float th = m_Texture[texNum].height;

	float u0 = (float)tcx / (float)tw;
	float v0 = (float)tcy / (float)th;
	float u1 = (float)(tcx + tcw) / (float)tw;
	float v1 = (float)(tcy + tch) / (float)th;


	//　ポリゴンの描画処理
	VERTEX_2D vtx[] = {//D3DPT_TRIANGLESTRIP
		{ D3DXVECTOR4(dx + 0.0f - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u0, v0) },//左上
		{ D3DXVECTOR4(dx + dw - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u1, v0) },//右上
		{ D3DXVECTOR4(dx + 0.0f - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u0, v1) },//左下
		{ D3DXVECTOR4(dx + dw - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u1, v1) },//右下
	};

	//　FVF（今から使用する頂点情報）の設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの貼り付け
	pDevice->SetTexture(0, m_pTexture[texNum]);

	//3D描画をOFFにして→2D描画をし→また3D描画をONにする//これをする事でUIを表示可能
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);//3D描画をFALSEにする(OFF)


	//アルファブレンディング
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンド開始
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチヤステージステートの設定
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//フィルタリング
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//アルファブレンディング



	//プリミティブ
	pDevice->DrawPrimitiveUP//これが呼ばれないとポリゴンが描画できない
	(
		D3DPT_TRIANGLESTRIP,//トライアングルストリップ//ポリゴンをどのように表示するか
		2,//三角形の面を2つ表示する//表示する面の数をいれる
		&vtx[0],//VERTEX_2D vtx[] = {};で作った内容を0番目から呼び出す
		sizeof(VERTEX_2D)//↑で作ったサイズを呼び出す
	);




	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//アルファブレンド終了//2018/12/12/add



	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);//3D描画をTRUEにする(ON)
	////////////////ここから↑の中身をいじる/////////////////////////////////////

}

//void DrawNumber(int 表したい数, float 表示するX座標, float 表示するY座標)
void UI::DrawNumber(int n, float x, float y)
{
	int nX = 0, nY = 0;
	if (n < 0 || n>9)
	{
		return;
	}
	if (n > 4)
	{
		nX = n - 5;
		nY = 1;
	}
	else
	{
		nX = n;
		nY = 0;
	}
	SetPolygonColor(D3DCOLOR_RGBA(150, 150, 150, 255));//ポリゴンカラーの設定
	Draw(4, x, y, NUMBER_WIDTH, NUMBER_HEIGHT, 0 + 29 * nX, 0 + 32 * nY, 29, 32);//テクスチャの描画
}

//void DrawScore(int 表したいスコアー(数字), int スコアーの右枠, float 表示したいX座標, float 表示したいY座標, bool スコアーの右枠を0で埋めるかどうか)
void UI::DrawScore(int nScore, int nDig, float x, float y, bool bZero)
{
	//左詰め
	if (nDig < 0)//nDigが0より小さいとき
	{
		nDig = 0;//nDigは0
		for (;;)//無限ループ
		{
			nScore /= 10;//nScore ÷= 10
			if (nScore == 0)//もしnScoreが0なら
			{
				break;
			}
			nDig++;
		}
	}

	//カンスト値
	int maxScore = 10;

	for (int i = 1; i < nDig; i++)
	{
		maxScore *= 10;
	}
	maxScore--;

	nScore = min(maxScore, nScore);

	for (int i = 1; i <= nDig; i++)
	{
		int n = nScore % 10;
		DrawNumber(n, x + NUMBER_WIDTH * (nDig - i), y);
		nScore /= 10;
		if (nScore == 0 && !bZero)
		{
			break;
		}
	}
}