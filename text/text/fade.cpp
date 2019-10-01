#include "fade.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "direct3d.h"

//�O���[�o���ϐ�
bool g_bFadeOut = false;
bool g_bFade = false;
int g_FadeFrame = 0;
int g_FadeFrameCount = 0;
int g_FadeStartFrame = 0;
D3DCOLOR g_FadeColor = 0;

typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}FadeVertex;

#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

void Fade_Init(void)
{
	//������
	g_bFade = false;
	g_FadeFrameCount = 0;
}
void Fade_Uninit(void)
{

}
void Fade_Update(void)
{
	//�X�V
	if (g_bFade)
	{
		int elapsedFrame = g_FadeFrameCount - g_FadeStartFrame;
		float e = elapsedFrame / (float)g_FadeFrame;
		float alpha = 0;

		if (elapsedFrame >= g_FadeFrame)
		{
			g_bFade = false;
			e = 1.0f;
		}
		
		alpha = g_bFadeOut ? e : 1.0f - e;

		D3DXCOLOR color = g_FadeColor;
		color.a = alpha;
		g_FadeColor = color;
		
	}
	g_FadeFrameCount++;

}
void Fade_Draw(void)
{
	/*�|���S���`��@SetTexture�ɂ�NULL�t�F�[�h�C�����I�����Ă���|���S���`���Ȃ�
		                              �t�F�[�h�A�E�g�I�����Ă���|���S���`���H*/

	D3DXCOLOR color = g_FadeColor;
	if (color.a <= 0.0001f)
	{
		return;
	}
	FadeVertex V[] = {
		
		{D3DXVECTOR4(0.0f,SCREEN_HEIGHT,0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f), g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,0.0f,0.0f,1.0f),g_FadeColor},
			

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(FadeVertex));
}

void Fade_Start(int frame, D3DCOLOR color, bool bFadeOut)
{
	/*�X�^�[�g
�@�@�J���[�E�t�F�[�h���ԁiframe�j�E�t�F�[�h�C��or�A�E�g*/
	g_FadeColor = color;
	g_FadeFrame = frame;
	g_bFadeOut = bFadeOut;
	g_FadeStartFrame = g_FadeFrameCount;//���݂̃t���[��
	g_bFade = true;                     //�t�F�[�h��
}

bool Fade_IsFade(void)
{
	return g_bFade;
}