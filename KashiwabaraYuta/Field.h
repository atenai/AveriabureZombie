#pragma once
//=============================================================================
//  
// �t�B�[���h�̕`��
//
//=============================================================================

#ifndef _FIELD_H_
#define _FIELD_H_

//*****************************************************************************
// ���N���X
//*****************************************************************************
//�t�B�[���h�N���X
class Field
{
public:
	Field();//�R���X�g���N�^
	~Field();//�f�X�g���N�^
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//���[���h�s��
	D3DXMATRIX mtxWorld;
	//�X�P�[��
	D3DXMATRIX mtxWorldS;//�g��p�ϐ�
	//�g�����X���[�V����
	D3DXMATRIX mtxWorldT;//�ړ��p�ϐ�
	D3DXVECTOR3 pos;//���W
};

//*****************************************************************************
// �h���N���X
//*****************************************************************************
//�n�ʃN���X
class Zimen:public Field
{
public:
	Zimen();//�R���X�g���N�^
	~Zimen();//�f�X�g���N�^
	void Init(void);//����������
};
//�X�J�C�h�[���N���X
class SkyDome:public Field
{
public:
	SkyDome();//�R���X�g���N�^
	~SkyDome();//�f�X�g���N�^
	void Init(void);//����������
};

#endif // _FIELD_H_


