#pragma once
//=============================================================================
//  
// �]���r�̕`��
//
//=============================================================================

#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#define ZOMBIE_NUM (7)//�]���r�̐�

class Zombie
{
public:
	Zombie();
	~Zombie();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	BOOL ZombieProbe(float *pfoundangley, int i2);//�G�L�����Ɏ��L������T������
	int GetLoop(int Loop)
	{
		return Loop;
	}
	//�]���r�̈ʒu���W���lX�𑗂�
	float GetPosX(int Loop)
	{
		return m_Zombie[Loop].pos.x;
	}
	//�]���r�̈ʒu���W���lY�𑗂�
	float GetPosY(int Loop)
	{
		return m_Zombie[Loop].pos.y;
	}
	//�]���r�̈ʒu���W���lZ�𑗂�
	float GetPosZ(int Loop)
	{
		return m_Zombie[Loop].pos.z;
	}
	//�v���C���[�̈ʒu���W���l�������Ă���
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}
	//�]���r�̕`���Ԃ������Ă���
	void SetZombieDraw(int num, bool draw)
	{
		m_Zombie[num].Draw = draw;
	}


	void SetIePos(D3DXVECTOR3 pos)
	{
		IePos = pos;
	}
	void SetIeMin(D3DXVECTOR3 min)
	{
		IeMin = min;
	}
	void SetIeMax(D3DXVECTOR3 max)
	{
		IeMax = max;
	}

	void SetIe2Pos(D3DXVECTOR3 pos)
	{
		Ie2Pos = pos;
	}
	void SetIe2Min(D3DXVECTOR3 min)
	{
		Ie2Min = min;
	}
	void SetIe2Max(D3DXVECTOR3 max)
	{
		Ie2Max = max;
	}
private:
//*****************************************************************************
// �\����
//*****************************************************************************
	//�������菉�������Ȃ��ƃf�o�b�O���[�h�Ńo�O��
	enum
	{
		TK_CHASE,//�ǐՃ��[�h(���L�����������Ă���)
		TK_SEARCH//�T�����[�h(���L�����������Ă��Ȃ�)
	};

	//�݌v�}�����
	typedef struct
	{
		D3DXVECTOR3 pos;//���W
		float Ykaitenidou = 0.0f;//Y��]�ړ��p���l
		//�G�L�����̎v�l���[�`�������
		float anglesp = D3DX_PI / 2;//90�x/s
		float searchpivot = 0.0f;//�T����
		int searchturn = -1;//�T����]����(-1:�����v���A1���v���)
		float looptime = 0.01f;//1���[�v�ɂ����鎞��(�b)
		float fangley = 0.0f;
		int tekimode = TK_SEARCH;//�G�L�����s�����[�h
		D3DXVECTOR3 vec1;
		D3DXVECTOR3 vec2;

		D3DXMATRIX mtxworld;//
		D3DXMATRIX mtxworldS;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldR;//�g�k�p�ϐ�
		D3DXMATRIX mtxworldT;//�ړ��p�֐�
		bool Draw = true;//�\���E��\��
	}ZOMBIE_DATA;

	ZOMBIE_DATA m_Zombie[ZOMBIE_NUM];//�\���̂ŃA�C�e����������邩��錾

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************
	//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;


	D3DXVECTOR3 PlayerPos;
	//�o�E���f�B���O�{�b�N�X(ABB)
	D3DXVECTOR3 IePos;//�Ƃ̍��W
	D3DXVECTOR3 IeMin;//�Ƃ̍ŏ����_
	D3DXVECTOR3 IeMax;//�Ƃ̍ő咸�_
	D3DXVECTOR3 Ie2Pos;//��2�̍��W
	D3DXVECTOR3 Ie2Min;//��2�̍ŏ����_
	D3DXVECTOR3 Ie2Max;//��2�̍ő咸�_

};
#endif // _ZOMBIE_H_
