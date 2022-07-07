#pragma once
//=============================================================================
//  
// �񕜃A�C�e���̕`��
//
//=============================================================================

#ifndef _RECOVERYITEM_H_
#define _RECOVERYITEM_H_

#define RECOVERYITEM_NUM (3)//�񕜃A�C�e���̐�
#define HP_NUM 64//HP�ϓ���

class RecoveryItem
{
public:
	RecoveryItem();
	~RecoveryItem();
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
		return m_RecoveryItem[Loop].pos.x;
	}
	//�A�C�e���̈ʒu���W���lY�𑗂�
	float GetPosY(int Loop)
	{
		return m_RecoveryItem[Loop].pos.y;
	}
	//�A�C�e���̈ʒu���W���lZ�𑗂�
	float GetPosZ(int Loop)
	{
		return m_RecoveryItem[Loop].pos.z;
	}

	//�A�C�e���̕`���Ԃ������Ă���
	void SetRecoveryItemDraw(int kazu, bool draw)
	{
		m_RecoveryItem[kazu].Draw = draw;
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

	ITEM_DATA m_RecoveryItem[RECOVERYITEM_NUM];//�\���̂ŃA�C�e����������邩��錾


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

#endif // _RECOVERYITEM_H_