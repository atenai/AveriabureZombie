#pragma once
//=============================================================================
//  
// ���̕`��
//
//=============================================================================

#ifndef _KUSA_H_
#define _KUSA_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

#define KUSA_NUM 100//���̐����w��

//*****************************************************************************
// ���N���X
//*****************************************************************************
//���N���X
class Kusa
{
public:
	Kusa();//�R���X�g���N�^
	~Kusa();//�f�X�g���N�^
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������

//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct  //�\���̂̒�`
	{
		FLOAT x, y, z;
		DWORD color;
		D3DXVECTOR2 texcoord;//�e�N�X�`���\��t�����W
	}CUSTOMVERTEX;


	typedef struct {
		D3DXVECTOR3 pos;//���W
		float Scale;//����̑傫��
		CUSTOMVERTEX vertices[6];//�\���̂̍\����
		VOID* pVertices;
		LPDIRECT3DVERTEXBUFFER9 pVB;
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
	}KUSA_DATA;

	KUSA_DATA m_Kusa[KUSA_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�
};

//*****************************************************************************
// �h���N���X
//*****************************************************************************
//��1�N���X
class Kusa1:public Kusa
{
public:
	Kusa1();//�R���X�g���N�^
	~Kusa1();//�f�X�g���N�^
	void Init(void);//����������
private:

};
//��2�N���X
class Kusa2 :public Kusa
{
public:
	Kusa2();//�R���X�g���N�^
	~Kusa2();//�f�X�g���N�^
	void Init(void);//����������
private:

};
//��3�N���X
class Kusa3 :public Kusa
{
public:
	Kusa3();//�R���X�g���N�^
	~Kusa3();//�f�X�g���N�^
	void Init(void);//����������
private:

};
//�؃N���X
class Tree :public Kusa
{
public:
	Tree();//�R���X�g���N�^
	~Tree();//�f�X�g���N�^
	void Init(void);//����������
private:

};


#endif // _KUSA_H_

