#include"BaseScene.h"
#include"GameManager.h"
#include"GameScene.h"
#include"Player.h"
#include"PadInput.h"
#include"Font.h"
#include"Transition.h"
#include"common.h"
#include"DxLib.h"
#include "ResultScene.h"

const unsigned int ResultScene::scoreStringColor = GetColor(233, 0, 100);
const unsigned int ResultScene::scoreColor = GetColor(147, 255, 216);

ResultScene::ResultScene():
	restart(false),
	transRate(static_cast<float>(initializeNum))
{
	score = GameScene::GetScoreCount();
	input = PadInput::GetInstance();
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	if (!restart && input->GetInput().Buttons[buttonA] || CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		restart = true;
	}
	UpdateFade();
}

void ResultScene::UpdateFade()
{
	if (Transition::GetWhiteTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateWhiteTransition(Transition::GetWhiteTransRate() - addRate);
	}
	if (Transition::GetBlackTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateBlackTransition(Transition::GetBlackTransRate() - addRate);
	}

	if (restart)
	{
		transRate += addRate;
		if (transRate >= maxTransRate)
		{
			transRate = maxTransRate;
		}
		Transition::UpdateWhiteTransition(transRate);
		if (transRate >= maxTransRate)
		{
			GameManager::ChangeScene(GameManager::SCENE::TITLE);
		}
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

	if (!Player::GetIsClear())
	{

	}
}