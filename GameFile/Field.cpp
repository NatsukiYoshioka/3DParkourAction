#include"DxLib.h"
#include"GameObject.h"
#include "Field.h"

Field::Field(int modelHandle, float posX, float posY, float posZ)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;
}

Field::~Field()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

void Field::Update()
{

}

void Field::Draw()
{

}