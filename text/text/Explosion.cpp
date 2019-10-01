#include <d3d9.h>
#include <d3dx9.h>

#include "texture.h"
#include "sprite.h"
#include "direct3d.h"
#include "Explosion.h"
#include "sound.h"

//グローバル変数
static int tex_Explosion;
static Explosion g_Explosion[EXPLOSION_MAX];

void Explosion_Init(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//フラグをiffにする
		g_Explosion[i].isUse = false;
		//座標の初期化
		g_Explosion[i].position.x = 0.0f;
		g_Explosion[i].position.y = 0.0f;

	}
	
	//テクスチャ
	tex_Explosion = Texture_SetLoadFile("Accet\\texture\\explosion.tga", 1024, 1024);
}
void Explosion_Update(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//アニメーションの更新（running　man と同じ
		if (g_Explosion[i].isUse)
		{
			g_Explosion[i].Animationcount++;
			
			//フラグoff(アニメーションが終わったら）
			if (g_Explosion[i].Animationcount >= 16)
			{
				g_Explosion[i].isUse = false;
				g_Explosion[i].Animationcount = 0;
			}
		}
	}
	

}
void Explosion_Draw(void)
{
	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//フラグがON
		if (g_Explosion[i].isUse)
		{
			Sprite_Draw(tex_Explosion, g_Explosion[i].position.x, g_Explosion[i].position.y, g_Explosion[i].Animationcount % 4 * 256, g_Explosion[i].Animationcount / 4 * 256, 256, 256, 0, g_Explosion[i].position.x, g_Explosion[i].position.y, 0.3, 0.3);

		}
	//爆発を描く
	}

}
void Explosion_Uninit(void)
{

	texture_Destroy();
}

void Explosion_Create(float x, float y)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosion[i].isUse)
		{
			//return;//何もしない
			g_Explosion[i].isUse = true;
			g_Explosion[i].position.x = x;
			g_Explosion[i].position.y = y;
			g_Explosion[i].Animationcount = 0;
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
	
	}

}