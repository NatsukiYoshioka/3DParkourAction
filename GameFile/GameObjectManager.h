#pragma once

using namespace std;

class Load;
class GameObject;

/// <summary>
/// �Q�[���I�u�W�F�N�g�Ǘ��N���X
/// </summary>
class GameObjectManager
{
private:
	/// <summary>
	/// �f�[�^�̃��[�h�ƃI�u�W�F�N�g�̐���
	/// </summary>
	GameObjectManager();

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~GameObjectManager();
	
	/// <summary>
	/// �I�u�W�F�N�g�S�̂̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �I�u�W�F�N�g�S�̂̕`��
	/// </summary>
	void Draw();
public:
	/// <summary>
	/// �C���X�^���X����x����������Ă��Ȃ�������C���X�^���X�𐶐�����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�̔j��
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�N���X�̃C���X�^���X</returns>
	static GameObjectManager* GetInstance() { gameObjectManager; }

private:
	static GameObjectManager* gameObjectManager;		//�Q�[���I�u�W�F�N�g�Ǘ��N���X�̃C���X�^���X
	Load* load;											//���[�h�N���X
	static const string dataFilePath;					//�f�[�^�i�[�t�@�C���̃p�X

	vector<GameObject*> objectInstance;					//�I�u�W�F�N�g�̃C���X�^���X
};

