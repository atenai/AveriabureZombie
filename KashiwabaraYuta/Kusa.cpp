//=============================================================================
//
// �� [Kusa.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Kusa.h"
#include "Renderer.h"

//==============
//�R���X�g���N�^
//==============
Kusa::Kusa()
{
}

//==============
//�f�X�g���N�^
//==============
Kusa::~Kusa()
{
}

//==============
//�R���X�g���N�^
//==============
Kusa1::Kusa1()
{
}

//==============
//�f�X�g���N�^
//==============
Kusa1::~Kusa1()
{
}

//==============
//�R���X�g���N�^
//==============
Kusa2::Kusa2()
{
}

//==============
//�f�X�g���N�^
//==============
Kusa2::~Kusa2()
{
}

//==============
//�R���X�g���N�^
//==============
Kusa3::Kusa3() 
{
}

//==============
//�f�X�g���N�^
//==============
Kusa3::~Kusa3() 
{
}

//==============
//�R���X�g���N�^
//==============
Tree::Tree()
{
}

//==============
//�f�X�g���N�^
//==============
Tree::~Tree()
{
}

//==============
//  �������֐�
//==============
void Kusa1::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{

		//���_�̏����l��ݒ�
		//����
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//�E��
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//���_�o�b�t�@�[���쐬
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "", MB_OK);
		}
		//���_�o�b�t�@�[�ɒ��_��ݒ�i�R�s�[�j����

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̃��b�N�Ɏ��s���܂���", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed001.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		}

	}

}

void Kusa2::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{

		//���_�̏����l��ݒ�
		//����
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//�E��
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//���_�o�b�t�@�[���쐬
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "", MB_OK);
		}
		//���_�o�b�t�@�[�ɒ��_��ݒ�i�R�s�[�j����

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̃��b�N�Ɏ��s���܂���", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed002.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		}

	}

}

void Kusa3::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = -0.15;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_Kusa[Loop].pos.z <= -51 || 51 <= m_Kusa[Loop].pos.z || m_Kusa[Loop].pos.x <= -51 || 51 <= m_Kusa[Loop].pos.x)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = rand() % 10;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{

		//���_�̏����l��ݒ�
		//����
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//�E��
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale * 0.2f;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -0.2f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 0.1f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);


		//���_�o�b�t�@�[���쐬
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "", MB_OK);
		}
		//���_�o�b�t�@�[�ɒ��_��ݒ�i�R�s�[�j����

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̃��b�N�Ɏ��s���܂���", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/weed003.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		}

	}

}

//==============
//  �������֐�
//==============
void Tree::Init(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		m_Kusa[Loop].pos.x = -50 + rand() % 100;
		m_Kusa[Loop].pos.y = 0;
		m_Kusa[Loop].pos.z = -50 + rand() % 100;
		//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
		if (m_Kusa[Loop].pos.x == 0 && m_Kusa[Loop].pos.z == 0)
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < 6 && 4 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Kusa[Loop].pos.x && m_Kusa[Loop].pos.x < -4 && -6 < m_Kusa[Loop].pos.z && m_Kusa[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Kusa[Loop].pos.x = -50 + rand() % 100;
			m_Kusa[Loop].pos.z = -50 + rand() & 100;
		}

		m_Kusa[Loop].Scale = 3 + rand() % 7;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{

		//���_�̏����l��ݒ�
		//����
		m_Kusa[Loop].vertices[0].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[0].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[0].z = 0.0f;
		m_Kusa[Loop].vertices[0].color = 0xff00ff00;
		m_Kusa[Loop].vertices[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[1].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[1].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[1].z = 0.0f;
		m_Kusa[Loop].vertices[1].color = 0xff0000ff;
		m_Kusa[Loop].vertices[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
		//�E��
		m_Kusa[Loop].vertices[2].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[2].y = -1.0f;
		m_Kusa[Loop].vertices[2].z = 0.0f;
		m_Kusa[Loop].vertices[2].color = 0xffff0000;
		m_Kusa[Loop].vertices[2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//�E��
		m_Kusa[Loop].vertices[3].x = m_Kusa[Loop].Scale;
		m_Kusa[Loop].vertices[3].y = -1.0f;
		m_Kusa[Loop].vertices[3].z = 0.0f;
		m_Kusa[Loop].vertices[3].color = 0xffff0000;
		m_Kusa[Loop].vertices[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[4].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[4].y = -1.0f;
		m_Kusa[Loop].vertices[4].z = 0.0f;
		m_Kusa[Loop].vertices[4].color = 0xffff0000;
		m_Kusa[Loop].vertices[4].texcoord = D3DXVECTOR2(0.0f, 1.0f);
		//����
		m_Kusa[Loop].vertices[5].x = m_Kusa[Loop].Scale * -1.0f;
		m_Kusa[Loop].vertices[5].y = m_Kusa[Loop].Scale * 2.0f;
		m_Kusa[Loop].vertices[5].z = 0.0f;
		m_Kusa[Loop].vertices[5].color = 0xff00ff00;
		m_Kusa[Loop].vertices[5].texcoord = D3DXVECTOR2(0.0f, 0.0f);





	//���_�o�b�t�@�[���쐬
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(m_Kusa[Loop].vertices),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &m_Kusa[Loop].pVB, NULL)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̍쐬�Ɏ��s���܂���", "", MB_OK);
		}
		//���_�o�b�t�@�[�ɒ��_��ݒ�i�R�s�[�j����

		if (FAILED(m_Kusa[Loop].pVB->Lock(0, sizeof(m_Kusa[Loop].vertices), (void**)&m_Kusa[Loop].pVertices, 0)))
		{
			MessageBox(0, "���_�o�b�t�@�[�̃��b�N�Ɏ��s���܂���", "", MB_OK);
		}
		memcpy(m_Kusa[Loop].pVertices, m_Kusa[Loop].vertices, sizeof(m_Kusa[Loop].vertices));
		m_Kusa[Loop].pVB->Unlock();

		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			/*d3dxMaterials[i].pTextureFilename*/"./data/texture/tree_b.png",
			&m_pTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		}



	}
}



//==============
//  �I���֐�
//==============
void Kusa::Uninit(void)
{

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		SAFE_RELEASE(m_Kusa[Loop].pVB);

	}
	SAFE_RELEASE(m_pTexture);//�e�N�X�`���̉��

}

//==============
// �@�X�V�֐�
//==============
void Kusa::Update(void)
{
	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{

		//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
		D3DXMatrixIdentity(&m_Kusa[Loop].mtxworld);//���������邽�߂̏�����

		D3DXMatrixTranslation(&m_Kusa[Loop].mtxworldT, m_Kusa[Loop].pos.x, m_Kusa[Loop].pos.y, m_Kusa[Loop].pos.z);//X���f���̕��s�ړ��֐�
		D3DXMatrixMultiply(&m_Kusa[Loop].mtxworld, &m_Kusa[Loop].mtxworld, &m_Kusa[Loop].mtxworldT);//����


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
		D3DXMatrixMultiply(&m_Kusa[Loop].mtxworld, &matCurrentView, &m_Kusa[Loop].mtxworld);
		///////////////////////�r���{�[�h����///////////////////////////////////////////
	}
}

//==============
// �@�`��֐�
//==============
void Kusa::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < KUSA_NUM; Loop++)//�\���̂̐������� 
	{
		//�A���t�@�u�����f�B���O
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//�A���t�@�u�����h�J�n
		pDevice->SetRenderState(D3DRS_ALPHAREF, 96);//�e�N�X�`���̔w�i�𓧖���
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//�e�N�X�`���̔w�i�𓧖���
		//�A���t�@�u�����f�B���O

		pDevice->SetTransform(D3DTS_WORLD, &m_Kusa[Loop].mtxworld);

		pDevice->SetStreamSource(0, m_Kusa[Loop].pVB, 0, sizeof(CUSTOMVERTEX));
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

