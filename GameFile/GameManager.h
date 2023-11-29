#pragma once

class BaseScene;
class GameObjectManager;
class PadInput;

/// <summary>
/// �Q�[���S�̂̊Ǘ�������N���X
/// </summary>
class GameManager
{
private:
	/// <summary>
	/// �V�[���̏������ƃI�u�W�F�N�g�̐���
	/// </summary>
	GameManager();

	/// <summary>
	/// �N���X�̌㏈��
	/// </summary>
	~GameManager();

public:
	/// <summary>
	/// �V�[���̏�Ԃ��Ǘ�
	/// </summary>
	enum class SCENE
	{
		TITLE,								//�^�C�g�����
		GAME,								//�Q�[�����
		RESULT								//���U���g���
	};

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
	static GameManager* GetInstance() { return sceneManager; }

	/// <summary>
	/// �V�[���������ɂ���ĕς���֐�
	/// </summary>
	/// <param name="scene">�ύX����V�[��</param>
	void ChangeScene(SCENE scene);

	/// <summary>
	/// ���݂̃V�[���̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���݂̃V�[���̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���̏�Ԃ��擾
	/// </summary>
	/// <returns>�V�[���̏��</returns>
	SCENE GetGameStatus() { return sceneStatus; }

private:
	static GameManager* sceneManager;			//�N���X�̃C���X�^���X
	static BaseScene* nowScene;					//���݂̃V�[��
	SCENE sceneStatus;							//�V�[���̏��

	GameObjectManager* gameObjectManager;		//�Q�[���I�u�W�F�N�g�Ǘ��N���X
	PadInput* input;
};

