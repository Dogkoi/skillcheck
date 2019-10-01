
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "Collision.h"
#include "ball.h"
#include "Explosion.h"
#include "sound.h"

unsigned int	g_BlockTexture;
BLOCK			g_Block[BLOCK_MAX];
static int				key;

static int score_val = 0;

//ball's information
Float2 BallPosition;
Float2 *BallVelocity;


void InitBlock()
{

	g_BlockTexture = LoadTexture("rom:/block.tga");

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].Use = false;
	}


	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetBlock(-300.0f + x * 200.0f, -375.0f + y * 130.0f, y);
		}
	}
}



void UninitBlock()
{
	score_val = 0;
	UnloadTexture(g_BlockTexture);

}


void UpdateBlock()
{
	int blockCount = 0;
	BallPosition = GetBallPosition();
	BallVelocity = GetBallVelocity();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Use == true)
			blockCount++;

		// Collision
		key = CollisionBB(BallPosition.x,BallPosition.y,BALL_WIDTH,BALL_HEIGHT,g_Block[i].Position.x, g_Block[i].Position.y,BLOCK_WIDTH,BLOCK_HEIGHT);
		if (g_Block[i].Use && key)
		{
			g_Block[i].Use = false;
			SetExplosion(BallPosition.x, BallPosition.y);
			score_val += 10;
			PlaySE(WSD_WATER_DROP1);
			if (key == 2 || key == 3)
			{
				// y‰ñ“]g_BallVelocity.y *= -1;

				BallVelocity->y *= -1;
				
			}
			else if (key == 4 || key == 5)
			{
				// x‰ñ“]g_BallVelocity.x *= -1;
				BallVelocity->x *= -1;
			}

		}
	}



}



void DrawBlock()
{

	SetTexture(g_BlockTexture);


	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Use == true)
		{
			DrawSprite(g_Block[i].Position.x, g_Block[i].Position.y, BLOCK_WIDTH, BLOCK_HEIGHT,
				0.0f, g_Block[i].Type * 0.25f, 1.0f, 0.25f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}


void SetBlock(float x, float y, int type)
{

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].Use == false)
		{
			g_Block[i].Position.x = x;
			g_Block[i].Position.y = y;
			g_Block[i].Type = type;
			g_Block[i].Use = true;
			break;
		}
	}

}


BLOCK *GetBlock()
{
	return g_Block;
}

int GetScore()
{
	return score_val;
}