#include <d3d9.h>
#include <d3dx9.h>

#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "Enemy.h"
#include "Bullet.h"

#define ENEMY_MAX (1000)

int tex_enemy[5];
float espeed = 3.0f;
static Enemy g_Enemys[ENEMY_MAX] = {};
static float speed = 0.0f;
static float x = 0.0f;
static float y = 0.0f;
static int count = 0;
static bool right = true;

void Enemy_Init(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemys[i].IsUsed = false;
	//	g_Enemys[i].g_Ecollision.radius =50;
	}
	
	tex_enemy[0] = Texture_SetLoadFile("Accet\\texture\\fish2.png", 100, 100);
	tex_enemy[1] = Texture_SetLoadFile("Accet\\texture\\fish1.png", 107, 170);
	tex_enemy[2] = Texture_SetLoadFile("Accet\\texture\\fish3.png", 135, 135);
}

void Enemy_Uninit(void)
{
	texture_Destroy();

}

void Enemy_Update(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemys[i].IsUsed)
		{
			continue;
		}

		switch (g_Enemys[i].type)
		{
		case ENEMY_FISH1:
			x = 1.0f;
			y = 2.0f;
			speed = 5.0f;
			if (g_Enemys[i].hp <= 0)
			{
				g_Enemys[i].IsUsed = false;
			}
			if (count > 0 && count % 50 == 0)
			{
				//Bullet_Create(g_Enemys[i].position.x, g_Enemys[i].position.y + 50);
			}
			break;

		case ENEMY_FISH2:
			x = 3.0f;
			y = 1.5f;
			speed = 8.0f;
			if (g_Enemys[i].hp <= 0)
			{
				g_Enemys[i].IsUsed = false;
			}
			if (count > 0 && count % 50 == 0)
			{
				//Bullet_Create(g_Enemys[i].position.x, g_Enemys[i].position.y + 50);

			}
			break;

		case ENEMY_FISH3:
			
			y = 2.5f;
			speed = 15.0f;

			if (right)
			{
				x = 0.3f;
			}
			if (!right)
			{
				x = -0.3f;
			}

			if (g_Enemys[i].position.x >= 1200)
			{
				right = false;
			}
			if (g_Enemys[i].position.x <= 50)
			{
				right = true;
			}

			if (g_Enemys[i].position.y >= 150)
			{
				g_Enemys[i].position.y = 150;
			}
			if (g_Enemys[i].hp <= 0)
			{
				g_Enemys[i].IsUsed = false;
			}
			if (count > 0 && count % 50 == 0)
			{
				//Bullet_Create(g_Enemys[i].position.x, g_Enemys[i].position.y + 50);

			}
			break;

		}
		//敵の座標の更新
		D3DXVECTOR2 dir(x, y);
		dir += D3DXVECTOR2(x, y);

		D3DXVec2Normalize(&dir, &dir);//ベクトルの正規化
		D3DXVECTOR2 vecSpeed = dir * speed;
		g_Enemys[i].position += vecSpeed;
		g_Enemys[i].g_Ecollision.position = g_Enemys[i].position;

		if (g_Enemys[i].position.y > SCREEN_HEIGHT + 34)
		{
			g_Enemys[i].IsUsed = false;
		}
		if (g_Enemys[i].position.y < 0)
		{
			g_Enemys[i].IsUsed = false;
		}
		if (g_Enemys[i].position.x > SCREEN_WIDTH + 50)
		{
			g_Enemys[i].IsUsed = false;
		}
		if (g_Enemys[i].position.x < -50)
		{
			g_Enemys[i].IsUsed = false;
		}

	}
	

	count++;

}

void Enemy_Draw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemys[i].IsUsed)
		{
			switch (g_Enemys[i].type)
			{
			case ENEMY_FISH1:
				Sprite_Draw(tex_enemy[0], g_Enemys[i].position.x, g_Enemys[i].position.y, 0, 0, 100, 100, 0, g_Enemys[i].position.x, g_Enemys[i].position.y, 0.5, 0.5);
				break;
			case ENEMY_FISH2:
				Sprite_Draw(tex_enemy[1], g_Enemys[i].position.x, g_Enemys[i].position.y, 0, 0, 107, 170, 0, g_Enemys[i].position.x, g_Enemys[i].position.y, 0.5, 0.5);
				break;
			case ENEMY_FISH3:
				Sprite_Draw(tex_enemy[2], g_Enemys[i].position.x, g_Enemys[i].position.y, 0, 0, 135, 135, 0, g_Enemys[i].position.x, g_Enemys[i].position.y, 0.5, 0.5);
				break;
			}
		}
	}
	
}
void Enemy_Create(float x, float y, ENEMY_TYPE type)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemys[i].IsUsed)
		{
			g_Enemys[i].IsUsed = true;
			g_Enemys[i].position.x = x;
			g_Enemys[i].position.y = y;
			g_Enemys[i].type = type;

			switch (g_Enemys[i].type)
			{
			case ENEMY_FISH1:
				g_Enemys[i].hp = 2;
				g_Enemys[i].g_Ecollision.radius = 50;
				break;
			case ENEMY_FISH2:
				g_Enemys[i].hp = 1;
				g_Enemys[i].g_Ecollision.radius = 25;
				break;
			case ENEMY_FISH3:
				g_Enemys[i].hp = 5;
				g_Enemys[i].g_Ecollision.radius = 70;
				break;
			}
		//	g_Enemys[i].g_Ecollision.position;
			break;
		}

	}
	
}

bool Enemy_IsUsed(int index)
{
	return g_Enemys[index].IsUsed;
}

void Enemy_Destroy(int index)
{
	g_Enemys[index].IsUsed = false;

}

CirCle* Enemy_GetCollision(int index)
{
	return &g_Enemys[index].g_Ecollision;
}

Enemy* GetEnemyposition(void)
{
	return &g_Enemys[0];
}

void hpminus(int n)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemys[i].hp -= n;
	}
}