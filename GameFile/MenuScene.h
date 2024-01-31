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
	/// タイトル描画
	/// </summary>
	void DrawTitleString();

	/// <summary>
	/// 選択状態を取得
	/// </summary>
	/// <returns></returns>
	static SELECT GetSelect() { return select; }

	/// <summary>
	/// 選択した状態を取得
	/// </summary>
	/// <returns></returns>
	static SELECT GetChoose() { return choose; }
private:
	static SELECT select;				//メニュー画面選択状態
	static SELECT choose;				//選択確定状態
	bool isChoose;				//選択確定したかどうか

	int cooltime;
	static constexpr int maxCoolTime = 10;

	PadInput* input;			//コントローラー入力情報取得用

	static constexpr int titleFontSize = 128;
	static constexpr int buttonFontSize = 64;						//ボタンの文字サイズ

	static const unsigned int buttonStringColor;					//ボタンの文字カラー
	static const unsigned int titleStringColor;
	static const unsigned int titleStringColor2;

	static constexpr const char* titleString = "Cyber Runner";
	static constexpr int titleStringX = 300;
	static constexpr int titleStringY = 300;
	static constexpr int titleStringY2 = 305;

	static constexpr const char* playString = "PLAY";				//"PLAY"文字列
	static constexpr int playStringX = 440;							//PLAYのX座標

	static constexpr const char* tutorialString = "TUTORIAL";		//"TUTORIAL"文字列
	static constexpr int tutorialStringX = 820;						//TUTORIALのX座標

	static constexpr const char* exitString = "EXIT";				//"EXIT"文字列
	static constexpr int exitStringX = 1345;						//EXITのX座標

	static constexpr const char* menuString = "MENU";
	static constexpr int buttonStringHeight = 717;					//ボタンの文字のY座標
};

