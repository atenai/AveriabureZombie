#pragma once
//=============================================================================
//  
// �Ƃ̕`��
//
//=============================================================================

#ifndef _IE_H_
#define _IE_H_
class Ie
{
public:
	Ie();
	~Ie();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	//�Ƃ̍��W�������Ă���
	void SetPos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	//�Ƃ̍��W�𑗂�
	D3DXVECTOR3 GetPos()
	{
		return IePos;
	}
	//�Ƃ̍ŏ����_�𑗂�
	D3DXVECTOR3 GetIeMin() 
	{
		return Min;
	}
	//�Ƃ̍ő咸�_�𑗂�
	D3DXVECTOR3 GetIeMax()
	{
		return Max;
	}

private:
//*****************************************************************************
// �����o�ϐ�
//*****************************************************************************

	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//���[���h�s��
	D3DXMATRIX m_mtxWorld;

	//�X�P�[��
	D3DXMATRIX m_mtxWorldS;//�g��p�ϐ�

	//�g�����X���[�V����
	D3DXMATRIX m_mtxWorldT;//�ړ��p�ϐ�
	D3DXVECTOR3 IePos;//�Ƃ̍��W

	//�o�E���f�B���O�{�b�N�X(ABB)
	D3DXVECTOR3 Min;//�ŏ����_
	D3DXVECTOR3 Max;//�ő咸�_
};
#endif // _IE_H_
