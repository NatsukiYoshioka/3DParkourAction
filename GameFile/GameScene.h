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
	static constexpr int countSize = 112;						//�J�E���g�̕����T�C�Y
	static constexpr float countX = 1275.0f;					//�J�E���g�̕���X���W
	static constexpr float countY = 200.0f;						//�J�E���g�̕���Y���W
	static const unsigned int countColor;						//�J�E���g�̕����J���[
	static constexpr float maxCount = 100.0f;					//��������
	int startCount;												//�ŏ��̃J�E���g����
	float nowCount;												//�c�萧������
};

