#pragma once
//=============================================================================
//  
// �e�̕`��
//
//=============================================================================

#ifndef _SHOT_H_
#define _SHOT_H_

#define SHOT_NUM 200//�e�̐�

class Shot
{
public:
	Shot();
	~Shot();
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
	//�e�̈ʒu���W���lX�𑗂�
	float GetPosX(int Loop)
	{
		return m_Shot[Loop].ShotPos.x;
	}
	//�e�̈ʒu���W���lY�𑗂�
	float GetPosY(int Loop)
	{
		return m_Shot[Loop].ShotPos.y;
	}
	//�e�̈ʒu���W���lZ�𑗂�
	float GetPosZ(int Loop)
	{
		return m_Shot[Loop].ShotPos.z;
	}
	//�e�̕`���Ԃ������Ă���
	void SetShotDraw(int kazu, bool draw)
	{
		m_Shot[kazu].Draw = draw;
	}
	//�e�̂����蔻���Ԃ������Ă���
	void SetShotAtariHantei(int kazu, bool draw)
	{
		m_Shot[kazu].AtariHantei = draw;
	}
	//�e�̕`���Ԃ𑗂�
	bool GetShotDraw(int kazu)
	{
		return m_Shot[kazu].Draw;
	}
	//�e�̂����蔻���Ԃ𑗂�
	bool GetShotAtariHantei(int Loop)
	{
		return m_Shot[Loop].AtariHantei;
	}

	void SetTamaHuyasu(int su)
	{
		num = num - su;//�e�������炷
		if (num < 0)//num��0�ȉ��̏ꍇ
		{
			num = 0;//num��0�ɂ���
		}
		Shot_UI = Shot_UI + su;//�e��UI�\���p�ϐ��𑝂₷
		if (Shot_UI > SHOT_NUM)//�e��UI�\����SHOT_NUM���z������
		{
			Shot_UI = SHOT_NUM;//�e��UI�\����SHOT_NUM�Ɠ����ɂ���
		}
	}

	//�v���C���[�̑O�x�N�g���������Ă���
	void SetPlayerFront(D3DXVECTOR3 ret)
	{
		PlayerFront = ret;
	}

	//�e�̎c��e����UI�𑗂鏈��
	int GetShot_UI()
	{
		return Shot_UI;
	}

private:
//*****************************************************************************
// �\����
//*****************************************************************************
//�݌v�}�����
	typedef struct
	{
		D3DXVECTOR3 ShotPos;//�e�̍��W
		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		bool Draw = false;//�e�̕\���E��\��
		bool AtariHantei = false;//�e�̂����蔻��
		D3DXVECTOR3 muki;//�v���C���[�̐��ʃx�N�g�����e�e�ɓ����ϐ�
	}SHOT_DATA;

	SHOT_DATA m_Shot[SHOT_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;

	int num = 0;//�e�̒e����
	int Shot_UI = SHOT_NUM;//�e��UI�\���p�ϐ�

	D3DXVECTOR3 PlayerPos;//�v���C���[�̍��W
	D3DXVECTOR3 PlayerFront;//�v���C���[�̑O�x�N�g��

	//�T�E���h
	int oto0;//���y�p�ϐ�
	int oto1;//���y�p�ϐ�
};


#endif // _SHOT_H_

