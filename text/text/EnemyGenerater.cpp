#include <d3d9.h>
#include <d3dx9.h>

#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "EnemyGenerater.h"

static int genalateCounter = 0;
static int frameCounter = 0;//èâä˙âªÇ≈Ç‡0ë„ì¸ÇÌÇ∑ÇÍÇ∏Ç…


static const EnemyGenerate ENEMY_GENERATE[] = {

    {60,100.0f,128.0f,ENEMY_FISH1},
	{160,450.0f,128.0f,ENEMY_FISH1},
	{190,300.0f,128.0f,ENEMY_FISH2},
	{260,200.0f,128.0f,ENEMY_FISH3},
	{300,100.0f,128.0f,ENEMY_FISH1},
	{350,350.0f,128.0f,ENEMY_FISH2},
	{410,700.0f,0.0f,ENEMY_FISH2},
	{428,800.0f,0.0f,ENEMY_FISH3},
	{470,0.0f,30.0f,ENEMY_FISH2,},
	{480,2.0f,60.0f,ENEMY_FISH3},
	{520,0.0f,90.0f,ENEMY_FISH2},
	{550,0.0f,120.0f,ENEMY_FISH2},
	{572,0.0f,150.0f,ENEMY_FISH2},
	{600,300.0f,0.0f,ENEMY_FISH3},
	{620,400.0f,0.0f,ENEMY_FISH1},
	{629,500.0f,0.0f,ENEMY_FISH3},
	{650,600.0f,0.0f,ENEMY_FISH1},
	{687,700.0f,0.0f,ENEMY_FISH2},
	{698,800.0f,0.0f,ENEMY_FISH3},
	{708,400.0f,0.0f,ENEMY_FISH1},
	{732,500.0f,0.0f,ENEMY_FISH1},
	{750,600.0f,0.0f,ENEMY_FISH3},
	{789,700.0f,0.0f,ENEMY_FISH1},
	{900,800.0f,0.0f,ENEMY_FISH2},
	{980,0.0f,30.0f,ENEMY_FISH2,},
	{1000,0.0f,60.0f,ENEMY_FISH3},
	{1010,0.0f,90.0f,ENEMY_FISH1},
	{1130,0.0f,120.0f,ENEMY_FISH1},
	{1340,0.0f,150.0f,ENEMY_FISH2},
	{1423,300.0f,0.0f,ENEMY_FISH3},
	{1500,400.0f,0.0f,ENEMY_FISH2},
	{1600,500.0f,0.0f,ENEMY_FISH1},
	{1700,600.0f,0.0f,ENEMY_FISH3},
	{1800,700.0f,0.0f,ENEMY_FISH2},
	{1900,800.0f,0.0f,ENEMY_FISH2},
	{2000,400.0f,0.0f,ENEMY_FISH3},
	{2100,50.0f,0.0f,ENEMY_FISH1},
	{2200,600.0f,0.0f,ENEMY_FISH3},
	{2300,700.0f,0.0f,ENEMY_FISH1},
	{2400,80.0f,0.0f,ENEMY_FISH2},
	{2572,0.0f,150.0f,ENEMY_FISH2},
	{2600,300.0f,0.0f,ENEMY_FISH3},
	{2620,400.0f,0.0f,ENEMY_FISH1},
	{2629,500.0f,0.0f,ENEMY_FISH3},
	{2650,600.0f,0.0f,ENEMY_FISH1},
	{2687,700.0f,0.0f,ENEMY_FISH2},
	{2698,800.0f,0.0f,ENEMY_FISH3},
	{2708,400.0f,0.0f,ENEMY_FISH1},
};

static const int ENEMY_GENERATE_MAX = sizeof(ENEMY_GENERATE) / sizeof(ENEMY_GENERATE[0]);
static int EnemyGenerate_Arrow = 0;
static int EnemyGenerate_FrameCount = 0;

void EG_Init(void)
{
	EnemyGenerate_Arrow = 0;
	EnemyGenerate_FrameCount = 0;
}
void EG_Uninit(void)
{
	texture_Destroy();
}
void EG_Update(void)
{
	for (EnemyGenerate_Arrow = 0; EnemyGenerate_Arrow < ENEMY_GENERATE_MAX; EnemyGenerate_Arrow++)
	{
		if (ENEMY_GENERATE[EnemyGenerate_Arrow].frame == frameCounter)
		{
			Enemy_Create(ENEMY_GENERATE[EnemyGenerate_Arrow].x, ENEMY_GENERATE[EnemyGenerate_Arrow].y, ENEMY_GENERATE[EnemyGenerate_Arrow].type);

			continue;
		}
		else if (ENEMY_GENERATE[EnemyGenerate_Arrow].frame > frameCounter)
		{
			break;
		}
	}
	
	/*if (frameCounter % 60 == 0)
	{
		//ìGî≠ê∂!!
		switch (genalateCounter % 3)
		{
		case 0:
			Enemy_Create(228.0f, -100.0f);
			Enemy_Create(700.0f, -50.0f);

			break;
		case 1:
			Enemy_Create(300.0f, -20.0f);
			Enemy_Create(950.0f, 0.0f);
			break;
		case 2:
			Enemy_Create(250.0f, 10.0f);
			break;

		}
		genalateCounter++;
	}*/
	frameCounter++;

}