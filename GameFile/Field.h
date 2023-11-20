#pragma once

class GameObject;

class Field:GameObject
{
public:
	Field(int modelHandle, float posX, float posY, float posZ);
	~Field();

	void Update();
	void Draw();

private:
	int modelHandle;
	VECTOR pos;
};

