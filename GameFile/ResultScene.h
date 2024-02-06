#pragma once

class BaseScene;

class ResultScene:public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	void Update();
	void Draw();
private:
	static constexpr const char* resultString = "RESULT";

	float score;

	static constexpr const char* scoreString = "SCORE";			//スコア文字の描画設定
	static constexpr int scoreStringSize = 128;
	static constexpr float scoreStringX = 650.0f;
	static constexpr float scoreStringY = 350.0f;
	static const unsigned int scoreStringColor;

	static constexpr int scoreSize = 180;						//スコア数の描画設定
	static constexpr float scoreX = 725.0f;
	static constexpr float scoreY = 600.0f;
	static const unsigned int scoreColor;
};

