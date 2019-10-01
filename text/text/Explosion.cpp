#include <d3d9.h>
#include <d3dx9.h>

#include "texture.h"
#include "sprite.h"
#include "direct3d.h"
#include "Explosion.h"
#include "sound.h"

//�O���[�o���ϐ�
static int tex_Explosion;
static Explosion g_Explosion[EXPLOSION_MAX];

void Explosion_Init(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//�t���O��iff�ɂ���
		g_Explosion[i].isUse = false;
		//���W�̏�����
		g_Explosion[i].position.x = 0.0f;
		g_Explosion[i].position.y = 0.0f;

	}
	
	//�e�N�X�`��
	tex_Explosion = Texture_SetLoadFile("Accet\\texture\\explosion.tga", 1024, 1024);
}
void Explosion_Update(void)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//�A�j���[�V�����̍X�V�irunning�@man �Ɠ���
		if (g_Explosion[i].isUse)
		{
			g_Explosion[i].Animationcount++;
			
			//�t���Ooff(�A�j���[�V�������I�������j
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
		//�t���O��ON
		if (g_Explosion[i].isUse)
		{
			Sprite_Draw(tex_Explosion, g_Explosion[i].position.x, g_Explosion[i].position.y, g_Explosion[i].Animationcount % 4 * 256, g_Explosion[i].Animationcount / 4 * 256, 256, 256, 0, g_Explosion[i].position.x, g_Explosion[i].position.y, 0.3, 0.3);

		}
	//������`��
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
			//return;//�������Ȃ�
			g_Explosion[i].isUse = true;
			g_Explosion[i].position.x = x;
			g_Explosion[i].position.y = y;
			g_Explosion[i].Animationcount = 0;
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
	
	}

}