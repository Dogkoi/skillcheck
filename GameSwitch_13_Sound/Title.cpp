#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "Title.h"
#include "Fade.h"
#include "sound.h"

static unsigned int	g_TitleTexture;


void InitTitle()
{
	g_TitleTexture = LoadTexture("rom:/title.tga");
}

void UninitTitle()
{
	UnloadTexture(g_TitleTexture);
}
void UpdateTitle()
{
	if (GetControllerPress(NpadButton::A::Index))
	{
		Fade(SCENE_GAME);
		PlaySE(STRM_BGM_GAME);
	}
}
void DrawTitle()
{
	SetTexture(g_TitleTexture);

	DrawSprite(0.0f, 0.0f, 1920.0f, 1080.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
}