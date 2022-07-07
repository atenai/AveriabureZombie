//=============================================================================
//
// �����_���[(DirectX) [Renderer.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Renderer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3D9			Renderer::pD3d = NULL;		//Direct3D�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9	Renderer::pDevice = NULL;	//Direct3D�f���@�C�X

//==============
//�R���X�g���N�^
//==============
Renderer::Renderer()
{
}

//==============
//�f�X�g���N�^
//==============
Renderer::~Renderer()
{
}

//==============
//  �������֐�
//==============
HRESULT Renderer::Init(HINSTANCE hInstance, HWND hWnd)
{

	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	if (FAILED(pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//3
		return E_FAIL;
	}//3

	 // �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));//��ɏ���������
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//���̃X�N���[���̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//���̃X�N���[���̍���
	d3dpp.BackBufferFormat = d3ddm.Format;//�F���̎w��
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//���ꂵ���I�΂Ȃ��@�����M�����ǂ�������
	d3dpp.EnableAutoDepthStencil = TRUE;//���true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//��΃R���ɂ���
	d3dpp.Windowed = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//�f�o�C�X�I�u�W�F�N�g�̍쐬
	//[�f�o�C�X�쐬����]<�`��>��<���_����>
	if (FAILED(pD3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&pDevice)))
	{//4
		MessageBox(NULL, "pDevice�̎擾�Ɏ��s���܂���", "���s", MB_OK);
		return E_FAIL;
	}//4

	//�����ɃZ�b�g�����_�[�X�e�[�g�̐ݒ�
	//�A���r�G���g���C�g(����)�̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));


	return S_OK;
}

//==============
//  �I���֐�
//==============
void Renderer::Uninit(void)
{
	if (pDevice != NULL)
	{//�f�o�C�X�̊J��//2
		pDevice->Release();//����ŊJ�������
		pDevice = NULL;//�A�h���X���c���Ă���̂�NULL�ŏ㏑��
	}//2

	if (pD3d != NULL)
	{//Direct3D�I�u�W�F�N�g�̊J��//3
		pD3d->Release();
		pD3d = NULL;
	}//3
}

//================
//  �`��J�n�֐�
//================
void Renderer::DrawBegin(void)
{
	////////////////////���C�g�ƃ}�e���A���̐ݒ�////////////////
	//�}�e���A���ݒ�
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	//�}�e���A���̐F��ς���
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 1.0f;
	mat.Ambient.a = 1.0f;
	pDevice->SetMaterial(&mat);

	//���C�g�̐ݒ�
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(-1.0f, 0.0f, 0.0f);//(X,Y,Z)�̌��̓�����������w�肷��
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	pDevice->SetLight(0, &light);//���C�g�ԍ�0�`3
	pDevice->LightEnable(0, TRUE);//0�ԃ��C�g�I���I
	////////////////////���C�g�ƃ}�e���A���̐ݒ�////////////////

	pDevice->Clear(
		0, NULL, //�w�肵���擪�A�h���X�̋�`�Ȃǂ̂��̂�NULL�̂Ƃ낱�ɉ��L������̂���NULL��
		(D3DCLEAR_TARGET | //�F��Clear
			D3DCLEAR_ZBUFFER),//�[�b�g�o�b�t�@��Clear
		D3DCOLOR_RGBA(169, 169, 169, 255),//�w�i�F�̕ύX
		1.0f, 0);//1.0f���[�b�g�o�b�t�@��Clear���l�A�X�e���V�������̒l��Clear����̂�

	 //Direct3D�ɂ��`��̊J�n
	pDevice->BeginScene();
}

//================
//  �`��I���֐�
//================
void Renderer::DrawEnd(void)
{
	pDevice->EndScene();//Direct3D�ɂ��`��̏I��
	pDevice->Present(NULL, NULL, NULL, NULL);//�`�悪�I����ăf�o�C�X�Ƀv���[���g����

}

LPDIRECT3DDEVICE9 Renderer::GetDevice() 
{
	return pDevice; 
}