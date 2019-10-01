#pragma once
#ifndef _BG_H_
#define _BG_H_

typedef struct BG_tag
{
	bool used;
}BG;
void BG_Init(void);
void BG_Uninit(void);
void BG_Update(void);
void BG_Draw(void);


#endif // !_BG_H_
