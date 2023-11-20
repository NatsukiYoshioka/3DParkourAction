#pragma once

class GameObject;
class Player :public GameObject
{
public:
	Player(int modelHandle);
	~Player();

	void Update();
	void Draw();

private:

};

