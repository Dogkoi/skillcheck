#include "bg.h"
#include "player.h"
#include "ball.h"
#include "Collision.h"
#include "Block.h"
#include "Explosion.h"
#include "Score.h"


void InitGame()
{
	InitBG();
	InitPlayer();
	InitBall();
	InitBlock();
	InitExplosion();
	InitScore();
}

void UninitGame()
{
	UninitBG();
	UninitPlayer();

	UninitBall();
	UninitBlock();
	UninitExplosion();
	UninitScore();
}

void UpdateGame()
{
	UpdateBG();
	UpdatePlayer();
	UpdateBall();
	UpdateBlock();
	UpdateExplosion();
	UpdateScore();
}

void DrawGame()
{
	DrawBG();
	DrawPlayer();

	DrawBall();
	DrawBlock();
	DrawExplosion();
	DrawScore();
}
