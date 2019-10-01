#pragma once
#ifndef _ENEMYGENERATER_H_
#define _ENEMYGENERATER_H_

#include "Enemy.h"

typedef struct EnemyGenerate_tag
{
	int frame;
	float x, y;
	ENEMY_TYPE type;
}EnemyGenerate;


void EG_Init(void);
void EG_Uninit(void);
void EG_Update(void);


#endif // !_ENEMYGENERATER_H_

