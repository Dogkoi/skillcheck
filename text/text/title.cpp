#include <d3d9.h>
#include <d3dx9.h>
#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "scene.h"
#include "input.h"
#include "fade.h"
#include "debug_font.h"
#include "common.h"
#include "sound.h"

bool isdown = false;
int tex_title;

void Title_Init(void)
{
	tex_title = Texture_SetLoadFile("Accet\\Texture\\title.jpg", 1280, 720);
}
void Title_Update(void)
{

	if (Keyboard_IsPress(DIK_RETURN))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		isdown = true;
		
	}
	if (isdown && !Fade_IsFade())
	{
		Scene_SetNextScene(SCENE_GAME);
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		isdown = false;
		PlaySound(SOUND_LABEL_BGM000);
	}

}
void Title_Draw(void)
{

	Sprite_Draw(tex_title, 0, 0);

}
void Title_Uninit(void)
{
	texture_Destroy();
}