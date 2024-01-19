#pragma once
#include"BaseScene.h"
#include<DxLib.h>

class BaseScene;
class PadInput;

/// <summary>
/// メニューシーン管理クラス
/// </summary>
class MenuScene:public BaseScene
{
public:
	/// <summary>
	/// ゲーム移行選択状態
	/// </summary>
	enum class SELECT
	{
		PLAY,
		TUTORIAL,
		EXIT
	};

	MenuScene();
	~MenuScene();

	/// <summary>
	/// メニューシーン更新
	/// </summary>
	void Update();

	/// <summary>
	/// 入力処理更新
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// メニューシーン描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ボタンに表示する文字の描画
	/// </summary>
	void DrawButtonString();

	/// <summary>
	/// 選択状態を取得
	/// </summary>
	/// <returns></returns>
	static SELECT GetSelect() { return select; }
private:
	static SELECT select;				//メニュー画面選択状態
	SELECT choose;				//選択確定状態
	bool isChoose;				//選択確定したかどうか

	PadInput* input;			//コントローラー入力情報取得用

	static constexpr int buttonFontSize = 64;						//ボタンの文字サイズ

	static const unsigned int buttonStringColor;					//ボタンの文字カラー

	static constexpr const char* playString = "PLAY";				//"PLAY"文字列
	static constexpr int playStringX = 445;							//PLAYのX座標

	static constexpr const char* tutorialString = "TUTORIAL";		//"TUTORIAL"文字列
	static constexpr int tutorialStringX = 840;						//TUTORIALのX座標

	static constexpr const char* exitString = "EXIT";				//"EXIT"文字列
	static constexpr int exitStringX = 1355;						//EXITのX座標

	static constexpr const char* menuString = "MENU";
	static constexpr int buttonStringHeight = 717;					//ボタンの文字のY座標
};

