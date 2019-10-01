#pragma once
#ifndef _FADE_H_
#define _FADE_H_

#include "direct3d.h"

void Fade_Init(void);
void Fade_Uninit(void);
void Fade_Update(void);
void Fade_Draw(void);
void Fade_Start(int frame, D3DCOLOR color, bool bFadeOut);//�t�F�[�h���ԁA�t�F�[�h�F�A
bool Fade_IsFade(void);
#endif // !_FADE_H_



