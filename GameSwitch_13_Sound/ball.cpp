#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "Collision.h"
#include "ball.h"
#include "Block.h"
#include "Fade.h"


unsigned int g_BallTexture;
Float2 g_BallPosition;
Float2 g_BallVelocity;


Float2 g_PlayerPosition2;

void InitBall()
{
	//絵を読み込み
	g_BallTexture = LoadTexture("rom:/ball.tga");

    //ボールの表示座標
	g_BallPosition.x = 0.0f;
	g_BallPosition.y = 300.0f;

	//移動速度
	g_BallVelocity.x = 10.0f;
	g_BallVelocity.y = -10.0f;
	
}

void UninitBall()
{
	//絵を破棄
	UnloadTexture(g_BallTexture);
}

void UpdateBall()
{
	g_PlayerPosition2 = GetPosition();
	g_BallPosition.x += g_BallVelocity.x;//ボールを1回進める
	g_BallPosition.y += g_BallVelocity.y;

	//左壁チェック
	if(g_BallPosition.x < -500.0f + 25.0f) //ball's size = 25.0f
	{
		g_BallPosition.x = -500.0f + 25.0f;
		g_BallVelocity.x *= -1.0f;//反転させている
	}
	//右壁チェック
	if(g_BallPosition.x > 500.0f - 25.0f)
	{
		g_BallPosition.x = 500.0f - 25.0f;
		g_BallVelocity.x *= -1.0f;
	}
	//下壁チェック
	if(g_BallPosition.y > 500.0f - 25.0f)
	{
		//gameover
		Fade(SCENE_TITLE);

	}
	//上壁チェック	
	if(g_BallPosition.y < -500.0f + 25.0f)
	{
		g_BallPosition.y = -500.f + 25.0f;
		g_BallVelocity.y *=-1.0f;
	}


	if (CollisionBB(g_BallPosition.x, g_BallPosition.y, 60.0f, 60.0f, g_PlayerPosition2.x, g_PlayerPosition2.y,256.0f, 64.0f)) {
		g_BallVelocity.y *= -1.0f;
	}

}


void DrawBall()
{
	SetTexture(g_BallTexture);
	DrawSprite(g_BallPosition.x,g_BallPosition.y,64,64,
	0.0f,0.0f,1.0f,1.0f,
	MakeFloat4(1.0f,1.0f,1.0f,1.0f));//x,y,w,h,u,v,size,size,Color
}


Float2 GetBallPosition()
{
	return g_BallPosition;
}


Float2 *GetBallVelocity()
{
	return &g_BallVelocity;
}