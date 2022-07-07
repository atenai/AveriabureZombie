//=============================================================================
//
// �� [Ie.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Ie.h"
#include "Renderer.h"



Ie::Ie()
{
}


Ie::~Ie()
{
}

//==============
//  �������֐�
//==============
void Ie::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/house.x", D3DXMESH_SYSTEMMEM,
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
				/*d3dxMaterials[i].pTextureFilename*/"./data/texture/house.bmp",
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//�������̊J��

	//�o�E���f�B���O�{�b�N�X(ABB)
	//�Ƃ̋��E�{�b�N�X�̍쐬
	//.x���f���̃��b�V���������ƂɎ����I�Ƀo�E���f�B���O�{�b�N�X���쐬���Ă����
	DWORD numv, stride;
	LPDIRECT3DVERTEXBUFFER9 pvb;
	BYTE *pvertices;
	HRESULT hr;
	D3DXVECTOR3 lminv(0.0f,0.0f,0.0f), lmaxv(0.0f, 0.0f, 0.0f);

	numv = pMesh->GetNumVertices();//���_�������߂�
	stride = D3DXGetFVFVertexSize(pMesh->GetFVF());
	hr = pMesh->GetVertexBuffer(&pvb);//���_�o�b�t�@�擾

	hr = pvb->Lock(0, 0, (VOID**)&pvertices, 0);//���_�o�b�t�@���b�N

	hr = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv, stride, &lminv, &lmaxv);

	Min = IePos + lminv;//�`��Ώۂ̍��W+lminv�������̂��r���f�B���O�{�b�N�X��minv�ɓ����
	Max = IePos + lmaxv;//�`��Ώۂ̍��W+lmaxv�������̂��r���f�B���O�{�b�N�X��maxv�ɓ����
	pvb->Unlock();//���_�o�b�t�@�A�����b�N
	//�o�E���f�B���O�{�b�N�X(ABB)


	//IeEnemyPos(IePos);//�Ƃ̍��W�𑗂�
	//IeEnemyMin(minv);//�Ƃ̃}�C�i�X��x�Ey�Ez��3���_���W���G�l�~�[�ɑ���
	//IeEnemyMax(maxv);//�Ƃ̃v���X��x�Ey�Ez��3���_���W���G�l�~�[�ɑ���

	//IeZombiePos(IePos);//�Ƃ̍��W�𑗂�
	//IeZombieMin(minv);//�Ƃ̃}�C�i�X��x�Ey�Ez��3���_���W���G�l�~�[�ɑ���
	//IeZombieMax(maxv);//�Ƃ̃v���X��x�Ey�Ez��3���_���W���G�l�~�[�ɑ���

}

//==============
//  �I���֐�
//==============
void Ie::Uninit(void)
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
void Ie::Update(void)
{

	//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
	D3DXMatrixIdentity(&m_mtxWorld);//���������邽�߂̏�����

	//�n�� 01
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//����

	D3DXMatrixTranslation(&m_mtxWorldT, IePos.x, IePos.y, IePos.z);//X���f���̕��s�ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);//����
}

//==============
// �@�`��֐�
//==============
void Ie::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

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
