//=======================================================================================
//						�o�E���f�B���O�{�b�N�X�����蔻��`��
//						2017.06.05
//=======================================================================================
#include<Windows.h>//#include<stdio.h>�̑���
#include<d3d9.h>
#include<d3dx9.h>
#include<stdio.h>
#include <math.h>
#include "BoxAtariHantei.h"



BoxAtariHantei::BoxAtariHantei()
{
}


BoxAtariHantei::~BoxAtariHantei()
{
}

void BoxAtariHantei::Init(void)
{

}

void BoxAtariHantei::Uninit(void)
{

}

void BoxAtariHantei::Update(void)
{
	PlayerSita = FALSE;
	PlayerUe = FALSE;
	PlayerMigi = FALSE;
	PlayerHidari = FALSE;
	//�v���C���[�ƉƂ̂����蔻��
	PlayerIeBoxAtari = BoxAtari(
		PlayerMinPos.x, PlayerMinPos.y, PlayerMinPos.z, PlayerMaxPos.x, PlayerMaxPos.y, PlayerMaxPos.z,
		IeMinPos.x, IeMinPos.y, IeMinPos.z, IeMaxPos.x, IeMaxPos.y, IeMaxPos.z
	);
	if (PlayerIeBoxAtari == TRUE)
	{
		if (IeMaxPos.x < PlayerMaxPos.x && IeMinPos.x < PlayerMinPos.x && PlayerMinPos.x < IeMaxPos.x)
		{
			//�v���C���[���E
			PlayerMigi = true;
		}
		if (PlayerMaxPos.x < IeMaxPos.x && PlayerMinPos.x < IeMinPos.x && IeMinPos.x < PlayerMaxPos.x)
		{
			//�v���C���[����
			PlayerHidari = true;
		}
		if (PlayerMinPos.z < IeMaxPos.z && PlayerMinPos.z > IeMinPos.z && PlayerMaxPos.z > IeMaxPos.z)
		{
			//�v���C���[����
			PlayerUe = true;
		}
		if (PlayerMaxPos.z > IeMinPos.z && PlayerMinPos.z < IeMinPos.z && PlayerMaxPos.z < IeMaxPos.z)
		{
			//�v���C���[����
			PlayerSita = true;
		}
	}

	//�v���C���[�Ɖ�2�̂����蔻��
	PlayerIe2BoxAtari = BoxAtari(
		PlayerMinPos.x, PlayerMinPos.y, PlayerMinPos.z, PlayerMaxPos.x, PlayerMaxPos.y, PlayerMaxPos.z,
		Ie2MinPos.x, Ie2MinPos.y, Ie2MinPos.z, Ie2MaxPos.x, Ie2MaxPos.y, Ie2MaxPos.z
	);
	if (PlayerIe2BoxAtari == TRUE)
	{
		if (Ie2MaxPos.x < PlayerMaxPos.x && Ie2MinPos.x < PlayerMinPos.x && PlayerMinPos.x < Ie2MaxPos.x)
		{
			//�v���C���[���E
			PlayerMigi = true;
		}
		if (PlayerMaxPos.x < Ie2MaxPos.x && PlayerMinPos.x < Ie2MinPos.x && Ie2MinPos.x < PlayerMaxPos.x)
		{
			//�v���C���[����
			PlayerHidari = true;
		}
		if (PlayerMinPos.z < Ie2MaxPos.z && PlayerMinPos.z > Ie2MinPos.z && PlayerMaxPos.z > Ie2MaxPos.z)
		{
			//�v���C���[����
			PlayerUe = true;
		}
		if (PlayerMaxPos.z > Ie2MinPos.z && PlayerMinPos.z < Ie2MinPos.z && PlayerMaxPos.z < Ie2MaxPos.z)
		{
			//�v���C���[����
			PlayerSita = true;
		}
	}
}

//�o�E���f�B���O�{�b�N�X(ABB)
//���E�{�b�N�X�̂����蔻��
BOOL BoxAtariHantei::BoxAtari(float Box1MinPosX, float Box1MinPosY, float Box1MinPosZ, float Box1MaxPosX, float Box1MaxPosY, float Box1MaxPosZ,
								float Box2MinPosX, float Box2MinPosY, float Box2MinPosZ, float Box2MaxPosX, float Box2MaxPosY, float Box2MaxPosZ)
{
	//�v���C���[�ƉƂ̂����蔻��

	if (
		(Box1MinPosX < Box2MaxPosX) && (Box1MaxPosX > Box2MinPosX) &&
		(Box1MinPosY < Box2MaxPosY) && (Box1MaxPosY > Box2MinPosY) &&
		(Box1MinPosZ < Box2MaxPosZ) && (Box1MaxPosZ > Box2MinPosZ)
		)
	{
		return TRUE;//�������Ă���
	}
	return FALSE;//�������Ă��Ȃ�
}
//�o�E���f�B���O�{�b�N�X(ABB)