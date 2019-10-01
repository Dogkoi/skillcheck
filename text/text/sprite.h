#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <d3d9.h>
#include <d3dx9.h>

void Sprite_Init(void);
void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth,float angle, float cx, float cy,float rx,float ry,bool isright);//切り取るｘ　ｙ　幅　高さ 回転の中心座標
void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth, float angle, float cx, float cy, float sx, float sy);
void Sprite_Draw(int textureId, float dx, float dy);
void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth);

void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z, bool isright);
void Sprite_Uninit(void);
void Sprite_SetColor(D3DCOLOR color);
#endif // !_SPRITE_H_
