//=============================================================================
//
// ���� [Bakuhu.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Bakuhu.h"
#include "Renderer.h"


Bakuhu::Bakuhu()
{
}


Bakuhu::~Bakuhu()
{
}

//==============
//  �������֐�
//==============
void Bakuhu::Init(void)
{

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�n���̐������� 
	{
		m_Bakuhu[Loop].Draw = false;//������\��
		m_Bakuhu[Loop].Timer = 0.0f;
	}

	

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/bakuha.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];//�}�e���A���̃������̈���}�e���A���̐������m�ۂ�pMeshMaterials�ɓ����
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];//�e�N�X�`���ɕK�v�ȃ������̈���m�ۂ�pMeshTextures�ɓ����

														   //��Ŋm�ۂ����������̈�ɒ��g�����Ă���
	for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;//�}�e���A���f�[�^������
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;//Ambient��Diffuse�Ɠ����l�ɂ���

															  //pTextureFilename�����ƂɃe�N�X�`���I�u�W�F�N�g�̐���
		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/bakuha.bmp",
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//�������̊J��

}

//==============
//  �I���֐�
//==============
void Bakuhu::Uninit(void)
{

	if (pMesh != NULL)
	{
		pMesh->Release();//����ŊJ�������
		pMesh = NULL;//�A�h���X���c���Ă���̂�NULL�ŏ㏑��
	}

}

//==============
// �@�X�V�֐�
//==============
void Bakuhu::Update(void)
{
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�n���̐������� 
	{
		
		if (m_Bakuhu[Loop].Draw == true)
		{
			m_Bakuhu[Loop].Timer = m_Bakuhu[Loop].Timer + 23.0f;
			
			if (m_Bakuhu[Loop].Timer < 2000)//Loop�Ԗ�2�b�̂�
			{
				float pt = m_Bakuhu[Loop].Timer;//0�b����2�b�܂ł�����

				//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
				D3DXMatrixIdentity(&m_Bakuhu[Loop].mtxworld);//���������邽�߂̏�����

				//�n�� 01
				D3DXMatrixScaling(&m_Bakuhu[Loop].mtxworldS, 1.0f + pt / 100.0f, 1.0f + pt / 100.0f, 1.0f + pt / 100.0f);//X���f���̊g��֐�
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldS);//����

				D3DXMatrixRotationY(&m_Bakuhu[Loop].mtxworldR, (float)timeGetTime() / 1000);//Y��]�֐�
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldR);//����

				D3DXMatrixTranslation(&m_Bakuhu[Loop].mtxworldT, m_Bakuhu[Loop].Pos.x, m_Bakuhu[Loop].Pos.y - 1.0f, m_Bakuhu[Loop].Pos.z);//X���f���̕��s�ړ��֐�
				D3DXMatrixMultiply(&m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworld, &m_Bakuhu[Loop].mtxworldT);//����


			}

			if (2000 < m_Bakuhu[Loop].Timer)//Loop�Ԗ�2�b��
			{
				m_Bakuhu[Loop].Draw = false;
			}

		}
	}
}

//==============
// �@�`��֐�
//==============
void Bakuhu::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�n���̐������� 
	{
		if (m_Bakuhu[Loop].Draw == true)
		{
			if (m_Bakuhu[Loop].Timer < 2000)//Loop�Ԗ�2�b�̂�
			{
				//�A���t�@�u�����f�B���O
				//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h�J�n
				//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
				//pDevice->SetRenderState(D3DRS_BLENDFACTOR, 0x88888888);

				//�n�� 01
				pDevice->SetTransform(D3DTS_WORLD, &m_Bakuhu[Loop].mtxworld);

				//Direct3D�ɂ�����u���b�V���v�́u�����_�����O�v�́u�}�e���A���v����ɂ��Ă��܂��B
				//Direct3D�ɂ�����u�I�u�W�F�N�g�f�[�^�v�́u�`��v�́u�\�ʓI�������v����ɂ��Ă��܂��B
				for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
				{
					pDevice->SetMaterial(&pMeshMaterials[i]);//�}�e���A����ݒ肷��
					pDevice->SetTexture(0, pMeshTextures[i]);//�e�N�X�`����ݒ肷��
					pMesh->DrawSubset(i);//�����_�����O����
				}

				//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//�A���t�@�u�����h�I��
			}

			if (2000 < m_Bakuhu[Loop].Timer)//Loop�Ԗ�2�b��
			{
				m_Bakuhu[Loop].Draw = false;
			}
		}
	}
}



void Bakuhu::ResetParameters(void)
{
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		m_Bakuhu[Loop].Draw = false;//�n���̔�\��
		m_Bakuhu[Loop].Timer = 0.0f;
	}
}

