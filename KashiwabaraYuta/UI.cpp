//=============================================================================
//  
// UI�̕`��
//2D�摜��\������ׂ�
//SetPolygonColor();//�|���S���J���[�̐ݒ�
//DrawPolygon();//�|���S���̐ݒ�
//��2���g���וK�v
//
//=============================================================================
#include "UI.h"
#include "Renderer.h"

//FVF�̐錾(�萔)
//���W			//�J���[		//�e�N�X�`��
#define FVF_VERTEX_2D  (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//�ݒ�


UI::UI()
{
}


UI::~UI()
{
}

//UI�̏���������
bool UI::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v
	if (pDevice == NULL)
	{
		return false;
	}

	//�e�N�X�`��
	HRESULT hr;

	for (int Loop = 0; Loop < TEX_MAX; Loop++)
	{
		//�e�N�X�`���𐶐�����֐�//������Ȃ�
		hr = D3DXCreateTextureFromFile(pDevice, m_Texture[Loop].fileName, &m_pTexture[Loop]);
		//�G���[�`�F�b�N
		if (FAILED(hr))
		{
			MessageBox(NULL, "UI�e�N�X�`�����ǂݍ��߂܂���", "�G���[", MB_OK);
			return false;
		}

	}

	////�A���t�@�u�����f�B���O
	////�����_�[�X�e�[�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h�J�n
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	////
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////�t�B���^�����O
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//�A���t�@�u�����h�I��//2018/12/12/add

	return true;
}

//UI�̏I������
void UI::Uninit(void)//������Ȃ�
{

	for (int Loop = TEX_1; Loop < TEX_MAX; Loop++)
	{
		if (m_pTexture[Loop] != NULL)
		{
			m_pTexture[Loop]->Release();
			m_pTexture[Loop] = NULL;
		}
	}


}

//UI�̍X�V����
void UI::Update(void)
{

}

//UI�̕`�揈��
void UI::Draw(int texNum, float dx, float dy, int dw, int dh, int tcx, int tcy, int tcw, int tch)//�摜��\��
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();//main.h//pDevice���g���ꍇ���ꂪ�K�v
	if (pDevice == NULL)
	{
		return;
	}

	//////////////////�������火�̒��g��������/////////////////////////////////

	float tw = m_Texture[texNum].width;
	float th = m_Texture[texNum].height;

	float u0 = (float)tcx / (float)tw;
	float v0 = (float)tcy / (float)th;
	float u1 = (float)(tcx + tcw) / (float)tw;
	float v1 = (float)(tcy + tch) / (float)th;


	//�@�|���S���̕`�揈��
	VERTEX_2D vtx[] = {//D3DPT_TRIANGLESTRIP
		{ D3DXVECTOR4(dx + 0.0f - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u0, v0) },//����
		{ D3DXVECTOR4(dx + dw - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u1, v0) },//�E��
		{ D3DXVECTOR4(dx + 0.0f - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u0, v1) },//����
		{ D3DXVECTOR4(dx + dw - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f), m_color, D3DXVECTOR2(u1, v1) },//�E��
	};

	//�@FVF�i������g�p���钸�_���j�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̓\��t��
	pDevice->SetTexture(0, m_pTexture[texNum]);

	//3D�`���OFF�ɂ��ā�2D�`��������܂�3D�`���ON�ɂ���//��������鎖��UI��\���\
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);//3D�`���FALSE�ɂ���(OFF)


	//�A���t�@�u�����f�B���O
	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h�J�n
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//�t�B���^�����O
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//�A���t�@�u�����f�B���O



	//�v���~�e�B�u
	pDevice->DrawPrimitiveUP//���ꂪ�Ă΂�Ȃ��ƃ|���S�����`��ł��Ȃ�
	(
		D3DPT_TRIANGLESTRIP,//�g���C�A���O���X�g���b�v//�|���S�����ǂ̂悤�ɕ\�����邩
		2,//�O�p�`�̖ʂ�2�\������//�\������ʂ̐��������
		&vtx[0],//VERTEX_2D vtx[] = {};�ō�������e��0�Ԗڂ���Ăяo��
		sizeof(VERTEX_2D)//���ō�����T�C�Y���Ăяo��
	);




	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);//�A���t�@�u�����h�I��//2018/12/12/add



	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);//3D�`���TRUE�ɂ���(ON)
	////////////////�������灪�̒��g��������/////////////////////////////////////

}

//void DrawNumber(int �\��������, float �\������X���W, float �\������Y���W)
void UI::DrawNumber(int n, float x, float y)
{
	int nX = 0, nY = 0;
	if (n < 0 || n>9)
	{
		return;
	}
	if (n > 4)
	{
		nX = n - 5;
		nY = 1;
	}
	else
	{
		nX = n;
		nY = 0;
	}
	SetPolygonColor(D3DCOLOR_RGBA(150, 150, 150, 255));//�|���S���J���[�̐ݒ�
	Draw(4, x, y, NUMBER_WIDTH, NUMBER_HEIGHT, 0 + 29 * nX, 0 + 32 * nY, 29, 32);//�e�N�X�`���̕`��
}

//void DrawScore(int �\�������X�R�A�[(����), int �X�R�A�[�̉E�g, float �\��������X���W, float �\��������Y���W, bool �X�R�A�[�̉E�g��0�Ŗ��߂邩�ǂ���)
void UI::DrawScore(int nScore, int nDig, float x, float y, bool bZero)
{
	//���l��
	if (nDig < 0)//nDig��0��菬�����Ƃ�
	{
		nDig = 0;//nDig��0
		for (;;)//�������[�v
		{
			nScore /= 10;//nScore ��= 10
			if (nScore == 0)//����nScore��0�Ȃ�
			{
				break;
			}
			nDig++;
		}
	}

	//�J���X�g�l
	int maxScore = 10;

	for (int i = 1; i < nDig; i++)
	{
		maxScore *= 10;
	}
	maxScore--;

	nScore = min(maxScore, nScore);

	for (int i = 1; i <= nDig; i++)
	{
		int n = nScore % 10;
		DrawNumber(n, x + NUMBER_WIDTH * (nDig - i), y);
		nScore /= 10;
		if (nScore == 0 && !bZero)
		{
			break;
		}
	}
}