#pragma once
//=============================================================================
//  
// �����_���[(DirectX)�̕`��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
//*****************************************************************************
// ���N���X
//*****************************************************************************
//�����_���[(DirectX)�N���X
//static�����Ȃ��ƃG���[���o��
class Renderer
{
public:
	Renderer();//�R���X�g���N�^
	~Renderer();//�f�X�g���N�^

	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);//����������
	static void Uninit(void);//�I������

	static void DrawBegin();//�����_���[(DirectX)�̕`�揈���J�n
	static void DrawEnd();//�����_���[(DirectX)�̕`�揈���I��

	static LPDIRECT3DDEVICE9 GetDevice();//Direct3D�f���@�C�X�𑗂�֐�
private:
	static LPDIRECT3D9			pD3d;//Direct3D�C���^�[�t�F�C�X
	static LPDIRECT3DDEVICE9	pDevice;	//Direct3D�f���@�C�X

};
#endif // _RENDERER_H_
