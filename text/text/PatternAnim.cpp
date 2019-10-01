#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"
#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "PatternAnim.h"


#define COCO_WALK_R_PATTERN_MAX (10)
int tex_coco;
bool isright1;
void PatternAnim_Init(void)
{

}
void PatternAnim_Draw(float dx, float dy, int frameCount)
{
	//int pattern = frameCount / 3 % COCO_WALK_R_PATTERN_MAX;//8は待ちフレーム　13最大パターン数
	//ココ右向き描画

//	Sprite_Draw(tex_coco, 100.0f, 100.0f, pattern * 1 , 0, 32, 32, 0.0f, 32, 32, 1.0f, 1.0f, 1.0f);


}