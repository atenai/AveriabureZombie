#pragma once
//=============================================================================
//  
// �񕜃A�C�e���}�[�J�[
//
//=============================================================================
#ifndef _RECOVERYITEMMARKER_H_
#define _RECOVERYITEMMARKER_H_
#include "RecoveryItem.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }//�������J�������ۃN���b�V�����Ȃ��悤�Ƀ`�F�b�N���鏈��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)//CreateVertexBuffer�ȂǗp�̒��_�̐����ݒ�

class RecoveryItemMarker
{
public:
	RecoveryItemMarker();
	~RecoveryItemMarker();
	void Init(void);//����������
	void Update(void);//�X�V����
	void Draw(void);//�摜��\��
	void Uninit(void);//�I������
	void ResetParameters(void);//�p�����[�^�̃��Z�b�g
	//�A�C�e���}�[�J�[���W�����Ă���
	void SetPos(int num, float x, float y, float z)
	{
		m_RecoveryItemMarker[num].Pos.x = x;
		m_RecoveryItemMarker[num].Pos.y = y;
		m_RecoveryItemMarker[num].Pos.z = z;
	}
	//�A�C�e���}�[�J�[�̕`���Ԃ������Ă���
	void SetRecoveryItemMarkerDraw(int num, bool draw)
	{
		m_RecoveryItemMarker[num].Draw = draw;
	}
private:
	//*****************************************************************************
	// �\����
	//*****************************************************************************
	//�݌v�}�����
	typedef struct  //�\���̂̒�`
	{
		FLOAT x, y, z;
		DWORD color;
		D3DXVECTOR2 texcoord;//�e�N�X�`���\��t�����W
	}CUSTOMVERTEX;

	typedef struct  //�\���̂̒�`
	{
		CUSTOMVERTEX vertices[4];//�\���̂̍\����
		D3DXMATRIX mtxworld;
		D3DXMATRIX mtxworldT;
		float Scale;//����̑傫��
		D3DXVECTOR3 Pos;
		bool Draw;//�`����
	}ITEMMARKER;

	ITEMMARKER m_RecoveryItemMarker[RECOVERYITEM_NUM];

	//*****************************************************************************
	// �����o�ϐ�
	//*****************************************************************************

	LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`��������ϐ�
};

#endif // _RECOVERYITEMMARKER_H_