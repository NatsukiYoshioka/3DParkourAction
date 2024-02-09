#include"GameManager.h"
#include"BaseScene.h"
#include"MenuScene.h"
#include"Transition.h"
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
	//écÇËêßå¿éûä‘ÇÃåvéZ
	if (nowCount >= static_cast<float>(initializeNum))
	{
		nowCount = maxCount - static_cast<float>((GetNowCount() - startCount) / secondFrame);
	}
	if (nowCount <= static_cast<float>(initializeNum)) nowCount = static_cast<float>(initializeNum);
	scoreCount = nowCount;
	//êßå¿éûä‘Ç™ñ≥Ç≠Ç»ÇÈÇ∆ÉäÉUÉãÉgâÊñ Ç…à⁄çs
	if (MenuScene::GetChoose() == MenuScene::SELECT::PLAY && nowCount <= static_cast<float>(initializeNum))
	{
		Transition::UpdateBlackTransition(Transition::GetBlackTransRate() + addRate);
		if (Transition::GetBlackTransRate() >= maxTransRate)
		{
			GameManager::ChangeScene(GameManager::SCENE::RESULT);
		}
	}
}

void GameScene::Draw()
{
	//DrawString(stringX, stringY, inGameString, sceneStringColor);
	//êßå¿éûä‘ï`âÊ
	ChangeFont(timeFontName, DX_CHARSET_DEFAULT);
	SetFontSize(countSize);
	if (MenuScene::GetChoose() == MenuScene::SELECT::PLAY)
	{
		DrawFormatStringF(countX, countY, countColor, "%.1f", nowCount);

		//ñ⁄ïWï`âÊ
		ChangeFont(configFontName, DX_CHARSET_DEFAULT);
		SetFontSize(targetSize);
		DrawStringF(targetStringX, targetStringY, targetString, descriptionColor);
	}
	else
	{
		DrawStringF(countX, countY, tutorialCount, countColor);

		//ñ⁄ïWï`âÊ
		ChangeFont(configFontName, DX_CHARSET_DEFAULT);
		SetFontSize(targetSize);
		DrawStringF(targetStringX, targetStringY, tutorialString, descriptionColor);
	}
	//ëÄçÏê‡ñæï`âÊ
	ChangeFont(configFontName, DX_CHARSET_DEFAULT);
	SetFontSize(descriptionSize);
	DrawStringF(descriptionX, runStringY, runString, countColor);
	DrawStringF(descriptionX, cameraStringY, cameraString, countColor);
	DrawStringF(descriptionX, jumpStringY, jumpString, countColor);
	DrawStringF(keepStringX, keepStringY, keepString, countColor);
	DrawStringF(highJumpStringX, keepStringY, highJumpString, countColor);
	DrawStringF(descriptionX, slideStringY, slideString, countColor);
}