/*========================================================================================

 ファイル分割のmydirect3d[direct3d.cpp]
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
	//1)Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//2)Direct3Dデバイスの取得
	D3DPRESENT_PARAMETERS d3dpp = {};//
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//backbufferの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//backbufferの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//
	d3dpp.BackBufferCount = 1;//backbufferのカウンター
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//入れ替える
	d3dpp.Windowed = TRUE;//
	d3dpp.EnableAutoDepthStencil = TRUE;//深度バッファ・ステンシルバッファを有効にする
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//ステンシルバッファはD
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//セット悪い方　D3DPRESENT_INTERVAL_ONEいい方 D3DPRESENT_INTERVAL_IMMEDIATE


	//デバイス作る
	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pDevice);//三番のところは対象のウィンドウハンドル→ hWnd まずvoid Init(HwND hWnd)　HWND hWnd = CreateWindow();Init(hWnd);

	//マクロ
	if (FAILED(hr) == TRUE) 	//hrが失敗してたら真になる     (SUCCEEDED(hr)) hrが成功したら真になる
	{
		MessageBox(NULL, "出来ません", "エラー4", MB_OK);
		return false;
	}
	return true;
}

void Direct3d_Uninit(void)
{
	//後片付け：先にデバイス→インターフェース
	if (g_pDevice != NULL) {
		g_pDevice->Release();
		g_pDevice = NULL;
	}
	if (g_pD3D != NULL) {
		g_pD3D->Release();//g_pD3Dは住所で、
		g_pD3D = NULL;
	}
	//*SAFE_RELEASEマクロ

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
