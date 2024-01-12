#include"BaseScene.h"
#include"GameManager.h"
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
	
}

void MenuScene::Draw()
{
	DrawString(stringX, stringY, menuString, sceneStringColor);
}