#include <d3d9.h>
#include <d3dx9.h>

#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#define BG_MAX (2)

int tex_BG;
BG g_BG[BG_MAX] = {};
static float BG_y;

void BG_Init(void)
{
	BG_y = 0;
	for (int i = 0; i < BG_MAX; i++)
	{
		g_BG[i].used = true;
	}
	tex_BG = Texture_SetLoadFile("Accet\\Texture\\bg.png", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void BG_Uninit(void)
{
	texture_Destroy();
}

void BG_Update(void)
{
	/*if (BG_y < SCREEN_HEIGHT)
	{
		BG_y++;
	if (BG_y >= SCREEN_HEIGHT)
		{
			BG_y = 0;
		}
	}*/
	BG_y += 2.0f;
}

void BG_Draw(void)
{
	for (int i = 0; i < BG_MAX; i++)
	{
		if (g_BG[i].used)
		{
			Sprite_Draw(tex_BG, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 - BG_y, SCREEN_WIDTH, SCREEN_HEIGHT + BG_y, 0.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 1, 1);
		}
	}
}