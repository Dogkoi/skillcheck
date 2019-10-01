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
	int lifeFrame;//����
	int spawnFrame;
	D3DCOLOR color;
	float size;
	//��ށ@���x�x�N�g��

}Effect;

void Effect_Init(void);
void Effect_Uninit(void);
void Effect_Update(void);
void Effect_Draw(void);
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float size);//�`�������W�F���ɃG�t�F�N�g�̊g�嗦��������Ɨǂ�



#endif // !_EFFECT_H_

