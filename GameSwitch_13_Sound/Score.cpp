
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Block.h"
#include "Score.h"
#include "Fade.h"


static unsigned int	g_ScoreTexture;
static int g_Score;
static int data[3];

void InitScore()
{
	g_ScoreTexture = LoadTexture("rom:/number.tga");
}


void UninitScore()
{
	
	UnloadTexture(g_ScoreTexture);
}



void UpdateScore()
{
	g_Score = GetScore();

	if (GetScore() >= 160)
	{
		Fade(SCENE_TITLE);
	}
		

	for (int i = 0; i < KETA; i++)
	{
		data[i] = g_Score / (int)pow(10, KETA-1 - i);
		g_Score = g_Score % (int)pow(10, KETA-1 - i);
	}

	
}



void DrawScore()
{
	SetTexture(g_ScoreTexture);


	for (int i = 0; i < KETA; i++)
	{
		DrawSprite(-800.0f+64.0f*i, -300.0f, 64.0f, 64.0f,
			(data[i] % 5)*0.2f, (data[i] / 5)*0.2f, 0.2f, 0.2f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
