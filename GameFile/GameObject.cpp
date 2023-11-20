#include"DxLib.h"
#include"common.h"
#include "GameObject.h"

GameObject::GameObject():
	modelHandle(initializeNum)
{
	pos = initializePos;
}

GameObject::~GameObject()
{

}