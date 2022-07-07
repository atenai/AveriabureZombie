#pragma once
//=============================================================================
//  
// �v���C���[�e�̕`��
//
//=============================================================================

#ifndef _PLAYERKAGE_H_
#define _PLAYERKAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�


class PlayerKage
{
public:
	PlayerKage();
	~PlayerKage();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw();//�`�揈��
	void Uninit(void);//�I������
	//�v���C���[�̍��W�������Ă���
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}
private:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct  //�\���̂̒�`
	{
		FLOAT x, y, z;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;//�e�N�X�`���\��t�����W
	}CUSTOMVERTEX;

	CUSTOMVERTEX vertices[4];//�\���̂̍\����

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�

	D3DXVECTOR3 PlayerPos;//�v���C���[�̍��W

	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxworldT;


	D3DCOLOR m_color = D3DCOLOR_RGBA(100, 100, 100, 100);

};
#endif // _PLAYERKAGE_H_
