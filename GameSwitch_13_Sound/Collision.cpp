#include "Collision.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

int CollisionBB(float bx, float by, float bw, float bh,float px, float py, float pw, float ph)
{
	if ((by + bh / 2) > (py - ph / 2) && (by - bh / 2) < (py + ph / 2) && (bx - bw / 2) < (px + pw / 2) && (bx + bw / 2) > (px - pw / 2))
	{
		
		if ((by +  ph / 2) <= py )
		{
			return 2; // b is upper than p
		}
		else if (by >= (py+ph/2) )
		{
			return 3;//b is lower than p
		}
		else if ((bx +pw / 2) <= px)
		{
			return 4;//b is left 
		}
		else if (bx >=( px + pw / 2))
		{
			return 5;//b is right
		}
		return 1;

	}
	else
	{
		return 0;
	}
}




//  b xia >= p shang  &&    b shang <= p xia  && b you >= p zuo   && b zuo <= p you