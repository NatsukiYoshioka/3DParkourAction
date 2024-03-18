#pragma once

class BaseScene;

class GameScene:public BaseScene
{
public:
	GameScene();
	~GameScene();
	
	void Update();
	void Draw();

	/// <summary>
	/// 残り制限時間取得
	/// </summary>
	/// <returns>残り制限時間</returns>
	static float GetScoreCount() { return scoreCount; }
private:
	static constexpr const char* inGameString = "INGAME";
	static constexpr int countSize = 112;						//カウントの文字サイズ
	static constexpr float countX = 1275.0f;					//カウントの文字X座標
	static constexpr float countY = 200.0f;						//カウントの文字Y座標
	static const unsigned int countColor;						//カウントの文字カラー
	static constexpr float maxCount = 100.0f;					//制限時間
					
	static constexpr const char* tutorialCount = "99.9";		//チュートリアル時の制限時間表記


	//操作説明用定数
	static constexpr int descriptionSize = 48;					//文字サイズ
	static const unsigned int descriptionColor;					//文字カラー
	static constexpr const char* jumpString = "JUMP";			//文字列
	static constexpr float jumpStringY = 865.0f;

	static constexpr const char* keepString = "KEEP";
	static constexpr const char* highJumpString = "HIGH JUMP";
	static constexpr float keepStringX = 1250.0f;
	static constexpr float keepStringY = 902.5f;
	static constexpr float highJumpStringX = 1450.0f;

	static constexpr const char* slideString = "SLIDE";
	static constexpr float slideStringY = 940.0f;

	static constexpr const char* runString = "RUN";
	static constexpr float runStringY = 715.0f;

	static constexpr const char* cameraString = "CAMERA";
	static constexpr float cameraStringY = 790.0f;

	static constexpr float descriptionX = 1350.0f;

	
	static constexpr float targetStringX = 50.0f;				//目標文字座標
	static constexpr float targetStringY = 75.0f;

	static constexpr int targetSize = 48;						//目標文字サイズ

	static constexpr const char* targetString = "RUN FROM TIME!!";
	static constexpr const char* tutorialString = "GO TO THE WARP HOLE";

	int startCount;												//最初のカウント時間
	float nowCount;												//残り制限時間
	static float scoreCount;									//スコア用時間
};

