#include"BaseScene.h"
#include"MenuScene.h"
#include"Font.h"
#include"common.h"
#include"DxLib.h"
#include "GameScene.h"

const unsigned int GameScene::countColor = GetColor(207, 255, 220);

GameScene::GameScene():
	startCount(initializeNum),
	nowCount(static_cast<float>(initializeNum))
{
	startCount = GetNowCount();
}

GameScene::~GameScene()
{
	
}

void GameScene::Update()
{
	nowCount = maxCount - static_cast<float>((GetNowCount() - startCount) / secondFrame);
}

void GameScene::Draw()
{
	//DrawString(stringX, stringY, inGameString, sceneStringColor);
	if (MenuScene::GetChoose() == MenuScene::SELECT::PLAY)
	{
		ChangeFont(timeFontName, DX_CHARSET_DEFAULT);
		SetFontSize(countSize);
		DrawFormatStringF(countX, countY, countColor, "%.1f", nowCount);
	}
}