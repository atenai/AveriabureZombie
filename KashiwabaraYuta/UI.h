#pragma once
//=============================================================================
//  
// UI�̕`��
//
//�@      
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include <Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

#define NUMBER_WIDTH (64)
#define NUMBER_HEIGHT (70)

#define DIG_SCORE (2)

class UI
{
public:
	UI();
	~UI();
	bool Init(void);//�|���S���̏���������
	void Uninit(void);//�|���S���̏I������
	void Update(void);//�|���S���̍X�V����
	void Draw(//�摜��\��
		int texNum,//�g���e�N�X�`��,
		float dx, //�`��ʒuX��
		float dy, //�`��ʒuY��
		int dw, //�e�N�X�`���̕\�����鉡�̒���
		int dh, //�e�N�X�`���̕\������c�̒���
		int tcx, //���̉摜�̐؂���J�n�ꏊ�i���j�i�摜�̍����琔����j
		int tcy, //���̉摜�̐؂���J�n�ꏊ�i�c�j�i�摜�̏ォ�琔����j
		int tcw, //���̉摜�̐؂��肽����
		int tch //���̉摜�̐؂��肽������
	);//�|���S���̕`�揈��

	//�|���S���J���[�̐ݒ�
	void SetPolygonColor(D3DCOLOR color)
	{
		m_color = color;
	}

	void DrawNumber(int n, float x, float y);	//int��0����9�̐����̂ݓ��͂���
	
	//void DrawScore(int �\�������X�R�A�[(����), int �X�R�A�[�̉E�g, float �\��������X���W, float �\��������Y���W, bool �X�R�A�[�̉E�g��0�Ŗ��߂邩�ǂ���)
	void DrawScore(int nScore, int nDig, float x, float y, bool bZero = false);	//nDig�͌���

private:
//===============
//�\���̒�`
//===============
	typedef struct
	{
		D3DXVECTOR4 pos;//���W
		D3DCOLOR color;//�J���[
		D3DXVECTOR2 texcoord;//�e�N�X�`��
	}VERTEX_2D;

	typedef struct
	{
		char fileName[256];
		float width;
		float height;
	}TEXTURE;

	//�e�N�X�`���񋓌^
	typedef enum
	{
		TEX_1 = 0,
		TEX_2,
		TEX_3,
		TEX_4,
		TEX_5,
		TEX_6,
		TEX_7,
		TEX_8,
		TEX_9,
		TEX_10,
		TEX_11,
		TEX_12,
		TEX_13,
		TEX_MAX
	}TEXTURE_NUM;

	D3DCOLOR m_color = D3DCOLOR_RGBA(255, 255, 255, 255);//�v���~�e�B�u�|���S���̐F//�|���S���J���[�̐ݒ�
	LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX] = { NULL };//�����Ŏg���e�N�X�`���̐�����NULL��ǉ����Ȃ��Ƃ����Ȃ�(2)

	TEXTURE m_Texture[TEX_MAX] = //�����Ŏg���e�N�X�`���Ƃ��̉摜�̃T�C�Y����͂���(3)
	{
		{ "data/texture/hurea2.png", 3500, 2333 },//1
		{ "data/texture/hurea4.png", 3500, 2333 },//2
		{ "data/texture/hurea5.png", 3500, 2333 },//3
		{ "data/texture/sousa4.png",1000,500 },//4
		{ "data/texture/Number.png",145,64 },//5
		{ "data/texture/Press_Enter.png", 800, 600 },//6
		{ "data/texture/rekuriteru.png", 500, 500 },//7
		{ "data/texture/Title4.png",800,600 },//8
		{ "data/texture/CLEAR.png", 1280, 720 },//9
		{ "data/texture/FAILED.png", 1280, 720 },//10
		{ "data/texture/title.png", 1280, 720 },//11
		{ "data/texture/hadairo.png", 128, 128 },//12
		{ "data/texture/kuro.png", 300, 300 },//13
	};
};

#endif // _UI_H_