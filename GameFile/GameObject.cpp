#include"DxLib.h"
#include"common.h"
#include "GameObject.h"

//�Q�[���I�u�W�F�N�g�̏�����
GameObject::GameObject():
	tag(),
	modelHandle(initializeNum)
{
	pos = initializePos;
}

GameObject::~GameObject()
{

}