#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3d9.h>

int Texture_SetLoadFile(const char* pFilename, int width, int height);//テクスチャファイル、テクスチャ幅、テクスチャ高さ　←予約番号（id）同じファイル名一回だけ書いて
int Texture_Load(void);//ファイルの読み込み←読み込み なかった数

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//予約番号
void Texture_Destroy(int ids[], int count);//部分解放関数　int ids[]解放したいidが入った配列の先頭アドレス、count配列数　*？一個
void texture_Destroy(void);//全部解放関数
int Texture_GetWidth(int id);
int Texture_GetHeight(int id);

#endif // _TEXTURE_H_
