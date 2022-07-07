#pragma once
//=============================================================================
//  
// �J����
//    
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
//*****************************************************************************
// ���N���X
//*****************************************************************************
//�J�����N���X
class Camera 
{
public:
	Camera();//�R���X�g���N�^
	~Camera();//�f�X�g���N�^
	void Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����

	//�v���C���[�̃��[���h�s��������Ă���
	void SetPlayerMatrix(D3DXMATRIX Mat) 
	{
		PlayerMatrix = Mat;
	}

	bool GetTPS()
	{
		return TPS;
	}

private:

	//�����Y
	D3DXMATRIX m_mtxProj;//�v���W�F�N�V�����s��

	//�J����
	D3DXMATRIX m_mtxView;//�r���[�s��
	D3DXMATRIX m_mtxWorld;

	D3DXVECTOR3 m_eye_pos;//�J�������W//eye
	D3DXVECTOR3 m_at_pos;//���_���W//at
	D3DXVECTOR3 m_up_pos;//��������W//up

	bool TPS = false;

	D3DXMATRIX PlayerMatrix;//�v���C���[�̃��[���h�s��

	//�T�E���h
	//int oto0;//���y�p�ϐ�
	int oto1;//���y�p�ϐ�
};


#endif // _CAMERA_H_


