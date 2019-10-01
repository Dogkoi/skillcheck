#include "HighScore.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "scene.h"
#include "score.h"
#include "Game.h"
#include "common.h"
#include "sound.h"
#include "number.h"

int tex_HS;//highscore bg
bool down = false;
static int PlayerScore;


void HighScore_Init(void)
{
	//Number_Init();
	tex_HS = Texture_SetLoadFile("Accet\\Texture\\result.jpg", 1280, 720);
}

void HighScore_Update(void)
{
	if (Keyboard_IsPress(DIK_RETURN))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		down = true;

	}
	if (down && !Fade_IsFade())
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		down = false;
		Scene_SetNextScene(SCENE_TITLE);

	}
}

void HighScore_Draw(void)
{
	Sprite_Draw(tex_HS, 0, 0);

	score_Draw(PlayerScore, SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 7, true, false);

}

void HighScore_Uninit(void)
{

	texture_Destroy();

}

void SetScore(int n)
{
	PlayerScore = n;
}