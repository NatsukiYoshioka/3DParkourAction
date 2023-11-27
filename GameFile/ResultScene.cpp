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
	DrawString(0, 16, "RESULT", GetColor(255, 255, 255));
}