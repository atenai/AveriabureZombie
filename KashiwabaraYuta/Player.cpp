//=============================================================================
//
// �v���C���[ [Player.cpp]
// Author : YUTA KASHIWABARA
//
//=============================================================================
#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Main.h"
#include "Player.h"
#include"input.h"
#include "Camera.h"
#include "Renderer.h"
#include "PlayerKage.h"
#include "Shot.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//==============
//�R���X�g���N�^
//==============
Player::Player()
{
	//�e�̃|�C���^�ݒ�(�e�����鏉��������)
	m_Part[0].Parent = NULL;//����
	m_Part[1].Parent = &m_Part[0];//��
	m_Part[2].Parent = &m_Part[0];//�E�r
	m_Part[3].Parent = &m_Part[2];//�E��
	m_Part[4].Parent = &m_Part[3];//�E��

	m_Part[5].Parent = &m_Part[0];//���r
	m_Part[6].Parent = &m_Part[5];//����
	m_Part[7].Parent = &m_Part[6];//����

	m_Part[8].Parent = &m_Part[0];//�E������
	m_Part[9].Parent = &m_Part[8];//�E��
	m_Part[10].Parent = &m_Part[9];//�E��

	m_Part[11].Parent = &m_Part[0];//��������
	m_Part[12].Parent = &m_Part[11];//����
	m_Part[13].Parent = &m_Part[12];//����

	m_Part[14].Parent = &m_Part[4];//�e
}

//==============
//�f�X�g���N�^
//==============
Player::~Player()
{
}

//==============
//  �������֐�
//==============
void Player::Init(void) 
{

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	HRESULT hr;

	//��
	hr = D3DXLoadMeshFromX("./data/xmodel/Karada.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[0].pD3DXMtrlBuffer,
		NULL,
		&m_Part[0].dwNumMaterials,
		&m_Part[0].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�̃��f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//��
	hr = D3DXLoadMeshFromX("./data/xmodel/Atama.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[1].pD3DXMtrlBuffer,
		NULL,
		&m_Part[1].dwNumMaterials,
		&m_Part[1].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�����f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E�r
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[2].pD3DXMtrlBuffer,
		NULL,
		&m_Part[2].dwNumMaterials,
		&m_Part[2].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�r���f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E�r
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[3].pD3DXMtrlBuffer,
		NULL,
		&m_Part[3].dwNumMaterials,
		&m_Part[3].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�胂�f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E��
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiTe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[4].pD3DXMtrlBuffer,
		NULL,
		&m_Part[4].dwNumMaterials,
		&m_Part[4].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�胂�f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//���r
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[5].pD3DXMtrlBuffer,
		NULL,
		&m_Part[5].dwNumMaterials,
		&m_Part[5].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���r���f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//���r
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariUde.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[6].pD3DXMtrlBuffer,
		NULL,
		&m_Part[6].dwNumMaterials,
		&m_Part[6].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���胂�f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//����
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariTe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[7].pD3DXMtrlBuffer,
		NULL,
		&m_Part[7].dwNumMaterials,
		&m_Part[7].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���胂�f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E������
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[8].pD3DXMtrlBuffer,
		NULL,
		&m_Part[8].dwNumMaterials,
		&m_Part[8].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E���������f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E������
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[9].pD3DXMtrlBuffer,
		NULL,
		&m_Part[9].dwNumMaterials,
		&m_Part[9].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�����f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�E��
	hr = D3DXLoadMeshFromX("./data/xmodel/MigiAsi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[10].pD3DXMtrlBuffer,
		NULL,
		&m_Part[10].dwNumMaterials,
		&m_Part[10].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�����f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//��������
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[11].pD3DXMtrlBuffer,
		NULL,
		&m_Part[11].dwNumMaterials,
		&m_Part[11].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�����������f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//��������
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariHutomomo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[12].pD3DXMtrlBuffer,
		NULL,
		&m_Part[12].dwNumMaterials,
		&m_Part[12].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�������f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//����
	hr = D3DXLoadMeshFromX("./data/xmodel/HidariAsi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[13].pD3DXMtrlBuffer,
		NULL,
		&m_Part[13].dwNumMaterials,
		&m_Part[13].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�������f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	//�e
	hr = D3DXLoadMeshFromX("./data/xmodel/Gun.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_Part[14].pD3DXMtrlBuffer,
		NULL,
		&m_Part[14].dwNumMaterials,
		&m_Part[14].pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�E�胂�f���̓ǂݍ��݂Ɏ��s���܂���", "���s���b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
	}

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		m_Part[Loop].d3dxMaterials = (D3DXMATERIAL*)m_Part[Loop].pD3DXMtrlBuffer->GetBufferPointer();

		m_Part[Loop].pMeshMaterials = new D3DMATERIAL9[m_Part[Loop].dwNumMaterials];//�}�e���A���̃������̈���}�e���A���̐������m�ۂ�pMeshMaterials�ɓ����
		m_Part[Loop].pMeshTextures = new LPDIRECT3DTEXTURE9[m_Part[Loop].dwNumMaterials];//�e�N�X�`���ɕK�v�ȃ������̈���m�ۂ�pMeshTextures�ɓ����

		//��Ŋm�ۂ����������̈�ɒ��g�����Ă���
		for (DWORD i = 0; i < m_Part[Loop].dwNumMaterials; i++) //�}�e���A���̐��������[�v����
		{
			m_Part[Loop].pMeshMaterials[i] = m_Part[Loop].d3dxMaterials[i].MatD3D;//�}�e���A���f�[�^������
			m_Part[Loop].pMeshMaterials[i].Ambient = m_Part[Loop].pMeshMaterials[i].Diffuse;//Ambient��Diffuse�Ɠ����l�ɂ���

																  //pTextureFilename�����ƂɃe�N�X�`���I�u�W�F�N�g�̐���
			m_Part[Loop].pMeshTextures[i] = NULL;
			if (m_Part[Loop].d3dxMaterials[i].pTextureFilename != NULL && lstrlen(m_Part[Loop].d3dxMaterials[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					m_Part[Loop].d3dxMaterials[i].pTextureFilename/*"./data/texture/Ground.bmp"*/,//�e�N�X�`�����w��
					&m_Part[Loop].pMeshTextures[i])))
				{
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
		m_Part[Loop].pD3DXMtrlBuffer->Release();//�������̊J��
	}
}

//==============
//  �I���֐�
//==============
void Player::Uninit(void)
{
	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		if (m_Part[Loop].pMesh != NULL)
		{
			m_Part[Loop].pMesh->Release();//����ŊJ�������
			m_Part[Loop].pMesh = NULL;//�A�h���X���c���Ă���̂�NULL�ŏ㏑��
		}
	}
}

//==============
// �@�X�V�֐�
//==============
void Player::Update(void) 
{

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		D3DXMatrixIdentity(&m_Part[Loop].World);//�s��̏�����
	}


	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		float rate = (float)m_Frame / (float)m_KeyFrame[m_Key].Frame;//�����䗦//rate��0�`1�̊Ԃ��s��������

		//���݂̃L�[�̈ړ����W�Ɖ�]���W
		D3DXVECTOR3 GenzaiPos = m_KeyFrame[m_Key].Key[Loop].Position;
		D3DXVECTOR3 GenziaRot = m_KeyFrame[m_Key].Key[Loop].Rotation;

		//���̃L�[�̈ړ����W�Ɖ�]���W
		D3DXVECTOR3 nextPos = m_KeyFrame[m_Key + 1].Key[Loop].Position;
		D3DXVECTOR3	nextRot = m_KeyFrame[m_Key + 1].Key[Loop].Rotation;

		//���`���
		m_Part[Loop].Position = GenzaiPos * (1.0f - rate) + nextPos * rate;
		m_Part[Loop].Rotate = GenziaRot * (1.0f - rate) + nextRot * rate;

	}


	if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_Q) || GetKeyboardPress(DIK_A))//�L�[�t���[����i�߂�
	{
		m_Frame++;
	}
	else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_E) || GetKeyboardPress(DIK_D))//�L�[�t���[����߂�
	{
		m_Frame--;
	}

	//�L�[�t���[����i�߂ăt���[����31���z�����ꍇ
	if (m_Frame >= 31/*m_KeyFrame[m_Key].Frame*/)//����m_Frame��m_KeyFrame[m_Key�Ԗ�]��Frame���傫���ꍇ
	{
		m_Frame = 0;//�t���[����0�ɂ���
		m_Key++;//���̃L�[�ɂ���

	}

	//�L�[���ő�܂ł�������ŏ��L�[�ɖ߂�����
	if (m_Key >= 4)//�L�[��4���傫���Ȃ����ꍇ
	{
		m_Key = 0;//�L�[��0�ɂ���
	}

	//�L�[�t���[����߂��ăt���[����-1����������ꍇ
	if (-1 >= m_Frame)
	{
		m_Frame = 30;//�t���[����30�ɂ���
		m_Key--;//�O�̃L�[�ɖ߂�
	}

	//�L�[���ŏ��܂ł�������ő�L�[�ɂ��鏈��
	if (-1 >= m_Key)//m�L�[��-1��菬�����Ȃ����ꍇ
	{
		m_Key = 3;//�L�[��3�ɂ���
	}

	//SRT�s��v�Z
	Scaling();//S�g�k����
	Rotation();//R��]����
	Translation();//T�ړ�����
	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		//�e��s��̐ݒ�
		//�e�̃}�g���N�X��������
		if (m_Part[Loop].Parent != NULL)
		{
			D3DXMatrixMultiply(&m_Part[Loop].World, &m_Part[Loop].World, &m_Part[Loop].Parent->Matrix);
		}
		m_Part[Loop].Matrix = m_Part[Loop].World;
	}
}

//�g�k����
void Player::Scaling()
{
	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixScaling(&m_Part[i].Scale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Scale);
	}
}

//��]����
void Player::Rotation()
{
	/////////////////��]����//////////////////////////////////////
	if (GetKeyboardPress(DIK_J) || GetKeyboardPress(DIK_Q) || GetKeyboardPress(DIK_LEFTARROW))//����I�L�[�����͂��ꂽ��
	{

		Ykaitenidou = Ykaitenidou - 0.016f;

	}
	else if (GetKeyboardPress(DIK_L) || GetKeyboardPress(DIK_E) || GetKeyboardPress(DIK_RIGHTARROW))//����P�L�[�����͂��ꂽ��
	{

		Ykaitenidou = Ykaitenidou + 0.016f;

	}

	m_Part[0].Rotate.y = Ykaitenidou;//�e�ł���{�f�B�̉�]���W�ɐV������]���W������
	/////////////////��]����//////////////////////////////////////

	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixRotationYawPitchRoll(&m_Part[i].Rotation, m_Part[i].Rotate.y, m_Part[i].Rotate.x, m_Part[i].Rotate.z);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Rotation);
	}
}

//�ړ�����
void Player::Translation()
{
	// �܂��͎��x�N�g����p�ӂ��� �����2���̂݁iY���͍l�����Ȃ��j
	D3DXVECTOR3 vecAxisX(1.0f, 0.0f, 0.0f);//�ϊ��O��X���x�N�g��
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);//�ϊ��O��Z���x�N�g��
	//X�AZ���x�N�g�����̂��̂������݂̉�]��Ԃɂ��ϊ�����
	D3DXVec3TransformCoord(&vecAxisX, &vecAxisX, &m_Part[0].Rotation);//���[�e�[�V�������������̂�ω��O��X���x�N�g���ɂ�����
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &m_Part[0].Rotation);//���[�e�[�V�������������̂�ω��O��Z���x�N�g���ɂ�����


	///////////////////////////////���E�ړ�///////////////////////
	if (GetKeyboardPress(DIK_A))//����A�L�[�����͂��ꂽ��
	{
		PlayerPos = PlayerPos - vecAxisX * 0.1f;//���ړ��X�s�[�h
	}
	else if (GetKeyboardPress(DIK_D))//����D�L�[�����͂��ꂽ��
	{
		PlayerPos = PlayerPos + vecAxisX * 0.1f;//���ړ��X�s�[�h
	}


	///////////////////////////////���E�ړ�///////////////////////
	///////////////////////////////�O��ړ�///////////////////////

	if (GetKeyboardPress(DIK_W))//����W�L�[�����͂��ꂽ��
	{
		PlayerPos = PlayerPos + vecAxisZ * 0.1f;//�c�ړ��X�s�[�h
	}
	else if (GetKeyboardPress(DIK_S))//����S�L�[�����͂��ꂽ��
	{
		PlayerPos = PlayerPos - vecAxisZ * 0.1f;//�c�ړ��X�s�[�h
	}

	///////////////////////////////�O��ړ�///////////////////////

	


	////�o�E���f�B���O�{�b�N�X
	////�v���C���[�̋��E�{�b�N�X�쐬
	////�v���C���[�̍��W����x.y.z��+-0.5f���ŏ����_�ƍő咸�_�����߂Ă�������E�{�b�N�X�̂����蔻��ɑ���
	D3DXVECTOR3 newpos = PlayerPos;//��ŋ��߂��V�������WMovePos��PlayerPos�𑫂������̂�newpos�ɓ����
	D3DXVECTOR3 mina(newpos.x - 0.5f, newpos.y - 0.5f, newpos.z - 0.5f);//�V�������W��x.y.z��-0.5f�������̂�mina�ɓ����
	D3DXVECTOR3 maxa(newpos.x + 0.5f, newpos.y + 0.5f, newpos.z + 0.5f);//�V�������W��x.y.z��+0.5f�������̂�maxa�ɓ����
	PlayerMin = mina;
	PlayerMax = maxa;
	if (PlayerIeBoxAtari == TRUE || PlayerIe2BoxAtari == TRUE)
	{
		//�������Ă���Ɣ��f
		if (PlayerSita == TRUE)
		{
			PlayerPos.z = PlayerPos.z - 0.2f;//�����
			m_Part[0].Position = PlayerPos;//�e�ł���{�f�B�̈ړ����W�ɐV�����ړ����W������
			PlayerSita = FALSE;
		}
		if (PlayerUe == TRUE)
		{
			PlayerPos.z = PlayerPos.z + 0.2f;//�����
			m_Part[0].Position = PlayerPos;//�e�ł���{�f�B�̈ړ����W�ɐV�����ړ����W������
			PlayerUe = FALSE;
		}
		if (PlayerMigi == TRUE)
		{
			PlayerPos.x = PlayerPos.x + 0.2f;//�����
			m_Part[0].Position = PlayerPos;//�e�ł���{�f�B�̈ړ����W�ɐV�����ړ����W������
			PlayerMigi = FALSE;
		}
		if (PlayerHidari == TRUE)
		{
			PlayerPos.x = PlayerPos.x - 0.2f;//�����
			m_Part[0].Position = PlayerPos;//�e�ł���{�f�B�̈ړ����W�ɐV�����ړ����W������
			PlayerHidari = FALSE;
		}
	}
	if (PlayerIeBoxAtari == FALSE && PlayerIe2BoxAtari == FALSE)//����BoxAtariHantei����Ԃ��Ă������e��==FALSE�Ȃ璆�g�����s
	{
		//�������ĂȂ��Ɣ��f
		m_Part[0].Position = PlayerPos;//�e�ł���{�f�B�̈ړ����W�ɐV�����ړ����W������
	}
	//�o�E���f�B���O�{�b�N�X

	for (int i = 0; i < PARTS_NUM; i++)
	{
		D3DXMatrixTranslation(&m_Part[i].Transform, m_Part[i].Position.x, m_Part[i].Position.y, m_Part[i].Position.z);
		D3DXMatrixMultiply(&m_Part[i].World, &m_Part[i].World, &m_Part[i].Transform);
	}
}

//==============
// �@�`��֐�
//==============
void Player::Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v

	for (int Loop = 0; Loop < PARTS_NUM; Loop++)
	{
		pDevice->SetTransform(D3DTS_WORLD, &m_Part[Loop].World);

		//Direct3D�ɂ�����u���b�V���v�́u�����_�����O�v�́u�}�e���A���v����ɂ��Ă��܂��B
		//Direct3D�ɂ�����u�I�u�W�F�N�g�f�[�^�v�́u�`��v�́u�\�ʓI�������v����ɂ��Ă��܂��B
		for (DWORD i = 0; i < m_Part[Loop].dwNumMaterials; i++) //�}�e���A���̐��������[�v����
		{
			pDevice->SetMaterial(&m_Part[Loop].pMeshMaterials[i]);//�}�e���A����ݒ肷��
			pDevice->SetTexture(0, m_Part[Loop].pMeshTextures[i]);//�e�N�X�`����ݒ肷��
			m_Part[Loop].pMesh->DrawSubset(i);//�����_�����O����
		}
	}
}

void Player::ResetParameters(void)//�p�����[�^�̃��Z�b�g
{
	PlayerPos.x = 0.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 0.0f;

	Ykaitenidou = 0.0f;

	m_Key = 2;//�L�[�t���[���̊e���W�̕ϐ�
	m_Frame = 0;//�t���[���Ԃ𓮂������߂̕ϐ�
}
