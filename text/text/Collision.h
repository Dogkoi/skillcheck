#pragma once
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <d3d9.h>
#include <d3dx9.h>

typedef struct Circle_tag
{
	D3DXVECTOR2 position;
	float radius;
}CirCle;

bool CirCle_Circle(CirCle* pA, CirCle* pB);
#endif // _COLLISION_H_
