
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "Collision.h"


unsigned int	g_PlayerTexture;
Float2			g_PlayerPosition;



void InitPlayer()
{

	g_PlayerTexture = LoadTexture("rom:/player.tga");

	g_PlayerPosition.x = 0.0f;
	g_PlayerPosition.y = 450.0f;
}



void UninitPlayer()
{

	UnloadTexture(g_PlayerTexture);

}


void UpdatePlayer()
{

	// ボタン
	if (GetControllerPress(NpadButton::Left::Index))
		g_PlayerPosition.x += -20.0f;
	if (GetControllerPress(NpadButton::Right::Index))
		g_PlayerPosition.x += 20.0f;
	if (GetControllerPress(NpadButton::Up::Index))
		g_PlayerPosition.y += -20.0f;
	if (GetControllerPress(NpadButton::Down::Index))
		g_PlayerPosition.y += 20.0f;


	// アナログスティック
	Float2 stick;
	stick = GetControllerLeftStick();
	g_PlayerPosition.x += stick.x * 20.0f;
	g_PlayerPosition.y += stick.y * -20.0f;




	// タッチスクリーン
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		g_PlayerPosition = touch;
	}



	// 加速度センサー
	if (GetControllerPress(NpadButton::A::Index))
	{
		Float3 acc;
		acc = GetControllerRightAcceleration();

		g_PlayerPosition.x += acc.x * 10.0f;
		g_PlayerPosition.y += -acc.y * 10.0f;
	}



	// ジャイロセンサー
	if (GetControllerPress(NpadButton::B::Index))
	{
		Float3 angle;
		angle = GetControllerRightAngle();

		g_PlayerPosition.x = angle.z * 1000.0f;
	}



	// 振動
	if (GetControllerPress(NpadButton::Y::Index))
	{
		SetControllerLeftVibration(5);
	}
	if (GetControllerPress(NpadButton::X::Index))
	{
		SetControllerRightVibration(5);
	}



	//移動範囲チェック
	if (g_PlayerPosition.x < -500.0f + 100.0f)
		g_PlayerPosition.x = -500.0f + 100.0f;

	if (g_PlayerPosition.x > 500.0f - 100.0f)
		g_PlayerPosition.x = 500.0f - 100.0f;

	if (g_PlayerPosition.y < -540.0f + 65.0f)
		g_PlayerPosition.y = -540.0f + 65.0f;
	if (g_PlayerPosition.y > 600.0f - 85.0f)
		g_PlayerPosition.y = 600.0f - 85.0f;
}



void DrawPlayer()
{

	SetTexture(g_PlayerTexture);

	DrawSprite(g_PlayerPosition.x, g_PlayerPosition.y, 256.0f, 64.0f,
						0.0f, 0.0f, 1.0f, 1.0f,
						MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}


Float2	GetPosition()
{
	return g_PlayerPosition;
}