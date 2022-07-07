#pragma once
//=============================================================================
//  
// �n���̕`��
//
//=============================================================================

#ifndef _ZIRAI_H_
#define _ZIRAI_H_

#define ZIRAI_NUM 6//�n���̐�

class Zirai
{
public:
	Zirai();
	~Zirai();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	//�v���C���[�̈ʒu���W���l�������Ă���
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}

	int GetLoop(int Loop)
	{
		return Loop;
	}
	//�n���̈ʒu���W���lX�𑗂�
	float GetPosX(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.x;
	}
	//�n���̈ʒu���W���lY�𑗂�
	float GetPosY(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.y;
	}
	//�n���̈ʒu���W���lZ�𑗂�
	float GetPosZ(int Loop)
	{
		return m_Zirai[Loop].ZiraiPos.z;
	}
	//�n���̕`���Ԃ������Ă���
	void SetZiraiDraw(int kazu, bool draw)
	{
		m_Zirai[kazu].Draw = draw;
	}
	//�n���̂����蔻���Ԃ������Ă���
	void SetZiraiAtariHantei(int kazu, bool draw)
	{
		m_Zirai[kazu].AtariHantei = draw;
	}
	//�n���̕`���Ԃ�Manager.cpp�ɑ���
	bool GetZiraiDraw(int kazu)
	{
		return m_Zirai[kazu].Draw;
	}
	//�n���̂����蔻���Ԃ�Manager.cpp�ɑ���
	bool GetZiraiAtariHantei(int Loop)
	{
		return m_Zirai[Loop].AtariHantei;
	}
	//�n�����𑗂�
	int GetZirai_UI() 
	{
		return m_Zirai_UI;
	}

public:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct
	{
		D3DXVECTOR3 ZiraiPos;//���W
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		bool Draw = false;//�n���̕\���E��\��
		bool AtariHantei = false;//�n���̂����蔻��
	}ZIRAI_DATA;

	ZIRAI_DATA m_Zirai[ZIRAI_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	int m_num = 0;//�n���̒n������
	int m_ZiraiTime = 0;//�n���̃`���[�W����
	int m_Zirai_UI = ZIRAI_NUM;//�n�����\���p�ϐ�

	D3DXVECTOR3 PlayerPos;//�v���C���[�̍��W

	//�T�E���h
	int m_count;//���y�p�ϐ�
};
#endif // _ZIRAI_H_

