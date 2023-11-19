#pragma once
#include"GameObejctTag.h"
#include"DxLib.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

protected:
	int modelHandle;
	VECTOR pos;
	ObjectTag tag;
};

