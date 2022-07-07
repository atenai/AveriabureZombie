//=============================================================================
//
// �]���r�̉e [HPgage.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "ZombieKage.h"
#include "Renderer.h"


ZombieKage::ZombieKage()
{
}


ZombieKage::~ZombieKage()
{
}

//==============
//  �������֐�
//==============
void ZombieKage::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_ZombieKage[Loop].Draw = true;//�{���x���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	}

	//�e�N�X�`��
	HRESULT hr;
	//�e�N�X�`���𐶐�����֐�//������Ȃ�
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kage.bmp", &m_pTexture);
	//�G���[�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "kage�e�N�X�`�����ǂݍ��߂܂���", "�G���[", MB_OK);
	}


}

//==============
//  �I���֐�
//==============
void ZombieKage::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//�e�N�X�`���̉��
}

//==============
// �@�X�V�֐�
//==============
void ZombieKage::Update(void)
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_ZombieKage[Loop].Draw == true)//�\���E��\�����Ǘ�����
		{
			//���_�̏����l��ݒ�
			//����
			m_ZombieKage[Loop].vertices[0].x = -0.5f;
			m_ZombieKage[Loop].vertices[0].y = 0.0f;
			m_ZombieKage[Loop].vertices[0].z = 0.5f;
			m_ZombieKage[Loop].vertices[0].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
			//�E��
			m_ZombieKage[Loop].vertices[1].x = 0.5f;
			m_ZombieKage[Loop].vertices[1].y = 0.0f;
			m_ZombieKage[Loop].vertices[1].z = 0.5f;
			m_ZombieKage[Loop].vertices[1].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
			//����
			m_ZombieKage[Loop].vertices[2].x = -0.5f;
			m_ZombieKage[Loop].vertices[2].y = 0.0f;
			m_ZombieKage[Loop].vertices[2].z = -0.5f;
			m_ZombieKage[Loop].vertices[2].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
			//�E��
			m_ZombieKage[Loop].vertices[3].x = 0.5f;
			m_ZombieKage[Loop].vertices[3].y = 0.0f;
			m_ZombieKage[Loop].vertices[3].z = -0.5f;
			m_ZombieKage[Loop].vertices[3].color = D3DCOLOR_RGBA(100, 100, 100, 100);
			m_ZombieKage[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);




			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_ZombieKage[Loop].mtxworld);//���������邽�߂̏�����

			D3DXMatrixTranslation(&m_ZombieKage[Loop].mtxworldT, m_ZombieKage[Loop].ZombiePos.x, -0.99f, m_ZombieKage[Loop].ZombiePos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_ZombieKage[Loop].mtxworld, &m_ZombieKage[Loop].mtxworld, &m_ZombieKage[Loop].mtxworldT);//����
		}
	}

}

//==============
// �@�`��֐�
//==============
void ZombieKage::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v
	if (pDevice == NULL)
	{
		return;
	}

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_ZombieKage[Loop].Draw == true)//�\���E��\�����Ǘ�����
		{

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

			pDevice->SetTransform(D3DTS_WORLD, &m_ZombieKage[Loop].mtxworld);

			//�@FVF�i������g�p���钸�_���j�̐ݒ�
			pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//��Őݒ肵��FVF���g�p
			//�e�N�X�`���̓\��t��
			pDevice->SetTexture(0, m_pTexture);


			//�v���~�e�B�u
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_ZombieKage[Loop].vertices, sizeof(CUSTOMVERTEX));

			//���Ƃɖ߂�
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

}


void ZombieKage::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_ZombieKage[Loop].Draw = true;//�{���x���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	}
}
