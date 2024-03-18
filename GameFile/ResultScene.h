#pragma once

class BaseScene;
class PadInput;

class ResultScene:public BaseScene
{
public:
	/// <summary>
	/// ���U���g�V�[��������
	/// </summary>
	ResultScene();

	/// <summary>
	/// �f�[�^���
	/// </summary>
	~ResultScene();

	/// <summary>
	/// ���U���g�V�[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �t�F�[�h�C���A�A�E�g�X�V
	/// </summary>
	void UpdateFade();

	/// <summary>
	/// ���U���g�V�[���`��
	/// </summary>
	void Draw();
private:
	static constexpr const char* resultString = "RESULT";

	PadInput* input;

	int noiseMovieHandle;
	static constexpr int movieLength = 3800;
	static constexpr const char* noiseMoviePath = "data/UI/noise.mp4";

	//�Q�[���I�[�o�[����o�͔͈͍��W
	static constexpr int moviePosX1 = 0;
	static constexpr int moviePosY1 = 0;
	static constexpr int moviePosX2 = 1920;
	static constexpr int moviePosY2 = 1080;

	//�Q�[���I�[�o�[�����`��萔
	static constexpr const char* gameoverString = "GAME OVER";
	static constexpr int gameoverStringSize = 128;
	static constexpr float gameoverStringX = 750.0f;
	static constexpr float gameoverStringY = 300.0f;
	static const unsigned int gameoverStringColor;

	bool isRestart;												//���X�^�[�g���邩�ǂ���
	float score;												//�Q�[���N���A���̃X�R�A

	float transRate;											//�g�����W�V�������ߗ�

	static constexpr const char* scoreString = "SCORE";			//�X�R�A�����̕`��ݒ�
	static constexpr int scoreStringSize = 128;
	static constexpr float scoreStringX = 650.0f;
	static constexpr float scoreStringY = 350.0f;
	static const unsigned int scoreStringColor;

	static constexpr int scoreSize = 180;						//�X�R�A���̕`��ݒ�
	static constexpr float scoreX = 725.0f;
	static constexpr float scoreY = 600.0f;
	static const unsigned int scoreColor;
};

