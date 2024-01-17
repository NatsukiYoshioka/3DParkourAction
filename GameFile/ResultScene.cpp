#include"BaseScene.h"
#include"GameManager.h"
#include"common.h"
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
	if (CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		GameManager::ChangeScene(GameManager::SCENE::GAME);
	}
}

void ResultScene::Draw()
{
	DrawString(stringX, stringY, resultString, sceneStringColor);
}