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
const unsigned int ResultScene::gameoverStringColor = GetColor(233, 0, 100);

ResultScene::ResultScene():
	restart(false),
	transRate(static_cast<float>(initializeNum))
{
	score = GameScene::GetScoreCount();
	input = PadInput::GetInstance();

	noiseMovieHandle = LoadGraph(noiseMoviePath);
}

ResultScene::~ResultScene()
{
	if (noiseMovieHandle != noHandle)DeleteGraph(noiseMovieHandle);
}

void ResultScene::Update()
{
	if (!Player::GetIsClear() && !restart)
	{
		PlayMovieToGraph(noiseMovieHandle);
		if (TellMovieToGraph(noiseMovieHandle) >= movieLength)
		{
			SeekMovieToGraph(noiseMovieHandle, initializeNum);
		}
	}
	if (!restart && input->GetInput().Buttons[buttonA] || CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		restart = true;
		PauseMovieToGraph(noiseMovieHandle);
	}
	UpdateFade();
}

void ResultScene::UpdateFade()
{
	//”’‰æ‘œ“§‰ß—¦‚ð‰º‚°‚éˆ—
	if (Transition::GetWhiteTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateWhiteTransition(Transition::GetWhiteTransRate() - addRate);
	}
	//•‰æ‘œ“§‰ß—¦‚ð‰º‚°‚éˆ—
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
		DrawExtendGraph(moviePosX1, moviePosY1, moviePosX2, moviePosY2, noiseMovieHandle, FALSE);
		ChangeFont(titleFontName);
		SetFontSize(gameoverStringSize);
		DrawStringF(gameoverStringX, gameoverStringY, gameoverString, gameoverStringColor);
	}
}