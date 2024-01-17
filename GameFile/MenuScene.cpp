#include"BaseScene.h"
#include"GameManager.h"
#include"common.h"
#include"DxLib.h"
#include "MenuScene.h"

MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		GameManager::ChangeScene(GameManager::SCENE::GAME);
	}
}

void MenuScene::Draw()
{
	DrawString(stringX, stringY, menuString, sceneStringColor);
	SetFontSize(128);
	DrawString(600,640,"press Enter",GetColor(29,43,83));
	SetFontSize(16);
}