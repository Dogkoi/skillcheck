#include <d3d9.h>
#include <d3dx9.h>

#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "direct3d.h"
#include "common.h"
#include "effect.h"

//�O���[�o���ϐ�
int tex_effect;//�e�N�X�`���p
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
	//�e�̏�����
	tex_effect = Texture_SetLoadFile("Accet\\Texture\\effect000.jpg",40, 40);

	g_EffectFrameCount = 0;
	
}

void Effect_Uninit(void)
{
	//�e�N�X�`���̉��
	texture_Destroy();

}

void Effect_Update(void)
{
	//�A�j���[�V�����̍X�V�i�t���O��on������j
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
			//���͊e�F�����Ə�Z�����..

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

	// �����_�[�X�e�[�g(���Z��������)
   // �F = (SRC�F * SRC�A���t�@) + (DEST�F * (1.0)�A���t�@)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0)

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//�����Ă���
		if (g_Effects[i].lifeFrame > 0)
		{
			Sprite_SetColor(g_Effects[i].color);
			Sprite_Draw(tex_effect, g_Effects[i].position.x, g_Effects[i].position.y,0,0,40,40,0.0f,g_Effects[i].position.x,g_Effects[i].position.y,g_Effects[i].size,g_Effects[i].size,g_Effects[i].size,isright);
		}
	}

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
   // �F = (SRC�F * SRC�A���t�@) + (DEST�F * (1.0 - SRC)�A���t�@)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0 - SRC)
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
		//�f�[�^���߂Ă���
		g_Effects[i].position.x = x;
		g_Effects[i].position.y = y;
		g_Effects[i].color = color;
		g_Effects[i].lifeFrame = lifeFrame;
		g_Effects[i].size = size;
		g_Effects[i].spawnFrame = g_EffectFrameCount;
		break;

	}


}

