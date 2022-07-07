#pragma once
//=============================================================================
//  
// �{���x�̕`��
//
//=============================================================================

#ifndef _BONBE_H_
#define _BONBE_H_
//*****************************************************************************
// ���N���X
//*****************************************************************************
//�{���x�N���X
class Bonbe
{
public:
	Bonbe();//�R���X�g���N�^
	~Bonbe();//�f�X�g���N�^
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������

	//void SetPos(float setpos)//���W������
	//{
	//	pos = setpos;
	//}

	//float GetPos()//���W������Ă���
	//{
	//	return pos;
	//}

	D3DXVECTOR3 SetBonbePos(float x, float y, float z)//���W������
	{
		BonbePos.x = x;
		BonbePos.y = y;
		BonbePos.z = z;

		return BonbePos;
	}
private:
	
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//���[���h�s��
	D3DXMATRIX mtxWorld;
	//�X�P�[��
	D3DXMATRIX mtxWorldS;//�g��p�ϐ�
	//�g�����X���[�V����
	D3DXMATRIX mtxWorldT;//�ړ��p�ϐ�

//*****************************************************************************
// �����o�ϐ�
//*****************************************************************************
	//float pos = 0.0f;//���W
	D3DXVECTOR3 BonbePos;
};
#endif // _BONBE_H_
