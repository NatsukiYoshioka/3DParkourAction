#include"BaseScene.h"
#include"GameManager.h"
#include"Font.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "MenuScene.h"

MenuScene::SELECT MenuScene::select = SELECT::PLAY;
const unsigned int MenuScene::buttonStringColor = GetColor(49, 225, 247);

MenuScene::MenuScene():
	choose(SELECT::PLAY),
	isChoose(false)
{
	input = PadInput::GetInstance();
}

MenuScene::~MenuScene()
{

}

//メニューシーン更新
void MenuScene::Update()
{
	UpdateInput();
}

//入力処理更新
void MenuScene::UpdateInput()
{
	//プレイ選択処理
	if (!isChoose)
	{
		if ((select == SELECT::PLAY && (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)) || (select == SELECT::EXIT && (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)))
		{
			select = SELECT::TUTORIAL;
		}
		else if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
		{
			select = SELECT::EXIT;
		}
		else if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
		{
			select = SELECT::PLAY;
		}

		if (input->GetInput().Buttons[buttonA] || CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
		{
			isChoose = true;
			choose = select;
		}
	}
	
	if (CheckHitKey(KEY_INPUT_RETURN) != initializeNum)
	{
		GameManager::ChangeScene(GameManager::SCENE::GAME);
	}
}

//メニューシーン描画
void MenuScene::Draw()
{
	DrawString(stringX, stringY, menuString, sceneStringColor);

	DrawButtonString();
}

//ボタンに表示する文字の描画
void MenuScene::DrawButtonString()
{
	ChangeFont(titleFontName, DX_CHARSET_DEFAULT);
	SetFontSize(buttonFontSize);
	DrawString(playStringX, buttonStringHeight, playString, buttonStringColor);
	DrawString(tutorialStringX, buttonStringHeight, tutorialString, buttonStringColor);
	DrawString(exitStringX, buttonStringHeight, exitString, buttonStringColor);
	ChangeFont(timeFontName, DX_CHARSET_DEFAULT);
	SetFontSize(16);
}