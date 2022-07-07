#pragma once
//=============================================================================
//  
// HP�Q�[�W�̕`��
//
//=============================================================================
#ifndef _HPGAGE_H_
#define _HPGAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

class EnemyHPgage
{
public:
	EnemyHPgage();
	~EnemyHPgage();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	//�G�l�~�[�̍��W�������Ă���
	void SetEnemyPos(D3DXVECTOR3 pos)
	{
		EnemyPos = pos;
	}
	//�G�l�~�[HP�Q�[�W�̎c�ʂ������Ă���
	void SetNokoriEnemyHP(float x)
	{
		Scale = x / 100.0f;
	}
private:
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

	CUSTOMVERTEX vertices[4];//�\���̂̍\����

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�

	D3DXVECTOR3 EnemyPos;

	D3DXMATRIX mtxworld;
	D3DXMATRIX mtxworldT;

	float Scale = 0.0f;//����̑傫��
};
#endif // _HPGAGE_H_
