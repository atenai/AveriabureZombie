#pragma once
//=======================================================================================
//						�o�E���f�B���O�{�b�N�X�����蔻��`��
//						2017.06.05
//=======================================================================================

#ifndef _BOXATARIHANTEI_H_
#define _BOXATARIHANTEI_H_
class BoxAtariHantei
{
public:
	BoxAtariHantei();
	~BoxAtariHantei();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Uninit(void);//�I������

	BOOL BoxAtari(float Box1MinPosX, float Box1MinPosY, float Box1MinPosZ, float Box1MaxPosX, float Box1MaxPosY, float Box1MaxPosZ, 
		float Box2MinPosX, float Box2MinPosY, float Box2MinPosZ, float Box2MaxPosX, float Box2MaxPosY, float Box2MaxPosZ);//���E�{�b�N�X�̂����蔻��

	//�Ƃ̍ŏ����_�������Ă���
	void SetIeMin(D3DXVECTOR3 Min)
	{
		IeMinPos = Min;//�Ƃ̍ŏ����_��IeMinPos�ɓ����
	}
	//�Ƃ̍ő咸�_�������Ă���
	void SetIeMax(D3DXVECTOR3 Max)
	{
		IeMaxPos = Max;//�Ƃ̍ő咸�_��IeMaxPos�ɓ����
	}
	//��2�̍ŏ����_�������Ă���
	void SetIe2Min(D3DXVECTOR3 Min)
	{
		Ie2MinPos = Min;//�Ƃ̍ŏ����_��Ie2MinPos�ɓ����
	}
	//��2�̍ő咸�_�������Ă���
	void SetIe2Max(D3DXVECTOR3 Max)
	{
		Ie2MaxPos = Max;//�Ƃ̍ő咸�_��Ie2MaxPos�ɓ����
	}
	//�v���C���[�̍ŏ����_�������Ă���
	void SetPlayerMin(D3DXVECTOR3 Min)
	{
		PlayerMinPos = Min;
	}
	//�v���C���[�̍ő咸�_�������Ă���
	void SetPlayerMax(D3DXVECTOR3 Max)
	{
		PlayerMaxPos = Max;
	}
	//�v���C���[�ƉƂ̂����蔻��̌��ʂ𑗂�
	bool GetPlayerIeBoxAtari()
	{
		return PlayerIeBoxAtari;
	}
	//�v���C���[�Ɖ�2�̂����蔻��̌��ʂ𑗂�
	bool GetPlayerIe2BoxAtari()
	{
		return PlayerIe2BoxAtari;
	}

	bool GetPlayerSita()
	{
		return PlayerSita;
	}
	bool GetPlayerMigi()
	{
		return PlayerMigi;
	}
	bool GetPlayerUe()
	{
		return PlayerUe;
	}
	bool GetPlayerHidari()
	{
		return PlayerHidari;
	}
private:
//*****************************************************************************
// �����o�ϐ�
//*****************************************************************************

//�o�E���f�B���O�{�b�N�X(ABB)
	//��
	D3DXVECTOR3 IeMinPos;//�ŏ����_
	D3DXVECTOR3 IeMaxPos;//�ő咸�_
	//��2
	D3DXVECTOR3 Ie2MinPos;//�ŏ����_
	D3DXVECTOR3 Ie2MaxPos;//�ő咸�_
	//�v���C���[
	D3DXVECTOR3 PlayerMinPos;//�ŏ����_
	D3DXVECTOR3 PlayerMaxPos;//�ő咸�_

	bool PlayerIeBoxAtari = false;
	bool PlayerIe2BoxAtari = false;

	bool PlayerSita = false;
	bool PlayerMigi = false;
	bool PlayerUe = false;
	bool PlayerHidari = false;

};
#endif //_BOXATARIHANTEI_H_
