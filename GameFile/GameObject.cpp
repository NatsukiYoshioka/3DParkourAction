#include"DxLib.h"
#include"common.h"
#include "GameObject.h"

//ゲームオブジェクトの初期化
GameObject::GameObject():
	tag(),
	modelHandle(initializeNum)
{
	pos = initializePos;
}

//ゲームオブジェクト後処理
GameObject::~GameObject()
{

}