/*========================================================================================

      進撃のボール[main.cpp]
                               Author:Koi(AT-12E-353 TAN LINA)
                               Last Data:2019/09/10
=========================================================================================*/
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "Title.h"
#include "Result.h"
#include "Fade.h"
#include "sound.h"
#include "game.h"


void Init();
void Uninit();
void Update();
void Draw();


SCENE g_Scene = SCENE_NONE;


extern "C" void nnMain()
{
	Init();

    while( true )
	{
		Update();
		Draw();
	}

	Uninit();
}



void Init()
{
	InitSound();
	InitSystem();
	InitController();
	InitFade();
	Fade(SCENE_TITLE);
	PlayBGM(STRM_CYLINDER);
}


void Uninit()
{
	Fade(SCENE_NONE);
	UninitFade();
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	}
	UninitController();
	UninitSystem();
	UninitSound();

}


void Update()
{
	UpdateController();
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();
	UpdateSound();
}


void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();
	SwapBuffers();
}




void SetScene(SCENE Scene)
{
	//uninit
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	}
	g_Scene = Scene;
	
	//init
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	}

}



