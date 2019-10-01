#include <d3d9.h>
#include <d3dx9.h>
#include "direct3d.h"
#include "common.h"
#include "texture.h"

/*--------------------------------------------------------------------------------
-      ���_�f�[�^�\���́i���_�̌`�i�t�H�[�}�b�g�j�̐錾

--------------------------------------------------------------------------------*/

typedef struct Vertex2d_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;//���W�̎��ɂ��邱��
	D3DXVECTOR2 UV;//���_�\���̂�UV�ǉ�     U--x V--y
}Vertex2d;
/*------------------------------------------------------------------
	  FVF�̐錾
-------------------------------------------------------------------*/
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


static D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);
static LPDIRECT3DDEVICE9 g_pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_IndexBuffer = NULL;

void Sprite_Init(void)
{
	g_pDevice = GetDevice();
	g_pDevice->CreateVertexBuffer(sizeof(Vertex2d) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);//�l���_�̃������~�����A����������ǂ߂�A����Ȃ��Ă������@0�ɏ���
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
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//���S�ړ�����
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
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//���0�S���̈Ӗ��E(void**)&pV ���z�A�h���X�E//lock�@CPU GPU�ꏏ
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


	//	WORD index[] = { 0,1,2,1,3,2 };//WORD 0-65535���_ 


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
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//���S�ړ�����
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
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);//���0�S���̈Ӗ��E(void**)&pV ���z�A�h���X�E//lock�@CPU GPU�ꏏ
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


	//	WORD index[] = { 0,1,2,1,3,2 };//WORD 0-65535���_ 


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
	//���_�f�[�^(�g���C�A���O���X�g���b�v)
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
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//���ɖ߂�
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   �g��A�k��
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0)},
	};

	//��]�@(0,0)�����_
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	//FVF�̐ݒ�
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//�e�N�X�`���̐ݒ�
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z, bool isright)
//                                                                                                      ��]�̒��S���W
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//���_�f�[�^(�g���C�A���O���X�g���b�v)
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
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//���ɖ߂�
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   �g��A�k��
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v0)},
	};

	//��]�@(0,0)�����_
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	Vertex2d*pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	//                          ���z�A�h���X

	//�������R�s�[
	memcpy(pV, v, sizeof(v));
	g_VertexBuffer->Unlock();
	//device�ɉ摜�o�b�t�@��^����
	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Vertex2d));
	//device��index�o�b�t�@��^����
	g_pDevice->SetIndices(g_IndexBuffer);
	//FVF�̐ݒ�
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//�e�N�X�`���̐ݒ�
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