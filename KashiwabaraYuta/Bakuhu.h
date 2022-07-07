#pragma once
//=============================================================================
//  
// �����̕`��
//
//=============================================================================

#ifndef _BAKUHU_H_
#define _BAKUHU_H_
#include "Zirai.h"
class Bakuhu
{
public:
	Bakuhu();
	~Bakuhu();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g

	//�n���̍��W�������Ă���
	void SetZiraiPos(int num, float x, float y, float z)
	{
		m_Bakuhu[num].Pos.x = x;
		m_Bakuhu[num].Pos.y = y;
		m_Bakuhu[num].Pos.z = z;
	}

	//�����̕`���Ԃ������Ă���
	void SetBakuhuDraw(int num, bool draw)
	{
		m_Bakuhu[num].Draw = draw;
	}

private:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct
	{
		D3DXVECTOR3 Pos;//���W
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		bool Draw = false;//�\���E��\��
		float Timer = 0.0f;
	}BAKUHU_DATA;

	BAKUHU_DATA m_Bakuhu[ZIRAI_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;


};

#endif // _BAKUHU_H_