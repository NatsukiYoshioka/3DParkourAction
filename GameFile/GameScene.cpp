#include"BaseScene.h"
#include"DxLib.h"
#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Update()
{

}

void GameScene::Draw()
{
	DrawString(stringX, stringY, inGameString, sceneStringColor);
}