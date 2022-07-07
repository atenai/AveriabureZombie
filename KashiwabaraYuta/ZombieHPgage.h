#pragma once
//=============================================================================
//  
// �]���rHP�Q�[�W�̕`��
//
//=============================================================================

#ifndef _ZOMBIEHPGAGE_H_
#define _ZOMBIEHPGAGE_H_
#include "Zombie.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

class ZombieHPgage
{
public:
	ZombieHPgage();
	~ZombieHPgage();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	//�]���rHP�Q�[�W�̍��W�������Ă���
	void SetPos(int su, float x, float y, float z)
	{
		m_ZombieHP[su].ZombiePos.x = x;//x�̒l��EnemyPos.x�ɓ����
		m_ZombieHP[su].ZombiePos.y = y;//y�̒l��EnemyPos.y�ɓ����
		m_ZombieHP[su].ZombiePos.z = z;//z�̒l��EnemyPos.z�ɓ����
	}//�]���rHP�Q�[�W�̎c��������Ă���
	void SetNokoriZombieHP(int su, float x)
	{
		m_ZombieHP[su].Scale = x / 100;
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

	typedef struct  //�\���̂̒�`
	{
		CUSTOMVERTEX vertices[4];//�\���̂̍\����
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		float Scale;//����̑傫��
		D3DXVECTOR3 ZombiePos;
	}ZOMBIEHP;

	ZOMBIEHP m_ZombieHP[ZOMBIE_NUM];

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�

};
#endif // _HPGAGE_H_

