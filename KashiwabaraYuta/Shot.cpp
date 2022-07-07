//=============================================================================
//
// �e [Shot.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Shot.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


Shot::Shot()
{
}


Shot::~Shot()
{
}

//==============
//  �������֐�
//==============
void Shot::Init(void)
{
	//�T�E���h
	oto0 = 0;//���y�p�ϐ�������
	oto1 = 0;//���y�p�ϐ�������

	num = 0;//�e�̒e����

	Shot_UI = SHOT_NUM;//�e���\���̏�����

	//�e�S�Ă��\���ɂ���
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		m_Shot[Loop].Draw = false;
		m_Shot[Loop].AtariHantei = false;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Tama.x", D3DXMESH_SYSTEMMEM,
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
void Shot::Uninit(void)
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
void Shot::Update(void)
{

	//�X�y�[�X�L�[�������`��
	if (GetKeyboardPress(DIK_SPACE) && num < SHOT_NUM)
	{

		//�T�E���h
		oto0++;
		if (oto0 > 0)
		{
			PlaySound(SOUND_LABEL_BGM002);//���y���Ȃ炷ok
		}
		oto0 = 0;
		//�T�E���h
		//�T�E���h
		oto1++;
		if (oto1 > 0)
		{
			PlaySound(SOUND_LABEL_BGM010);//���y���Ȃ炷ok
		}
		oto1 = 0;
		//�T�E���h

		//�v���C���[�̐��ʃx�N�g���������Ă��鏈��
		m_Shot[num].muki.x = PlayerFront.x;
		m_Shot[num].muki.y = PlayerFront.y;
		m_Shot[num].muki.z = PlayerFront.z;
		//�v���C���[�̐��ʃx�N�g���������Ă��鏈��

		m_Shot[num].ShotPos.x = PlayerPos.x;//num�Ԗڂ̒e�̍��W�Ƀv���C���[�̍��W������
		m_Shot[num].ShotPos.y = PlayerPos.y;//num�Ԗڂ̒e�̍��W�Ƀv���C���[�̍��W������
		m_Shot[num].ShotPos.z = PlayerPos.z;//num�Ԗڂ̒e�̍��W�Ƀv���C���[�̍��W������
		m_Shot[num].Draw = true;//num�Ԗڂ̒e��`�悷��
		m_Shot[num].AtariHantei = true;//num�Ԗڂ̒e�̂����蔻���ON
		num++;//num��+1����
		Shot_UI--;//TamaUI��-1����
	}

	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		//�\��������`�悷��
		if (m_Shot[Loop].Draw == true)
		{
			//�e��z���x�N�g����*1.0f�������̂�e�̍��W�ɂ���
			m_Shot[Loop].ShotPos = m_Shot[Loop].ShotPos + m_Shot[Loop].muki * 1.0f;


			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_Shot[Loop].mtxworld);//���������邽�߂̏�����

			//x���f�� 05
			D3DXMatrixScaling(&m_Shot[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
			D3DXMatrixMultiply(&m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworldS);//����


			D3DXMatrixTranslation(&m_Shot[Loop].mtxworldT, m_Shot[Loop].ShotPos.x, m_Shot[Loop].ShotPos.y , m_Shot[Loop].ShotPos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworld, &m_Shot[Loop].mtxworldT);//����
		}
	}

}

//==============
// �@�`��֐�
//==============
void Shot::Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		//�\��������`�悷��
		if (m_Shot[Loop].Draw == true)
		{
			//
			pDevice->SetTransform(D3DTS_WORLD, &m_Shot[Loop].mtxworld);

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

void Shot::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	//�T�E���h
	oto0 = 0;//���y�p�ϐ�������
	oto1 = 0;//���y�p�ϐ�������

	num = 0;//�e�̒e����

	Shot_UI = SHOT_NUM;//�e���\���̏�����

	//�e�S�Ă��\���ɂ���
	for (int Loop = 0; Loop < SHOT_NUM; Loop++)
	{
		m_Shot[Loop].Draw = false;
		m_Shot[Loop].AtariHantei = false;
	}
}
