#pragma once
//=============================================================================
//  
// �G�l�~�[�̕`��
//
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ENEMY_NUM (1)
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	BOOL JikiProbe(float *pfoundangley);//�G�L�����Ɏ��L������T������
	//�G�l�~�[�̍��W�������Ă���
	void SetPos(D3DXVECTOR3 Pos)
	{
		EnemyPos = Pos;
	}
	//�G�l�~�[�̍��W�𑗂�
	D3DXVECTOR3 GetEnemyPos()
	{
		return EnemyPos;//���^�[���͌^��������
	}
	//�v���C���[���W�������Ă���
	void SetPlayerPos(D3DXVECTOR3 pos)
	{
		PlayerPos = pos;
	}
	//�G�̕`���Ԃ������Ă���
	void SetEnemyDraw(bool draw)
	{
		EnemyDraw = draw;

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
// �����o�ϐ�
//*****************************************************************************
//X���f���\���p�ϐ�
	LPD3DXMESH pMesh = NULL;
	DWORD dwNumMaterials = 0;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;

	//���[���h�s��
	D3DXMATRIX m_mtxWorld;

	//�X�P�[��
	D3DXMATRIX m_mtxWorldS;//�g��p�ϐ�

	//���[�e�[�V����
	float Ykaitenidou = 0.0f;//Y��]�ړ��p���l
	D3DXMATRIX m_mtxWorldR;//��]�p�ϐ�

	//�g�����X���[�V����
	D3DXMATRIX m_mtxWorldT;//�ړ��p�ϐ�
	D3DXVECTOR3 EnemyPos;

	D3DXVECTOR3 PlayerPos;

	bool EnemyDraw = true;//�G�̕\���E��\��


	//�G�L�����̎v�l���[�`�������
	float anglesp = D3DX_PI / 2;//90�x/s
	float searchpivot = 0.0f;//�T����
	int searchturn = -1;//�T����]����(-1:�����v���A1���v���)

	enum
	{
		TK_CHASE,//�ǐՃ��[�h(���L�����������Ă���)
		TK_SEARCH//�T�����[�h(���L�����������Ă��Ȃ�)
	};
	int tekimode = TK_SEARCH;//�G�L�����s�����[�h

	//�o�E���f�B���O�{�b�N�X(ABB)
	D3DXVECTOR3 IePos;//�Ƃ̍��W
	D3DXVECTOR3 IeMin;//�Ƃ̍ŏ����_
	D3DXVECTOR3 IeMax;//�Ƃ̍ő咸�_
	D3DXVECTOR3 Ie2Pos;//��2�̍��W
	D3DXVECTOR3 Ie2Min;//��2�̍ŏ����_
	D3DXVECTOR3 Ie2Max;//��2�̍ő咸�_
};



#endif // _ENEMY_H_

