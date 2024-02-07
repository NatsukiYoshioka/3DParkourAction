#pragma once

class BaseScene;
class PadInput;

class ResultScene:public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	void Update();

	void UpdateFade();

	void Draw();
private:
	static constexpr const char* resultString = "RESULT";

	PadInput* input;

	int noiseMovieHandle;
	static constexpr int movieLength = 3800;
	static constexpr const char* noiseMoviePath = "data/UI/noise.mp4";

	static constexpr int moviePosX1 = 0;
	static constexpr int moviePosY1 = 0;
	static constexpr int moviePosX2 = 1920;
	static constexpr int moviePosY2 = 1080;

	static constexpr const char* gameoverString = "GAME OVER";
	static constexpr int gameoverStringSize = 128;
	static constexpr float gameoverStringX = 750.0f;
	static constexpr float gameoverStringY = 300.0f;
	static const unsigned int gameoverStringColor;

	bool restart;
	float score;

	float transRate;

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

