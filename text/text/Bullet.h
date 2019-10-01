#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Collision.h"

#define BULLET_MAX (1000)

typedef struct Bullet_tag
{
	D3DXVECTOR2 position;
	CirCle  g_collision;
	bool IsUsed;
	//種類　速度ベクトル

}Bullet;

void Bullet_Init(void);
void Bullet_Uninit(void);
void Bullet_Update(void);
void Bullet_Draw(void);
void Bullet_Create(float x, float y);
bool Bullet_IsUsed(int index);
void Bullet_Destroy(int index);
CirCle* Bullet_GetCollision(int index);

#endif // !_BULLET_H_

