#include"GameManager.h"
#include"BaseScene.h"
#include"MenuScene.h"
#include"Font.h"
#include"common.h"
#include"DxLib.h"
#include "GameScene.h"

const unsigned int GameScene::countColor = GetColor(207, 255, 220);
const unsigned int GameScene::descriptionColor = GetColor(53, 1, 63);

float GameScene::scoreCount = static_cast<float>(initializeNum);

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
	//�c�萧�����Ԃ̌v�Z
	nowCount = maxCount - static_cast<float>((GetNowCount() - startCount) / secondFrame);
	scoreCount = nowCount;
	//�������Ԃ������Ȃ�ƃ��U���g��ʂɈڍs
	if (MenuScene::GetChoose() == MenuScene::SELECT::PLAY && nowCount <= static_cast<float>(initializeNum))
	{
		GameManager::ChangeScene(GameManager::SCENE::RESULT);
	}
}

void GameScene::Draw()
{
	//DrawString(stringX, stringY, inGameString, sceneStringColor);
	//�������ԕ`��
	ChangeFont(timeFontName, DX_CHARSET_DEFAULT);
	SetFontSize(countSize);
	if (MenuScene::GetChoose() == MenuScene::SELECT::PLAY)
	{
		DrawFormatStringF(countX, countY, countColor, "%.1f", nowCount);

		//�ڕW�`��
		ChangeFont(configFontName, DX_CHARSET_DEFAULT);
		SetFontSize(targetSize);
		DrawStringF(targetStringX, targetStringY, targetString, descriptionColor);
	}
	else
	{
		DrawStringF(countX, countY, tutorialCount, countColor);

		//�ڕW�`��
		ChangeFont(configFontName, DX_CHARSET_DEFAULT);
		SetFontSize(targetSize);
		DrawStringF(targetStringX, targetStringY, tutorialString, descriptionColor);
	}
	//��������`��
	ChangeFont(configFontName, DX_CHARSET_DEFAULT);
	SetFontSize(descriptionSize);
	DrawStringF(descriptionX, runStringY, runString, descriptionColor);
	DrawStringF(descriptionX, cameraStringY, cameraString, descriptionColor);
	DrawStringF(descriptionX, jumpStringY, jumpString, descriptionColor);
	DrawStringF(descriptionX, slideStringY, slideString, descriptionColor);
}