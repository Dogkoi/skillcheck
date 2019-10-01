#include <d3d9.h>
#include <d3dx9.h>
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "Bullet.h"
#include "effect.h"



int player;
bool isright = false;
float speed = 5.0f;
float PlusSpeed = 10.0f;
float angle = 0.0f;
float rx = 1.0f;
float ry = 1.0f;
static bool isShoot = false;
static int flame = 0;
Player g_player[PLAYER_MAX] = {};


void player_Init()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_player[i].position = { 300.0f,500.0f };
		player = Texture_SetLoadFile("Accet\\Texture\\airou.png", 128, 128);
		g_player[i].collision.radius = 64;
		g_player[i].IsUsed = true;
	}
	//g_player_position = { 300.0f,500.0f };
	//player = Texture_SetLoadFile("Accet\\Texture\\airou.png", 128, 128);
	isShoot = false;
	flame = 0;
	//playercollision.radius = 64;
}
void player_Update()
{
	Keyboard_Update();



	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (!g_player[i].IsUsed)
		{
			continue;
		}

		D3DXVECTOR2 dir(0.0f, 0.0f);

		if (Keyboard_IsPress(DIK_W))
		{
			dir -= D3DXVECTOR2(0.0f, 1.0f);
			//dir.y-=1;

		}
		if (Keyboard_IsPress(DIK_S))
		{
			dir += D3DXVECTOR2(0.0f, 1.0f);
			//dir.y+=1;

		}
		if (Keyboard_IsPress(DIK_A))
		{
			dir -= D3DXVECTOR2(1.0f, 0.0f);
			//dir.x-=1;

			isright = true;
		}
		if (Keyboard_IsPress(DIK_D))
		{
			//speedx += 1.0f;
			dir += D3DXVECTOR2(1.0f, 0.0f);

			//dir.x += 1;
			isright = false;
		}
		if (!isShoot)
		{
			if (Keyboard_IsPress(DIK_J))
			{
				isShoot = true;
				Bullet_Create(g_player[i].position.x, g_player[i].position.y);
			}

		}

		//maru += maru_speed;

		if (g_player[i].position.x > SCREEN_WIDTH - 64)
		{
			g_player[i].position.x = SCREEN_WIDTH - 64;
		}
		if (g_player[i].position.x < 64)
		{
			g_player[i].position.x = 64;
		}
		if (g_player[i].position.y < 64)
		{
			g_player[i].position.y = 64;
		}
		if (g_player[i].position.y > SCREEN_HEIGHT - 64)
		{
			g_player[i].position.y = SCREEN_HEIGHT - 64;
		}

		D3DXVec2Normalize(&dir, &dir);//ベクトルの正規化
		D3DXVECTOR2 vecSpeed = dir * speed;
		g_player[i].position += vecSpeed;
		if (Keyboard_IsPress(DIK_K))
		{
			//PlusSpeed += 0.03f;
			D3DXVECTOR2 vecSpeed = dir * PlusSpeed;
			g_player[i].position += vecSpeed;
		}
		if (isShoot)
		{
			flame++;
		}
		if (flame % 15 == 0)
		{
			isShoot = false;
			flame = 0;
		}

	}

	
	//Effect_Create(g_player_position.x, g_player_position.y, D3DCOLOR_RGBA(200, 100, 0, 150), 10, 0.8f);

	
}
void player_Draw()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_player[i].IsUsed)
		{
			Sprite_Draw(player, g_player[i].position.x, g_player[i].position.y, 0, 0, 128, 128, angle, 128, 128, rx, ry, !isright);

		}

	}

}
void player_Uninit()
{
	//テクスチャの解放
	texture_Destroy();

}
Player* GetPlayerPosition(void)
{
	return &g_player[0];
}
bool Player_IsUsed(int index)
{
	return g_player[index].IsUsed;
}
CirCle* Player_GetCollision(int index)
{
	return &g_player[index].collision;
}
void Player_Destroy(int index)
{
	g_player[index].IsUsed = false;
}