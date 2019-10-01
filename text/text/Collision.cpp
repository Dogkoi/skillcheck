#include "Collision.h"
#include "Enemy.h"
#include "Bullet.h"

bool CirCle_Circle(CirCle* pA, CirCle* pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius) > D3DXVec2LengthSq(&(pA->position - pB->position));
}