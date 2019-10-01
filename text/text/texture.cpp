#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"

#define FILENAME_MAX (128)
#define TEXTUREDATA_MAX (100)

typedef struct TextureData_tag
{
	char filename[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureData;

static TextureData g_texturedata[TEXTUREDATA_MAX] = {};
static LPDIRECT3DDEVICE9 g_pDevice = NULL;
//HRESULT tx[TEXTUREDATA_MAX] = {};

int Texture_SetLoadFile(const char* pFilename, int width, int height)
{
	//“¯‚¶ƒtƒ@ƒCƒ‹–¼‚ð’T‚·
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (strcmp(g_texturedata[i].filename, pFilename) == 0)
		{
			return i;
		}
	}
	//V‹K“o˜^
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		//Žg—p‚³‚ê‚Ä‚¢‚È‚¢êŠ‚ð’T‚·
		if (g_texturedata[i].filename[0] != 0)
		{
			continue;
		}
		//“o˜^
		strcpy(g_texturedata[i].filename, pFilename);
		g_texturedata[i].width = width;
		g_texturedata[i].height = height;
		return i;
	}
	return -1;
}

int Texture_Load(void)
{
	g_pDevice = GetDevice();
	int error_count = 0;
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_texturedata[i].pTexture != NULL)
		{
			continue;
		}
		
		//ƒeƒNƒXƒ`ƒƒ“Ç‚Ýž‚Ý
		HRESULT hr=		D3DXCreateTextureFromFile(g_pDevice, g_texturedata[i].filename, &g_texturedata[i].pTexture);
		/*if (FAILED(hr))
		{
			MessageBox(NULL, "‰æ‘œ‚ªo—ˆ‚Ü‚¹‚ñ", "ƒGƒ‰[", MB_OK);
			return false;
		}*/
		
	}

	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_texturedata[i].filename[0] == 0)
		{
			continue;
		}
	}
	
	return error_count;
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id)
{
	return g_texturedata[id].pTexture;
}
void Texture_Destroy(int ids[], int count)
{
	for (int i = 0; i < count; i++) {
		if (g_texturedata[ids[i]].pTexture != NULL) {
			g_texturedata[ids[i]].pTexture->Release();
			g_texturedata[ids[i]].pTexture = NULL;
			g_texturedata[ids[i]].filename[0] = 0;
		}
	}
}
void texture_Destroy(void)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_texturedata[i].pTexture != NULL) {
			g_texturedata[i].pTexture->Release();
			g_texturedata[i].pTexture = NULL;
			g_texturedata[i].filename[0] = 0;
		}
	}
}
int Texture_GetWidth(int id)
{
	return g_texturedata[id].width;
}
int Texture_GetHeight(int id)
{
	return g_texturedata[id].height;
}