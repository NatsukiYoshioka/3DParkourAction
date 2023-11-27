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
	DrawString(0, 16, "MENU", GetColor(255, 255, 255));
}