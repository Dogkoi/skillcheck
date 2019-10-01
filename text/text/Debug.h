#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_


#include "direct3d.h"

void Debug_Init(void);
void Debug_Uninit(void);
void Debug_Begin(void);
void Debug_End(void);
void Debug_DrawCircle(float x, float y, float radius);
void Debug_SetColor(D3DCOLOR color);



#endif // !_DEBUG_H_

