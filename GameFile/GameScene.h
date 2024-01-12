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
};

