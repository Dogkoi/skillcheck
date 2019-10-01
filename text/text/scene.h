#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

enum SCENE
{
	SCENE_TITLE,     //0
	SCENE_GAME,      //1
	SCENE_HIGHSCORE, //2
	SCENE_END,       //3
	SCENE_MAX        //4
};

void Scene_Init(void);
void Scene_Update(void);
void Scene_Draw(void);
void Scene_Uninit(void);
void Scene_SetNextScene(SCENE next_scene);//���̃V�[���o�^
bool Scene_Change(void);//bool���A�v���P�[�V�����̏I����true

#endif // !_SCENE_H_
