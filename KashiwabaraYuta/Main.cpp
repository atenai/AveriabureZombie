//=============================================================================
//
// メイン [main.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include<Windows.h>//#include<stdio.h>の代わり
#include<d3d9.h>
#include<d3dx9.h>
#include<stdio.h>
#include "Main.h"
#include"input.h"
#include "Renderer.h"
#include "Manager.h"
#include "imgui.h"//ImGui
#include "imgui_impl_dx9.h"//ImGui
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
///////////////このプログラムの中身はウィンドウ名を表示するやつ///////////////////////////////////////////
#define CLASS_NAME "クラスネーム"//文字置き換え
#define WINDOW_NAME "アヴェリアブル・ゾンビ"//文字置き換え
///////////////このプログラムの中身はウィンドウ名を表示するやつ///////////////////////////////////////////

//===============
//グローバル変数
//===============
//ImGui
#ifdef _DEBUG
bool b_MainWindow;//メインウィンドウを開いているかのフラグ
bool b_SubWindow;//サブウィンドウ
#endif // DEBUG
//ImGui

//===========================
//クラスの(設計図)の名前付け
//===========================
Manager *p_Manager;//マネージャークラス(設計図)のポインタを用意

//===============
//プロトタイプ宣言
//===============
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//ウィンドウプロシージャ コールバック
HRESULT Init(HINSTANCE nInstance, HWND hWnd);//HRESULT//初期化処理
void Uninit(void);//終了処理
void Update(void);//更新処理
void Draw(void);//画像表示
//ImGui
#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//ImGuiのプロシージャ
#endif // DEBUG
//ImGui

//===========
//メイン関数
//===========
//int main(void)の代わりが下の奴↓//エントリーポイント(最初に実行される関数)//いじらない
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{//1

	HWND hWnd = NULL;//ウィンドウを格納する変数
	MSG msg;//OSから受け取るメッセージを格納するために必要


 //↓ウィンドウを画面に表示する処理
 // ウィンドウの初期化

 //WNDCLASSEX構造体でウィンドウクラスのパラメータを指定
 //↓
 //RegisterClassEx()でそのウィンドウクラスを登録
 //↓
 //CreateWindow()で登録したクラスをもとにウィンドウを作り
 //↓
 //ShowWindow()とUpdateWindow()で表示するという一連の流れ（セット）

	WNDCLASSEX  wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = CLASS_NAME;
	wndclass.hIconSm = NULL;


	RegisterClassEx(&wndclass);//ウィンドウクラスの登録,createwindowexで使うのに絶対必要（使わないと動かない）

	hWnd = CreateWindowEx//ウィンドウの作成
	(
		0,//拡張ウィンドウスタイル
		CLASS_NAME,//"クラスネーム"//登録されているクラス名
		WINDOW_NAME,//"カラフル"//ウィンドウ名
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//ウィンドウの横方向の位置
		CW_USEDEFAULT,//ウィンドウの縦方向の位置
		SCREEN_WIDTH, //幅(1366)//ウィンドウの幅
		SCREEN_HEIGHT, //高さ(768)//ウィンドウの高さ
		NULL,//親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,//メニューハンドルまたは識別子
		hInstance,//アプリケーションインスタンスのハンドル
		NULL//ウィンドウ作成データ
	);

	ShowWindow(hWnd, nCmdShow);//ウィンドウ表示
	UpdateWindow(hWnd);//ウィンドウ表示
	//↑ウィンドウを画面に表示する処理



	//---- 初期化関数 ----
	// ダイレクト３Dの初期化関数を呼ぶ
	if (FAILED(Init(hInstance, hWnd)))//ここでDirectXが初期化され利用できるようになる
	{
		return 0;//WinMain関数はOSから呼ばれている為returnすることはアプリケーションの終了を意味する。
	}

	//======================ゲームループ開始==============
	DWORD dwTimeNow = timeGetTime();//自分風に書く
	DWORD dwTimeOld = timeGetTime();//自分風に書く
	
	//分解能
	timeBeginPeriod(1);

	// メッセージループ
	ZeroMemory(&msg, sizeof(msg));//msg構造体を0で初期化
	while (msg.message != WM_QUIT)//msg構造体のmessageがWM_QUITでない限りループを繰り返す処理
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))//OSからメッセージがあるかを調べmsg構造体にメッセージを格納する
		{
			//メッセージがある場合この内容を実行しメッセージを格納する
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//メッセージがない場合はこの内容を実行する
			
			//ゲーム処理
			dwTimeNow = timeGetTime();//今の時間 = timeGetTime();
									  //		ミリ秒　　　ミリ秒
			if ((dwTimeNow - dwTimeOld) >= (1000 / 60))//if((今の時間 - 前のフレームの時間) >= (1000/60))
			{
				//更新
				Update();
				//描画
				Draw();
		

				dwTimeOld = timeGetTime();//前フレームの時間 = 今の時間;
			
			}
		}
	}
	//WM_QUITがきたらwhileループを抜けてこの下の処理を実行する

	timeEndPeriod(1);
	//=======================ゲームループ完了============================

	Uninit();//終了処理

	return(int)msg.wParam;
}//1


//OSからのメッセージに対しての内容を実行//ここは俺の書いた内容のみ//いじらない
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//1
	//ImGui
	#ifdef _DEBUG
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))//ImGuiのプロシージャ
		{
			return true;
		}
	#endif // DEBUG
	//ImGui

	switch (uMsg)
	{//switch(uMsg)の始まり中カッコ2

		//ImGui
		#ifdef _DEBUG
			case WM_SIZE://WM_SIZEウィンドウサイズが変わった際に起動する
				//デバイスの作成・破棄が行われたらInvalidateDeviceObjects()・CreateDeviceObjects()を呼び出す。
				ImGui_ImplDX9_InvalidateDeviceObjects();
				ImGui_ImplDX9_CreateDeviceObjects();
				break;
		#endif // DEBUG
		//ImGui

		case WM_DESTROY://ウィンドウを閉じたら(×ボタン押したら)プラグラムが終了する動作
			PostQuitMessage(0);//アプリケーションの終了を促す
			break;

		case WM_KEYDOWN:
		{//4
			switch (wParam)//wParamは追加情報を入れる
			{//5
				case VK_ESCAPE://[ESC]キーが押されたら？
					int nID;//nIDという箱を作る
					nID = MessageBox(hWnd, "一時停止中\nゲームを終了しますか？", "ESCキー", MB_YESNO);//MB_YESNOはyesかnoのメッセージボタンが出る
					if (nID == IDYES)//もしYESを押したら{}の中を起動する
					{//7
						DestroyWindow(hWnd);//Windowを壊す
					}//7
					break;

				case VK_RETURN://エンターキーが押されたら
					
					break;
		
				
				}//5
			break;//switch(wParam)のbreak
		}//4
	
		default://switch(uMsg)
		break;//switch(uMsg)
	}//switch(uMsg)の終わり中カッコ2
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}//1

 //DirectXの内容はここから下から
 //==============
 //  初期化関数
 //==============
HRESULT Init(HINSTANCE hInstance, HWND hWnd)//HRESULT
{//1
	InitSound(NULL);//音楽を初期化
	Renderer::Init(hInstance, hWnd);//レンダラー(DirectX)の初期化処理

	//ImGui
	#ifdef _DEBUG

		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDeviceを使う場合これが必要

		b_MainWindow = true;
		b_SubWindow = false;

		IMGUI_CHECKVERSION();//ImGuiのバージョンチェック
		ImGui::CreateContext();

		//入出力の確保
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui_ImplDX9_Init(hWnd, pDevice);//ImGuiの初期化処理

		ImGui::StyleColorsDark();//ImGuiのウィンドウカラー
	#endif // DEBUG
	//ImGui


	/////////////////////初期化処理をこの↓に入れる////////////////////////////

	
	InitKeyboard(hInstance, hWnd);//キー入力の初期化処理

	p_Manager = new Manager;//マネージャークラスオブジェクトの生成とメモリの確保とコンストラクタの実行
	p_Manager->Init();//マネージャーの初期化処理


	/////////////////////初期化処理をこの↑に入れる////////////////////////////
	
	
	return S_OK;
}//1

 //==============
 //  終了関数
 //==============
void Uninit(void)
{//1

	p_Manager->Uninit();//マネージャーの終了処理
	delete p_Manager;//マネージャークラスオブジェクトの破棄とメモリの解放とデストラクタの実行

	UninitKeyboard();//キー入力の終了処理
	UninitSound();//音楽の終了処理

	//ImGui
	#ifdef _DEBUG
		ImGui_ImplDX9_Shutdown();//終了処理
		ImGui::DestroyContext();//コンテキストの破棄・メッセージの破棄
	#endif // DEBUG
	//ImGui

	Renderer::Uninit();//レンダラー(DirectX)の終了処理
}//1

 //==============
 // 　更新関数
 //==============
void Update(void)
{//1	
	
	//////////////////ここから↓の中身をいじる/////////////////////////////////

	p_Manager->Update();//マネージャーの更新処理

		UpdateKeyboard();//main.cpp(void Updata(void))//キー入力の更新処理

	////////////////ここから↑の中身をいじる///////////////////////////////////	
}//1

 //==============
 // 　描画関数
 //==============
void Draw(void)
{//1


	Renderer::DrawBegin();//レンダラー(DirectX)の描画処理開始

	 ////////////////ここから↓の中身をいじる//この中にDraw系を入れる///////////////////////////////
	 //この中に描画したいプログラムをいれる
	

		p_Manager->Draw();//マネージャーの描画処理


	////////////////ここから↑の中身をいじる//この中にDraw系を入れる////////////////////////////////

	//ImGui(Update)
	#ifdef _DEBUG
		ImGui_ImplDX9_NewFrame();//ImGuiの更新処理するやつの一番最初に呼び出さないといけない
	//ImGui(Update)

	//ImGuI(Draw)
		if (b_MainWindow)
		{
			ImGui::SetNextWindowPos(ImVec2(1100, 30), ImGuiSetCond_Once);//ウィンドウの左上座標のセット
			ImGui::SetNextWindowSize(ImVec2(350, 70), ImGuiSetCond_Once);//ウィンドウサイズのセット

			ImGui::Begin("ImGui Main Window", &b_MainWindow);//1ウィンドウ分の描画開始宣言
			//////////////////ここから↓の中身をいじる//この中にImGui系を入れる///////////////////////////////

			ImGui::Text("Kashiwabara Yuta");//テキストを入れる

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FPS表示


			//////////////////ここから↑の中身をいじる//この中にImGui系を入れる///////////////////////////////////		
			ImGui::End();//1ウィンドウの描画終了宣言
		}

		ImGui::EndFrame();//ImGuiの更新処理の最後

		ImGui::Render();//描画命令

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());//?
	#endif // DEBUG
	//ImGui(Draw)

	Renderer::DrawEnd();//レンダラー(DirectX)の描画処理終了

}//1

