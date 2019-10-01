#include "score.h"
#include "number.h"
#include "sprite.h"

static int num = 0;



void score_Draw(int score, float x, float y, int digit, bool zero = true, bool left = false)
//　　　                                         7     ZEROめからするかどうか　　左詰め
{
	for (int i = 0; i < digit; i++)
	{
		num = score % 10;
		Number_Draw(num, x - 40.0f * i, y);
		score /= 10;
	}
}
