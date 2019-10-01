#include <d3d9.h>
#include <d3dx9.h>
#include "Debug.h"
#include "direct3d.h"
#include "Collision.h"

//定数
#define DEBUG_CIRCLE_VERTEX_NUM (8)
#define DEBUG_CIRCLE_MAX (4096)

typedef struct DebugCircleVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;

}DebugCircleVertex;

#define FVF_DEBUG_CIRCLE_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//グローバル変数
static LPDIRECT3DDEVICE9 g_pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
CirCle g_Circles[DEBUG_CIRCLE_MAX];
int g_CircleCount = 0;
D3DCOLOR g_color = 0xFFFFFFFF;
D3DCOLOR g_colors[DEBUG_CIRCLE_MAX];

void Debug_Init(void)
{
	//初期化
	//頂点バッファを作る 量＝DEBUG_CIRCLE_VERTEX_NUM
	//                      *DEBUG_CIRCLE_MAX
	//                      *sizeof(DebugCircle)
	g_pDevice = GetDevice();
	g_pDevice->CreateVertexBuffer(sizeof(DebugCircleVertex) * DEBUG_CIRCLE_VERTEX_NUM * DEBUG_CIRCLE_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_CIRCLE_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	//インデックスバッファ　量＝ DEBUG_CIRCLE_VERTEX_NUM * 2
	//                         * DEBUG_CIRCLE_MAX * sizeof(WORD)
	g_pDevice->CreateIndexBuffer(sizeof(WORD) * DEBUG_CIRCLE_VERTEX_NUM * 2 * DEBUG_CIRCLE_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

void Debug_Uninit(void)
{

}

void Debug_Begin(void)
{
	g_CircleCount = 0;

}

void Debug_End(void)
{
	static const float A = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX_NUM;
	DebugCircleVertex * pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	for (int i = 0; i < g_CircleCount; i++)
	{
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM;
		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pV[startIndex + j].position.x = cosf(A * j) * g_Circles[i].radius + g_Circles[i].position.x;
			pV[startIndex + j].position.y = sinf(A * j) * g_Circles[i].radius + g_Circles[i].position.y;
			pV[startIndex + j].position.z = 0.0f;
			pV[startIndex + j].position.w = 1.0f;
			pV[startIndex + j].color = g_colors[i];
		}
	}
	g_pVertexBuffer->Unlock();

	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
	for (int i = 0; i < g_CircleCount; i++)
	{
		int startIndex = DEBUG_CIRCLE_VERTEX_NUM * 2 * i;
		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pI[startIndex + j * 2 + 0] = startIndex + j;
			pI[startIndex + j * 2 + 1] = startIndex + ((j + 1) % DEBUG_CIRCLE_VERTEX_NUM);
		}
	}
	g_pIndexBuffer->Unlock();

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(DebugCircleVertex));
	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0,
		g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM, 0,
		g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM);
}

void Debug_DrawCircle(float x, float y, float radius)
{
	g_colors[g_CircleCount] = g_color;
	g_Circles[g_CircleCount].position.x = x;
	g_Circles[g_CircleCount].position.y = y;
	g_Circles[g_CircleCount].radius = radius;
	g_CircleCount++;
}

void Debug_SetColor(D3DCOLOR color)
{
	g_color = color;
}

