#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_MAX (1)
#include <d3d9.h>
#include <d3dx9.h>
#include "Collision.h"

typedef struct Plyaer_Tag
{
	D3DXVECTOR2 position;
	CirCle collision;
	bool IsUsed;
	float speed;
	float PlusSpeed;
}Player;

void player_Init();
void player_Update();
void player_Draw();
void player_Uninit();
Player* GetPlayerPosition(void);
bool Player_IsUsed(int index);
CirCle* Player_GetCollision(int index);
void Player_Destroy(int index);
#endif // _PLAYER_H_

