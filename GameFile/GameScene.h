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
	/// �c�萧�����Ԏ擾
	/// </summary>
	/// <returns>�c�萧������</returns>
	static float GetScoreCount() { return scoreCount; }
private:
	static constexpr const char* inGameString = "INGAME";
	static constexpr int countSize = 112;						//�J�E���g�̕����T�C�Y
	static constexpr float countX = 1275.0f;					//�J�E���g�̕���X���W
	static constexpr float countY = 200.0f;						//�J�E���g�̕���Y���W
	static const unsigned int countColor;						//�J�E���g�̕����J���[
	static constexpr float maxCount = 100.0f;					//��������
					
	static constexpr const char* tutorialCount = "99.9";		//�`���[�g���A�����̐������ԕ\�L


	//��������p�萔
	static constexpr int descriptionSize = 48;					//�����T�C�Y
	static const unsigned int descriptionColor;					//�����J���[
	static constexpr const char* jumpString = "JUMP";			//������
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

	
	static constexpr float targetStringX = 50.0f;				//�ڕW�������W
	static constexpr float targetStringY = 75.0f;

	static constexpr int targetSize = 48;						//�ڕW�����T�C�Y

	static constexpr const char* targetString = "RUN FROM TIME!!";
	static constexpr const char* tutorialString = "GO TO THE WARP HOLE";

	int startCount;												//�ŏ��̃J�E���g����
	float nowCount;												//�c�萧������
	static float scoreCount;									//�X�R�A�p����
};

