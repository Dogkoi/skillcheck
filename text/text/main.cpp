/*========================================================================================

A Cat.game[main.cpp]
								Author:Koi
								Data:2019/05/07
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�E
				   �@�@�@�@�@�@�@�@�@ �E
							          �E
								Data:2019/09/25
=========================================================================================*/

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "common.h"
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "system_timer.h"
#include "debug_font.h"
#include "PatternAnim.h"
#include "input.h"
#include "Game.h"
#include "sound.h"
#include "scene.h"
#include "title.h"
#include "fade.h"

/*---------------------------------------------------------------------------------------


			�萔��`

---------------------------------------------------------------------------------------*/

#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "�E�B���h�E�\������"


#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^(WS_THICKFRAME|WS_MAXIMIZEBOX))
#define FPS_MEASUREMENT_TIME (1.0f)


//X��Y��Z��RHW����1���_�f�[�^��\���@RHW��NS�_���ł� �K�����_�\���̂̉��ɏ���
#define SCREEN_VERTEX_UNTEX *pVertices = new SCREEN_VERTEX_UNTEX[2 * D3DX_PI * nRadius];

/*--------------------------------------------------------------------------------------


			   �v���g�^�C�v�錾


----------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static bool Init(HWND hWnd);//������
static void Uninit(void);//�I�������֐�
static void Update(void);//�Q�[���̍X�V
static void Draw(void);//�Q�[���̉��

/*---------------------------------------------------------------------------------------


           �O���[�o���ϐ�
			  
-----------------------------------------------------------------------------------------*/
static LPDIRECT3DDEVICE9 g_pDevice = NULL;




static int g_FrameCount = 0;//�t���[���J�E���^�[
static int g_FPSBaseFrameCount = 0;//FPS�v���i���������j�̊�ƂȂ�t���[���J�E���^�[
static double g_FPSBaseTime = 0.0;//FPS�v���i���������j�̊�ƂȂ鎞��
static double g_StaticFrameTime = 0.0;//�t���[���Œ�p�v������
static float g_FPS = 0.0f;//FPS

/*--------------------------------------------------------------------------------------

	�@�@�@�@�@  ���C��

----------------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = {};//wc�͕ϐ����@={}�S���������i=0���֗��@�� ={0})
	wc.lpfnWndProc = WndProc;//wc.lpfnWndProc�̓E�B���h�E�v���V�[�W���ichuangkou chengxu�j�̓o�^�@WndProc�͊֐��|�C���^�@�󂯎��̊֐�
	wc.lpszClassName = CLASS_NAME;//wc.lpszClassName = "�N���X��";
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);//�I���W�i���N���X�o�^����@�@&�F�A�h���X�@���@WNDCLASS�@�̏�������

	//�E�B���h�E�̐ݒ�

	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//left,top,right,bottom

	AdjustWindowRect(&window_rect,
		WS_OVERLAPPEDWINDOW,
		FALSE //MENU�Ȃ�
	);

	int window_width = window_rect.right - window_rect.left;//�����̃^�C�g�����܂�
	int window_height = window_rect.bottom - window_rect.top;//�����̃^�C�g�����܂ށi�ӂ��ށj
	


/*---------------------------------------------------

�v���C�}�����j�^�[�̉�ʉ𑜓x�̎擾

------------------------------------------------------*/

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

/*---------------------------------------------------

�E�B���h�E�܂�Ȃ��̂���

-----------------------------------------------------*/

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd = CreateWindow(
		CLASS_NAME,//�N���X��
		WINDOW_CAPTION,//�E�B���h�E�^�C�g��
		WINDOW_STYLE,//�E�B���h�E�̃T�C�Y�F��̔����^�C�g�����܂�
		window_x,//�|�W�V������X 
		window_y,//�|�W�V������Y  
		window_width,//�E�B���h�E�̕� 
		window_height,//�E�B���h�E�̍��� 
		NULL,
		NULL,
		hInstance,//
		NULL
	);

	
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�\������
	UpdateWindow(hWnd);//�E�B���h�E�X�V����

	Keyboard_Initialize(hInstance, hWnd);

	/*---------------------------------------------------

				  �Q�[�����[�v

	-----------------------------------------------------*/
	MSG msg = {};
	//Init(hWnd);
	if (!Init(hWnd)) {
		return -1;
	}
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			double time = SystemTimer_GetTime();
			if (time - g_StaticFrameTime < 1.0 / 60.0)
			{
				Sleep(0);
			}
			else
			{
				g_StaticFrameTime = time;
				//�Q�[������
				Update();
				Draw();
				if (Scene_Change())
				{
					break;
				}

			}
			
		}
	}
	Uninit();
	return (int)msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN://key�̓��͂�����
		if (wParam == VK_ESCAPE) {//
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);//�E�B���h�E����
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


bool Init(HWND hWnd)
{
	Direct3d_Init(hWnd);

	g_pDevice = GetDevice();

	DebugFont_Initialize();
	
	//PatternAnim_Init();
	Sprite_Init();

	InitSound(hWnd);


	Fade_Init();
	Scene_Init();


	if (Texture_Load() < 0)
	{
		//�ǂݍ��݂Ɏ��s�����������
		MessageBox(NULL, "LOAD�o���Ȃ�", "�G���[", MB_OK);
		return false;

	}
	
	
	SystemTimer_Initialize();//�V�X�e���^�C�}�[�̏�����

	
	SystemTimer_Start();//�V�X�e���^�C�}�[�̋N��

	//FPS�v���p�ϐ��Q�̏�����
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFrameTime = g_FPSBaseTime;

	return true;
}


void Uninit(void)
{
	Direct3d_Uninit();
	DebugFont_Finalize();
	Keyboard_Finalize();
	Sprite_Uninit();
	Scene_Uninit();
	Fade_Uninit();
	//Game_Uninit();
	UninitSound();
}

bool text = false;
bool ro = true;

void Update(void)
{
	Keyboard_Update();
	Fade_Update();
	Scene_Update();
	//Game_Update();
	

	
	g_FrameCount++;//�t���[���J�E���g�̍X�V
	
	double time = SystemTimer_GetTime();//���݂̃V�X�e�����Ԃ̎擾�i����Ƃ��j

	//�O���FPS�v�����Ԃ���K��i���Ă��j���Ԍo���Ă�����FPS�v��
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME)
	{
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));  //FPS�̌v�Z�i�O�񂩂�̌o�߁i�������j�t���[���@/�@�o�ߎ��ԁj

		g_FPSBaseFrameCount = g_FrameCount;                  //FPS�v���̊�ɂȂ�ϐ����X�V
		g_FPSBaseTime = time;                                //FPS�v���̊�ɂȂ�ϐ����X�V
	}
}

void Draw(void)
{

	//��ʂ̃N���A
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);

	//���_�f�[�^��p�ӂ���

	g_pDevice->BeginScene();//�`�� *Draw��BeginScene~EndScene
	
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h��L���ɂ���
	//������`�悷��RGB x ������`�悷�郿 + ��ʂ�RGB x (1- ������`�悷�郿)*�l�͂P�`0
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	Scene_Draw();
	Fade_Draw();

	//Game_Draw();
	DebugFont_Draw(2.0f, 2.0f, "%f", g_FPS);

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);//��񂾂������@Begin��End����ł�����

	
}

