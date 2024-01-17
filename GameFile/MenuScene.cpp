#include"BaseScene.h"
#include"GameManager.h"
#include"Font.h"
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

	ChangeFont(titleFontName, DX_CHARSET_DEFAULT);
	SetFontSize(128);
	DrawString(600,640,"press Enter",GetColor(29,43,83));
	ChangeFont(timeFontName, DX_CHARSET_DEFAULT);
	SetFontSize(16);
}