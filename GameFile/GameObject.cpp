#include"DxLib.h"
#include"common.h"
#include "GameObject.h"

GameObject::GameObject():
	tag(),
	modelHandle(initializeNum)
{
	pos = initializePos;
}

GameObject::~GameObject()
{

}