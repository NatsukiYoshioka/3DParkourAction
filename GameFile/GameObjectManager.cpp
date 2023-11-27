#include<vector>
#include<string>
#include"Load.h"
#include"GameObject.h"
#include"Player.h"
#include"Field.h"
#include"Obstacle.h"
#include"common.h"
#include "GameObjectManager.h"
using namespace std;

GameObjectManager* GameObjectManager::gameObjectManager = nullptr;
const string GameObjectManager::dataFilePath = "data/pathfile/data.csv";

//�f�[�^�̃��[�h
GameObjectManager::GameObjectManager()
{
	Load::CreateInstance();
	load = Load::GetInstance();
	load->ReadFile(dataFilePath, true, true);
	load->LoadData();
}

//�f�[�^�̉��
GameObjectManager::~GameObjectManager()
{

}

//�C���X�^���X�̐���
void GameObjectManager::CreateInstance()
{
	if (!gameObjectManager)
	{
		gameObjectManager = new GameObjectManager();
	}
}

//�C���X�^���X�̔j��
void GameObjectManager::DestroyInstance()
{
	Load::DestroyInstance();
	if (gameObjectManager)
	{
		delete(gameObjectManager);
	}
}

//�C���X�^���X�̏�����
void GameObjectManager::InitObject()
{
	//�I�u�W�F�N�g���ǉ�����Ă������x����������
	if (!objectInstance.empty())
	{
		objectInstance.clear();
	}

	//�v���C���[�I�u�W�F�N�g�̒ǉ�
	objectInstance.push_back(new Player(load->GetPlayerModelHandle(),load->GetPlayerAnimationHandle()));

	//�t�B�[���h�I�u�W�F�N�g�̒ǉ�
	for (int i = initializeNum; i < load->GetFieldModelHandle().size(); i++)
	{
		objectInstance.push_back(new Field(load->GetFieldModelHandle().at(i), load->GetFieldPos().at(i)));
	}

	//��Q���I�u�W�F�N�g�̒ǉ�
	for (int i = initializeNum; i < load->GetObstacleModelHandle().size(); i++)
	{
		objectInstance.push_back(new Obstacle(load->GetObstacleModelHandle().at(i), load->GetObstaclePos().at(i)));
	}
}

//�I�u�W�F�N�g�S�̂̍X�V
void GameObjectManager::Update()
{

}

//�I�u�W�F�N�g�S�̂̕`��
void GameObjectManager::Draw()
{

}