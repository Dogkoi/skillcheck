#include "texture.h"
#include "direct3d.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "number.h"


#define NUMBER_PATTERN_MAX (10)//ç≈ëÂÉpÉ^Éì

static int tex_number;

void Number_Init()
{
	tex_number = Texture_SetLoadFile("Accet\\texture\\number.tga", 512, 512);
}


void Number_Draw(int number, float x, float y)
{
	if (number < 0 || number>9)
	{
		return;
	}
	int pattern = number % NUMBER_PATTERN_MAX;
	Sprite_Draw(tex_number, x, y, pattern % 5 * NUMBER_WIDTH, pattern / 5 * NUMBER_HEIGHT, NUMBER_WIDTH, NUMBER_HEIGHT, 0, x, y, 0.5, 0.5);
}
