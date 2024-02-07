#pragma once

class Transition
{
private:
	/// <summary>
	/// �摜�̃��[�h
	/// </summary>
	Transition();

	/// <summary>
	/// �f�[�^�j��
	/// </summary>
	~Transition();
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
	/// <returns>�N���X�̃C���X�^���X</returns>
	static Transition* GetInstance() { return transition; }

	/// <summary>
	/// ���摜�̓��ߗ��ݒ�
	/// </summary>
	/// <param name="transRate">���ߗ�</param>
	static void UpdateWhiteTransition(float transRate);

	/// <summary>
	/// ���摜�̓��ߗ��ݒ�
	/// </summary>
	/// <param name="transRate">���ߗ�</param>
	static void UpdateBlackTransition(float transRate);

	/// <summary>
	/// �摜�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���摜���ߗ��擾
	/// </summary>
	/// <returns>���摜���ߗ�</returns>
	static float GetWhiteTransRate() { return whiteTransRate; }

	/// <summary>
	/// ���摜���ߗ��擾
	/// </summary>
	/// <returns>���摜���ߗ�</returns>
	static float GetBlackTransRate() { return blackTransRate; }
private:
	static Transition* transition;			//�N���X�̃C���X�^���X

	static float whiteTransRate;			//���摜�̓��ߗ�
	static float blackTransRate;			//���摜�̓��ߗ�

	static constexpr float maxTransRate = 1.0f;

	static constexpr float maxFade = 255;	//�ő哧�ߗ�

	int whiteTextureHandle;					//���摜�n���h��
	int blackTextureHandle;					//���摜�n���h��

	static constexpr int texturePosX1 = 0;	//�`�悷��͈͍��W
	static constexpr int texturePosX2 = 1920;
	static constexpr int texturePosY1 = -5;
	static constexpr int texturePosY2 = 1080;

	static constexpr const char* whiteTexturePath = "data/UI/white.png";	//�摜�̃p�X
	static constexpr const char* blackTexturePath = "data/UI/black.png";
};

