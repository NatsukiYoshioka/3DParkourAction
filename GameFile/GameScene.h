#pragma once

class BaseScene;

class GameScene:public BaseScene
{
public:
	GameScene();
	~GameScene();
	
	void Update();
	void Draw();
private:
	static constexpr const char* inGameString = "INGAME";
	static constexpr int countSize = 112;						//カウントの文字サイズ
	static constexpr float countX = 1275.0f;					//カウントの文字X座標
	static constexpr float countY = 200.0f;						//カウントの文字Y座標
	static const unsigned int countColor;						//カウントの文字カラー
	static constexpr float maxCount = 100.0f;					//制限時間
	int startCount;												//最初のカウント時間
	float nowCount;												//残り制限時間
};

