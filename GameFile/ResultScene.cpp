#include"BaseScene.h"
#include"GameManager.h"
#include"GameScene.h"
#include"Font.h"
#include"common.h"
#include"DxLib.h"
#include "ResultScene.h"

const unsigned int ResultScene::scoreStringColor = GetColor(233, 0, 100);
const unsigned int ResultScene::scoreColor = GetColor(147, 255, 216);

ResultScene::ResultScene()
{
	score = GameScene::GetScoreCount();
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_W) != initializeNum)
	{
		GameManager::ChangeScene(GameManager::SCENE::TITLE);
	}
}

void ResultScene::Draw()
{
	//DrawString(stringX, stringY, resultString, sceneStringColor);
	ChangeFont(titleFontName);
	SetFontSize(scoreStringSize);
	DrawStringF(scoreStringX, scoreStringY, scoreString, scoreStringColor);

	ChangeFont(timeFontName);
	SetFontSize(scoreSize);
	DrawFormatStringF(scoreX, scoreY, scoreColor, "%.1f", score);
}