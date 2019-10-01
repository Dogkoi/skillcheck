#pragma once


#define BLOCK_MAX		 100
#define BLOCK_WIDTH		(128.0f)
#define BLOCK_HEIGHT	(64.0f)

struct BLOCK
{
	Float2	Position;
	int		Type;
	bool	Use;
};


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(float x, float y, int type);
BLOCK *GetBlock();
int GetScore();