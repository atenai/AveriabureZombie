//=============================================================================
//
// �]���r [Zombie.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Zombie.h"
#include "Renderer.h"


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

//==============
//  �������֐�
//==============
void Zombie::Init(void)
{
	//�������菉�������Ȃ��ƃf�o�b�O���[�h�Ńo�O��
	//for (Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	//{
	//	m_Zombie[Loop].Ykaitenidou = 0.0f;
	//	m_Zombie[Loop].anglesp = D3DX_PI / 2;//90�x/s
	//	m_Zombie[Loop].searchpivot = 0.0f;//�T����
	//	m_Zombie[Loop].searchturn = -1;//�T����]����(-1:�����v���A1���v���)
	//	m_Zombie[Loop].looptime = 0.01f;//1���[�v�ɂ����鎞��(�b)
	//	m_Zombie[Loop].fangley = 0.0f;
	//}

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zombie[Loop].pos.x = -50 + rand() % 100;
		m_Zombie[Loop].pos.y = 0;
		m_Zombie[Loop].pos.z = -50 + rand() % 100;
		//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
		if (m_Zombie[Loop].pos.x == 0 && m_Zombie[Loop].pos.z == 0)
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_Zombie[Loop].pos.z <= -51 || 51 <= m_Zombie[Loop].pos.z || m_Zombie[Loop].pos.x <= -51 || 51 <= m_Zombie[Loop].pos.x)
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Zombie[Loop].pos.x && m_Zombie[Loop].pos.x < 6 && 4 < m_Zombie[Loop].pos.z && m_Zombie[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Zombie[Loop].pos.x && m_Zombie[Loop].pos.x < -4 && -6 < m_Zombie[Loop].pos.z && m_Zombie[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() & 100;
		}
	}

	//�]���r���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zombie[Loop].Draw = true;//�]���r�̕\��
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/Human.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];//�}�e���A���̃������̈���}�e���A���̐������m�ۂ�pMeshMaterials�ɓ����
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];//�e�N�X�`���ɕK�v�ȃ������̈���m�ۂ�pMeshTextures�ɓ����

														   //��Ŋm�ۂ����������̈�ɒ��g�����Ă���
	for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;//�}�e���A���f�[�^������
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;//Ambient��Diffuse�Ɠ����l�ɂ���

															  //pTextureFilename�����ƂɃe�N�X�`���I�u�W�F�N�g�̐���
		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename/*"./data/texture/Ground.bmp"*/,//�e�N�X�`�����w��
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();//�������̊J��

}

//==============
//  �I���֐�
//==============
void Zombie::Uninit(void)
{

	if (pMesh != NULL)
	{
		pMesh->Release();//����ŊJ�������
		pMesh = NULL;//�A�h���X���c���Ă���̂�NULL�ŏ㏑��
	}

}

//==============
// �@�X�V�֐�
//==============
void Zombie::Update(void)
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{

		if (m_Zombie[Loop].Draw == true)
		{


			////�ǔ�
			//D3DXVECTOR3 vDir = PlayerPos - Zombie[Loop].pos;//�����x�N�g�����o��(�S�[�� - �X�^�[�g)
			//D3DXVec3Normalize(&vDir, &vDir);//�o���������x�N�g���𐳋K������(���̐��Ȃ�1�E���̐��Ȃ�-1�E0�Ȃ�0�ɂ���)
			//vDir *= 0.05f;//�����x�N�g���Ɉړ��ʂ������Ă�����
			//Zombie[Loop].pos += vDir;//�ړ��ʂ����݂̓G�|�W�V�����ɂ����Ă�����


			

			switch (m_Zombie[Loop].tekimode)
			{
			case TK_SEARCH://�T�����[�h
			{
				//looptime�������ĂȂ�
				m_Zombie[Loop].Ykaitenidou = m_Zombie[Loop].Ykaitenidou + m_Zombie[Loop].searchturn * m_Zombie[Loop].anglesp * m_Zombie[Loop].looptime;
				if (fabs(m_Zombie[Loop].searchpivot - m_Zombie[Loop].Ykaitenidou) > D3DX_PI / 1.5f)//fabs�֐��͐�Βl��Ԃ��֐�[searchpivot - Ykaitenidou�̍���120�x( D3DX_PI / 1.5f)���z�����璆�g�����s]
				{
					m_Zombie[Loop].searchturn = m_Zombie[Loop].searchturn * -1;
				}
				if (ZombieProbe(&m_Zombie[Loop].fangley, Loop) == TRUE)
				{
					//�G�L�����Ɏ��L������T������
					m_Zombie[Loop].tekimode = TK_CHASE;//�ǐՃ��[�h�ɕύX
				}
				break;
				
			}
			case TK_CHASE://�ǐՃ��[�h
			{

				if (ZombieProbe(&m_Zombie[Loop].fangley, Loop) == TRUE)
				{
					if (m_Zombie[Loop].fangley < m_Zombie[Loop].Ykaitenidou)
					{
						m_Zombie[Loop].searchturn = -1;
					}
					else
					{
						m_Zombie[Loop].searchturn = 1;
					}
					m_Zombie[Loop].Ykaitenidou = m_Zombie[Loop].Ykaitenidou + m_Zombie[Loop].searchturn * m_Zombie[Loop].anglesp * m_Zombie[Loop].looptime;
					if (fabs(m_Zombie[Loop].fangley - m_Zombie[Loop].Ykaitenidou) < D3DX_PI / 12)
					{
						//�O�i����
						m_Zombie[Loop].vec1.x = 0.0f;
						m_Zombie[Loop].vec1.y = 0.0f;
						m_Zombie[Loop].vec1.z = 0.05f;
						m_Zombie[Loop].vec2;
						D3DXMatrixRotationY(&m_Zombie[Loop].mtxworldR, m_Zombie[Loop].Ykaitenidou);
						D3DXVec3TransformCoord(&m_Zombie[Loop].vec2, &m_Zombie[Loop].vec1, &m_Zombie[Loop].mtxworldR);
						m_Zombie[Loop].pos = m_Zombie[Loop].pos + m_Zombie[Loop].vec2;
					}
				}
				else
				{
					//��������
					m_Zombie[Loop].searchpivot = m_Zombie[Loop].Ykaitenidou;
					m_Zombie[Loop].searchturn = -1;
					m_Zombie[Loop].tekimode = TK_SEARCH;
				}

				break;
			}
			}



			//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
			D3DXMatrixIdentity(&m_Zombie[Loop].mtxworld);//���������邽�߂̏�����

													  //�n�� 01
			D3DXMatrixScaling(&m_Zombie[Loop].mtxworldS, 1.0f, 1.0f, 1.0f);//X���f���̊g��֐�
			D3DXMatrixMultiply(&m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworldS);//����

			D3DXMatrixRotationY(&m_Zombie[Loop].mtxworldR, m_Zombie[Loop].Ykaitenidou);
			D3DXMatrixMultiply(&m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworldR);//����

			D3DXMatrixTranslation(&m_Zombie[Loop].mtxworldT, m_Zombie[Loop].pos.x, m_Zombie[Loop].pos.y, m_Zombie[Loop].pos.z);//X���f���̕��s�ړ��֐�
			D3DXMatrixMultiply(&m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworld, &m_Zombie[Loop].mtxworldT);//����

		}
	}
}

//==============
// �@�`��֐�
//==============
void Zombie::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		if (m_Zombie[Loop].Draw == true)
		{
			//�n�� 01
			pDevice->SetTransform(D3DTS_WORLD, &m_Zombie[Loop].mtxworld);

			//Direct3D�ɂ�����u���b�V���v�́u�����_�����O�v�́u�}�e���A���v����ɂ��Ă��܂��B
			//Direct3D�ɂ�����u�I�u�W�F�N�g�f�[�^�v�́u�`��v�́u�\�ʓI�������v����ɂ��Ă��܂��B
			for (DWORD i = 0; i < dwNumMaterials; i++) //�}�e���A���̐��������[�v����
			{
				pDevice->SetMaterial(&pMeshMaterials[i]);//�}�e���A����ݒ肷��
				pDevice->SetTexture(0, pMeshTextures[i]);//�e�N�X�`����ݒ肷��
				pMesh->DrawSubset(i);//�����_�����O����
			}
		}
	}
}

//�G�L�����Ɏ��L������T������
BOOL Zombie::ZombieProbe(float *pfoundangley, int i2)
{
	//���L�����̋��E�{�b�N�X�쐬
	D3DXVECTOR3 PlayerMin(PlayerPos.x - 0.5f, PlayerPos.y - 0.5f, PlayerPos.z - 0.5f);//�v���C���[�̍ŏ����_���v�Z����
	D3DXVECTOR3 PlayerMax(PlayerPos.x + 0.5f, PlayerPos.y + 0.5f, PlayerPos.z + 0.5f);//�v���C���[�̍ő咸�_���v�Z����

	D3DXVECTOR3 probevec1(0.0f, 0.0f, 1.0f);//�����x�N�g��
	D3DXVECTOR3 probevec2;
	D3DXMATRIXA16 matWorld;
	//45�x�̎����4.5�x�P�ʂŒT��

	for (int i = -5; i < 6; i = i + 1)
	{
		D3DXMatrixRotationY(&matWorld, m_Zombie[i2].Ykaitenidou + D3DX_PI / 40 * i);
		D3DXVec3TransformCoord(&probevec2, &probevec1, &matWorld);
		if (D3DXBoxBoundProbe(&PlayerMin, &PlayerMax, &m_Zombie[i2].pos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�Ƀv���C���[���������Ȃ牺�̓��e�����s
		{
			//�n�`�Ƃ̓����蔻��
			D3DXVECTOR3 temp1 = PlayerPos - m_Zombie[i2].pos;//���L�����Ƃ̋����𒲂ׂ�
			float l1 = D3DXVec3Length(&temp1);//�v���C���[�ƃG�l�~�[�̋�����l1�ɓ����

			if (D3DXBoxBoundProbe(&IeMin, &IeMax, &m_Zombie[i2].pos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�ɉƂ��������Ȃ牺�̓��e�����s
			{

				temp1 = IePos - m_Zombie[i2].pos;//�ƂƂ̋����𒲂ׂ�
				float l2 = D3DXVec3Length(&temp1);//�ƂƃG�l�~�[�̋�����l2�ɓ����

				if (l2 < l1)//�� - �G�l�~�[�̋��� < �v���C���[ - �G�l�~�[�̋���
				{
					//���L�����Ƃ̊Ԃɂ��� 
					break;//���[�v���o�Ă��̊֐����I������
				}

			}

			if (D3DXBoxBoundProbe(&Ie2Min, &Ie2Max, &m_Zombie[i2].pos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�ɉ�2���������Ȃ牺�̓��e�����s
			{

				temp1 = Ie2Pos - m_Zombie[i2].pos;//�ƂƂ̋����𒲂ׂ�
				float l3 = D3DXVec3Length(&temp1);//�ƂƃG�l�~�[�̋�����l2�ɓ����

				if (l3 < l1)//�� - �G�l�~�[�̋��� < �v���C���[ - �G�l�~�[�̋���
				{
					//���L�����Ƃ̊Ԃɂ��� 
					break;//���[�v���o�Ă��̊֐����I������
				}

			}

			//����
			*pfoundangley = m_Zombie[i2].Ykaitenidou + D3DX_PI / 40 * i;
			return TRUE;
		}
	}
	return FALSE;
}

void Zombie::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zombie[Loop].pos.x = -50 + rand() % 100;
		m_Zombie[Loop].pos.y = 0;
		m_Zombie[Loop].pos.z = -50 + rand() % 100;
		//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
		if (m_Zombie[Loop].pos.x == 0 && m_Zombie[Loop].pos.z == 0)
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
		if (m_Zombie[Loop].pos.z <= -51 || 51 <= m_Zombie[Loop].pos.z || m_Zombie[Loop].pos.x <= -51 || 51 <= m_Zombie[Loop].pos.x)
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//��1�p(0.0f,0.0f,10.0f)
		if (-6 < m_Zombie[Loop].pos.x && m_Zombie[Loop].pos.x < 6 && 4 < m_Zombie[Loop].pos.z && m_Zombie[Loop].pos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() % 100;
		}
		//��2�p(-10.0f,0.0f,0.0f)
		if (-16 < m_Zombie[Loop].pos.x && m_Zombie[Loop].pos.x < -4 && -6 < m_Zombie[Loop].pos.z && m_Zombie[Loop].pos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
		{
			m_Zombie[Loop].pos.x = -50 + rand() % 100;
			m_Zombie[Loop].pos.z = -50 + rand() & 100;
		}
	}

	//�]���r���v���C���[�ɓ����������̕\���E��\�����Ǘ�
	for (int Loop = 0; Loop < ZOMBIE_NUM; Loop++)//�\���̂̐������� 
	{
		m_Zombie[Loop].Draw = true;//�]���r�̕\��
	}
}