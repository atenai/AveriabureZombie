#pragma once
//=============================================================================
//  
// �v���C���[�̕`��
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PARTS_NUM 15 //�p�[�c�̐�

//*****************************************************************************
// ���N���X
//*****************************************************************************
//�v���C���[�N���X
class Player
{
public:
	Player();//�R���X�g���N�^
	~Player();//�f�X�g���N�^
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g

	D3DXVECTOR3 GetFront(void)//�v���C���[�̑O�x�N�g���𑗂�
	{
		D3DXVECTOR3 ret = D3DXVECTOR3(m_Part[0].World._31, m_Part[0].World._32, m_Part[0].World._33);

		D3DXVec3Normalize(&ret, &ret);

		return ret;
	}


	//�v���C���[�̍��W�������Ă���
	void SetPlayerPos(D3DXVECTOR3 Pos)
	{
		PlayerPos = Pos;
	}
	//�v���C���[�̍��W�𑗂�
	D3DXVECTOR3 GetPlayerPos()
	{
		return PlayerPos;//���^�[���͌^��������
	}
	//�v���C���[�ƉƂ̃o�E���f�B���O�{�b�N�X�����蔻��̌��ʂ������Ă���
	void SetPlayerIeBoxAtari(bool hit)
	{
		PlayerIeBoxAtari = hit;
	}
	//�v���C���[�Ɖ�2�̃o�E���f�B���O�{�b�N�X�����蔻��̌��ʂ������Ă���
	void SetPlayerIe2BoxAtari(bool hit)
	{
		PlayerIe2BoxAtari = hit;
	}
	//�v���C���[�̍ŏ����_�𑗂�
	D3DXVECTOR3 GetPlayerMin()
	{
		return PlayerMin;
	}
	//�v���C���[�̍ő咸�_�𑗂�
	D3DXVECTOR3 GetPlayerMax()
	{
		return PlayerMax;
	}

	void SetPlayerSita(bool hit)
	{
		PlayerSita = hit;
	}
	void SetPlayerUe(bool hit)
	{
		PlayerUe = hit;
	}
	void SetPlayerMigi(bool hit)
	{
		PlayerMigi = hit;
	}
	void SetPlayerHidari(bool hit)
	{
		PlayerHidari = hit;
	}

	////�v���C���[�̉�]���W�ƈړ����W���J�����ɑ���֐�
	D3DXMATRIX GetMtxWorld() 
	{
		return m_Part[0].World;
	}

private:
//*****************************************************************************
// �����o�ϐ�
//*****************************************************************************

	//�o�E���f�B���O�{�b�N�X�̂����蔻��
	D3DXVECTOR3 PlayerMin;
	D3DXVECTOR3 PlayerMax;
	bool PlayerIeBoxAtari = false;
	bool PlayerIe2BoxAtari = false;

	bool PlayerSita = false;
	bool PlayerMigi = false;
	bool PlayerUe = false;
	bool PlayerHidari = false;

	//�X�P�[��
	void Scaling();//�g�k����

	//���[�e�[�V����
	void Rotation();//��]����
	float Ykaitenidou = 0.0f;//Y��]�ړ��p���l

	//�g�����X���[�V����
	void Translation();//�ړ�����
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ��搔�l

	//�L�[�t���[���A�j���[�V����
	int m_Key = 2;//�L�[�t���[���̊e���W�̕ϐ�
	int m_Frame = 0;//�t���[���Ԃ𓮂������߂̕ϐ�

	struct PARTS
	{
		//X���f���\���p�ϐ�
		LPD3DXMESH pMesh = NULL;      //���b�V�����󂯂Ƃ�ϐ�
		DWORD dwNumMaterials = 0;	 //�}�e���A����
		D3DMATERIAL9* pMeshMaterials = NULL;
		LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;//�}�e���A�����󂯎��
		D3DXMATERIAL* d3dxMaterials;
		//X���f���\���p�ϐ�

		D3DXVECTOR3 Position;//���W�ϐ�
		D3DXVECTOR3 Rotate;//��]�ϐ�
		D3DXMATRIX World;//���[���h�s��
		D3DXMATRIX Matrix;//�s��
		D3DXMATRIX Transform;//�ړ��s��
		D3DXMATRIX Rotation;//��]�s��
		D3DXMATRIX Scale;//�g�k�s��
		PARTS *Parent;//�e������
	};
	PARTS m_Part[PARTS_NUM];//�p�[�c�\���̂�10����


	//1�p�[�c�̍��W�Ɖ�]
	typedef struct
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Rotation;
	}KEY;

	//�L�[�t���[��
	typedef struct
	{
		int Frame;//��ԃt���[����
		KEY Key[PARTS_NUM];//��̈ړ����W�Ɖ�]���W�������Ă���
	}KEY_FRAME;

	KEY_FRAME m_KeyFrameWalk[PARTS_NUM] = //�\���̂ŃA�C�e����������邩��錾
	{
		//m_Key0
			{
			//Frame = 30 m_Frame = 0 ���r���� Frame >= m_Frame�̊Ԃ����p�[�c�𓮂���
			30,
			{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.7f,-0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�e
	}
},

//m_Key1
{
	//Frame = 30 m_Frame = 0 ���r���� Frame >= m_Frame�̊Ԃ����p�[�c�𓮂���
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.65f,-0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(-1.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�e
	}
},

//m_Key2//�n�܂�
{
	//Frame = 30 m_Frame = 0 ���r���� Frame >= m_Frame�̊Ԃ����p�[�c�𓮂���
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.6f,-0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�e
	}
},

//m_Key3
{
	//Frame = 30 m_Frame = 0 ���r���� Frame >= m_Frame�̊Ԃ����p�[�c�𓮂���
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.65f,-0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(-1.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�e
	}
},

//m_Key4
{
	//Frame = 30 m_Frame = 0 ���r���� Frame >= m_Frame�̊Ԃ����p�[�c�𓮂���
	30,
	{
		//key[10]
		{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.0f,0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��
		{ D3DXVECTOR3(0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,-1.7f,-0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.5f) },//�E�r
		{ D3DXVECTOR3(0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.2f,0.15f,0.0f),D3DXVECTOR3(0.0f,1.75f,0.2f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.75f,0.0f) },//���r
		{ D3DXVECTOR3(-0.25f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�E��
		{ D3DXVECTOR3(-0.1f,-0.35f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//��������
		{ D3DXVECTOR3(0.0f,-0.25f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//����
		{ D3DXVECTOR3(0.1f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },//�e
	}
}
	};

	KEY_FRAME *m_KeyFrame = m_KeyFrameWalk;

	float test = 0.0f;
};

#endif // _PLAYER_H_
