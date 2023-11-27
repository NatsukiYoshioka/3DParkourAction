#pragma once

class BaseScene;

class ResultScene:public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	void Update();
	void Draw();
};

