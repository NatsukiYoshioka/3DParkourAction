#pragma once
#include"DxLib.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	int modelHandle;
	VECTOR pos;
};

