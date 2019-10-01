#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3d9.h>

int Texture_SetLoadFile(const char* pFilename, int width, int height);//�e�N�X�`���t�@�C���A�e�N�X�`�����A�e�N�X�`�������@���\��ԍ��iid�j�����t�@�C������񂾂�������
int Texture_Load(void);//�t�@�C���̓ǂݍ��݁��ǂݍ��� �Ȃ�������

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//�\��ԍ�
void Texture_Destroy(int ids[], int count);//��������֐��@int ids[]���������id���������z��̐擪�A�h���X�Acount�z�񐔁@*�H���
void texture_Destroy(void);//�S������֐�
int Texture_GetWidth(int id);
int Texture_GetHeight(int id);

#endif // _TEXTURE_H_
