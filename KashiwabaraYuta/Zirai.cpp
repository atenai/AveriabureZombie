//=============================================================================
//
// �n�� [Zirai.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Zirai.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include"sound.h"

Zirai::Zirai()
{
}


Zirai::~Zirai()
{
}

//==============
//  �������֐�
//==============
void Zirai::Init(void)
{
	//�T�E���h
	m_count = 0;//���y�p�ϐ�������

	m_num = 0;//�n�����̏�����
	m_Zirai_UI = ZIRAI_NUM;//�n�����\���̏�����

	//�X�y�[�X�L�[�������ꂽ�玞�̕\���E��\�����Ǘ�
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zirai[Loop].Draw = false;//�n����\��
		m_Zirai[Loop].AtariHantei = false;//�n���̂����蔻���OFF
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Zirai4.x", D3DXMESH_SYSTEMMEM,
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
				d3dxMaterials[i].pTextureFilename,
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
void Zirai::Uninit(void)
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
void Zirai::Update(void)
{


	//�X�y�[�X�L�[����������firenum��120�b�ȏ�̎��e�̕`��
	if (GetKeyboardRelease(DIK_M) && m_ZiraiTime >= 10 && m_num < ZIRAI_NUM)
	{
		//�T�E���h
		m_count++;
		if (m_count > 0)
		{
			PlaySound(SOUND_LABEL_BGM011);//���y���Ȃ炷ok
		}
		m_count = 0;
		//�T�E���h

		//�v���C���[�̍��W��n���̍��W�ɂ�����
		m_Zirai[m_num].ZiraiPos.x = PlayerPos.x;
		m_Zirai[m_num].ZiraiPos.y = PlayerPos.y;
		m_Zirai[m_num].ZiraiPos.z = PlayerPos.z;

		m_Zirai[m_num].Draw = true;//�n����`��
		m_Zirai[m_num].AtariHantei = true;//�n���̂����蔻���ON
		m_ZiraiTime = 0;//ZiraiTime��0�ɏ�����
		m_num++;//kazu��+1����
		m_Zirai_UI--;//HixyouziZirai��-1����
	}


	m_ZiraiTime++;//ZiraiTime��+1����


	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_Zirai[Loop].Draw == true)//�n���̕\���E��\�����Ǘ�����
		{

			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_Zirai[Loop].mtxworld);//���������邽�߂̏�����

													 //x���f�� 05
			D3DXMatrixScaling(&m_Zirai[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
			D3DXMatrixMultiply(&m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworldS);//����

			D3DXMatrixTranslation(&m_Zirai[Loop].mtxworldT, m_Zirai[Loop].ZiraiPos.x, m_Zirai[Loop].ZiraiPos.y, m_Zirai[Loop].ZiraiPos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworld, &m_Zirai[Loop].mtxworldT);//����
		}
	}


}

//==============
// �@�`��֐�
//==============
void Zirai::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_Zirai[Loop].Draw == true)//�n���̕\���E��\�����Ǘ�����
		{
			//
			pDevice->SetTransform(D3DTS_WORLD, &m_Zirai[Loop].mtxworld);

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

void Zirai::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	//�T�E���h
	m_count = 0;//���y�p�ϐ�������

	m_num = 0;//�n�����̏�����
	m_Zirai_UI = ZIRAI_NUM;//�n�����\���̏�����

	//�X�y�[�X�L�[�������ꂽ�玞�̕\���E��\�����Ǘ�
	for (int Loop = 0; Loop < ZIRAI_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zirai[Loop].Draw = false;//�n����\��
		m_Zirai[Loop].AtariHantei = false;//�n���̂����蔻���OFF
	}

}