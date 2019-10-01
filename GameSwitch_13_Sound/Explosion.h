#pragma once

#define EXPLOSION_MAX		 100
#define EXPLOSION_WIDTH		(128.0f)
#define EXPLOSION_HEIGHT	(64.0f)

struct EXPLOSION
{
	Float2	Position;
	int		Type;
	bool	Use;
	int		frame;
};


void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();

void SetExplosion(float x, float y);
EXPLOSION *GetExplosion();