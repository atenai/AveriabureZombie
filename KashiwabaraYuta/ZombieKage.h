#pragma once
//=============================================================================
//  
// �]���r�̉e�̕`��
//
//=============================================================================

#ifndef _ZOMBIEKAGE_H_
#define _ZOMBIEKAGE_H_
#include "Zombie.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

class ZombieKage
{
public:
	ZombieKage();
	~ZombieKage();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	//�]���r�e�̍��W�������Ă���
	void SetPos(int su, float x, float y, float z)
	{
		m_ZombieKage[su].ZombiePos.x = x;//x�̒l��EnemyPos.x�ɓ����
		m_ZombieKage[su].ZombiePos.y = y;//y�̒l��EnemyPos.y�ɓ����
		m_ZombieKage[su].ZombiePos.z = z;//z�̒l��EnemyPos.z�ɓ����
	}
	//�]���r�e�̕`���Ԃ������Ă���
	void SetZombieKageDraw(int su, bool draw)
	{
		m_ZombieKage[su].Draw = draw;
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

	typedef struct  //�\���̂̒�`
	{
		CUSTOMVERTEX vertices[4];//�\���̂̍\����
		D3DXVECTOR3 ZombiePos;
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		bool Draw;//�{���x�̕\���E��\��
	}ZOMBIEKAGE;

	ZOMBIEKAGE m_ZombieKage[ZOMBIE_NUM];
	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�



};
#endif // _ENEMYKAGE_H_
