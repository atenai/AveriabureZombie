//=============================================================================
//
// �񕜃A�C�e�� [RecoveryItem.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "RecoveryItem.h"
#include "Renderer.h"



RecoveryItem::RecoveryItem()
{
}


RecoveryItem::~RecoveryItem()
{
}

//==============
//  �������֐�
//==============
void RecoveryItem::Init(void)
{
	//�\���̂ō�����{���x�̈ʒu���W���w��

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
		m_RecoveryItem[Loop].pos.y = 0;
		m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
		if (m_RecoveryItem[Loop].pos.x == 0 && m_RecoveryItem[Loop].pos.z == 0)
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_RecoveryItem[Loop].pos.z <= -51 || 51 <= m_RecoveryItem[Loop].pos.z || m_RecoveryItem[Loop].pos.x <= -51 || 51 <= m_RecoveryItem[Loop].pos.x)
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (4 < m_RecoveryItem[Loop].pos.z  && m_RecoveryItem[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_RecoveryItem[Loop].pos.x && m_RecoveryItem[Loop].pos.x < -4)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
		}

		m_RecoveryItem[Loop].Draw = true;//�{���x���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	}


	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/FirstAidKit3.x", D3DXMESH_SYSTEMMEM,
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
				d3dxMaterials[i].pTextureFilename/*"./data/texture/Ground.bmp"*/,//�e�N�X�`�����w��
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
void RecoveryItem::Uninit(void)
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
void RecoveryItem::Update(void)
{

	Ykaitenidou = Ykaitenidou + 0.05f;

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_RecoveryItem[Loop].Draw == true)//�{���x�̕\���E��\�����Ǘ�����
		{

			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_RecoveryItem[Loop].mtxworld);//���������邽�߂̏�����

			D3DXMatrixScaling(&m_RecoveryItem[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
			D3DXMatrixMultiply(&m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworldS);//����

			D3DXMatrixRotationY(&m_RecoveryItem[Loop].mtxworldR, Ykaitenidou);//X���f����Y��]�֐�
			D3DXMatrixMultiply(&m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworldR);//����

			D3DXMatrixTranslation(&m_RecoveryItem[Loop].mtxworldT, m_RecoveryItem[Loop].pos.x, m_RecoveryItem[Loop].pos.y, m_RecoveryItem[Loop].pos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworld, &m_RecoveryItem[Loop].mtxworldT);//����
		}
	}
}

//==============
// �@�`��֐�
//==============
void RecoveryItem::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_RecoveryItem[Loop].Draw == true)//�{���x�̕\���E��\�����Ǘ�����
		{
			
			pDevice->SetTransform(D3DTS_WORLD, &m_RecoveryItem[Loop].mtxworld);

			//Direct3D�ɂ�����u���b�V���v�́u�����_�����O�v�́u�}�e���A���v����ɂ��Ă��܂��B
			//Direct3D�ɂ�����u�I�u�W�F�N�g�f�[�^�v�́u�`��v�́u�\�ʓI�������v����ɂ��Ă��܂��B
			for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
			{
				pDevice->SetMaterial(&pMeshMaterials[i]);//�}�e���A����ݒ肷��
				pDevice->SetTexture(0, pMeshTextures[i]);//�e�N�X�`����ݒ肷��
				pMesh->DrawSubset(i);//�����_�����O����
			}
		}
	}
}

void RecoveryItem::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{

	for (int Loop = 0; Loop < RECOVERYITEM_NUM; Loop++)//�\���̂̐������� 
	{
		m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
		m_RecoveryItem[Loop].pos.y = 0;
		m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
		if (m_RecoveryItem[Loop].pos.x == 0 && m_RecoveryItem[Loop].pos.z == 0)
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_RecoveryItem[Loop].pos.z <= -51 || 51 <= m_RecoveryItem[Loop].pos.z || m_RecoveryItem[Loop].pos.x <= -51 || 51 <= m_RecoveryItem[Loop].pos.x)
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (4 < m_RecoveryItem[Loop].pos.z  && m_RecoveryItem[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_RecoveryItem[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_RecoveryItem[Loop].pos.x && m_RecoveryItem[Loop].pos.x < -4)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_RecoveryItem[Loop].pos.x = -50 + rand() % 100;
		}

		m_RecoveryItem[Loop].Draw = true;//�{���x���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	}


}