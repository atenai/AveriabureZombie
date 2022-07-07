//=============================================================================
//
// �A�C�e���}�[�J�[ [ItemMarker.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "ItemMarker.h"
#include "Renderer.h"

ItemMarker::ItemMarker()
{
}


ItemMarker::~ItemMarker()
{
}

//==============
//  �������֐�
//==============
void ItemMarker::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		m_ItemMarker[Loop].Draw = true;
	}


	//�e�N�X�`��
	HRESULT hr;
	//�e�N�X�`���𐶐�����֐�//������Ȃ�
	hr = D3DXCreateTextureFromFile(pDevice, "./data/texture/kiro.png", &m_pTexture);
	//�G���[�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "kiro�e�N�X�`�����ǂݍ��߂܂���", "�G���[", MB_OK);
	}


}

//==============
//  �I���֐�
//==============
void ItemMarker::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);//�e�N�X�`���̉��
}

//==============
// �@�X�V�֐�
//==============
void ItemMarker::Update(void)
{
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_ItemMarker[Loop].Draw == true)
		{
			//���_�̏����l��ݒ�
			//����
			m_ItemMarker[Loop].vertices[0].x = -0.2f;
			m_ItemMarker[Loop].vertices[0].y = 0.2f;
			m_ItemMarker[Loop].vertices[0].z = 0.0f;
			m_ItemMarker[Loop].vertices[0].color = 0xff00ff00;
			m_ItemMarker[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
			//�E��
			m_ItemMarker[Loop].vertices[1].x = 0.2f;
			m_ItemMarker[Loop].vertices[1].y = 0.2f;
			m_ItemMarker[Loop].vertices[1].z = 0.0f;
			m_ItemMarker[Loop].vertices[1].color = 0xff0000ff;
			m_ItemMarker[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
			//����
			m_ItemMarker[Loop].vertices[2].x = 0.0f;
			m_ItemMarker[Loop].vertices[2].y = -0.2f;
			m_ItemMarker[Loop].vertices[2].z = 0.0f;
			m_ItemMarker[Loop].vertices[2].color = 0xffff0000;
			m_ItemMarker[Loop].vertices[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);




			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_ItemMarker[Loop].mtxworld);//���������邽�߂̏�����

			D3DXMatrixTranslation(&m_ItemMarker[Loop].mtxworldT, m_ItemMarker[Loop].Pos.x, m_ItemMarker[Loop].Pos.y + 0.5f, m_ItemMarker[Loop].Pos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_ItemMarker[Loop].mtxworld, &m_ItemMarker[Loop].mtxworld, &m_ItemMarker[Loop].mtxworldT);//����


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
			D3DXMatrixMultiply(&m_ItemMarker[Loop].mtxworld, &matCurrentView, &m_ItemMarker[Loop].mtxworld);
			///////////////////////�r���{�[�h����///////////////////////////////////////////
		}
	}
}

//==============
// �@�`��֐�
//==============
void ItemMarker::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v
	if (pDevice == NULL)
	{
		return;
	}

	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_ItemMarker[Loop].Draw == true)
		{

			pDevice->SetTransform(D3DTS_WORLD, &m_ItemMarker[Loop].mtxworld);

			//�@FVF�i������g�p���钸�_���j�̐ݒ�
			pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//��Őݒ肵��FVF���g�p
			//�e�N�X�`���̓\��t��
			pDevice->SetTexture(0, m_pTexture);


			//�v���~�e�B�u
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, m_ItemMarker[Loop].vertices, sizeof(CUSTOMVERTEX));
		}
	}

}

void ItemMarker::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	for (int Loop = 0; Loop < ITEM_NUM; Loop++)//�\���̂̐������� 
	{
		m_ItemMarker[Loop].Draw = true;//�{���x���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	}
}