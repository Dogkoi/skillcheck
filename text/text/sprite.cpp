#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"
#include "common.h"
#include "texture.h"

/*--------------------------------------------------------------------------------
-      頂点データ構造体（頂点の形（フォーマット）の宣言

--------------------------------------------------------------------------------*/

typedef struct Vertex2d_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;//座標の次にすること
	D3DXVECTOR2 UV;//頂点構造体にUV追加     U--x V--y
}Vertex2d;
/*------------------------------------------------------------------
	  FVFの宣言
-------------------------------------------------------------------*/
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


static D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);
static LPDIRECT3DDEVICE9 g_pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_IndexBuffer = NULL;

void Sprite_Init(void)
{
	g_pDevice = GetDevice();
	g_pDevice->CreateVertexBuffer(sizeof(Vertex2d) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);//四頂点のメモリ欲しい、書き換える読める、入れなくてもいい　0に書く
	g_pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_IndexBuffer, NULL);
}

void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth, float angle, float cx, float cy, float sx, float sy, bool isright)
{
	g_pDevice = GetDevice();


	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cutx / (float)w;
	float v0 = cuty / (float)h;
	float u1 = (cutx + cutw) / (float)w;
	float v1 = (cuty + cuth) / (float)h;

	//D3DXMATRIX mtxRot;

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//中心移動完成
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, sx, sy, 1.0f);//x y z
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;

	float u[2];
	if (isright)
	{
		u[0] = u1;
		u[1] = u0;
	}
	else
	{
		u[0] = u0;
		u[1] = u1;
	}

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - 0.5f - cutw / 2,dy - 0.5f + cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v1)},
		{D3DXVECTOR4(dx - 0.5f - cutw / 2,dy - 0.5 - cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v0)},
		{D3DXVECTOR4(dx - 0.5f + cutw / 2,dy - 0.5f + cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v1)},
		{D3DXVECTOR4(dx - 0.5f + cutw / 2,dy - 0.5f - cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v0)},
	};
	/*Vertex2d v[] = {
		{D3DXVECTOR4(-0.5f,-0.5f + cuth,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(-0.5f, -0.5,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(-0.5f + cutw, -0.5f + cuth,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(-0.5f + cutw, -0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0)},
	};*/
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);


	Vertex2d* pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//第二0全部の意味・(void**)&pV 仮想アドレス・//lock　CPU GPU一緒
	memcpy(pV, v, sizeof(v));
	g_VertexBuffer->Unlock();

	WORD* pIndex;
	g_IndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	g_IndexBuffer->Unlock();


	//	WORD index[] = { 0,1,2,1,3,2 };//WORD 0-65535個頂点 


	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Vertex2d));
	g_pDevice->SetIndices(g_IndexBuffer);
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth, float angle, float cx, float cy, float sx, float sy)
{
	g_pDevice = GetDevice();
	

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cutx / (float)w;
	float v0 = cuty / (float)h;
	float u1 = (cutx + cutw) / (float)w;
	float v1 = (cuty + cuth) / (float)h;

	//D3DXMATRIX mtxRot;

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//中心移動完成
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, sx, sy, 1.0f);//x y z
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;
	
	Vertex2d v[] = {
		{D3DXVECTOR4(dx -0.5f - cutw / 2,dy - 0.5f + cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx -0.5f - cutw / 2,dy - 0.5 - cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + cutw / 2,dy - 0.5f + cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(dx - 0.5f + cutw / 2,dy - 0.5f - cuth / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0)},
	};


	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);


	Vertex2d* pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//第二0全部の意味・(void**)&pV 仮想アドレス・//lock　CPU GPU一緒
	memcpy(pV, v, sizeof(v));
	g_VertexBuffer->Unlock();

	WORD* pIndex;
	g_IndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	g_IndexBuffer->Unlock();


	//	WORD index[] = { 0,1,2,1,3,2 };//WORD 0-65535個頂点 


	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Vertex2d));
	g_pDevice->SetIndices(g_IndexBuffer);
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
void Sprite_Draw(int textureId, float dx, float dy)
{
	g_pDevice = GetDevice();

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);
	
	/*Vertex2d v[] = {
		{D3DXVECTOR4(-0.5f,dy-0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(-0.5f, -0.5,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(dx-0.5f, dy-0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,1.0f)},
		{D3DXVECTOR4(dx-0.5f, -0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,0.0f)},
	};*/

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(dx - 0.5f, dy - 0.5,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(dx + w - 0.5f, dy + h - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,1.0f)},
		{D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,0.0f)},
	};

	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}

void Sprite_Draw(int textureId, float dx, float dy, int cutx, int cuty, int cutw, int cuth)
{
	g_pDevice = GetDevice();
	
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);


	Vertex2d v[] = {
	{D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,1.0f)},
	{D3DXVECTOR4(dx - 0.5f, dy - 0.5,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(dx + w - 0.5f, dy + h - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,0.0f)},
	};
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//頂点データ(トライアングルストリップ)
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	float u[2] = {};


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//元に戻す
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   拡大、縮小
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0)},
	};

	//回転　(0,0)が原点
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z, bool isright)
//                                                                                                      回転の中心座標
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//頂点データ(トライアングルストリップ)
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	float u[2] = {};
	if (isright)
	{
		u[0] = u1;
		u[1] = u0;
	}
	if (!isright)
	{
		u[0] = u0;
		u[1] = u1;
	}

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//元に戻す
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   拡大、縮小
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v0)},
	};

	//回転　(0,0)が原点
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	Vertex2d*pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	//                          仮想アドレス

	//メモリコピー
	memcpy(pV, v, sizeof(v));
	g_VertexBuffer->Unlock();
	//deviceに画像バッファを与える
	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Vertex2d));
	//deviceにindexバッファを与える
	g_pDevice->SetIndices(g_IndexBuffer);
	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}




void Sprite_Uninit(void)
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
	if (g_IndexBuffer)
	{
		g_IndexBuffer->Release();
		g_IndexBuffer = NULL;
	}
}

void Sprite_SetColor(D3DCOLOR color)
{
	g_color = color;
}