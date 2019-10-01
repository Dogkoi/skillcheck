#pragma once

#include "system.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


enum SCENE
{
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
};




void SetScene(SCENE Scene);
