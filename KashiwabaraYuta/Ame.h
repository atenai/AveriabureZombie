#pragma once
//=============================================================================
//  
// �J�̕`��
//
//=============================================================================

#ifndef _AME_H_
#define _AME_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

#define AME_NUM 100

//*****************************************************************************
// ���N���X
//*****************************************************************************
//�J�N���X
class Ame
{
public:
	Ame();//�R���X�g���N�^
	~Ame();//�f�X�g���N�^
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������

	void AmesetTimer(DWORD time);
	BOOL AmeisTimerGoal();
private:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	struct CUSTOMVERTEX //�\���̂̒�`
	{
		FLOAT x, y, z;
		DWORD color;
		D3DXVECTOR2 texcoord;//�e�N�X�`���\��t�����W
	};

	typedef struct {
		D3DXVECTOR3 pos;//���W
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		BOOL used;//�g�p���������t���O
	}AME_DATA;

	AME_DATA m_Ame[AME_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//�|���S���\���p�ϐ�
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�

	//�J�p
	DWORD Ameg_goaltimes;

};
#endif // _AME_H_
