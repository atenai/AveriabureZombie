//=============================================================================
//
// UAV [UAV.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "UAV.h"
#include "Renderer.h"



UAV::UAV()
{
}


UAV::~UAV()
{
}

//==============
//  �������֐�
//==============
void UAV::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/UAV8.x", D3DXMESH_SYSTEMMEM,
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
void UAV::Uninit(void)
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
void UAV::Update(void)
{

	////////////////////////////�������ړ�///////////////////////////////////
	//������������ꍇ�̓J������������Ȃ��Ƃ����Ȃ��I
	m_zmovespeed += 0.5f;//X���f���̉��ɐi�ރX�s�[�h

	if (m_okuidou >= 330) {//���ړ��͈̔͐���
		m_zmovespeed = 0;
	}

	m_okuidou = m_okuidou + m_zmovespeed;//���ړ��v�Z
	m_zmovespeed = 0;//���ړ��̃X�s�[�h��������
	////////////////////////////�������ړ�///////////////////////////////////



	//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
	D3DXMatrixIdentity(&m_mtxWorld);//���������邽�߂̏�����

	//x���f�� 05
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//����

	D3DXMatrixTranslation(&m_mtxWorld, 0.0f, 7.0f, m_okuidou);//X���f���̕��s�ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorld);//����


}

//==============
// �@�`��֐�
//==============
void UAV::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	//x���f�� 05
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//Direct3D�ɂ�����u���b�V���v�́u�����_�����O�v�́u�}�e���A���v����ɂ��Ă��܂��B
	//Direct3D�ɂ�����u�I�u�W�F�N�g�f�[�^�v�́u�`��v�́u�\�ʓI�������v����ɂ��Ă��܂��B
	for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
	{
		pDevice->SetMaterial(&pMeshMaterials[i]);//�}�e���A����ݒ肷��
		pDevice->SetTexture(0, pMeshTextures[i]);//�e�N�X�`����ݒ肷��
		pMesh->DrawSubset(i);//�����_�����O����
	}

}
