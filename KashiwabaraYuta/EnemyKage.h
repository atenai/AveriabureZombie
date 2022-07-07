#pragma once
//=============================================================================
//  
// �G�l�~�[�e�̕`��
//
//=============================================================================
#ifndef _ENEMYKAGE_H_
#define _ENEMYKAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

class EnemyKage
{
public:
	EnemyKage();
	~EnemyKage();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	//
	void SetEnemyPos(D3DXVECTOR3 pos)
	{
		EnemyPos = pos;
	}

	void SetEnemyKageDraw(bool draw)
	{
		KageDraw = draw;
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

	D3DXVECTOR3 EnemyPos;

	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxworldT;

	bool KageDraw = true;


};
#endif // _ENEMYKAGE_H_
