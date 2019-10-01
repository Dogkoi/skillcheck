
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Collision.h"
#include "ball.h"
#include "Explosion.h"
#include "Block.h"


unsigned int	g_ExplosionTexture;

EXPLOSION		g_Explosion[EXPLOSION_MAX];






void InitExplosion()
{

	g_ExplosionTexture = LoadTexture("rom:/explosion.tga");

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Use = false;
	}
}



void UninitExplosion()
{

	UnloadTexture(g_ExplosionTexture);

}


void UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{

		if (g_Explosion[i].Use == true)
		{
			g_Explosion[i].frame++;
		}

		if (g_Explosion[i].frame == 16)
		{
			g_Explosion[i].Use = false;
			g_Explosion[i].frame = 0;
		}


	}
}



void DrawExplosion()
{

	SetTexture(g_ExplosionTexture);

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].Use == true)
		{
			DrawSprite(g_Explosion[i].Position.x, g_Explosion[i].Position.y, 128.0f, 128.0f,
				(g_Explosion[i].frame % 4 )* 0.25f, (g_Explosion[i].frame / 4)* 0.25f, 0.25f, 0.25f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}


void SetExplosion(float x, float y)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].Use == false)
		{
			g_Explosion[i].Position.x = x;
			g_Explosion[i].Position.y = y;
			g_Explosion[i].Use = true;
			g_Explosion[i].frame = 0;
			break;
		}
	}

}


EXPLOSION *GetExplosion()
{
	return g_Explosion;
}