//=============================================================================
//
// �J [Ame.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Ame.h"
#include "Renderer.h"


//==============
//�R���X�g���N�^
//==============
Ame::Ame()
{
}

//==============
//�f�X�g���N�^
//==============
Ame::~Ame()
{
}


//==============
//  �������֐�
//==============
void Ame::Init(void)
{

	for (int i = 0; i < AME_NUM; i++)//�\���̂̐������� 
	{
		m_Ame[i].used = FALSE;
		m_Ame[i].pos.x = -50 + rand() % 100;
		m_Ame[i].pos.y = 30;
		m_Ame[i].pos.z = -50 + rand() % 100;
	}

	//�����^�C�}�[�ݒ�
	AmesetTimer(0.00000001);//�����ōŏ��̐��\������܂ł̎��Ԃ��J�E���g����(0.1�b����o�Ă���)

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	//���_�̏����l��ݒ�
	CUSTOMVERTEX vertices[] =
	{

	{ -0.05f,1.0f,0.0f,0xff00ff00, D3DXVECTOR2(0.0f,0.0f) },
	{ 0.05f, 1.0f,0.0f,0xff0000ff,D3DXVECTOR2(1.0f,0.0f) },
	{ 0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(1.0f,1.0f) },

	{ 0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(1.0f,1.0f) },
	{ -0.05f,-1.0f,0.0f,0xffff0000, D3DXVECTOR2(0.0f,1.0f) },
	{ -0.05f,1.0f,0.0f,0xff00ff00, D3DXVECTOR2(0.0f,0.0f) },

	};

	//���_�o�b�t�@�[���쐬
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(vertices),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &pVB, NULL)))
	{
		MessageBox(0, "���_�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "", MB_OK);
	}
	//���_�o�b�t�@�[�ɒ��_��ݒ�i�R�s�[�j����
	VOID* pVertices;
	if (FAILED(pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		MessageBox(0, "���_�o�b�t�@�[�̃��b�N�Ɏ��s���܂���", "", MB_OK);
	}
	memcpy(pVertices, vertices, sizeof(vertices));
	pVB->Unlock();

	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		/*d3dxMaterials[i].pTextureFilename*/"./data/texture/Ame2.png",
		&m_pTexture)))
	{
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
	}




}

//==============
//  �I���֐�
//==============
void Ame::Uninit(void)
{

	SAFE_RELEASE(pVB);
	SAFE_RELEASE(m_pTexture);//�e�N�X�`���̉��

}

//==============
// �@�X�V�֐�
//==============
void Ame::Update(void)
{
	//�J�̏o��
	if (AmeisTimerGoal() == TRUE)//isTimeGoal��TRUE�Ȃ牺�̓��e�����s
	{

		//�J���o��������
		for (int i = 0; i < AME_NUM; i = i + 1)
		{
			if (m_Ame[i].used == FALSE)
			{

				m_Ame[i].pos.x = -50 + rand() % 100;
				m_Ame[i].pos.y = 30;
				m_Ame[i].pos.z = -50 + rand() % 100;

				m_Ame[i].used = TRUE;
				break;//�����ŏ����I��
			}
		}

		AmesetTimer(0.00000001);//0.1�b�����ɐ��TRUE//�܂�0.1�b�`���[�W����

	}

	//�J�̕\���E�ړ�
	for (int i = 0; i < AME_NUM; i = i + 1)
	{
		if (m_Ame[i].used == TRUE)
		{
			m_Ame[i].pos.y = m_Ame[i].pos.y - 0.4f;//�ړ�
			if (m_Ame[i].pos.y <= -2.0f) //��ʊO�ɏo�������
			{
				m_Ame[i].used = FALSE;
			}

			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_Ame[i].mtxworld);//���������邽�߂̏�����

			D3DXMatrixTranslation(&m_Ame[i].mtxworldT, m_Ame[i].pos.x, m_Ame[i].pos.y, m_Ame[i].pos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_Ame[i].mtxworld, &m_Ame[i].mtxworld, &m_Ame[i].mtxworldT);//����


			///////////////////////�r���{�[�h����///////////////////////////////////////////
			LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

			D3DXMATRIXA16 matCurrentView;//�r���[�s����Ƃ�����p�ϐ�
			//���݂̃r���[�s��𓾂āA�A
			pDevice->GetTransform(D3DTS_VIEW, &matCurrentView);
			// ������t�s��ɂ��āA�A
			D3DXMatrixTranspose(&matCurrentView, &matCurrentView);
			//�t�s��ɂ����ۂ̃g�����X���[�V���������ɂ͔��f�����Ȃ�����(��������Ȃ��ƃJ�����Ƀr���{�[�h�����Ă���)
			matCurrentView._14 = 0.0f;
			matCurrentView._24 = 0.0f;
			matCurrentView._34 = 0.0f;
			// ���[���h�s��Ɋ|�����킹��ƁA�r���[�ϊ���ł��������ƂɂȂ�
			D3DXMatrixMultiply(&m_Ame[i].mtxworld, &matCurrentView, &m_Ame[i].mtxworld);
			///////////////////////�r���{�[�h����///////////////////////////////////////////

		}
	}

}

//==============
// �@�`��֐�
//==============
void Ame::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int i = 0; i < AME_NUM; i++)//�\���̂̐������� 
	{
		//�A���t�@�u�����f�B���O
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//�A���t�@�u�����h�J�n
		pDevice->SetRenderState(D3DRS_ALPHAREF, 96);//�e�N�X�`���̔w�i�𓧖���
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//�e�N�X�`���̔w�i�𓧖���
		//�A���t�@�u�����f�B���O

		pDevice->SetTransform(D3DTS_WORLD, &m_Ame[i].mtxworld);

		pDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
		pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//��Őݒ肵��FVF���g�p

		pDevice->SetTexture(0, m_pTexture);//�e�N�X�`�����Z�b�g

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

		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//�e�N�X�`�����Z�b�g
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);//�e�N�X�`�����Z�b�g
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);//�e�N�X�`�����Z�b�g

		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//�A���t�@�u�����h�I��//2018/12/12/add
	}
}

//�������牺�͐�p�̊֐�
//�ڕW���Ԃ��Z�b�g����
void Ame::AmesetTimer(DWORD time)
{

	Ameg_goaltimes = timeGetTime() + time;//�Z�b�g����2�b��+timeGetTime(0����+1���Ȃ�֐�)=g_goaltime//�������J�E���g�̍ő�l
	//�i��j3000 = 0 + 3000
}

//�^�C�}�[���`�F�b�N����
BOOL Ame::AmeisTimerGoal()//�������J�E���g����
{
	//������timeGetTime���܂�0�~���b���琔���邻����g_goaltimes���z������TRUE�ɂȂ�
	//�i��j3000 > 0 = false
	if (Ameg_goaltimes > timeGetTime())//g_goaltime��timeGetTime���傫���ꍇ
	{

		return FALSE;//FALSE�ɂ���

	}
	//�i��jtimeGetTime��3001�ɂȂ�����
	return TRUE;//TRUE�ɂ���

}