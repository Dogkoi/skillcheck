#include "Judgement.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Collision.h"
#include "Explosion.h"
#include "score.h"
#include "Game.h"
#include "player.h"
#include "fade.h"
#include "scene.h"

static void hitCheck_Bullet_Enemy(void);
static void hitCheck_Player_Enemy(void);
Enemy *pg_Enemy;
Player *pg_Player;


void Judgement_Update(void)
{
	hitCheck_Bullet_Enemy();
	hitCheck_Player_Enemy();
}

void hitCheck_Bullet_Enemy(void)
{
	pg_Enemy = GetEnemyposition();
	for (int i = 0; i < BULLET_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if (Bullet_IsUsed(i) && Enemy_IsUsed(j))
			{
				if (CirCle_Circle(Bullet_GetCollision(i), Enemy_GetCollision(j)))
				{
					/*とく点を入れるなるこのタイミング*/
					Enemy_Destroy(j);//すぐ壊すのではなくライフを持ったり
					Addscore(50);
					Explosion_Create((pg_Enemy + j)->position.x, (pg_Enemy + j)->position.y);
					Bullet_Destroy(i);//やろなければかんつう弾
				}
			}

		}
		
	}

}

static void hitCheck_Player_Enemy(void)
{
	pg_Player = GetPlayerPosition();
	pg_Enemy = GetEnemyposition();
	/*for (int i = 0; i < PLAYER_MAX; i++)
	{
		
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			switch ((pg_Enemy + j)->type)
			{
			case ENEMY_FISH2:
				if (Player_IsUsed(i) && Enemy_IsUsed(j))
				{
					if (CirCle_Circle(Player_GetCollision(i), Enemy_GetCollision(j)))
					{
						Player_Destroy(i);
						Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
						Scene_SetNextScene(SCENE_HIGHSCORE);
						Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
					}
				}
			}
			break;
			
		}
	}*/
	for (int i = 0; i < ENEMY_MAX; i++)
    {
		switch ((pg_Enemy + i)->type)
		{
		case ENEMY_FISH1:

			for (int j = 0; j < PLAYER_MAX; j++)
			{

				if (Enemy_IsUsed(i) && Player_IsUsed(j))
				{
					if (CirCle_Circle(Enemy_GetCollision(i), Player_GetCollision(j)))
					{
						Player_Destroy(j);
						Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
						Scene_SetNextScene(SCENE_HIGHSCORE);
					    Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
					}
				}
			}
			break;
		}
	}
    
}