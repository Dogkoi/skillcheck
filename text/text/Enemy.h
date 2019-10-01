#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Collision.h"

#define ENEMY_MAX (100)

enum ENEMY_TYPE
{
	ENEMY_FISH1,
	ENEMY_FISH2,
	ENEMY_FISH3,
};

typedef struct Enemy_tag
{
	D3DXVECTOR2 position;
	CirCle g_Ecollision;
	bool IsUsed;
	ENEMY_TYPE type;
	int hp;
}Enemy;


void Enemy_Init(void);
void Enemy_Uninit(void);
void Enemy_Update(void);
void Enemy_Draw(void);
void Enemy_Create(float x, float y, ENEMY_TYPE type);
bool Enemy_IsUsed(int index);
void Enemy_Destroy(int index);
CirCle* Enemy_GetCollision(int index);
Enemy* GetEnemyposition(void);

void hpminus(int n);
#endif // !_ENEMY_H_

