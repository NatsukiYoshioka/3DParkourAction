#pragma once

class BaseScene;

class MenuScene:public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void Update();
	void Draw();
};

