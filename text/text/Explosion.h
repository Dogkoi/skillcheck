#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define EXPLOSION_MAX (100)

typedef struct Explosion_tag
{
	D3DXVECTOR2 position;
	int Animationcount;
	bool isUse;

}Explosion;

void Explosion_Init(void);
void Explosion_Update(void);
void Explosion_Draw(void);
void Explosion_Uninit(void);
void Explosion_Create(float x, float y);//�����̈�ԏ��߂ɍ��W

#endif // !_EXPLOSION_H_
