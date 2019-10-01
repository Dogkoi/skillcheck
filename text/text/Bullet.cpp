#include <d3d9.h>
#include <d3dx9.h>

#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "Bullet.h"
#include "Collision.h"
#include "effect.h"



//グローバル変数
int tex_bullet;//テクスチャ用
static Bullet g_Bullets[BULLET_MAX] = {};
float bspeed = 10.0f;

void Bullet_Init(void)
{
	//g_Bullets全てのusedフラグをfalseにする

	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].IsUsed = false;
		g_Bullets[i].g_collision.radius = 11;

	}
	//弾の初期化
	//tex_bullet = Texture_SetLoadFile("Accet\\Texture\\tama.png", 21, 59);
	tex_bullet = Texture_SetLoadFile("Accet\\Texture\\bullet000.png", 20, 20);
}

void Bullet_Uninit(void)
{
	//テクスチャの解放
	texture_Destroy();
	
}

void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{

		if (!g_Bullets[i].IsUsed)
		{
			continue;//何もしない
		}
		//弾の座標の更新
		D3DXVECTOR2 dir(0.0f, 0.0f);
		dir -= D3DXVECTOR2(0.0f, 1.0f);

		D3DXVec2Normalize(&dir, &dir);
		D3DXVECTOR2 vecSpeed = dir * bspeed;
		g_Bullets[i].position += vecSpeed;
		g_Bullets[i].g_collision.position = g_Bullets[i].position;
		Effect_Create(g_Bullets[i].position.x, g_Bullets[i].position.y, D3DCOLOR_RGBA(255, 255, 0, 0), 5, 0.5f);


		if (g_Bullets[i].position.x < -11)
		{
			g_Bullets[i].IsUsed = false;
		}
		if (g_Bullets[i].position.x > SCREEN_WIDTH + 11)
		{
			g_Bullets[i].IsUsed = false;
		}
		if (g_Bullets[i].position.y < -30)
		{
			g_Bullets[i].IsUsed = false;
		}
		if (g_Bullets[i].position.y > SCREEN_HEIGHT + 30)
		{
			g_Bullets[i].IsUsed = false;
		}
	}
	


	
	
}

void Bullet_Draw(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].IsUsed)
		{
			Sprite_Draw(tex_bullet, g_Bullets[i].position.x, g_Bullets[i].position.y, 0, 0, 20, 20, 0, g_Bullets[i].position.x, g_Bullets[i].position.y, 1, 1);
			//Sprite_Draw(tex_bullet, g_Bullets[i].position.x, g_Bullets[i].position.y);

		}
	}
	
}

void Bullet_Create(float x, float y)
{

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullets[i].IsUsed)
		{
			//ここで一発分作る
			g_Bullets[i].IsUsed = true;
			g_Bullets[i].position.x = x;
			g_Bullets[i].position.y = y;
			//g_Bullets[i].g_collision.position;
			break;
		}
			
		
	}

	
}

bool Bullet_IsUsed(int index)//(int index)
{
	return g_Bullets[index].IsUsed;
}
void Bullet_Destroy(int index)//(int index)
{
	g_Bullets[index].IsUsed = false;
}

CirCle* Bullet_GetCollision(int index)//(int index)
{
	return &g_Bullets[index].g_collision;
}