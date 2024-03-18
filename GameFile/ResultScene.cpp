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

//���U���g�V�[��������
ResultScene::ResultScene():
	isRestart(false),
	transRate(static_cast<float>(initializeNum))
{
	score = GameScene::GetScoreCount();
	input = PadInput::GetInstance();

	//����̃��[�h
	noiseMovieHandle = LoadGraph(noiseMoviePath);
}

//�f�[�^�̉��
ResultScene::~ResultScene()
{
	if (noiseMovieHandle != noHandle)DeleteGraph(noiseMovieHandle);
}

//���U���g�V�[���X�V
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

//�t�F�[�h�C���A�A�E�g�X�V
void ResultScene::UpdateFade()
{
	//���摜���ߗ��������鏈��
	if (Transition::GetWhiteTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateWhiteTransition(Transition::GetWhiteTransRate() - addRate);
	}
	//���摜���ߗ��������鏈��
	if (Transition::GetBlackTransRate() > static_cast<float>(initializeNum))
	{
		Transition::UpdateBlackTransition(Transition::GetBlackTransRate() - addRate);
	}

	//���X�^�[�g���̃t�F�[�h�A�E�g
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

//���U���g�V�[���`��
void ResultScene::Draw()
{
	//DrawString(stringX, stringY, resultString, sceneStringColor);
	ChangeFont(titleFontName);
	SetFontSize(scoreStringSize);
	DrawStringF(scoreStringX, scoreStringY, scoreString, scoreStringColor);

	ChangeFont(timeFontName);
	SetFontSize(scoreSize);
	DrawFormatStringF(scoreX, scoreY, scoreColor, "%.1f", score);

	//�Q�[���I�[�o�[���̕`��
	if (!Player::GetIsClear())
	{
		DrawExtendGraph(moviePosX1, moviePosY1, moviePosX2, moviePosY2, noiseMovieHandle, FALSE);
		ChangeFont(titleFontName);
		SetFontSize(gameoverStringSize);
		DrawStringF(gameoverStringX, gameoverStringY, gameoverString, gameoverStringColor);
	}
}