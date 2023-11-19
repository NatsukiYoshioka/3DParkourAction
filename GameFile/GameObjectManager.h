#pragma once

using namespace std;

class GameObject;

/// <summary>
/// �Q�[���I�u�W�F�N�g�Ǘ��N���X
/// </summary>
class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
	
public:
	/// <summary>
	/// �C���X�^���X����x����������Ă��Ȃ�������C���X�^���X�𐶐�����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�N���X�̃C���X�^���X</returns>
	static GameObjectManager* GetInstance() { gameObjectManager; }

private:
	static GameObjectManager* gameObjectManager;		//�Q�[���I�u�W�F�N�g�Ǘ��N���X�̃C���X�^���X
	vector<GameObject*> objectInstance;					//�I�u�W�F�N�g�̃C���X�^���X
};

