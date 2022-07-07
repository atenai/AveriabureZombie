//=============================================================================
//
// �v���C���[�e�̕`�� [PlayerKage.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "PlayerKage.h"
#include "Renderer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//==============
//�R���X�g���N�^
//==============
PlayerKage::PlayerKage()
{
}

//==============
//�f�X�g���N�^
//==============
PlayerKage::~PlayerKage()
{
}

//==============
//  �������֐�
//==============
void PlayerKage::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	//�e�N�X�`��
	HRESULT hr;
	//�e�N�X�`���𐶐�����֐�//������Ȃ�
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kage.bmp", &m_pTexture);
	//�G���[�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "boy�e�N�X�`�����ǂݍ��߂܂���", "�G���[", MB_OK);
	}


}

//==============
//  �I���֐�
//==============
void PlayerKage::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//�e�N�X�`���̉��
}

//==============
// �@�X�V�֐�
//==============
void PlayerKage::Update(void)
{

	//���_�̏����l��ݒ�
	//����
	vertices[0].x = -0.5f;
	vertices[0].y = 0.0f;
	vertices[0].z = 0.5f;
	vertices[0].color = m_color;
	vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
	//�E��
	vertices[1].x = 0.5f;
	vertices[1].y = 0.0f;
	vertices[1].z = 0.5f;
	vertices[1].color = m_color;
	vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
	//����
	vertices[2].x = -0.5f;
	vertices[2].y = 0.0f;
	vertices[2].z = -0.5f;
	vertices[2].color = m_color;
	vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
	//�E��
	vertices[3].x = 0.5f;
	vertices[3].y = 0.0f;
	vertices[3].z = -0.5f;
	vertices[3].color = m_color;
	vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);




	//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
	D3DXMatrixIdentity(&mtxworld);//���������邽�߂̏�����

	D3DXMatrixTranslation(&mtxworldT, PlayerPos.x, -0.99f, PlayerPos.z);//X���f���̕��s�ړ��֐�
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxworldT);//����

}

//==============
// �@�`��֐�
//==============
void PlayerKage::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v
	if (pDevice == NULL)
	{
		return;
	}

	//�A���t�@�u�����f�B���O
	//�A���t�@�����̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�A���t�@�u�����f�B���O

	//�e�N�X�`���ƒ��_�F�̗����𔽉f������
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pDevice->SetTransform(D3DTS_WORLD, &mtxworld);

	//�@FVF�i������g�p���钸�_���j�̐ݒ�
	pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//��Őݒ肵��FVF���g�p
	//�e�N�X�`���̓\��t��
	pDevice->SetTexture(0, m_pTexture);


	//�v���~�e�B�u
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(CUSTOMVERTEX));

	//���Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}