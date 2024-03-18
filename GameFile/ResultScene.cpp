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

//リザルトシーン初期化
ResultScene::ResultScene():
	isRestart(false),
	transRate(static_cast<float>(initializeNum))
{
	score = GameScene::GetScoreCount();
	input = PadInput::GetInstance();

	//動画のロード
	noiseMovieHandle = LoadGraph(noiseMoviePath);
}

//データの解放
ResultScene::~ResultScene()
{
	if (noiseMovieHandle != noHandle)DeleteGraph(noiseMovieHandle);
}

//リザルトシーン更新
void ResultScene::Update()
{
	if (!Player::GetIsClear() && !isRestart)
	{
		PlayMovieToGraph(noiseMovieHandle);
		if (TellMovieToGraph(noiseMovieHandle) >= movieLength)
		{
			SeekMovieToGraph(noiseMovieHandle, initializeNum);
		}
	}
	if (!isRestart && input->GetInput().Buttons[buttonA] || CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		isRestart = true;
		PauseMovieToGraph(noiseMovieHandle);
	}
	UpdateFade();
}

//フェードイン、アウト更新
void ResultScene::UpdateFade()
{
	//白画像透過率を下げる処理
	if (Transition::GetWhiteTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateWhiteTransition(Transition::GetWhiteTransRate() - addRate);
	}
	//黒画像透過率を下げる処理
	if (Transition::GetBlackTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateBlackTransition(Transition::GetBlackTransRate() - addRate);
	}

	//リスタート時のフェードアウト
	if (isRestart)
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

//リザルトシーン描画
void ResultScene::Draw()
{
	//DrawString(stringX, stringY, resultString, sceneStringColor);
	ChangeFont(titleFontName);
	SetFontSize(scoreStringSize);
	DrawStringF(scoreStringX, scoreStringY, scoreString, scoreStringColor);

	ChangeFont(timeFontName);
	SetFontSize(scoreSize);
	DrawFormatStringF(scoreX, scoreY, scoreColor, "%.1f", score);

	//ゲームオーバー時の描画
	if (!Player::GetIsClear())
	{
		DrawExtendGraph(moviePosX1, moviePosY1, moviePosX2, moviePosY2, noiseMovieHandle, FALSE);
		ChangeFont(titleFontName);
		SetFontSize(gameoverStringSize);
		DrawStringF(gameoverStringX, gameoverStringY, gameoverString, gameoverStringColor);
	}
}