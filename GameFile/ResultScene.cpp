#include"BaseScene.h"
#include"DxLib.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{

}

void ResultScene::Draw()
{
	DrawString(stringX, stringY, resultString, sceneStringColor);
}