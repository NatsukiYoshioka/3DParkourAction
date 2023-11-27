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
	DrawString(0, 16, "INGAME", GetColor(255, 255, 255));
}