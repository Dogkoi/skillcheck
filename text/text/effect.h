#pragma once
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Collision.h"

#define EFFECT_MAX (1000)

typedef struct Effect_tag
{
	D3DXVECTOR2 position;
	bool IsUsed;
	int lifeFrame;//寿命
	int spawnFrame;
	D3DCOLOR color;
	float size;
	//種類　速度ベクトル

}Effect;

void Effect_Init(void);
void Effect_Uninit(void);
void Effect_Update(void);
void Effect_Draw(void);
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float size);//チャレンジ：後ろにエフェクトの拡大率を入れられると良い



#endif // !_EFFECT_H_

