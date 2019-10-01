#include <d3d9.h>
#include <d3dx9.h>

#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "effect.h"

//グローバル変数
int tex_effect;//テクスチャ用
static Effect g_Effects[EFFECT_MAX];
int g_EffectFrameCount = 0;
static bool isright = true;

void Effect_Init(void)
{

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effects[i].lifeFrame = 0;
		g_Effects[i].spawnFrame = -1;

	}
	//弾の初期化
	tex_effect = Texture_SetLoadFile("Accet\\Texture\\effect000.jpg",40, 40);

	g_EffectFrameCount = 0;
	
}

void Effect_Uninit(void)
{
	//テクスチャの解放
	texture_Destroy();

}

void Effect_Update(void)
{
	//アニメーションの更新（フラグがonたっら）
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effects[i].lifeFrame > 0)
		{
			int elapsedFrame = g_EffectFrameCount - g_Effects[i].spawnFrame;
			float e = elapsedFrame / (float)g_Effects[i].lifeFrame;

			if (e > 1.0f) 
			{
				e = 1.0f;
				g_Effects[i].lifeFrame = 0;
				g_Effects[i].spawnFrame = -1;
				continue;
			}
			//g_Effects[i].scale *= scalerate;
			//αは各色成分と乗算される..

			D3DXCOLOR color = g_Effects[i].color;
			color.a = 1.0f - e;
			g_Effects[i].color = color;
		}
	
	}

	g_EffectFrameCount++;

}

void Effect_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// レンダーステート(加算合成処理)
   // 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0)アルファ)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定(1.0)

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//生きてたら
		if (g_Effects[i].lifeFrame > 0)
		{
			Sprite_SetColor(g_Effects[i].color);
			Sprite_Draw(tex_effect, g_Effects[i].position.x, g_Effects[i].position.y,0,0,40,40,0.0f,g_Effects[i].position.x,g_Effects[i].position.y,g_Effects[i].size,g_Effects[i].size,g_Effects[i].size,isright);
		}
	}

	// レンダーステート(通常ブレンド処理)
   // 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0 - SRC)アルファ)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定(1.0 - SRC)
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float size)
{

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effects[i].lifeFrame > 0 && g_Effects[i].spawnFrame >= 0)
		{
			continue;
		
		}
		//データをつめている
		g_Effects[i].position.x = x;
		g_Effects[i].position.y = y;
		g_Effects[i].color = color;
		g_Effects[i].lifeFrame = lifeFrame;
		g_Effects[i].size = size;
		g_Effects[i].spawnFrame = g_EffectFrameCount;
		break;

	}


}

