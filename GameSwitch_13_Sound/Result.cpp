#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "Block.h"
#include "Score.h"
#include "Result.h"

static unsigned int	g_ResultTexture;
static int g_Score;
static int data[3];


void InitResult()
{
	g_ResultTexture = LoadTexture("rom:/Fade.tga");
}

void UninitResult()
{
	UnloadTexture(g_ResultTexture);
}

void UpdateResult()
{
	/*g_Score = GetScore();


	for (int i = 0; i < KETA; i++)
	{
		data[i] = g_Score / (int)pow(10, KETA - 1 - i);
		g_Score = g_Score % (int)pow(10, KETA - 1 - i);
	}*/

	if (GetControllerPress(NpadButton::Plus::Index))
	{
		SetScene(SCENE_TITLE);

	}

}
void DrawResult()
{
	/*SetTexture(g_ResultTexture);

	for (int i = 0; i < KETA; i++)
	{
		DrawSprite(-256.0f+ 256.0f*i, 0.0f, 256.0f, 256.0f,
			(data[i] % 5)*0.2f, (data[i] / 5)*0.2f, 0.2f, 0.2f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}*/
	SetTexture(g_ResultTexture);
	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
}