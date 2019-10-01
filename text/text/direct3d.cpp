/*========================================================================================

 �t�@�C��������mydirect3d[direct3d.cpp]
								Author:Koi
							
								Data:2019/06/05
=========================================================================================*/
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"

#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

bool Direct3d_Init(HWND hWnd)
{
	//1)Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//2)Direct3D�f�o�C�X�̎擾
	D3DPRESENT_PARAMETERS d3dpp = {};//
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//backbuffer�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//backbuffer�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//
	d3dpp.BackBufferCount = 1;//backbuffer�̃J�E���^�[
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//����ւ���
	d3dpp.Windowed = TRUE;//
	d3dpp.EnableAutoDepthStencil = TRUE;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@��L���ɂ���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�X�e���V���o�b�t�@��D
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//�Z�b�g�������@D3DPRESENT_INTERVAL_ONE������ D3DPRESENT_INTERVAL_IMMEDIATE


	//�f�o�C�X���
	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pDevice);//�O�Ԃ̂Ƃ���͑Ώۂ̃E�B���h�E�n���h���� hWnd �܂�void Init(HwND hWnd)�@HWND hWnd = CreateWindow();Init(hWnd);

	//�}�N��
	if (FAILED(hr) == TRUE) 	//hr�����s���Ă���^�ɂȂ�     (SUCCEEDED(hr)) hr������������^�ɂȂ�
	{
		MessageBox(NULL, "�o���܂���", "�G���[4", MB_OK);
		return false;
	}
	return true;
}

void Direct3d_Uninit(void)
{
	//��Еt���F��Ƀf�o�C�X���C���^�[�t�F�[�X
	if (g_pDevice != NULL) {
		g_pDevice->Release();
		g_pDevice = NULL;
	}
	if (g_pD3D != NULL) {
		g_pD3D->Release();//g_pD3D�͏Z���ŁA
		g_pD3D = NULL;
	}
	//*SAFE_RELEASE�}�N��

}

void Direct3d_Update(void)
{

}
void Direct3d_Draw(void)
{

}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pDevice;
}
