#include "scene.h"
#include "title.h"
#include "Game.h"
#include "HighScore.h"
#include "texture.h"

//グローバル変数
SCENE g_Scene = SCENE_TITLE;       //今のシーン
SCENE g_NextScene = SCENE_TITLE;   //次のシーン

//関数ポインタ
typedef void(*Func)(void);

static const Func INITS[] = {
	Title_Init,
	Game_Init,
	HighScore_Init,
};

void Scene_Init(void)
{
	//シーンの初期化
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		Game_Init();
		break;

	case SCENE_GAME:
		Game_Init();
		break;

	case SCENE_HIGHSCORE:

		Game_Init();
		HighScore_Init();
		break;

	}
	Texture_Load();
}

void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();

		break;

	case SCENE_GAME:
		Game_Update();
		break;

	case SCENE_HIGHSCORE:
		HighScore_Update();
		break;

	}
	
}

void Scene_Draw(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;

	case SCENE_GAME:
		Game_Draw();
		break;

	case SCENE_HIGHSCORE:

		HighScore_Draw();
		break;

	}

}

void Scene_Uninit(void)
{
	texture_Destroy();
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();
		break;

	case SCENE_GAME:
		Game_Uninit();
		break;

	case SCENE_HIGHSCORE:

		HighScore_Uninit();
		break;

	}

}

void Scene_SetNextScene(SCENE next_scene)
{
	g_NextScene = next_scene;
}

bool Scene_Change(void) //bool→アプリケーションの終了時true
{
	if (g_Scene != g_NextScene)
	{
		Scene_Uninit();
		if (g_NextScene == SCENE_END)
		{
			return true;
		}
		Scene_Init();
		g_Scene = g_NextScene;
		
	}
	return false;
}