//=============================================================================
//
// �G�l�~�[ [Enemy.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Enemy.h"
#include "Renderer.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

//==============
//  �������֐�
//==============
void Enemy::Init(void)
{


	EnemyDraw = true;//�G�̕\���E��\��
	EnemyPos.x = -50 + rand() % 100;
	EnemyPos.y = 0;
	EnemyPos.z = -50 + rand() % 100;
	//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
	if (EnemyPos.x == 0 && EnemyPos.z == 0)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
	if (EnemyPos.z <= -51 || 51 <= EnemyPos.z || EnemyPos.x <= -51 || 51 <= EnemyPos.x)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//��1�p(0.0f,0.0f,10.0f)
	if (-6 < EnemyPos.x && EnemyPos.x < 6 && 4 < EnemyPos.z && EnemyPos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//��2�p(-10.0f,0.0f,0.0f)
	if (-16 < EnemyPos.x && EnemyPos.x < -4 && -6 < EnemyPos.z && EnemyPos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() & 100;
	}

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

											//X�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("./data/xmodel/OneMeshTank.x", D3DXMESH_SYSTEMMEM,
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
				d3dxMaterials[i].pTextureFilename/*"./data/texture/kusa.png"*/,
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
void Enemy::Uninit(void)
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
void Enemy::Update(void)
{
	if (EnemyDraw == true)
	{

		////�ǔ�
		//D3DXVECTOR3 vDir = PlayerPos - EnemyPos;//�����x�N�g�����o��(�S�[�� - �X�^�[�g)
		//D3DXVec3Normalize(&vDir, &vDir);//�o���������x�N�g���𐳋K������(���̐��Ȃ�1�E���̐��Ȃ�-1�E0�Ȃ�0�ɂ���)
		//vDir *= 0.05f;//�����x�N�g���Ɉړ��ʂ������Ă�����
		//EnemyPos += vDir;//�ړ��ʂ����݂̓G�|�W�V�����ɂ����Ă�����


		float looptime = 0.01;//1���[�v�ɂ����鎞��(�b)
		float fangley;

		switch (tekimode)
		{
		case TK_SEARCH://�T�����[�h
		{
			//looptime�������ĂȂ�
			Ykaitenidou = Ykaitenidou + searchturn * anglesp * looptime;
			if (fabs(searchpivot - Ykaitenidou) > D3DX_PI / 1.5f)//fabs�֐��͐�Βl��Ԃ��֐�[searchpivot - Ykaitenidou�̍���120�x( D3DX_PI / 1.5f)���z�����璆�g�����s]
			{
				searchturn = searchturn * -1;
			}
			if (JikiProbe(&fangley) == TRUE)
			{
				//�G�L�����Ɏ��L������T������
				tekimode = TK_CHASE;//�ǐՃ��[�h�ɕύX
			}
			break;
		}
		case TK_CHASE://�ǐՃ��[�h
		{

			if (JikiProbe(&fangley) == TRUE)
			{
				if (fangley < Ykaitenidou)
				{
					searchturn = -1;
				}
				else
				{
					searchturn = 1;
				}
				Ykaitenidou = Ykaitenidou + searchturn * anglesp * looptime;
				if (fabs(fangley - Ykaitenidou) < D3DX_PI / 12)
				{
					//�O�i����
					D3DXVECTOR3 vec1(0.0f, 0.0f, 0.05f);
					D3DXVECTOR3 vec2;
					D3DXMatrixRotationY(&m_mtxWorldR, Ykaitenidou);
					D3DXVec3TransformCoord(&vec2, &vec1, &m_mtxWorldR);
					EnemyPos = EnemyPos + vec2;
				}
			}
			else
			{
				//��������
				searchpivot = Ykaitenidou;
				searchturn = -1;
				tekimode = TK_SEARCH;
			}

			break;
		}
		}



		//SRT(�X�P�[�������[�e�[�V�������g�����X���[�V����)�̏��Ԃō������Ȃ��Ƃ����Ȃ�
		D3DXMatrixIdentity(&m_mtxWorld);//���������邽�߂̏�����


		D3DXMatrixScaling(&m_mtxWorldS, 0.5f, 0.5f, 0.5f);//X���f���̊g��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorld);//����

		D3DXMatrixRotationY(&m_mtxWorldR, Ykaitenidou);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldR);//����

		D3DXMatrixTranslation(&m_mtxWorldT, EnemyPos.x, EnemyPos.y - 0.2f, EnemyPos.z);//X���f���̕��s�ړ��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);//����

	}

}

//==============
// �@�`��֐�
//==============
void Enemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	if (EnemyDraw == true)
	{

		//�n�� 01
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

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

void Enemy::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	EnemyDraw = true;//�G�̕\���E��\��
	EnemyPos.x = -50 + rand() % 100;
	EnemyPos.y = 0;
	EnemyPos.z = -50 + rand() % 100;
	//�v���C���[�̏������W�ɔ��Ȃ��悤�ɂ���
	if (EnemyPos.x == 0 && EnemyPos.z == 0)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//�t�B�[���h�O�ɏo�Ȃ��悤�ɂ���
	if (EnemyPos.z <= -51 || 51 <= EnemyPos.z || EnemyPos.x <= -51 || 51 <= EnemyPos.x)
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//��1�p(0.0f,0.0f,10.0f)
	if (-6 < EnemyPos.x && EnemyPos.x < 6 && 4 < EnemyPos.z && EnemyPos.z < 16)//����z���W��4���傫������16��菬�����ꍇ������xz���W�̂�蒼��
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() % 100;
	}
	//��2�p(-10.0f,0.0f,0.0f)
	if (-16 < EnemyPos.x && EnemyPos.x < -4 && -6 < EnemyPos.z && EnemyPos.z < 6)//����x���W��-16���傫������-4��菬�����ꍇ������xx���W�̂�蒼��
	{
		EnemyPos.x = -50 + rand() % 100;
		EnemyPos.z = -50 + rand() & 100;
	}

}

//�G�L�����Ɏ��L������T������
BOOL Enemy::JikiProbe(float *pfoundangley)
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
		D3DXMatrixRotationY(&matWorld, Ykaitenidou + D3DX_PI / 40 * i);
		D3DXVec3TransformCoord(&probevec2, &probevec1, &matWorld);
		if (D3DXBoxBoundProbe(&PlayerMin, &PlayerMax, &EnemyPos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�Ƀv���C���[���������Ȃ牺�̓��e�����s
		{
			//�n�`�Ƃ̓����蔻��
			D3DXVECTOR3 temp1 = PlayerPos - EnemyPos;//���L�����Ƃ̋����𒲂ׂ�
			float l1 = D3DXVec3Length(&temp1);//�v���C���[�ƃG�l�~�[�̋�����l1�ɓ����

			if (D3DXBoxBoundProbe(&IeMin, &IeMax, &EnemyPos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�ɉƂ��������Ȃ牺�̓��e�����s
			{

				temp1 = IePos - EnemyPos;//�ƂƂ̋����𒲂ׂ�
				float l2 = D3DXVec3Length(&temp1);//�ƂƃG�l�~�[�̋�����l2�ɓ����

				if (l2 < l1)//�� - �G�l�~�[�̋��� < �v���C���[ - �G�l�~�[�̋���
				{
					//���L�����Ƃ̊Ԃɂ��� 
					break;//���[�v���o�Ă��̊֐����I������
				}

			}

			if (D3DXBoxBoundProbe(&Ie2Min, &Ie2Max, &EnemyPos, &probevec2) == TRUE)//�����G�l�~�[�̎��E�ɉ�2���������Ȃ牺�̓��e�����s
			{

				temp1 = Ie2Pos - EnemyPos;//�ƂƂ̋����𒲂ׂ�
				float l3 = D3DXVec3Length(&temp1);//�ƂƃG�l�~�[�̋�����l2�ɓ����

				if (l3 < l1)//�� - �G�l�~�[�̋��� < �v���C���[ - �G�l�~�[�̋���
				{
					//���L�����Ƃ̊Ԃɂ��� 
					break;//���[�v���o�Ă��̊֐����I������
				}

			}

			//����
			*pfoundangley = Ykaitenidou + D3DX_PI / 40 * i;
			return TRUE;
		}
	}
	return FALSE;
}


