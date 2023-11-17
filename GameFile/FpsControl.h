#pragma once

/// <summary>
/// �V���O���g���p�^�[����FPS����N���X
/// </summary>
class FpsControl
{
private:
	/// <summary>
	/// �J�E���g�̏�����
	/// </summary>
	FpsControl();

	/// <summary>
	/// �N���X�㏈��
	/// </summary>
	~FpsControl() {}
public:
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�j��
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�N���X�ϐ�</returns>
	static FpsControl* GetInstance() { return fpsControl; }

	/// <summary>
	/// �t���[�����[�g�v�Z
	/// </summary>
	void Update();

	/// <summary>
	/// FPS�\��
	/// </summary>
	void Draw();

	/// <summary>
	/// �t���[�����[�g����
	/// </summary>
	void Control();

private:
	static FpsControl* fpsControl;	//�N���X�ϐ�
	int startTime;					//����J�n����
	int count;						//�J�E���^
	float nowFps;					//���݂�Fps
	const int sampleAvg = 60;		//���ς����T���v����
	const int FPS = 60;				//�ݒ肵��FPS

	static constexpr int fpsX = 0;							//FPS��\������X���W
	static constexpr int fpsY = 0;							//FPS��\������Y���W
	static const unsigned int blueColor;					//�F��ێ�����萔
	static constexpr const char* valueString = "%.1f";		//FPS�l��\�����镶����
};

