/*========================================================================================

A Cat.game[main.cpp]
								Author:Koi
								Data:2019/05/07
　　　　　　　　　　　　　　　　　　　・
				   　　　　　　　　　 ・
							          ・
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


			定数定義

---------------------------------------------------------------------------------------*/

#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "ウィンドウ表示処理"


#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^(WS_THICKFRAME|WS_MAXIMIZEBOX))
#define FPS_MEASUREMENT_TIME (1.0f)


//XとYとZとRHWをも1つ頂点データを表す　RHWはNSダメです 必ず頂点構造体の下に書く
#define SCREEN_VERTEX_UNTEX *pVertices = new SCREEN_VERTEX_UNTEX[2 * D3DX_PI * nRadius];

/*--------------------------------------------------------------------------------------


			   プロトタイプ宣言


----------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static bool Init(HWND hWnd);//初期化
static void Uninit(void);//終了処理関数
static void Update(void);//ゲームの更新
static void Draw(void);//ゲームの画面

/*---------------------------------------------------------------------------------------


           グローバル変数
			  
-----------------------------------------------------------------------------------------*/
static LPDIRECT3DDEVICE9 g_pDevice = NULL;




static int g_FrameCount = 0;//フレームカウンター
static int g_FPSBaseFrameCount = 0;//FPS計測（けいそく）の基となるフレームカウンター
static double g_FPSBaseTime = 0.0;//FPS計測（けいそく）の基となる時間
static double g_StaticFrameTime = 0.0;//フレーム固定用計測時間
static float g_FPS = 0.0f;//FPS

/*--------------------------------------------------------------------------------------

	　　　　　  メイン

----------------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = {};//wcは変数名　={}全部初期化（=0より便利　＝ ={0})
	wc.lpfnWndProc = WndProc;//wc.lpfnWndProcはウィンドウプロシージャ（chuangkou chengxu）の登録　WndProcは関数ポインタ　受け取るの関数
	wc.lpszClassName = CLASS_NAME;//wc.lpszClassName = "クラス名";
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);//オリジナルクラス登録する　　&：アドレス　→　WNDCLASS　の情報を入れる

	//ウィンドウの設定

	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//left,top,right,bottom

	AdjustWindowRect(&window_rect,
		WS_OVERLAPPEDWINDOW,
		FALSE //MENUない
	);

	int window_width = window_rect.right - window_rect.left;//白いのタイトルを含む
	int window_height = window_rect.bottom - window_rect.top;//白いのタイトルを含む（ふくむ）
	


/*---------------------------------------------------

プライマリモニターの画面解像度の取得

------------------------------------------------------*/

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

/*---------------------------------------------------

ウィンドウまんなかのため

-----------------------------------------------------*/

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd = CreateWindow(
		CLASS_NAME,//クラス名
		WINDOW_CAPTION,//ウィンドウタイトル
		WINDOW_STYLE,//ウィンドウのサイズ：上の白いタイトルを含む
		window_x,//ポジションのX 
		window_y,//ポジションのY  
		window_width,//ウィンドウの幅 
		window_height,//ウィンドウの高さ 
		NULL,
		NULL,
		hInstance,//
		NULL
	);

	
	ShowWindow(hWnd, nCmdShow);//ウィンドウ表示する
	UpdateWindow(hWnd);//ウィンドウ更新する

	Keyboard_Initialize(hInstance, hWnd);

	/*---------------------------------------------------

				  ゲームループ

	-----------------------------------------------------*/
	MSG msg = {};
	//Init(hWnd);
	if (!Init(hWnd)) {
		return -1;
	}
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//メッセージ処理
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
				//ゲーム処理
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
	case WM_KEYDOWN://keyの入力したん
		if (wParam == VK_ESCAPE) {//
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);//ウィンドウ閉じる
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
		//読み込みに失敗したやつがいる
		MessageBox(NULL, "LOAD出来ない", "エラー", MB_OK);
		return false;

	}
	
	
	SystemTimer_Initialize();//システムタイマーの初期化

	
	SystemTimer_Start();//システムタイマーの起動

	//FPS計測用変数群の初期化
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
	

	
	g_FrameCount++;//フレームカウントの更新
	
	double time = SystemTimer_GetTime();//現在のシステム時間の取得（しゅとく）

	//前回のFPS計測時間から規定（きてい）時間経っていたらFPS計測
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME)
	{
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));  //FPSの計算（前回からの経過（けいか）フレーム　/　経過時間）

		g_FPSBaseFrameCount = g_FrameCount;                  //FPS計測の基になる変数を更新
		g_FPSBaseTime = time;                                //FPS計測の基になる変数を更新
	}
}

void Draw(void)
{

	//画面のクリア
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);

	//頂点データを用意する

	g_pDevice->BeginScene();//描く *DrawのBeginScene~EndScene
	
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンドを有効にする
	//今から描画するRGB x 今から描画するα + 画面のRGB x (1- 今から描画するα)*値は１～0
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	Scene_Draw();
	Fade_Draw();

	//Game_Draw();
	DebugFont_Draw(2.0f, 2.0f, "%f", g_FPS);

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);//一回だけ書く　BeginとEnd何回でもいい

	
}

