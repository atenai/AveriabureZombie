#pragma once
//=============================================================================
//  
// �A�C�e���̕`��
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#define ITEM_NUM (6)//�A�C�e���̐�

class Item
{
public:
	Item();
	~Item();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g

	int GetLoop(int Loop)
	{
		return Loop;
	}
	//�A�C�e���̈ʒu���W���lX�𑗂�
	float GetPosX(int Loop)
	{
		return m_Item[Loop].pos.x;
	}
	//�A�C�e���̈ʒu���W���lY�𑗂�
	float GetPosY(int Loop)
	{
		return m_Item[Loop].pos.y;
	}
	//�A�C�e���̈ʒu���W���lZ�𑗂�
	float GetPosZ(int Loop)
	{
		return m_Item[Loop].pos.z;
	}

	//�A�C�e���̕`���Ԃ������Ă���
	void SetItemDraw(int kazu, bool draw)
	{
		m_Item[kazu].Draw = draw;
	}

private:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct
	{
		D3DXVECTOR3 pos;//���W
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		bool Draw;//�{���x�̕\���E��\��
		
	}ITEM_DATA;

	ITEM_DATA m_Item[ITEM_NUM];//�\���̂ŃA�C�e����������邩��錾


	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	float Ykaitenidou = 0.0f;

};

#endif // _ITEM_H_

