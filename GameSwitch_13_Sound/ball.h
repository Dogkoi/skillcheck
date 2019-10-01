#pragma once  //インクルードガード
#include "main.h"

void InitBall();
void UninitBall();
void UpdateBall();
void DrawBall();

#define BALL_WIDTH		(64.0f)
#define BALL_HEIGHT		(64.0f)



Float2 GetBallPosition();
Float2 *GetBallVelocity();