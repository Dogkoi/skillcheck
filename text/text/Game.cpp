#include "Game.h"
#include "player.h"
#include "Bullet.h"
#include "EnemyGenerater.h"
#include "Enemy.h"
#include "Judgement.h"
#include "Explosion.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "Debug.h"
#include "effect.h"
#include "fade.h"
#include "input.h"
#include "scene.h"
#include "bg.h"
#include "HighScore.h"
#include "texture.h"


static int g_score = 0;
bool go;

void Game_Init()
{

	BG_Init();
	Debug_Init();
	player_Init();
	Bullet_Init();
	EG_Init();
	Enemy_Init();
	Explosion_Init();
	Number_Init();
	Effect_Init();

	g_score = 0;
}

void Game_Update()
{

	BG_Update();
	player_Update();
	Bullet_Update();
	EG_Update();
	Enemy_Update();
	Judgement_Update();
	Explosion_Update();
	Effect_Update();

	if (Keyboard_IsPress(DIK_X))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		go = true;
	}
	if (go && !Fade_IsFade())
	{
		Scene_SetNextScene(SCENE_HIGHSCORE);
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		go = false;
	}

	SetScore(g_score);

}
void Game_Draw()
{
	BG_Draw();
	score_Draw(g_score, 1250, 50, 7, true, false);
	player_Draw();
	Bullet_Draw();
	Enemy_Draw();
	Explosion_Draw();
	Effect_Draw();
}
void Game_Uninit()
{
	BG_Uninit();
	player_Uninit();
	Bullet_Uninit();
	EG_Uninit();
	Enemy_Uninit();
	Explosion_Uninit();
	Effect_Uninit();

	//texture_Destroy();
}

void Addscore(int n)
{
	g_score += n;
}