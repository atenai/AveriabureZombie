//=============================================================================
//
// �J���� [Camera.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include"Camera.h"
#include"Main.h"
#include"input.h"
#include "Player.h"
#include "Renderer.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//==============
//�R���X�g���N�^
//==============
Camera::Camera()
{
}

//==============
//�f�X�g���N�^
//==============
Camera::~Camera()
{
}

//==============
//  �������֐�
//==============
void Camera::Init(void)
{
	m_up_pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//==============
//  �I���֐�
//==============
void Camera::Uninit(void)
{

}

//==============
// �@�X�V�֐�
//==============
void Camera::Update(void)
{
	//�J����
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
	D3DXMatrixIdentity(&m_mtxWorld);//���������邽�߂̏�����

	if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT))
	{

		//�T�E���h
		if (oto1 == 0)
		{
			PlaySound(SOUND_LABEL_BGM006);//���y���Ȃ炷ok
		}
		oto1++;//2�x�ڂ̉��y��炳�Ȃ�
		//�T�E���h

		TPS = true;//���z���J����
	}
	else
	{
		oto1 = 0;//���y��������

		TPS = false;//�ʏ�J����
	}

	//�ʏ�J����
	if (TPS == false)
	{

		//�J������l�Ԃ̌��ɔz�u�B�����͐l�Ԃ̕��������悤�ɂ���
		D3DXVECTOR3 eyemove(0.0f, 3.0f, -6.0f);//�J�����̈ړ�����W��ݒ�(�v���C���[�̏������)
		//CameraMove = �v���C���[�̈ړ����]�Ȃǂ������܂Ƃ܂����s��(D3DMATRIX)�������Ă���
		D3DXVec3TransformCoord(&eyemove, &eyemove, &PlayerMatrix);//�v���C���[�̍s��𐳖ʂƂ��āAeyemove(�J�����̈ړ�����W)��������(��]���W�ƕ��s�ړ����W���|�����킹��)
		//v = v + PlayerPos;//�v���C���[�̈ړ����W�����łɓ����Ă���̂ł���͂���Ȃ�
		m_eye_pos = eyemove;//�v���C���[����J�����̈ړ�����W�����������W���J�������W�ɓ����
		D3DXVECTOR3 atmove(0.0f, 0.0f, 0.0f);//���_�̈ړ�����W��ݒ�
		D3DXVec3TransformCoord(&atmove, &atmove, &PlayerMatrix);//�v���C���[�̍s��𐳖ʂƂ��āAatmove(���_�̈ړ�����W)��������(��]���W�ƕ��s�ړ����W���|�����킹��)
		//g_at_pos = PlayerPos;//�J�����̎��_���W(at)���v���C���[�̍��W�Ɠ����ɂ���
		m_at_pos = atmove;//�J�����̎��_���W(at)���v���C���[�̍��W�Ɠ����ɂ���
	}
	//���z���J����
	if (TPS == true)
	{
		//�J������l�Ԃ̌��ɔz�u�B�����͐l�Ԃ̕��������悤�ɂ���
		D3DXVECTOR3 eyemove(0.5, 0.25, -1);//�J�����̈ړ�����W��ݒ�(�v���C���[�̏������)
		//CameraMove = �v���C���[�̈ړ����]�Ȃǂ������܂Ƃ܂����s��(D3DMATRIX)�������Ă���
		D3DXVec3TransformCoord(&eyemove, &eyemove, &PlayerMatrix);//�v���C���[�̍s��𐳖ʂƂ��āAeyemove(�J�����̈ړ�����W)��������(��]���W�ƕ��s�ړ����W���|�����킹��)
		//v = v + PlayerPos;//�v���C���[�̈ړ����W�����łɓ����Ă���̂ł���͂���Ȃ�
		m_eye_pos = eyemove;//�v���C���[����J�����̈ړ�����W�����������W���J�������W�ɓ����
		D3DXVECTOR3 atmove(0.5, 0.25, 0);//���_�̈ړ�����W��ݒ�
		D3DXVec3TransformCoord(&atmove, &atmove, &PlayerMatrix);//�v���C���[�̍s��𐳖ʂƂ��āAatmove(���_�̈ړ�����W)��������(��]���W�ƕ��s�ړ����W���|�����킹��)
		//g_at_pos = PlayerPos;//�J�����̎��_���W(at)���v���C���[�̍��W�Ɠ����ɂ���
		m_at_pos = atmove;//�J�����̎��_���W(at)���v���C���[�̍��W�Ɠ����ɂ���
	}


	//�J����
	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXMatrixLookAtLH(&m_mtxView, &m_eye_pos, &m_at_pos, &m_up_pos);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxView);//����

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxWorld);
	
	//�����Y
	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(&m_mtxProj, D3DX_PI / 3, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}