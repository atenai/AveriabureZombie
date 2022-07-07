#pragma once
//=============================================================================
//  
// UAV�̕`��
//
//=============================================================================

#ifndef _UAV_H_
#define _UAV_H_
class UAV
{
public:
	UAV();
	~UAV();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
private:
//*****************************************************************************
// �����o�ϐ�
//*****************************************************************************

	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	//x���f��
	D3DXMATRIX m_mtxWorld;

	//�X�P�[��
	D3DXMATRIX m_mtxWorldS;//�g��p�ϐ�

	//�g�����X���[�V����
	D3DXMATRIX m_mtxWorldT;//�ړ��p�ϐ�
	float m_okuidou = 0.0f;//���ړ��p���l//X���f����Z���W
	float m_zmovespeed = 0.0f;//X���f����z�X�s�[�h
};
#endif // _UAV_H_
