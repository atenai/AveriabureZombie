//=============================================================================
//
// ���C�� [main.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include<Windows.h>//#include<stdio.h>�̑���
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
// �}�N����`
//*****************************************************************************
///////////////���̃v���O�����̒��g�̓E�B���h�E����\��������///////////////////////////////////////////
#define CLASS_NAME "�N���X�l�[��"//�����u������
#define WINDOW_NAME "�A���F���A�u���E�]���r"//�����u������
///////////////���̃v���O�����̒��g�̓E�B���h�E����\��������///////////////////////////////////////////

//===============
//�O���[�o���ϐ�
//===============
//ImGui
#ifdef _DEBUG
bool b_MainWindow;//���C���E�B���h�E���J���Ă��邩�̃t���O
bool b_SubWindow;//�T�u�E�B���h�E
#endif // DEBUG
//ImGui

//===========================
//�N���X��(�݌v�})�̖��O�t��
//===========================
Manager *p_Manager;//�}�l�[�W���[�N���X(�݌v�})�̃|�C���^��p��

//===============
//�v���g�^�C�v�錾
//===============
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�E�B���h�E�v���V�[�W�� �R�[���o�b�N
HRESULT Init(HINSTANCE nInstance, HWND hWnd);//HRESULT//����������
void Uninit(void);//�I������
void Update(void);//�X�V����
void Draw(void);//�摜�\��
//ImGui
#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//ImGui�̃v���V�[�W��
#endif // DEBUG
//ImGui

//===========
//���C���֐�
//===========
//int main(void)�̑��肪���̓z��//�G���g���[�|�C���g(�ŏ��Ɏ��s�����֐�)//������Ȃ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{//1

	HWND hWnd = NULL;//�E�B���h�E���i�[����ϐ�
	MSG msg;//OS����󂯎�郁�b�Z�[�W���i�[���邽�߂ɕK�v


 //���E�B���h�E����ʂɕ\�����鏈��
 // �E�B���h�E�̏�����

 //WNDCLASSEX�\���̂ŃE�B���h�E�N���X�̃p�����[�^���w��
 //��
 //RegisterClassEx()�ł��̃E�B���h�E�N���X��o�^
 //��
 //CreateWindow()�œo�^�����N���X�����ƂɃE�B���h�E�����
 //��
 //ShowWindow()��UpdateWindow()�ŕ\������Ƃ�����A�̗���i�Z�b�g�j

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


	RegisterClassEx(&wndclass);//�E�B���h�E�N���X�̓o�^,createwindowex�Ŏg���̂ɐ�ΕK�v�i�g��Ȃ��Ɠ����Ȃ��j

	hWnd = CreateWindowEx//�E�B���h�E�̍쐬
	(
		0,//�g���E�B���h�E�X�^�C��
		CLASS_NAME,//"�N���X�l�[��"//�o�^����Ă���N���X��
		WINDOW_NAME,//"�J���t��"//�E�B���h�E��
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�̉������̈ʒu
		CW_USEDEFAULT,//�E�B���h�E�̏c�����̈ʒu
		SCREEN_WIDTH, //��(1366)//�E�B���h�E�̕�
		SCREEN_HEIGHT, //����(768)//�E�B���h�E�̍���
		NULL,//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎��ʎq
		hInstance,//�A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL//�E�B���h�E�쐬�f�[�^
	);

	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�\��
	UpdateWindow(hWnd);//�E�B���h�E�\��
	//���E�B���h�E����ʂɕ\�����鏈��



	//---- �������֐� ----
	// �_�C���N�g�RD�̏������֐����Ă�
	if (FAILED(Init(hInstance, hWnd)))//������DirectX�����������ꗘ�p�ł���悤�ɂȂ�
	{
		return 0;//WinMain�֐���OS����Ă΂�Ă����return���邱�Ƃ̓A�v���P�[�V�����̏I�����Ӗ�����B
	}

	//======================�Q�[�����[�v�J�n==============
	DWORD dwTimeNow = timeGetTime();//�������ɏ���
	DWORD dwTimeOld = timeGetTime();//�������ɏ���
	
	//����\
	timeBeginPeriod(1);

	// ���b�Z�[�W���[�v
	ZeroMemory(&msg, sizeof(msg));//msg�\���̂�0�ŏ�����
	while (msg.message != WM_QUIT)//msg�\���̂�message��WM_QUIT�łȂ����胋�[�v���J��Ԃ�����
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))//OS���烁�b�Z�[�W�����邩�𒲂�msg�\���̂Ƀ��b�Z�[�W���i�[����
		{
			//���b�Z�[�W������ꍇ���̓��e�����s�����b�Z�[�W���i�[����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//���b�Z�[�W���Ȃ��ꍇ�͂��̓��e�����s����
			
			//�Q�[������
			dwTimeNow = timeGetTime();//���̎��� = timeGetTime();
									  //		�~���b�@�@�@�~���b
			if ((dwTimeNow - dwTimeOld) >= (1000 / 60))//if((���̎��� - �O�̃t���[���̎���) >= (1000/60))
			{
				//�X�V
				Update();
				//�`��
				Draw();
		

				dwTimeOld = timeGetTime();//�O�t���[���̎��� = ���̎���;
			
			}
		}
	}
	//WM_QUIT��������while���[�v�𔲂��Ă��̉��̏��������s����

	timeEndPeriod(1);
	//=======================�Q�[�����[�v����============================

	Uninit();//�I������

	return(int)msg.wParam;
}//1


//OS����̃��b�Z�[�W�ɑ΂��Ă̓��e�����s//�����͉��̏��������e�̂�//������Ȃ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//1
	//ImGui
	#ifdef _DEBUG
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))//ImGui�̃v���V�[�W��
		{
			return true;
		}
	#endif // DEBUG
	//ImGui

	switch (uMsg)
	{//switch(uMsg)�̎n�܂蒆�J�b�R2

		//ImGui
		#ifdef _DEBUG
			case WM_SIZE://WM_SIZE�E�B���h�E�T�C�Y���ς�����ۂɋN������
				//�f�o�C�X�̍쐬�E�j�����s��ꂽ��InvalidateDeviceObjects()�ECreateDeviceObjects()���Ăяo���B
				ImGui_ImplDX9_InvalidateDeviceObjects();
				ImGui_ImplDX9_CreateDeviceObjects();
				break;
		#endif // DEBUG
		//ImGui

		case WM_DESTROY://�E�B���h�E�������(�~�{�^����������)�v���O�������I�����铮��
			PostQuitMessage(0);//�A�v���P�[�V�����̏I���𑣂�
			break;

		case WM_KEYDOWN:
		{//4
			switch (wParam)//wParam�͒ǉ���������
			{//5
				case VK_ESCAPE://[ESC]�L�[�������ꂽ��H
					int nID;//nID�Ƃ����������
					nID = MessageBox(hWnd, "�ꎞ��~��\n�Q�[�����I�����܂����H", "ESC�L�[", MB_YESNO);//MB_YESNO��yes��no�̃��b�Z�[�W�{�^�����o��
					if (nID == IDYES)//����YES����������{}�̒����N������
					{//7
						DestroyWindow(hWnd);//Window����
					}//7
					break;

				case VK_RETURN://�G���^�[�L�[�������ꂽ��
					
					break;
		
				
				}//5
			break;//switch(wParam)��break
		}//4
	
		default://switch(uMsg)
		break;//switch(uMsg)
	}//switch(uMsg)�̏I��蒆�J�b�R2
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}//1

 //DirectX�̓��e�͂������牺����
 //==============
 //  �������֐�
 //==============
HRESULT Init(HINSTANCE hInstance, HWND hWnd)//HRESULT
{//1
	InitSound(NULL);//���y��������
	Renderer::Init(hInstance, hWnd);//�����_���[(DirectX)�̏���������

	//ImGui
	#ifdef _DEBUG

		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

		b_MainWindow = true;
		b_SubWindow = false;

		IMGUI_CHECKVERSION();//ImGui�̃o�[�W�����`�F�b�N
		ImGui::CreateContext();

		//���o�͂̊m��
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui_ImplDX9_Init(hWnd, pDevice);//ImGui�̏���������

		ImGui::StyleColorsDark();//ImGui�̃E�B���h�E�J���[
	#endif // DEBUG
	//ImGui


	/////////////////////���������������́��ɓ����////////////////////////////

	
	InitKeyboard(hInstance, hWnd);//�L�[���͂̏���������

	p_Manager = new Manager;//�}�l�[�W���[�N���X�I�u�W�F�N�g�̐����ƃ������̊m�ۂƃR���X�g���N�^�̎��s
	p_Manager->Init();//�}�l�[�W���[�̏���������


	/////////////////////���������������́��ɓ����////////////////////////////
	
	
	return S_OK;
}//1

 //==============
 //  �I���֐�
 //==============
void Uninit(void)
{//1

	p_Manager->Uninit();//�}�l�[�W���[�̏I������
	delete p_Manager;//�}�l�[�W���[�N���X�I�u�W�F�N�g�̔j���ƃ������̉���ƃf�X�g���N�^�̎��s

	UninitKeyboard();//�L�[���͂̏I������
	UninitSound();//���y�̏I������

	//ImGui
	#ifdef _DEBUG
		ImGui_ImplDX9_Shutdown();//�I������
		ImGui::DestroyContext();//�R���e�L�X�g�̔j���E���b�Z�[�W�̔j��
	#endif // DEBUG
	//ImGui

	Renderer::Uninit();//�����_���[(DirectX)�̏I������
}//1

 //==============
 // �@�X�V�֐�
 //==============
void Update(void)
{//1	
	
	//////////////////�������火�̒��g��������/////////////////////////////////

	p_Manager->Update();//�}�l�[�W���[�̍X�V����

		UpdateKeyboard();//main.cpp(void Updata(void))//�L�[���͂̍X�V����

	////////////////�������灪�̒��g��������///////////////////////////////////	
}//1

 //==============
 // �@�`��֐�
 //==============
void Draw(void)
{//1


	Renderer::DrawBegin();//�����_���[(DirectX)�̕`�揈���J�n

	 ////////////////�������火�̒��g��������//���̒���Draw�n������///////////////////////////////
	 //���̒��ɕ`�悵�����v���O�����������
	

		p_Manager->Draw();//�}�l�[�W���[�̕`�揈��


	////////////////�������灪�̒��g��������//���̒���Draw�n������////////////////////////////////

	//ImGui(Update)
	#ifdef _DEBUG
		ImGui_ImplDX9_NewFrame();//ImGui�̍X�V���������̈�ԍŏ��ɌĂяo���Ȃ��Ƃ����Ȃ�
	//ImGui(Update)

	//ImGuI(Draw)
		if (b_MainWindow)
		{
			ImGui::SetNextWindowPos(ImVec2(1100, 30), ImGuiSetCond_Once);//�E�B���h�E�̍�����W�̃Z�b�g
			ImGui::SetNextWindowSize(ImVec2(350, 70), ImGuiSetCond_Once);//�E�B���h�E�T�C�Y�̃Z�b�g

			ImGui::Begin("ImGui Main Window", &b_MainWindow);//1�E�B���h�E���̕`��J�n�錾
			//////////////////�������火�̒��g��������//���̒���ImGui�n������///////////////////////////////

			ImGui::Text("Kashiwabara Yuta");//�e�L�X�g������

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FPS�\��


			//////////////////�������灪�̒��g��������//���̒���ImGui�n������///////////////////////////////////		
			ImGui::End();//1�E�B���h�E�̕`��I���錾
		}

		ImGui::EndFrame();//ImGui�̍X�V�����̍Ō�

		ImGui::Render();//�`�施��

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());//?
	#endif // DEBUG
	//ImGui(Draw)

	Renderer::DrawEnd();//�����_���[(DirectX)�̕`�揈���I��

}//1

